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
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/views \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/interfaces \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/graphics \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/audio \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen \
../../../../.SDK/DeviceWrappers/native/_Includes \
../../../../.SDK/DeviceWrappers/native/_Common/Fonts \
../../../../.SDK/DeviceWrappers/native/_Common/Events \
../../../../.SDK/DeviceWrappers/native/_Common/Audio \
../../../../.SDK/DeviceWrappers/native/_Common/Arrays \
../../../../.SDK/DeviceWrappers/native/_Common
	LOCAL_MODULE := Coconut2D
	LOCAL_SRC_FILES := src/main.cpp \
src/fxGLWrap.cpp \
src/fxDeviceWrapper.cpp \
src/MainActivity.cpp \
../../_Common/animations/Page1.cpp \
../../_Common/animations/NewAnimation.cpp \
../../_Common/TestInterfaces.cpp \
../../_Common/GameEngine.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.webgl/native/src/WebGLRenderingContext.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/views/CocoUIView.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/views/CocoUIPage.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUITextBox.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUILabel.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUIControl.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUIComboBox.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUICheckBox.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.ui/native/gen/controls/CocoUIButton.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/ImageData.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLWindow.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLImageElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLEvent.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/src/HTMLAudioElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLTextMetrics.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLDocument.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLCanvasPattern.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLCanvasGradient.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/HTMLCanvasElement.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.html5/native/gen/CanvasRenderingContext2D.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/interfaces/ITickable.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/interfaces/IEventTarget.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/interfaces/IEventListener.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/graphics/CocoText.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/graphics/CocoImage.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine/DeviceTouches.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine/DeviceMessage.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine/CocoTickable.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine/CocoEvents.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/engine/CocoEngine.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/audio/CocoAudio.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/Constants.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoTimeline.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoScene.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoMatrix.cpp \
../../../../.SDK/Frameworks/org.coconut2d.sdk.anim/native/gen/CocoClip.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Fonts/fxFontFace.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Fonts/CocoFont.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Events/EventTarget.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Coconut2D.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Audio/fxAudioStream.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Arrays/TypedArray.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Arrays/ArrayBufferView.cpp \
../../../../.SDK/DeviceWrappers/native/_Common/Arrays/ArrayBuffer.cpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)