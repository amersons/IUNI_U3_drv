LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
picture_frame_files := $(LOCAL_PATH)/picture_frame
DIRS := $(addprefix $(TARGET_OUT)/, etc/gn_camera_feature/res/picture_frame)

$(DIRS):
	@echo Directory : $@
	@mkdir -p $@
	@cp -rf $(picture_frame_files)/* $@

ALL_PREBUILT += $(DIRS)
