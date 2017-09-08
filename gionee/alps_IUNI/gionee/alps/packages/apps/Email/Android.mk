
# Copyright 2008, The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)

ifneq ("$(APK_DEFAULT_EMAIL_SUPPORT)", "no")

# Build the Email application itself, along with its tests and tests for the emailcommon
# static library.  All tests can be run via runtest email

include $(CLEAR_VARS)

# Include res dir from chips, unified, emailcommon, and photoviewer
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#chips_dir := ../../../frameworks/ex/chips/res
#unified_email_dir := ../UnifiedEmail
#photo_dir := ../../../frameworks/opt/photoviewer/res ../../../frameworks/opt/photoviewer/activity/res
#emailcommon_dir := emailcommon
#gridlayout_dir := ../../../frameworks/support/v7/gridlayout/res
#res_dir := res $(unified_email_dir)/res $(chips_dir) $(photo_dir) $(emailcommon_dir)/res $(gridlayout_dir)

chips_dir := $(PWD)/frameworks/ex/chips/res
unified_email_dir := ../UnifiedEmail
photo_dir := $(PWD)/frameworks/opt/photoviewer/res $(PWD)/frameworks/opt/photoviewer/activity/res
emailcommon_dir := emailcommon
gridlayout_dir := $(PWD)/frameworks/support/v7/gridlayout/res
res_dir := res $(unified_email_dir)/res $(emailcommon_dir)/res
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, $(unified_email_dir)/src)
LOCAL_SRC_FILES += $(call all-java-files-under, src/com/android)
LOCAL_SRC_FILES += $(call all-java-files-under, src/com/beetstra)
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 begin
#LOCAL_RESOURCE_DIR := $(addprefix $(LOCAL_PATH)/, $(res_dir))
LOCAL_RESOURCE_DIR := $(chips_dir) $(photo_dir) $(gridlayout_dir) $(mail_common_dir) $(addprefix $(LOCAL_PATH)/, $(res_dir))
#Gionee: <compile_error> <wangmeng> <20140117> modify for CR01027269 end
# Use assets dir from UnifiedEmail
# (the default package target doesn't seem to deal with multiple asset dirs)
LOCAL_ASSET_DIR := $(LOCAL_PATH)/$(unified_email_dir)/assets

LOCAL_AAPT_FLAGS := --auto-add-overlay
LOCAL_AAPT_FLAGS += --extra-packages com.android.ex.chips:com.android.mail:com.android.email:com.android.emailcommon:com.android.ex.photo:android.support.v7.gridlayout

LOCAL_STATIC_JAVA_LIBRARIES := android-common com.android.emailcommon com.android.emailsync guava android-common-chips libphotoviewer
LOCAL_STATIC_JAVA_LIBRARIES += android-support-v4
LOCAL_STATIC_JAVA_LIBRARIES += android-support-v7-gridlayout
LOCAL_STATIC_JAVA_LIBRARIES += android-support-v13

LOCAL_PACKAGE_NAME := Email

LOCAL_PROGUARD_FLAG_FILES := proguard.flags $(unified_email_dir)/proguard.flags

LOCAL_SDK_VERSION := current

include $(BUILD_PACKAGE)

endif
# only include rules to build other stuff for the original package, not the derived package.
ifeq ($(strip $(LOCAL_PACKAGE_OVERRIDES)),)
# additionally, build unit tests in a separate .apk
include $(call all-makefiles-under,$(LOCAL_PATH))
endif

