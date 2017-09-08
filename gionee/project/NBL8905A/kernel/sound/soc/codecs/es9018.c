/*
 * es9018.c -- es9018 ALSA SoC audio driver
 *
 * Copyright (C) 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/initval.h>
#include <sound/tlv.h>
#include <trace/events/asoc.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include "es9018.h"
#include <linux/i2c.h>

/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
#include <linux/proc_fs.h>

static struct proc_dir_entry *codec_dir;
#define BUFF_SIZE 64
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */

/* We only include the analogue supplies here; the digital supplies
 * need to be available well before this driver can be probed.
 */
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
char es9018_init_register[26]={
		0x00,//0  
		0x8c,//1  :I2S input 0X8c
		0x18,//2
		0x10,//3
		0x00,//4
		0x68,//5
		0x42,//6
		0x80,//7
		0x10,//8
		0x22,//9	:slave mode 0Xa2
		0x2d,//10
		0x02,//11
		0x5a,//12
		0x00,//13
		0x8a,//14
		0x00,//15
		0x00,//16
		0xff,//17
		0xff,//18
		0xff,//19
		0x7f,//20
		0x00,//21
		0x00,//22
		0x00,//23 
		0x00,//24
		0xf2//25 
	};
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */

/* codec private data */

struct es9018_data {
	int reset_gpio;
	int power_gpio;
	int i2c_scl_gpio;
	int i2c_sda_gpio;
	int i2c_addr;
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
	int isl_switch_gpio;
	int isl_select_gpio;
	int isl_mute_gpio;
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--
};

struct es9018_priv {
	struct snd_soc_codec *codec;
	struct i2c_client *i2c_client;
    struct es9018_data *es9018_data;
    struct delayed_work sleep_work;
    struct mutex power_lock;
} es9018_priv;



static unsigned int es9018_power_state = 0;
static struct es9018_priv *g_es9018_priv = NULL;
static int es9018_write_reg(struct i2c_client *client, int reg, u8 value);
#define ES9018_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |	\
		     SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |	\
		     SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_48000 |	\
		     SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_192000)

#define ES9018_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE | \
		       SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE | \
		       SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S24_BE | \
		       SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE)


static void power_gpio_H(void)
{
	printk("es9018:power_gpio_H\n");
	printk(" power_gpio_H_level = %d\n",  __gpio_get_value(g_es9018_priv->es9018_data->power_gpio));
	if ( __gpio_get_value(g_es9018_priv->es9018_data->power_gpio) == 0) {
        gpio_set_value(g_es9018_priv->es9018_data->power_gpio, 1);
        printk(" power_gpio_H_level_1= %d\n",  __gpio_get_value(g_es9018_priv->es9018_data->power_gpio));
    }	
}

static void power_gpio_L(void)
{
	printk("es9018:power_gpio_L\n");
	 printk("power_gpio_L_level = %d\n",__gpio_get_value(g_es9018_priv->es9018_data->power_gpio));
	if ( __gpio_get_value(g_es9018_priv->es9018_data->power_gpio) == 1) {
        gpio_set_value(g_es9018_priv->es9018_data->power_gpio, 0);
        printk("power_gpio_L_level_1 = %d\n",__gpio_get_value(g_es9018_priv->es9018_data->power_gpio));
    }	
}

static void reset_gpio_H(void)
{
	printk("es9018:reset_gpio_H\n");
	printk(" reset_gpio_H_level = %d\n", __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio));
	if ( __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio) == 0) {
        gpio_set_value(g_es9018_priv->es9018_data->reset_gpio, 1);
		udelay(1000);
        printk(" reset_gpio_H_level_1= %d\n", __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio));
    }	
}

static void reset_gpio_L(void)
{
	printk("es9018:reset_gpio_L\n");
	printk("reset_gpio_L_level = %d\n", __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio));
	if ( __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio) == 1) {
        gpio_set_value(g_es9018_priv->es9018_data->reset_gpio, 0);
		udelay(1000);
        printk("reset_gpio_L_level_1 = %d\n", __gpio_get_value(g_es9018_priv->es9018_data->reset_gpio));
    }	
}

static void select_gpio_L(void)
{
	gpio_set_value(g_es9018_priv->es9018_data->isl_select_gpio, 0);
}

static void select_gpio_H(void)
{
	gpio_set_value(g_es9018_priv->es9018_data->isl_select_gpio, 1);       
}


static int es9018_open(void)
{
	int i = 0;
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
	power_gpio_H();
	mdelay(1);
	reset_gpio_L();
    mdelay(5);
	reset_gpio_H();
	mdelay(1);
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */
	for(i=0;i<26;i++){ 
		es9018_write_reg(g_es9018_priv->i2c_client,i,es9018_init_register[i]);
	}
  	//power_gpio_L();
	select_gpio_L();
	return 0;
}

static int es9018_close(void)
{
	select_gpio_H();
	reset_gpio_L();
	power_gpio_L();
	return 0;
}

static int es9018_get_power_state_enum(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	pr_info("GAC:%s(): power state = %d\n", __func__,
		es9018_power_state);
	ucontrol->value.enumerated.item[0] = es9018_power_state;
	pr_info("%s(): ucontrol = %d\n", __func__,
		ucontrol->value.enumerated.item[0]);

	return 0;
}

static int es9018_put_power_state_enum(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	int ret=0;
	printk("es9018:ucontrol = %d\n",ucontrol->value.enumerated.item[0]);
	printk("es9018:power state= %d\n",es9018_power_state);

	if (es9018_power_state == ucontrol->value.enumerated.item[0]) {
		pr_info("GAC:%s():no power state change\n", __func__);
	}

	if (ucontrol->value.enumerated.item[0])
		ret = es9018_open();
	else 
		ret = es9018_close();

    es9018_power_state = ucontrol->value.enumerated.item[0];
	return ret;
}


static const char * const es9018_power_state_texts[] = {
	"Close","Open"
};

static const struct soc_enum es9018_power_state_enum =
	SOC_ENUM_SINGLE(SND_SOC_NOPM, 0,
			ARRAY_SIZE(es9018_power_state_texts),
			es9018_power_state_texts);

static struct snd_kcontrol_new es9018_digital_ext_snd_controls[] = {
	/* commit controls */
	
	SOC_ENUM_EXT("Set HIFI es9018 State", es9018_power_state_enum,
		       es9018_get_power_state_enum, es9018_put_power_state_enum)

};

static int es9018_read_reg(struct i2c_client *client, int reg)
{
	int ret;

	ret = i2c_smbus_read_byte_data(client, reg);
	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return ret;
}

static int es9018_write_reg(struct i2c_client *client, int reg, u8 value)
{

	int ret,i;

	for (i=0; i<3; i++)
	{
		ret = i2c_smbus_write_byte_data(client, reg, value);
		if (ret < 0)
		{
			dev_err(&client->dev, "%s: err %d,and try again\n", __func__, ret);
			mdelay(50);
		}
		else
			break;
	}

	if (ret < 0)
		dev_err(&client->dev, "%s: err %d\n", __func__, ret);

	return ret;
}

static int es9018_populate_get_pdata(struct device *dev,
			struct es9018_data *pdata)
{
	
	pdata->reset_gpio = of_get_named_gpio(dev->of_node,
				"dac,reset-gpio", 0);
	if (pdata->reset_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"dac,reset-gpio", dev->of_node->full_name,
			pdata->reset_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: reset gpio %d", __func__, pdata->reset_gpio);

	pdata->i2c_scl_gpio= of_get_named_gpio(dev->of_node,
				"dac,i2c-scl-gpio", 0);
	if (pdata->i2c_scl_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"dac,i2c-scl-gpio", dev->of_node->full_name,
			pdata->i2c_scl_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: i2c_scl_gpio %d", __func__, pdata->i2c_scl_gpio);

	pdata->i2c_sda_gpio= of_get_named_gpio(dev->of_node,
				"dac,i2c-sda-gpio", 0);
	if (pdata->i2c_sda_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"dac,i2c-sda-gpio", dev->of_node->full_name,
			pdata->i2c_sda_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: power gpio %d", __func__, pdata->power_gpio);

	pdata->power_gpio= of_get_named_gpio(dev->of_node,
				"dac,power-gpio", 0);
	if (pdata->power_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"dac,power-gpio", dev->of_node->full_name,
			pdata->power_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: power gpio %d", __func__, pdata->power_gpio);

	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
	pdata->isl_switch_gpio = of_get_named_gpio(dev->of_node,
				"isl,hifi-swh", 0);
	if (pdata->isl_switch_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"isl,hifi-swh", dev->of_node->full_name,
			pdata->isl_switch_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: switch gpio %d", __func__, pdata->isl_switch_gpio);

	pdata->isl_select_gpio = of_get_named_gpio(dev->of_node,
				"isl,hifi-sel", 0);
	if (pdata->isl_select_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"isl,hifi-sel", dev->of_node->full_name,
			pdata->isl_select_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: select gpio %d", __func__, pdata->isl_select_gpio);

	pdata->isl_mute_gpio = of_get_named_gpio(dev->of_node,
				"isl,ear-mute", 0);
	if (pdata->isl_mute_gpio < 0) {
		dev_err(dev, "Looking up %s property in node %s failed %d\n",
			"isl,ear-mute", dev->of_node->full_name,
			pdata->isl_mute_gpio);
		goto err;
	}
	dev_dbg(dev, "%s: mute gpio %d", __func__, pdata->isl_mute_gpio);
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--



	return 0;
err:
	devm_kfree(dev, pdata);
	return -1;
}

static unsigned int es9018_codec_read(struct snd_soc_codec *codec,
				      unsigned int reg)
{
	//struct es9018_priv *priv = codec->control_data;
	return 0;
}

static int es9018_codec_write(struct snd_soc_codec *codec, unsigned int reg,
			      unsigned int value)
{
	//struct es9018_priv *priv = codec->control_data;
	return 0;
}


static int es9018_set_bias_level(struct snd_soc_codec *codec,
				 enum snd_soc_bias_level level)
{
	int ret = 0;

	/* dev_dbg(codec->dev, "%s(codec, level = 0x%04x): entry\n", __func__, level); */

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		break;

	case SND_SOC_BIAS_STANDBY:
		break;

	case SND_SOC_BIAS_OFF:
		break;
	}
	codec->dapm.bias_level = level;

	/* dev_dbg(codec->dev, "%s(): exit\n", __func__); */
	return ret;
}

static int es9018_suspend(struct snd_soc_codec *codec)
{
	es9018_set_bias_level(codec, SND_SOC_BIAS_OFF);
	return 0;
}

static int es9018_resume(struct snd_soc_codec *codec)
{
	es9018_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	return 0;
}

static int es9018_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *codec_dai)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;
}

static int es9018_mute(struct snd_soc_dai *dai, int mute)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;

}

static int es9018_set_clkdiv(struct snd_soc_dai *codec_dai, int div_id, int div)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;
}

static int es9018_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;
}


static int es9018_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;
}

static int es9018_set_fll(struct snd_soc_dai *codec_dai,
			  int pll_id, int source, unsigned int freq_in,
			  unsigned int freq_out)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	
	return 0;
}


static int es9018_pcm_trigger(struct snd_pcm_substream *substream,
			      int cmd, struct snd_soc_dai *codec_dai)
{
	//struct snd_soc_codec *codec = codec_dai->codec;
	//struct es9018_priv *priv = codec->control_data;
	return 0;
}

static unsigned char reg_addr = 0, reg_value = 0;
static ssize_t es9018_reg_addr_show(
        struct device *dev, struct device_attribute *attr, char *buf)
{
    sprintf(buf, "0x%x\n", reg_addr);

    return strlen(buf);
}
static ssize_t es9018_reg_addr_store(
        struct device *dev, struct device_attribute *attr,
        char const *buf, size_t count)
{
    char *p, *tmp = NULL;
    int addr;                

    tmp = kmalloc(strlen(buf)+1, GFP_KERNEL);
    if (NULL == tmp){
        printk("malloc memory fail\n");
        return -1;
    }

    strncpy(tmp, buf, strlen(buf)+1);

    p = tmp;    
    while(*(p++))
        if (*p=='X') *p='x';

    sscanf(tmp, "0x%x", &addr);
    if (addr <= 0xff)
        reg_addr = addr;

    kfree(tmp);

    return strlen(buf);
}

static ssize_t es9018_reg_value_show(
        struct device *dev, struct device_attribute *attr, char *buf)
{
    reg_value = es9018_read_reg(g_es9018_priv->i2c_client, reg_addr);      

    sprintf(buf, "0x%x\n", reg_value);

    return strlen(buf);
}
static ssize_t es9018_reg_value_store(
        struct device *dev, struct device_attribute *attr,
        char const *buf, size_t count)
{
    char *p, *tmp = NULL;
    int value = 0;

    tmp = kmalloc(strlen(buf)+1, GFP_KERNEL);
    if (NULL == tmp){
        printk("malloc memory fail\n");
        return -1;
    }

    strncpy(tmp, buf, strlen(buf)+1);

    p = tmp;
    while(*(p++))
        if (*p=='X') *p='x';

    sscanf(tmp, "0x%x", &value);
    if (value <= 0xff)
        reg_value = value;

    kfree(tmp);

    es9018_write_reg(g_es9018_priv->i2c_client, reg_addr, reg_value);      

    return strlen(buf);
}

// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
static ssize_t isl_switch_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int value;

	value = __gpio_get_value(g_es9018_priv->es9018_data->isl_switch_gpio);
	sprintf(buf, "  %d\n", value);

	return strlen(buf);
}

static ssize_t isl_switch_store(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t count)
{
	int value = 0;

	if (sscanf(buf, "%d", &value) == 1) {
		printk("[xLin] 1value: %d", value);
		if (value == 0) {
			printk("[xLin] 2value: %d", value);
			gpio_set_value(g_es9018_priv->es9018_data->isl_switch_gpio, 0);
		} else {
			printk("[xLin] 3value: %d", value);
			gpio_set_value(g_es9018_priv->es9018_data->isl_switch_gpio, 1);
		}
		return count;
	}
	return -EINVAL;
}

static ssize_t isl_mute_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int value = 0;

	value = __gpio_get_value(g_es9018_priv->es9018_data->isl_mute_gpio);
	sprintf(buf, "  %d\n", value);

	return strlen(buf);
}

static ssize_t isl_mute_store(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t count)
{
	int value = 0;

	if (sscanf(buf, "%d", &value) == 1) {
		if (value == 0) {
			gpio_set_value(g_es9018_priv->es9018_data->isl_mute_gpio, 0);
		} else {
			gpio_set_value(g_es9018_priv->es9018_data->isl_mute_gpio, 1);
		}
		return count;
	}
	return -EINVAL;
}

static ssize_t isl_select_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int value = 0;

	value = __gpio_get_value(g_es9018_priv->es9018_data->isl_select_gpio);
	sprintf(buf, "  %d\n", value);

	return strlen(buf);
}

static ssize_t isl_select_store(struct device *dev,
		struct device_attribute *attr, char const *buf, size_t count)
{
	int value = 0;

	if (sscanf(buf, "%d", &value) == 1) {
		if (value == 0) {
			gpio_set_value(g_es9018_priv->es9018_data->isl_select_gpio, 0);
		} else {
			gpio_set_value(g_es9018_priv->es9018_data->isl_select_gpio, 1);
		}
		return count;
	}
	return -EINVAL;
}
// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--

DEVICE_ATTR(addr, S_IRUGO |S_IWUGO, es9018_reg_addr_show, es9018_reg_addr_store);
DEVICE_ATTR(value, S_IRUGO |S_IWUGO, es9018_reg_value_show, es9018_reg_value_store);
// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
DEVICE_ATTR(switch_gpio, S_IRUGO |S_IWUGO, isl_switch_show, isl_switch_store);
DEVICE_ATTR(select_gpio, S_IRUGO |S_IWUGO, isl_select_show, isl_select_store);
DEVICE_ATTR(mute_gpio, S_IRUGO |S_IWUGO, isl_mute_show, isl_mute_store);
// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--

static struct device_attribute *gn_es9018_attr_list[] = {
    &dev_attr_addr,
    &dev_attr_value,
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
	&dev_attr_switch_gpio,
	&dev_attr_select_gpio,
	&dev_attr_mute_gpio,
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--
};

static int gn_device_create_attr(struct device *dev) 
{
    int idx, err = 0;
    int num = (int)(sizeof(gn_es9018_attr_list)/sizeof(gn_es9018_attr_list[0]));

    if(!dev){
        return -EINVAL;
    }	

    for(idx = 0; idx < num; idx++){
        if((err = device_create_file(dev, gn_es9018_attr_list[idx]))){            
            printk("device_create_file (%s) = %d\n", gn_es9018_attr_list[idx]->attr.name, err);        
            break;
        }
    }

    return err;
}

//static int gn_device_remove_attr(struct device *dev)
//{
  //  int idx;
  //  int num = (int)(sizeof(gn_es9018_attr_list)/sizeof(gn_es9018_attr_list[0]));

   // if(!dev){
  //      return -EINVAL;
  //  }	

  //  for(idx = 0; idx < num; idx++){
  //      device_remove_file(dev, gn_es9018_attr_list[idx]);
   // }	

   // return 0;
//}

static const struct snd_soc_dai_ops es9018_dai_ops = {
	 .hw_params	= es9018_pcm_hw_params,
	 .digital_mute	= es9018_mute,
	 .trigger	= es9018_pcm_trigger,
	 .set_fmt	= es9018_set_dai_fmt,
	 .set_sysclk	= es9018_set_dai_sysclk,
	 .set_pll	= es9018_set_fll,
	 .set_clkdiv	= es9018_set_clkdiv,
};

static struct snd_soc_dai_driver es9018_dai = {
	.name = "es9018-hifi",
	.playback = {
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = ES9018_RATES,
		.formats = ES9018_FORMATS,
	},
	.capture = {
		 .stream_name = "Capture",
		 .channels_min = 2,
		 .channels_max = 2,
		 .rates = ES9018_RATES,
		 .formats = ES9018_FORMATS,
	 },
	.ops = &es9018_dai_ops,
};

static  int es9018_codec_probe(struct snd_soc_codec *codec)
{
	int rc = 0;
	struct es9018_priv *priv = snd_soc_codec_get_drvdata(codec);
	dev_info(codec->dev, "%s(): entry\n", __func__);
	dev_info(codec->dev, "%s(): codec->name = %s\n", __func__, codec->name);
    printk("es9018_codec_probe !!!!!!!!!!");


	priv->codec = codec;

	codec->control_data = snd_soc_codec_get_drvdata(codec);

	dev_info(codec->dev, "%s(): codec->control_data = 0x%08x\n", __func__, (unsigned int)codec->control_data);

	es9018_set_bias_level(codec, SND_SOC_BIAS_STANDBY);

	
	rc = snd_soc_add_codec_controls(codec, es9018_digital_ext_snd_controls,
					ARRAY_SIZE(es9018_digital_ext_snd_controls));
	if (rc)
		dev_err(codec->dev, "%s(): es325_digital_snd_controls failed\n", __func__);
	
	//es9018_open();
	dev_info(codec->dev, "%s(): exit\n", __func__);

	return 0;
}

static int  es9018_codec_remove(struct snd_soc_codec *codec)
{
	struct es9018_priv *priv = snd_soc_codec_get_drvdata(codec);
	
	es9018_set_bias_level(codec, SND_SOC_BIAS_OFF);

	kfree(priv);

	return 0;
}

static struct snd_soc_codec_driver soc_codec_dev_es9018 = {
	.probe =	es9018_codec_probe,
	.remove =	es9018_codec_remove,
	.suspend = 	es9018_suspend,
	.resume =	es9018_resume,
	.read = es9018_codec_read,
	.write = es9018_codec_write,
	.set_bias_level = es9018_set_bias_level,
};

static int __devinit es9018_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
	struct es9018_priv *priv;
	struct es9018_data *pdata;
    int ret = 0;
    printk("es9018_probe !!!!!!!!!!\n");


	if (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev, "%s: no support for i2c read/write"
				"byte data\n", __func__);
		return -EIO;
	}

	if (client->dev.of_node) {
		pdata = devm_kzalloc(&client->dev,
			sizeof(struct es9018_data), GFP_KERNEL);
		if (!pdata) {
			dev_err(&client->dev, "Failed to allocate memory\n");
			return -ENOMEM;
		}

		ret = es9018_populate_get_pdata(&client->dev, pdata);
		if (ret) {
			dev_err(&client->dev, "Parsing DT failed(%d)", ret);
			return ret;
		}
	} else
		pdata = client->dev.platform_data;

	if (!pdata) {
		dev_err(&client->dev, "%s: no platform data\n", __func__);
		return -EINVAL;
	}

	priv = devm_kzalloc(&client->dev, sizeof(struct es9018_priv),
			    GFP_KERNEL);
	if (priv == NULL)
		return -ENOMEM;
    priv->i2c_client = client;
	priv->es9018_data = pdata;
	i2c_set_clientdata(client, priv);
	
	g_es9018_priv = priv;

	ret = gpio_request(pdata->power_gpio, "es9018_power");
	if (ret < 0) {
		dev_err(&client->dev, "%s(): es9018 _power_gpio request failed",
			__func__);
		goto power_gpio_request_error;
	}
	ret = gpio_direction_output(pdata->power_gpio, 1);
	if (ret < 0) {
	pr_err("%s: speaker_PA direction failed\n",
			   __func__);
		goto power_gpio_request_error;
	}
	gpio_set_value(pdata->power_gpio, 0);

	ret = gpio_request(pdata->reset_gpio, "es9018_reset");
	if (ret < 0) {
		dev_err(&client->dev, "%s(): es9018_reset request failed",
			__func__);
		goto reset_gpio_request_error;
	}
	ret = gpio_direction_output(pdata->reset_gpio, 1);
	if (ret < 0) {
	pr_err("%s: speaker_PA direction failed\n",
			   __func__);
		goto reset_gpio_request_error;
	}
	gpio_set_value(pdata->reset_gpio, 0);

	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
	ret = gpio_request(pdata->isl_switch_gpio, "isl_switch");
	if (ret < 0) {
		dev_err(&client->dev, "%s(): isl_switch request failed",
			__func__);
		goto switch_gpio_request_error;
	}
	ret = gpio_direction_output(pdata->isl_switch_gpio, 1);
	if (ret < 0) {
		pr_err("%s: switch_gpio direction failed\n",
			   __func__);
		goto switch_gpio_request_error;
	}
	gpio_set_value(pdata->isl_switch_gpio, 1);

	ret = gpio_request(pdata->isl_mute_gpio, "isl_mute");
	if (ret < 0) {
		dev_err(&client->dev, "%s(): isl_mute request failed",
			__func__);
		goto mute_gpio_request_error;
	}
	ret = gpio_direction_output(pdata->isl_mute_gpio, 1);
	if (ret < 0) {
		pr_err("%s: mute_gpio direction failed\n",
			   __func__);
		goto mute_gpio_request_error;
	}
	gpio_set_value(pdata->isl_mute_gpio, 0);

	ret = gpio_request(pdata->isl_select_gpio, "isl_select");
	if (ret < 0) {
		dev_err(&client->dev, "%s(): isl_select request failed",
			__func__);
		goto select_gpio_request_error;
	}
	ret = gpio_direction_output(pdata->isl_select_gpio, 1);
	if (ret < 0) {
		pr_err("%s: select_gpio direction failed\n",
			   __func__);
		goto select_gpio_request_error;
	}
	gpio_set_value(pdata->isl_select_gpio, 1);
	// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--
	if (client->dev.of_node)
		dev_set_name(&client->dev, "%s", "es9018-codec");

	if(gn_device_create_attr(&client->dev) != 0){
        printk("%s:unable to create attributes!!\n",__func__);
        return -1;
    }

	ret = snd_soc_register_codec(&client->dev, &soc_codec_dev_es9018,
			&es9018_dai, 1);
    
    return ret;

reset_gpio_request_error:
	gpio_free(pdata->reset_gpio);
power_gpio_request_error:
	gpio_free(pdata->power_gpio);
	return ret;
// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. -->
switch_gpio_request_error:
	gpio_free(pdata->isl_switch_gpio);
	return ret;
mute_gpio_request_error:
	gpio_free(pdata->isl_mute_gpio);
	return ret;
select_gpio_request_error:
	gpio_free(pdata->isl_select_gpio);
	return ret;
// Gionee Driver, XiongLin, 20140810, add for ES9018 HiFi chip. <--

}

static int __devexit es9018_remove(struct i2c_client *client)
{
	return 0;
}

static struct of_device_id es9018_match_table[] = {
	{ .compatible = "dac,es9018-codec", },
	{}
};

static const struct i2c_device_id es9018_id[] = {
	{ "es9018", 0 },
	{ },
};
MODULE_DEVICE_TABLE(i2c, isa1200_id);

static struct i2c_driver es9018_driver = {
	.driver	= {
		.name	= "es9018-codec",
		.of_match_table = es9018_match_table,
	},
	.probe		= es9018_probe,
	.remove		= __devexit_p(es9018_remove),
	//.suspend	= es9018_suspend,
	//.resume		= es9018_resume,
	.id_table	= es9018_id,
};

/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
/*
 *write reg 0x01 as 0x55: echo 0x01 0x55 > /proc/codec/reg_write
 */

static ssize_t proc_write_reg(struct file *file, const char *buffer,
							  unsigned long length, void *data)
{
		char reg_str[BUFF_SIZE] = {0};
		unsigned int reg;
		unsigned int value;
		char *str_end;
		int i;

		if (length > BUFF_SIZE - 1)
				length = BUFF_SIZE - 1;
		if (copy_from_user(reg_str, buffer, length))
				return -EINVAL;
		printk("%s\n", reg_str);
		reg_str[length] = '\0';

		reg = simple_strtoul(reg_str, &str_end, 16);
		printk("reg: %#x\n", reg);
		value = simple_strtoul(str_end + 1, NULL, 16);
		printk("value: %#x\n", value);

		if(reg == 0xfe){
			printk("power down");
			power_gpio_L();
			return length;
		}else if(reg == 0xfd){
			printk("power up");
			power_gpio_H();
			return length;
		}else if(reg == 0xfc){
			printk("init reg");
			for(i=0;i<26;i++){
				es9018_write_reg(g_es9018_priv->i2c_client,i,es9018_init_register[i]);
			}
			return length;
		}
		else if(reg == 0xfb){
			gpio_set_value(g_es9018_priv->es9018_data->isl_select_gpio, value);
			return length;
		}else if(reg == 0xfa){
			printk("reset H");
			reset_gpio_H();
			return length;
		}else if(reg == 0xf9){
			printk("reset L");
			reset_gpio_L();
			return length;
		}
		es9018_write_reg(g_es9018_priv->i2c_client, reg, value);

		return length;
}
/*
 * read all reg: echo 0xff > /proc/codec/reg_read
 * read 0x01 reg: echo 0x01 > /proc/codec/reg_read
 */
static ssize_t proc_read_reg(struct file *file, const char *buffer,
										unsigned long length, void * data)
{
		char reg_str[BUFF_SIZE] = {'0'};
		unsigned int reg;
		int i;

		if (length > BUFF_SIZE - 1)
				length = BUFF_SIZE - 1;
		if (copy_from_user(reg_str, buffer, length))
				return -EINVAL;

		printk("%s\n", reg_str);
		reg_str[length] = '\0';
		reg = simple_strtoul(reg_str, NULL, 16);
		if(reg == 0xff){
			for(i = 0; i < sizeof(es9018_init_register); ++i){
				printk("reg(%#x):%#x\n", i, es9018_read_reg(g_es9018_priv->i2c_client, i));
			}
		}else
			printk("reg(%#x):%#x\n", reg, es9018_read_reg(g_es9018_priv->i2c_client, reg));

		return length;
}

static void init_proc(void)
{
		struct proc_dir_entry *reg_read, *reg_write;

		codec_dir = proc_mkdir("codec", NULL);
		reg_read = create_proc_entry("reg_read", 0644, codec_dir);
		if (reg_read)
				reg_read->write_proc = proc_read_reg;

		reg_write = create_proc_entry("reg_write", 0644, codec_dir);
		if (reg_write)
				reg_write->write_proc = proc_write_reg;

}

static void remove_proc(void)
{
		remove_proc_entry("reg_read", codec_dir);
		remove_proc_entry("reg_write", codec_dir);
}
/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */
static int __init es9018_init(void)
{
	/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
	init_proc();
	/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */
	return i2c_add_driver(&es9018_driver);
}

static void __exit es9018_exit(void)
{
	/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin */
	remove_proc();
	/* GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end */
	i2c_del_driver(&es9018_driver);
}

module_init(es9018_init);
module_exit(es9018_exit);

MODULE_DESCRIPTION("ASoC ES9018 driver");
MODULE_AUTHOR("Weiwei Gionee");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:es9018-codec");
