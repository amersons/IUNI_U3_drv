ifneq ("$(APK_DEFAULT_CALENDAR_SUPPORT)", "no")

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

# Include res dir from chips
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#chips_dir := ../../../frameworks/ex/chips/res
#color_picker_dir := ../../../frameworks/opt/colorpicker/res
#datetimepicker_dir := ../../../frameworks/opt/datetimepicker/res
#timezonepicker_dir := ../../../frameworks/opt/timezonepicker/res
#res_dirs := $(chips_dir) $(color_picker_dir) $(datetimepicker_dir) $(timezonepicker_dir) res

chips_dir := $(PWD)/frameworks/ex/chips/res
color_picker_dir := $(PWD)/frameworks/opt/colorpicker/res
datetimepicker_dir := $(PWD)/frameworks/opt/datetimepicker/res
timezonepicker_dir := $(PWD)/frameworks/opt/timezonepicker/res
res_dirs := res
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end
src_dirs := src

LOCAL_EMMA_COVERAGE_FILTER := +com.android.calendar.*

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under,$(src_dirs))

# bundled
#LOCAL_STATIC_JAVA_LIBRARIES += \
#        android-common \
#        android-common-chips \
#        calendar-common

# unbundled
LOCAL_STATIC_JAVA_LIBRARIES := \
        android-common \
        android-common-chips \
        colorpicker \
        android-opt-datetimepicker \
        android-opt-timezonepicker \
        android-support-v4 \
        calendar-common

LOCAL_SDK_VERSION := current

#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dirs))
LOCAL_RESOURCE_DIR := $(chips_dir) $(color_picker_dir) $(datetimepicker_dir) $(timezonepicker_dir) $(addprefix $(LOCAL_PATH)/, $(res_dirs))
$(shell cp $(PWD)/frameworks/opt/datetimepicker/proguard.flags $(LOCAL_PATH)/proguard_datetimepicker.flags)
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

LOCAL_PACKAGE_NAME := Calendar

#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#LOCAL_PROGUARD_FLAG_FILES := proguard.flags \
#                             ../../../frameworks/opt/datetimepicker/proguard.flags
LOCAL_PROGUARD_FLAG_FILES := proguard.flags \
                             proguard_datetimepicker.flags			     
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

LOCAL_AAPT_FLAGS := --auto-add-overlay
LOCAL_AAPT_FLAGS += --extra-packages com.android.ex.chips
LOCAL_AAPT_FLAGS += --extra-packages com.android.colorpicker
LOCAL_AAPT_FLAGS += --extra-packages com.android.datetimepicker
LOCAL_AAPT_FLAGS += --extra-packages com.android.timezonepicker

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))

endif
