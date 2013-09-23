LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_base
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libv8_base.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := preparser_lib
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libpreparser_lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_nosnapshot
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_snapshot
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libv8_snapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := png
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libopenal.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Tremolo
LOCAL_SRC_FILES := ../../Libraries/Android/$(TARGET_ARCH_ABI)/libTremolo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
	LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 -lOpenSLES -lz
	LOCAL_STATIC_LIBRARIES := stdc++ android_native_app_glue v8_base preparser_lib v8_nosnapshot v8_nosnapshot png jpeg freetype openal curl Tremolo
	LOCAL_C_INCLUDES := ../Include ../Common ../Common/fxJS
	LOCAL_MODULE := CocoEngine
	LOCAL_SRC_FILES := main.cpp \
		fxDeviceWrapper.cpp \
		fxGLWrap.cpp \
		../../Common/fxCRL.cpp \
		../../Common/fxFontFace.cpp \
		../../Common/fxAudioStream.cpp \
		../../Common/fxJS/ArrayBuffer.cpp \
		../../Common/fxJS/ArrayBufferView.cpp \
		../../Common/fxJS/Audio.cpp \
		../../Common/fxJS/DataView.cpp \
		../../Common/fxJS/fxFont.cpp \
		../../Common/fxJS/TypedArray.cpp \
		../../Common/fxJS/WebGLRenderingContext.cpp \
		../../Common/fxJS/XMLHttpRequest.cpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)