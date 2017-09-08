$(info kkkkk$(APK_DEFAULT_SMS_SUPPORT)kkkkk) 

ifneq ("$(APK_DEFAULT_SMS_SUPPORT)", "no")



kkkkkkk
# Copyright 2007-2008 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
# Include res dir from chips
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#chips_dir := ../../../frameworks/ex/chips/res
#res_dirs := $(chips_dir) res

chips_dir := $(PWD)/frameworks/ex/chips/res
res_dirs := res
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

$(shell rm -f $(LOCAL_PATH)/chips)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := Mms

# Builds against the public SDK
#LOCAL_SDK_VERSION := current

LOCAL_JAVA_LIBRARIES += telephony-common mms-common
LOCAL_STATIC_JAVA_LIBRARIES += android-common jsr305
LOCAL_STATIC_JAVA_LIBRARIES += android-common-chips

#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dirs))
LOCAL_RESOURCE_DIR := $(chips_dir) $(addprefix $(LOCAL_PATH)/, $(res_dirs))
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end
LOCAL_AAPT_FLAGS := --auto-add-overlay
LOCAL_AAPT_FLAGS += --extra-packages com.android.ex.chips

LOCAL_REQUIRED_MODULES := SoundRecorder

LOCAL_PROGUARD_FLAG_FILES := proguard.flags

LOCAL_PRIVILEGED_MODULE := true

include $(BUILD_PACKAGE)

# This finds and builds the test apk as well, so a single make does both.
include $(call all-makefiles-under,$(LOCAL_PATH))

endif
