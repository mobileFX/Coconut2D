LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_base
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libv8_base.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := preparser_lib
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libpreparser_lib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_nosnapshot
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := v8_snapshot
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libv8_snapshot.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := png
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := jpeg
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libjpeg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libopenal.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := curl
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libcurl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := Tremolo
LOCAL_SRC_FILES := ../../../Common/SDK/Libraries/Android/$(TARGET_ARCH_ABI)/libTremolo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
	LOCAL_LDLIBS := -landroid -llog -lEGL -lGLESv2 -lOpenSLES -lz
	LOCAL_STATIC_LIBRARIES := stdc++ android_native_app_glue v8_base preparser_lib v8_nosnapshot v8_nosnapshot png jpeg freetype openal curl Tremolo
	LOCAL_C_INCLUDES :=  -I../jni -I../../../Common/SDK/Includes -I../../../Common/SDK/Includes/AL -I../../../Common/SDK/Includes/freetype -I../../../Common/SDK/Includes/freetype/config -I../../../Common/SDK/Includes/freetype/internal -I../../../Common/SDK/Includes/freetype/internal/services -I../../../Common/SDK/Includes/JavaScriptCore -I../../../Common/SDK/Includes/ogg -I../../../Common/SDK/Includes/tremor -I../../../Common/SDK/src -I../../../Common/SDK/src/Audio -I../../../Common/SDK/src/Coconut2D/anim -I../../../Common/SDK/src/Coconut2D/game -I../../../Common/SDK/src/Fonts -I../../../Common/SDK/src/HTML5 -I../../../Common/usr -I../../../Common/usr/animations
	LOCAL_MODULE := CocoEngine
	LOCAL_SRC_FILES := fxDeviceWrapper.cpp fxGLWrap.cpp main.cpp MainActivity.cpp ../../../Common/SDK/src/Audio/fxAudioStream.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoAudio.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoClip.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoEngine.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoImage.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoImageSibling.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoKeyFrame.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoMatrix.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoRect.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoScene.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoSequence.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoTimeLabel.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoTimeline.cpp ../../../Common/SDK/src/Coconut2D/anim/CocoVector.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSprite.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpriteActor.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpriteBonus.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpriteBullet.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpriteEnemy.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpritePlayer.cpp ../../../Common/SDK/src/Coconut2D/game/CocoSpriteVisual.cpp ../../../Common/SDK/src/Coconut2D/game/CocoTiledLayer.cpp ../../../Common/SDK/src/Fonts/CocoFont.cpp ../../../Common/SDK/src/Fonts/fxFontFace.cpp ../../../Common/SDK/src/HTML5/ArrayBuffer.cpp ../../../Common/SDK/src/HTML5/ArrayBufferView.cpp ../../../Common/SDK/src/HTML5/CanvasRenderingContext2D.cpp ../../../Common/SDK/src/HTML5/DeviceEvent.cpp ../../../Common/SDK/src/HTML5/EventTarget.cpp ../../../Common/SDK/src/HTML5/HTMLAudioElement.cpp ../../../Common/SDK/src/HTML5/HTMLCanvasContext.cpp ../../../Common/SDK/src/HTML5/HTMLCanvasElement.cpp ../../../Common/SDK/src/HTML5/HTMLDocument.cpp ../../../Common/SDK/src/HTML5/HTMLElement.cpp ../../../Common/SDK/src/HTML5/HTMLEvent.cpp ../../../Common/SDK/src/HTML5/HTMLImageElement.cpp ../../../Common/SDK/src/HTML5/HTMLWindow.cpp ../../../Common/SDK/src/HTML5/Touch.cpp ../../../Common/SDK/src/HTML5/TouchList.cpp ../../../Common/SDK/src/HTML5/TypedArray.cpp ../../../Common/SDK/src/HTML5/WebGLRenderingContext.cpp ../../../Common/usr/GameEngine.cpp ../../../Common/usr/animations/GridSymbol.cpp ../../../Common/usr/animations/SceneGameBoard.cpp ../../../Common/usr/animations/SceneTitle.cpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)