#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cutils/log.h>
#include <fcntl.h>
#include <cutils/properties.h>
#include "ft_api.h"

#define LOG_TAG "ft_api"

static int ft_fd = -1;
static pthread_mutex_t cmd_mutex;
 
void ft_send_cmd(const char *fmt, ...)
{
    char cmdBuffer[80] = {0,};
	va_list args;
    pthread_mutex_lock(&cmd_mutex);
	va_start(args, fmt);
	vsnprintf(cmdBuffer,sizeof(cmdBuffer),fmt, args);
	va_end(args);
	ALOGE("fm_put_cmd: \"%s\"\n", cmdBuffer);
	write(ft_fd, cmdBuffer, sizeof(cmdBuffer));
    
    memset(cmdBuffer, 0, sizeof(cmdBuffer));
    read(ft_fd, cmdBuffer, sizeof(cmdBuffer));
    ALOGE("fm_put_cmd: \"retval = %s\"\n", cmdBuffer);
    pthread_mutex_unlock(&cmd_mutex);
    return ;
}

void ft_init()
{
	char dev[PROPERTY_VALUE_MAX];
	ALOGD("ft_init\n");
	do {
        property_get("init.svc.ft_svc", dev, "stopped");
        sleep(1);
    } while(strcmp(dev, "running") == 0);
    
	if (property_set("ctl.start", "ft_svc") < 0) {
        ALOGE("Failed to start fm service\n");
        return;
    }
    
    do {
        property_get("ft_pts_dev", dev, "ondev");
        sleep(1);
    } while(strcmp(dev, "ondev") == 0);
	ALOGE("find device: %s\n", dev);
	
    ft_fd = open(dev, O_RDWR);
    if (ft_fd < 0) {
        ALOGE("open device failed.\n");
    }
}

void wifi_drv_load()
{
	ft_send_cmd("wifi_drv_load");
}

void wifi_drv_unload()
{
	ft_send_cmd("wifi_drv_unload");
}

void wifi_drv_load_wcn36x0()
{
	ft_send_cmd("wcn36x0_wifi_drv_load");
}

void wifi_drv_unload_wcn36x0()
{
	ft_send_cmd("wcn36x0_wifi_drv_unload");
}


void wifi_connect_ap()
{
	ft_send_cmd("wifi_connect_ap");
}

void wifi_tx_test(struct wifi_opt wo)
{
	char opt_cmd[100];
    	sprintf(opt_cmd,"athtestcmd -i wlan0 --tx %s --txfreq %s --txrate %s --%s",
    		wo.tx,wo.txfreq,wo.txrate,wo.pwr);
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
}

void wifi_tx_test_36x0(struct wifi_opt wo)
{
	char opt_cmd[100];
    	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 ftm 1");//start ftm 
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 set_cb %s",wo.set_cb);//no channle bonding 
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 set_channel %s",wo.txfreq);//set to channel
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 ena_chain 2");//enable tx chain 
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 pwr_cntl_mode %s",wo.pwr_cntl_mode);//SCPC mode; 2 for CLPC 
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 set_txpower %s",wo.pwr);// set tx power  
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 set_txrate %s",wo.txrate);//set tx rate  
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 tx 1");//tx start  
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
}

void wifi_tx_test_36x0_stop(struct wifi_opt wo)
{
	char opt_cmd[100];
	sprintf(opt_cmd,"iwmulticall iwpriv wlan0 tx 0");//tx start  
	ft_send_cmd("wifi_tx_test %s",opt_cmd);
}


void ft_exit()
{
	ft_send_cmd("exit");
}

void bt_dev_open()
{
	ft_send_cmd("bt_dev_open");
}

void bt_dev_close()
{
	ft_send_cmd("bt_dev_close");
}


void bt_tx_test(struct wifi_opt wo)
{
	char opt_cmd[100];
	sprintf(opt_cmd,"btconfig /dev/smd3 rawcmd 0x3F 0x004 0x05 %s %s %s 0x20 0x00 0x00 0x00 0x00",
    		wo.txfreq,wo.pwr,wo.tx);
	ft_send_cmd("bt_tx_test %s",opt_cmd);
}

void bt_tx_burst(struct wifi_opt wo)
{
	char opt_cmd[200];
	sprintf(opt_cmd,"btconfig /dev/smd3 rawcmd 0x3F 0x0004 0x04 %s %s %s %s %s 0x04 %s 0x00 0x09 0x01 0x9C 0x35 0xBD 0x9C 0x35 0xBD 0x00 %s %s 0x00",
    		wo.txfreq,wo.txfreq,wo.txfreq,wo.txfreq,wo.txfreq,wo.pck_type,wo.pck_length1,wo.pck_length2);
	ft_send_cmd("bt_tx_test %s",opt_cmd);
}

void bt_tx_test_stop()
{
	ft_send_cmd("bt_tx_test_stop");
}
void bt_test_mode()
{
	ft_send_cmd("bt_test_mode");
}

void lcd_test()
{
	ft_send_cmd("lcd_test");
}

void lcd_test_stop()
{
	ft_send_cmd("lcd_stop_test");
}
