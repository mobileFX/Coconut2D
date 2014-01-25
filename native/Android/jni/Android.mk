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
	LOCAL_C_INCLUDES := ../Include ../Common ../Common/HTML5 ../Common/Coconut2D ../Common/Coconut2D/anim ../Common/usr ../Common/usr/animations
	LOCAL_MODULE := CocoEngine
	LOCAL_SRC_FILES := \
		../../Common/HTML5/HTMLEvent.cpp \
		../../Common/HTML5/HTMLCanvasElement.cpp \
		fxDeviceWrapper.cpp \
		../../Common/HTML5/ArrayBuffer.cpp \
		../../Common/HTML5/ArrayBufferView.cpp \
		../../Common/usr/animations/SceneGameBoard.cpp \
		../../Common/HTML5/TypedArray.cpp \
		../../Common/Coconut2D/anim/CocoClip.cpp \
		../../Common/Coconut2D/anim/CocoTimeline.cpp \
		fxGLWrap.cpp \
		../../Common/Coconut2D/anim/CocoEngineState.cpp \
		../../Common/Coconut2D/anim/CocoMatrix.cpp \
		../../Common/Coconut2D/anim/CocoImage.cpp \
		../../Common/Coconut2D/anim/CocoAudio.cpp \
		../../Common/Coconut2D/anim/CocoTimeLabel.cpp \
		../../Common/HTML5/Window.cpp \
		../../Common/HTML5/WebGLRenderingContext.cpp \
		../../Common/Coconut2D/anim/CocoScene.cpp \
		../../Common/Coconut2D/anim/CocoImageSibling.cpp \
		../../Common/Coconut2D/anim/CocoKeyFrame.cpp \
		../../Common/fxAudioStream.cpp \
		../../Common/Coconut2D/anim/CocoRect.cpp \
		../../Common/usr/GameEngine.cpp \
		main.cpp \
		../../Common/HTML5/HTMLImageElement.cpp \
		../../Common/Coconut2D/anim/CocoSequence.cpp \
		../../Common/Coconut2D/anim/CocoSound.cpp \
		../../Common/fxFontFace.cpp \
		../../Common/Coconut2D/anim/CocoEngine.cpp \
		../../Common/usr/animations/SceneTitle.cpp \
		../../Common/Coconut2D/anim/CocoVector.cpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)