LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_SRC_FILES:= \
    gionee_factorytest_jni.cpp \
    jni_onload.cpp

LOCAL_SHARED_LIBRARIES := \
     libandroid_runtime \
	libhardware \
	libnativehelper \
	libutils \
	libcutils \
	libui \
	libft_api 


LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES += \
    system/factorytest

LOCAL_LDLIBS += -ldl

LOCAL_MODULE:= libfactorytest_bt_jni

include $(BUILD_SHARED_LIBRARY)
