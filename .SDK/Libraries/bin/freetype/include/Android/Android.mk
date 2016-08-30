LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype2
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/freetype/prebuilt/Android/$(TARGET_ARCH_ABI)/libfreetype2.a
include $(PREBUILT_STATIC_LIBRARY)
