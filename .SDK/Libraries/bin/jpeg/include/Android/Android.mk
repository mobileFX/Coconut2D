LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/jpeg/prebuilt/Android/$(TARGET_ARCH_ABI)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)
