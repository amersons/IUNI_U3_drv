
/*Gionee luliya add begin */

#include <pm8x41.h>
#include <platform/gpio.h>
#include <kernel/timer.h>
#include <platform/timer.h>
#include <debug.h>
#include <list.h>
#include <kernel/thread.h>
#include <platform.h>
#include <debug.h>
#include <smem.h>
#include <msm_panel.h>
#include <pm8x41_wled.h>
#include <board.h>
#include <mdp5.h>
#include <i2c_qup.h>
#include <blsp_qup.h>
#include <mipi_dsi.h>
#include <sys/types.h>
#include "pwrkey_vibrator.h"

void msm8974_clk_vibrator_on(void)
{
	struct qup_i2c_dev  *dev;
	char data_buf_0[] = {0x30,0x91};
	char data_buf_1[] = {0x31,0X80};
	char data_buf_2[] = {0x35,0XB5};
	char data_buf_3[] = {0x36,0XB6};

	dev = qup_blsp_i2c_init(BLSP_ID_2, QUP_ID_4, 100000, 19200000);
	if (!dev) {
		dprintf(CRITICAL, "Failed initializing I2c\n");
		return;
	}

	struct i2c_msg msg_buf_0[] = {
		{0x48, I2C_M_WR, 2, data_buf_0}
	};
	struct i2c_msg msg_buf_1[] = {
		{0x48, I2C_M_WR, 2, data_buf_1}
	};
	struct i2c_msg msg_buf_2[] = {
		{0x48, I2C_M_WR, 2, data_buf_2}
	};
	struct i2c_msg msg_buf_3[] = {
		{0x48, I2C_M_WR, 2, data_buf_3}
	};

	qup_i2c_xfer(dev, msg_buf_0, 1);
	qup_i2c_xfer(dev, msg_buf_1, 1);
	qup_i2c_xfer(dev, msg_buf_2, 1);
	qup_i2c_xfer(dev, msg_buf_3, 1);
	

}


void clk_vibrator_init(void)
{

	pm8x41_reg_write(0xD140, 0x14); 
	pm8x41_reg_write(0xD141, 0x02); 
	pm8x41_reg_write(0xD142, 0x05); 
	pm8x41_reg_write(0xD143, 0x00);
 	pm8x41_reg_write(0xD144, 0x00); 
	pm8x41_reg_write(0xD145, 0x03);
	pm8x41_reg_write(0xD146, 0x80);

	pm8x41_reg_write(0x5D43, 0x01); 
	pm8x41_reg_write(0x5D46, 0x80);

	gpio_tlmm_config(86, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_8MA, GPIO_DISABLE);
	mdelay(5);
	gpio_set(86, 2);
	//mdelay(20);

	msm8974_clk_vibrator_on();
	mdelay(100);


	gpio_set(86, 0);
	mdelay(5);
	pm8x41_reg_write(0x5D46, 0x00);//Disables GPIO18 output

}

void msm8974_pwm_vibrator_on(void)
{
	struct qup_i2c_dev  *dev;
	char data_buf_0[] = {0x30,0x88};
	char data_buf_1[] = {0x31,00};


	dev = qup_blsp_i2c_init(BLSP_ID_2, QUP_ID_4, 100000, 19200000);
	if (!dev) {
		dprintf(CRITICAL, "Failed initializing I2c\n");
		return;
	}

	struct i2c_msg msg_buf_0[] = {
		{0x48, I2C_M_WR, 2, data_buf_0}
	};
	struct i2c_msg msg_buf_1[] = {
		{0x48, I2C_M_WR, 2, data_buf_1}
	};


	qup_i2c_xfer(dev, msg_buf_0, 1);
	qup_i2c_xfer(dev, msg_buf_1, 1);
	

}


void pwm_vibrator_init(void)
{

	pm8x41_reg_write(0xE340, 0x16);//Configures to output LPG channel 8 
	pm8x41_reg_write(0xE341, 0x00);//voltage source = vph_pwer 
	pm8x41_reg_write(0xE342, 0x05);//no pulls since LPG actively drives GPIO 
	pm8x41_reg_write(0xE345, 0x03);//CMOS drive, high strength 
	pm8x41_reg_write(0xE346, 0x80);//Enables GPIO36 output

	/* The following sets up LPG channel 8 for 26.24kHz PWM frequency and 50% duty cycle */ 
	pm8x41_reg_write(0x1B844, 0x05);//PWM_SIZE=6, Master Clock=19.2MHz 
	pm8x41_reg_write(0x1B845, 0x00);//divide ratio = 3, M = 2 
	pm8x41_reg_write(0x1B841, 0x03);//PWM_SIZE=6, Master Clock=19.2MHz 
	pm8x41_reg_write(0x1B842, 0x22);//divide ratio = 3, M = 2 
	pm8x41_reg_write(0x1B843, 0x20);//divide ratio = 3, M = 2 
	pm8x41_reg_write(0x1B846, 0x04);//Set PWM_VALUE bit<0> = 0 

	/* Enable the GPIO and LPG channel 8 outputs */ 
	 
	pm8x41_reg_write(0x1B846, 0xE4);//Enables LPG Channel 8 output in PWM mode 
	pm8x41_reg_write(0x1B844, 0x05);//Set PWM_VALUE again 
	pm8x41_reg_write(0x1B845, 0x00);//Set PWM_VALUE again 


	gpio_tlmm_config(86, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_8MA, GPIO_DISABLE);
	mdelay(5);
	gpio_set(86, 2);
	//mdelay(20);

	msm8974_pwm_vibrator_on();
	mdelay(100);

	gpio_set(86, 0);
	mdelay(5);
	pm8x41_reg_write(0x1B846, 0x04);
	pm8x41_reg_write(0xE346, 0x00);//Disables GPIO36 output

}

/*Gionee luliya add end */



