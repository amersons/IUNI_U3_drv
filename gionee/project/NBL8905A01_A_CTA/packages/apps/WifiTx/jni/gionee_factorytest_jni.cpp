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

#define LOG_TAG "Factorytest"

#include <cutils/properties.h>
#include "JNIHelp.h"
#include "jni.h"
#include "utils/Log.h"
#include "utils/misc.h"
#include "android_runtime/AndroidRuntime.h"
extern "C" {
#include "ft_api.h"
}

#include <string.h>

namespace android {

struct option{
	int index;
	const char *cmd;
}; 

static int mode_index = 0;

static struct option wifi_signal_mode[] = {
	{0,"sine"},// CW Signal
	{1,"tx99"},// TX_CONTINUOUS
	{2,"off"},// Off
};

static struct option wifi_freq[] = {
	{0,"1"},//channel 1
	{1,"2"},//channel 2
	{2,"3"},//channel 3
	{3,"4"},//channel 4
	{4,"5"},//channel 5
	{5,"6"},//channel 6
	{6,"7"},//channel 7
	{7,"8"},//channel 8
	{8,"9"},//channel 9
	{9,"10"},//channel 10
	{10,"11"},//channel 11
	{11,"12"},//channel 12
	{12,"13"},//channel 13
};

static struct option wifi_freq_bgn_ht20[] = {
	{0,"1"},//channel 1
	{1,"6"},//channel 6
	{2,"11"},//channel 11
	{3,"13"},//channel 13
	{4,"149"},//channel 149
	{5,"165"},//channel 165
};

static struct option wifi_freq_n_ht40[] = {
	{0,"3"},//channel 3
	{1,"6"},//channel 6
	{2,"9"},//channel 9
	{3,"11"},//channel 11
	{4,"151"},//channel 151
	{5,"159"},//channel 159
	{6,"163"},//channel 163
};

static struct option wifi_freq_ac_ht20[] = {
	{0,"36"},//channel 36
	{1,"64"},//channel 64
};

static struct option wifi_freq_ac_ht40[] = {
	{0,"38"},//channel 38
	{1,"62"},//channel 62
};

static struct option wifi_freq_ac_ht80[] = {
	{0,"42"},//channel 42
	{1,"58"},//channel 58
	{2,"155"},//channel 155
};

static struct option wifi_freq_a_ht20[] = {
	{0,"149"},//channel 149
	{1,"165"},//channel 165
};




static struct option wifi_rate[] = {
	{0,"0"},//1 Mbps
	{1,"1"},//2 Mbps
	{2,"2"},//5.5 Mbps
	{3,"3"},//11 Mbps
	{4,"4"},//6 Mbps
	{5,"5"},//9 Mbps
	{6,"6"},//12 Mbps
	{7,"7"},//18 Mbps
	{8,"8"},//24 Mbps
	{9,"9"},//36 Mbps
	{10,"10"},//48 Mbps
	{11,"11"},//54 Mbps
	{12,"12"},//MCS0 HT20
	{13,"13"},//MCS1 HT20
	{14,"14"},//MCS2 HT20
	{15,"15"},//MCS3 HT20
	{16,"16"},//MCS4 HT20
	{17,"17"},//MCS5 HT20
	{18,"18"},//MCS6 HT20
	{19,"19"},//MCS7 HT20
};

static struct option wifi_rate_b[] = {
	{0,"11B_LONG_1_MBPS"},
	{0,"11B_LONG_5_5_MBPS"},
	{0,"11B_LONG_11_MBPS"},
};

static struct option wifi_rate_g[] = {
	{0,"11A_6_MBPS"},
	{0,"11A_24_MBPS"},
	{0,"11A_54_MBPS"},
};

static struct option wifi_rate_n_ht20[] = {
	{0,"MCS_6_5_MBPS"},
	{0,"MCS_39_MBPS"},
	{0,"MCS_65_MBPS"},
};

static struct option wifi_rate_n_ht40[] = {
	{0,"MCS_CB_13_5_MBPS"},
	{0,"MCS_CB_81_MBPS"},
	{0,"MCS_CB_135_MBPS"},
};

static struct option wifi_rate_ac_ht20[] = {
	{0,"VHT_MCS_NGI_6_5_MBPS"},
	{0,"VHT_MCS_NGI_39_MBPS"},
	{0,"VHT_MCS_NGI_78_MBPS"},
};

static struct option wifi_rate_ac_ht40[] = {
	{0,"VHT_MCS_CB_NGI_13_5_MBPS"},
	{0,"VHT_MCS_CB_NGI_108_MBPS"},
	{0,"VHT_MCS_CB_NGI_180_MBPS"},
};

static struct option wifi_rate_ac_ht80[] = {
	{0,"VHT_MCS_CB_NGI_29_3_MBPS"},
	{0,"VHT_MCS_CB_NGI_234_MBPS"},
	{0,"VHT_MCS_CB_NGI_390_MBPS"},
};

static struct option wifi_rate_a_ht20[] = {
	{0,"11A_6_MBPS"},
	{0,"11A_24_MBPS"},
	{0,"11A_54_MBPS"},
};


/*static struct option wifi_pwr[] = {
	{0,"tgtpwr"},
	{1,"txpwr 1"},
	{2,"txpwr 2"},
	{3,"txpwr 3"},
	{4,"txpwr 4"},
	{5,"txpwr 5"},
	{6,"txpwr 6"},
	{7,"txpwr 7"},
	{8,"txpwr 8"},
	{9,"txpwr 9"},
	{10,"txpwr 10"},
	{11,"txpwr 11"},
	{12,"txpwr 12"},
	{13,"txpwr 13"},
	{14,"txpwr 14"},
};*/

static struct option wifi_pwr[] = {
	{0,"9"},
	{1,"10"},
	{2,"11"},
	{3,"12"},
	{4,"13"},
	{5,"14"},
	{6,"15"},
	{7,"16"},
	{8,"17"},
	{9,"18"},
	{10,"19"},
	{11,"20"},
	{12,"21"},
	{13,"22"},
	{14,"23"},
	{15,"24"},
};

static struct option wifi_pwr_cntl_mode[] = {
	{0,"0"},//open loop
	{1,"1"},//SCPC
	{2,"2"},//CLPC
};
static struct option wifi_channel_bounding[] = {
	{0,"0"},//means 20 MHz IF bandwidth centered on IF carrier
	{1,"1"},//40MHz BW Primary LOW
	{2,"2"},//40MHz BW Primary CENTERED
	{3,"3"},//40MHz BW Primary HIGH
	{4,"4"},//80MHz BW 20/40MHZ LOW 40/80MHZ CENTERED
	{5,"5"},//80MHz BW 20/40MHZ CENTERED 40/80MHZ CENTERED
	{6,"6"},//80MHz BW 20/40MHZ HIGH 40/80MHZ CENTERED
	{7,"7"},//80MHz BW 20/40MHZ LOW 40/80MHZ LOW
	{8,"8"},//80MHz BW 20/40MHZ HIGH 40/80MHZ LOW
	{9,"9"},//80MHz BW 20/40MHZ LOW 40/80MHZ HIGH
	{10,"10"},//80MHz BW 20/40MHZ HIGH 40/80MHZ HIGH
	
	
};


static struct option bt_signal_mode[] = {
	{0,"0x04"},// CW Signal
	{1,"0x05"},// TX_CONTINUOUS Rate 1M(GFSK) 
	{2,"0x0B"},// TX_CONTINUOUS Rate 3M(8DPSK) 
};

static struct option bt_freq[] = {
	{0,"0x00"},//channel 0
	{1,"0x27"},//channel 39
	{2,"0x4E"},//channel 78
};

static struct option bt_pwr[] = {
	{0,"0x09"},
};

enum opt_id {
	SIGNAL_MODE,
	FREQ,
	RATE,
	POWER,
	WIFI_MODE,
	POWER_MODE,
};

static struct wifi_opt wo;

static void gionee_factorytest_wifi_tx_set_parm(JNIEnv* env, jclass clazz,jint id, jint index) {
    switch(id)
    {
    		case WIFI_MODE :
			mode_index = index;
    			break;
    		case SIGNAL_MODE :
    			wo.tx = wifi_signal_mode[index].cmd;
    			break;
    		case FREQ :
			switch(mode_index)
			{
				case 0://11b
				case 1://11g
				case 2://11n_ht20
					wo.txfreq = wifi_freq_bgn_ht20[index].cmd;
					wo.set_cb = wifi_channel_bounding[0].cmd;//20 MHz IF bandwidth centered on IF carrier
					break;
				case 3://11n_ht40
					wo.txfreq = wifi_freq_n_ht40[index].cmd;
					wo.set_cb = wifi_channel_bounding[2].cmd;//40MHz BW Primary CENTERED
					break;
				case 4://11ac_ht20
					wo.txfreq = wifi_freq_ac_ht20[index].cmd;
					wo.set_cb = wifi_channel_bounding[0].cmd;//20 MHz IF bandwidth centered on IF carrier
					break;
				case 5://11ac_ht40
					wo.txfreq = wifi_freq_ac_ht40[index].cmd;
					wo.set_cb = wifi_channel_bounding[2].cmd;//40MHz BW Primary CENTERED
					break;
				case 6://11ac_ht80
					wo.txfreq = wifi_freq_ac_ht80[index].cmd;
					wo.set_cb = wifi_channel_bounding[5].cmd;//80MHz BW 20/40MHZ CENTERED 40/80MHZ CENTERED
					break;
				case 7://11a_ht20
					wo.txfreq = wifi_freq_a_ht20[index].cmd;
					wo.set_cb = wifi_channel_bounding[0].cmd;//20 MHz IF bandwidth centered on IF carrier
					break;
			}
    			//wo.txfreq = wifi_freq[index].cmd;
    			break;
    		case RATE :
			switch(mode_index)
			{
				case 0://11b
					wo.txrate = wifi_rate_b[index].cmd;
					break;
				case 1://11g
					wo.txrate = wifi_rate_g[index].cmd;
					break;
				case 2://11n_ht20
					wo.txrate = wifi_rate_n_ht20[index].cmd;
					break;
				case 3://11n_ht40
					wo.txrate = wifi_rate_n_ht40[index].cmd;
					break;
				case 4://11ac_ht20
					wo.txrate = wifi_rate_ac_ht20[index].cmd;
					break;
				case 5://11ac_ht40
					wo.txrate = wifi_rate_ac_ht40[index].cmd;
					break;
				case 6://11ac_ht80
					wo.txrate = wifi_rate_ac_ht80[index].cmd;
					break;
				case 7://11a_ht20
					wo.txrate = wifi_rate_a_ht20[index].cmd;
					break;
			}
    			//wo.txrate = wifi_rate[index].cmd;
    			break;
    		case POWER :
    			wo.pwr = wifi_pwr[index].cmd;
    			break;
    		case POWER_MODE :
    			wo.pwr_cntl_mode = wifi_pwr_cntl_mode[index].cmd;
    			break;
    		default :
    			break;
    }
}

static void gionee_factorytest_bt_tx_set_parm(JNIEnv* env, jclass clazz,jint id, jint index) {
    switch(id)
    {
    		case SIGNAL_MODE :
    			wo.tx = bt_signal_mode[index].cmd;
    			break;
    		case FREQ :
    			wo.txfreq = bt_freq[index].cmd;
    			break;
    		/*case RATE :
    			wo.txrate = bt_rate[index].cmd;
    			break;*/
    		case POWER :
    			wo.pwr = bt_pwr[index].cmd;
    			break;
    		default :
    			break;
    }
}

static void gionee_factorytest_wifi_tx_test(JNIEnv* env, jclass clazz) {
    //wifi_tx_test(wo);
    switch(mode_index){
		case 0:
			
			break;
    	}
    wifi_tx_test_36x0(wo);
}

static void gionee_factorytest_wifi_tx_test_stop(JNIEnv* env, jclass clazz) {
    //wo.tx = wifi_signal_mode[2].cmd;
    //wifi_tx_test(wo);
    wifi_tx_test_36x0_stop(wo);
}

static void gionee_factorytest_wifi_drv_load(JNIEnv* env, jclass clazz) {
    //wifi_drv_load();
    wifi_drv_load_wcn36x0();
}

static void gionee_factorytest_wifi_drv_unload(JNIEnv* env, jclass clazz) {
    //wifi_drv_unload();
    wifi_drv_unload_wcn36x0();
}

static void gionee_factorytest_wifi_connect_ap(JNIEnv* env, jclass clazz) {
     wifi_connect_ap();
}

static void gionee_factorytest_bt_dev_open(JNIEnv* env, jclass clazz) {
    bt_dev_open();
}

static void gionee_factorytest_bt_dev_close(JNIEnv* env, jclass clazz) {
    bt_dev_close();
}

static void gionee_factorytest_bt_tx_test(JNIEnv* env, jclass clazz) {
    bt_tx_test(wo);
}

static void gionee_factorytest_bt_tx_test_stop(JNIEnv* env, jclass clazz) {
    bt_tx_test_stop();
}

static void gionee_factorytest_ft_test_init(JNIEnv* env, jclass clazz) {
    ft_init();
}

static void gionee_factorytest_ft_test_exit(JNIEnv* env, jclass clazz) {
    ft_exit();
}

static JNINativeMethod sMethods[] = {
     /* name, signature, funcPtr */
    {"ft_test_init", "()V", (void *)gionee_factorytest_ft_test_init},
    {"ft_test_exit", "()V", (void *)gionee_factorytest_ft_test_exit},
    {"wifi_tx_set_parm", "(II)V", (void *)gionee_factorytest_wifi_tx_set_parm},
    {"wifi_tx_test", "()V", (void *)gionee_factorytest_wifi_tx_test},
    {"wifi_tx_test_stop", "()V", (void *)gionee_factorytest_wifi_tx_test_stop},
    {"wifi_drv_load", "()V", (void *)gionee_factorytest_wifi_drv_load},
    {"wifi_drv_unload", "()V", (void *)gionee_factorytest_wifi_drv_unload},
    //{"wifi_connect_ap", "()V", (void *)gionee_factorytest_wifi_connect_ap},
    //{"bt_tx_set_parm", "(II)V", (void *)gionee_factorytest_bt_tx_set_parm},
    //{"bt_tx_test", "()V", (void *)gionee_factorytest_bt_tx_test},
    //{"bt_tx_test_stop", "()V", (void *)gionee_factorytest_bt_tx_test_stop},
    //{"bt_dev_open", "()V", (void *)gionee_factorytest_bt_dev_open},
    //{"bt_dev_close", "()V", (void *)gionee_factorytest_bt_dev_close},
};

int register_gionee_factorytest_jni(JNIEnv* env)
{
    return jniRegisterNativeMethods(env, "com/gionee/wifitx/EMWifi", sMethods, NELEM(sMethods));
}

} /* namespace android */
