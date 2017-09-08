ifneq ("$(APK_DEFAULT_DESKCLOCK_SUPPORT)", "no")

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

# include res directory from timepicker
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#datetimepicker_dir := ../../../frameworks/opt/datetimepicker/res
#res_dirs := $(datetimepicker_dir) res
#LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dirs))
datetimepicker_dir := $(PWD)/frameworks/opt/datetimepicker/res
res_dirs := res
LOCAL_RESOURCE_DIR := $(datetimepicker_dir) $(addprefix $(LOCAL_PATH)/, $(res_dirs))
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := android-support-v13
LOCAL_STATIC_JAVA_LIBRARIES += android-support-v4
LOCAL_STATIC_JAVA_LIBRARIES += android-opt-datetimepicker

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := DeskClock

LOCAL_OVERRIDES_PACKAGES := AlarmClock

# LOCAL_SDK_VERSION := current

#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#LOCAL_PROGUARD_FLAG_FILES := proguard.flags
#LOCAL_PROGUARD_FLAG_FILES += ../../../frameworks/opt/datetimepicker/proguard.flags
$(shell cp $(PWD)/frameworks/opt/datetimepicker/proguard.flags $(LOCAL_PATH)/proguard_datetimepicker.flags)
LOCAL_PROGUARD_FLAG_FILES := proguard.flags \
                             proguard_datetimepicker.flags			     
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

LOCAL_AAPT_FLAGS := --auto-add-overlay
LOCAL_AAPT_FLAGS += --extra-packages com.android.datetimepicker

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))

endif
