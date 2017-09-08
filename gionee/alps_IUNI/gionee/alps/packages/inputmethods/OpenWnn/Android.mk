ifneq ("$(APK_DEFAULT_OPENWNN_SUPPORT)", "no")

ifeq ("$(GN_JANPANESEINPUTMETHOD_SUPPORT)","yes")

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := OpenWnn

LOCAL_JNI_SHARED_LIBRARIES := \
	 libWnnEngDic libWnnJpnDic libwnndict

LOCAL_AAPT_FLAGS += -c hdpi

include $(BUILD_PACKAGE)

include $(call all-makefiles-under,$(LOCAL_PATH))

endif

endif
