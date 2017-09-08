PREBUILT_PATH := $(call my-dir)
LOCAL_PATH         := $(PREBUILT_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE        := qlogd
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/xbin/qlogd
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/xbin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := cnd
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/cnd
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lowi_test
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/lowi_test
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := profiler_daemon
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/profiler_daemon
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lowi-server
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/lowi-server
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := mcStarter
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/mcStarter
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := xtwifi-inet-agent
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/xtwifi-inet-agent
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := quipc_igsn
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/quipc_igsn
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := adsprpcd
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/adsprpcd
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := quipc_main
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/quipc_main
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := nqs
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/nqs
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := hvdcp
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/hvdcp
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := imsqmidaemon
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/imsqmidaemon
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := StoreKeybox
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/StoreKeybox
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := charger_monitor
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/charger_monitor
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := xtwifi-client
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/xtwifi-client
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := ims_rtp_daemon
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/ims_rtp_daemon
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := location-mq
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/location-mq
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := imsdatadaemon
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/imsdatadaemon
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := oemprtest
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/oemprtest
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := drmdiagapp
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/drmdiagapp
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := qosmgr
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/bin/qosmgr
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/bin
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := PresenceApp
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/PresenceApp.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := SVIService
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/SVIService.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := com.qualcomm.msapm
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/com.qualcomm.msapm.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

ifneq ("$(APK_DEFAULT_MSAPU_SUPPORT)", "no")
include $(CLEAR_VARS)
LOCAL_MODULE        := com.qualcomm.msapu
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/com.qualcomm.msapu.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)
endif


include $(CLEAR_VARS)
LOCAL_MODULE        := RcsImsBootstraputil
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/RcsImsBootstraputil.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := RCSBootstraputil
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/RCSBootstraputil.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := com.qualcomm.services.location
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/com.qualcomm.services.location.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := CABLService
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/CABLService.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

ifneq ("$(APK_DEFAULT_DLT_SUPPORT)", "no")
include $(CLEAR_VARS)
LOCAL_MODULE        := ODLT
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/ODLT.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)
endif

include $(CLEAR_VARS)
LOCAL_MODULE        := Logkit
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/Logkit.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := xtra_t_app
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/xtra_t_app.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)

ifneq ("$(APK_DEFAULT_QLOGCAT_SUPPORT)", "no")
include $(CLEAR_VARS)
LOCAL_MODULE        := com.qualcomm.qlogcat
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/app/com.qualcomm.qlogcat.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/app
include $(BUILD_PREBUILT)
endif

include $(CLEAR_VARS)
LOCAL_MODULE        := qlog-conf.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/qlog-conf.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := qosmgr_rules.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/qosmgr_rules.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := SwimConfig.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/cne/SwimConfig.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/cne
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := NsrmConfiguration.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/cne/NsrmConfiguration.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/cne
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := andsfCne.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/cne/andsfCne.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/cne
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := quipc.conf
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/quipc.conf
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := cneapiclient.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/permissions/cneapiclient.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/permissions
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := rcsservice.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/permissions/rcsservice.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/permissions
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := com.qualcomm.qmapbridge.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/permissions/com.qualcomm.qmapbridge.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/permissions
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := rcsimssettings.xml
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/permissions/rcsimssettings.xml
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/permissions
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := xtwifi.conf
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/xtwifi.conf
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := msap.conf
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/msap.conf
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := leia_pm4_470.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/leia_pm4_470.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.b00
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.b00
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := leia_pfp_470.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/leia_pfp_470.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.b04
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.b04
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.mdt
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.mdt
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a300_pfp.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a300_pfp.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.mbn
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.mbn
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a225p5_pm4.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a225p5_pm4.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a330_pfp.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a330_pfp.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.b03
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.b03
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a300_pm4.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a300_pm4.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a225_pfp.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a225_pfp.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.b02
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.b02
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a330_pm4.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a330_pm4.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := a225_pm4.fw
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/a225_pm4.fw
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := venus.b01
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/firmware/venus.b01
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/firmware
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := xtra_root_cert.pem
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/xtra_root_cert.pem
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := dynamic_debug_mask.cfg
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/logmask/dynamic_debug_mask.cfg
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/logmask
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := default_diag_mask.cfg
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/logmask/default_diag_mask.cfg
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc/logmask
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lowi.conf
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/lowi.conf
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := cacert_location.pem
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := ETC
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/etc/cacert_location.pem
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/etc
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libfastcvadsp
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/rfsa/adsp/libfastcvadsp.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/rfsa/adsp
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libapps_mem_heap
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/rfsa/adsp/libapps_mem_heap.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/rfsa/adsp
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libfastcvadsp_skel
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/rfsa/adsp/libfastcvadsp_skel.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/rfsa/adsp
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libscveT2T_skel
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/rfsa/adsp/libscveT2T_skel.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/rfsa/adsp
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdspCV_skel
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/rfsa/adsp/libdspCV_skel.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/rfsa/adsp
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libgeofence
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libgeofence.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libloc2jnibridge
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libloc2jnibridge.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := librs_adreno_sha1
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/librs_adreno_sha1.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libgsl
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libgsl.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imscamera
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imscamera.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libadreno_utils
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libadreno_utils.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rtpsl
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rtpsl.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libxtwifi_zpp_adaptor
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libxtwifi_zpp_adaptor.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libSHIMDivxDrm
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libSHIMDivxDrm.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := liblistensoundmodel
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/liblistensoundmodel.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rtpcommon
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rtpcommon.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libizat_core
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libizat_core.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libOmxQcelp13Dec
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libOmxQcelp13Dec.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libq3dtools_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/egl/libq3dtools_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/egl
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libGLESv1_CM_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/egl/libGLESv1_CM_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/egl
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libGLESv2_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/egl/libGLESv2_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/egl
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := eglsubAndroid
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/egl/eglsubAndroid.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/egl
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libEGL_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/egl/libEGL_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/egl
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imss
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imss.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libDivxDrm
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libDivxDrm.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libOpenVG
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libOpenVG.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rcsimssjni
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rcsimssjni.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsecureuisvc_jni
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsecureuisvc_jni.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera2_stats_algorithm
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera2_stats_algorithm.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera2_frame_algorithm
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera2_frame_algorithm.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqc-opt
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libqc-opt.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libcneutils
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libcneutils.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libC2D2
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libC2D2.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libNimsWrap
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libNimsWrap.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmm-hdcpmgr
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmm-hdcpmgr.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rtpdaemoninterface
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rtpdaemoninterface.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libusutils
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libusutils.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libwifiscanner
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libwifiscanner.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libc2d2_z180
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libc2d2_z180.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsSDP
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsSDP.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmm-color-convertor
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmm-color-convertor.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := librs_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/librs_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdrmprplugin
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/drm/libdrmprplugin.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/drm
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera_hdr_gb_lib
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera_hdr_gb_lib.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libalarmservice_jni
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libalarmservice_jni.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libtzplayready
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libtzplayready.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rcsjni
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rcsjni.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libxt_native
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libxt_native.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libRSDriver_adreno
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libRSDriver_adreno.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libHevcSwDecoder
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libHevcSwDecoder.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdrmtime
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libdrmtime.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsecureui
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsecureui.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-dplmedia
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-dplmedia.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libscve
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libscve.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libc2d30
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libc2d30.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsqimf
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsqimf.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libc2d30-a4xx
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libc2d30-a4xx.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libcneapiclient
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libcneapiclient.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libOmxEvrcDec
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libOmxEvrcDec.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libllvm-qcom
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libllvm-qcom.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libadsprpc
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libadsprpc.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmQSM
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmQSM.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libI420colorconvert
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libI420colorconvert.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libSecureUILib
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libSecureUILib.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsrcs
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsrcs.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsvt
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsvt.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libquipc_ulp_adapter
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libquipc_ulp_adapter.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := liblowi_client
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/liblowi_client.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libxtwifi_ulp_adaptor
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libxtwifi_ulp_adaptor.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libfastcvopt
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libfastcvopt.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera_tintless_bg_pca_algo
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera_tintless_bg_pca_algo.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsdpl
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsdpl.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libxtadapter
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libxtadapter.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera_hdr_lib
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera_hdr_lib.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libQSEEComAPI
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libQSEEComAPI.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libprdrmdecrypt
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libprdrmdecrypt.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := librpmb
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/librpmb.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-rtpcore
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-rtpcore.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libscale
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libscale.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libscve_stub
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libscve_stub.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libssd
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libssd.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmsapm_jni
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmsapm_jni.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-imsxml
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-imsxml.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdrmfs
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libdrmfs.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libprofiler_msmadc
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libprofiler_msmadc.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libulp2
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libulp2.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdrmdiag
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libdrmdiag.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmm-abl
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmm-abl.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := liboemcrypto
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/liboemcrypto.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libOpenCL
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libOpenCL.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdisp-aba
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libdisp-aba.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libcneconn
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libcneconn.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libppl
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libppl.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqcvirt
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/soundfx/libqcvirt.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/soundfx
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqcreverb
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/soundfx/libqcreverb.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/soundfx
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqcbassboost
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/soundfx/libqcbassboost.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/soundfx
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsc-a2xx
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsc-a2xx.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera_wavelet_lib
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera_wavelet_lib.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmQTA
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmQTA.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := lib-sec-disp
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/lib-sec-disp.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libc2d30-a3xx
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libc2d30-a3xx.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libmmcamera_tintless_algo
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libmmcamera_tintless_algo.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libfastcvadsp_stub
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libfastcvadsp_stub.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := flp.default
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/hw/flp.default.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib/hw
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsecureui_svcsock
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsecureui_svcsock.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libCB
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libCB.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libepdsp
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libepdsp.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsrsprocessing
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsrsprocessing.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libdiagbridge
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libdiagbridge.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsc-a3xx
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libsc-a3xx.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := librmp
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/librmp.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libtzdrmgenprov
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libtzdrmgenprov.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libquipc_os_api
LOCAL_MODULE_CLASS  := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/system/vendor/lib/libquipc_os_api.so
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/system/vendor/lib
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqc-dalvik
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libqc-dalvik_intermediates/libqc-dalvik.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqc-mpctl
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libqc-mpctl_intermediates/libqc-mpctl.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqc-skia
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libqc-skia_intermediates/libqc-skia.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := liboemcrypto_L1
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/liboemcrypto_L1_intermediates/liboemcrypto_L1.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := liboemcrypto
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/liboemcrypto_intermediates/liboemcrypto.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqc-surfaceflinger
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libqc-surfaceflinger_intermediates/libqc-surfaceflinger.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libqsappsver
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libqsappsver_intermediates/libqsappsver.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libisdbtmm
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libisdbtmm_intermediates/libisdbtmm.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libloc_mq_client
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libloc_mq_client_intermediates/libloc_mq_client.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libASFParserLib
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libASFParserLib_intermediates/libASFParserLib.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libsensors_lib
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libsensors_lib_intermediates/libsensors_lib.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libloc_base_util
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libloc_base_util_intermediates/libloc_base_util.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE        := libQSEEComAPIStatic
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := STATIC_LIBRARIES
LOCAL_MODULE_SUFFIX := .a
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/obj/STATIC_LIBRARIES/libQSEEComAPIStatic_intermediates/libQSEEComAPIStatic.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := hdcp-mgr/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/hdcp-mgr/inc/hdcpmgr_api.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := pp/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/pp/inc/aba_type.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := pp/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/pp/inc/diagplatform.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := pp/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/pp/inc/aba_cabl.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := pp/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/pp/inc/aba_svi.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := pp/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/pp/inc/aba_core_api.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/opencl.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl_gl.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl_platform.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl_ext.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl_ext_qcom.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno/CL
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/CL/cl_gl_ext.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/c2dExt.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := adreno
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/adreno/c2d2.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := ultrasound/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/ultrasound/inc/eposexports.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := ultrasound/inc
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/ultrasound/inc/pplexports.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-audio/audio-listen
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-audio/audio-listen/ListenSoundModelLib.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libxtadapter
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libxtadapter/XtAdapter.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-camera
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-camera/dmlrocorrection_bg_pca.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-camera
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-camera/dmlrocorrection.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-video/SwVdec
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-video/SwVdec/SwVdecTypes.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-video/SwVdec
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-video/SwVdec/SwVdecAPI.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := fastcv
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/fastcv/fastcv.inl
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := fastcv
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/fastcv/fastcv.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/config_file.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/postcard.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/memorystream.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/queue.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/log.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/list.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/time_routines.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/base_util
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/base_util/sync.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libloc/mq_client
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libloc/mq_client/mq_client.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libizat_core
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libizat_core/IzatAdapterBase.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libizat_core
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libizat_core/IzatApiBase.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libizat_core
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libizat_core/IzatApiV02.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := libizat_core
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/libizat_core/IzatApiRpc.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := mm-color-convertor
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/mm-color-convertor/MMColorConvert.h
include $(BUILD_COPY_HEADERS)

include $(CLEAR_VARS)
LOCAL_COPY_HEADERS_TO := scale
LOCAL_COPY_HEADERS    := ../../.././target/product/msm8974/obj/include/scale/scale.h
include $(BUILD_COPY_HEADERS)

ifneq ("$(APK_DEFAULT_PLAYREADYDRMTESTING_SUPPORT)", "no")
include $(CLEAR_VARS)
LOCAL_MODULE        := PlayreadyDrmTesting
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/data/app/PlayreadyDrmTesting.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/data/app
include $(BUILD_PREBUILT)
endif

ifneq ("$(APK_DEFAULT_TREPN_SUPPORT)", "no")
include $(CLEAR_VARS)
LOCAL_MODULE        := Trepn
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := APPS
LOCAL_CERTIFICATE   := platform
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/data/app/Trepn.apk
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/data/app
include $(BUILD_PREBUILT)
endif


include $(CLEAR_VARS)
LOCAL_MODULE        := security_boot_check
LOCAL_MODULE_OWNER  := qcom
LOCAL_MODULE_TAGS   := optional
LOCAL_MODULE_CLASS  := EXECUTABLES
LOCAL_SRC_FILES     := ../../.././target/product/msm8974/root/sbin/security_boot_check
LOCAL_MODULE_PATH   := $(PRODUCT_OUT)/root/sbin
include $(BUILD_PREBUILT)
LOCAL_PATH         := $(PREBUILT_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE               := rcsimssettings
LOCAL_MODULE_OWNER         := qcom
LOCAL_MODULE_TAGS          := optional
LOCAL_MODULE_CLASS         := JAVA_LIBRARIES
LOCAL_MODULE_SUFFIX        := $(COMMON_JAVA_PACKAGE_SUFFIX)
LOCAL_SRC_FILES            := ../../.././target/common/obj/JAVA_LIBRARIES/rcsimssettings_intermediates/classes.jar
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE               := security-bridge
LOCAL_MODULE_OWNER         := qcom
LOCAL_MODULE_TAGS          := optional
LOCAL_MODULE_CLASS         := JAVA_LIBRARIES
LOCAL_MODULE_SUFFIX        := $(COMMON_JAVA_PACKAGE_SUFFIX)
LOCAL_SRC_FILES            := ../../.././target/common/obj/JAVA_LIBRARIES/security-bridge_intermediates/javalib.jar
ifeq ($(WITH_DEXPREOPT),true)
LOCAL_DEX_PREOPT           := true
endif
include $(BUILD_PREBUILT)
###################################################################
# Prebuilt dex optimized boot class jars are not handled by the
# Android Build System and generated odex files are not copied
# to /system/framework directory. Here defining rule to copy
# the generated odex file to /system/framework
###################################################################
ifeq ($(WITH_DEXPREOPT),true)
ifdef LOCAL_DEX_PREOPT
dexpreopt_boot_jar_module := $(filter $(LOCAL_MODULE),$(DEXPREOPT_BOOT_JARS_MODULES))
ifneq ($(dexpreopt_boot_jar_module),)
dexpreopted_boot_jar := $(DEXPREOPT_BOOT_JAR_DIR_FULL_PATH)/$(dexpreopt_boot_jar_module)_nodex.jar
$(LOCAL_BUILT_MODULE) : $(dexpreopted_boot_jar) | $(ACP)
	$(call copy-file-to-target)

dexpreopted_boot_odex := $(DEXPREOPT_BOOT_JAR_DIR_FULL_PATH)/$(dexpreopt_boot_jar_module).odex
built_odex := $(basename $(LOCAL_BUILT_MODULE)).odex
$(built_odex) : $(dexpreopted_boot_odex) | $(ACP)
	$(call copy-file-to-target)

else # dexpreopt_boot_jar_module
built_odex := $(basename $(LOCAL_BUILT_MODULE)).odex
$(built_odex): PRIVATE_MODULE := $(LOCAL_MODULE)
# Make sure the boot jars get dex-preopt-ed first
$(built_odex) : $(DEXPREOPT_BOOT_ODEXS)
$(built_odex) : $(common_javalib.jar) | $(DEXPREOPT) $(DEXOPT)
	@echo "Dexpreopt Jar: $(PRIVATE_MODULE) ($@)"
	$(hide) rm -f $@
	@mkdir -p $(dir $@)
	$(call dexpreopt-one-file,$<,$@)

$(LOCAL_BUILT_MODULE) : $(common_javalib.jar) | $(ACP) $(AAPT)
	$(call copy-file-to-target)
ifneq (nostripping,$(LOCAL_DEX_PREOPT))
	$(call dexpreopt-remove-classes.dex,$@)
endif

endif # dexpreopt_boot_jar_module
endif # LOCAL_DEX_PREOPT
endif # WITH_DEXPREOPT

include $(CLEAR_VARS)
LOCAL_MODULE               := rcsservice
LOCAL_MODULE_OWNER         := qcom
LOCAL_MODULE_TAGS          := optional
LOCAL_MODULE_CLASS         := JAVA_LIBRARIES
LOCAL_MODULE_SUFFIX        := $(COMMON_JAVA_PACKAGE_SUFFIX)
LOCAL_SRC_FILES            := ../../.././target/common/obj/JAVA_LIBRARIES/rcsservice_intermediates/classes.jar
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE               := cneapiclient
LOCAL_MODULE_OWNER         := qcom
LOCAL_MODULE_TAGS          := optional
LOCAL_MODULE_CLASS         := JAVA_LIBRARIES
LOCAL_MODULE_SUFFIX        := $(COMMON_JAVA_PACKAGE_SUFFIX)
LOCAL_SRC_FILES            := ../../.././target/common/obj/JAVA_LIBRARIES/cneapiclient_intermediates/classes.jar
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE               := qsb-port
LOCAL_MODULE_OWNER         := qcom
LOCAL_MODULE_TAGS          := optional
LOCAL_MODULE_CLASS         := JAVA_LIBRARIES
LOCAL_MODULE_SUFFIX        := $(COMMON_JAVA_PACKAGE_SUFFIX)
LOCAL_SRC_FILES            := ../../.././target/common/obj/JAVA_LIBRARIES/qsb-port_intermediates/javalib.jar
ifeq ($(WITH_DEXPREOPT),true)
LOCAL_DEX_PREOPT           := true
endif
include $(BUILD_PREBUILT)
###################################################################
# Prebuilt dex optimized boot class jars are not handled by the
# Android Build System and generated odex files are not copied
# to /system/framework directory. Here defining rule to copy
# the generated odex file to /system/framework
###################################################################
ifeq ($(WITH_DEXPREOPT),true)
ifdef LOCAL_DEX_PREOPT
dexpreopt_boot_jar_module := $(filter $(LOCAL_MODULE),$(DEXPREOPT_BOOT_JARS_MODULES))
ifneq ($(dexpreopt_boot_jar_module),)
dexpreopted_boot_jar := $(DEXPREOPT_BOOT_JAR_DIR_FULL_PATH)/$(dexpreopt_boot_jar_module)_nodex.jar
$(LOCAL_BUILT_MODULE) : $(dexpreopted_boot_jar) | $(ACP)
	$(call copy-file-to-target)

dexpreopted_boot_odex := $(DEXPREOPT_BOOT_JAR_DIR_FULL_PATH)/$(dexpreopt_boot_jar_module).odex
built_odex := $(basename $(LOCAL_BUILT_MODULE)).odex
$(built_odex) : $(dexpreopted_boot_odex) | $(ACP)
	$(call copy-file-to-target)

else # dexpreopt_boot_jar_module
built_odex := $(basename $(LOCAL_BUILT_MODULE)).odex
$(built_odex): PRIVATE_MODULE := $(LOCAL_MODULE)
# Make sure the boot jars get dex-preopt-ed first
$(built_odex) : $(DEXPREOPT_BOOT_ODEXS)
$(built_odex) : $(common_javalib.jar) | $(DEXPREOPT) $(DEXOPT)
	@echo "Dexpreopt Jar: $(PRIVATE_MODULE) ($@)"
	$(hide) rm -f $@
	@mkdir -p $(dir $@)
	$(call dexpreopt-one-file,$<,$@)

$(LOCAL_BUILT_MODULE) : $(common_javalib.jar) | $(ACP) $(AAPT)
	$(call copy-file-to-target)
ifneq (nostripping,$(LOCAL_DEX_PREOPT))
	$(call dexpreopt-remove-classes.dex,$@)
endif

endif # dexpreopt_boot_jar_module
endif # LOCAL_DEX_PREOPT
endif # WITH_DEXPREOPT
