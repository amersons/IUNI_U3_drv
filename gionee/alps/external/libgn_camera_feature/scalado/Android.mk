LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= ScaladoLiveEffect.cpp \
                  ScaladoCameraFeature.cpp \
                  ScaladoHdrLowlight.cpp \
				  ScaladoPictureFrame.cpp \
				  ScaladoPanorama.cpp

LOCAL_MODULE:= libscalado

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/include \
	$(TOP)/external/libgn_camera_feature/include

ifeq "$(strip $(GN_SCALADO_FEATURE_SUPPORT))" "yes"
include $(BUILD_STATIC_LIBRARY)
endif

include $(CLEAR_VARS)
scalado_warp_files := $(LOCAL_PATH)/warp
DIRS := $(addprefix $(TARGET_OUT)/, etc/gn_camera_feature/scalado/warp)

$(DIRS):
	@echo Directory : $@
	@mkdir -p $@
	@cp -rf $(scalado_warp_files)/* $@

ifeq "$(strip $(GN_SCALADO_FEATURE_SUPPORT))" "yes"
ALL_PREBUILT += $(DIRS)
endif
