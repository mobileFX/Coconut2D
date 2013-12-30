// ==================================================================================================================================
//	   ______                             __     ___   ____     ___    ____  ____
//	  / ____/___  _________  ____  __  __/ /_   |__ \ / __ \   /   |  / __ \/  _/
//	 / /   / __ \/ ___/ __ \/ __ \/ / / / __/   __/ // / / /  / /| | / /_/ // /
//	/ /___/ /_/ / /__/ /_/ / / / / /_/ / /_    / __// /_/ /  / ___ |/ ____// /
//	\____/\____/\___/\____/_/ /_/\__,_/\__/   /____/_____/  /_/  |_/_/   /___/
//
// ==================================================================================================================================

#ifndef __COCONUT2D_HPP__
#define __COCONUT2D_HPP__

#define GLOBAL_FPS 30.0f
#define COCO_STOP_ON_CURRENT_FRAME -1

#include "Window.hpp"

//#include <cassert>
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <vector>
#include <map>

//# DO NOT EDIT BEGIN #//
class Null;
class Object;
class Array;
class Function;
class String;
class Number;
class Integer;
class Float;
class Boolean;
class Date;
class Math;
class RegExp;
class ArrayBuffer;
class ArrayBufferView;
class Float32Array;
class Int32Array;
class Uint8Array;
class Error;
class EvalError;
class RangeError;
class ReferenceError;
class SyntaxError;
class TypeError;
class EventTarget;
class Event;
class HTMLCanvasElement;
class HTMLElement;
class HTMLDocument;
class ImageData;
class Image;
class ImageDataBuffer;
class Touch;
class TouchEvent;
class HTMLWindow;
class TouchList;
class WebGLActiveInfo;
class WebGLBuffer;
class WebGLContextAttributes;
class WebGLFramebuffer;
class WebGLObject;
class WebGLRenderbuffer;
class WebGLShader;
class WebGLShaderPrecisionFormat;
class WebGLTexture;
class WebGLUniformLocation;
class WebGLProgram;
class WebGLRenderingContext;
class CocoImageSibling;
class CocoRect;
class CocoSequence;
class CocoImage;
class CocoSound;
class CocoTimeLabel;
class CocoVector;
class CocoMatrix;
class CocoKeyFrame;
class CocoTimeline;
class CocoClip;
class CocoScene;
class CocoEngineState;
class CocoEngine;
class CocoSprite;
class CocoSpriteActor;
class CocoSpriteBonus;
class CocoSpriteBullet;
class CocoSpriteEnemy;
class CocoSpritePlayer;
class CocoSpriteVisual;
class CocoTiledLayer;
class UIView;
class UIControlView;
class UIButtonView;
class UICheckboxView;
class UILabelView;
class UINavbarView;
class UIPageView;
class UIPickerView;
class UIScrollView;
class UITabView;
class UITextView;
class SceneGameBoard;
class SceneTitle;
class State_GameBoard;
class State_TitleScreen;
class GameEngine;
//# DO NOT EDIT END #//

#define CocoException	std::string
#define Number          float
#define Boolean         bool
#define String          std::string
#define Function        void*
#define Object          void*
//template<class T> using Array = std::vector<T>;
template<class T> using Stack = std::stack<T>;
template<class T> using Dictionary = std::map<std::string, T>;
template<class T> using Index = std::map<size_t, T>;

static bool operator!(std::string str) { return str.empty(); }

template<class T> class Array : public std::vector<T>
{
public:
	Array() : std::vector<T>() {}
	Array(std::initializer_list<T> val) : std::vector<T>(val) {}
	void push(const T& v)
	{
		std::vector<T>::push_back(v);
	};
	T pop()
	{
		T ret = std::vector<T>::back();
		std::vector<T>::pop_back();
		return ret;
	}
	void splice(int index, int count)
	{
		std::vector<T>::erase(std::vector<T>::begin() + index, std::vector<T>::begin() + index + count);
	}
};

typedef void (CocoScene::*FPAction)(WebGLRenderingContext*, Number, Number, CocoScene*, CocoClip*);

////////////////////////////////////////////////////////////////
#ifdef IOS_APPLICATION
#define PLATFORM "iOS"
#define fxAPIGetKey(E) (*(const uint32_t*)(E))
#define fxAPIGetMouseEventX(E) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].x)
#define fxAPIGetMouseEventY(E) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].y)
#define fxAPIGetTouchEventX(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
#define fxAPIGetTouchEventY(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
#define fxAPIGetChangedTouchEventX(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
#define fxAPIGetChangedTouchEventY(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
#define fxAPIGetTouchesLength(E) ([[(UIEvent*)E allTouches] count])
#define fxAPIGetChangedTouchesLength(E) ([[(UIEvent*)E allTouches] count])
#elif ANDROID_APPLICATION
#define PLATFORM "Android"
#include <jni.h>
#include <android_native_app_glue.h>
#define fxAPIGetMouseEventX(E) AMotionEvent_getX((AInputEvent*)E, 0)
#define fxAPIGetMouseEventY(E) AMotionEvent_getY((AInputEvent*)E, 0)
#define fxAPIGetTouchEventX(E, I) AMotionEvent_getX((AInputEvent*)E, I)
#define fxAPIGetTouchEventY(E, I) AMotionEvent_getY((AInputEvent*)E, I)
#define fxAPIGetChangedTouchEventX(E, I) AMotionEvent_getX((AInputEvent*)E, I)
#define fxAPIGetChangedTouchEventY(E, I) AMotionEvent_getY((AInputEvent*)E, I)
#define fxAPIGetTouchesLength(E) AMotionEvent_getPointerCount((AInputEvent*)E)
#define fxAPIGetChangedTouchesLength(E) AMotionEvent_getPointerCount((AInputEvent*)E)
#else
#define PLATFORM "General"
#define fxAPIGetKey(E)(*(const uint32_t*)(E))
#define fxAPIGetMouseEventX(E) (((QMouseEvent*)(E))->x())
#define fxAPIGetMouseEventY(E) (((QMouseEvent*)(E))->y())
#define fxAPIGetTouchEventX(E, I) (((QMouseEvent*)(E))->x())
#define fxAPIGetTouchEventY(E, I) (((QMouseEvent*)(E))->y())
#define fxAPIGetChangedTouchEventX(E, I) (((QMouseEvent*)(E))->x())
#define fxAPIGetChangedTouchEventY(E, I) (((QMouseEvent*)(E))->y())
#define fxAPIGetTouchesLength(E) (((QEvent*)(E))->type() == QEvent::MouseButtonRelease ? 0 : 1)
#define fxAPIGetChangedTouchesLength(E) 1
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_FX_DEBUG
#ifdef ANDROID_APPLICATION
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, APPNAME, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, APPNAME, __VA_ARGS__))
#else
#include <cstdio>
#define LOGI(...) {fprintf(stdout, __VA_ARGS__); fflush(stdout);}
#define LOGW(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
#endif
#else
#define LOGI(...)
#define LOGW(...)
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_PNG_SUPPORT
#include <png.h>
#elif !DISABLE_PNG_SUPPORT
#warning "Building without PNG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_JPEG_SUPPORT
#undef FALSE
#undef TRUE
#include <jpeglib.h>
#elif !DISABLE_JPEG_SUPPORT
#warning "Building without JPEG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OGG_SUPPORT
#define AUDIO_SAMPLE_SIZE 2
#define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
#define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16
#include <tremor/ivorbisfile.h>
#elif !DISABLE_OGG_SUPPORT
#warning "Building without Vorbis OGG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OPENAL_SUPPORT
#ifdef IOS_APPLICATION
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#elif !DISABLE_OPENAL_SUPPORT
#warning "Building without Audio support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_FREETYPE_SUPPORT
#include <ft2build.h>
#include FT_FREETYPE_H
#elif !DISABLE_FREETYPE_SUPPORT
#warning "Building without Font support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_CURL_SUPPORT
#include <curl.h>
#elif !DISABLE_CURL_SUPPORT
#warning "Building without XMLHttpRequest support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OPENGL_SUPPORT
#ifdef ANDROID_APPLICATION
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#elif IOS_APPLICATION
#include <OpenGLES/ES2/gl.h>
#else
#include <QtOpenGL/QtOpenGL>
#endif
#elif !DISABLE_OPENGL_SUPPORT
#warning "Building without OpenGL support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#define JSINTERVAL_MIN 4
#define JSTOUCHLIST_MAX_LENGTH 5
#define SHADER_SOURCE_BUFFER_SIZE 4096
#define INFO_LOG_BUFFER_SIZE 4096
#define fxObjectUID size_t


#endif

