#Gionee chuqf 2014-07-03 for cdrom, begin
ifeq ($(GN_CDROM_SUPPORT), y)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

PRODUCT_COPY_FILES += $(LOCAL_PATH)/DriverSetup.iso:system/mobile_toolkit/DriverSetup.iso

endif
#Gionee chuqf 2014-07-03 for cdrom, end
