/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_NDEBUG 1

#include <cutils/log.h>

#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#include <sys/ioctl.h>
#include <sys/types.h>

#include <hardware/lights.h>

/******************************************************************************/

static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static struct light_state_t g_notification;
static struct light_state_t g_battery;
//Gionee liujiang 2013-10-15 add for CR00921377 start
static struct light_state_t g_rgb;
//Gionee liujiang 2013-10-15 add for CR00921377 end

static int g_attention = 0;

char const*const RED_LED_FILE
        = "/sys/class/leds/red/brightness";

char const*const GREEN_LED_FILE
        = "/sys/class/leds/green/brightness";

char const*const BLUE_LED_FILE
        = "/sys/class/leds/blue/brightness";

char const*const LCD_FILE
        = "/sys/class/leds/lcd-backlight/brightness";

//Gionee liujiang 2013-08-19 add for rgb led start
char const*const RED_STEP_MS_FILE
        = "/sys/class/leds/red/ramp_step_ms";

char const*const RED_DUTY_PCTS_FILE
        = "/sys/class/leds/red/duty_pcts";

char const*const RED_BLINK_FILE
        = "/sys/class/leds/red/blink";

char const*const GREEN_STEP_MS_FILE
        = "/sys/class/leds/green/ramp_step_ms";

char const*const GREEN_DUTY_PCTS_FILE
        = "/sys/class/leds/green/duty_pcts";

char const*const GREEN_BLINK_FILE
        = "/sys/class/leds/green/blink";

char const*const BLUE_STEP_MS_FILE
        = "/sys/class/leds/blue/ramp_step_ms";

char const*const BLUE_DUTY_PCTS_FILE
        = "/sys/class/leds/blue/duty_pcts";

char const*const BLUE_BLINK_FILE
        = "/sys/class/leds/blue/blink";
//Gionee liujiang 2013-08-19 add for rgb led end

//Gionee liujiang 2013-08-15 add for button led start
char const*const BUTTON_FILE
        = "/sys/class/leds/button-backlight/brightness";
//Gionee liujiang 2013-08-15 add for button led end

//Gionee wanglei, 2013-10-19 add for torch led, start
char const*const TORCH_FILE
        = "/sys/class/leds/led:flash_torch/brightness";
//Gionee wanglei, 2013-10-19 add for torch led, end

//Gionee liujiang 2013-08-19 add for rgb led start
#define	PWM_LUT_MAX_SIZE		62
#define RGB_MAX_LEVEL			255
#define GN_BSP_RGB_SMOOTHNESS_SUPPORT 1
//Gionee liujiang 2013-08-19 add for rgb led end

/**
 * device methods
 */

void init_globals(void)
{
    // init the mutex
    pthread_mutex_init(&g_lock, NULL);
}

static int
write_int(char const* path, int value)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        char buffer[20];
        int bytes = sprintf(buffer, "%d\n", value);
        int amt = write(fd, buffer, bytes);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            ALOGE("write_int failed to open %s\n", path);
            already_warned = 1;
        }
        return -errno;
    }
}

//Gionee liujiang 2013-08-19 add for rgb led start
static int
write_str(char const* path, char *str,int str_len)
{
    int fd;
    static int already_warned = 0;

    fd = open(path, O_RDWR);
    if (fd >= 0) {
        int amt = write(fd, str, str_len);
        close(fd);
        return amt == -1 ? -errno : 0;
    } else {
        if (already_warned == 0) {
            ALOGE("write_int failed to open %s\n", path);
            already_warned = 1;
        }
        return -errno;
    }
}
//Gionee liujiang 2013-08-19 add for rgb led end

static int
is_lit(struct light_state_t const* state)
{
    return state->color & 0x00ffffff;
}

static int
rgb_to_brightness(struct light_state_t const* state)
{
    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff))
            + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}

static int
set_light_backlight(struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    int brightness = rgb_to_brightness(state);
    pthread_mutex_lock(&g_lock);
    err = write_int(LCD_FILE, brightness);
    pthread_mutex_unlock(&g_lock);
    return err;
}

static int
set_speaker_light_locked(struct light_device_t* dev,
        struct light_state_t const* state)
{
    int len;
    int alpha, red, green, blue;
    int blink;
    int onMS, offMS;
    unsigned int colorRGB;

    switch (state->flashMode) {
        case LIGHT_FLASH_TIMED:
            onMS = state->flashOnMS;
            offMS = state->flashOffMS;
            break;
        case LIGHT_FLASH_NONE:
        default:
            onMS = 0;
            offMS = 0;
            break;
    }

    colorRGB = state->color;

#if LOG_NDEBUG
    ALOGE("set_speaker_light_locked mode %d, colorRGB=%08X, onMS=%d, offMS=%d\n",
            state->flashMode, colorRGB, onMS, offMS);
#endif

    red = (colorRGB >> 16) & 0xFF;
    green = (colorRGB >> 8) & 0xFF;
    blue = colorRGB & 0xFF;
	
	if ((!!red)+(!!green)+(!!blue) > 1)
		return 0;

    if (onMS > 0 && offMS > 0) {
#ifndef GN_BSP_RGB_SMOOTHNESS_SUPPORT
        int i,tmp,num1,num2;
		int brightness;
		int step_ms,on_step_num,off_step_num;
		int duty,str_len;
		char *tmp_ptr;
		char buf[4*PWM_LUT_MAX_SIZE];

		brightness = red+green+blue;
		num1 = (onMS > offMS)? onMS:offMS;
		num2 = (onMS > offMS)? offMS:onMS;
		if ((num1 / num2)>(PWM_LUT_MAX_SIZE-1))
		{
			num2 = num1 / (PWM_LUT_MAX_SIZE-1);
			num1 = num2 * (PWM_LUT_MAX_SIZE-1);
			onMS = (onMS > offMS)? num1:num2;
			offMS = (onMS > offMS)? num2:num1;
		}
		for(i=0;;i++)
		{
			if((num1%num2)==0)
			{
				tmp = num2;
				break;
			}
			else
			{
				tmp = num1 % num2;
				if((onMS/tmp)+(offMS/tmp) > PWM_LUT_MAX_SIZE)
				{
					tmp = num2;
					break;
				}
				num1 = num2;
				num2 = tmp;
			}
		}
		step_ms = tmp;
		on_step_num = onMS / step_ms;
		off_step_num = offMS / step_ms;
		if((on_step_num + off_step_num) > PWM_LUT_MAX_SIZE)
			ALOGE("set_speaker_light_locked step calc err!!!\n");
		duty = brightness*99/RGB_MAX_LEVEL;
		str_len = 0;
		tmp_ptr = buf;
		for (i = 0;i < off_step_num; i ++)
		{
			tmp_ptr = buf + str_len;
			str_len += sprintf(tmp_ptr,"%d,",0);
		}
		for (i = 0;i < on_step_num; i ++)
		{
			tmp_ptr = buf + str_len;
			str_len += sprintf(tmp_ptr,"%d,",duty);
		}
#else
#define DUTY_LEVEL  20
		char buf[4*DUTY_LEVEL] = "0,0,0,0,5,10,20,30,40,50,60,70,80,90,99,99,90,80,70,60,50,40,30,20,10,5,0,0,0,0";
		int step_ms;
		int str_len;

		step_ms = (onMS + offMS)/DUTY_LEVEL;
		str_len = strlen(buf);
#endif
//Gionee liujiang 2013-12-04 modify for CR00967403 start
		ALOGE("set_speaker_light_locked set pct = %s\n",buf);
		ALOGE("set_speaker_light_locked set step_ms = %d\n",step_ms);
		
		if(red > 0)
		{
			write_str(RED_DUTY_PCTS_FILE,buf,str_len);
			write_int(RED_STEP_MS_FILE,step_ms);
			write_int(GREEN_BLINK_FILE, 0);
			write_int(BLUE_BLINK_FILE, 0);
			write_int(RED_BLINK_FILE, 1);
		}
		else if(green > 0)
		{
			write_str(GREEN_DUTY_PCTS_FILE,buf,str_len);
			write_int(GREEN_STEP_MS_FILE,step_ms);
			write_int(BLUE_BLINK_FILE, 0);
			write_int(RED_BLINK_FILE, 0);
			write_int(GREEN_BLINK_FILE, 1);
		}
		else if(blue > 0)
		{
			write_str(BLUE_DUTY_PCTS_FILE,buf,str_len);
			write_int(BLUE_STEP_MS_FILE,step_ms);
			write_int(RED_BLINK_FILE, 0);
			write_int(GREEN_BLINK_FILE, 0);
			write_int(BLUE_BLINK_FILE, 1);
		}
    } else {
		write_int(RED_BLINK_FILE, 0);
		write_int(GREEN_BLINK_FILE, 0);
		write_int(BLUE_BLINK_FILE, 0);
		if(red > 0)
		{
			write_int(GREEN_LED_FILE, green);
			write_int(BLUE_LED_FILE, blue);
			write_int(RED_LED_FILE, red);
		}
		else if(green > 0)
		{
			write_int(BLUE_LED_FILE, blue);
			write_int(RED_LED_FILE, red);
			write_int(GREEN_LED_FILE, green);
		}
		else if(blue > 0)
		{
			write_int(RED_LED_FILE, red);
			write_int(GREEN_LED_FILE, green);
	    	write_int(BLUE_LED_FILE, blue);
		}
    }
//Gionee liujiang 2013-12-04 modify for CR00967403 end
//Gionee liujiang 2013-08-19 add for rgb led end

    return 0;
}

static void
handle_speaker_battery_locked(struct light_device_t* dev)
{
    if (is_lit(&g_battery)) {
        set_speaker_light_locked(dev, &g_battery);
    } else {
        set_speaker_light_locked(dev, &g_notification);
    }
}

static int
set_light_notifications(struct light_device_t* dev,
        struct light_state_t const* state)
{
    pthread_mutex_lock(&g_lock);
    g_notification = *state;
    handle_speaker_battery_locked(dev);
    pthread_mutex_unlock(&g_lock);
    return 0;
}

//Gionee liujiang 2013-10-15 add for charge light start
static int
set_light_battery(struct light_device_t* dev,
        struct light_state_t const* state)
{
	pthread_mutex_lock(&g_lock);
    g_battery = *state;
    handle_speaker_battery_locked(dev);
    pthread_mutex_unlock(&g_lock);
    return 0;
}

static void
handle_speaker_rgb_locked(struct light_device_t* dev)
{
    set_speaker_light_locked(dev, &g_rgb);
}

static int
set_light_rgb(struct light_device_t* dev,
        struct light_state_t const* state)
{
	pthread_mutex_lock(&g_lock);
    g_rgb = *state;
    handle_speaker_rgb_locked(dev);
    pthread_mutex_unlock(&g_lock);
    return 0;
}
//Gionee liujiang 2013-10-15 add for charge light end

static int
set_light_attention(struct light_device_t* dev,
        struct light_state_t const* state)
{
    pthread_mutex_lock(&g_lock);
    if (state->flashMode == LIGHT_FLASH_HARDWARE) {
        g_attention = state->flashOnMS;
    } else if (state->flashMode == LIGHT_FLASH_NONE) {
        g_attention = 0;
    }
    handle_speaker_battery_locked(dev);
    pthread_mutex_unlock(&g_lock);
    return 0;
}

static int
set_light_buttons(struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;

#if LOG_NDEBUG
	ALOGE("set_light_buttons  brightness=%d\n",(state->color & 0xFF));
#endif
    pthread_mutex_lock(&g_lock);
    err = write_int(BUTTON_FILE, state->color & 0xFF);
    pthread_mutex_unlock(&g_lock);
    return err;
}
//Gionee wanglei, 2013-10-19, add for torch led, start
static int
set_light_torch(struct light_device_t* dev,
        struct light_state_t const* state)
{
    int err = 0;
    pthread_mutex_lock(&g_lock);
    ALOGE("wanglei: set_light_torch --> open %s\n", TORCH_FILE);
    err = write_int(TORCH_FILE, state->color & 0xFF);
    ALOGE("wanglei: set_light_torch --> err = %d\n", err);
    pthread_mutex_unlock(&g_lock);
    return err;
}
//Gionee wanglei, 2013-10-19, add for torch led, end

/** Close the lights device */
static int
close_lights(struct light_device_t *dev)
{
    if (dev) {
        free(dev);
    }
    return 0;
}


/******************************************************************************/

/**
 * module methods
 */

/** Open a new instance of a lights device using name */
static int open_lights(const struct hw_module_t* module, char const* name,
        struct hw_device_t** device)
{
    int (*set_light)(struct light_device_t* dev,
            struct light_state_t const* state);

    if (0 == strcmp(LIGHT_ID_BACKLIGHT, name))
        set_light = set_light_backlight;
//Gionee liujiang 2013-10-15 modify for charge light start
    else if (0 == strcmp(LIGHT_ID_NOTIFICATIONS, name))
        set_light = set_light_rgb; //set_light_notifications;
//Gionee liujiang 2013-10-15 modify for charge light start
    else if (0 == strcmp(LIGHT_ID_BUTTONS, name))
        set_light = set_light_buttons;
//Gionee wanglei, 2013-10-19, add for torch led, start
	else if (0 == strcmp(LIGHT_ID_TORCH, name))
        set_light = set_light_torch;
//Gionee wanglei, 2013-10-19, add for torch led, end
//Gionee liujiang 2013-10-15 add for charge light start
	else if (0 == strcmp(LIGHT_ID_BATTERY, name))
		set_light = set_light_rgb; //set_light_battery;
//Gionee liujiang 2013-10-15 add for charge light end
    else
        return -EINVAL;

    pthread_once(&g_init, init_globals);

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;
    return 0;
}

static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "lights Module",
    .author = "Google, Inc.",
    .methods = &lights_module_methods,
};
