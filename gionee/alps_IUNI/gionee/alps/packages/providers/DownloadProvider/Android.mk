ifneq ("$(APK_DEFAULT_DOWNLOADPROVIDER_SUPPORT)", "no")

#Gionee <lairufei><20131112> add for CR00948501 begin
ifeq ("$(GN_APK_DOWNLOADPROVIDER_SUPPORT)","yes")
#Gionee <lairufei><20131112> add for CR00948501 end
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)


LOCAL_PACKAGE_NAME := DownloadProvider
LOCAL_CERTIFICATE := media
LOCAL_PRIVILEGED_MODULE := true
LOCAL_STATIC_JAVA_LIBRARIES := guava

include $(BUILD_PACKAGE)

# build UI + tests
include $(call all-makefiles-under,$(LOCAL_PATH))
#Gionee <lairufei><20131112> add for CR00948501 begin
endif
#Gionee <lairufei><20131112> add for CR00948501 end

endif
