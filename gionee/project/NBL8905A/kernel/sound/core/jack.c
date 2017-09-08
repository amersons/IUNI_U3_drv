/*
 *  Jack abstraction layer
 *
 *  Copyright 2008 Wolfson Microelectronics
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <linux/input.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <sound/jack.h>
#include <sound/core.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/completion.h>
#include <linux/regulator/consumer.h>
#include <linux/err.h>
#include <linux/workqueue.h>
#include <linux/sched.h> 
#include <linux/interrupt.h>  


static int jack_switch_types[] = {
	SW_HEADPHONE_INSERT,
	SW_MICROPHONE_INSERT,
	SW_LINEOUT_INSERT,
	SW_JACK_PHYSICAL_INSERT,
	SW_VIDEOOUT_INSERT,
	SW_LINEIN_INSERT,
	SW_HPHL_OVERCURRENT,
	SW_HPHR_OVERCURRENT,
	SW_UNSUPPORT_INSERT,
	SW_MICROPHONE2_INSERT,
};

//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 begin
#ifdef CONFIG_GN_Q_BSP_AUDIO_MBHC_CALIBRATION

#define HOOK_KEYCODE_DELAY 500		//MS
#define HOOK_LONG_PRESS_DELAY 500		//MS
static struct delayed_work report_keycode_work;
static struct delayed_work report_hook_long_press_work;
static volatile int hook_press_counter;
static int hook_flag;
static int hook_long_press;
static int hook_value;
static struct snd_jack *jack_hook;

static void report_multi_keycode_handle (struct work_struct *work);
static void report_hook_long_press_handle (struct work_struct *work);
static void handle_jack_hookkey_press(void);
static void handle_jack_hookkey_long_press(void);

static void report_multi_keycode_handle(struct work_struct *work)
{
	int i;

	if(!jack_hook) {
		printk("Error::jack_hook is a NULL pointer!!!");
		return;
	}
	
	if (hook_press_counter == 1) {
		hook_value = SND_JACK_BTN_0;
		printk("%s::::::hook_press_counter=%d:::::::KEY_MEDIA\n", __func__, hook_press_counter);
	} else if (hook_press_counter == 2) {
		hook_value = SND_JACK_BTN_3;
		printk("%s:::::::hook_press_counter=%d::::::KEY_NEXTSONG\n", __func__, hook_press_counter);
	} else if (hook_press_counter > 2){
		hook_value = SND_JACK_BTN_4;
		printk("%s::::::hook_press_counter=%d:::::::KEY_PREVIOUSSONG\n", __func__, hook_press_counter);
	}

	for (i = 0; i < ARRAY_SIZE(jack_hook->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;
		if (jack_hook->type & testbit) {
			input_report_key(jack_hook->input_dev, jack_hook->key[i],
					 hook_value & testbit);
		}
	}

	for (i = 0; i < ARRAY_SIZE(jack_switch_types); i++) {
		int testbit = 1 << i;
		if (jack_hook->type & testbit)
			input_report_switch(jack_hook->input_dev,
					    jack_switch_types[i],
					    hook_value & testbit);
	}

	input_sync(jack_hook->input_dev);

	mdelay(50);

	for (i = 0; i < ARRAY_SIZE(jack_hook->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;
		if (jack_hook->type & testbit) {
			input_report_key(jack_hook->input_dev, jack_hook->key[i],
					 0 & testbit);
		}
	}

	for (i = 0; i < ARRAY_SIZE(jack_switch_types); i++) {
		int testbit = 1 << i;
		if (jack_hook->type & testbit)
			input_report_switch(jack_hook->input_dev,
					    jack_switch_types[i],
					    0 & testbit);
	}

	input_sync(jack_hook->input_dev);
	hook_press_counter = 0;
}

static void report_hook_long_press_handle (struct work_struct *work)
{
	int i;
	
	hook_long_press = 1;
	if (delayed_work_pending(&report_keycode_work)) {
		cancel_delayed_work_sync(&report_keycode_work);
	}

	if(!jack_hook) {
		printk("Error::jack_hook is a NULL pointer!!!");
		return;
	}
	
	for (i = 0; i < ARRAY_SIZE(jack_hook->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;
		if (jack_hook->type & testbit) {
			input_report_key(jack_hook->input_dev, jack_hook->key[i],
					 SND_JACK_BTN_0 & testbit);
		}
	}

	for (i = 0; i < ARRAY_SIZE(jack_switch_types); i++) {
		int testbit = 1 << i;
		if (jack_hook->type & testbit)
			input_report_switch(jack_hook->input_dev,
					    jack_switch_types[i],
					    SND_JACK_BTN_0 & testbit);
	}

	input_sync(jack_hook->input_dev);
	hook_press_counter = 0;
}

static void handle_jack_hookkey_press(void)
{

	if (delayed_work_pending(&report_hook_long_press_work)) {
		cancel_delayed_work_sync(&report_hook_long_press_work);
		hook_long_press = 0;
	}
	
	if (hook_press_counter == 0) {
		hook_press_counter ++;
        schedule_delayed_work(&report_keycode_work,
                msecs_to_jiffies(HOOK_KEYCODE_DELAY));
	} else if (hook_press_counter > 0) {
		if (delayed_work_pending(&report_keycode_work)) {
			cancel_delayed_work_sync(&report_keycode_work);
			hook_press_counter ++;
	        schedule_delayed_work(&report_keycode_work,
	                msecs_to_jiffies(HOOK_KEYCODE_DELAY));
		}
	}
}

static void handle_jack_hookkey_long_press(void)
{
    schedule_delayed_work(&report_hook_long_press_work,
            msecs_to_jiffies(HOOK_LONG_PRESS_DELAY));
}
#endif
//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 end

static int snd_jack_dev_free(struct snd_device *device)
{
	struct snd_jack *jack = device->device_data;

	if (jack->private_free)
		jack->private_free(jack);

	/* If the input device is registered with the input subsystem
	 * then we need to use a different deallocator. */
	if (jack->registered)
		input_unregister_device(jack->input_dev);
	else
		input_free_device(jack->input_dev);

	kfree(jack->id);
	kfree(jack);

	return 0;
}

static int snd_jack_dev_register(struct snd_device *device)
{
	struct snd_jack *jack = device->device_data;
	struct snd_card *card = device->card;
	int err, i;

	snprintf(jack->name, sizeof(jack->name), "%s %s",
		 card->shortname, jack->id);
	jack->input_dev->name = jack->name;

	/* Default to the sound card device. */
	if (!jack->input_dev->dev.parent)
		jack->input_dev->dev.parent = snd_card_get_device_link(card);

	/* Add capabilities for any keys that are enabled */
	for (i = 0; i < ARRAY_SIZE(jack->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;

		if (!(jack->type & testbit))
			continue;

		if (!jack->key[i])
			jack->key[i] = BTN_0 + i;

		input_set_capability(jack->input_dev, EV_KEY, jack->key[i]);
	}

	err = input_register_device(jack->input_dev);
	if (err == 0)
		jack->registered = 1;

	return err;
}

/**
 * snd_jack_new - Create a new jack
 * @card:  the card instance
 * @id:    an identifying string for this jack
 * @type:  a bitmask of enum snd_jack_type values that can be detected by
 *         this jack
 * @jjack: Used to provide the allocated jack object to the caller.
 *
 * Creates a new jack object.
 *
 * Returns zero if successful, or a negative error code on failure.
 * On success jjack will be initialised.
 */
int snd_jack_new(struct snd_card *card, const char *id, int type,
		 struct snd_jack **jjack)
{
	struct snd_jack *jack;
	int err;
	int i;
	static struct snd_device_ops ops = {
		.dev_free = snd_jack_dev_free,
		.dev_register = snd_jack_dev_register,
	};

	jack = kzalloc(sizeof(struct snd_jack), GFP_KERNEL);
	if (jack == NULL)
		return -ENOMEM;

	jack->id = kstrdup(id, GFP_KERNEL);

	jack->input_dev = input_allocate_device();
	if (jack->input_dev == NULL) {
		err = -ENOMEM;
		goto fail_input;
	}

	jack->input_dev->phys = "ALSA";

	jack->type = type;

	for (i = 0; i < ARRAY_SIZE(jack_switch_types); i++)
		if (type & (1 << i))
			input_set_capability(jack->input_dev, EV_SW,
					     jack_switch_types[i]);

	err = snd_device_new(card, SNDRV_DEV_JACK, jack, &ops);
	if (err < 0)
		goto fail_input;

	*jjack = jack;

//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 begin
#ifdef CONFIG_GN_Q_BSP_AUDIO_MBHC_CALIBRATION
	INIT_DELAYED_WORK(&report_keycode_work, report_multi_keycode_handle);
	INIT_DELAYED_WORK(&report_hook_long_press_work, report_hook_long_press_handle);
#endif
//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 end

	return 0;

fail_input:
	input_free_device(jack->input_dev);
	kfree(jack->id);
	kfree(jack);
	return err;
}
EXPORT_SYMBOL(snd_jack_new);

/**
 * snd_jack_set_parent - Set the parent device for a jack
 *
 * @jack:   The jack to configure
 * @parent: The device to set as parent for the jack.
 *
 * Set the parent for the jack input device in the device tree.  This
 * function is only valid prior to registration of the jack.  If no
 * parent is configured then the parent device will be the sound card.
 */
void snd_jack_set_parent(struct snd_jack *jack, struct device *parent)
{
	WARN_ON(jack->registered);

	jack->input_dev->dev.parent = parent;
}
EXPORT_SYMBOL(snd_jack_set_parent);

/**
 * snd_jack_set_key - Set a key mapping on a jack
 *
 * @jack:    The jack to configure
 * @type:    Jack report type for this key
 * @keytype: Input layer key type to be reported
 *
 * Map a SND_JACK_BTN_ button type to an input layer key, allowing
 * reporting of keys on accessories via the jack abstraction.  If no
 * mapping is provided but keys are enabled in the jack type then
 * BTN_n numeric buttons will be reported.
 *
 * Note that this is intended to be use by simple devices with small
 * numbers of keys that can be reported.  It is also possible to
 * access the input device directly - devices with complex input
 * capabilities on accessories should consider doing this rather than
 * using this abstraction.
 *
 * This function may only be called prior to registration of the jack.
 */
int snd_jack_set_key(struct snd_jack *jack, enum snd_jack_types type,
		     int keytype)
{
	int key = fls(SND_JACK_BTN_0) - fls(type);

	WARN_ON(jack->registered);

	if (!keytype || key >= ARRAY_SIZE(jack->key))
		return -EINVAL;

	jack->type |= type;
	jack->key[key] = keytype;
	
	return 0;
}
EXPORT_SYMBOL(snd_jack_set_key);

/**
 * snd_jack_report - Report the current status of a jack
 *
 * @jack:   The jack to report status for
 * @status: The current status of the jack
 */
void snd_jack_report(struct snd_jack *jack, int status)
{
	int i;

	if (!jack)
		return;

//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 begin
#ifdef CONFIG_GN_Q_BSP_AUDIO_MBHC_CALIBRATION
		if (status == SND_JACK_BTN_0 && hook_flag == 0) {
			jack_hook = jack;
			hook_flag = 1;
			handle_jack_hookkey_long_press();
			return;
		} else if (status == 0 && hook_flag == 1){
			jack_hook = jack;
			hook_flag = 0;
			if (hook_long_press == 0) {
				handle_jack_hookkey_press();
				return;
			} else {
				hook_long_press = 0;
			}
		} else {
			jack_hook = NULL;
		}
#endif
//Gionee huangzhuolin 20140626 add for U2 Multi-function headset CR01296447 end

	for (i = 0; i < ARRAY_SIZE(jack->key); i++) {
		int testbit = SND_JACK_BTN_0 >> i;
		if (jack->type & testbit) {
			input_report_key(jack->input_dev, jack->key[i],
					 status & testbit);
		}
	}

	for (i = 0; i < ARRAY_SIZE(jack_switch_types); i++) {
		int testbit = 1 << i;
		if (jack->type & testbit)
			input_report_switch(jack->input_dev,
					    jack_switch_types[i],
					    status & testbit);
	}

	input_sync(jack->input_dev);
}
EXPORT_SYMBOL(snd_jack_report);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("Jack detection support for ALSA");
MODULE_LICENSE("GPL");
