LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := png
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/png/prebuilt/Android/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)
