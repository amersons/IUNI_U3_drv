LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libAK8975/libAK8975.a
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/libAK8975
LOCAL_SRC_FILES += \
	AKMD_APIs.c \
	FileIO.c \
	Measure.c

LOCAL_WHOLE_STATIC_LIBRARIES += libAK8975
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_MODULE:=libAKM8975
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
