# Copyright Statement:
#
#GIONEE Inc. (C) 2011. All rights reserved.
#


# This is a generic product that isn't specialized for a specific device.
# It includes the base Android platform.

PRODUCT_PACKAGES += Exchange

ifeq ($(strip $(GN_APP_APPMANAGER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_AppManager
endif

ifeq ($(strip $(GN_APP_COMPASS_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_Compass
endif
#Gionee liuran 20111119 add for qc compile start

#Gionee mengqj 20120508 add for CR00596583 start
#Gionee mengqj 20120802 modify for CR00663357 start
ifneq ($(filter yes%,$(GN_APP_LAUNCHER_PLUS_VERSION_SUPPORT)),)
PRODUCT_PACKAGES += GNLauncherPlus
else
PRODUCT_PACKAGES += Launcher2
endif
#Gionee mengqj 20120802 modify for CR00663357 end
#Gionee mengqj 20120508 add for CR00596583 end

ifeq ($(strip $(GN_APP_CALENDAR_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_Calendar
endif

#Gionee liuran 20111119 add for qc compile end

#Gionee qiuxd 2011119 add for add SoundRecorder start
#gionee lichao 2013-9-18 modify for CR00874667 begin
#ifeq ($(strip $(GN_SOUNDRECORDER_SUPPORT)), yes)
ifeq ($(strip $(GN_APK_SOUNDRECORDER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_SoundRecorder
else
  PRODUCT_PACKAGES += SoundRecorder	
endif
#gionee lichao 2013-9-18 modify for CR00874667 end
#Gionee qiuxd 2011119 add for add SoundRecorder end

#Gionee wangth 20120209 add for CR00515794 start
ifeq ($(strip $(GN_APP_CONTACTS_SUPPORT)), yes)
PRODUCT_PACKAGES += GN_Contacts
PRODUCT_PACKAGES += GN_ContactsProvider
endif
#Gionee wangth 20120209 add end

#Gionee fengjianyi 20111115 add for aora clock start
ifeq ($(strip $(GN_3RD_AORACLOCK_SUPPORT)), yes)
  PRODUCT_PACKAGES += AoraClock
endif
#Gionee fengjianyi 20111115 add for aora clock end

#Gionee fengjianyi 20111115 add for aora estore start
ifeq ($(strip $(GN_3RD_AORAESTORE_SUPPORT)), yes)
  PRODUCT_PACKAGES += AoraEStore
endif
#Gionee fengjianyi 20111115 add for aora estore end

#Gionee fengjianyi 20111115 add for aora eweather start
ifeq ($(strip $(GN_3RD_AORAEWEATHER_SUPPORT)), yes)
  PRODUCT_PACKAGES += AoraEWeather
endif
#Gionee fengjianyi 20111115 add for aora eweather end

#Gionee fengjianyi 20111115 add for aora pim start
ifeq ($(strip $(GN_3RD_AORAPIM_SUPPORT)), yes)
  PRODUCT_PACKAGES += AoraPIM
endif
#Gionee fengjianyi 20111115 add for aora pim end

#Gionee fengjianyi 20111115 add for sogou input start
ifeq ($(strip $(GN_3RD_SOGOUINPUT_SUPPORT)), yes)
  PRODUCT_PACKAGES += SogouInput
endif
#Gionee fengjianyi 20111115 add for sogou input end

#Gionee:xuwen 20110630 added for aora number area begin
ifeq ($(strip $(GN_3RD_AORANUMAREA_SUPPORT)), yes)
  PRODUCT_PACKAGES += AoraNumArea
endif
#Gionee:xuwen 20110630 added end

#Gionee xiaolin 20120211 add for CR00516269 start
ifeq ($(strip $(GN_MMI_TEST_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_MMITest
endif
#Gionee xiaolin 20120211 add for CR00516269 end

ifeq ($(strip $(GN_AUTO_MMI_SUPPORT)),yes)
   PRODUCT_PACKAGES += AutoMMI
endif

#Gionee liuwei 2013-09-10 added for CR00898722 start
ifeq ($(strip $(GN_APK_DOWNLOADPROVIDER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_DownloadProvider
  PRODUCT_PACKAGES += GN_DownloadProviderUi
endif
#Gionee liuwei 2013-09-10 added for CR00898722 end

#Gionee chencc 20120213 add for CR00516549 begin
ifeq ($(strip $(GN_APP_WIFITEST_SUPPORT)), yes)
  PRODUCT_PACKAGES += WifiTest
endif
#Gionee chencc 20120213 add for CR00516549 end

#Gionee huming 2012-07-27 add for CR00657653 begin
ifeq ($(strip $(GN_APP_THEME_SUPPORT)), yes)
    PRODUCT_PACKAGES += GN_Net_ThemeMgr
endif
#Gionee huming 2012-07-27 add for CR00657653 end

#Gionee fengjianyi 20120308 add for 3rd start
ifeq ($(strip $(GN_3RD_FRUITNINJA_SUPPORT)), yes)
  PRODUCT_PACKAGES += FruitNinJa
endif

ifeq ($(strip $(GN_3RD_BAIDUMAP_SUPPORT)), yes)
  PRODUCT_PACKAGES += BaiduMap
endif

#Gionee liuwei 2013-11-12 add for CR00943221 begin
ifeq ($(strip $(QCOM_FILEMANAGER_SUPPORT)), yes)
  PRODUCT_PACKAGES += FileExplorer
endif
#Gionee liuwei 2013-11-12 add for CR00943221 end

ifeq ($(strip $(GN_3RD_RENREN_SUPPORT)), yes)
  PRODUCT_PACKAGES += RenRen
endif

ifeq ($(strip $(GN_3RD_WEIBO_SUPPORT)), yes)
  PRODUCT_PACKAGES += WeiBo
endif

ifeq ($(strip $(GN_3RD_QQ_SUPPORT)), yes)
  PRODUCT_PACKAGES += QQ
endif

ifeq ($(strip $(GN_3RD_HIMARKET_SUPPORT)), yes)
  PRODUCT_PACKAGES += Himarket
endif

ifeq ($(strip $(GN_3RD_POWERWORD_SUPPORT)), yes)
  PRODUCT_PACKAGES += PowerWord
endif

ifeq ($(strip $(GN_3RD_KWPLAYER_SUPPORT)), yes)
  PRODUCT_PACKAGES += KWPlayer
endif
#Gionee fengjianyi 20120308 add for 3rd end

#Gionee zhangxx 20120718 add for CR00651382 start
ifeq ($(strip $(GN_APP_WIFI_DIRECT_SUPPORT)), yes)
  PRODUCT_PACKAGES += WifiDirect
endif
#Gionee zhangxx 20120718 add for CR00651382 end

#gionee dengll 20120307 add for sms registry begin
ifeq ($(strip $(GN_APP_SMSREGISTRY_SUPPORT)), yes)
  PRODUCT_PACKAGES += SmsReg
endif
#gionee dengll 20120307 add for sms registry end

#Gionee fengjianyi 20120406 add for 3rd start
ifeq ($(strip $(GN_3RD_BESTPAY_SUPPORT)), yes)
  PRODUCT_PACKAGES += BestPay
endif

ifeq ($(strip $(GN_3RD_EGAME_SUPPORT)), yes)
  PRODUCT_PACKAGES += eGame
endif

ifeq ($(strip $(GN_3RD_ICARTOON_SUPPORT)), yes)
  PRODUCT_PACKAGES += iCartoon
endif

ifeq ($(strip $(GN_3RD_IMUSIC_SUPPORT)), yes)
  PRODUCT_PACKAGES += iMusic
endif

ifeq ($(strip $(GN_3RD_QQBROWSER_SUPPORT)), yes)
  PRODUCT_PACKAGES += QQBrowser
endif
#Gionee fengjianyi 20120406 add for 3rd end

#Gionee fengjianyi 20120410 add for 3rd start
ifeq ($(strip $(GN_3RD_FISHGAME_SUPPORT)), yes)
  PRODUCT_PACKAGES += FishGame
endif

ifeq ($(strip $(GN_3RD_TYSX_SUPPORT)), yes)
  PRODUCT_PACKAGES += TYSX
endif
#Gionee fengjianyi 20120410 add for 3rd end

#Gionee zhang_xin 20120414 add for CR00572062 start
ifeq ($(strip $(GN_APP_BESTTONE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_BestTone
endif

ifeq ($(strip $(GN_APP_189MAILBOX_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_189MailBox
endif

ifeq ($(strip $(GN_APP_TIANYIREADING_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_TianYiReading
endif
#Gionee zhang_xin 20120414 add for CR00572062 end

#Gionee zhang_xin 20120510 add for CR00589118 start
ifeq ($(strip $(GN_APP_CUSTOMER_SERVICE_SUPPORT)),yes)
  PRODUCT_PACKAGES += GN_GioneeCustomerService
endif
#Gionee zhang_xin 20120510 add for CR00589118 end

#Gionee zhang_xin 20120510 add for CR00596723 start
ifeq ($(strip $(GN_3RD_VIAFLY_SUPPORT)), yes)
  PRODUCT_PACKAGES += ViaFly
endif
#Gionee zhang_xin 20120510 add for CR00596723 end

#Gionee lihq 20120511 add for CR00589116 start
ifeq ($(strip $(GN_APP_FIREWALL_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_FireWall
endif
#Gionee lihq 20120511 add for CR00589116 end

#Gionee qiuxd 2012-5-14 add for CR00568365 start
ifeq ($(strip $(GN_APP_CALENDAR_IMPORTER_SUPPORT)),yes)
  PRODUCT_PACKAGES += CalendarImporter
endif
#Gionee qiuxd 2012-5-14 add for CR00568365 end


#Gionee:huming 20110722 added for add Theme app
ifeq ($(strip $(GN_APP_THEME_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_ThemeMgr
endif
#Gionee:huming 20110722 added end

#Gionee: Houjie 20120220 add for C+W begin
ifeq ($(strip $(GN_TELECOM_CTWLAN_SUPPORT)), yes)
    PRODUCT_PACKAGES += CTWLan
endif
#Gionee: Houjie 20120220 add for C+W end

ifeq ($(strip $(GN_3RD_UCWEB_SUPPORT)),yes)
	PRODUCT_PACKAGES += UCWeb	
endif

ifeq ($(strip $(GN_3RD_BAIDUSEARCH_SUPPORT)),yes)
	PRODUCT_PACKAGES += BaiduSearch
endif

ifeq ($(strip $(GN_3RD_ESTOCK_SUPPORT)),yes)
	PRODUCT_PACKAGES += eStock
endif

ifeq ($(strip $(GN_3RD_DIANPING_SUPPORT)),yes)
	PRODUCT_PACKAGES += DianPing
endif

ifeq ($(strip $(GN_3RD_360BUY_SUPPORT)),yes)
	PRODUCT_PACKAGES += 360buy
endif

ifeq ($(strip $(GN_3RD_AORAESTORE_SUPPORT = yes)),yes)
	PRODUCT_PACKAGES += AoraEStore
endif

ifeq ($(strip $(GN_3RD_QUNAR_SUPPORT)),yes)
	PRODUCT_PACKAGES += Qunar
endif

ifeq ($(strip $(GN_3RD_SOHUNEWS_SUPPORT)),yes)
	PRODUCT_PACKAGES += SohuNews
endif

ifeq ($(strip $(GN_3RD_AORAEWEATHER_SUPPORT)),yes)
	PRODUCT_PACKAGES += AoraEWeather
endif

ifeq ($(strip $(GN_3RD_IREADER_SUPPORT)),yes)
	PRODUCT_PACKAGES += iReader
endif

ifeq ($(strip $(GN_3RD_JJLORD_SUPPORT)),yes)
	PRODUCT_PACKAGES += JJLord
endif

ifeq ($(strip $(GN_3RD_MAPBAR_SUPPORT)),yes)
	PRODUCT_PACKAGES += Mapbar
endif

ifeq ($(strip $(GN_3RD_QQWEIBO_SUPPORT)),yes)
	PRODUCT_PACKAGES += QQWeiBo
endif

ifeq ($(strip $(GN_3RD_WEIXIN_SUPPORT)),yes)
	PRODUCT_PACKAGES += WeiXin
endif

ifeq ($(strip $(GN_3RD_XUNFEIINPUT_SUPPORT)),yes)
	PRODUCT_PACKAGES += XunfeiInput
endif

ifeq ($(strip $(GN_3RD_KASCENDVIDEO_SUPPORT)),yes)
	PRODUCT_PACKAGES += KascendVideo
endif

ifeq ($(strip $(GN_3RD_GUOJIBIFENG_SUPPORT)),yes)
	PRODUCT_PACKAGES += GuoJiBiFeng
endif

#Gionee lihq 2012-07-25 add for CR00651972 start
ifeq ($(strip $(GN_APP_SETTINGS_SURPORT)),yes)
ifeq ($(strip $(GN_APP_SETTINGS_SCHEDULE_ON_OFF_AIRPLANE_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_SchAirPlane
endif

ifeq ($(strip $(GN_SIMMANAGERMENT_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_SimManagerment
endif

endif
#Gionee lihq 2012-07-25 add for CR00651972 end

#Gionee zengxuanhui 2012-08-15 add for audioprofile start
ifeq ($(strip $(GN_APP_AUDIO_PROFILE_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_AudioProfile
endif
#Gionee zengxuanhui 2012-08-15 add for audioprofile end

#Gionee lichao 2013-8-14 modify for CR00857555 begin
#ifeq ($(strip $(GN_APP_CALCULATOR_SUPPORT)),yes)
ifeq ($(strip $(GN_APK_CALCULATOR_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_Calculator
endif
ifeq ($(strip $(QCOM_CALCULATOR_SUPPORT)),yes)
	PRODUCT_PACKAGES += Calculator
endif
#Gionee lichao 2013-8-14 modify for CR00857555 end

#Gionee liuwei 2013-08-15 modify for CR00858037 begin
#Gionee yangxiong add for CR00632244 start
ifneq ($(filter yes%,$(GN_BACKUP_MANAGE_SUPPORT)),)
   PRODUCT_PACKAGES += GN_BackupRestore
   PRODUCT_PACKAGES += GN_BackupRestoreAssist
   PRODUCT_PACKAGES += backup_restore_apk_binder
   PRODUCT_PACKAGES += GN_MyAppWidget
endif
#Gionee yangxiong add for CR00632244 end
#Gionee liuwei 2013-08-15 modify for CR00858037 end

ifeq ($(strip $(GN_APP_FILE_MANAGER_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_FileManager
endif

ifeq ($(strip $(GN_SETTING_OTA_UPDATE_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_SettingUpdate
endif

# Gionee fengjianyi 2012-09-10 add for CR00687736 start
ifneq ($(filter yes%,$(GN_APK_VOICE_HELPER_SUPPORT)),)
  PRODUCT_PACKAGES += GN_VoiceHelper
ifeq ($(strip $(GN_3RD_SPEECHSERVICE_SUPPORT)), yes)
  PRODUCT_PACKAGES += speechService
endif
endif
# Gionee fengjianyi 2012-09-10 add for CR00687736 end

#Gionee: chenng 20121105 added for CR00724736 start
ifneq ($(filter yes%,$(GN_DYNAMIC_WEATHER_VERSION)),)
PRODUCT_PACKAGES += GN_DynamicWeather
endif
#Gionee: chenng 20121105 added for CR00724736 end

#Gionee liss 2012-08-09 add for CR00655183 start
ifeq ($(strip $(GN_APP_CHANGER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_Changer
endif
#Gionee liss 2012-08-09 add for CR00655183 end

#Gionee: maxw 20121022 modify for CR00717132 begin
#Gionee lichao 2013-8-14 modify for CR00857533 begin
#ifneq ($(filter yes%,$(GN_APP_GNSERVICE_SUPPORT)),)
ifneq ($(filter yes%,$(GN_APK_SERVICE_SUPPORT)),)
    PRODUCT_PACKAGES += GN_Service
endif
#Gionee lichao 2013-8-14 modify for CR00857533 end
#Gionee: mxw 20121022 modify for CR00717132 end

#Gionee: huyuke 20121019 modify for CR00705805 begin
ifeq ($(strip $(GN_APK_MUSIC_SUPPORT)), yes)
	  PRODUCT_PACKAGES += GN_Music
endif
#Gionee: huyuke 20121019 modify for CR00705805 begin

#Gionee xiongjiaxin 2012-8-30 add for CR00673317 start
ifneq ($(filter yes%,$(GN_APP_RINGTONE_SETTINGS_SUPPORT)),)
  PRODUCT_PACKAGES += GN_RingtoneSettings
endif
#Gionee xiongjiaxin 2012-8-30 add for CR00673317 end
#Gionee xuna 20130826 add for CR00873106 start
ifeq ($(strip $(GN_APK_RINGTONE_SUPPORT)),yes)
  PRODUCT_PACKAGES += GN_RingTone
endif
#Gionee xuna 20130826 add for CR00873106 end
#Gionee fangbin 20120809 added for CR00646833 GioneeNote start
ifneq ($(filter yes%,$(GN_APP_GIONEENOTE_SUPPORT)),)
  PRODUCT_PACKAGES += GN_Note
endif
#Gionee fangbin 20120809 added for CR00646833 GioneeNote end

#Gionee dengm 20120818 add for CR00672630 start
ifeq ($(strip $(GN_APP_FLASH_LIGHT_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_FlashLight
endif
#Gionee dengm 20120818 add for CR00672630 end

#Gionee longzp 2013.08.16 add for CR00858854 start
ifeq ($(strip $(GN_APK_GAMEHALL1_1_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_GameHall1_1
endif

ifeq ($(strip $(GN_APK_GOU_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_Gou
endif

ifeq ($(strip $(GN_APK_PAY_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_Pay
endif
ifeq ($(strip $(GN_APK_STATISTICS_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_Statistics
endif


#Gionee longzp 2013.08.16 add for CR00858854 end


#Gionee tangzepeng 2012-10-10 add for adding voice dailer begin
ifeq ($(strip $(GN_VOICE_DAILER_SUPPORT)), yes)
   PRODUCT_PACKAGES += VoiceDialer
endif
#Gionee tangzepeng 2012-10-10 add for adding voice dailer end

ifeq ($(strip $(GN_3RD_BAIDUMUSIC_SUPPORT)), yes)
   PRODUCT_PACKAGES += BaiduMusic
endif

#Gionee lichao 2013-8-14 modify for CR00857264 begin
#ifneq ($(filter yes%,$(GN_APP_ACCOUNT_SUPPORT)),)
ifneq ($(filter yes%,$(GN_APK_ACCOUNT_SUPPORT)),)
   PRODUCT_PACKAGES += GN_Account
endif
#Gionee lichao 2013-8-14 modify for CR00857264 end

ifeq ($(strip $(GN_3RD_DANGDANG_SUPPORT)), yes)
   PRODUCT_PACKAGES += DangDang
endif

ifeq ($(strip $(GN_3RD_FENGYUNTIANXIA_SUPPORT)), yes)
   PRODUCT_PACKAGES += Fengyuntianxia
endif

ifeq ($(strip $(GN_3RD_MITUHOTEL_SUPPORT)), yes)
   PRODUCT_PACKAGES += MituHotel
endif

ifeq ($(strip $(GN_3RD_QQSTEWARD_SUPPORT)), yes)
   PRODUCT_PACKAGES += QQSteward
endif

#Gionee lichao 2013-8-14 modify for CR00857548 begin
#ifneq ($(filter yes%,$(GN_APP_CUSTOMERSERVICE_SUPPORT)),)
#  PRODUCT_PACKAGES += CustomerService
ifneq ($(filter yes%,$(GN_APK_CUSTOMERSERVICE_SUPPORT)),)
  PRODUCT_PACKAGES += GN_CustomerService
endif
#Gionee lichao 2013-8-14 modify for CR00857548 end

ifeq ($(strip $(GN_APK_TELEPATH_SUPPORT)),yes)
  PRODUCT_PACKAGES += GN_Telepath
endif

ifneq ($(filter yes%,$(GN_APP_SYNCHRONIZER_SUPPORT)),)
  PRODUCT_PACKAGES += GN_Synchronizer
endif

ifeq ($(strip $(GN_APK_ANTISTOLEN_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_AntiStolen
endif

ifneq ($(filter yes%,$(GN_APK_GUIDE_SUPPORT)),)
  PRODUCT_PACKAGES += GN_BootGuide
endif

ifeq ($(strip $(GN_APK_SUPERGOU_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_SuperGou
endif

ifeq ($(strip $(GN_APK_SUPERGAMES_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_SuperGames
endif

ifeq ($(strip $(GN_APK_ONEKEY_CLEAN_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_OneClean
endif

ifeq ($(strip $(GN_3RD_BAIDULBS_SUPPORT)), yes)
   PRODUCT_PACKAGES += NetworkLocation
endif

#Gionee tianyr 20120724 add for CR00637533 start
ifeq ($(strip $(GN_APP_NUMAREA_SUPPORT)), gionee)
  PRODUCT_PACKAGES += NumArea
endif
#Gionee tianyr 20120724 add for CR00637533 end

#Gionee fangbin 20120525 added for CR00608714 GN_ZoomClipView start
ifeq ($(strip $(GN_APK_ZOOMCLIPVIEW_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_ZoomClipView
endif
#Gionee fangbin 20120525 added for CR00608714 GN_ZoomClipView end

#Gionee: xuhz 20121103 add for CR00686800 start
ifeq ($(strip $(GN_APK_WEIBOWIDGET_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_WeiboWidget
endif
#Gionee: xuhz 20121103 add for CR00686800 end

#Gionee huangyuncai 2013-2-28 add for start
ifeq ($(strip $(GN_APP_UPGRADE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_AppUpgrade
endif
#Gionee huangyuncai 2013-2-28 add for end

#Gionee huangyuncai 2013-2-28 add for start
ifeq ($(strip $(GN_APK_POWERSAVER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_PowerSaver
endif
#Gionee huangyuncai 2013-2-28 add for end

#Gionee huangyuncai 2013-2-28 add for start
ifeq ($(strip $(GN_3RD_MUSICSCENE_SUPPORT)), yes)
  PRODUCT_PACKAGES += NiTingMusicScene
endif
#Gionee huangyuncai 2013-2-28 add for end

#Gionee huangyuncai 2013-2-28 add for start
ifeq ($(strip $(GN_3RD_SOUNDHOUND_SUPPORT)), yes)
  PRODUCT_PACKAGES += SoundHound
endif
#Gionee huangyuncai 2013-2-28 add for end

#Gionee: zhanglina 2013 add for CR00686800 start
ifeq ($(strip $(GN_APP_OVERSEA_WEATHER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_Weather
endif
#Gionee: zhanglina 20121103 add for CR00686800 end

#Gionee: zhanglina 2013 add for CR00686800 start
ifeq ($(strip $(GN_3RD_WEIXIN_SUPPORT)), yes)
  PRODUCT_PACKAGES += WeiXin
endif
#Gionee: zhanglina 20121103 add for CR00686800 end

#Gionee: huangyuncai 20130309 add for CR00686800 start
ifeq ($(strip $(GN_PUSH_SUPPORT)), yes)
  PRODUCT_PACKAGES += GPE
endif
#Gionee: huangyuncai 20130309 add for CR00686800 end

#Gionee huangzy 20120824 add for CR00614805 start
ifeq ($(strip $(GN_NEW_FEATURE_THIRD_VERSION)), yes)
  PRODUCT_PACKAGES += GnHotlinesProvider
endif
#Gionee huangzy 20120824 add for CR00614805 end

#Gionee: 2012.11.26 cuijiuyu add for CR00740472 begin
ifeq ($(strip $(GN_OVERSEA_SALES_STATISTIC_SUPPORT)),yes)
  PRODUCT_PACKAGES += GN_SalesStatistic
endif
#Gionee: 2012.11.26 cuijiuyu add for CR00740472 end

ifeq ($(strip $(GN_3RD_AMAP_SUPPORT)), yes)
  PRODUCT_PACKAGES += AMAP
endif

ifeq ($(strip $(GN_3RD_AORAMARKET_SUPPORT)), yes)
  PRODUCT_PACKAGES += AORAMARKET
endif

ifeq ($(strip $(GN_3RD_BAIDUGROUPON_SUPPORT)), yes)
  PRODUCT_PACKAGES += BaiduGroupon
endif

ifeq ($(strip $(GN_3RD_BURNVEGETABLES_SUPPORT)), yes)
  PRODUCT_PACKAGES += BurnVegetables
endif

ifeq ($(strip $(GN_3RD_FISHINGJOY_SUPPORT)), yes)
  PRODUCT_PACKAGES += FishingJoy
endif

ifeq ($(strip $(GN_3RD_HGCJ_SUPPORT)), yes)
  PRODUCT_PACKAGES += hgcj
endif

ifeq ($(strip $(GN_3RD_IFLYIME_SUPPORT)), yes)
  PRODUCT_PACKAGES += iFlyIME
endif

ifeq ($(strip $(GN_3RD_SOHUNEWSCLIENT_SUPPORT)), yes)
  PRODUCT_PACKAGES += SohuNewsClient
endif

ifeq ($(strip $(GN_3RD_LETVCLIENT_SUPPORT)), yes)
  PRODUCT_PACKAGES += LetvClient
endif

ifeq ($(strip $(GN_3RD_STONETIMES_SUPPORT)), yes)
  PRODUCT_PACKAGES += stonetimes
endif

ifeq ($(strip $(GN_3RD_TAOBAOHOT_SUPPORT)), yes)
  PRODUCT_PACKAGES += TaoBaoHot
endif

ifeq ($(strip $(GN_3RD_TENCENTMOBILEMANAGER_SUPPORT)), yes)
  PRODUCT_PACKAGES += TencentMobileManager
endif

ifeq ($(strip $(GN_3RD_WPS_SUPPORT)), yes)
  PRODUCT_PACKAGES += wps
endif

ifeq ($(strip $(GN_3RD_YOUDAODICT_SUPPORT)), yes)
  PRODUCT_PACKAGES += youdaodict
endif

#Gionee jiantf 2013-08-13 add for CR00855664 start
ifeq ($(strip $(GN_APK_SOFTMANAGER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_SoftManager
endif
#Gionee jiantf 2013-08-13 add for CR00855664 end

#Gionee jiantf 2013-08-13 add for CR00855914 start
ifeq ($(strip $(GN_APK_ONECLEAN_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_OneClean
endif
#Gionee jiantf 2013-08-13 add for CR00855914 end
#Gionee jiantf 2013-08-15 add for CR00857949 start
ifeq ($(strip $(GN_APK_BROWSER_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_Browser
endif
#Gionee jiantf 2013-08-15 add for CR00857949 end

#Gionee lichao 2013-08-14 add for CR00857519 start
ifeq ($(strip $(GN_APK_BOOTGUIDE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_BootGuide
endif
#Gionee lichao 2013-08-14 add for CR00857519 end

#Gionee lichao 2013-08-14 add for CR00857548 start
ifeq ($(strip $(GN_APK_USERGUIDE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_UserGuide
endif
#Gionee lichao 2013-08-14 add for CR00857548 end

ifeq ($(strip $(GN_APK_PUSH_SUPPORT)),yes)
	PRODUCT_PACKAGES += GN_Push
endif

ifeq ($(strip $(GN_APP_AUDIO_PROFILE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_AudioProfile
endif

ifeq ($(strip $(GN_APK_SCHEDULE_ON_OFF_AIRPLANE_SUPPORT)), yes)
  PRODUCT_PACKAGES += GN_SchAirPlane
endif

# Gionee huangshuiqiang 2013-08-21 add for CR00867772 start
ifeq ("$(GN_APK_LOCKSCREENMANAGER_SUPPORT)","yes")
   PRODUCT_PACKAGES += GN_LockScreenManager
endif
# Gionee huangshuiqiang 2013-08-21 add for CR00867772 end

#Gionee zhonggj 20130826 add for CR00873835 start
ifeq ($(strip $(GN_APK_FLOATINGTOUCH_SUPPORT)),yes)
  PRODUCT_PACKAGES += GN_FloatingTouch
endif
#Gionee zhonggj 20130826 add for CR00873835 end

#Gionee lichao 2013-08-24 add for CR00871656 start
ifeq ($(strip $(GN_3RD_BAIDU_NETDISK_SUPPORT)), yes)
   PRODUCT_PACKAGES += Netdisk
endif
#Gionee zhonggj 20130909 add for cutrope games end

#Gionee zhangzs 20130828 add for CR00855351 begin
ifeq ($(strip $(GN_APK_CAMERA_SUPPORT)), yes)
   PRODUCT_PACKAGES += GN_Camera
endif
#Gionee zhangzs 20130828 add for CR00855351 end

#Gionee zhonggj 20130909 add for cutrope games start
ifeq ($(strip $(GN_3RD_CUTROPE_SUPPORT)), yes)
   PRODUCT_PACKAGES += CutRope
endif
# Gionee <daizm> <2013-10-11> add for CTA Permission begin
ifeq ($(strip $(GN_CTA_SEC_SUPPORT)), yes)
   PRODUCT_PACKAGES += Amigo_Account
   PRODUCT_PACKAGES += Amigo_Service
   PRODUCT_PACKAGES += Amigo_BackupRestore
   PRODUCT_PACKAGES += Amigo_BackupRestoreAssist
   PRODUCT_PACKAGES += Amigo_SoftManager
   PRODUCT_PACKAGES += Amigo_AntiStolen
   PRODUCT_PACKAGES += Amigo_OneClean
   PRODUCT_PACKAGES += Amigo_Push
   PRODUCT_PACKAGES += QQSteward
   PRODUCT_PACKAGES += GN_Netdisk  
endif
# Gionee <daizm> <2013-10-11> add for CTA Permission end

#Gionee wangzhen 2014-05-26 add for CTA wifi bt test begin
ifeq ($(strip $(GN_CTA_TESTAPK_SUPPORT)), yes)
   PRODUCT_PACKAGES += WifiTx
   PRODUCT_PACKAGES += BtTx
endif
#Gionee wangzhen 2014-05-26 add for CTA wifi bt test begin

#gionee, chuqf, for online resize data image, begin
ifeq ($(strip $(GN_Q_BSP_ONLINE_RESIZE_DATA_SUPPORT)), yes)
   PRODUCT_PACKAGES += ext4_resize
   PRODUCT_PACKAGES += resize2fs
endif
#gionee, chuqf, for online resize data image, end
