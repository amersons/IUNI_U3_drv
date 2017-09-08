#
# Copyright (C) 2007 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

######################################################################
# This is a do-nothing template file.  To use it, copy it to a file
# named "buildspec.mk" in the root directory, and uncomment or change
# the variables necessary for your desired configuration.  The file
# "buildspec.mk" should never be checked in to source control.
######################################################################

# Choose a product to build for.  Look in the products directory for ones
# that work.
TARGET_PRODUCT:=msm8974
ifndef TARGET_PRODUCT
#TARGET_PRODUCT:=generic
endif

# Choose a variant to build.  If you don't pick one, the default is eng.
# User is what we ship.  Userdebug is that, with a few flags turned on
# for debugging.  Eng has lots of extra tools for development.
ifndef TARGET_BUILD_VARIANT
#TARGET_BUILD_VARIANT:=user
#TARGET_BUILD_VARIANT:=userdebug
TARGET_BUILD_VARIANT:=eng
endif

# Choose additional targets to always install, even when building
# minimal targets like "make droid".  This takes simple target names
# like "Browser" or "MyApp", the names used by LOCAL_MODULE or
# LOCAL_PACKAGE_NAME.  Modules listed here will always be installed in
# /system, even if they'd usually go in /data.
ifndef CUSTOM_MODULES
#CUSTOM_MODULES:=
endif

# Set this to debug or release if you care.  Otherwise, it defaults to release.
ifndef TARGET_BUILD_TYPE
TARGET_BUILD_TYPE:=release
endif

# Uncomment this if you want the host tools built in debug mode.  Otherwise
# it defaults to release.
ifndef HOST_BUILD_TYPE
#HOST_BUILD_TYPE:=debug
endif

# Turn on debugging for selected modules.  If DEBUG_MODULE_<module-name> is set
# to a non-empty value, the appropriate HOST_/TARGET_CUSTOM_DEBUG_CFLAGS
# will be added to LOCAL_CFLAGS when building the module.
#DEBUG_MODULE_ModuleName:=true

# Specify an alternative tool chain prefix if needed.
#TARGET_TOOLS_PREFIX:=

# Specify the extra CFLAGS to use when building a module whose
# DEBUG_MODULE_ variable is set.  Host and device flags are handled
# separately.
#HOST_CUSTOM_DEBUG_CFLAGS:=
#TARGET_CUSTOM_DEBUG_CFLAGS:=

# Choose additional locales, like "en_US" or "it_IT", to add to any
# built product.  Any locales that appear in CUSTOM_LOCALES but not in
# the locale list for the selected product will be added to the end
# of PRODUCT_LOCALES.
ifndef CUSTOM_LOCALES
#CUSTOM_LOCALES:=
endif

# If you have a special place to put your ouput files, set this, otherwise
# it goes to <build-root>/out
#OUT_DIR:=/tmp/stuff

# If you want to always set certain system properties, add them to this list.
# E.g., "ADDITIONAL_BUILD_PROPERTIES += ro.prop1=5 prop2=value"
# This mechanism does not currently support values containing spaces.
#ADDITIONAL_BUILD_PROPERTIES +=

# If you want to reduce the system.img size by several meg, and are willing to
# lose access to CJK (and other) character sets, define NO_FALLBACK_FONT:=true
ifndef NO_FALLBACK_FONT
#NO_FALLBACK_FONT:=true
endif

# To enable instrumentation in webcore based apps like gmail and
# the browser, define WEBCORE_INSTRUMENTATION:=true
ifndef WEBCORE_INSTRUMENTATION
#WEBCORE_INSTRUMENTATION:=true
endif

# To disable SVG in webcore define ENABLE_SVG:=false
ifndef ENABLE_SVG
#ENABLE_SVG:=false
endif

# when the build system changes such that this file must be updated, this
# variable will be changed.  After you have modified this file with the new
# changes (see buildspec.mk.default), update this to the new value from
# buildspec.mk.default.
BUILD_ENV_SEQUENCE_NUMBER := 10

############# DRIVER MACRO DEFINE BEGIN #########
#Gionee xiaoqian 2014-10-21 add for commcon usage, begin
GN_Q_BSP_SUPPORT = y
#Gionee xiaoqian 2014-10-21 add for common usage, end
#Gionee yezg 2013-05-08 add for support samsung oled begin
GN_Q_BSP_LCD_SAMSUNG_S6E8AA0X01_720p_SUPPORT= y
#Gionee yezg 2013-05-08 add for support samsung oled end
#Gionee chenqiang 20130104,add for camera driver
GN_CAMERA_SUPPORT = y
#Gionee chenqiang 20130812,add for camera driver
GN_CAMERA_24M_MCLOCK_SUPPORT = y
#Gionee taochao 2013-05-27, add for capture dmesg begin
GN_Q_BSP_CAPTURE_DMESG_SUPPORT = n
#Gionee taochao 2013-05-27, add for capture dmesg end
#Gionee taochao 2013-10-14, add for sync mdss vsync and release begin
GN_Q_BSP_SYNC_MDSS_VSYNC = y
#Gionee taochao 2013-10-14, add for sync mdss vsync and release end
#Gionee taochao 2013-10-19, add for cpufreq limit begin
GN_Q_BSP_CPUFREQ_LIMIT = y
#Gionee taochao 2013-10-19, add for cpufreq limit end
#Gionee taochao 2013-10-19, add for cpufreq smart up begin
GN_Q_BSP_CPUFREQ_SMART_UP = y
#Gionee taochao 2013-10-19, add for cpufreq smart up end
#Gionee taochao 2013-10-19, add for cpufreq step up begin
GN_Q_BSP_CPUFREQ_STEP_UP = y
#Gionee taochao 2013-10-19, add for cpufreq step up end
#Gionee taochao 2013-10-19, add for limit the cpufreq while input event begin
GN_Q_BSP_INPUT_EVENT_LIMIT_CPUFREQ = y
#Gionee taochao 2013-10-19, add for limit the cpufreq while input event end
#Gionee taochao 2014-2-19, add for modify the cpu info begin
GN_Q_BSP_CPU_INFO_MODIFY = n
#Gionee taochao 2014-2-19, add for modify the cpu info end
#Gionee wanglei, 2013-06-26, add for TP driver, begin
GN_Q_BSP_TP_SYNAPTICS_SUPPORT = y
#Gionee wanglei, 2013-06-26, add for TP driver, end
#Gionee wanglei, 2013-10-15, add for Color Temperature adjust LCD, begin
GN_Q_BSP_SENSOR_ADJUST_LCD_SUPPORT = yes
#Gionee wanglei, 2013-10-15, add for Color Temperature adjust LCD, end
#Gionee wanglei, 2013-09-23, add for device check, begin
GN_DEVICE_TYPE_CHECK = y
#Gionee wanglei, 2013-09-23, add for device check, end
#Gionee zhaocq 20130516,add for headset switch driver begin
GN_Q_BSP_AUDIO_HEADSET_SUPPORT = y
#Gionee zhaocq 20130516,add for headset switch driver end
#Gionee wudp 2013-07-05 add for support poweroff chg begin
GN_Q_BSP_PM_POWEROFF_CHG_SUPPORT= y
#Gionee wudp 2013-07-05 add for support poweroff chg end
#Gionee wudp 2013-07-11 add for chg debug begin
GN_Q_BSP_PM_CHG_DEBUG_SUPPORT= y
#Gionee wudp 2013-07-11 add for  chg debug end
#Gionee wudp 2013-12-05 add for bms debug log begin
GN_Q_BSP_PM_BMS_LOG_SUPPORT = y
#Gionee wudp 2013-12-05 add for bms debug log end
#Gionee liuxw 2013-07-16 add for gn_correlative_nv 
GN_Q_BSP_FACTORY_NV_SUPPORT = y
#Gionee zhaocq 20130718,add for es325 driver begin
GN_Q_BSP_AUDIO_ES325_SUPPORT = y
#Gionee zhaocq 20130516,add for es325 driver end
#Gionee huangzhuolin 20131021,add for recording pause feature begin
GN_Q_BSP_RECORD_PAUSE_SUPPORT = y
#Gionee huangzhuolin 20131021,add for recording pause feature end
#Gionee wangzhen 2013-07-22 add for BCM20793 NFC driver begin
GN_Q_BSP_NFC_BCM20793_SUPPORT = y
#Gionee wangzhen 2013-07-22 add for BCM20793 NFC driver end
#Gionee wangzhen 2013-09-02 add for Wifi MAC address begin
GN_Q_BSP_WIFI_MAC_ADDR_SUPPORT = y
#Gionee wangzhen 2013-09-02 add for Wifi MAC address end
#Gionee wangzhen 2013-09-19 add for Recovery begin
GN_Q_BSP_RECOVERY_SUPPORT = y
#Gionee wangzhen 2013-09-19 add for Recovery end
#Gionee zhaocq 20130723,add for FM speak <--> headset begin
GN_Q_BSP_AUDIO_FM_SUPPORT = y
#Gionee zhaocq 20130723,add for FM speak <--> headset end
#Gionee wudp 2013-07-30 add for non-standard charger begin
GN_Q_BSP_PM_NON_STANDARD_CHARGER_SUPPORT = y
#Gionee wudp 2013-07-30 add for non-standard charger end
#Gionee xiangzhong 2013-07-31 add for lm3630 begin
GN_Q_BSP_BACKLIGHT_LM3630_SUPPORT = y
#Gionee xiangzhong 2013-07-31 add for lm3630 end
#Gionee xiangzhong 2013-08-05 add for lcd compatibility begin
GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT = y
#Gionee xiangzhong 2013-08-05 add for lcd compatibility end
#Gionee xiangzhong 2013-08-05 add for tianma truly jdi lcd begin
GN_Q_BSP_LCD_TRULY_R63419_SUPPORT = y
GN_Q_BSP_LCD_JDI_R63419_SUPPORT = y
GN_Q_BSP_LCD_SHARP_R63419_SUPPORT = y
#Gionee xiangzhong 2013-08-05 add for tianma truly jdi lcd end
#Gionee xiangzhong 2013-08-13 add for gionee logo begin
GN_Q_BSP_LCD_GIONEE_LOGO_SUPPORT = y
#Gionee xiangzhong 2013-08-13 add for gionee logo end
#Gionee huangzhuolin 2014-06-24 add for mbhc calibration begin
GN_Q_BSP_AUDIO_MBHC_CALIBRATION = y
#Gionee huangzhuolin 2014-06-24 add for mbhc calibration end
#Gionee weiwei 2013-08-19 add for mmitest mic begin
GN_Q_BSP_AUDIO_MMI_TEST_SUPPORT = y
#Gionee weiwei 2013-08-19 add for mmitest mic end
#Gionee weiwei 2013-11-11 add for audio public macro begin
GN_Q_BSP_AUDIO_SUPPORT = y
#Gionee weiwei 2013-11-11 add for audio public macro end
#Gionee weiwei 2013-09-25 modify for CR00898432 begin
GN_Q_BSP_AUDIO_REMOVE_FASTMIXER_SUPPORT = y
#Gionee weiwei 2013-09-25 modify for CR00898432 end
#Gionee liujiang 2013-08-20 add for usb begin
GN_Q_BSP_USB_SUPPORT = n
#Gionee liujiang 2013-08-20 add for usb end
#Gionee liujiang 2013-09-22 add for isa1200 begin
GN_Q_BSP_ISA1200_QPNPCLK_SUPPORT = y
#Gionee liujiang 2013-09-22 add for isa1200 end
#Gionee licz modify 2014-09-18 begin
GN_Q_BSP_AKM8963_PDC_SUPPORT = no
#Gionee licz modify 2014-09-18 end
#Gionee liujiang 2013-10-22 add for isa1200 level begin
GN_Q_BSP_ISA1200_LEVEL_SUPPORT = y
#Gionee liujiang 2013-10-22 add for isa1200 level end
#Gionee liujiang 2013-10-25 add for ps calib start
GN_Q_BSP_PS_CALIB_SUPPORT = y
#Gionee liujiang 2013-10-25 add for ps calib end
#Gionee liujiang 2013-12-27 add for amigo poweroff ui start
GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE = iuni
#Gionee liujiang 2013-12-27 add for amigo poweroff ui end
#Gionee wudp 2013-08-21 add for PM8941 charger begin
GN_Q_BSP_PM8941_CHARGER_SUPPORT = y
#Gionee wudp 2013-08-21 add for PM8941 charger end
#Gionee xiangzhong 2013-08-27 add for charge logo begin
GN_Q_BSP_LCD_CHARGE_LOGO_SUPPORT = y
#Gionee xiangzhong 2013-08-27 add for charge logo end
#Gionee luliya 2013-8-27 add for power key vibrator begin
GN_Q_BSP_PWM_PWRKEY_VIBRATOR_SUPPORT = n
#Gionee luliya 2013-8-27 add for power key vibrator end
#Gionee luliya 2013-8-27 add for power key vibrator begin
GN_Q_BSP_CLK_PWRKEY_VIBRATOR_SUPPORT = y
#Gionee luliya 2013-8-27 add for power key vibrator end
#Gionee luliya 2013-8-29 add for power key check begin
GN_Q_BSP_LK_PWRKEY_CHECK_SUPPORT = y
#Gionee luliya 2013-8-29 add for power key check end
#Gionee luliya 2014-2-26 add for copy sns.reg begin 
GN_Q_BSP_COPY_SNS_REG_FILE = y
#Gionee luliya 2014-2-26 add for copy sns.reg end
#Gionee wudp 2013-09-10 add for charger voltage begin
GN_Q_BSP_CHARGE_VOLTAGE_SUPPORT = y
#Gionee wudp 2013-09-10 add for charger voltage end
#Gionee, chuqf, 2013-09-21, rtc alarm, begin
GN_Q_BSP_LK_RTC_ALARM_SUPPORT = y
GN_Q_BSP_KERNEL_RTC_ALARM_SUPPORT = y
#Gionee, chuqf, 2013-09-21, rtc alarm, end
#Gionee wudp 2013-07-25 add for bms battery data begin
GN_Q_BSP_PM_BMS_BATTERY_DATA_SUPPORT = y
#Gionee wudp 2013-07-25 add for bms battery data end
#Gionee xiangzhong 2013-09-30 add for tps65132 begin
GN_Q_BSP_LCD_TPS65132_SUPPORT = y
#Gionee xiangzhong 2013-09-30 add for tps65132 end
#Gionee wudp 2013-10-10 add for GBW8901 10K NTC begin
GN_Q_BSP_BATTERY_10K_NTC_SUPPORT = y
#Gionee wudp 2013-10-10 add for GBW8901 10K NTC end
#Gionee wudp 2013-10-16 add for btc config begin
GN_Q_BSP_BTC_CONFIG_SUPPORT = y
#Gionee wudp 2013-10-16 add for btc config end
#Gionee wudp 2013-10-26 add for PMIC OVP 9.5V begin
GN_Q_BSP_OVP_9P5V_SUPPORT = y
#Gionee wudp 2013-10-26 add for PMIC OVP 9.5V end
#Gionee zhengwei 2013-11-01 add for disable wled begin
GN_Q_BSP_DISABLE_WLED_SUPPORT = y
#Gionee zhengwei 2013-11-01 add for disable wled end
#Gionee zhengwei 2013-11-01 add for gpio52 begin
GN_Q_BSP_CONFIG_GPIO52_SUPPORT = y
#Gionee zhengwei 2013-11-01 add for gpio52 end
#Gionee xiangzhong 2013-11-14 add for change cabc mode begin
GN_Q_BSP_LCD_CABC_CHANGE_SUPPORT = y
#Gionee xiangzhong 2013-11-14 add for change cabc mode end
#Gionee yezg 2013-11-15 add for enable write property for hotplug_disabled begin
GN_Q_BSP_CPU_WR_HOTPLUG_DISABLED_SUPPORT = y
#Gionee yezg 2013-11-15 add for enable write property for hotplug_disabled end
#Gionee xiangzhong 2013-11-15 add for recovery display begin
GN_Q_BSP_LCD_RECOVERY_DISPLAY_SUPPORT = y
#Gionee xiangzhong 2013-11-15 add for recovery display end
#Gionee wudp 2013-11-18 add for optimize fuel gauge under low temperature begin
GN_Q_BSP_BAT_OPTIMIZE_LOW_TEMP_FUEL_GAUGE = y
#Gionee wudp 2013-11-18 add for optimize fuel gauge under low temperature end
#Gionee liuxw 2013-11-18 add for china ecc support
GN_Q_BSP_CHINA_ECC_SUPPORT = y
#Gionee, chuqf, 2013-11-30, pwr+vol_up+vol_down to emergency dl mode, begin
GN_Q_BSP_LK_EMERGENCY_DL_MODE_SUPPORT = y
#Gionee, chuqf, 2013-11-30, pwr+vol_up+vol_down to emergency dl mode, end
#Gionee, chuqf, 2013-11-30, to support ums while com.tencent.mm is on, begin
GN_Q_BSP_SUPPORT_UMS_MOVE_MNT = y
#Gionee, chuqf, 2013-11-30, to support ums while com.tencent.mm is on, end
#Gionee xiangzhong 2013-12-14 add for bring up begin
GN_Q_BSP_BRINGUP_SUPPORT = y
#Gionee xiangzhong 2013-12-14 add for bring up end
#Gionee xiangzhong 2013-12-16 add for lcd reset begin
GN_Q_BSP_LCD_RESET_SUPPORT = y
#Gionee xiangzhong 2013-12-16 add for lcd reset end
#Gionee wudp 2013-12-10 add for optimize soc begin
GN_Q_BSP_OPTIMIZE_SOC_SUPPORT = y
#Gionee wudp 2013-12-10 add for optimize soc end
#Gionee wudp 2013-12-14 add for save poweroff chg log begin
GN_Q_BSP_SAVE_POWEROFFCHG_LOG_SUPPORT = y
#Gionee wudp 2013-12-14 add for save poweroff chg log end
#Gionee xiangzhong 2014-01-16 add for msm8974ac display begin
GN_Q_BSP_LCD_MSM8974AC_SUPPORT = y
#Gionee xiangzhong 2014-01-16 add for msm8974ac display end
#Gionee xiangzhong 2014-02-18 add for tianma r63421 begin
GN_Q_BSP_LCD_TIANMA_R63421_SUPPORT = y
#Gionee xiangzhong 2014-02-18 add for tianma r63421 end
#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 begin
GN_Q_BSP_LCD_RESET_VOL_1V8_SUPPORT = y
#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 end
#Gionee xiangzhong 2014-04-15 add for wqhd begin
GN_Q_BSP_WQHD_LCD_SUPPORT = y
#Gionee xiangzhong 2014-04-15 add for wqhd end
#Gionee yezg 2014-3-13 modify for pmic tm_low_interrupt begin
GN_Q_BSP_PMIC_DISABLE_LOW_TM_INTERRUPTS_SUPPORT = y
#Gionee yezg 2014-3-13 modify for pmic tm_low_interrupt end
#Gionee xiangzhong 2014-05-05 add for iovcc control begin
GN_Q_BSP_LCD_IOVCC_CONTROL_SUPPORT = y
#Gionee xiangzhong 2014-05-05 add for iovcc control end
#Gionee wudp 2014-05-04 add for optimize bms soc begin
GN_Q_BSP_BMS_OPTIMIZE_SOC_SUPPORT = y
#Gionee wudp 2013-12-14 add for optimize bms soc end
#Gionee xiangzhong 2014-05-12 add for lk dual dsi display begin
GN_Q_BSP_LCD_LK_DUAL_DSI_SUPPORT = y
#Gionee xiangzhong 2014-05-12 add for lk dual dsi display begin
#Gionee xiangzhong 2014-06-16 add for fastboot display begin
GN_Q_BSP_FASTBOOT_MODE_PROMPT_SUPPORT = y
#Gionee xiangzhong 2014-06-16 add for fastboot display end
#Gionee xiangzhong 2014-05-29 add for lk logo bigin
GN_Q_BSP_LCD_LK_SPLASH_SUPPORT = y
BOOT_LOGO = wqhd
#Gionee xiangzhong 2014-05-29 add for lk logo end
#Gionee chuqf 2014-07-03 for online resize data image, begin
GN_Q_BSP_ONLINE_RESIZE_DATA_SUPPORT=yes
#Gionee chuqf 2014-07-03 for online resize data image, end

#Gionee liuxw 2014-06-07 add for radio config begin
GN_RADIO_DEFAULT_NETWORK = 20
GN_RADIO_MULTISIM_CONFIG = dsds
#GN_RADIO_RESTORE_MODE_PREF_ENABLE = 1
#Gionee liuxw 2014-06-07 add for radio config end

#GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin
GN_Q_BSP_HIFI_24BITS=yes
#GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end
############ DRIVER MACRO DEFINE  END  ###################

############# CUST BEGIN ##################################
GN_EXTERNAL_VERNUMBER = SV1.0
GN_EXTERNAL_MODEL = IUNI U3 mini
GN_BUILD_DISPLAY_ID = SV1.0
GN_PRODUCT_MODEL = IUNI U3 mini
GN_PRODUCT_BRAND = IUNI
GN_PRODUCT_NAME = IUNI
GN_TARGET_DEVICE = IUNI
GN_PRODUCT_MANUFACTURER = IUNI
GN_RO_GN_GNVERNUMBERREL = 01
GIONEEPROJECTID=NBL8905A

#Gionee add for QCOM APP
QCOM_SNAPDRAGONSDKTEST_SUPPORT = no
QCOM_FACTORYKIT_SUPPORT = no
#QCOM_VOICEDIAlER_SUPPORT = no
QCOM_CNESETTINGS_SUPPORT = no
QCOM_EMBMSTESTAPP_SUPPORT = no
#QCOM_FEATURE_SETTINGS_SUPPORT = no
QCOM_QVTESTER04_SUPPORT = no
#QRDExt_ProfileMgr = no
#QCOM_DATAMONITOR_SUPPORT = no
#Gionee liuwei 2013-11-18 modify for CR00943221 begin
QCOM_FILEMANAGER_SUPPORT = yes
#Gionee liuwei 2013-11-18 modify for CR00943221 end
QCOM_QUICKSEARCHBOX_SUPPORT = no
#QCOM_WOREAD_SUPPORT = no
QCOM_SSE_SAMPLE_TEST_SUPPORT = no
#QCOM_WOWALLPAPER_SUPPORT = no
QCOM_QSENSORTEST_SUPPORT = no
QCOM_MULTIPLEPDPTEST_SUPPORT = no
QCOM_BTTESTAPP_SUPPORT = no
QCOM_DIGITALPENSETTING_SUPPORT = no
QCOM_IMSPRESENCE_SUPPORT = no

#Logkit qlogcat ODLT for qualcomm debug tools
#QCOM_HY11_APPLICATION = Logkit qlogcat ODLT SecureTouchPerf MSAPU QcomIZat Trepn
QCOM_HY11_APPLICATION = Logkit SystemAgent

#OPTR:ct cta cu default
QCOM_OPTR_SPEC_DEF = cta

GN_KERNEL_TMP_FILE = gn_project/.drv_feature
GN_KCONFIG_TMP_FILE = gn_project/.cfg_tmp
export GN_KERNEL_TMP_FILE
export GN_KCONFIG_TMP_FILE
GN_KERNEL_CFG_FILE = kernel/arch/arm/configs/msm7627a-perf_defconfig
GN_BOOTABLE_CFG_FILE = bootable/bootloader/lk/makefile
GN_BOOTABLE_TMP_FILE = gn_project/.bootable_feature

#Gionee:niejn 20130924 add for CR00907351 begin
GN_PRODUCT_LOCALES = zh_CN en_US xxhdpi xhdpi hdpi mdpi
#Gionee:niejn 20130924 add for CR00907351 end

#GN_PROJECT_PACKAGES_NAME = packages_qc_ics_qrd8625

#PLATFORM:QCOM MTK OTHER
GN_PRODUCT_PLATFORM = QCOM

#Gionee <LogKit> <wangmeng> <20140408> modify for CR01173526.begin
GN_QC_LOGKIT_QUIET_SUPPORT = yes
#Gionee <LogKit> <wangmeng> <20140408> modify for CR01173526.end

################# CUST END   ###############################

################################# APP BEGIN  ###############################
GN_DEFAULT_INPUT_METHOD = com.android.inputmethod.pinyin.PinyinIME
GN_MMI_TEST_SUPPORT = yes
GN_MMI_KEYTEST_APP = no
GN_MMI_KEYTEST_MENU = yes
GN_MMI_MIC2 = no
GN_MMI_RECEIVER2 = yes
GN_MMI_TP_CROSS = yes
GN_CTA_FILEMANAGER_SUPPORT = yes

GN_APK_DOWNLOADPROVIDER_SUPPORT = yes
GN_APK_VIDEOEDITOR_SUPPORT = no
GN_APK_VOICEDIALER_SUPPORT = no
GN_JANPANESEINPUTMETHOD_SUPPORT = no
#Gionee add by jiantf for CR01072835 begin
GN_PHONE_NETWORKMODE = 4
#Gionee add by jiantf for CR01072835 end

#Gionee bug jiantf 2014-3-18 add for CR01099667 begin
GN_QMI_RIL_SYS_PROP_RAT_OPTION = combine
#Gionee bug jiantf 2014-3-18 add for CR01099667 end

#Gionee wangzhen 2014-05-26 add for CTA wifi bt test begin
GN_CTA_TESTAPK_SUPPORT = yes
#Gionee wangzhen 2014-05-26 add for CTA wifi bt test end

#Gionee <bug> <jiantf> <2014-3-18> add for CR01099667 begin
GN_QMI_RIL_SYS_PROP_RAT_OPTION = combine
#Gionee <bug> <jiantf> <2014-3-18> add for CR01099667 end
################################# APP END   ################################

################################# 3RD BEGIN   ##############################
################################# 3RD END   ################################

################################# 3RD RECOVER START ########################
GN_3RD_RECOVER_FROM_SDCARD = n
GN_3RD_RECOVER_FROM_RAM = n
################################# 3RD RECOVER END #########################

#Gionee <qudw> 20131127 modify to remove original apps
GN_APP_ORIGINAL_APPS_REMOVE_LIST = VideoEditor BTTestApp CNESettings EmbmsTestApp SecureMsmSample FactoryKit FM msapu MultiplePdpTest NfcDefaultApps QSensorTest QVTester SecureTouchPerf ODLT WfdClient CameraHawk Perfect365 WhipForPhone VoiceDialer HomeLocation QRDFeatureSettings QualcommSettings qlogcat DigitalPenSettings PenPairingApp UltrasoundSettings extendedoffscreen QtiBackupAgent
# Gionee <daizm> <2013-10-11> add for CTA Permission begin
GN_CTA_SEC_SUPPORT=yes
GN_CTA_QQ_STEWARD_SUPPORT=no
# Gionee <daizm> <2013-10-11> add for CTA Permission end
