# Copyright 2011 The Android Open Source Project

ifneq ($(BUILD_TINY_ANDROID),true)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	charger.c \
    battery_ac.c

ifeq ($(strip $(BOARD_CHARGER_DISABLE_INIT_BLANK)),true)
LOCAL_CFLAGS := -DCHARGER_DISABLE_INIT_BLANK
endif

ifeq ($(strip $(BOARD_CHARGER_ENABLE_SUSPEND)),true)
LOCAL_CFLAGS += -DCHARGER_ENABLE_SUSPEND
endif

ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),default)
LOCAL_CFLAGS += -DGN_Q_BSP_POWEROFF_CHG_UI_DEFAULT
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),amigo)
LOCAL_CFLAGS += -DGN_Q_BSP_POWEROFF_CHG_UI_AMIGO
LOCAL_CFLAGS += -DGN_Q_BSP_BATTERY_HEALTH_SUPPORT
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),gionee)
LOCAL_CFLAGS += -DGN_Q_BSP_POWEROFF_CHG_UI_GIONEE
LOCAL_CFLAGS += -DGN_Q_BSP_BATTERY_HEALTH_SUPPORT
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),iuni)
LOCAL_CFLAGS += -DGN_Q_BSP_POWEROFF_CHG_UI_IUNI
endif
LOCAL_MODULE := charger
LOCAL_MODULE_TAGS := optional
LOCAL_FORCE_STATIC_EXECUTABLE := true
LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT)
LOCAL_REQUIRED_MODULES := charger_res_images
LOCAL_UNSTRIPPED_PATH := $(TARGET_ROOT_OUT_UNSTRIPPED)

LOCAL_C_INCLUDES := bootable/recovery

LOCAL_STATIC_LIBRARIES := libminui libpixelflinger_static libpng
ifeq ($(strip $(BOARD_CHARGER_ENABLE_SUSPEND)),true)
LOCAL_STATIC_LIBRARIES += libsuspend
endif
LOCAL_STATIC_LIBRARIES += libz libstdc++ libcutils liblog libm libc

include $(BUILD_EXECUTABLE)

define _add-charger-image
include $$(CLEAR_VARS)
LOCAL_MODULE := system_core_charger_$(notdir $(1))
LOCAL_MODULE_STEM := $(notdir $(1))
_img_modules += $$(LOCAL_MODULE)
LOCAL_SRC_FILES := $1
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $$(TARGET_ROOT_OUT)/res/images/charger
include $$(BUILD_PREBUILT)
endef

_img_modules :=
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),default)
_images :=
$(foreach _img, $(call find-subdir-subdir-files, "default_chg_img", "*.png"), \
  $(eval $(call _add-charger-image,$(_img))))
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),amigo)
_images :=
$(foreach _img, $(call find-subdir-subdir-files, "amigo_chg_img", "*.png"), \
  $(eval $(call _add-charger-image,$(_img))))
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),gionee)
_images :=
$(foreach _img, $(call find-subdir-subdir-files, "gionee_chg_img", "*.png"), \
  $(eval $(call _add-charger-image,$(_img))))
endif
ifeq ($(GN_Q_BSP_POWEROFF_CHARGER_UI_TYPE),iuni)
_images :=
$(foreach _img, $(call find-subdir-subdir-files, "iuni_chg_img", "*.png"), \
  $(eval $(call _add-charger-image,$(_img))))
endif

include $(CLEAR_VARS)
LOCAL_MODULE := charger_res_images
LOCAL_MODULE_TAGS := optional
LOCAL_REQUIRED_MODULES := $(_img_modules)
include $(BUILD_PHONY_PACKAGE)

_add-charger-image :=
_img_modules :=

endif
