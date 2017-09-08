/*
 *  hall_key.c - Hall-Key driver
 *
 *  Copyright (C) 2014 gionee Electronics
 *  liujiang <liujiang@gionee.com>
 *  Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/regulator/consumer.h>
#include <linux/of_gpio.h>
#include <linux/input.h>
#include <linux/platform_device.h>

struct hall_key_regulator {
	const char *name;
	u32	min_uV;
	u32	max_uV;
	u32	load_uA;
};
	
struct hall_key_chip {
	const char *name;
	struct regulator **regs;
	struct device *dev;
	int irq; 
	struct input_dev *input_dev;
	int irq_gpio;
	unsigned long irq_flags;
	struct hall_key_regulator *regulator_info;
	u8 num_regulators;
};

static int hall_key_reg_power(struct hall_key_chip *hall_key, bool on)
{
	const struct hall_key_regulator *reg_info =
				hall_key->regulator_info;
	u8 i, num_reg = hall_key->num_regulators;
	int rc;

	for (i = 0; i < num_reg; i++) {
		rc = regulator_set_optimum_mode(hall_key->regs[i],
					on ? reg_info[i].load_uA : 0);
		if (rc < 0) {
			pr_err("%s: regulator_set_optimum_mode failed(%d)\n",
							__func__, rc);
			goto regs_fail;
		}

		rc = on ? regulator_enable(hall_key->regs[i]) :
			regulator_disable(hall_key->regs[i]);
		if (rc < 0) {
			pr_err("%s: regulator %sable fail %d\n", __func__,
					on ? "en" : "dis", rc);
			regulator_set_optimum_mode(hall_key->regs[i],
					!on ? reg_info[i].load_uA : 0);
			goto regs_fail;
		}
	}

	return 0;

regs_fail:
	while (i--) {
		regulator_set_optimum_mode(hall_key->regs[i],
				!on ? reg_info[i].load_uA : 0);
		!on ? regulator_enable(hall_key->regs[i]) :
			regulator_disable(hall_key->regs[i]);
	}
	return rc;
}

static int hall_key_reg_setup(struct hall_key_chip *hall_key, bool on)
{
	const struct hall_key_regulator *reg_info =
				hall_key->regulator_info;
	u8 i, num_reg = hall_key->num_regulators;
	int rc = 0;

	/* put regulators */
	if (on == false) {
		i = num_reg;
		goto put_regs;
	}

	hall_key->regs = kzalloc(num_reg * sizeof(struct regulator *),
							GFP_KERNEL);
	if (!hall_key->regs) {
		pr_err("unable to allocate memory\n");
		return -ENOMEM;
	}

	for (i = 0; i < num_reg; i++) {
		hall_key->regs[i] = regulator_get(hall_key->dev,
						reg_info[i].name);
		if (IS_ERR(hall_key->regs[i])) {
			rc = PTR_ERR(hall_key->regs[i]);
			pr_err("%s:regulator get failed(%d)\n", __func__, rc);
			goto put_regs;
		}

		if (regulator_count_voltages(hall_key->regs[i]) > 0) {
			rc = regulator_set_voltage(hall_key->regs[i],
				reg_info[i].min_uV, reg_info[i].max_uV);
			if (rc) {
				pr_err("%s: regulator_set_voltage failed(%d)\n",
								__func__, rc);
				regulator_put(hall_key->regs[i]);
				goto put_regs;
			}
		}
	}

	return rc;

put_regs:
	while (i--) {
		if (regulator_count_voltages(hall_key->regs[i]) > 0)
			regulator_set_voltage(hall_key->regs[i], 0,
						reg_info[i].max_uV);
		regulator_put(hall_key->regs[i]);
	}
	kfree(hall_key->regs);
	return rc;
}

#ifdef CONFIG_OF
static int hall_key_parse_dt(struct device *dev,
			struct hall_key_chip *pdata)
{
	struct device_node *temp, *np = dev->of_node;
	struct hall_key_regulator *reg_info;
	int rc = 0;
	u32 temp_val;
	const char *temp_string;
	u32 value; 


	rc = of_property_read_string(np, "label", &pdata->name);
	if (rc) {
		dev_err(dev, "Unable to read device name\n");
		return rc;
	}

	pdata->num_regulators = 0;
	temp = NULL;
	while ((temp = of_get_next_child(np, temp)))
		pdata->num_regulators++;

	if (!pdata->num_regulators)
		return 0;

	reg_info = devm_kzalloc(dev, pdata->num_regulators *
				sizeof(struct hall_key_regulator), GFP_KERNEL);
	if (!reg_info)
		return -ENOMEM;

	pdata->regulator_info = reg_info;

	for_each_child_of_node(np, temp) {
		rc = of_property_read_string(temp,
			"regulator-name", &temp_string);
		if (rc) {
			dev_err(dev, "Unable to read regulator name\n");
			return rc;
		} else
			reg_info->name = temp_string;

		rc = of_property_read_u32(temp, "regulator-max-microvolt",
			&temp_val);
		if (rc) {
			dev_err(dev, "Unable to read max uV\n");
			return rc;
		} else
			reg_info->max_uV = temp_val;

		rc = of_property_read_u32(temp, "regulator-min-microvolt",
			&temp_val);
		if (rc) {
			dev_err(dev, "Unable to read min uV\n");
			return rc;
		} else
			reg_info->min_uV = temp_val;

		rc = of_property_read_u32(temp, "regulator-max-microamp",
			&temp_val);
		if (rc) {
			dev_err(dev, "Unable to read load uA\n");
			return rc;
		} else
			reg_info->load_uA = temp_val;

		reg_info++;
	}

	pdata->irq_gpio = of_get_named_gpio_flags(np,
			"hall,irq-gpio", 0, NULL);
	printk("hall_key irq gpio = %d\n",pdata->irq_gpio);
	rc = of_property_read_u32(np, "hall,irq-flags", &value);
	if (rc < 0)
	{
		printk("hall_key no irq flag\n");
		return rc;
	}
	else
		pdata->irq_flags = value;
	
	return 0;
}
#endif

static irqreturn_t hall_key_irq(int irq, void *data)
{
	struct hall_key_chip *hall_key = data;
	int state;
	static int last_state = 5;
	
	state = gpio_get_value(hall_key->irq_gpio);
	printk("hall-key status = %d\n",state);
	
	if(state != last_state)
	{
		if(state) //open
		{
			input_report_key(hall_key->input_dev, 188, 1);
			input_report_key(hall_key->input_dev, 188, 0);
		}
		else
		{
			input_report_key(hall_key->input_dev, 189, 1);
			input_report_key(hall_key->input_dev, 189, 0);
		}
		input_sync(hall_key->input_dev);
		last_state = state;
	}
	
	return IRQ_HANDLED;
}

static int __devinit hall_key_probe(struct platform_device *pdev)
{
	struct hall_key_chip *hall_key;
	//struct device_node *node = pdev->dev.of_node;
	int ret;
	
	hall_key = devm_kzalloc(&pdev->dev, sizeof(struct hall_key_chip), GFP_KERNEL);
	if (!hall_key) {
		dev_err(&pdev->dev, "not enough memory\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, hall_key);
	hall_key->dev = &pdev->dev;

	ret = hall_key_parse_dt(&pdev->dev, hall_key);
	if (ret) {
		dev_err(&pdev->dev, "Parsing DT failed(%d)", ret);
		return ret;
	}

	ret = gpio_request(hall_key->irq_gpio, "hall-key");
	if (ret) {
		pr_err("%s: Failed to get gpio %d (code: %d)",
				__func__, hall_key->irq_gpio, ret);
		return ret;
	}

	ret = gpio_direction_input(hall_key->irq_gpio);
	if (ret) { //gpio_free
		pr_err("%s: Failed to set gpio %d direction (code: %d)",
				__func__, hall_key->irq_gpio, ret);
		goto config_gpio_fail;
	}
		
	hall_key->irq = gpio_to_irq(hall_key->irq_gpio);
	ret = request_irq(hall_key->irq,
			hall_key_irq, hall_key->irq_flags | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			"HALL_KEY", hall_key);
	if (ret < 0) {
		dev_err(&pdev->dev,
				"%s: Failed to request irq\n",
				__func__);
		goto req_irq_fail;
	}
	disable_irq(hall_key->irq);
	
	printk("hall key register ok\n");
	hall_key->input_dev = input_allocate_device();
	if (hall_key->input_dev == NULL) {
		dev_err(&pdev->dev,
				"%s: Failed to allocate input device\n",
				__func__);
		ret = -ENOMEM;
		goto err_input_device;
	}
	hall_key->input_dev->name = "hall-key";
	hall_key->input_dev->phys = "hall-key";
	hall_key->input_dev->id.product = 0x01;
	hall_key->input_dev->id.version = 0x01;
	hall_key->input_dev->dev.parent = &pdev->dev;
	input_set_drvdata(hall_key->input_dev, hall_key);

	set_bit(EV_SYN, hall_key->input_dev->evbit);
	set_bit(EV_KEY, hall_key->input_dev->evbit);
	input_set_capability(hall_key->input_dev, EV_KEY, 188);
	input_set_capability(hall_key->input_dev, EV_KEY, 189);
	ret = input_register_device(hall_key->input_dev);
	if (ret) {
		dev_err(&pdev->dev,
				"%s: Failed to register input device\n",
				__func__);
		goto err_register_input;
	}

	if (hall_key->regulator_info) {
		ret = hall_key_reg_setup(hall_key, true);
		if (ret) {
			dev_err(&pdev->dev, "%s: regulator setup failed\n",
							__func__);
			goto reg_setup_fail;
		}

		ret = hall_key_reg_power(hall_key, true);
		if (ret) {
			dev_err(&pdev->dev, "%s: regulator power failed\n",
							__func__);
			goto reg_pwr_fail;
		}
	}
	
	enable_irq(hall_key->irq);
	printk("hall-key probe ok\n");
	return ret;

reg_pwr_fail:
	if (hall_key->regulator_info)
		hall_key_reg_setup(hall_key, false);
reg_setup_fail:
err_register_input:
	input_free_device(hall_key->input_dev);
err_input_device:
	free_irq(hall_key->irq, hall_key);
req_irq_fail:
config_gpio_fail:
	gpio_free(hall_key->irq_gpio);
	return ret;
}

static int __devexit hall_key_remove(struct platform_device *pdev)
{
	struct hall_key_chip *hall_key = platform_get_drvdata(pdev);
	printk("%s \n",__func__);
	gpio_free(hall_key->irq_gpio);
	
	/* power-off the chip */
	if (hall_key->regulator_info) {
		hall_key_reg_power(hall_key, false);
		hall_key_reg_setup(hall_key, false);
	}
	free_irq(hall_key->irq, hall_key);
	input_free_device(hall_key->input_dev);
	kfree(hall_key);
	return 0;
}

#ifdef CONFIG_PM
static int hall_key_suspend(struct platform_device *pdev, pm_message_t mesg)
{
	struct hall_key_chip *hall_key = platform_get_drvdata(pdev);

	printk("%s\n",__func__);
	if (hall_key->regulator_info)
		hall_key_reg_power(hall_key, false);

	
	enable_irq_wake(hall_key->irq);
	return 0;
}

static int hall_key_resume(struct platform_device *pdev)
{
	struct hall_key_chip *hall_key = platform_get_drvdata(pdev);
	
	printk("%s\n",__func__);
	if (hall_key->regulator_info)
		hall_key_reg_power(hall_key, true);

	disable_irq_wake(hall_key->irq);
	return 0;
}
#else
#define isa1200_suspend		NULL
#define isa1200_resume		NULL
#endif


static const struct of_device_id of_hall_matach[] = {
	{
		.compatible = "liujiang,hall_key",
	},
	{ },
};
MODULE_DEVICE_TABLE(of, of_dwc3_matach);

static struct platform_driver hall_key_driver = {
	.probe		= hall_key_probe,
	.remove		= __devexit_p(hall_key_remove),
	.driver		= {
		.name	= "hall-key",
		.of_match_table	= of_hall_matach,
	},
	.suspend	= hall_key_suspend,
	.resume		= hall_key_resume,
};

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("liujiang hall-key driver");
MODULE_AUTHOR("liujiang <liujiang@gionee.com>");

static int __devinit hall_key_init(void)
{
	return platform_driver_register(&hall_key_driver);
}
module_init(hall_key_init);

static void __exit hall_key_exit(void)
{
	platform_driver_unregister(&hall_key_driver);
}
module_exit(hall_key_exit);

