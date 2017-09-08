/*
 *  tps65132.c 
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
#include "mdss_dsi.h"

static struct i2c_client *i2c_client = NULL;

static int tps65132_i2c_txdata(char *txdata, int length)
{
	int ret;
	struct i2c_msg msg = {
			.addr	= i2c_client->addr,
			.flags	= 0,
			.len	= length,
			.buf	= txdata,
	};

	ret = i2c_transfer(i2c_client->adapter, &msg, 1);
	if (ret < 0)
		pr_err("%s i2c write error: %d\n", __func__, ret);

	return ret;
}

void tps65132_write_reg(char buf[])
{
    	int ret = -1;

    	ret = tps65132_i2c_txdata(buf, 2);
    	if (ret < 0) {
        	pr_err("write reg failed! %#x ret: %d", buf[0], ret);
    	}
}

void tps65132_set_vol(char vol_buf[])
{
	tps65132_write_reg(vol_buf); 
}

static int __devinit tps65132_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	static const char *tps_ic_name;
   	i2c_client = client;

	tps_ic_name = of_get_property(client->dev.of_node, "label", NULL);
	if (!tps_ic_name) {
		printk("Unable to read device name\n");
		return -ENODEV;
	}
	printk("tps ic name = %s\n",tps_ic_name);
    	printk("tps65132 probe done\n");

    	return 0;
}

static int __devexit tps65132_remove(struct i2c_client *client)
{
	return 0;
}

static const struct i2c_device_id tps65132_id[] = {
	{ "tps65132_1", 0 },
	{ },
};

MODULE_DEVICE_TABLE(i2c, tps65132_id);

static struct of_device_id tps65132_match_table[] = {
	{ .compatible = "ti,tps65132",},
	{ },
};

static struct i2c_driver tps65132_driver = {
	.driver	= {
		.name	= "tps65132",
		.of_match_table = tps65132_match_table,
	},
	.probe		= tps65132_probe,
	.remove		= __devexit_p(tps65132_remove),
//	.suspend	= tps65132_suspend,
//	.resume	= tps65132_resume,
	.id_table	= tps65132_id,
};

static int __init tps65132_init(void)
{
	return i2c_add_driver(&tps65132_driver);
}

static void __exit tps65132_exit(void)
{
	i2c_del_driver(&tps65132_driver);
}

module_init(tps65132_init);
module_exit(tps65132_exit);

MODULE_AUTHOR("www.gionee.com");
MODULE_DESCRIPTION("tps65132 backlight driver");
MODULE_LICENSE("GPL");

