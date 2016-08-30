LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := cairo
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/cairo/prebuilt/Android/$(TARGET_ARCH_ABI)/libcairo.a
include $(PREBUILT_STATIC_LIBRARY)
