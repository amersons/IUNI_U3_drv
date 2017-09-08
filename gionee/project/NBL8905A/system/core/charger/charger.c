/*
 * Copyright (C) 2011 The Android Open Source Project
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

//#define DEBUG_UEVENTS
#define CHARGER_KLOG_LEVEL 6

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <hardware_legacy/power.h>
#include <hardware_legacy/vibrator.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#include <cutils/android_reboot.h>
#include <cutils/klog.h>
#include <cutils/list.h>
#include <cutils/misc.h>
#include <cutils/uevent.h>

#include <linux/android_alarm.h>

#ifdef CHARGER_ENABLE_SUSPEND
#include <suspend/autosuspend.h>
#endif

#include "minui/minui.h"

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#define ARRAY_SIZE(x)           (sizeof(x)/sizeof(x[0]))

#define MSEC_PER_SEC            (1000LL)
#define NSEC_PER_MSEC           (1000000LL)

#define BATTERY_UNKNOWN_TIME    (2 * MSEC_PER_SEC)
#define POWER_ON_KEY_TIME       (MSEC_PER_SEC / 2)
#define UNPLUGGED_SHUTDOWN_TIME (2 * MSEC_PER_SEC)

//Gionee liujiang 2013-11-06 add for poweroff charger start
#define BATTERY_15_THRESH		15
//Gionee liujiang 2013-11-06 add for poweroff charger end
#define BATTERY_FULL_THRESH     100

#define BACKLIGHT_TOGGLE_PATH "/sys/class/leds/lcd-backlight/brightness"

#define LAST_KMSG_PATH          "/proc/last_kmsg"
#define LAST_KMSG_MAX_SZ        (32 * 1024)

#define LOGE(x...) do { KLOG_ERROR("charger", x); } while (0)
#define LOGI(x...) do { KLOG_INFO("charger", x); } while (0)
#define LOGV(x...) do { KLOG_DEBUG("charger", x); } while (0)

//Gionee liujiang 2013-11-18 add for battery health start

#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
enum {
	POWER_SUPPLY_HEALTH_UNKNOWN = 0,
	POWER_SUPPLY_HEALTH_GOOD,
	POWER_SUPPLY_HEALTH_OVERHEAT,
	POWER_SUPPLY_HEALTH_DEAD,
	POWER_SUPPLY_HEALTH_OVERVOLTAGE,
	POWER_SUPPLY_HEALTH_UNSPEC_FAILURE,
	POWER_SUPPLY_HEALTH_COLD,
};

static char *health_text[] = {
		"Unknown", "Good", "Overheat", "Dead", "Over voltage",
		"Unspecified failure", "Cold",
};
#endif
//Gionee liujiang 2013-11-18 add for battery health start

int is_usb_exist();
int is_ac_exist();
int is_unknown_exist();

struct key_state {
    bool pending;
    bool down;
    int64_t timestamp;
};

struct power_supply {
    struct listnode list;
    char name[256];
    char type[32];
    bool online;
    bool valid;
    char cap_path[PATH_MAX];
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	char health_path[PATH_MAX];
    int health;
#endif
//Gionee liujiang 2013-11-18 add for battery health end
};

struct frame {
    const char *name;
    int disp_time;
    int min_capacity;
    bool level_only;

    gr_surface surface;
};

struct animation {
    bool run;
//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
    struct frame *frames_15percent;
    struct frame *frames_num;
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
	struct frame *frames_b;
    struct frame *frames_c;
	struct frame *frames_d;
	struct frame *frames_num;
#endif
    struct frame *frames;
    int cur_frame;
    int num_frames;

    int cur_cycle;
    int num_cycles;

    /* current capacity being animated */
    int capacity;
};

struct charger {
    int64_t next_screen_transition;
    int64_t next_key_check;
    int64_t next_pwr_check;

    struct key_state keys[KEY_MAX + 1];
    int uevent_fd;

    struct listnode supplies;
    int num_supplies;
    int num_supplies_online;

    struct animation *batt_anim;
    gr_surface surf_unknown;
//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
    gr_surface battery_bg;
    gr_surface battery_line;
    gr_surface battery_full;
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
	gr_surface battery_full;
#endif
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	gr_surface battery_overheat;
	gr_surface battery_cold;
#endif
//Gionee liujiang 2013-11-18 add for battery health end
    struct power_supply *battery;
};

struct uevent {
    const char *action;
    const char *path;
    const char *subsystem;
    const char *ps_name;
    const char *ps_type;
    const char *ps_online;
};

//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE

#define ANIM_X 387
#define ANIM_Y 802
#define ANIN_H 52
#define BATTERY_H 488
#define BATTERY_W 344
#define BATTERY_X 368
#define BATTERY_Y 743
#define NUM_W 84
#define NUM_SPACE 20

static struct frame batt_anim_frames[] = {
    {
        .name = "charger/fhd_bat_animation_01",
        .disp_time = 250,
        .min_capacity = 0,
    },
    {
        .name = "charger/fhd_bat_animation_02",
        .disp_time = 250,
        .min_capacity = 20,
    },
    {
        .name = "charger/fhd_bat_animation_03",
        .disp_time = 250,
        .min_capacity = 40,
    },
    {
        .name = "charger/fhd_bat_animation_04",
        .disp_time = 250,
        .min_capacity = 60,
    },
    {
        .name = "charger/fhd_bat_animation_05",
        .disp_time = 250,
        .min_capacity = 80,
        .level_only = true,
    },
    {
        .name = "charger/fhd_bat_animation_06",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_animation_07",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_animation_08",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_animation_09",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_animation_10",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};

static struct frame batt_anim_frames_15percent[] = {
    {
        .name = "charger/fhd_bat_10_01",
        .disp_time = 250,
        .min_capacity = 0,
    },
    {
        .name = "charger/fhd_bat_10_02",
        .disp_time = 250,
        .min_capacity = 20,
    },
    {
        .name = "charger/fhd_bat_10_03",
        .disp_time = 250,
        .min_capacity = 40,
    },
    {
        .name = "charger/fhd_bat_10_04",
        .disp_time = 250,
        .min_capacity = 60,
    },
    {
        .name = "charger/fhd_bat_10_05",
        .disp_time = 250,
        .min_capacity = 80,
        .level_only = true,
    },
    {
        .name = "charger/fhd_bat_10_06",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_10_07",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_10_08",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_10_09",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_bat_10_10",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};

static struct frame batt_frames_num[] = {
    {
        .name = "charger/fhd_num_0",
        .disp_time = 250,
        .min_capacity = 0,
    },
    {
        .name = "charger/fhd_num_1",
        .disp_time = 250,
        .min_capacity = 20,
    },
    {
        .name = "charger/fhd_num_2",
        .disp_time = 250,
        .min_capacity = 40,
    },
    {
        .name = "charger/fhd_num_3",
        .disp_time = 250,
        .min_capacity = 60,
    },
    {
        .name = "charger/fhd_num_4",
        .disp_time = 250,
        .min_capacity = 80,
        .level_only = true,
    },
    {
        .name = "charger/fhd_num_5",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_num_6",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_num_7",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_num_8",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_num_9",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/fhd_num_percent",
        .disp_time = 250,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_DEFAULT
static struct frame batt_anim_frames[] = {
	{
        .name = "charger/battery_0",
        .disp_time = 750,
        .min_capacity = 0,
    },
    {
        .name = "charger/battery_1",
        .disp_time = 750,
        .min_capacity = 20,
    },
    {
        .name = "charger/battery_2",
        .disp_time = 750,
        .min_capacity = 40,
    },
    {
        .name = "charger/battery_3",
        .disp_time = 750,
        .min_capacity = 60,
    },
    {
        .name = "charger/battery_4",
        .disp_time = 750,
        .min_capacity = 80,
        .level_only = true,
    },
    {
        .name = "charger/battery_5",
        .disp_time = 750,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
#endif

#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
#define AMIGO_MAIN_X 219
#define AMIGO_MAIN_Y 639
#define AMIGO_NUM_W  22
#define AMIGO_NUM_H  34
#define AMIGO_NUM_PERENT_W 35
#define AMIGO_NUM_SPACE_W  4
#define AMIGO_NUM_Y	 (985+56)

static struct frame batt_anim_frames[] = {
    {
        .name = "charger/amigo_chg_fhd_a01",
        .disp_time = 130,
        .min_capacity = 0,
    },
    {
        .name = "charger/amigo_chg_fhd_a02",
        .disp_time = 130,
        .min_capacity = 20,
    },
    {
        .name = "charger/amigo_chg_fhd_a03",
        .disp_time = 130,
        .min_capacity = 40,
    },
    {
        .name = "charger/amigo_chg_fhd_a04",
        .disp_time = 130,
        .min_capacity = 60,
    },
    {
        .name = "charger/amigo_chg_fhd_a05",
        .disp_time = 130,
        .min_capacity = 80,
    },
    {
        .name = "charger/amigo_chg_fhd_a06",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a07",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a08",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a09",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a10",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a11",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_a12",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
static struct frame batt_anim_frames_b[] = {
    {
        .name = "charger/amigo_chg_fhd_b01",
        .disp_time = 130,
        .min_capacity = 0,
    },
    {
        .name = "charger/amigo_chg_fhd_b02",
        .disp_time = 130,
        .min_capacity = 20,
    },
    {
        .name = "charger/amigo_chg_fhd_b03",
        .disp_time = 130,
        .min_capacity = 40,
    },
    {
        .name = "charger/amigo_chg_fhd_b04",
        .disp_time = 130,
        .min_capacity = 60,
    },
    {
        .name = "charger/amigo_chg_fhd_b05",
        .disp_time = 130,
        .min_capacity = 80,
    },
    {
        .name = "charger/amigo_chg_fhd_b06",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b07",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b08",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b09",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b10",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b11",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_b12",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
static struct frame batt_anim_frames_c[] = {
    {
        .name = "charger/amigo_chg_fhd_c01",
        .disp_time = 130,
        .min_capacity = 0,
    },
    {
        .name = "charger/amigo_chg_fhd_c02",
        .disp_time = 130,
        .min_capacity = 20,
    },
    {
        .name = "charger/amigo_chg_fhd_c03",
        .disp_time = 130,
        .min_capacity = 40,
    },
    {
        .name = "charger/amigo_chg_fhd_c04",
        .disp_time = 130,
        .min_capacity = 60,
    },
    {
        .name = "charger/amigo_chg_fhd_c05",
        .disp_time = 130,
        .min_capacity = 80,
    },
    {
        .name = "charger/amigo_chg_fhd_c06",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c07",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c08",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c09",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c10",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c11",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_c12",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
static struct frame batt_anim_frames_d[] = {
    {
        .name = "charger/amigo_chg_fhd_d01",
        .disp_time = 130,
        .min_capacity = 0,
    },
    {
        .name = "charger/amigo_chg_fhd_d02",
        .disp_time = 130,
        .min_capacity = 20,
    },
    {
        .name = "charger/amigo_chg_fhd_d03",
        .disp_time = 130,
        .min_capacity = 40,
    },
    {
        .name = "charger/amigo_chg_fhd_d04",
        .disp_time = 130,
        .min_capacity = 60,
    },
    {
        .name = "charger/amigo_chg_fhd_d05",
        .disp_time = 130,
        .min_capacity = 80,
    },
    {
        .name = "charger/amigo_chg_fhd_d06",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d07",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d08",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d09",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d10",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d11",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_d12",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
static struct frame batt_anim_frames_num[] = {
    {
        .name = "charger/amigo_chg_fhd_num00",
        .disp_time = 130,
        .min_capacity = 0,
    },
    {
        .name = "charger/amigo_chg_fhd_num01",
        .disp_time = 130,
        .min_capacity = 20,
    },
    {
        .name = "charger/amigo_chg_fhd_num02",
        .disp_time = 130,
        .min_capacity = 40,
    },
    {
        .name = "charger/amigo_chg_fhd_num03",
        .disp_time = 130,
        .min_capacity = 60,
    },
    {
        .name = "charger/amigo_chg_fhd_num04",
        .disp_time = 130,
        .min_capacity = 80,
    },
    {
        .name = "charger/amigo_chg_fhd_num05",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_num06",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_num07",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_num08",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_num09",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
    {
        .name = "charger/amigo_chg_fhd_num_percent",
        .disp_time = 130,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
#endif

//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
static struct frame batt_anim_frames[] = {
    {
        .name = "charger/iuni_chg_2k_00",
        .disp_time = 4000,
        .min_capacity = 0,
    },
    {
        .name = "charger/iuni_chg_2k_01",
        .disp_time = 4000,
        .min_capacity = 10,
    },
    {
        .name = "charger/iuni_chg_2k_02",
        .disp_time = 4000,
        .min_capacity = 20,
    },
    {
        .name = "charger/iuni_chg_2k_03",
        .disp_time = 4000,
        .min_capacity = 30,
    },
    {
        .name = "charger/iuni_chg_2k_04",
        .disp_time = 4000,
        .min_capacity = 40,
    },
    {
        .name = "charger/iuni_chg_2k_05",
        .disp_time = 4000,
        .min_capacity = 50,
    },
    {
        .name = "charger/iuni_chg_2k_06",
        .disp_time = 4000,
        .min_capacity = 60,
    },
    {
        .name = "charger/iuni_chg_2k_07",
        .disp_time = 4000,
        .min_capacity = 70,
    },
    {
        .name = "charger/iuni_chg_2k_08",
        .disp_time = 4000,
        .min_capacity = 80,
    },
    {
        .name = "charger/iuni_chg_2k_09",
        .disp_time = 4000,
        .min_capacity = 90,
    },
    {
        .name = "charger/iuni_chg_2k_10",
        .disp_time = 4000,
        .min_capacity = BATTERY_FULL_THRESH,
    },
};
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end

static struct animation battery_animation = {
//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
    .frames_15percent = batt_anim_frames_15percent,
    .frames_num = batt_frames_num,
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
	.frames_b = batt_anim_frames_b,
    .frames_c = batt_anim_frames_c,
	.frames_d = batt_anim_frames_d,
	.frames_num = batt_anim_frames_num,
#endif
    .frames = batt_anim_frames,
    .num_frames = ARRAY_SIZE(batt_anim_frames),
    .num_cycles = 3,
};

static struct charger charger_state = {
    .batt_anim = &battery_animation,
};

static int char_width;
static int char_height;

static void write_file(const char *file_path, const char * str, int count)
{
    int fd = -1;
    fd = open(file_path, O_RDWR);
    if (fd >= 0) {
        write(fd, str, count);
        close(fd);
    }
}
void close_red_led()
{
    write_file("/sys/class/leds/red/brightness", "0", 1);
}
void open_red_led()
{
    write_file("/sys/class/leds/red/brightness", "255", 3);
}
void close_blue_led()
{
    write_file("/sys/class/leds/blue/brightness", "0", 1);
}
void open_blue_led()
{
    write_file("/sys/class/leds/blue/brightness", "255", 3);
}

void close_green_led()
{
    write_file("/sys/class/leds/green/brightness", "0", 1);
}
void open_green_led()
{
    write_file("/sys/class/leds/green/brightness", "255", 3);
}

void update_leds(int batt_cap)
{
//Gionee liujiang 2013-11-06 modify for poweroff charger 
	if (batt_cap < BATTERY_15_THRESH){
        close_blue_led();
        close_green_led();
		open_red_led();
	} else if (batt_cap < BATTERY_FULL_THRESH){
        close_red_led();
        close_green_led();
        open_blue_led();
    } else {
        close_red_led();
        close_blue_led();
		open_green_led();
    }
}

void exit_offmode_charging()
{
    close_blue_led();
    close_green_led();
    close_red_led();
    gr_exit();
    android_reboot(ANDROID_RB_RESTART, 0, 0);
}
unsigned int get_pmic_alarm_time()
{
    char buffer[80];
    int rc;
    static int fd = -1;
    unsigned int alarm_secs;

    if (fd < 0) {
        fd = open("/sys/android_alarm/alarmtimeinpmic", O_RDONLY);
        if (fd < 0) {
            return 0;
        }
    }

    lseek(fd, 0, SEEK_SET);
    rc = read(fd, buffer, sizeof(buffer));

    buffer[rc % 80] = '\0';

    sscanf(buffer, "0x%x", &alarm_secs);

    return alarm_secs;
}

unsigned int get_pmic_time()
{
    char buffer[80];
    int rc;
    static int fd = -1;
    unsigned int secs , tmp;

    if (fd < 0) {
        fd = open("/sys/android_alarm/alarmtimeinpmic", O_RDONLY);
        if (fd < 0) {
            return 0;
        }
    }

    lseek(fd, 0, SEEK_SET);
    rc = read(fd, buffer, sizeof(buffer));

    buffer[rc % 80] = '\0';

    sscanf(buffer, "0x%x,0x%x", &tmp, &secs);

    return secs;
}

/*On certain targets the FBIOBLANK ioctl does not turn off the
 * backlight. In those cases we need to manually toggle it on/off
 */
static int set_backlight(int toggle)
{
        int fd;
        char buffer[10];

        memset(buffer, '\0', sizeof(buffer));
        fd = open(BACKLIGHT_TOGGLE_PATH, O_RDWR);
        if (fd < 0) {
                LOGE("Could not open backlight node : %s", strerror(errno));
                goto cleanup;
        }
        if (toggle) {
                LOGI("Enabling backlight");
                snprintf(buffer, sizeof(int), "%d\n", 100);
        } else {
                LOGI("Disabling backlight");
                snprintf(buffer, sizeof(int), "%d\n", 0);
        }
        if (write(fd, buffer,strlen(buffer)) < 0) {
                LOGE("Could not write to backlight node : %s", strerror(errno));
                goto cleanup;
        }
cleanup:
        if (fd >= 0)
                close(fd);
        return 0;
}
/* current time in milliseconds */
static int64_t curr_time_ms(void)
{
    struct timespec tm;
    clock_gettime(CLOCK_MONOTONIC, &tm);
    return tm.tv_sec * MSEC_PER_SEC + (tm.tv_nsec / NSEC_PER_MSEC);
}

static int curr_realtime_s(void)
{
    struct timespec tm;
    clock_gettime(CLOCK_REALTIME, &tm);
    return tm.tv_sec;
}

static int Alarm_init()
{
    return open("/dev/alarm", O_RDWR);
}

static void Alarm_close(int fd)
{
    close(fd);
}

static void Alarm_set(int fd, int type, int seconds, int nanoseconds)
{
    struct timespec ts;
    ts.tv_sec = seconds;
    ts.tv_nsec = nanoseconds;

    int result = ioctl(fd, ANDROID_ALARM_SET(type), &ts);
    if (result < 0){
        LOGE("Unable to set alarm to %d,%d: %s\n", seconds, nanoseconds, strerror(errno));
    }
}
static int Alarm_wait(int fd)
{
    int result = 0;

    do{
        result = ioctl(fd, ANDROID_ALARM_WAIT);
    } while (result < 0 && errno == EINTR);

    if (result < 0){
        LOGE("Unable to wait on alarm: %s\n", strerror(errno));
        return 0;
    }

    return result;
}

static void clear_screen(void)
{
    gr_color(0, 0, 0, 255);
    gr_fill(0, 0, gr_fb_width(), gr_fb_height());
};

#define MAX_KLOG_WRITE_BUF_SZ 256

static void dump_last_kmsg(void)
{
    char *buf;
    char *ptr;
    unsigned sz = 0;
    int len;

    LOGI("\n");
    LOGI("*************** LAST KMSG ***************\n");
    LOGI("\n");
    buf = load_file(LAST_KMSG_PATH, &sz);
    if (!buf || !sz) {
        LOGI("last_kmsg not found. Cold reset?\n");
        goto out;
    }

    len = min(sz, LAST_KMSG_MAX_SZ);
    ptr = buf + (sz - len);

    while (len > 0) {
        int cnt = min(len, MAX_KLOG_WRITE_BUF_SZ);
        char yoink;
        char *nl;

        nl = memrchr(ptr, '\n', cnt - 1);
        if (nl)
            cnt = nl - ptr + 1;

        yoink = ptr[cnt];
        ptr[cnt] = '\0';
        klog_write(6, "<6>%s", ptr);
        ptr[cnt] = yoink;

        len -= cnt;
        ptr += cnt;
    }

    free(buf);

out:
    LOGI("\n");
    LOGI("************* END LAST KMSG *************\n");
    LOGI("\n");
}

static int read_file(const char *path, char *buf, size_t sz)
{
    int fd;
    size_t cnt;

    fd = open(path, O_RDONLY, 0);
    if (fd < 0)
        goto err;

    cnt = read(fd, buf, sz - 1);
    if (cnt <= 0)
        goto err;
    buf[cnt] = '\0';
    if (buf[cnt - 1] == '\n') {
        cnt--;
        buf[cnt] = '\0';
    }

    close(fd);
    return cnt;

err:
    if (fd >= 0)
        close(fd);
    return -1;
}

static int read_file_int(const char *path, int *val)
{
    char buf[32];
    int ret;
    int tmp;
    char *end;

    ret = read_file(path, buf, sizeof(buf));
    if (ret < 0)
        return -1;

    tmp = strtol(buf, &end, 0);
    if (end == buf ||
        ((end < buf+sizeof(buf)) && (*end != '\n' && *end != '\0')))
        goto err;

    *val = tmp;
    return 0;

err:
    return -1;
}

static int get_battery_capacity(struct charger *charger)
{
    int ret;
    int batt_cap = -1;

    if (!charger->battery)
        return -1;

    ret = read_file_int(charger->battery->cap_path, &batt_cap);
    if (ret < 0 || batt_cap > 100) {
        batt_cap = -1;
    }

    return batt_cap;
}

static struct power_supply *find_supply(struct charger *charger,
                                        const char *name)
{
    struct listnode *node;
    struct power_supply *supply;

    list_for_each(node, &charger->supplies) {
        supply = node_to_item(node, struct power_supply, list);
        if (!strncmp(name, supply->name, sizeof(supply->name)))
            return supply;
    }
    return NULL;
}

static struct power_supply *add_supply(struct charger *charger,
                                       const char *name, const char *type,
                                       const char *path, bool online)
{
    struct power_supply *supply;

    supply = calloc(1, sizeof(struct power_supply));
    if (!supply)
        return NULL;

    strlcpy(supply->name, name, sizeof(supply->name));
    strlcpy(supply->type, type, sizeof(supply->type));
    snprintf(supply->cap_path, sizeof(supply->cap_path),
             "/sys/%s/capacity", path);
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	snprintf(supply->health_path, sizeof(supply->cap_path),
             "/sys/%s/health", path);
#endif
//Gionee liujiang 2013-11-18 add for battery health end
    supply->online = online;
    list_add_tail(&charger->supplies, &supply->list);
    charger->num_supplies++;
    LOGV("... added %s %s %d\n", supply->name, supply->type, online);
    return supply;
}

static void remove_supply(struct charger *charger, struct power_supply *supply)
{
    if (!supply)
        return;
    list_remove(&supply->list);
    charger->num_supplies--;
    free(supply);
}

#ifdef CHARGER_ENABLE_SUSPEND
static int request_suspend(bool enable)
{
    if (enable)
        return autosuspend_enable();
    else
        return autosuspend_disable();
}
#else
static int request_suspend(bool enable)
{
    return 0;
}
#endif

static void parse_uevent(const char *msg, struct uevent *uevent)
{
    uevent->action = "";
    uevent->path = "";
    uevent->subsystem = "";
    uevent->ps_name = "";
    uevent->ps_online = "";
    uevent->ps_type = "";

    /* currently ignoring SEQNUM */
    while (*msg) {
#ifdef DEBUG_UEVENTS
        LOGV("uevent str: %s\n", msg);
#endif
        if (!strncmp(msg, "ACTION=", 7)) {
            msg += 7;
            uevent->action = msg;
        } else if (!strncmp(msg, "DEVPATH=", 8)) {
            msg += 8;
            uevent->path = msg;
        } else if (!strncmp(msg, "SUBSYSTEM=", 10)) {
            msg += 10;
            uevent->subsystem = msg;
        } else if (!strncmp(msg, "POWER_SUPPLY_NAME=", 18)) {
            msg += 18;
            uevent->ps_name = msg;
        } else if (!strncmp(msg, "POWER_SUPPLY_ONLINE=", 20)) {
            msg += 20;
            uevent->ps_online = msg;
        } else if (!strncmp(msg, "POWER_SUPPLY_TYPE=", 18)) {
            msg += 18;
            uevent->ps_type = msg;
        }

        /* advance to after the next \0 */
        while (*msg++)
            ;
    }

    LOGV("event { '%s', '%s', '%s', '%s', '%s', '%s' }\n",
         uevent->action, uevent->path, uevent->subsystem,
         uevent->ps_name, uevent->ps_type, uevent->ps_online);
}

static void process_ps_uevent(struct charger *charger, struct uevent *uevent)
{
    int online;
    char ps_type[32];
    struct power_supply *supply = NULL;
    int i;
    bool was_online = false;
    bool battery = false;

    if (uevent->ps_type[0] == '\0') {
        char *path;
        int ret;

        if (uevent->path[0] == '\0')
            return;
        ret = asprintf(&path, "/sys/%s/type", uevent->path);
        if (ret <= 0)
            return;
        ret = read_file(path, ps_type, sizeof(ps_type));
        free(path);
        if (ret < 0)
            return;
    } else {
        strlcpy(ps_type, uevent->ps_type, sizeof(ps_type));
    }

//Gionee liujiang 2014-05-22 add for CR01216121
    if ((!strncmp(ps_type, "Battery", 7))&&(!strncmp(uevent->ps_name, "battery", 7)))
        battery = true;

    online = atoi(uevent->ps_online);
    supply = find_supply(charger, uevent->ps_name);
    if (supply) {
        was_online = supply->online;
        supply->online = online;
    }

    if (!strcmp(uevent->action, "add")) {
        if (!supply) {
            supply = add_supply(charger, uevent->ps_name, ps_type, uevent->path,
                                online);
            if (!supply) {
                LOGE("cannot add supply '%s' (%s %d)\n", uevent->ps_name,
                     uevent->ps_type, online);
                return;
            }
            /* only pick up the first battery for now */
            if (battery && !charger->battery)
                charger->battery = supply;
        } else {
            LOGE("supply '%s' already exists..\n", uevent->ps_name);
        }
    } else if (!strcmp(uevent->action, "remove")) {
        if (supply) {
            if (charger->battery == supply)
                charger->battery = NULL;
            remove_supply(charger, supply);
            supply = NULL;
        }
    } else if (!strcmp(uevent->action, "change")) {
        if (!supply) {
            LOGE("power supply '%s' not found ('%s' %d)\n",
                 uevent->ps_name, ps_type, online);
            return;
        }
    } else {
        return;
    }

    /* allow battery to be managed in the supply list but make it not
     * contribute to online power supplies. */
    if (!battery) {
        if (was_online && !online)
            charger->num_supplies_online--;
        else if (supply && !was_online && online)
            charger->num_supplies_online++;
    }

    LOGI("power supply %s (%s) %s (action=%s num_online=%d num_supplies=%d)\n",
         uevent->ps_name, ps_type, battery ? "" : online ? "online" : "offline",
         uevent->action, charger->num_supplies_online, charger->num_supplies);
}

static void process_uevent(struct charger *charger, struct uevent *uevent)
{
    if (!strcmp(uevent->subsystem, "power_supply"))
        process_ps_uevent(charger, uevent);
}

#define UEVENT_MSG_LEN  1024
static int handle_uevent_fd(struct charger *charger, int fd)
{
    char msg[UEVENT_MSG_LEN+2];
    int n;

    if (fd < 0)
        return -1;

    while (true) {
        struct uevent uevent;

        n = uevent_kernel_multicast_recv(fd, msg, UEVENT_MSG_LEN);
        if (n <= 0)
            break;
        if (n >= UEVENT_MSG_LEN)   /* overflow -- discard */
            continue;

        msg[n] = '\0';
        msg[n+1] = '\0';

        parse_uevent(msg, &uevent);
        process_uevent(charger, &uevent);
    }

    return 0;
}

static int uevent_callback(int fd, short revents, void *data)
{
    struct charger *charger = data;

    if (!(revents & POLLIN))
        return -1;
    return handle_uevent_fd(charger, fd);
}

/* force the kernel to regenerate the change events for the existing
 * devices, if valid */
static void do_coldboot(struct charger *charger, DIR *d, const char *event,
                        bool follow_links, int max_depth)
{
    struct dirent *de;
    int dfd, fd;

    dfd = dirfd(d);

    fd = openat(dfd, "uevent", O_WRONLY);
    if (fd >= 0) {
        write(fd, event, strlen(event));
        close(fd);
        handle_uevent_fd(charger, charger->uevent_fd);
    }

    while ((de = readdir(d)) && max_depth > 0) {
        DIR *d2;

        LOGV("looking at '%s'\n", de->d_name);

        if ((de->d_type != DT_DIR && !(de->d_type == DT_LNK && follow_links)) ||
           de->d_name[0] == '.') {
            LOGV("skipping '%s' type %d (depth=%d follow=%d)\n",
                 de->d_name, de->d_type, max_depth, follow_links);
            continue;
        }
        LOGV("can descend into '%s'\n", de->d_name);

        fd = openat(dfd, de->d_name, O_RDONLY | O_DIRECTORY);
        if (fd < 0) {
            LOGE("cannot openat %d '%s' (%d: %s)\n", dfd, de->d_name,
                 errno, strerror(errno));
            continue;
        }

        d2 = fdopendir(fd);
        if (d2 == 0)
            close(fd);
        else {
            LOGV("opened '%s'\n", de->d_name);
            do_coldboot(charger, d2, event, follow_links, max_depth - 1);
            closedir(d2);
        }
    }
}

static void coldboot(struct charger *charger, const char *path,
                     const char *event)
{
    char str[256];

    LOGV("doing coldboot '%s' in '%s'\n", event, path);
    DIR *d = opendir(path);
    if (d) {
        snprintf(str, sizeof(str), "%s\n", event);
        do_coldboot(charger, d, str, true, 1);
        closedir(d);
    }
}

static int draw_text(const char *str, int x, int y)
{
    int str_len_px = gr_measure(str);

    if (x < 0)
        x = (gr_fb_width() - str_len_px) / 2;
    if (y < 0)
        y = (gr_fb_height() - char_height) / 2;
    gr_text(x, y, str, 0);

    return y + char_height;
}

static void android_green(void)
{
    gr_color(0xa4, 0xc6, 0x39, 255);
}

/* returns the last y-offset of where the surface ends */
static int draw_surface_centered(struct charger *charger, gr_surface surface)
{
    int w;
    int h;
    int x;
    int y;

    w = gr_get_width(surface);
    h = gr_get_height(surface);
    x = (gr_fb_width() - w) / 2 ;
    y = (gr_fb_height() - h) / 2 ;

    LOGV("drawing surface %dx%d+%d+%d\n", w, h, x, y);
    gr_blit(surface, 0, 0, w, h, x, y);
    return y + h;
}

static void draw_unknown(struct charger *charger)
{
    int y;
    if (charger->surf_unknown) {
        draw_surface_centered(charger, charger->surf_unknown);
    } else {
        android_green();
        y = draw_text("Charging!", -1, -1);
        draw_text("?\?/100", -1, y + 25);
    }
}

static void draw_capacity(struct charger *charger)
{
    char cap_str[64];
    int x, y;
    int str_len_px;

    snprintf(cap_str, sizeof(cap_str), "%d%%", charger->batt_anim->capacity);
    str_len_px = gr_measure(cap_str);
    x = (gr_fb_width() - str_len_px) / 2;
    y = (gr_fb_height() + char_height) / 2;
    android_green();
    gr_text(x, y, cap_str, 0);
}

static void draw_battery(struct charger *charger)
{
    struct animation *batt_anim = charger->batt_anim;
    struct frame *frame = &batt_anim->frames[batt_anim->cur_frame];

    if (batt_anim->num_frames != 0) {
        draw_surface_centered(charger, frame->surface);
        LOGV("drawing frame #%d name=%s min_cap=%d time=%d\n",
             batt_anim->cur_frame, frame->name, frame->min_capacity,
             frame->disp_time);
    }
}

//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
static void draw_surface_num_gionee(struct charger *charger)
{
    gr_surface surface;
    int w;
    int h;
    int i,x,y,n,m,capacity;

    n = 2;
    capacity = charger->batt_anim->capacity;
    if(charger->batt_anim->capacity < 10)
    {
        n = 0;

    }
    else if(charger->batt_anim->capacity < 100)
    {
        n = 1;
    }
    x = BATTERY_X + BATTERY_W - (BATTERY_W - ((2+n)*NUM_W + (n+1)*NUM_SPACE))/2 - NUM_W;
    y = BATTERY_Y - 264;
    surface = charger->batt_anim->frames_num[10].surface;
    for(i=0;i<(n+2);i++)
    {

        w = gr_get_width(surface);
        h = gr_get_height(surface);
        gr_blit(surface, 0, 0, w, h, x, y);
        m = capacity % 10;
        capacity /= 10;
        surface = charger->batt_anim->frames_num[m].surface;
        x -= (NUM_W + NUM_SPACE);
    }

}
static int draw_surface_anim_gionee(struct charger *charger, gr_surface surface)
{
    int w;
    int h;
    int x;
    int y;

    w = gr_get_width(surface);
    h = gr_get_height(surface);
    x = ANIM_X;
    y = ANIM_Y +(100-charger->batt_anim->capacity)*(BATTERY_H-ANIN_H)/100;

    LOGV("drawing surface %dx%d+%d+%d\n", w, h, x, y);
    gr_blit(surface, 0, 0, w, h, x, y);
    return y + h;
}

static void draw_battery_bg_gionee(struct charger *charger)
{
    int w,h,x,cnt;
    int y,y1,i;
    if (charger->battery_bg) {
        draw_surface_centered(charger, charger->battery_bg);
    } 

    if (charger->battery_line) {
        w = gr_get_width(charger->battery_line);
        h = gr_get_height(charger->battery_line);
        x = ANIM_X;
        y = ANIM_Y+(100-charger->batt_anim->capacity)*(BATTERY_H-ANIN_H)/100+ANIN_H;
		y1 = ANIM_Y+BATTERY_H;
        cnt =(y>y1)?0:(y1-y);
        for(i=0;i<cnt;i++)
        {
            y1 = y+i;
            gr_blit(charger->battery_line, 0, 0, w, h, x, y1);
        }
    }

    
}
typedef int (*pdraw_surface_fun)(struct charger *,gr_surface);

static void draw_battery_gionee(struct charger *charger)
{
    struct animation *batt_anim = charger->batt_anim;
    struct frame *frame = &batt_anim->frames[batt_anim->cur_frame];
    pdraw_surface_fun pdraw_surface;

    if(batt_anim->capacity >= 100)
    {
        if (charger->battery_full) {
            draw_surface_centered(charger, charger->battery_full);
        } 
        return;

    }
    else if(batt_anim->capacity<=15)
    {

        frame = &batt_anim->frames_15percent[batt_anim->cur_frame];
        pdraw_surface = draw_surface_centered;
    }
    else
    {
        draw_battery_bg_gionee(charger);
        pdraw_surface = draw_surface_anim_gionee;
    }

    if (batt_anim->num_frames != 0) {
        pdraw_surface(charger, frame->surface);
        LOGV("drawing frame #%d name=%s min_cap=%d time=%d\n",
             batt_anim->cur_frame, frame->name, frame->min_capacity,
             frame->disp_time);
    }
    draw_surface_num_gionee(charger);
}
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end

#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
static int draw_surface_amigo_main(struct charger *charger,gr_surface surface)
{
	int w;
    int h;

    w = gr_get_width(surface);
    h = gr_get_height(surface);

	LOGV("drawing amigo surface main %dx%d+%d+%d\n", w, h, AMIGO_MAIN_X, AMIGO_MAIN_Y);
    gr_blit(surface, 0, 0, w, h, AMIGO_MAIN_X, AMIGO_MAIN_Y);
    return AMIGO_MAIN_Y + h;
}

static void draw_capacity_amigo(struct charger *charger)
{
    gr_surface surface;
    int w,total_w;
    int h;
    int i,x,y,n,m,capacity;

    capacity = charger->batt_anim->capacity;
    if(charger->batt_anim->capacity < 10)
        n = 0;
    else if(charger->batt_anim->capacity < 100)
        n = 1;
	else
		n = 2;
	total_w = n*(AMIGO_NUM_W + AMIGO_NUM_SPACE_W) + AMIGO_NUM_PERENT_W;
    x = (gr_fb_width()-total_w)/2 + total_w - AMIGO_NUM_PERENT_W;
    y = AMIGO_NUM_Y;
	
    surface = charger->batt_anim->frames_num[10].surface;
    for(i=0;i<(n+2);i++)
    {
        w = gr_get_width(surface);
        h = gr_get_height(surface);
        gr_blit(surface, 0, 0, w, h, x, y);
        m = capacity % 10;
        capacity /= 10;
        surface = charger->batt_anim->frames_num[m].surface;
        x -= (AMIGO_NUM_W + AMIGO_NUM_SPACE_W);
    }

}

static void draw_battery_amigo(struct charger *charger)
{
	struct animation *batt_anim = charger->batt_anim;
    struct frame *frame;
	
    if(batt_anim->capacity >= 100)
    {
		if (charger->battery_full) {
            draw_surface_amigo_main(charger, charger->battery_full);
        } 
        return;
    }
	else if(batt_anim->capacity >= 61)
	{
		frame = &batt_anim->frames[batt_anim->cur_frame];
	}
	else if(batt_anim->capacity >= 31)
	{
		frame = &batt_anim->frames_b[batt_anim->cur_frame];
	}
	else if(batt_anim->capacity >= 11)
	{
		frame = &batt_anim->frames_c[batt_anim->cur_frame];
	}
	else
	{
		frame = &batt_anim->frames_d[batt_anim->cur_frame];
	}
	if (frame->surface)
		draw_surface_amigo_main(charger, frame->surface);
}
#endif
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
int get_battery_health(struct charger *charger)
{
	int ret;
    int batt_health = POWER_SUPPLY_HEALTH_UNKNOWN;
	char health_status[10];

    if (!charger->battery)
        return -1;

    ret = read_file(charger->battery->health_path, health_status,sizeof(health_status));
    if (ret < 0) {
		LOGI("read battery health file failed\n");
        batt_health = POWER_SUPPLY_HEALTH_UNKNOWN;
    }
	else
	{
		int i;
		LOGI("battery health:%s\n",health_status);
		for(i=0; i<sizeof(health_text); i++)
		{
			ret = memcmp(health_status,health_text[i],strlen(health_text[i]));
			if (!ret)
				break;
		}
		if ((i == sizeof(health_text))||(
			(i != POWER_SUPPLY_HEALTH_GOOD)&&
			(i != POWER_SUPPLY_HEALTH_OVERHEAT)&&
			(i != POWER_SUPPLY_HEALTH_COLD)))
			i = POWER_SUPPLY_HEALTH_UNKNOWN;
		batt_health = i;
	}
    return batt_health;
}
void draw_battery_health_gionee(struct charger *charger)
{
	if(charger->battery->health == POWER_SUPPLY_HEALTH_OVERHEAT)
	{
		LOGI("liujiang charger  draw_battery_overheat\n");
		draw_surface_centered(charger, charger->battery_overheat);
	}
	else if(charger->battery->health == POWER_SUPPLY_HEALTH_COLD)
	{
		LOGI("liujiang charger  draw_battery_overheat\n");
		draw_surface_centered(charger, charger->battery_cold);
	}
}
#endif
//Gionee liujiang 2013-11-18 add for battery health end
static void redraw_screen(struct charger *charger)
{
    struct animation *batt_anim = charger->batt_anim;

    clear_screen();

    /* try to display *something* */
    if (batt_anim->capacity < 0 || batt_anim->num_frames == 0)
        draw_unknown(charger);
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	else if(charger->battery->health != POWER_SUPPLY_HEALTH_GOOD)
		draw_battery_health_gionee(charger);
#endif
//Gionee liujiang 2013-11-18 add for battery health end
    else {
//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
        draw_battery_gionee(charger);
#endif
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_DEFAULT
        draw_battery(charger);
        draw_capacity(charger);
#endif
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
		draw_battery_amigo(charger);
        draw_capacity_amigo(charger);
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
        draw_battery(charger);
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end
    }
    gr_flip();
}

static void kick_animation(struct animation *anim)
{
    anim->run = true;
}

static void reset_animation(struct animation *anim)
{
    anim->cur_cycle = 0;
    anim->cur_frame = 0;
    anim->run = false;
}

static void update_screen_state(struct charger *charger, int64_t now)
{
    struct animation *batt_anim = charger->batt_anim;
    int cur_frame;
    int disp_time;

    if (!batt_anim->run || now < charger->next_screen_transition)
        return;

    /* animation is over, blank screen and leave */
    if (batt_anim->cur_cycle == batt_anim->num_cycles) {
        reset_animation(batt_anim);
//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
		batt_anim->num_frames = ARRAY_SIZE(batt_anim_frames);
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end
        charger->next_screen_transition = -1;
        set_backlight(false);
        gr_fb_blank(true);
        LOGV("[%lld] animation done\n", now);
        if (charger->num_supplies_online > 0)
            request_suspend(true);
        return;
    }

    disp_time = batt_anim->frames[batt_anim->cur_frame].disp_time;

    /* animation starting, set up the animation */
    if (batt_anim->cur_frame == 0) {
        int batt_cap;
        int ret;

        LOGV("[%lld] animation starting\n", now);
        batt_cap = get_battery_capacity(charger);
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_DEFAULT
        if (batt_cap >= 0 && batt_anim->num_frames != 0) {
            int i;

            /* find first frame given current capacity */
            for (i = 1; i < batt_anim->num_frames; i++) {
                if (batt_cap < batt_anim->frames[i].min_capacity)
                    break;
            }
            batt_anim->cur_frame = i - 1;

            /* show the first frame for twice as long */
            disp_time = batt_anim->frames[batt_anim->cur_frame].disp_time * 2;
        }
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
		batt_anim->cur_frame = batt_cap/10;
		disp_time = batt_anim->frames[batt_anim->cur_frame].disp_time;
		batt_anim->num_frames = batt_anim->cur_frame + 1;
		batt_anim->num_cycles = 1; 
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end
        batt_anim->capacity = batt_cap;
    }

    /* unblank the screen  on first cycle */
    if (batt_anim->cur_cycle == 0){
        gr_fb_blank(false);
        set_backlight(true);
    }
//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	charger->battery->health = get_battery_health(charger);
#endif
//Gionee liujiang 2013-11-18 add for battery health end
    /* draw the new frame (@ cur_frame) */
    redraw_screen(charger);

    /* if we don't have anim frames, we only have one image, so just bump
     * the cycle counter and exit
     */
    if (batt_anim->num_frames == 0 || batt_anim->capacity < 0) {
        LOGV("[%lld] animation missing or unknown battery status\n", now);
        charger->next_screen_transition = now + BATTERY_UNKNOWN_TIME;
        batt_anim->cur_cycle++;
        return;
    }

    /* schedule next screen transition */
    charger->next_screen_transition = now + disp_time;

    /* advance frame cntr to the next valid frame
     * if necessary, advance cycle cntr, and reset frame cntr
     */
    batt_anim->cur_frame++;

    /* if the frame is used for level-only, that is only show it when it's
     * the current level, skip it during the animation.
     */
    while (batt_anim->cur_frame < batt_anim->num_frames &&
           batt_anim->frames[batt_anim->cur_frame].level_only)
        batt_anim->cur_frame++;
    if (batt_anim->cur_frame >= batt_anim->num_frames) {
        batt_anim->cur_cycle++;
        batt_anim->cur_frame = 0;

        /* don't reset the cycle counter, since we use that as a signal
         * in a test above to check if animation is over
         */
    }
}

static int set_key_callback(int code, int value, void *data)
{
    struct charger *charger = data;
    int64_t now = curr_time_ms();
    int down = !!value;

    if (code > KEY_MAX)
        return -1;

    /* ignore events that don't modify our state */
    if (charger->keys[code].down == down)
        return 0;

    /* only record the down even timestamp, as the amount
     * of time the key spent not being pressed is not useful */
    if (down)
        charger->keys[code].timestamp = now;
    charger->keys[code].down = down;
    charger->keys[code].pending = true;
    if (down) {
        LOGV("[%lld] key[%d] down\n", now, code);
    } else {
        int64_t duration = now - charger->keys[code].timestamp;
        int64_t secs = duration / 1000;
        int64_t msecs = duration - secs * 1000;
        LOGV("[%lld] key[%d] up (was down for %lld.%lldsec)\n", now,
            code, secs, msecs);
    }

    return 0;
}

static void update_input_state(struct charger *charger,
                               struct input_event *ev)
{
    if (ev->type != EV_KEY)
        return;
    set_key_callback(ev->code, ev->value, charger);
}

static void set_next_key_check(struct charger *charger,
                               struct key_state *key,
                               int64_t timeout)
{
    int64_t then = key->timestamp + timeout;

    if (charger->next_key_check == -1 || then < charger->next_key_check)
        charger->next_key_check = then;
}

static void process_key(struct charger *charger, int code, int64_t now)
{
    struct key_state *key = &charger->keys[code];
    int64_t next_key_check;

    if (code == KEY_POWER) {
        if (key->down) {
            int64_t reboot_timeout = key->timestamp + POWER_ON_KEY_TIME;
            if (now >= reboot_timeout) {
                LOGI("process_key now:[%lld] reboot_timeout:[%lld] exit off mode charging\n", now, reboot_timeout);
                clear_screen();
                gr_flip();
                exit_offmode_charging();
            } else {
                /* if the key is pressed but timeout hasn't expired,
                 * make sure we wake up at the right-ish time to check
                 */
                set_next_key_check(charger, key, POWER_ON_KEY_TIME);
            }
        } else {
            /* if the power key got released, force screen state cycle */
            if (key->pending){
//Gionee liujiang 2014-06-12 modify for CR01288132 start
				if(false == charger->batt_anim->run)
				{
					request_suspend(false);
	                kick_animation(charger->batt_anim);
				}
				else
				{
					reset_animation(charger->batt_anim);
//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
					charger->batt_anim->num_frames = ARRAY_SIZE(batt_anim_frames);
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end
			        charger->next_screen_transition = -1;
			        set_backlight(false);
			        gr_fb_blank(true);
			        LOGV("[%lld] animation done by power key\n", now);
			        if (charger->num_supplies_online > 0)
			            request_suspend(true);
				}
//Gionee liujiang 2014-06-12 modify for CR01288132 end
            }
        }
    }

    key->pending = false;
}

static void handle_input_state(struct charger *charger, int64_t now)
{
    process_key(charger, KEY_POWER, now);

    if (charger->next_key_check != -1 && now > charger->next_key_check)
        charger->next_key_check = -1;
}

static void handle_power_supply_state(struct charger *charger, int64_t now)
{
    if (charger->num_supplies_online == 0) {
        request_suspend(false);
        if (charger->next_pwr_check == -1) {
            charger->next_pwr_check = now + UNPLUGGED_SHUTDOWN_TIME;
            LOGI("[%lld] device unplugged: shutting down in %lld (@ %lld)\n",
                 now, UNPLUGGED_SHUTDOWN_TIME, charger->next_pwr_check);
        } else if (now >= charger->next_pwr_check) {
            LOGI("handle_power_supply_state now:[%lld] charger->next_pwr_check:[%lld] shutting down\n", now, charger->next_pwr_check);
            LOGI("[%lld] shutting down\n", now);
            android_reboot(ANDROID_RB_POWEROFF, 0, 0);
        } else {
            /* otherwise we already have a shutdown timer scheduled */
        }
    } else {
        /* online supply present, reset shutdown timer if set */
        if (charger->next_pwr_check != -1) {
            LOGI("[%lld] device plugged in: shutdown cancelled\n", now);
            kick_animation(charger->batt_anim);
        }
        charger->next_pwr_check = -1;
    }
}

static void wait_next_event(struct charger *charger, int64_t now)
{
    int64_t next_event = INT64_MAX;
    int64_t timeout;
    struct input_event ev;
    int ret;

    LOGV("[%lld] next screen: %lld next key: %lld next pwr: %lld\n", now,
         charger->next_screen_transition, charger->next_key_check,
         charger->next_pwr_check);

    if (charger->next_screen_transition != -1)
        next_event = charger->next_screen_transition;
    if (charger->next_key_check != -1 && charger->next_key_check < next_event)
        next_event = charger->next_key_check;
    if (charger->next_pwr_check != -1 && charger->next_pwr_check < next_event)
        next_event = charger->next_pwr_check;

    if (next_event != -1 && next_event != INT64_MAX)
        timeout = max(0, next_event - now);
    else
        timeout = -1;
    LOGV("[%lld] blocking (%lld)\n", now, timeout);
    ret = ev_wait((int)timeout);
    if (!ret)
        ev_dispatch();
}

static int input_callback(int fd, short revents, void *data)
{
    struct charger *charger = data;
    struct input_event ev;
    int ret;

    ret = ev_get_input(fd, revents, &ev);
    if (ret)
        return -1;
    update_input_state(charger, &ev);
    return 0;
}

static void event_loop(struct charger *charger)
{
    int ret;

    while (true) {
        int64_t now = curr_time_ms();

        LOGV("[%lld] event_loop()\n", now);
        handle_input_state(charger, now);
        //handle_power_supply_state(charger, now);

        //In the charging mode, we don't need to check sync and remount_ro. just make target reboot.
        //the flag ANDROID_RB_FLAG_NO_STOP_MD is not suit for this case.
        //use (ANDROID_RB_FLAG_NO_SYNC | ANDROID_RB_FLAG_NO_REMOUNT_RO) to replace ANDROID_RB_FLAG_NO_STOP_MD.
        //Add 2 seconds sleep before enter event loop to wait for Power_supply enable.
        if ((!is_usb_exist()) && (!is_ac_exist()) && (!is_unknown_exist())){
            LOGI("event_loop shutting down is_usb_exist()=%d is_ac_exist()=%d is_unknown_exist()=%d\n", is_usb_exist(), is_ac_exist(), is_unknown_exist());
            LOGI("[%lld] shutting down\n", now);
//Gionee wudp 2013.03.29 add for save poweroff chg log begin    
#if defined(CONFIG_GN_Q_BSP_SAVE_POWEROFFCHG_LOG_SUPPORT)
	    property_set("ctl.stop", "savekmsg");
#endif
//Gionee wudp 2013.03.29 add for save poweroff chg log end
            android_reboot(ANDROID_RB_POWEROFF,
                0, 0);
        }

        /* do screen update last in case any of the above want to start
         * screen transitions (animations, etc)
         */
        update_screen_state(charger, now);
        update_leds(get_battery_capacity(charger));

        unsigned int pmic_current_time = get_pmic_time();
        unsigned int pmic_alarm_time = get_pmic_alarm_time();

        if (pmic_current_time != 0 && pmic_alarm_time != 0){
            if (pmic_alarm_time >= (unsigned int)pmic_current_time &&
	            pmic_alarm_time - (unsigned int)pmic_current_time <= 15){
		            LOGI("event_loop pmic_alarm_time=%lld >= pmic_current_time=%lld\n", pmic_alarm_time, pmic_current_time);
                    LOGI("[%lld] exit off mode charging\n", now);
                    exit_offmode_charging();
	        }else if (pmic_alarm_time < (unsigned int)pmic_current_time &&
	                 (unsigned int)pmic_current_time - pmic_alarm_time <= 60){
 		            LOGI("event_loop pmic_alarm_time=%lld < pmic_current_time=%lld\n", pmic_alarm_time, pmic_current_time);
                    LOGI("[%lld] exit off mode charging\n", now);
                    exit_offmode_charging();
	        }
        }

        wait_next_event(charger, now);
    }
}

void * alarm_thread( void * p)
{
    int fd;
    fd = Alarm_init();
//Gionee, chuqf, 2013-09-21, rtc alarm, begin
#if defined(CONFIG_GN_Q_BSP_KERNEL_RTC_ALARM_SUPPORT)				
	unsigned int pmic_current_time;
	unsigned int pmic_alarm_time;
#endif
//Gionee, chuqf, 2013-09-21, rtc alarm, end			
    while(1){
//Gionee, chuqf, 2013-09-21, rtc alarm, begin
#if defined(CONFIG_GN_Q_BSP_KERNEL_RTC_ALARM_SUPPORT)				
        pmic_current_time = get_pmic_time();
        pmic_alarm_time = get_pmic_alarm_time();
        if (pmic_current_time != 0 && pmic_alarm_time != 0){
            if (pmic_alarm_time >= (unsigned int)pmic_current_time &&
	            pmic_alarm_time - (unsigned int)pmic_current_time <= 60){
                    LOGI("poweroff alarm arrived, exit off mode charging, pmic_alarm_time: %d, pmic_current_time: %d\n", pmic_alarm_time, pmic_current_time);
                    exit_offmode_charging();
	        }else if (pmic_alarm_time < (unsigned int)pmic_current_time &&
	                 (unsigned int)pmic_current_time - pmic_alarm_time <= 60){
                    LOGI("poweroff alarm arrived, exit off mode charging, pmic_alarm_time: %d, pmic_current_time: %d\n", pmic_alarm_time, pmic_current_time);
                    exit_offmode_charging();
	        }
        }
#endif
//Gionee, chuqf, 2013-09-21, rtc alarm, end		
		
        Alarm_set(fd, ANDROID_ALARM_RTC_WAKEUP, curr_realtime_s() + 30, 0);
        Alarm_wait(fd);
        LOGE("Alarm arrived %d\n", curr_realtime_s());
    }

    return NULL;
}

void create_alarm_thread()
{
    pthread_t ptid;
    int res;
    res = pthread_create(&ptid, NULL, alarm_thread, NULL);
    if (res < 0){
        fprintf(stderr, "can't create pthread: %s\n", strerror(errno));
    }

    return;
}

int main(int argc, char **argv)
{
    int ret;
    struct charger *charger = &charger_state;
    int64_t now = curr_time_ms() - 1;
    int fd;
    int i;
//Gionee liujiang 2013-11-06 add for poweroff charger start
	int batt_cap;
	
	ret = read_file_int("/sys/class/power_supply/battery/capacity", &batt_cap);
    if (ret >= 0 && batt_cap <= 100) {
        update_leds(batt_cap);
    }
//Gionee liujiang 2013-11-06 add for poweroff charger end
    /* add 2 seconds sleep to wait for Power_supply enable. */
    sleep(2);

    create_alarm_thread();

    list_init(&charger->supplies);

    klog_init();
    klog_set_level(CHARGER_KLOG_LEVEL);

    dump_last_kmsg();
//Gionee wudp 2013.03.29 add for save poweroff chg log begin    
#if defined(CONFIG_GN_Q_BSP_SAVE_POWEROFFCHG_LOG_SUPPORT)
    property_set("ctl.start", "savekmsg");
#endif
//Gionee wudp 2013.03.29 add for save poweroff chg log end
    LOGI("--------------- STARTING CHARGER MODE ---------------\n");

    gr_init();
    gr_font_size(&char_width, &char_height);

    ev_init(input_callback, charger);

    fd = uevent_open_socket(64*1024, true);
    if (fd >= 0) {
        fcntl(fd, F_SETFL, O_NONBLOCK);
        ev_add_fd(fd, uevent_callback, charger);
    }
    charger->uevent_fd = fd;
    coldboot(charger, "/sys/class/power_supply", "add");
	
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_DEFAULT
    ret = res_create_surface("charger/battery_fail", &charger->surf_unknown);
    if (ret < 0) {
        LOGE("Cannot load image\n");
        charger->surf_unknown = NULL;
    }

    for (i = 0; i < charger->batt_anim->num_frames; i++) {
        struct frame *frame = &charger->batt_anim->frames[i];

        ret = res_create_surface(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
    }
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 begin
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_GIONEE
    ret = res_create_surface_png("charger/fhd_bat_bg", &charger->battery_bg);
    if (ret < 0) {
        LOGE("Cannot load bg image\n");
        charger->battery_bg = NULL;
    }
    ret = res_create_surface_png("charger/fhd_bat_img", &charger->battery_line);
    if (ret < 0) {
        LOGE("Cannot load line image\n");
        charger->battery_line = NULL;
    }
    ret = res_create_surface_png("charger/fhd_bat_100", &charger->battery_full);
	if (ret < 0) {
        LOGE("Cannot load full image\n");
        charger->battery_full = NULL;
    }
	for (i = 0; i < charger->batt_anim->num_frames; i++) {
        struct frame *frame = &charger->batt_anim->frames[i];

        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
        frame = &charger->batt_anim->frames_15percent[i];

        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image 15percent %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        } 
    }
	
	for (i = 0; i < ARRAY_SIZE(batt_frames_num); i++) {
        struct frame *frame = &charger->batt_anim->frames_num[i];

        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot num image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
 
    }
#endif
//Gionee liujiang 2013-11-06 add for CR00942122 end
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_AMIGO
	ret = res_create_surface_png("charger/amigo_chg_fhd_full", &charger->battery_full);
	if (ret < 0) {
        LOGE("Cannot load full image\n");
        charger->battery_full = NULL;
    }
	for (i = 0; i < charger->batt_anim->num_frames; i++) {
        struct frame *frame = &charger->batt_anim->frames[i];

        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
		
        frame = &charger->batt_anim->frames_b[i];
        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image frame_b %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        } 

		frame = &charger->batt_anim->frames_c[i];
        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image frame_c %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        } 

		frame = &charger->batt_anim->frames_d[i];
        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image frame_d %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        } 
    }
	
	for (i = 0; i < ARRAY_SIZE(batt_anim_frames_num); i++) {
        struct frame *frame = &charger->batt_anim->frames_num[i];

        ret = res_create_surface_png(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot num image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
    }
#endif

//Gionee liujiang 2014-06-06 add for iuni charge ui start
#ifdef GN_Q_BSP_POWEROFF_CHG_UI_IUNI
    for (i = 0; i < charger->batt_anim->num_frames; i++) {
        struct frame *frame = &charger->batt_anim->frames[i];

        ret = res_create_surface(frame->name, &frame->surface);
        if (ret < 0) {
            LOGE("Cannot load image %s\n", frame->name);
            /* TODO: free the already allocated surfaces... */
            charger->batt_anim->num_frames = 0;
            charger->batt_anim->num_cycles = 1;
            break;
        }
    }
#endif
//Gionee liujiang 2014-06-06 add for iuni charge ui end

//Gionee liujiang 2013-11-18 add for battery health start
#ifdef GN_Q_BSP_BATTERY_HEALTH_SUPPORT
	ret = res_create_surface("charger/fhd_bat_overheat", &charger->battery_overheat);
    if (ret < 0) {
        LOGI("liujiang charger Cannot load batt_heat image\n");
        charger->battery_overheat = NULL;
    }
	ret = res_create_surface("charger/fhd_bat_cold", &charger->battery_cold);
    if (ret < 0) {
        LOGI("liujiang charger Cannot load batt_cold image\n");
        charger->battery_cold = NULL;
    }
#endif
//Gionee liujiang 2013-11-18 add for battery health end

    ev_sync_key_state(set_key_callback, charger);

#ifndef CHARGER_DISABLE_INIT_BLANK
    set_backlight(false);
    gr_fb_blank(true);
#endif

    charger->next_screen_transition = now - 1;
    charger->next_key_check = -1;
    charger->next_pwr_check = -1;
    reset_animation(charger->batt_anim);
    kick_animation(charger->batt_anim);

    event_loop(charger);

    return 0;
}
