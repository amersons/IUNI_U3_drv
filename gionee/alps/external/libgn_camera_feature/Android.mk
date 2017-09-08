LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS:= optional

LOCAL_SRC_FILES:= GNCameraFeature.cpp \
                  GNCameraFeatureBase.cpp 

LOCAL_MODULE:= libgn_camera_feature

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include 

#Gionee <zhangwu><2013-08-14> modify for CR00854504 begin
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS = -Wall -Wno-error
#Gionee <zhangwu><2013-08-14> modify for CR00854504 end

LOCAL_SHARED_LIBRARIES:= \
    libutils \
    libcutils \
	libcamera_client

LOCAL_SCALADO_LIB_ROOT_PATH:= $(LOCAL_PATH)/scalado/bin
LOCAL_LDFLAGS += \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmhdr2.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmlowlight.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmlowligt.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmphotoart.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmexif.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmautorama.a  \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/baseapi.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/excodecs.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmspeedview.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/codecs.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/capseng.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/facedetector.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmface.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/libFace.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmlocaltimewarp.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/osl_gcc.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmclearshot.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmextencoder.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmfacebeautification.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmimageenhance.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmimagefusion.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmjpegsqueeze.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/fmjpegtools.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/libFB.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/oslansi.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/oslbase.a \
	$(LOCAL_SCALADO_LIB_ROOT_PATH)/render2d_opengl.a

LOCAL_ARCSOFT_LIB_ROOT_PATH:= $(LOCAL_PATH)/arcsoft/bin
LOCAL_LDFLAGS += \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_piczoom.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_victorysign.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_vsign_detection.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_beautyshot.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_flawless_face.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_eyeoutline.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_makeup_common.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_teeth_whitening.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_iyounger.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_anti_shine.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_eye_brightening.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_skin_soften.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_skin_complexion.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_facesalon_common.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_skin_extract.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_faceoutline.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_funnybase.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libpuzzle.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_agegender_estimation.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_mobilecv.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_face_detection.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_face_tracking.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_face_base.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libasdplugin.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_asd.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_night_shot.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libarcsoft_dynamic_light.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libamipengine.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libampostprocess.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libamimageprocess.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libmtpng.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libmtzlib.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libmpkernel.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libmputility.a \
	$(LOCAL_ARCSOFT_LIB_ROOT_PATH)/libmpbase.a \


LOCAL_CRUNCHFISH_LIB_ROOT_PATH:= $(LOCAL_PATH)/crunchfish/bin
LOCAL_LDFLAGS += \
	$(LOCAL_CRUNCHFISH_LIB_ROOT_PATH)/libtouchless_a3d.so

ifeq "$(strip $(GN_SCALADO_FEATURE_SUPPORT))" "yes"
LOCAL_C_INCLUDES += $(LOCAL_PATH)/scalado/include
LOCAL_STATIC_LIBRARIES += libscalado
endif

ifeq "$(strip $(GN_ARCSOFT_FEATURE_SUPPORT))" "yes" 
LOCAL_C_INCLUDES += $(LOCAL_PATH)/arcsoft/include
LOCAL_STATIC_LIBRARIES += libarcsoft
endif

ifeq "$(strip $(GN_CRUNCHFISH_FEATURE_SUPPORT))" "yes" 
LOCAL_C_INCLUDES += $(LOCAL_PATH)/crunchfish/include
LOCAL_STATIC_LIBRARIES += libcrunchfish
endif

ifeq "$(strip $(GN_CAMERA_FEATURE_SUPPORT))" "yes"
include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
endif



