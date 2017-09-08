#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include "gn_hall.h"
#include <linux/switch.h>

#define POWER_SET 0
struct hall_dev_data {
	struct input_dev *input_dev;
	struct hall_platform_data *pdata;
	bool power_on;
	struct regulator *vdd;
	int irq;
};

static struct switch_dev hall_data;
//static struct input_dev *input_dev;
static struct task_struct *thread = NULL;
static struct hall_dev_data *hall_data_ts = NULL;


enum hall_state
{
	HALL_CLOSE = 0,
    HALL_OPEN =1
};
static int hall_event_handler(void *unused);
static irqreturn_t hall_irq_handler(int irq, void *dev_id);

static int  gn_hall_flag=0;
//struct task_struct *thread= NULL;

static DECLARE_WAIT_QUEUE_HEAD(waiter);
#if POWER_SET
static int hall_power_on(struct hall_dev_data *ts)
{
	int ret;

	if (ts->power_on) {
		printk("Device already power on\n");
		return 0;
	}

	if (!IS_ERR(ts->vdd)) {
		/*
		ret = regulator_set_voltage(ts->vdd, hall_VTG_MIN_UV,
					   hall_VTG_MAX_UV);
		if (ret) {
			printk("Regulator set_vtg failed vdd ret=%d\n", ret);
			goto err_set_vtg_vdd;
		}
*/
		ret = regulator_enable(ts->vdd);
		if (ret) {
			printk("Regulator vdd enable failed ret=%d\n", ret);
			goto err_enable_vdd;
		}
	}
	ts->power_on = true;
	return 0;

err_enable_vdd:

	ts->power_on = false;
	return ret;
}
#endif
static int hall_request_io_port(struct hall_dev_data *ts)
{
	
	struct hall_platform_data *pdata = ts->pdata;
	int ret;
	pdata->irq_gpio=hall_irq_gpio;
	if (gpio_is_valid(pdata->irq_gpio)) {
		ret = gpio_request(pdata->irq_gpio, "hall_irq_gpio");
		if (ret) {
			printk( "irq gpio request failed\n");
			goto pwr_off;
		}
	    printk("%s irq_gpio ok\n",__func__);
		ret = gpio_direction_input(pdata->irq_gpio);
		if (ret) {
			printk("set_direction for irq gpio failed\n");
			goto free_irq_gpio;
		}
	} else {
		printk("irq gpio is invalid!\n");
		ret = -EINVAL;
		goto free_irq_gpio;
	}

	return ret;
free_irq_gpio:
	if (gpio_is_valid(pdata->irq_gpio))
		gpio_free(pdata->irq_gpio);
pwr_off:
	return ret;
}

static int hall_parse_dt(struct device *dev, struct hall_platform_data *pdata)
{
	//struct device_node *np = dev->of_node;
	
	pdata->irq_gpio = hall_irq_gpio;

	//printk("%s irq=%d\n",__func__,pdata->irq_gpio);
	return 0;
}
static int hall_request_irq(struct hall_dev_data *ts)
{
	int ret;
    gpio_direction_input(ts->pdata->irq_gpio);
//	ret = request_irq(ts->irq, hall_irq_handler,  IRQF_TRIGGER_MASK ,HALL_NAME, ts);
	ret = request_irq(ts->irq, hall_irq_handler,  IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING ,HALL_NAME, ts);
	if (ret) {
		printk("Request IRQ failed!ERRNO:%d.\n",ret);
		return ret;
	}
		disable_irq_nosync(ts->irq);
		//ts->use_irq = true;
		return 0;
	//}
}
int hall_event_handler(void *unused)
{
	u8 hallkey_state;
	u8 old_state;
	// struct hall_platform_data *pdata;
	 // struct hall_dev_data *ts;
	//struct sched_param param = { .sched_priority = RTPM_PRIO_TPD };
    //sched_setscheduler(current, SCHED_RR, &param);

	do{ 
		enable_irq(hall_data_ts->irq);
	    set_current_state(TASK_INTERRUPTIBLE);

        wait_event_interruptible(waiter,gn_hall_flag!=0);

        gn_hall_flag = 0;


        set_current_state(TASK_RUNNING);
	    hallkey_state = __gpio_get_value(hall_data_ts->pdata->irq_gpio);
	    old_state = !hallkey_state;

	    //printk("%s: hallkey_state = %d\n",__func__,hallkey_state);
	    if(!hall_data_ts->input_dev) {
	    	printk("KPD input device not ready\n");
	    	return 0;
	    }
		
	    if(hallkey_state==1) //hall open
	    {
	    	input_report_key(hall_data_ts->input_dev, KEY_F18, 1);
			input_sync(hall_data_ts->input_dev);
	    	input_report_key(hall_data_ts->input_dev, KEY_F18, 0);
			input_sync(hall_data_ts->input_dev);
	    	switch_set_state((struct switch_dev *)&hall_data, HALL_OPEN);
	    }
	    else//hall close
	    {
	    	input_report_key(hall_data_ts->input_dev, KEY_F19, 1);
			input_sync(hall_data_ts->input_dev);
    		input_report_key(hall_data_ts->input_dev, KEY_F19, 0);
			input_sync(hall_data_ts->input_dev);
    		switch_set_state((struct switch_dev *)&hall_data, HALL_CLOSE);
    	}
	
	   

	}while(!kthread_should_stop());
    return 0;
}

static irqreturn_t hall_irq_handler(int irq, void *dev_id)
{
	struct hall_dev_data *ts=dev_id;
	disable_irq_nosync(ts->irq);
    gn_hall_flag = 1;
    wake_up_interruptible(&waiter);
	return IRQ_HANDLED;
}

static int hall_probe(struct platform_device *pdev)
{

    struct hall_platform_data *pdata;
    struct hall_dev_data *data;
    struct input_dev *input_dev;
    int ret;
    pdata = kzalloc(sizeof(struct hall_platform_data), GFP_KERNEL);
		if (!pdata) {
			printk("Failed to allocate memory\n");
			return -ENOMEM;
		}

	ret = hall_parse_dt(&pdev->dev, pdata);
		if (ret)
			return ret;
	data = kzalloc(sizeof(struct hall_dev_data), GFP_KERNEL);
	memset(data, 0, sizeof(*data));
	input_dev = input_allocate_device();
	if (!data || !input_dev) {
		printk( "Failed to allocate memory\n");
		ret = -ENOMEM;
		goto exit_init_device_failed;
	}

    data->pdata = pdata;
    data->input_dev = input_dev;
	data->irq=gpio_to_irq(hall_irq_gpio);
	hall_data_ts=data;
	ret = hall_request_io_port(data);
	if (ret) {
		dev_err(&pdev->dev, "hall_switch request IO port failed.\n");
		goto exit_init_device_failed;
	}

    //data->client->irq=gpio_to_irq(pdata->irq_gpio);

    hall_request_irq(data);

	input_dev->name = HALL_NAME;
	set_bit(EV_KEY,input_dev->evbit);
	__set_bit(KEY_F18, input_dev->keybit);
	__set_bit(KEY_F19, input_dev->keybit);
	
    ret = input_register_device(data->input_dev);
    if (ret) {
        printk( "Register %s input device failed.\n", data->input_dev->name);
        goto exit_init_device_failed;
    }
	
    input_set_drvdata(data->input_dev, data);
#if POWER_SET    
    // power on
    data->vdd = regulator_get(&pdev->dev, "vdd");
	if (IS_ERR(data->vdd)) {
		ret = PTR_ERR(data->vdd);
		printk("Regulator get failed vdd ret=%d\n", ret);
		return ret;
	}

   ret = hall_power_on(data);
    if(ret) {
        printk("Power on failed vdd ret=%d\n", ret);
		return ret;
    }
#endif
	  hall_data.name = "hall_switch";
	  hall_data.index = 0;
	  hall_data.state = HALL_OPEN;
	  ret = switch_dev_register(&hall_data);
	  if(ret){
	  	printk("register switch failed (%d)\n",ret);
	}
	  	
		if(__gpio_get_value(hall_data_ts->pdata->irq_gpio) == 0)	//low ->high for trigger
		{
			switch_set_state((struct switch_dev *)&hall_data, HALL_CLOSE);
			//¢mt_eint_registration(CUST_EINT_MHALL_NUM, CUST_EINT_MHALL_TYPE, kpd_hall_eint_handler, 0);	
		}
		else
		{
			switch_set_state((struct switch_dev *)&hall_data, HALL_OPEN);
			//mt_eint_registration(CUST_EINT_MHALL_NUM, CUST_EINT_MHALL_TYPE, kpd_hall_eint_handler, 0);
		}

    thread = kthread_run(hall_event_handler, 0, hall_data.name);
    if (IS_ERR(thread)) { 
        ret = PTR_ERR(thread);
        printk( " failed to create kernel thread: %d\n",ret);
        goto exit_init_device_failed;
    }

    disable_irq_nosync(data->irq);

    enable_irq(data->irq);
    enable_irq_wake(data->irq);//moxizheng
    return 0;
exit_init_device_failed:
    printk("%d %s prob failed\n", __LINE__, __func__);
  
    return ret;

// gionee liudj end
}

static int hall_remove(struct platform_device *pdev)
{
    return 0;
}

static struct of_device_id hall_match_table[] = {
	{ .compatible = "hall_switch", },
	{ },
};

static int sn5100_key_suspend(struct device *dev)
{
	enable_irq_wake(hall_data_ts->irq);
	return 0;
}
static int sn5100_key_resume(struct device *dev)
{
	disable_irq_wake(hall_data_ts->irq);
	return 0;
}
static const struct dev_pm_ops sn5100_pm_ops = {
	.suspend	= sn5100_key_suspend,
	.resume		= sn5100_key_resume,
};
static struct platform_driver hall_driver = {
	.probe      = hall_probe,
	.remove     = __devexit_p(hall_remove),
	.driver = {
		.name     = HALL_NAME,
		.owner    = THIS_MODULE,
		.of_match_table = hall_match_table,
		.pm	= &sn5100_pm_ops,
	},
};

static int __devinit hall_init(void)
{
	int ret;
	ret = platform_driver_register(&hall_driver);
	return ret;
}
static void __exit hall_exit(void)
{
	platform_driver_unregister(&hall_driver);
}


module_init(hall_init);
module_exit(hall_exit);

MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Hall_Switch Driver");
MODULE_LICENSE("GPL v2");

