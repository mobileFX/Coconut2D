LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/curl/prebuilt/Android/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)
