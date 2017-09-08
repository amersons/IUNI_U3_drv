LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= \
	CrunchfishCameraFeature.cpp \

LOCAL_MODULE:= libcrunchfish

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/include \
	$(TOP)/external/libgn_camera_feature/include 

PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/bin/libtouchless_a3d.so:system/lib/libtouchless_a3d.so

ifeq "$(strip $(GN_CRUNCHFISH_FEATURE_SUPPORT))" "yes"
include $(BUILD_STATIC_LIBRARY)
endif
