ifneq ("$(APK_DEFAULT_VOICEDIALER_SUPPORT)", "no")

#Gionee <lairufei><20131116> add for CR00947932 begin
ifeq ("$(GN_APK_VOICEDIALER_SUPPORT)","yes")
#Gionee <lairufei><20131116> add for CR00947932 end
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src) \

LOCAL_PACKAGE_NAME := VoiceDialer

LOCAL_REQUIRED_MODULES := libsrec_jni

LOCAL_PRIVILEGED_MODULE := true

include $(BUILD_PACKAGE)

# Install the srec data files if VoiceDialer.apk is installed to system image.
include external/srec/config/en.us/config.mk
$(LOCAL_INSTALLED_MODULE) : | $(SREC_CONFIG_TARGET_FILES)
# SREC_CONFIG_TARGET_FILES is from external/srec/config/en.us/config.mk and now can be cleaned up.
SREC_CONFIG_TARGET_FILES :=

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
#Gionee <lairufei><20131116> add for CR00947932 begin
endif
#Gionee <lairufei><20131116> add for CR00947932 end

endif
