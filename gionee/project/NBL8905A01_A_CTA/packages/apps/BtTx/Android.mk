LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := BtTx

LOCAL_CERTIFICATE := platform

#LOCAL_STATIC_JAVA_LIBRARIES := libcommons-net

LOCAL_JNI_SHARED_LIBRARIES := libfactorytest_bt_jni

LOCAL_REQUIRED_MODULES := libfactorytest_bt_jni

include $(BUILD_PACKAGE)

#include $(CLEAR_VARS)
#LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := libcommons-net:lib/commons-net-3.0.1.jar
#include $(BUILD_MULTI_PREBUILT)

include $(call all-makefiles-under,$(LOCAL_PATH))
