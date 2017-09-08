#!/usr/bin/perl
# Copyright Statement:
if(defined($ENV{GN_EXTERNAL_VERNUMBER})){
    #GIONEE: luohui 2013-02-03 modify for CR00771002 Oversea start->
    if (exists $ENV{GN_OVERSEA_PRODUCT} && $ENV{GN_OVERSEA_PRODUCT} eq "yes") {
        if (exists $ENV{GN_OVERSEA_FAKE_EXTERNAL_VERNUMBER} && $ENV{GN_OVERSEA_FAKE_EXTERNAL_VERNUMBER} ne "") {
            print "ro.gn.extvernumber=$ENV{GN_OVERSEA_FAKE_EXTERNAL_VERNUMBER}\n";
        } else {
            print "ro.gn.extvernumber=$ENV{GN_OVERSEA_EXTERNAL_VERNUMBER}\n";
        }
        print "ro.gn.extHWvernumber=$ENV{GN_OVERSEA_HW_VERSION}\n";
    } else {
    print "ro.gn.extvernumber=$ENV{GN_EXTERNAL_VERNUMBER}\n"
    }
    #GIONEE: luohui 2013-02-03 modify for CR00771002 Oversea end<-
}

if(defined($ENV{GN_EXTERNAL_MODEL})){
    print "ro.gn.extmodel=$ENV{GN_EXTERNAL_MODEL}\n";
}

if(defined($ENV{GN_BUILD_DISPLAY_ID})){
    print "ro.build.display.id=$ENV{GN_BUILD_DISPLAY_ID}\n";
}

if(defined($ENV{GN_PRODUCT_MODEL})){
    print "ro.product.model=$ENV{GN_PRODUCT_MODEL}\n";
}

if(defined($ENV{GN_PRODUCT_BRAND})){
    print "ro.product.brand=$ENV{GN_PRODUCT_BRAND}\n";
}

if(defined($ENV{GN_PRODUCT_NAME})){
    print "ro.product.name=$ENV{GN_PRODUCT_NAME}\n";
}

if(defined($ENV{GN_TARGET_DEVICE})){
    print "ro.product.device=$ENV{GN_TARGET_DEVICE}\n"; 
}

if(defined($ENV{GN_RO_GN_GNVERNUMBERREL})){
    print "ro.gn.gnvernumberrel=$ENV{GN_RO_GN_GNVERNUMBERREL}\n";
}

if(defined($ENV{GIONEEPRODUCTID})){
    print "ro.gn.gnproductid=$ENV{GIONEEPRODUCTID}\n";
}

if(defined($ENV{GIONEEPROJECTID})){
    print "ro.gn.gnprojectid=$ENV{GIONEEPROJECTID}\n";
}

if(defined($ENV{GN_ZN_INTERNAL_VER_NUMBER})){
    print "ro.gn.gnznvernumber=$ENV{GN_ZN_INTERNAL_VER_NUMBER}\n";
}

if(defined($ENV{GN_INTERNAL_VER_NUMBER})){
    print "ro.gn.gnvernumber=$ENV{GN_INTERNAL_VER_NUMBER}\n";
}

if(exists $ENV{GN_ROM_VERNUMBER}){
    print "ro.gn.gnromvernumber=$ENV{GN_ROM_VERNUMBER}\n";
}

if(defined($ENV{GN_DEVICE_MODEL})){
    print "ro.device.model=$ENV{GN_DEVICE_MODEL}\n";
}
################################# APP BEGIN #################################
#gionee zengxuanhui 20120716 add for cta begin
if (exists $ENV{GN_CTA_SUPPORT}) {
print "ro.gn.cta.support=$ENV{GN_CTA_SUPPORT}\n";
}
#gionee zengxuanhui 20120716 add for cta end

#Gionee huangsf 2012-06-25 add for meid CR00622338 start
if (exists $ENV{GN_APP_MEID_LENGTH_FIFTEEN_SUPPORT} && $ENV{GN_APP_MEID_LENGTH_FIFTEEN_SUPPORT} eq "yes") {
print "ro.gn.meid.fifteen.length=$ENV{GN_APP_MEID_LENGTH_FIFTEEN_SUPPORT}\n";
}
#Gionee huangsf 2012-06-25 add for meid CR00622338 end

#Gionee huming 2012-07-27 add for CR00657653 begin
if(defined($ENV{GN_DEFAULT_THEME_STYLE}))  {
    print "ro.gn.theme.style=$ENV{GN_DEFAULT_THEME_STYLE}\n";
}

print "ro.gn.theme.prop=$ENV{GN_APP_THEME_SUPPORT}\n";

if (exists $ENV{GN_THEME_DEFAULT_PACKAGENAME})
{
    print "ro.gn.theme.default=$ENV{GN_THEME_DEFAULT_PACKAGENAME}\n";
}
#Gionee huming 2012-07-27 add for CR00657653 end

# Gionee lihq 2012-07-20 add for CR00651972 start
print "ro.gn.settings.OnOffAirplane=$ENV{GN_APP_SETTINGS_SCHEDULE_ON_OFF_AIRPLANE_SUPPORT}\n";
# Gionee lihq 2012-07-20 add for CR00651972 end

# Gionee lihq 2012-08-09 add for CR00672460 start
print "ro.gn.mtk.poweroff.alarm.prop=$ENV{GN_MTK_POWEROFF_ALARM_SUPPORT}\n";
# Gionee lihq 2012-08-09 add for CR00672460 end

##### 联系人 begin #####
#Gionee wangth 20120722 add start
print "ro.gn.contacts.support=$ENV{GN_APP_CONTACTS_SUPPORT}\n";
print "ro.gn.contacts.newfeature=$ENV{GN_CONTACTS_NEWFEATURE}\n";
#Gionee wangth 20120209 add end

#Gionee liuyanbo 20120724 merge for CR00652086 begin
print "ro.gn.match.numberlength=$ENV{GN_MATCH_CONTACTS_NUMBER_LENGTH}\n";
#Gionee liuyanbo 20120724 merge for CR00652086 end
##### 联系人 end #####

##### 短信 begin #####
#金立短信风格
if (exists $ENV{GN_APP_MSG_BOX_SUPPORT} && $ENV{GN_APP_MSG_BOX_SUPPORT} eq "yes")
{
    print "ro.gn.msgbox.prop=$ENV{GN_APP_MSG_BOX_SUPPORT}\n";
}

if (exists $ENV{GN_APP_MSG_CONTACT_PICKER} && $ENV{GN_APP_MSG_CONTACT_PICKER} eq "yes")
{
    print "ro.gn.msg.contactpicker=$ENV{GN_APP_MSG_CONTACT_PICKER}\n";
}

if (exists $ENV{GN_APP_CONTACT_CONTAINER_SUPPORT} && $ENV{GN_APP_CONTACT_CONTAINER_SUPPORT} eq "yes")
{
    print "ro.gn.msg.container.prop=$ENV{GN_APP_CONTACT_CONTAINER_SUPPORT}\n";
}

if (exists $ENV{GN_APP_MSG_RECOMMENDBOX_SUPPORT} && $ENV{GN_APP_MSG_RECOMMENDBOX_SUPPORT} eq "yes")
{
    print "ro.gn.recommendbox.prop=$ENV{GN_APP_MSG_RECOMMENDBOX_SUPPORT}\n";
}

#短信草稿箱
if (exists $ENV{GN_APP_MSG_DRAFTBOX_SUPPORT} && $ENV{GN_APP_MSG_DRAFTBOX_SUPPORT} eq "yes")
{
    print "ro.gn.draftbox.prop=$ENV{GN_APP_MSG_DRAFTBOX_SUPPORT}\n";
}
#短信备份
if (exists $ENV{GN_MSG_BACKUP_SUPPORT} && $ENV{GN_MSG_BACKUP_SUPPORT} eq "yes")
{
    print "ro.gn.msgbackup.prop=$ENV{GN_MSG_BACKUP_SUPPORT}\n";
}
#短信大字号
if (exists $ENV{GN_APP_MSG_BIG_FONT_SUPPORT})
{
    print "ro.gn.msgbigfont.prop=$ENV{GN_APP_MSG_BIG_FONT_SUPPORT}\n";
}
#短信弹出框提示
if (exists $ENV{GN_POPUP_MSG_SUPPORT} && $ENV{GN_POPUP_MSG_SUPPORT} eq "yes")
{
    print "ro.gn.popupmsg.prop=$ENV{GN_POPUP_MSG_SUPPORT}\n";
}
#待机新短信亮屏提醒
if (exists $ENV{GN_NEWMSG_WAKELOCK_SUPPORT} && $ENV{GN_NEWMSG_WAKELOCK_SUPPORT} eq "yes")
{
    print "ro.gn.newmsgwakelock.prop=$ENV{GN_NEWMSG_WAKELOCK_SUPPORT}\n";
}
#加密
if (exists $ENV{GN_ENCRYPTION_SUPPORT} )
{
    print "ro.gn.encryption.prop=$ENV{GN_ENCRYPTION_SUPPORT}\n";
}
#短信支持SD卡铃声
if (exists $ENV{GN_APP_MSG_SD_RING_SUPPORT} )
{
    print "ro.gn.msgsdring.prop=$ENV{GN_APP_MSG_SD_RING_SUPPORT}\n";
}
#短信导入导出
if (exists $ENV{GN_MMS_IMPORT_EXPORT_SUPPORT} )
{
    print "ro.gn.export.import.support=$ENV{GN_MMS_IMPORT_EXPORT_SUPPORT}\n";
}
#产品定义：收件人上限为100个
if (exists $ENV{GN_RECIPIENT_LIMIT_SUPPORT} )
{
    print "ro.gn.recipientlimit.prop=$ENV{GN_RECIPIENT_LIMIT_SUPPORT}\n";
}
##### 短信 end #####

# Gionee huming 2012-09-03 add for CR00683926 begin
if (exists $ENV{GN_THEME_NET_FUNCTION_SUPPORT} && $ENV{GN_THEME_NET_FUNCTION_SUPPORT} eq "no") 
{
    print "ro.gn.theme.net.support=$ENV{GN_THEME_NET_FUNCTION_SUPPORT}\n";
} else {
    print "ro.gn.theme.net.support=yes\n";
}
# Gionee huming 2012-09-03 add for CR00683926 end

################################# APP END #################################
# Gionee Inc. (C) 2011. All rights reserved.

#系统锁屏样式
#gionee gaojt add for CR00754274 2012-12-26 start
if(defined($ENV{GN_LOCK_SCREEN_TYPE})){
    print "curlockscreen=$ENV{GN_LOCK_SCREEN_TYPE}\n";
}
#gionee gaojt add for CR00754274 2012-12-26 end

#Gionee wangyaohui 20120522 add for GUI4.0 CR00588626 start
if (exists $ENV{GN_SETTINGS_PLATFORM} && $ENV{GN_SETTINGS_PLATFORM} ne "") {
print "ro.gn.settings.prop=yes\n"
}
#Gionee wangyaohui 20120522 add for GUI4.0 CR00588626 end

#Gionee fengjianyi 2012-12-28 add for CR00751916 start
if (exists $ENV{GN_WIDGET_SUPPORT} && $ENV{GN_WIDGET_SUPPORT} eq "yes")
{
    print "ro.gn.widget.support=$ENV{GN_WIDGET_SUPPORT}\n";
}
#Gionee fengjianyi 2012-12-28 add for CR00751916 end

#Gionee fengjianyi 2013-01-22 add for CR00766838 start
if (exists $ENV{GN_ACTION_REBOOT_SUPPORT} && $ENV{GN_ACTION_REBOOT_SUPPORT} eq "yes")
{
    print "ro.gn.action.reboot.support=$ENV{GN_ACTION_REBOOT_SUPPORT}\n";
}
#Gionee fengjianyi 2013-01-22 add for CR00766838 end

#Gionee zengxuanhui 20120809 add for CR00672106 begin
if (exists $ENV{GN_GEMINI_RINGTONE_SUPPORT} && $ENV{GN_GEMINI_RINGTONE_SUPPORT} eq "yes") 
{
    print "ro.gn.gemini.ringtone.support=$ENV{GN_GEMINI_RINGTONE_SUPPORT}\n";
}
#Gionee zengxuanhui 20120809 add for CR00672106 end

#Gionee baorui 2013-02-17 modify for CR00770720 begin
if (exists $ENV{GN_SOUNDRECORDER_OGG_SUPPORT} && $ENV{GN_SOUNDRECORDER_OGG_SUPPORT} eq "no") 
{
    print "ro.gn.soundrecorder.ogg.support=$ENV{GN_SOUNDRECORDER_OGG_SUPPORT}\n";
}
#Gionee baorui 2013-02-17 modify for CR00770720 end

#gionee fengxb 2013-2-21 add for CR00771365 start 
if (exists $ENV{GN_DELAY_UPDATE_SIGNAL_STRENGTH}){
print "ro.gn.delayupdateSignalStrength=$ENV{GN_DELAY_UPDATE_SIGNAL_STRENGTH}\n";
}
#gionee fengxb 2013-2-21 add for CR00771365 end

#Gionee lihuafang 2012-06-11 add for CR00623519 begin
if (exists $ENV{GN_OPERATOR_SHOWDIGITALSLOT}){
print "ro.gn.operator.showdigitalslot=$ENV{GN_OPERATOR_SHOWDIGITALSLOT}\n";
}
#Gionee lihuafang 2012-06-11 add for CR00623519 end

#Gionee:niejn 20111220 add for  CR00471826 start
if (exists $ENV{GN_SHUTDOWN_NOCONFIRM_SUPPORT} && $ENV{GN_SHUTDOWN_NOCONFIRM_SUPPORT} eq "yes"){
print "ro.gn.shutdown.noconfirm=$ENV{GN_SHUTDOWN_NOCONFIRM_SUPPORT}\n";
}
#Gionee:niejn 20111220 add for  CR00471826 end 

#Gionee fengjianyi 2013-02-22 add for CR00773021 start
if (exists $ENV{GN_NOTIFICATION_TOOLBAR_SUPPORT} && $ENV{GN_NOTIFICATION_TOOLBAR_SUPPORT} eq "yes"){
print "ro.gn.notifi.toolbar.support=$ENV{GN_NOTIFICATION_TOOLBAR_SUPPORT}\n";
}
#Gionee fengjianyi 2013-02-22 add for CR00773021 end

#Gionee wangyy 2012-7-27 add for CR00643075 start
if (exists $ENV{GN_USB_UI_SUPPORT} && $ENV{GN_USB_UI_SUPPORT} eq "yes") {
    print "ro.gn.usb.ui.support=$ENV{GN_USB_UI_SUPPORT}\n";
}
#Gionee wangyy 2012-7-27 add for CR00643075 end

#Gionee:niejn 20120528 add for CR00605063 begin
if(defined($ENV{GN_3RD_KOMOXO_SUPPORT})) {
    print "ro.gn.3rd.komoxo.prop=$ENV{GN_3RD_KOMOXO_SUPPORT}\n";
}
#Gionee:niejn 20120528 add for CR00605063 end

#Gionee cuijiuyu 20121122 add for salesstatistic begin
print "ro.gn.salesstatistic.support=$ENV{GN_OVERSEA_SALES_STATISTIC_SUPPORT}\n";
if(exists $ENV{GN_OVERSEA_SALES_STATISTIC_URL} && $ENV{GN_OVERSEA_SALES_STATISTIC_URL} ne "")
{
    print "ro.gn.sales.salesstatistic.url=$ENV{GN_OVERSEA_SALES_STATISTIC_URL}\n";
}
#Gionee cuijiuyu 20121122 add for salesstatistic end

#GIONEE: luohui 2013-02-19 modify for CR00770997 Oversea start->
if (exists $ENV{GN_OVERSEA_PRODUCT} && $ENV{GN_OVERSEA_PRODUCT} eq "yes") {
    print "ro.gn.oversea.product=$ENV{GN_OVERSEA_PRODUCT}\n";
}

if (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} ne "") {
    print "ro.gn.oversea.custom=$ENV{GN_OVERSEA_CUSTOM}\n";
}

if (exists $ENV{GN_OVERSEA_ODM} && $ENV{GN_OVERSEA_ODM} eq "yes") {
    print "ro.gn.oversea.odm=$ENV{GN_OVERSEA_ODM}\n";
}

if (exists $ENV{GN_APP_OVERSEA_WEATHER_SOURCE} && $ENV{GN_APP_OVERSEA_WEATHER_SOURCE} ne "") {
   print "ro.gn.oversea.weather.source=$ENV{GN_APP_OVERSEA_WEATHER_SOURCE}\n";
}

if($ENV{GN_SETTING_OTA_UPDATE_SUPPORT} eq "yes" && $ENV{GN_OVERSEA_CUSTOM_OTA_SERVER} ne "") {
    print "ro.gn.oversea.ota.server=$ENV{GN_OVERSEA_CUSTOM_OTA_SERVER}\n";
}

###default time zone begin
if (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "INDIA_MICROMAX") {
	print "persist.sys.timezone=Asia/Calcutta\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "VIETNAM_VHH") {
	print "persist.sys.timezone=Asia/Saigon\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "RUSSIA_FLY") {
	print "persist.sys.timezone=Europe/Moscow\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "TAIWAN_GPLUS") {
	print "persist.sys.timezone=Asia/Taipei\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "INDONESIA_MITO") {
	print "persist.sys.timezone=Asia/Jakarta\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "AFRICA_GIONEE") {
	print "persist.sys.timezone=Africa/Brazzaville\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "MYANMAR_STRONGSOURCE") {
	print "persist.sys.timezone=Asia/Rangoon\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "SAUDI_GIONEE") {
	print "persist.sys.timezone=Asia/Baghdad\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "VISUALFAN") {
	print "persist.sys.timezone=Europe/Minsk\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "INDONESIA_POLYTRON") {
	print "persist.sys.timezone=Asia/Jakarta\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "PAKISTAN_QMOBILE") {
	print "persist.sys.timezone=Asia/Karachi\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "BANGLADESH_SYMPHONY") {
	print "persist.sys.timezone=Asia/Almaty\n";	
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "SOUTH_AMERICA_BLU") {
	print "persist.sys.timezone=America/Mexico_City\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "INDIA_GIONEE") {
	print "persist.sys.timezone=Asia/Calcutta\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "VIETNAM_GIONEE") {
	print "persist.sys.timezone=Asia/Saigon\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "ITALY_NGM") {
	print "persist.sys.timezone=Europe/Amsterdam\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "AIRIS"){
	print "persist.sys.timezone=Europe/Helsinki\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "NEPAL_TELETALK") {
	print "persist.sys.timezone=Asia/Katmandu\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "RUSSIA_EXPLAY") {
	print "persist.sys.timezone=Europe/Moscow\n";
}elsif (exists $ENV{GN_OVERSEA_CUSTOM} && $ENV{GN_OVERSEA_CUSTOM} eq "INDIA_LAVA") {
	print "persist.sys.timezone=Asia/Calcutta\n";
}else {
    print "persist.sys.timezone=Asia/Shanghai\n";
}
###default time zone end

#GIONEE: luohui 2013-02-19 modify for CR00770997 Oversea end<-

#Gionee xufei 20111104 add for CR00424618 start
if ($ENV{GN_SOUNDS_SUPPORT} eq "yes")
{
print "ro.config.notification_sound=$ENV{GN_DEFAULT_NOTIFICATION}\n";
print "ro.config.alarm_alert=$ENV{GN_DEFAULT_ALARM_ALERT}\n";
print "ro.config.ringtone=$ENV{GN_DEFAULT_VOICE_CALL}\n";
print "ro.gn.default.ringtone2=$ENV{GN_DEFAULT_VOICE_CALL2}\n";
print "ro.gn.default.mmstone=$ENV{GN_DEFAULT_MMS}\n";
print "ro.gn.default.mmstone2=$ENV{GN_DEFAULT_MMS2}\n";
#Gionee songganggang 20120721 add for CR00652126 start
}else {
print "ro.config.notification_sound=$ENV{OVERSEA_DEFAULT_NOTIFICATION}\n";
print "ro.config.alarm_alert=$ENV{OVERSEA_DEFAULT_ALARM_ALERT}\n";
print "ro.config.ringtone=$ENV{OVERSEA_DEFAULT_VOICE_CALL}\n";
#GIONEE: luohui 2012-11-29 modify for CR00737314 Oversea start->
print "ro.gn.default.ringtone2=$ENV{OVERSEA_DEFAULT_VOICE_CALL2}\n";
print "ro.gn.default.mmstone=$ENV{OVERSEA_DEFAULT_MMS}\n";
print "ro.gn.default.mmstone2=$ENV{OVERSEA_DEFAULT_MMS2}\n";
#GIONEE: luohui 2012-11-29 modify for CR00737314 Oversea end<-
}
#Gionee songganggang 20120721 add for CR00652126 end
#Gionee xufei 20111104 add for CR00424618 end

#Gionee zengxh 20121121 add for CR00724044 start
if (exists $ENV{GN_APP_AUDIO_PROFILE_SUPPORT} && $ENV{GN_APP_AUDIO_PROFILE_SUPPORT} eq "yes") 
{
    print "ro.gn.audioprofile.support=$ENV{GN_APP_AUDIO_PROFILE_SUPPORT}\n";
}
#Gionee zengxh 20121121 add for CR00724044 end

#Gionee huangyuncai 2013-2-24 add start
if (exists $ENV{GN_2SIM_SUPPORT} && $ENV{GN_2SIM_SUPPORT} eq "yes") 
{
    print "ro.gn.2sim.support=$ENV{GN_2SIM_SUPPORT}\n";
}
#Gionee huangyuncai 2013-2-24 add end

#Gionee huangyuncai 2013-2-25 add start
if (exists $ENV{GN_APP_THEME_SUPPORT} && $ENV{GN_APP_THEME_SUPPORT} eq "yes") {
   print "ro.gn.theme.combinpkg=com.android.camera&com.android.gallery3d#com.mediatek.FMRadio&com.quicinc.fmradio\n";
}
#Gionee huangyuncai 2013-2-25 add end

#Gionee fangbin 20120813 added for CR00646833 start
if (exists $ENV{GN_3RD_DOCTORAN_OPENAPI_SUPPORT}){
print "ro.doctoran.openapi.prop=$ENV{GN_3RD_DOCTORAN_OPENAPI_SUPPORT}\n";
}
#Gionee fangbin 20120813 added for CR00646833 end

#Gionee wangyy 2013-2-25 add for ota start
if (exists $ENV{GN_SETTING_OTA_UPDATE_SUPPORT} && $ENV{GN_SETTING_OTA_UPDATE_SUPPORT} eq "yes") 
{
    print "ro.gn.ota.update=$ENV{GN_SETTING_OTA_UPDATE_SUPPORT}\n";
}
#Gionee wangyy 2013-2-25 add for ota end

#Gionee fangbin 20120530 added for CR00608714 GN_ZoomClipView start
if (exists $ENV{GN_APK_ZOOMCLIPVIEW_SUPPORT}){
print "ro.gn.zoomclipview.prop=$ENV{GN_APK_ZOOMCLIPVIEW_SUPPORT}\n";
}
#Gionee fangbin 20120530 added for CR00608714 GN_ZoomClipView end

#Gionee fangbin 20120814 add for GIUI4.3 start
if (exists $ENV{GN_NEW_FEATURE_THIRD_VERSION}){
print "ro.gn.newfeature.v3=$ENV{GN_NEW_FEATURE_THIRD_VERSION}\n";
}
#Gionee fangbin 20120814 add for GIUI4.3 end

#Gionee xiongjiaxin 2012-6-27 add for CR00625665 start
if (exists $ENV{GN_EMAIL_CN_SUPPORT}){
print "ro.gn.email.cn.support=$ENV{GN_EMAIL_CN_SUPPORT}\n";
}
#Gionee xiongjiaxin 2012-6-27 add for CR00625665 end

#Gionee xiongjiaxin 2012-6-27 add for CR00625665 start
if (exists $ENV{GN_DTS_SUPPORT}){
print "ro.gn.music.dts=$ENV{GN_DTS_SUPPORT}\n";
}
#Gionee xiongjiaxin 2012-6-27 add for CR00625665 end

#Gionee liuran 2012-08-15 add for CR00677854 start
if (exists $ENV{GN_PUSH_SUPPORT}){
print "ro.gn.gpe.support=$ENV{GN_PUSH_SUPPORT}\n";
}
if (exists $ENV{GN_CTRL_3RD_APP_PUSH}){
print "ro.gn.ctrl.3rd.app.push=$ENV{GN_CTRL_3RD_APP_PUSH}\n";
}
#Gionee liuran 2012-08-15 add for CR00677854 end

#Gionee fengjianyi 2012-09-28 add for CR00705430 start
if (exists $ENV{GN_GUEST_MODE_SUPPORT} && $ENV{GN_GUEST_MODE_SUPPORT} eq "yes")
{
    print "ro.gn.guestmode.support=$ENV{GN_GUEST_MODE_SUPPORT}\n";
}
#Gionee fengjianyi 2012-09-28 add for CR00705430 end

#Gionee huangyuncai 2013-2-25 add start
if (exists $ENV{GN_POWERSAVING_SUPPORT} && $ENV{GN_POWERSAVING_SUPPORT} eq "yes")
{
    print "ro.gn.powersaving.support=$ENV{GN_POWERSAVING_SUPPORT}\n";
}
#Gionee huangyuncai 2013-2-25 add end

#Gionee huyuke 2011-07-25 add for CR00303875 begin
if(exists $ENV{GN_APP_SYSTEMUI_STATUSBAR_GIONEE_STYLE_SUPPORT}){
print "ro.gn.statusbar.gionee.style=$ENV{GN_APP_SYSTEMUI_STATUSBAR_GIONEE_STYLE_SUPPORT}\n";
}
#Gionee huyuke 2011-07-25 add for CR00303875 end

#Gionee niejn 20130304 add for CR00778286 begin
if (exists $ENV{GN_DEFAULT_INPUT_METHOD}){
print "ro.gn.defaultime.support=$ENV{GN_DEFAULT_INPUT_METHOD}\n";
}
#Gionee niejn 20130304 add for CR00778286 end

#Gionee lihuafang 2012-06-11 add for CR00623519 begin
if (exists $ENV{GN_OPERATOR_SHOWDIGITALSLOT}){
print "ro.gn.operator.showdigitalslot=$ENV{GN_OPERATOR_SHOWDIGITALSLOT}\n";
}
#Gionee lihuafang 2012-06-11 add for CR00623519 end

#Gionee:zjy 20110708 added for CR00289444 start
if(exists $ENV{GN_APP_PHONE_IP_DIAL_SUPPORT}){
print "ro.gn.ip.dial=$ENV{GN_APP_PHONE_IP_DIAL_SUPPORT}\n";
}
#Gionee:zjy 20110708 added for CR00289444 end

#Gionee:zjy 20110802 added for double card or single card start
if(exists $ENV{GN_APP_PHONE_DOUBLE_IP_DIAL_SUPPORT}){
print "ro.gn.double.ip.dial=$ENV{GN_APP_PHONE_DOUBLE_IP_DIAL_SUPPORT}\n";
}
#Gionee:zjy 20110802 added for double card or single card end

#Gionee zengxuanhui 20120809 add for CR00672106 begin
if (exists $ENV{GN_GEMINI_RINGTONE_SUPPORT} && $ENV{GN_GEMINI_RINGTONE_SUPPORT} eq "yes") 
{
    print "ro.gn.gemini.ringtone.support=$ENV{GN_GEMINI_RINGTONE_SUPPORT}\n";
}
#Gionee zengxuanhui 20120809 add for CR00672106 end

#Gionee fangbin 2013-03-04 add for CR00774730 begin
if ($ENV{GN_ANSWER_SHAKE_VOLUME_UP_SUPPORT} eq "yes")
{
    print "ro.gn.shake.volume.up.support=$ENV{GN_ANSWER_SHAKE_VOLUME_UP_SUPPORT}\n";
}
#Gionee fangbin 2013-03-04 add for CR00774730 end

#Gionee fengxb 2012-7-6 add for CR00627511 start
if (exists $ENV{GN_PHONE_NOWALLPAPER}){
print "ro.gn.phone.nowallpaper=$ENV{GN_PHONE_NOWALLPAPER}\n";
}
#Gionee fengxb 2012-7-6 add for CR00627511 end

#Gionee:huangyuncai 20110728 added for Overturn Mute begin
if(exists $ENV{GN_APP_PHONE_OVERTURN_MUTE_SUPPORT}){
print "ro.gn.phone.overturnMute=$ENV{GN_APP_PHONE_OVERTURN_MUTE_SUPPORT}\n";
}
#Gionee:huangyuncai 20110728 added for Overturn Mute end

#Gionee:tianyr 20120731 added for CR00662756 number area
if(exists $ENV{GN_APP_NUMAREA_SUPPORT}){
print "ro.gn.gioneenumarea.prop=$ENV{GN_APP_NUMAREA_SUPPORT}\n";
}

#Gionee fengjianyi 2012-07-27 add for CR00614662 start
if ($ENV{GN_APK_VOICE_HELPER_SUPPORT} =~ /^yes/)
{
    print "ro.gn.voicehelper.support=$ENV{GN_APK_VOICE_HELPER_SUPPORT}\n";
}
#Gionee fengjianyi 2012-07-27 add for CR00614662 end

#Gionee:fengxb 20110701 added for phone start
if(exists $ENV{GN_APP_PHONE_SUPPORT}){
print "ro.gn.phone=$ENV{GN_APP_PHONE_SUPPORT}\n";
}
#Gionee:fengxb 20110701 added for phone end

#gionee zengxuanhui 20120704 add for CR00633823 start 
if(exists $ENV{GN_SCREEN_SHOT_SUPPORT}){
print "ro.gn.screenshot.prop=$ENV{GN_SCREEN_SHOT_SUPPORT}\n";
}
#gionee zengxuanhui 20120704 add for CR00633823 end

#gionee zengxuanhui 20120704 add for CR00633823 start 
if(exists $ENV{GN_PRODUCT_LOCALE_SUPPORT}){
print "ro.product.locale.region=$ENV{GN_PRODUCT_LOCALE_SUPPORT}\n";
}
#gionee zengxuanhui 20120704 add for CR00633823 end

#gionee zengxuanhui 20120704 add for CR00633823 start 
if(exists $ENV{GN_2CARD_SWAP_SUPPORT}){
print "ro.gn.gn2sdcardswap=$ENV{GN_2CARD_SWAP_SUPPORT}\n";
}
#gionee zengxuanhui 20120704 add for CR00633823 end

#Gionee lihq 2012-9-4 add for CR00682401 start
if (exists $ENV{GN_APP_CHANGER_SUPPORT} && $ENV{GN_APP_CHANGER_SUPPORT} eq "yes")
{
    print "ro.gn.change.support=$ENV{GN_APP_CHANGER_SUPPORT}\n";
}
#Gionee lihq 2012-9-4 add for CR00682401 end

#Gionee:huangyuncai 20110720 added for vibrate when connect begin
if(exists $ENV{GN_APP_PHONE_CONNECT_VIBRATE_SUPPORT}){
print "ro.gn.phone.vibrateOnConnect=$ENV{GN_APP_PHONE_CONNECT_VIBRATE_SUPPORT}\n";
}
#Gionee:huangyuncai 20110720 added for vibrate when connect end

#gionee gaoj 2012-5-11 added for GIUI4.0 CR00555790 start
if (exists $ENV{GN_POPUP_MSG_SUPPORT}){
print "ro.gn.popupmsg.prop=$ENV{GN_POPUP_MSG_SUPPORT}\n";
}

if (exists $ENV{GN_ENCRYPTION_SUPPORT}){
print "ro.gn.encryption.prop=$ENV{GN_ENCRYPTION_SUPPORT}\n";
}
if (exists $ENV{GN_TRANSPARENT_SUPPORT}){
print "ro.gn.transparent.prop=$ENV{GN_TRANSPARENT_SUPPORT}\n";
}
#gionee gaoj 2012-5-11 added for GIUI4.0 CR00555790 end

#Gionee: zhanglina 2012-11-12 modify for remove custom theme begin
if (exists $ENV{GN_OVERSEA_REMOVE_CUSTOM_THEME} && $ENV{GN_OVERSEA_REMOVE_CUSTOM_THEME} eq "yes") 
{
    print "ro.gn.remove.custom.theme=$ENV{GN_OVERSEA_REMOVE_CUSTOM_THEME}\n";
}
#Gionee: zhanglina 2012-11-12 modify for remove custom theme end

#Gionee lich 2013-03-08 add for CR00780241 begin
if (exists $ENV{GN_CLOUDDISK_SUPPORT})
{
    print "ro.gn.clouddisk.support=$ENV{GN_CLOUDDISK_SUPPORT}\n";
}
#Gionee lich 2013-03-08 add for CR00780241 end

#Gionee qiuxd 20121015 add for CR00711865 start
if(exists $ENV{GN_APP_PERMISSION_CONTROL_SUPPORT}){
    print "ro.gn.app.perm.ctrl=$ENV{GN_APP_PERMISSION_CONTROL_SUPPORT}\n";
}
#Gionee qiuxd 20121015 add for CR00711865 end

#Gionee gaocong 20120703 add for CR00633527 begin
if (exists $ENV{GN_WIFI_AP_LIST_DIALOG_SUPPORT} && $ENV{GN_WIFI_AP_LIST_DIALOG_SUPPORT} eq "yes")
{
    print "ro.gn.wifidialog.support=$ENV{GN_WIFI_AP_LIST_DIALOG_SUPPORT}\n";
}
#Gionee gaocong 20120703 add for CR00633527 end

#gionee yewq 2013-3-12 add for CR00780320 begin
if (exists $ENV{GN_CAMERA_SOUND_CHOOSE_SUPPORT} && $ENV{GN_CAMERA_SOUND_CHOOSE_SUPPORT} eq "yes") 
{
    print "ro.gn.camera.sound.support=$ENV{GN_CAMERA_SOUND_CHOOSE_SUPPORT}\n";
}
#gionee yewq 2013-3-12 add for CR00780320 end

#Gionee liuyanbo 2012-03-14 add for CR00783791 start
if (exists $ENV{GN_SEND_ERROR_REPORT_SUPPORT} && $ENV{GN_SEND_ERROR_REPORT_SUPPORT} eq "yes")
{
    print "ro.gn.sendreport.support=$ENV{GN_SEND_ERROR_REPORT_SUPPORT}\n";
}   
#Gionee liuyanbo 2012-03-14 add for CR00783791 end

#Gionee huangwenting 20121106 add for CR00725065 start
if(defined($ENV{GN_LIVE_WALLPAPER_VU_MATER})) {
    print "gn.lwallpaper.vu.mater=$ENV{GN_LIVE_WALLPAPER_VU_MATER}\n";
}
if(defined($ENV{GN_LIVE_WALLPAPER_COLORS})) {
    print "gn.lwallpaper.colors=$ENV{GN_LIVE_WALLPAPER_COLORS}\n";
}
if(defined($ENV{GN_LIVE_WALLPAPER_WAVEFORM})) {
    print "gn.lwallpaper.waveform=$ENV{GN_LIVE_WALLPAPER_WAVEFORM}\n";
}
if(defined($ENV{GN_LIVE_WALLPAPER_POLARCLOCK})) {
    print "gn.lwallpaper.polarclock=$ENV{GN_LIVE_WALLPAPER_POLARCLOCK}\n";
}
if(defined($ENV{GN_LIVE_WALLPAPER_MAGICSMOKE})) {
    print "gn.lwallpaper.magicsmoke=$ENV{GN_LIVE_WALLPAPER_MAGICSMOKE}\n";
}
if(defined($ENV{GN_LIVE_WALLPAPER_FREQUENCY_SPECTRUM})) {
    print "gn.lwallpaper.frequency=$ENV{GN_LIVE_WALLPAPER_FREQUENCY_SPECTRUM}\n";
}
#Gionee huangwenting 20121106 add for CR00725065 end

#Gionee xiaolin 20120528 add for CR00611372 start

if (exists $ENV{GN_MMI_TEST_SUPPORT} && $ENV{GN_MMI_TEST_SUPPORT} eq "yes"){
print "ro.gn.mmi.test=$ENV{GN_MMI_TEST_SUPPORT}\n";
}
if(defined($ENV{GN_MMI_WCDMA})) {
    print "gn.mmi.wcdma=$ENV{GN_MMI_WCDMA}\n";
}
if(defined($ENV{GN_MMI_MIC2})) {
    print "gn.mmi.mic2=$ENV{GN_MMI_MIC2}\n";
}
if(defined($ENV{GN_MMI_KEYTEST_MENU})) {
    print "gn.mmi.keytest.menu=$ENV{GN_MMI_KEYTEST_MENU}\n";
}
if(defined($ENV{GN_MMI_KEYTEST_APP})) {
    print "gn.mmi.keytest.app=$ENV{GN_MMI_KEYTEST_APP}\n";
}
if(defined($ENV{GN_MMI_KEYTEST_SEARCH})) {
    print "gn.mmi.keytest.search=$ENV{GN_MMI_KEYTEST_SEARCH}\n";
}
if(defined($ENV{GN_MMI_KEYTEST_CAMERA})) {
    print "gn.mmi.keytest.camera=$ENV{GN_MMI_KEYTEST_CAMERA}\n";
}
if(defined($ENV{GN_MMI_KEYTEST_HALL})) {
    print "gn.mmi.keytest.hall=$ENV{GN_MMI_KEYTEST_HALL}\n";
}
if(defined($ENV{GN_MMI_SENSOR_LIGHT})) {
    print "gn.mmi.sensor.light=$ENV{GN_MMI_SENSOR_LIGHT}\n";
}
if(defined($ENV{GN_MMI_CAMERA_FRONT})) {
    print "gn.mmi.camera.front=$ENV{GN_MMI_CAMERA_FRONT}\n";
}
if(defined($ENV{GN_MMI_SENSOR_GYRO})) {
	print "gn.mmi.sensor.gyro=$ENV{GN_MMI_SENSOR_GYRO}\n";
}
if(defined($ENV{GN_MMI_SENSOR_COMPASS})) {
	print "gn.mmi.sensor.compass=$ENV{GN_MMI_SENSOR_COMPASS}\n";
}
if(defined($ENV{GN_MMI_RECEIVER2})) { 
    print "gn.mmi.receiver2=$ENV{GN_MMI_RECEIVER2}\n";
}
if(defined($ENV{GN_MMI_FLASH_LIGHT})) {
    print "gn.mmi.flashlight=$ENV{GN_MMI_FLASH_LIGHT}\n";
}
if(defined($ENV{GN_MMI_NFC})) {
    print "gn.mmi.nfc=$ENV{GN_MMI_NFC}\n";
}
#Gionee xiaolin 20120528 add for CR00611372 end

#Gionee:xuwen 20110914 modified for CR00366489 start
if (exists $ENV{MTK_CTA_SUPPORT}){
print "ro.cta.support=$ENV{MTK_CTA_SUPPORT}\n";
}
#Gionee:xuwen 20110914 modified end

#Gionee liss 2012-12-14 add for CR00740992 start
if (exists $ENV{GN_APP_CHANGE_3DBAREWALLPAPER_SUPPORT} && $ENV{GN_APP_CHANGE_3DBAREWALLPAPER_SUPPORT} eq "yes") 
{
    print "ro.gn.3d.barewallpaper.support=$ENV{GN_APP_CHANGE_3DBAREWALLPAPER_SUPPORT}\n";
}
#Gionee liss 2012-12-14 add for CR00740992 end

#Gionee huangwenting 2012-12-10 add for CR00741564 start
if (exists $ENV{GN_3RD_LIVEWALLPAPER_SUPPORT} && $ENV{GN_3RD_LIVEWALLPAPER_SUPPORT} eq "yes") 
{
    print "ro.gn.3dlivewallpaper.support=$ENV{GN_3RD_LIVEWALLPAPER_SUPPORT}\n";
}
#Gionee huangwenting 2012-12-10 add for CR00741564 end

#Gionee:xuwen 20110630 added for aora number area
if(exists $ENV{GN_3RD_AORANUMAREA_SUPPORT}){
print "ro.gn.3rd.aoranumarea.prop=$ENV{GN_3RD_AORANUMAREA_SUPPORT}\n";
}

#Gionee:niejn 20110927 add for CR00384845 begin
if (exists $ENV{GN_3RD_AORAPIM_SUPPORT}){
print "ro.gn.3rd.aorapim.prop=$ENV{GN_3RD_AORAPIM_SUPPORT}\n";
}
#Gionee:niejn 20110927 add for CR00384845 end

#Gionee niejn 20111102 add for dual system start
if (exists $ENV{GN_3RD_DOCTORAN_SUPPORT}){
print "ro.gn.3rd.doctoran=$ENV{GN_3RD_DOCTORAN_SUPPORT}\n";
}
#Gionee niejn 20111102 add for dual system end

#Gionee niejn 20111102 add for dual system start
if (exists $ENV{GN_3RD_DUALSYSTEM_SUPPORT}){
print "ro.gn.3rd.dualsystem=$ENV{GN_3RD_DUALSYSTEM_SUPPORT}\n";
}
#Gionee niejn 20111102 add for dual system end

#Gionee:dingwen 2012-09-22 add for add torch menu in locksetting begin 
if (exists $ENV{GN_ADD_TORCH_MENU_SUPPORT} && $ENV{GN_ADD_TORCH_MENU_SUPPORT} eq "yes") 
{
    print "ro.gn.add.torchmenu=$ENV{GN_ADD_TORCH_MENU_SUPPORT}\n";
}
#Gionee:dingwen 2012-09-22 add for add torch menu in locksetting end

#Gionee baorui 2012-12-15 modify for CR00739833 begin
if (exists $ENV{GN_APP_DESKCLOCK1_2_SUPPORT}){
print "ro.gn.alarm.alert.poweron=$ENV{GN_APP_DESKCLOCK1_2_SUPPORT}\n";
}
#Gionee baorui 2012-12-15 modify for CR00739833 end

#Gionee Jingjc 2012-09-16 add for CR00693470 start
if (exists $ENV{GN_AMOLED_LCM_ACL_SUPPORT} && $ENV{GN_AMOLED_LCM_ACL_SUPPORT} eq "yes") 
{
    print "ro.gn.amoled.lcmacl.support=$ENV{GN_AMOLED_LCM_ACL_SUPPORT}\n";
}
#Gionee Jingjc 2012-09-16 add for CR00693470 end

#Gionee:zhang_xin 2012-10-23 add for CR00717539 start
if ($ENV{GN_APP_DEFAULT_SORT_SUPPORT} eq "yes")
{
    print "ro.gn.appsort.default=$ENV{GN_APP_DEFAULT_SORT_SUPPORT}\n";
}   
#Gionee:zhang_xin 2012-10-23 add for CR00717539 end

#GIONEE: tianxl 20121117 add for CR00733470 begin
if(exists $ENV{GN_APP_ASSOCIATION_SIM_SUPPORT} && $ENV{GN_APP_ASSOCIATION_SIM_SUPPORT} eq "yes")
{
    print "ro.gn.association.sim=$ENV{GN_APP_ASSOCIATION_SIM_SUPPORT}\n";
}
#GIONEE: tianxl 20121117 add for CR00733470 end

#Gionee:yuyongbao 20120408 added for audio para version check start
if (exists $ENV{GN_AUDIO_PARA_VERSION}){
print "ro.gn.audio_para_ver=$ENV{GN_AUDIO_PARA_VERSION}\n";
}
#Gionee:yuyongbao 20120408 added for audio para version check end

#GIONEE: luohui 2012-08-30 modify for CR00683229 start->#tangzepeng 2012-11-13 merge for CR00730213
#耳机已插入状态，来电自动接听
if(defined($ENV{GN_AUTO_ANSWER_CALL_HEADSET_SUPPORT})){
   print "ro.gn.auto.answercall.headset=$ENV{GN_AUTO_ANSWER_CALL_HEADSET_SUPPORT}\n";
}
#GIONEE: luohui 2012-08-30 modify for CR00683229 end<-

#Gionee wangyy 2012-9-3 add for CR00683419 start
if ($ENV{GN_BACKUP_MANAGE_SUPPORT} =~ /^yes/)
{
    print "ro.gn.backup.manage.support=$ENV{GN_BACKUP_MANAGE_SUPPORT}\n";
}
#Gionee wangyy 2012-9-3 add for CR00683419 end

#Gionee ligang 2011-10-9 add for CR00389010 browser homepage start
if ($ENV{GN_APP_GN_BROWSER_HOMEPAGE} ne "")
{
    #Gionee 20120804 chenrui modify for CR00664345 start
    if (exists $ENV{GN_PRODUCT_MODEL_EXTRA} && $ENV{GN_PRODUCT_MODEL_EXTRA} ne "")
    {
        print "ro.gn.browser.homepage=".$ENV{GN_APP_GN_BROWSER_HOMEPAGE}."?m=".$ENV{GN_EXTERNAL_MODEL}.$ENV{GN_PRODUCT_MODEL_EXTRA}."&b=".$ENV{GN_APP_GN_BROWSER_HOMEPAGE_B}."\n";
    }
    else
    {
        print "ro.gn.browser.homepage=".$ENV{GN_APP_GN_BROWSER_HOMEPAGE}."?m=".$ENV{GN_EXTERNAL_MODEL}."&b=".$ENV{GN_APP_GN_BROWSER_HOMEPAGE_B}."\n";
    }
    #Gionee 20120804 chenrui modify for CR00664345 end
}
#Gionee ligang 2011-10-9 add for CR00389010 browser homepage end

#Gionee:zjy 20110708 added for CR00289444 start
if(exists $ENV{GN_APP_PHONE_IP_DIAL_SUPPORT} && $ENV{GN_APP_PHONE_IP_DIAL_SUPPORT} eq "yes"){
print "ro.gn.ip.dial=$ENV{GN_APP_PHONE_IP_DIAL_SUPPORT}\n";
}
#Gionee:zjy 20110708 added for CR00289444 end

#Gionee:zjy 20110802 added for double card or single card start
if(exists $ENV{GN_APP_PHONE_DOUBLE_IP_DIAL_SUPPORT} && $ENV{GN_APP_PHONE_DOUBLE_IP_DIAL_SUPPORT} eq "yes"){
print "ro.gn.double.ip.dial=$ENV{GN_APP_PHONE_DOUBLE_IP_DIAL_SUPPORT}\n";
}
#Gionee:zjy 20110802 added for double card or single card end

#gionee yewq 2013-3-16 modify for CR00785447 begin
if (exists $ENV{GN_EMAIL_GENERAL_SIGNATURE_SUPPORT} && $ENV{GN_EMAIL_GENERAL_SIGNATURE_SUPPORT} eq "yes") 
{
    print "ro.gn.email.generalsignature=$ENV{GN_EMAIL_GENERAL_SIGNATURE_SUPPORT}\n";
}
#gionee yewq 2013-3-16 modify for CR00785447 end

# Gionee zhanglina 2012.7.19 add for remove lunar view start
if (exists $ENV{GN_REMOVE_CALENDAR_LUNAR_SUPPORT} && $ENV{GN_REMOVE_CALENDAR_LUNAR_SUPPORT} eq "yes") 
{
    print "ro.gn.remove.calendar.lunar=$ENV{GN_REMOVE_CALENDAR_LUNAR_SUPPORT}\n";
}
# Gionee zhanglina 2012.7.19 add for remove lunar view end

# Gionee tianliang modify start
if (exists $ENV{GN_OVERSEA_MUSIC_OFFLINE_SUPPORT} && $ENV{GN_OVERSEA_MUSIC_OFFLINE_SUPPORT} eq "yes") 
{
    print "ro.gn.oversea.music.offline.ver=$ENV{GN_OVERSEA_MUSIC_OFFLINE_SUPPORT}\n";
}
# Gionee tianliang modify end


#Gionee fangbin 20120511 added for GIUI4.0 CR00555786 start
if (exists $ENV{GN_APP_NUMAREA_UPDATE_SUPPORT} && $ENV{GN_APP_NUMAREA_UPDATE_SUPPORT} eq "yes"){
print "ro.gn.gioneenumareaupdate.prop=$ENV{GN_APP_NUMAREA_UPDATE_SUPPORT}\n";
}
#Gionee fangbin 20120511 added for GIUI4.0 CR00555786 end

#gionee zhouyj 2012-04-17 add for CR00556198 start
if (exists $ENV{GN_EMAIL_SUPPORT} && $ENV{GN_EMAIL_SUPPORT} eq "yes"){
print "ro.gn.email.prop=$ENV{GN_EMAIL_SUPPORT}\n";
}
#gionee zhouyj 2012-04-17 add for CR00556198 end

#Gionee gaoj 2011-12-26 added for CR00479542 start
if (exists $ENV{GN_EMPTY_COMMONCONTACT} && $ENV{GN_EMPTY_COMMONCONTACT} eq "yes"){
print "ro.gn.empty.commoncontact=$ENV{GN_EMPTY_COMMONCONTACT}\n";
}
#Gionee gaoj 2011-12-26 added for CR00479542 end

#Gionee:tianliang 2012.11.1 modify for  CR00724340 start 
if (exists $ENV{GN_MUSIC_FILTRATION_SUPPORT} && $ENV{GN_MUSIC_FILTRATION_SUPPORT} eq "yes") 
{
    print "ro.gn.filtration.suport=$ENV{GN_MUSIC_FILTRATION_SUPPORT}\n";
}
#Gionee:tianliang 2012.11.1 modify for  CR00724340 end 

#Gionee huyuke 2012-9-29  add for CR00705805 begin
if (exists $ENV{GN_GIONEE_GALLERY_SUPPORT} && $ENV{GN_GIONEE_GALLERY_SUPPORT} eq "yes")
{
    print "ro.gn.gallery=$ENV{GN_GIONEE_GALLERY_SUPPORT}\n";
}   
#Gionee huyuke 2012-9-29  add for CR00705805 end

#Gionee: lvxp 20120425 add for setting ota update flag start 
if (exists $ENV{GN_SETTING_OTA_UPDATE_SUPPORT} && $ENV{GN_SETTING_OTA_UPDATE_SUPPORT} eq "yes") 
{ 
    print "ro.gn.gnotaupdate.support=$ENV{GN_SETTING_OTA_UPDATE_SUPPORT}\n";
}
#Gionee: lvxp 20120425 add for setting ota update flag end

# Gionee chenql 2103-1-12 add for CR00763487 begin
if (exists $ENV{GN_THEME_SPECIAL_DISPLAY_SUPPORT}) {
   print "ro.gn.theme.display=$ENV{GN_THEME_SPECIAL_DISPLAY_SUPPORT}\n";
}
# Gionee chenql 2103-1-12 add for CR00763487 end

#Gionee: zhanglina 2012-12-28 modify for hide theme begin
if (exists $ENV{GN_OVERSEA_HIDE_THEME_ENTRANCE} && $ENV{GN_OVERSEA_HIDE_THEME_ENTRANCE} eq "yes") 
{
    print "ro.gn.hide.theme.entrance=$ENV{GN_OVERSEA_HIDE_THEME_ENTRANCE}\n";
}
#Gionee: zhanglina 2012-12-28 modify for hide theme end

#Gionee kangjj 2012-9-29 add for CR00710946 start
if (exists $ENV{GN_MMS_ONLINE_SUPPORT} && $ENV{GN_MMS_ONLINE_SUPPORT} eq "yes")
{
    print "ro.gn.mms.online.support=$ENV{GN_MMS_ONLINE_SUPPORT}\n";
}
#Gionee kangjj 2012-9-29 add for CR00710946 end

#Gionee liuyanbo 20120820 add for CR00680327 start
if ($ENV{GN_NETWORKALERT_SUPPORT} eq "yes")
{
    print "ro.gn.networkalert.support=$ENV{GN_NETWORKALERT_SUPPORT}\n";
}   
#Gionee liuyanbo 20120820 add for CR00680327  end

#Gionee chenxiong 2013-02-03 add for CR00770989 begin
if (exists $ENV{GN_NOT_DISPLAY_REMOVED_APP_SUPPORT} && $ENV{GN_NOT_DISPLAY_REMOVED_APP_SUPPORT} eq "yes") 
{
    print "ro.gn.notdisplay.removedapp=$ENV{GN_NOT_DISPLAY_REMOVED_APP_SUPPORT}\n";
}
#Gionee chenxiong 2013-02-03 add for CR00770989 end

#gionee zhouyj 2012-11-03 add for CR00724293 start
if (exists $ENV{GN_CELL_CONN_PLATFORM_4_1_SUPPORT} && $ENV{GN_CELL_CONN_PLATFORM_4_1_SUPPORT} eq "yes")
{ 
    print "ro.gn.cell.conn.platform.4.1=$ENV{GN_CELL_CONN_PLATFORM_4_1_SUPPORT}\n";
}
#gionee zhouyj 2012-11-03 add for CR00724293 end

#Gionee Jingjc 20120807 modify for CR00663406 start
if (exists $ENV{GN_CHECK_AUTO_TIME} && $ENV{GN_CHECK_AUTO_TIME} eq "yes") 
{
    print "ro.gn.check.autotime.prop=$ENV{GN_CHECK_AUTO_TIME}\n";
}
#Gionee Jingjc 20120807 modify for CR00663406 end

#Gionee huangzy 2012-10-11 add for CR00710695 start
if (exists $ENV{GN_CONTACTS_GNDIALERSEARCH} && $ENV{GN_CONTACTS_GNDIALERSEARCH} eq "yes"){
print "ro.gn.contacts.gndialersearch=$ENV{GN_CONTACTS_GNDIALERSEARCH}\n";
}
#Gionee huangzy 2012-10-11 add for CR00710695 end

#cancel context menu
if(exists $ENV{GN_MENU_CANCEL_SUPPORT} && $ENV{GN_MENU_CANCEL_SUPPORT} eq "yes"){
print "ro.gn.menu.cancel=$ENV{GN_MENU_CANCEL_SUPPORT}\n";
}
#Gionee:xufei 20110731 add for CR00313562 start

#POP默认关閉
if (exists $ENV{GN_POP_DEFAULT_VALUE} && $ENV{GN_POP_DEFAULT_VALUE} eq "yes"){
print "ro.gn.popdefaultvalue.prop=$ENV{GN_POP_DEFAULT_VALUE}\n";
}
#gionee gaoj 2012-6-26 added for CR00626901 end

#Gionee lich 2012-08-31 add for CR00683085 start
if (exists $ENV{GN_POWERPROFILE_SUPPORT} && $ENV{GN_POWERPROFILE_SUPPORT} eq "yes"){
print "ro.gn.powerprofile.support=$ENV{GN_POWERPROFILE_SUPPORT}\n";
}
#Gionee lich 2012-08-31 add for CR00683085 end

#Gionee Jingjc 2012-6-29 add for CR00632151 start
if(exists $ENV{GN_SETTINGS_AUTOTIME_SUPPORT} && $ENV{GN_SETTINGS_AUTOTIME_SUPPORT} eq "yes") 
{
    print "ro.gn.settings.autotime.prop=$ENV{GN_SETTINGS_AUTOTIME_SUPPORT}\n";
}
#Gionee Jingjc 2012-6-29 add for CR00632151 end

#gionee huangwenting 20120611 add for CR00611813 begin
if (exists $ENV{GN_SINGLE_SCREEN_WALLPAPER_SUPPORT} && $ENV{GN_SINGLE_SCREEN_WALLPAPER_SUPPORT} eq "yes")
{
    print "ro.gn.singlescreen.support=$ENV{GN_SINGLE_SCREEN_WALLPAPER_SUPPORT}\n";
}
#gionee huangwenting 20120611 add for CR00611813 end

#Gionee gaoj 2012-10-30 add for CR00722769 start
if (exists $ENV{GN_SMS_RECIPIENT_LIMIT})
{
    print "ro.gn.sms.recipient.limit=$ENV{GN_SMS_RECIPIENT_LIMIT}\n";
}
#Gionee gaoj 2011-10-30 add for CR00722769 end

#gionee licheng 20120608 add for CR00622958 begin
if (exists $ENV{GN_SOUNDRECORDER_SUPPORT} && $ENV{GN_SOUNDRECORDER_SUPPORT} eq "yes")
{
    print "ro.gn.soundrecorder.support=$ENV{GN_SOUNDRECORDER_SUPPORT}\n";
}
#gionee licheng 20120608 add for CR00622958 end

if (exists $ENV{GN_PRODUCT_MANUFACTURER} && $ENV{GN_PRODUCT_MANUFACTURER} ne "")
{
    print "ro.product.manufacturer=$ENV{GN_PRODUCT_MANUFACTURER}\n";
}
#Gionee:xuwen 20110914 modified end

#Gionee 20130308 chenrui add for CRCR00780313 start
if (exists $ENV{GN_LAUNCHER_TOOLBAR_APP_MARKET_SUPPORT} && $ENV{GN_LAUNCHER_TOOLBAR_APP_MARKET_SUPPORT} eq "yes") 
{
    print "ro.gn.launcher.toolbarappmarket=$ENV{GN_LAUNCHER_TOOLBAR_APP_MARKET_SUPPORT}\n";
}
#Gionee 20130308 chenrui add for CRCR00780313 end

#Gionee:zhanglina 20121212 add for CR00742359 start (merge CR00717589)
if (exists $ENV{GN_LAUNCHER_DOUBLE_LINE_TEXT_SUPPORT} && $ENV{GN_LAUNCHER_DOUBLE_LINE_TEXT_SUPPORT} eq "yes") 
{
    print "ro.gn.launcher.dblinetext=$ENV{GN_LAUNCHER_DOUBLE_LINE_TEXT_SUPPORT}\n";
}
#Gionee:zhanglina 20121212 add for CR00742359 start (merge CR00717589)

#GIONEE: lujian 2012.07.30 modify for "fly CR00793136" begin
if (exists $ENV{GN_OVERSEA_RUSSIA_FLY} && $ENV{GN_OVERSEA_RUSSIA_FLY} eq "yes") 
{
    print "ro.gn.fly.version.number=$ENV{GN_FLY_VERSION_NUMBER}\n";
}
#GIONEE: lujian 2012.07.30 modify for "fly CR00793136"   end

#Gionee: wangfei 2013-04-10 modify for CR00795699 begin
if (exists $ENV{GN_SETTINGS_DEVELOPER_OPTIONS_SUPPORT} && $ENV{GN_SETTINGS_DEVELOPER_OPTIONS_SUPPORT} eq "yes") 
{
    print "ro.gn.developeroption.support=$ENV{GN_SETTINGS_DEVELOPER_OPTIONS_SUPPORT}\n";
}
#Gionee: wangfei 2013-04-10 modify for CR00795699 end

# Gionee lixiaohu 2012.9.6 add for CR00688166 start->yuanqingqing merge in CR00795231
if ($ENV{GN_CALLLOG_COMBINE_MATCH_NUMBER_SUPPORT} eq "yes") 
{
    print "ro.gn.calllog.combinenumber=$ENV{GN_CALLLOG_COMBINE_MATCH_NUMBER_SUPPORT}\n";
}
# Gionee lixiaohu 2012.9.6 add for CR00688166 end->yuanqingqing merge in CR00795231

#GIONEE: lujian 2013.04.11 modify for "fly CR00791471" begin
if (exists $ENV{GN_EXTERNAL_MODEL_SUPPORT}) 
{
    print "ro.gn.extmodel.support=$ENV{GN_EXTERNAL_MODEL_SUPPORT}\n";
}
#GIONEE: lujian 2012.07.30 modify for "fly CR00791471"   end

#GIONEE:wangmeng 20130808 modify for strict mode. CR00850109 begin
print "persist.sys.strictmode.disable=1\n";
print "persist.sys.strictmode.visual=0\n";
#GIONEE:wangmeng 20130808 modify for strict mode. CR00850109 end

#GIONEE:xuml 20130814 modify for ril mode. CR00850088 begin
print "persist.radio.oem_socket=1\n";
#GIONEE:xuml 20130814 modify for ril mode. CR00850088 end

# Gionee lihuafang 2013-06-14 add for CR00826289 begin
if (exists $ENV{GN_SOUND_CONTROL_SUPPORT} && $ENV{GN_SOUND_CONTROL_SUPPORT} eq "yes") 
{
  print "ro.gn.soundctrl.support=$ENV{GN_SOUND_CONTROL_SUPPORT}\n";
}
# Gionee lihuafang 2013-06-14 add for CR00826289 end

#Gionee zhonggj 20130826 add for CR00873835 start
if (exists $ENV{GN_SUSPENDBUTTON_SUPPORT} && $ENV{GN_SUSPENDBUTTON_SUPPORT} eq "yes")
{
    print "ro.gn.suspendbutton.support=$ENV{GN_SUSPENDBUTTON_SUPPORT}\n";
}
if (exists $ENV{GN_OPERATION_SUPPORT} && $ENV{GN_OPERATION_SUPPORT} eq "yes")
{
    print "ro.gn.operation.support=$ENV{GN_OPERATION_SUPPORT}\n";
}
#Gionee zhonggj 20130826 add for CR00873835 end

#GIONEE:zhangzs 20130916 add for CR00901013 begin
print "persist.camera.is.setting=2\n";
#GIONEE:zhangzs 20130916 add for CR00901013 end

# Gionee <daizm> <2013-10-11> add for CTA Permission begin
if ($ENV{GN_CTA_SEC_SUPPORT} eq "yes")
{
    print "ro.gn.ctasec.support=$ENV{GN_CTA_SEC_SUPPORT}\n";
}
# Gionee <daizm> <2013-10-11> add for CTA Permission end

#<Gionee> <auto-time> <zhonggj> add for CR01096981 start
if (exists $ENV{GN_CHECK_AUTOTIME_PROP} && $ENV{GN_CHECK_AUTOTIME_PROP} eq "yes") 
{
    print "#ro.gn.check.autotime.prop=$ENV{GN_CHECK_AUTOTIME_PROP}\n";
}
#<Gionee> <auto-time> <zhonggj> add for CR01096981 end
#Gionee bug jiantf 2014-3-18 add for CR01099667 begin
if (exists $ENV{GN_QMI_RIL_SYS_PROP_RAT_OPTION}){
    print "persist.radio.rat_on=$ENV{GN_QMI_RIL_SYS_PROP_RAT_OPTION}\n";
}
#Gionee bug jiantf 2014-3-18 add for CR01099667 end

#Gionee liuxw 2014-06-07 add for radio config begin
if (exists $ENV{GN_RADIO_DEFAULT_NETWORK}){
    print "ro.telephony.default_network=$ENV{GN_RADIO_DEFAULT_NETWORK}\n";
}

if (exists $ENV{GN_RADIO_MULTISIM_CONFIG}){
    print "persist.radio.multisim.config=$ENV{GN_RADIO_MULTISIM_CONFIG}\n";
}

if (exists $ENV{GN_RADIO_RESTORE_MODE_PREF_ENABLE}){
    print "persist.radio.restore_mode_pref=$ENV{GN_RADIO_RESTORE_MODE_PREF_ENABLE}\n";
}
#Gionee liuxw 2014-06-07 add for radio config end

#Gionee <LogKit> <wangmeng> <20140408> modify for CR01173526.begin
if (exists $ENV{GN_PRODUCT_PLATFORM} && $ENV{GN_PRODUCT_PLATFORM} eq "QCOM"){
    if (exists $ENV{GN_QC_LOGKIT_QUIET_SUPPORT} && $ENV{GN_QC_LOGKIT_QUIET_SUPPORT} eq "yes"){
        print "persist.sys.logkit.ctrlcode=0\n";
    }
    else{
        print "persist.sys.logkit.ctrlcode=1\n";
    }
}
#Gionee <LogKit> <wangmeng> <20140408> modify for CR01173526.end

exit 0;
