LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= ArcSoftCameraFeature.cpp \
				  ArcSoftNightShot.cpp \
				  ArcSoftSceneDetection.cpp \
				  ArcSoftFaceBeauty.cpp \
				  ArcSoftGestureShot.cpp \
				  ArcSoftLiveEffect.cpp \
				  ArcSoftFaceProcess.cpp \
				  ArcSoftAgeGenderDetection.cpp \
				  ArcSoftPicZoom.cpp

#Gionee <zhangwu><2013-08-14> modify for CR00854504 begin
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
#Gionee <zhangwu><2013-08-14> modify for CR00854504 end

LOCAL_MODULE:= libarcsoft

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/include \
	$(TOP)/external/libgn_camera_feature/include 

ifeq "$(strip $(GN_ARCSOFT_FEATURE_SUPPORT))" "yes"
include $(BUILD_STATIC_LIBRARY)
endif

include $(CLEAR_VARS)
arcsoft_maskfiles := $(LOCAL_PATH)/maskfile
DIRS := $(addprefix $(TARGET_OUT)/, etc/gn_camera_feature/arcsoft/maskfile)

$(DIRS):
	@echo Directory : $@
	@mkdir -p $@
	@cp -rf $(arcsoft_maskfiles)/* $@

ifeq "$(strip $(GN_ARCSOFT_FEATURE_SUPPORT))" "yes"
ALL_PREBUILT += $(DIRS)
endif
