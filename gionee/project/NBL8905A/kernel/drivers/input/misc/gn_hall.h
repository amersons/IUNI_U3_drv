#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/slab.h>
#include <linux/regulator/consumer.h>
#include <linux/irq.h>

#include <linux/module.h>
#include <linux/init.h>
#include <linux/firmware.h>
#include <linux/input/mt.h>
#include <linux/gpio.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/of_gpio.h>


#define  HALL_NAME  "hall_switch"
//#define hall_VTG_MIN_UV	1800000
//#define hall_VTG_MAX_UV	1800000
#define hall_irq_gpio    54
struct hall_platform_data {
	unsigned long irqflags;
	int irq_gpio;
	u32 irq_gpio_flags;
};



