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

static struct option wifi_pwr[] = {
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
};

static struct option bt_signal_mode[] = {
	{0,"0x04"},// CW Signal
	{1,"0X05"},// TX_CONTINUOUS Rate 1M(GFSK)
	{2,"0X06"},// TX_CONTINUOUS Rate 3M(8DPSK)
	{3,"0X07"},
	{4,"0X08"},
	{5,"0X09"},
	{6,"0X0A"},
	{7,"0X0B"},
	{8,"0X0C"},
	{9,"0X0D"},
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
};

static struct wifi_opt wo;

static void gionee_factorytest_wifi_tx_set_parm(JNIEnv* env, jclass clazz,jint id, jint index) {
    switch(id)
    {
    		case SIGNAL_MODE :
    			wo.tx = wifi_signal_mode[index].cmd;
    			break;
    		case FREQ :
    			wo.txfreq = wifi_freq[index].cmd;
    			break;
    		case RATE :
    			wo.txrate = wifi_rate[index].cmd;
    			break;
    		case POWER :
    			wo.pwr = wifi_pwr[index].cmd;
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
    wifi_tx_test(wo);
}

static void gionee_factorytest_wifi_tx_test_stop(JNIEnv* env, jclass clazz) {
    wo.tx = wifi_signal_mode[2].cmd;
    wifi_tx_test(wo);
}

static void gionee_factorytest_wifi_drv_load(JNIEnv* env, jclass clazz) {
    wifi_drv_load();
}

static void gionee_factorytest_wifi_drv_unload(JNIEnv* env, jclass clazz) {
    wifi_drv_unload();
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

static void gionee_factorytest_bt_test_mode(JNIEnv* env, jclass clazz) {
    bt_test_mode();
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
    //{"wifi_tx_set_parm", "(II)V", (void *)gionee_factorytest_wifi_tx_set_parm},
    //{"wifi_tx_test", "()V", (void *)gionee_factorytest_wifi_tx_test},
    //{"wifi_tx_test_stop", "()V", (void *)gionee_factorytest_wifi_tx_test_stop},
    //{"wifi_drv_load", "()V", (void *)gionee_factorytest_wifi_drv_load},
    //{"wifi_drv_unload", "()V", (void *)gionee_factorytest_wifi_drv_unload},
    //{"wifi_connect_ap", "()V", (void *)gionee_factorytest_wifi_connect_ap},
    {"bt_tx_set_parm", "(II)V", (void *)gionee_factorytest_bt_tx_set_parm},
    {"bt_tx_test", "()V", (void *)gionee_factorytest_bt_tx_test},
    {"bt_tx_test_stop", "()V", (void *)gionee_factorytest_bt_tx_test_stop},
    {"bt_test_mode", "()V", (void *)gionee_factorytest_bt_test_mode},
    {"bt_dev_open", "()V", (void *)gionee_factorytest_bt_dev_open},
    {"bt_dev_close", "()V", (void *)gionee_factorytest_bt_dev_close},
};

int register_gionee_factorytest_jni(JNIEnv* env)
{
    return jniRegisterNativeMethods(env, "com/gionee/bttx/EMWifi", sMethods, NELEM(sMethods));
}

} /* namespace android */
