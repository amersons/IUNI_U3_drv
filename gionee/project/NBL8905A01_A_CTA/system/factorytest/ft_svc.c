#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <cutils/properties.h>
#include <cutils/log.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

//#include <dbus/dbus.h>
//#include <bluedroid/bluetooth.h>

#define LOG_TAG "ft_svc"

static int ft_main_exited = 0;
static int ft_pts_fd = -1;

int send(char *cmdparam)
{
    if (ft_pts_fd < 0){
        return -1;
    }
	ALOGE("%s\n",__func__);
    int len = write(ft_pts_fd,cmdparam,sizeof(cmdparam));
    if (len > 0){
        return 0;
    }

    return -1;
}

int wifi_drv_load(char *cmdparam)
{
	int ret = 0;
	ALOGE("%s!\n",__func__);
	//ret = system("insmod /system/wifi/ar6000.ko testmode=1");
	ret = system("insmod system/lib/modules/ath6kl/cfg80211.ko");
	ret = system("insmod system/lib/modules/ath6kl/ath6kl_sdio.ko testmode=1");
	return send("0");
}

int wifi_drv_unload(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	//system("rmmod ar6000.ko");
	system("rmmod cfg80211.ko");
	system("rmmod ath6kl_sdio.ko");
	return send("0");
}

int wifi_drv_load_wcn36x0(char *cmdparam)
{
	int ret = 0;
	ALOGE("%s!\n",__func__);
	ret = system("insmod /system/lib/modules/pronto/pronto_wlan.ko con_mode=5");
    ret = system("ptt_socket_app &");
	return send("0");
}

int wifi_drv_unload_wcn36x0(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	system("rmmod wlan");
	return send("0");
}


int wifi_tx_test(char *cmdparam)
{
	ALOGE("%s :%s\n",__func__,cmdparam);
	system(cmdparam);
	return send("0");
}

int wifi_connect_ap(char *cmdparam)
{
	int ret = 0;
	ALOGE("%s\n",__func__);
	system("echo 1 > /data/misc/wifi/abc");
	system("/data/misc/wifi/wifi_test.sh");
	return send("0");
}

int bt_dev_open(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	//bt_enable();
    system("btconfig /dev/smd3 reset");
    ALOGE("%s edutm\n",__func__);
    system("btconfig /dev/smd3 edutm");
	return send("0");
}

int bt_dev_close(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	//bt_disable();
	return send("0");
}

int bt_tx_test(char *cmdparam)
{
	ALOGE("%s :%s\n",__func__,cmdparam);
	system("btconfig /dev/smd3 rawcmd 0x3F 0x000B 0x01 0x1B 0x01 0x00");
	system("btconfig /dev/smd3 rawcmd 0x03 0x0003");
	system(cmdparam);
	return send("0");
}

int bt_tx_test_stop(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	system("btconfig /dev/smd3 rawcmd 0x3F 0x000B 0x01 0x1B 0x01 0x00");
	system("btconfig /dev/smd3 rawcmd 0x03 0x0003");
	return send("0");
}

int bt_test_mode(char *cmdparam)
{	
    system("btconfig /dev/smd3 reset");
	ALOGE("%s\n",__func__);
    system("btconfig /dev/smd3 rawcmd 0x06 0x0003");
    system("btconfig /dev/smd3 rawcmd 0x03 0x0005 0x02 0x00 0x02");
    system("btconfig /dev/smd3 rawcmd 0x03 0x001A 0x03");
    system("btconfig /dev/smd3 rawcmd 0x03 0x0020 0x00");
    system("btconfig /dev/smd3 rawcmd 0x03 0x0022 0x00");
	return send("0");
}

int lcd_test(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	system("echo 1 > sys/class/leds/lcd-cabc/brightness");
	return send("0");
}

int lcd_test_stop(char *cmdparam)
{
	ALOGE("%s\n",__func__);
	system("echo 0 > sys/class/leds/lcd-cabc/brightness");
	return send("0");
}


static struct 
{
	const char *cmd;
	void (*func)(char *cmdparam);
	char *doc;
} command[] = 
{
    {"wifi_connect_ap", wifi_connect_ap, "connect ap"},
    {"wifi_tx_test", wifi_tx_test, "wifi tx test"},
    {"wifi_drv_load", wifi_drv_load, "load wifi driver"},
    {"wifi_drv_unload", wifi_drv_unload, "unload wifi driver"},
    {"wcn36x0_wifi_drv_load", wifi_drv_load_wcn36x0, "load wcn36x0 wifi driver"},
    {"wcn36x0_wifi_drv_unload", wifi_drv_unload_wcn36x0, "unload wcn36x0 wifi driver"},
    {"bt_tx_test", bt_tx_test, "bt tx test"},
    {"bt_tx_test_stop", bt_tx_test_stop, "stop bt tx test"},
    {"bt_test_mode", bt_test_mode, "start bt test mode"},
    {"bt_dev_open", bt_dev_open, "open bt device"},
    {"bt_dev_close", bt_dev_close, "close bt device"},
    {"lcd_test", lcd_test, "lcd test"},
    {"lcd_stop_test", lcd_test_stop, "lcd test stop"},
    {"exit", NULL, "Exit this application"},
    {NULL, NULL, NULL},
};

int open_ft_pts(void)
{   
    ft_pts_fd = open("/dev/ptmx", O_RDWR);

    char* pts = ptsname(ft_pts_fd);
    if (pts == NULL) {
        ALOGE("couldn't open dev pts.\n");
        return -1;
    }

    ALOGE("open dev:%s\n", strdup(pts));

    property_set("ft_pts_dev", strdup(pts));

    struct termios options;
    tcgetattr(ft_pts_fd, &options); //get the parameters
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //set raw input
    options.c_iflag &= ~(INLCR | ICRNL | IGNCR);
    options.c_oflag &= ~(OPOST| OLCUC| ONLRET| ONOCR| OCRNL); //set raw output
    tcsetattr(ft_pts_fd, TCSANOW, &options);

    grantpt(ft_pts_fd);
    unlockpt(ft_pts_fd);

    chmod(strdup(pts), 0777);
    
    return 0;
}

static void sig_hup(int sig)
{
}

static void sig_term(int sig)
{
    ft_main_exited = 1;
}

int main(int argc, char *argv[])
{
	char cmdline[100] = {0,};
	int i;
	int r;
	struct sigaction sa;
	sigset_t sigs;
	// need start the bluetoothd daemon and
	// start the service hciattach(brcm_patchram_plus)

    

    if (open_ft_pts() < 0){
        ALOGE("open pts failed\n");
        return -1;
    }
    

	memset(&sa, 0, sizeof(sa));
	sa.sa_flags   = SA_NOCLDSTOP;
	sa.sa_handler = SIG_IGN;
	//sigaction(SIGCHLD, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);

	sa.sa_handler = sig_term;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT,  &sa, NULL);

	sa.sa_handler = sig_hup;
	sigaction(SIGHUP, &sa, NULL);

	for (;;) {
        int sel;
        fd_set fdr;
        ioctl(ft_pts_fd, TCSBRK, 1);
        FD_ZERO(&fdr);
        FD_SET(ft_pts_fd, &fdr);
        if (ft_main_exited) {
            break;
        }
        
        sel = select(ft_pts_fd + 1, &fdr, NULL, NULL, NULL);
        if (sel > 0){
            if (!FD_ISSET(ft_pts_fd, &fdr)){
                continue;
            }
        } else {
            break;
        }

		memset(cmdline, 0, sizeof(cmdline));
        int len = read(ft_pts_fd, cmdline, sizeof(cmdline));
        if (len <= 0){
            break;
        }
        

        ALOGE("get cmdline: \"%s\"\n", cmdline);
        
        for (i=0; command[i].cmd; ++i)
        {
            if (strncmp(command[i].cmd, cmdline, strlen(command[i].cmd)))
            {
                if (command[i+1].cmd == NULL)
                {
                    ALOGE("unknown cmd\n");
                }
                continue;
            }
            if (strncmp(command[i].cmd, "exit", strlen("exit")))
            {
                command[i].func(cmdline + strlen(command[i].cmd));
                break;
            }
            else
            {
                //exit
                ALOGE("exit\n");
                property_set("ft_pts_dev", "ondev");
                return 0;
            }
        }
	}

    return 0;
}
