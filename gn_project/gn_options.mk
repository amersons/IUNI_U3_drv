-include $(TOPDIR)gn_project/tools/gn_functions.mk

OUT_DIR:=$(TOPDIR)out

#############DRIVER MACRO DEFINE BEGIN ###################
#*********************************************************#
#*** LCD & LCD BL Driver macro define begin , yangyong ***#
#***                                                   ***#

# add for lm3630 backlight 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BACKLIGHT_LM3630_SUPPORT

# add for lcd normal porting 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_PORTING_SUPPORT

# add for lcd compatibility, for lk
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT

# default used the video mode, for lk 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_CMD_MODE_SUPPORT

# add for sharp r63417 panel, for lk
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_SHARP_R63417_PANEL_SUPPORT

# add for jdi r63417 panel, for lk
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_JDI_R63417_PANEL_SUPPORT 

# add for cabc function on/off
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_CABC_CHANGE_SUPPORT

#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_RESET_VOL_1V8_SUPPORT
#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 end

#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_TRULY_R63419_SUPPORT
#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 end

#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_JDI_R63419_SUPPORT
#Gionee xiangzhong 2014-04-10 add for modify reset vol to 1v8 end

#Gionee xiangzhong 2013-08-05 add for lcd compatibility begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_COMPATIBILITY_SUPPORT 
#Gionee xiangzhong 2013-08-05 add for lcd compatibility end

#Gionee xiangzhong 2013-07-31 add for lm3630 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BACKLIGHT_LM3630_SUPPORT
#Gionee xiangzhong 2013-07-31 add for lm3630 end

#Gionee xiangzhong 2014-04-10 add for sharp r63419 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_SHARP_R63419_SUPPORT
#Gionee xiangzhong 2014-04-10 add for sharp r63419 begin

#Gionee xiangzhong 2013-09-30 add for tps65132 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_TPS65132_SUPPORT
#Gionee xiangzhong 2013-09-30 add for tps65132 end

#Gionee xiangzhong 2013-09-30 add for reset lcd begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_RESET_SUPPORT
#Gionee xiangzhong 2013-09-30 add for reset lcd end

#Gionee xiangzhong 2013-08-27 add for charge logo begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_CHARGE_LOGO_SUPPORT
#Gionee xiangzhong 2013-08-27 add for charge logo end

#Gionee xiangzhong 2014-04 15 add for wqhd begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_WQHD_LCD_SUPPORT
#Gionee xiangzhong 2014-04 15 add for wqhd end
#Gionee xiangzhong 2014-04-30 add for iovcc control begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_IOVCC_CONTROL_SUPPORT
#Gionee xiangzhong 2014-04-30 add for iovcc control end

#Gionee xiangzhong 2014-05-12 add for lk dual dsi display begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_LK_DUAL_DSI_SUPPORT
#Gionee xiangzhong 2014-05-12 add for lk dual dsi display begin

#Gionee xiangzhong 2014-05-29 add for lk splash logo begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_LK_SPLASH_SUPPORT
#Gionee xiangzhong 2014-05-29 add for lk splash logo end

#Gionee xiangzhong 2014-06-23 add for truly video begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_TRULY_R63419_VIDEO_SUPPORT
#Gionee xiangzhong 2014-06-23 add for truly video end

#Gionee xiangzhong 2014-07-09 add for sharp video begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_SHARP_R63419_VIDEO_SUPPORT
#Gionee xiangzhong 2014-07-09 add for sharp video end

#Gionee guoshite 2014-09-15 add for TE analog signal begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LCD_TE_ANALOG_SUPPORT
#Gionee guoshite 2014-09-15 add for TE analog signal end

#Gionee chuqf 2014-07-03 for cdrom, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CDROM_SUPPORT
#Gionee chuqf 2014-07-03 for cdrom, end
#*********************************************************#
#xiaoqian, 20141021, add for common usage, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_SUPPORT
#xiaoqian, 20141021, add for common usage, end
#Gionee liushengbin 20131104 add for camera start
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_24M_MCLOCK_SUPPORT
#Gionee liushengbin 20131104 add for camera end
#Gionee taochao 2013-05-27, add for capture dmesg begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_CAPTURE_DMESG_SUPPORT
#Gionee taochao 2013-05-27, add for capture dmesg end
#Gionee taochao 2013-11-20, add for delete the download mode when device crash begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_NO_DOWNLOAD_MODE
#Gionee taochao 2013-11-20, add for delete the download mode when device crash end
#Gionee chenqiang 20130104,add for camera driver
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_SUPPORT
#Gionee yezg 2013-05-08 add for support samsung oled end
#Gionee wanglei, 2013-06-26, add for TP driver, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_TP_MELFAS_SUPPORT
#Gionee wanglei, 2013-06-26, add for TP driver, end
#Gionee zhaocq 20130516,add for headset switch driver begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_HEADSET_SUPPORT
#Gionee zhaocq 20130516,add for headset switch driver end
#Gionee wudp 2013-07-05 add for support poweroff chg begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM_POWEROFF_CHG_SUPPORT
#Gionee wudp 2013-07-05 add for support poweroff chg end
#Gionee wudp 2013-07-11 add for chg debug begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM_CHG_DEBUG_SUPPORT
#Gionee wudp 2013-07-11 add for  chg debug end
#Gionee liuxw 2013-07-16 add for gn_correlative_nv 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_FACTORY_NV_SUPPORT
#Gionee <zhangwu><2013-08-14> add for CR00854504 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_SCALADO_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_PICTURE_FRAME_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_FACE_BEAUTY_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_GESTURE_SHOT_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_LIVE_EFFECT_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_ARCSOFT_FEATURE_SUPPORT
#Gionee <zhangwu><2013-08-14> add for CR00854504 end
#xiaoqian, 20130905, add for supporting external sd card formatting, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_SD_FORMAT_SUPPORT
#xiaoqian, 20130905, add for supporting external sd card formatting, end
#Gionee Gionee wangym 2013-0918 add for audio recorder pause support begin 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_RECORDER_PAUSE_SUPPORT
#Gionee Gionee wangym 2013-0918 add for audio recorder pause support end
#Gionee huangzhuolin 2014-06-24 add for mbhc calibration begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_MBHC_CALIBRATION
#Gionee huangzhuolin 2014-06-24 add for mbhc calibration end
#Gionee weiwei 2013-11-11 modify for audio public macro begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_SUPPORT
#Gionee weiwei 2013-11-11 modify for audio public macro end
#Gionee weiwei 2013-08-19 add for mmitest mic begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_MMI_TEST_SUPPORT
#Gionee weiwei 2013-08-19 add for mmitest mic end
#Gionee weiwei 2013-09-25 modify for CR00898432 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_AUDIO_REMOVE_FASTMIXER_SUPPORT
#Gionee weiwei 2013-09-25 modify for CR00898432 end
#Gionee licz 20131022 add for vibrator begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_VIBRATOR_ERM_SUPPORT
#Gionee licz 20131022 add for vibrator end
#Gionee liujiang 2013-08-20 add for usb begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_USB_SUPPORT
#Gionee liujiang 2013-08-20 add for usb end
#Gionee liujiang 2013-09-22 add for isa1200 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_ISA1200_QPNPCLK_SUPPORT
#Gionee liujiang 2013-09-22 add for isa1200 end
#Gionee liujiang 2013-10-22 add for isa1200 level begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_ISA1200_LEVEL_SUPPORT
#Gionee liujiang 2013-10-22 add for isa1200 level end
#Gionee liujiang 2013-10-25 add for ps calib start
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PS_CALIB_SUPPORT
#Gionee liujiang 2013-10-25 add for ps calib end
#Gionee yezg 2014-3-13 modify for pmic tm_low_interrupt begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PMIC_DISABLE_LOW_TM_INTERRUPTS_SUPPORT 
#Gionee yezg 2014-3-13 modify for pmic tm_low_interrupt end
#Gionee wudp 2013-07-25 add for bms battery data begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM_BMS_BATTERY_DATA_SUPPORT
#Gionee wudp 2013-07-25 add for bms battery data end
#Gionee wudp 2013-07-30 add for non-standard charger begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM_NON_STANDARD_CHARGER_SUPPORT
#Gionee wudp 2013-07-30 add for non-standard charger end
#Gionee wudp 2013-08-21 add for PM8941 charger begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM8941_CHARGER_SUPPORT
#Gionee wudp 2013-08-21 add for PM8941 charger end
#Gionee luliya 2013-8-27 add for power key vibrator begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PWM_PWRKEY_VIBRATOR_SUPPORT
#Gionee luliya 2013-8-27 add for power key vibrator end
#Gionee luliya 2013-8-27 add for power key vibrator begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_CLK_PWRKEY_VIBRATOR_SUPPORT
#Gionee luliya 2013-8-27 add for power key vibrator end
#Gionee luliya 2013-8-29 add for power key check begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LK_PWRKEY_CHECK_SUPPORT
#Gionee luliya 2013-8-29 add for power key check end
#Gionee luliya 2014-2-26 add for copy sns.reg begin 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_COPY_SNS_REG_FILE
#Gionee luliya 2014-2-26 add for copy sns.reg end
#Gionee wudp 2013-09-10 add for charger voltage begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_CHARGE_VOLTAGE_SUPPORT
#Gionee wudp 2013-09-10 add for charger voltage end
#Gionee, chuqf, 2013-09-21, rtc alarm, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LK_RTC_ALARM_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_KERNEL_RTC_ALARM_SUPPORT
#Gionee, chuqf, 2013-09-21, rtc alarm, end
#Gionee wudp 2013-10-10 add for GBW8901 10K NTC begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BATTERY_10K_NTC_SUPPORT
#Gionee wudp 2013-10-10 add for GBW8901 10K NTC end
#Gionee wudp 2013-10-16 add for btc config begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BTC_CONFIG_SUPPORT
#Gionee wudp 2013-10-16 add for btc config end
#Gionee wudp 2013-10-26 add for PMIC OVP 9.5V begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_OVP_9P5V_SUPPORT
#Gionee wudp 2013-10-26 add for PMIC OVP 9.5V end
#Gionee wudp 2013-11-18 add for optimize fuel gauge under low temperature begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BAT_OPTIMIZE_LOW_TEMP_FUEL_GAUGE
#Gionee wudp 2013-11-18 add for optimize fuel gauge under low temperature end
#Gionee wudp 2013-12-05 add for bms debug log begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_PM_BMS_LOG_SUPPORT
#Gionee wudp 2013-12-05 add for bms debug log end
#Gionee wudp 2013-12-10 add for optimize soc begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_OPTIMIZE_SOC_SUPPORT
#Gionee wudp 2013-12-10 add for optimize soc end
#Gionee wudp 2013-12-14 add for save poweroff chg log begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_SAVE_POWEROFFCHG_LOG_SUPPORT
#Gionee wudp 2013-12-14 add for save poweroff chg log end
#Gionee chuqf 2014-3-8 add disable emmc hs400 mode begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_LK_DISABLE_EMMC_HS400
#Gionee chuqf 2014-3-8 add disable emmc hs400 mode end
#Gionee chuqf 2014-4-18 add enforce emmc timeout begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_ENFORCE_EMMC_TIMEOUT_SUPPORT
#Gionee chuqf 2014-4-18 add enforce emmc timeout end
#Gionee wudp 2014-05-04 add for optimize bms soc begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BMS_OPTIMIZE_SOC_SUPPORT
#Gionee wudp 2013-12-14 add for optimize bms soc end
#Gionee liuxw 2014-05-28 add for china ecc support 
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_CHINA_ECC_SUPPORT
#Gionee xiangzhong 2014-06-16 add for fastboot display begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_FASTBOOT_MODE_PROMPT_SUPPORT 
#Gionee xiangzhong 2014-06-16 add for fastboot display end
#Gionee <zhuangxiaojian> <2014-05-20> modify for CR01261494 begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_SCALADO_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_FACE_BEAUTY_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_AGEGENDER_DETECTION_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_GESTURE_SHOT_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_LIVE_EFFECT_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_ARCSOFT_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_NIGHT_SHOT_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_CAMERA_FEATURE_PICZOOM_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_SCALADO_FEATURE_SUPPORT
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_SCALADO_MIRROR_SUPPORT
#Gionee <zhuangxiaojian> <2014-05-20> modify for CR01261494 end
#Gionee wudp 2014-08-18 add for optimize phone restart soc error begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_BMS_OPTIMIZE_PHONE_RESTART_SOC_SUPPORT
#Gionee wudp 2013-08-18 add for optimize phone restart soc error end
#GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_HIFI_24BITS
#GIONEE guogy 2014-10-31 CR01406672 modify for 24bits HIFI end

#Gionee chuqf 2014-07-03 for online resize data image, begin
AUTO_ADD_GLOBAL_DEFINE_BY_NAME += GN_Q_BSP_ONLINE_RESIZE_DATA_SUPPORT
#Gionee chuqf 2014-07-03 for online resize data image, end

#############DRIVER MACRO DEFINE  END  ################### 

GIONEE_CDEFS := $(call gionee.custom.generate-macros)
export GIONEE_CDEFS
$(call gn_warning,"GIONEE_CDEFS:$(GIONEE_CDEFS)")
GIONEE_TMP_CFG := $(call gionee.custom.generate-tmp-cfg)

GIONEE_OPTIONS := $(strip $(foreach t,$(AUTO_ADD_GLOBAL_DEFINE_BY_NAME),$(if $(filter true,$($(t))),$(t))))
export GIONEE_OPTIONS
$(call gn_warning,"GIONEE_OPTIONS:$(GIONEE_OPTIONS)")

#############DRIVER MACRO DEFINE END ###################

#############APP MODULES DEFINE BEGIN ###################
GIONEE_MODULES := $(strip $(foreach t,$(AUTO_ADD_MODULES_BY_NAME),$(t)))
$(call gn_warning,"GIONEE_MODULES:$(GIONEE_MODULES)")

#############APP MODULES DEFINE END ###################

#############APP RO DEFINE BEGIN ###################

gn_ro_script_file="gn_project/tools/gn_ro_setting.sh"
$(shell echo " ">> ${gn_ro_script_file} )

GIONEE_TEST_VARS := $(foreach t,$(AUTO_ADD_RO_BY_NAME),$(shell echo "echo \"ro.gionee.$(call lc,$(t))=$($(t))\"" >> $(gn_ro_script_file))) 


#################CUST CUST CUST CUST CUST CUST CUST  END ############################

