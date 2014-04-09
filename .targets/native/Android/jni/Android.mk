LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_base
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libv8_base.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := preparser_lib
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libpreparser_lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_nosnapshot
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_snapshot
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libv8_snapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := png
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libopenal.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Tremolo
LOCAL_SRC_FILES := ../../../../.SDK/DeviceWrappers/native/_Libraries/Android/$(TARGET_ARCH_ABI)/libTremolo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
	LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 -lOpenSLES -lz
	LOCAL_STATIC_LIBRARIES := stdc++ android_native_app_glue v8_base preparser_lib v8_nosnapshot v8_nosnapshot png jpeg freetype openal curl Tremolo
	LOCAL_C_INCLUDES := ./src \
../../_Common/animations \
../../_Common \
../../../../.SDK/Frameworks/org.coconut2d.sdk.webgl/native/src \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen \
../../../../.SDK/DeviceWrappers/native/_Includes
	LOCAL_MODULE := Coconut2D
	LOCAL_SRC_FILES := src/main.cpp \
src/fxGLWrap.cpp \
src/fxDeviceWrapper.cpp \
src/MainActivity.cpp \
../../_Common/animations/NewAnimation.cpp \
../../_Common/GameEngine.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.webgl/native/src/WebGLRenderingContext.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/fxFontFace.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/fxAudioStream.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/TypedArray.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/TouchList.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/Touch.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLWindow.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLImageElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLEvent.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLDocument.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLCanvasElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLCanvasContext.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLAudioElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/EventTarget.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/DeviceEvent.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/CocoFont.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/CanvasRenderingContext2D.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/ArrayBufferView.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/ArrayBuffer.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoVector.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoTimeline.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoTimeLabel.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoSequence.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoScene.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoRect.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoMatrix.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoKeyFrame.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoImageSibling.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoImage.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoEngine.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoClip.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoAudio.cpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)