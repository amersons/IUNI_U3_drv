ifeq "$(strip $(GN_Q_BSP_SAVE_POWEROFFCHG_LOG_SUPPORT))" "y"
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        savelog.cpp


LOCAL_MODULE:= savelog
LOCAL_MODULE_TAGS := optional eng 

include $(BUILD_EXECUTABLE) 
 
endif