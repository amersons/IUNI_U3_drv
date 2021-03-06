TARGET_USES_QCOM_BSP := true
#Gionee wangzhen 2014-07-16 we don't use QCA NFC chip begin
TARGET_USES_QCA_NFC := false
#Gionee wangzhen 2014-07-16 we don't use QCA NFC chip end

ifeq ($(TARGET_USES_QCOM_BSP), true)
# Add QC Video Enhancements flag
TARGET_ENABLE_QC_AV_ENHANCEMENTS := true
#TARGET_ENABLE_DEFAULT_SMOOTHSTREAMING := true
endif #TARGET_USES_QCOM_BSP

#TARGET_DISABLE_DASH := true
#TARGET_DISABLE_OMX_SECURE_TEST_APP := true

# media_profiles and media_codecs xmls for 8974
ifeq ($(TARGET_ENABLE_QC_AV_ENHANCEMENTS), true)
PRODUCT_COPY_FILES += device/qcom/msm8974/media/media_profiles_8974.xml:system/etc/media_profiles.xml \
                      device/qcom/msm8974/media/media_codecs_8974.xml:system/etc/media_codecs.xml
endif  #TARGET_ENABLE_QC_AV_ENHANCEMENTS

#Gionee 20140930 huangrh add for CR01392847 start
PRODUCT_COPY_FILES += device/qcom/msm8974/GN_Google_Supl_Certificate_Geo.cer:/system/etc/supl/GN_Google_Supl_Certificate_Geo.cer
#Gionee 20140930 huangrh add for CR01392847 end

$(call inherit-product, device/qcom/common/common.mk)

PRODUCT_NAME := msm8974
PRODUCT_DEVICE := msm8974

PRODUCT_BOOT_JARS += qcmediaplayer:WfdCommon:oem-services:org.codeaurora.Performance:qcom.fmradio:security-bridge:qsb-port:vcard
###add by wangyongliang
PRODUCT_BOOT_JARS += gnframework:aurora-framework:qcrilhook:qcnvitems
###end by wangyongliang

# Audio configuration file
PRODUCT_COPY_FILES += \
    device/qcom/msm8974/audio_policy.conf:system/etc/audio_policy.conf \
    device/qcom/msm8974/audio_effects.conf:system/vendor/etc/audio_effects.conf \
    device/qcom/msm8974/mixer_paths.xml:system/etc/mixer_paths.xml \
    device/qcom/msm8974/mixer_paths_auxpcm.xml:system/etc/mixer_paths_auxpcm.xml

PRODUCT_PACKAGES += \
    libqcomvisualizer \
    libqcomvoiceprocessing \
    libqcompostprocbundle

# Feature definition files for 8974
PRODUCT_COPY_FILES += \
    system/bluetooth/data/main.le.conf:system/etc/bluetooth/main.conf \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.sensor.barometer.xml:system/etc/permissions/android.hardware.sensor.barometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepcounter.xml:system/etc/permissions/android.hardware.sensor.stepcounter.xml \
    frameworks/native/data/etc/android.hardware.sensor.stepdetector.xml:system/etc/permissions/android.hardware.sensor.stepdetector.xml

#Gionee liusb 2014-9-25 add for tp img update
PRODUCT_COPY_FILES += device/qcom/msm8974/PR1698117_s7020_8905_OB_00000008.img:system/etc/firmware/PR1698117_s7020_8905_OB_00000008.img
PRODUCT_COPY_FILES += device/qcom/msm8974/PR1698117_s7020_8905_OW_00000008.img:system/etc/firmware/PR1698117_s7020_8905_OW_00000008.img
PRODUCT_COPY_FILES += device/qcom/msm8974/PR1698117_s7020_8905_TB_00000008.img:system/etc/firmware/PR1698117_s7020_8905_TB_00000008.img
PRODUCT_COPY_FILES += device/qcom/msm8974/PR1698117_s7020_8905_TW_00000008.img:system/etc/firmware/PR1698117_s7020_8905_TW_00000008.img

#battery_monitor
PRODUCT_PACKAGES += \
    battery_monitor \
    battery_shutdown

#fstab.qcom
PRODUCT_PACKAGES += fstab.qcom
#Gionee wangzhen 2013-09-17 add wifi test tool for cta test begin
#PRODUCT_COPY_FILES += system/factorytest/iwmulticall:system/bin/iwmulticall
#PRODUCT_COPY_FILES += system/factorytest/ptt_socket_app:system/bin/ptt_socket_app
#PRODUCT_COPY_FILES += system/factorytest/btconfig:system/bin/btconfig
#Gionee wangzhen 2013-09-17 add wifi test tool for cta test end
#wlan driver
PRODUCT_COPY_FILES += \
    device/qcom/msm8974/WCNSS_qcom_cfg.ini:system/etc/wifi/WCNSS_qcom_cfg.ini \
    device/qcom/msm8974/WCNSS_qcom_wlan_nv.bin:persist/WCNSS_qcom_wlan_nv.bin

PRODUCT_PACKAGES += \
    wpa_supplicant_overlay.conf \
    p2p_supplicant_overlay.conf

PRODUCT_PACKAGES += wcnss_service

#ANT stack
PRODUCT_PACKAGES += \
        AntHalService \
        libantradio \
        ANTRadioService \
        antradio_app

# Enable strict operation
PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.strict_op_enable=false

PRODUCT_DEFAULT_PROPERTY_OVERRIDES += \
    persist.sys.whitelist=/system/etc/whitelist_appops.xml

PRODUCT_COPY_FILES += \
    device/qcom/msm8974/whitelist_appops.xml:system/etc/whitelist_appops.xml


# NFC packages
ifeq ($(TARGET_USES_QCA_NFC),true)
NFC_D := true

ifeq ($(NFC_D), true)
    PRODUCT_PACKAGES += \
        libnfcD-nci \
        libnfcD_nci_jni \
        nfc_nci.msm8974 \
        NfcDNci \
        Tag \
        com.android.nfc_extras \
        com.android.nfc.helper
else
PRODUCT_PACKAGES += \
    libnfc-nci \
    libnfc_nci_jni \
    nfc_nci.msm8974 \
    NfcNci \
    Tag \
    com.android.nfc_extras
endif

# file that declares the MIFARE NFC constant
# Commands to migrate prefs from com.android.nfc3 to com.android.nfc
# NFC access control + feature files + configuration
PRODUCT_COPY_FILES += \
        packages/apps/Nfc/migrate_nfc.txt:system/etc/updatecmds/migrate_nfc.txt \
        frameworks/native/data/etc/com.nxp.mifare.xml:system/etc/permissions/com.nxp.mifare.xml \
        frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml \
        frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml
endif

#iuni wolfu add for recovery
#PRODUCT_COPY_FILES += \
#    device/qcom/msm8974/recovery.img:recovery.img
