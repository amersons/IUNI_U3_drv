LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libft_api
LOCAL_MODULE_TAGS := debug
LOCAL_SRC_FILES = ft_api.c

LOCAL_SHARED_LIBRARIES := \
	libcutils 
	
LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE = ft_svc
LOCAL_MODULE_TAGS := debug
LOCAL_SRC_FILES = ft_svc.c

#LOCAL_C_INCLUDES := \
#	$(call include-path-for, bluedroid) \
#	external/dbus \
#	system/bluetooth/bluez-clean-headers
	
LOCAL_SHARED_LIBRARIES := \
	libcutils 
#	libbluedroid
	
LOCAL_PRELINK_MODULE := false

include $(BUILD_EXECUTABLE)
