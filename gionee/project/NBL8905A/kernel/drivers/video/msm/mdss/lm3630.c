/*
 *  lm3630.c 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/pwm.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>
#include "../../../staging/android/timed_output.h"
#include <linux/of_gpio.h>

bool sleep = 1;
static struct i2c_client *i2c_client = NULL;
#include <linux/leds.h>
#define LCD_CABC_MAX_NUM 1

static int lm3630_write_reg(u8 addr, u8 para);
static void lm3630_change_mode(int mode)
{
	if (mode == 0)
		lm3630_write_reg(0x01,0x08);// 0x09 disable cabc
	else if(mode == 1)
		lm3630_write_reg(0x01,0x08);// 0x09 enable cabc
	else
		printk("lm3630 mode wrong\n");
}
static void lcd_cabc_mode_set(struct led_classdev *led_cdev, enum led_brightness brightness)
{
	unsigned int level;
	level = (int) brightness;
	printk("change cabc mode to %d\n",level);
	lm3630_change_mode(level);
}
static struct led_classdev backlight_cabc = {
	.name = "lcd-cabc",
	.brightness = LCD_CABC_MAX_NUM,
	.brightness_set = lcd_cabc_mode_set,
};


static int lm3630_i2c_txdata(char *txdata, int length)
{
	int ret;
	struct i2c_msg msg = {
			.addr	= i2c_client->addr,
			.flags	= 0,
			.len	= length,
			.buf	= txdata,
	};

   	//msleep(1);
	ret = i2c_transfer(i2c_client->adapter, &msg, 1);
	if (ret < 0)
		pr_err("%s i2c write error: %d\n", __func__, ret);

	return ret;
}

static int lm3630_write_reg(u8 addr, u8 para)
{
    u8 buf[3];
    int ret = -1;

    buf[0] = addr;
    buf[1] = para;
    ret = lm3630_i2c_txdata(buf, 2);
    if (ret < 0) {
        pr_err("write reg failed! %#x ret: %d", buf[0], ret);
        return -1;
    }
    
    return 0;
}

int cabc_change = 0;
void set_backlight_lm3630(unsigned int level)
{
	u8 para;

	para = (u8) (level);
	printk("mdss:backlight level = %d\n",para);
	if(para == 0)
	{
		printk("mdss:backlight level = 0\n");//add for check backlight on or not for cr 00922981 
		if(sleep == 1)
			return ;
	
		lm3630_write_reg(0x03,para & 0xff);
		lm3630_write_reg(0x04,para & 0x00);
//		lm3630_write_reg(0x03,para);
//		lm3630_write_reg(0x04,para);
		sleep = 1;
	}
	else
	{
		if(sleep == 1)
		{
			printk("init the lm3630 register\n");
			lm3630_write_reg(0x00,0x11);
			if(level > 60)
			{
				lm3630_write_reg(0x01,0x08);// 0x09 for cabc
				cabc_change = 1;
			}
			else
			{	
				lm3630_write_reg(0x01,0x08);// 0x09 for cabc
				cabc_change = 0;
			}
			lm3630_write_reg(0x02,0x33);//set freq to 1M for 4.7 u
			lm3630_write_reg(0x05,0x14);
			lm3630_write_reg(0x03,para & 0xff);
			lm3630_write_reg(0x04,para & 0x00);
			lm3630_write_reg(0x00,0x17);

			sleep = 0;
		}
		else
		{
			if(level < 60)
			{
				if(1 == cabc_change)
				{
					lm3630_write_reg(0x01,0x08);// 0x09 for cabc
					cabc_change = 0;
				}
			}else {
				if(0 == cabc_change)
				{
					lm3630_write_reg(0x01,0x08);// 0x09 for cabc
					cabc_change = 1;
				}
			}

			lm3630_write_reg(0x03,para & 0xff);
			lm3630_write_reg(0x04,para & 0x00);
		}
	}
}


static int __devinit lm3630_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int err = 0;
	static const char *backlight_ic_name;
   	i2c_client = client;

	backlight_ic_name = of_get_property(client->dev.of_node, "label", NULL);
	if (!backlight_ic_name) {
		printk("Unable to read device name\n");
		return -ENODEV;
	}
	printk("backlight ic name = %s\n",backlight_ic_name);

    	msleep(10);  

  	err =  lm3630_write_reg(0x00,0x17);


    	if (err<0)
    	{
        	printk( " fail to write tpd cfg %d\n", err );
        	return err;
    	}

	if (led_classdev_register(&client->dev, &backlight_cabc))
		pr_err("led_classdev_register failed\n");
    	printk("lm3630 probe done\n");
    	return 0;
}

static int __devexit lm3630_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id lm3630_id[] = {
	{ "lm3630_1", 0 },
	{ },
};

MODULE_DEVICE_TABLE(i2c, lm3630_id);

static struct of_device_id lm3630_match_table[] = {
	{ .compatible = "ti,lm3630",},
	{ },
};

static struct i2c_driver lm3630_driver = {
	.driver	= {
		.name	= "lm3630",
		.of_match_table = lm3630_match_table,
	},
	.probe		= lm3630_probe,
	.remove		= __devexit_p(lm3630_remove),
	.id_table	= lm3630_id,
};

static int __init lm3630_init(void)
{
	return i2c_add_driver(&lm3630_driver);
}

static void __exit lm3630_exit(void)
{
	i2c_del_driver(&lm3630_driver);
}

module_init(lm3630_init);
module_exit(lm3630_exit);

MODULE_AUTHOR("www.gionee.com");
MODULE_DESCRIPTION("lm3630 backlight driver");
MODULE_LICENSE("GPL");
