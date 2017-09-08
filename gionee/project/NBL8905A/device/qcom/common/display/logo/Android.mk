LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional eng

$(info  python $(LOCAL_PATH)/logo_gen.py $(LOCAL_PATH)/$(BOOT_LOGO)/logo.png)

$(shell python $(LOCAL_PATH)/logo_gen.py $(LOCAL_PATH)/$(BOOT_LOGO)/logo.png)

#GIONEE: oversea del
#$(shell cp $(LOCAL_PATH)/splash.img $(PRODUCT_OUT))
