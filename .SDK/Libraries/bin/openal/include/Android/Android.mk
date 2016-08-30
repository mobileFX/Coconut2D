LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ogg
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/openal/prebuilt/Android/$(TARGET_ARCH_ABI)/libogg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/openal/prebuilt/Android/$(TARGET_ARCH_ABI)/libopenal.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := tremolo
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/openal/prebuilt/Android/$(TARGET_ARCH_ABI)/libtremolo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := tremor
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/openal/prebuilt/Android/$(TARGET_ARCH_ABI)/libtremor.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := vorbis
LOCAL_SRC_FILES := ../../../../../.SDK/Libraries/bin/openal/prebuilt/Android/$(TARGET_ARCH_ABI)/libvorbis.a
include $(PREBUILT_STATIC_LIBRARY)
