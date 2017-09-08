ifneq ("$(APK_DEFAULT_INCALLUI_SUPPORT)", "no")

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_STATIC_JAVA_LIBRARIES := com.android.services.telephony.common \
        guava \

LOCAL_JNI_SHARED_LIBRARIES := libvt_jni libimscamera_jni
LOCAL_REQUIRED_MODULES := libvt_jni libimscamera_jni

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := InCallUI
LOCAL_CERTIFICATE := platform
LOCAL_PRIVELEGED_MODULE := false

LOCAL_PROGUARD_FLAG_FILES := proguard.flags

include $(BUILD_PACKAGE)

# Build the test package
include $(call all-makefiles-under,$(LOCAL_PATH))

endif
