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
	LOCAL_C_INCLUDES :=  "../jni" "../../Common" "../../Common/Audio_API" "../../Common/Coconut2D" "../../Common/Coconut2D/anim" "../../Common/Coconut2D/game" "../../Common/Fonts_API" "../../Common/HTML5" "../../Common/usr" "../../Common/usr/animations" "../../Include" "../../Include/AL" "../../Include/freetype" "../../Include/freetype/config" "../../Include/freetype/internal" "../../Include/freetype/internal/services" "../../Include/JavaScriptCore" "../../Include/ogg" "../../Include/tremor"
	LOCAL_MODULE := CocoEngine
	LOCAL_SRC_FILES := "fxDeviceWrapper.cpp" "fxGLWrap.cpp" "main.cpp" "MainActivity.cpp" "../../Common/Audio_API/fxAudioStream.cpp" "../../Common/Coconut2D/anim/CocoAudio.cpp" "../../Common/Coconut2D/anim/CocoClip.cpp" "../../Common/Coconut2D/anim/CocoEngine.cpp" "../../Common/Coconut2D/anim/CocoImage.cpp" "../../Common/Coconut2D/anim/CocoImageSibling.cpp" "../../Common/Coconut2D/anim/CocoKeyFrame.cpp" "../../Common/Coconut2D/anim/CocoMatrix.cpp" "../../Common/Coconut2D/anim/CocoRect.cpp" "../../Common/Coconut2D/anim/CocoScene.cpp" "../../Common/Coconut2D/anim/CocoSequence.cpp" "../../Common/Coconut2D/anim/CocoSound.cpp" "../../Common/Coconut2D/anim/CocoTimeLabel.cpp" "../../Common/Coconut2D/anim/CocoTimeline.cpp" "../../Common/Coconut2D/anim/CocoVector.cpp" "../../Common/Coconut2D/game/CocoSprite.cpp" "../../Common/Coconut2D/game/CocoSpriteActor.cpp" "../../Common/Coconut2D/game/CocoSpriteBonus.cpp" "../../Common/Coconut2D/game/CocoSpriteBullet.cpp" "../../Common/Coconut2D/game/CocoSpriteEnemy.cpp" "../../Common/Coconut2D/game/CocoSpritePlayer.cpp" "../../Common/Coconut2D/game/CocoSpriteVisual.cpp" "../../Common/Coconut2D/game/CocoTiledLayer.cpp" "../../Common/Fonts_API/CocoFont.cpp" "../../Common/Fonts_API/fxFontFace.cpp" "../../Common/HTML5/ArrayBuffer.cpp" "../../Common/HTML5/ArrayBufferView.cpp" "../../Common/HTML5/CanvasRenderingContext2D.cpp" "../../Common/HTML5/DeviceEvent.cpp" "../../Common/HTML5/EventTarget.cpp" "../../Common/HTML5/HTMLAudioElement.cpp" "../../Common/HTML5/HTMLCanvasContext.cpp" "../../Common/HTML5/HTMLCanvasElement.cpp" "../../Common/HTML5/HTMLDocument.cpp" "../../Common/HTML5/HTMLElement.cpp" "../../Common/HTML5/HTMLEvent.cpp" "../../Common/HTML5/HTMLImageElement.cpp" "../../Common/HTML5/HTMLWindow.cpp" "../../Common/HTML5/Touch.cpp" "../../Common/HTML5/TouchList.cpp" "../../Common/HTML5/TypedArray.cpp" "../../Common/HTML5/WebGLRenderingContext.cpp" "../../Common/usr/GameEngine.cpp" "../../Common/usr/animations/BitmapSymbolsTest.cpp" "../../Common/usr/animations/GridSymbol.cpp" "../../Common/usr/animations/SceneGameBoard.cpp" "../../Common/usr/animations/SceneTitle.cpp" "../../Common/usr/animations/SynthesisTest.cpp" "../../Common/usr/animations/Test.cpp" "../../Common/usr/animations/TestSequences.cpp" "../../Common/usr/animations/TestText.cpp"
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)