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

////////////////////////////////////////////////////////////////////////////////////////////////////
// Application-wide constants
////////////////////////////////////////////////////////////////////////////////////////////////////

#define APPNAME "Coconut2D"
#define GLOBAL_FPS 30.0f
#define COCO_STOP_ON_CURRENT_FRAME -1
#define RADIANS (M_PI / 180.0f)

////////////////////////////////////////////////////////////////////////////////////////////////////
// Common Includes
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Structs.h"
#include <UIKit/UIEvent.h>
#include <UIKit/UITouch.h>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Auto-generated class list
////////////////////////////////////////////////////////////////////////////////////////////////////

//# DO NOT EDIT BEGIN #//
class CocoTest;
class EventTarget;
class DeviceEvent;
class Audio;
class HTMLCanvasContext;
class HTMLCanvasElement;
class HTMLCanvasGradient;
class HTMLCanvasPattern;
class HTMLElement;
class HTMLDocument;
class HTMLTextMetrics;
class CanvasRenderingContext2D;
class HTMLWindow;
class ImageData;
class Image;
class ImageDataBuffer;
class Touch;
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
class CocoAudio;
class CocoImageSibling;
class CocoRect;
class CocoSequence;
class CocoImage;
class CocoTimeLabel;
class CocoVector;
class CocoMatrix;
class CocoKeyFrame;
class CocoTimeline;
class CocoClip;
class CocoScene;
class CocoEngine;
class CocoSprite;
class CocoSpriteActor;
class CocoSpriteBonus;
class CocoSpriteBullet;
class CocoSpriteEnemy;
class CocoSpritePlayer;
class CocoSpriteVisual;
class CocoTiledLayer;
class CocoUIView;
class CocoUIControlView;
class CocoUIButtonView;
class CocoUICheckboxView;
class CocoUILabelView;
class CocoUINavbarView;
class CocoUIPageView;
class CocoUIPickerView;
class CocoUIScrollView;
class CocoUITabView;
class CocoUITextView;
class GameEngine;
class BitmapSymbolsTest;
class SynthesisTest;
class Test;
class TestSequences;
//# DO NOT EDIT END #//

////////////////////////////////////////////////////////////////////////////////////////////////////
// Externs for global objects
////////////////////////////////////////////////////////////////////////////////////////////////////
extern CocoEngine* engine;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for HTML5 Events
////////////////////////////////////////////////////////////////////////////////////////////////////
enum fxEvent
{
	LOAD = 0,
	FOCUS,
	BLUR,
	UNLOAD,
	RESIZE,
	CLICK,
	KEYDOWN,
	KEYPRESS,
	KEYUP,
	TOUCHSTART,
	TOUCHMOVE,
	TOUCHEND,
	TOUCHCANCEL,
	GESTURESTART,
	GESTURECHANGE,
	GESTUREEND
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for screen resolution dpi
////////////////////////////////////////////////////////////////////////////////////////////////////
enum SCREEN_RESOLUTION_DPI_ENUM
{
    RESOLUTION_nodpi							= 0,
    RESOLUTION_ldpi								= 1,
    RESOLUTION_mdpi								= 2,
    RESOLUTION_tvdpi							= 3,
    RESOLUTION_hdpi								= 4,
    RESOLUTION_xhdpi							= 5,
    RESOLUTION_Retina							= 5,
    RESOLUTION_DefaultDpi						= 0
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for filter shaders.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum COCO_FILTER_ENUM
{
    FILTER_INHERIT					= 0,
    FILTER_SIMPLE					= 1,
    FILTER_SIMPLE_WITH_ALPHA		= 2,
	FILTER_SATURATION_WITH_ALPHA	= 3
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for clip symbol loop synchronization.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum COCO_CLIP_SYMBOL_LOOP_ENUM
{
    CLIP_SYMBOL_LOOP_CONTINUOUS					= 0,
    CLIP_SYMBOL_LOOP_SYNCHRONIZED_WITH_PARENT	= 1,
    CLIP_SYMBOL_LOOP_ONCE						= 2
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for keyframe interpolation calculation.
////////////////////////////////////////////////////////////////////////////////////////////////////
enum COCO_KEYFRAME_INTERPOLATION_ENUM
{
    KEYFRAME_INTERPOLATION_NONE					= 0,
    KEYFRAME_INTERPOLATION_MOTION_TWEEN			= 1,
    KEYFRAME_INTERPOLATION_ECHO					= 2,
    KEYFRAME_INTERPOLATION_PHYSICS				= 3
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for text alignment
////////////////////////////////////////////////////////////////////////////////////////////////////
enum COCO_TEXT_ALIGN_ENUM
{
	TEXT_ALIGN_NEAR								= 0,
	TEXT_ALIGN_CENTER							= 1,
	TEXT_ALIGN_FAR								= 2
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Enum for text trimming
////////////////////////////////////////////////////////////////////////////////////////////////////
enum COCO_TEXT_TRIMMING_ENUM
{
    StringTrimmingNone							= 0,
    StringTrimmingCharacter						= 1,
    StringTrimmingWord							= 2,
    StringTrimmingEllipsisCharacter				= 3,
    StringTrimmingEllipsisWord					= 4,
    StringTrimmingEllipsisPath					= 5
};

// ==================================================================================================================================
//	  ______                 ____       ____
//	 /_  __/_  ______  ___  / __ \___  / __/____
//	  / / / / / / __ \/ _ \/ / / / _ \/ /_/ ___/
//	 / / / /_/ / /_/ /  __/ /_/ /  __/ __(__  )
//	/_/  \__, / .___/\___/_____/\___/_/ /____/
//	    /____/_/
// ==================================================================================================================================

#define CocoException	std::string
#define Number          float
#define Function        void
#define Time			float

#define trace(...)

typedef void (*CocoAction)(CocoScene*, CocoClip*);
typedef void (CocoEngine::*CocoEventAction)(DeviceEvent* e);

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> using Stack = std::stack<T>;
template<class T> using Dictionary = std::map<std::string, T>;
template<class T> using Index = std::map<size_t, T>;

////////////////////////////////////////////////////////////////////////////////////////////////////
struct State
{
	virtual void enter() {}
	virtual void exit() {}
	virtual void tick(float time) = 0;
	virtual void paint(WebGLRenderingContext* gl, float time) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class String : public std::string
{
public:
	operator bool() const { return !empty(); }
	String& operator =(const char* c_str) { std::string::operator=(c_str); return *this; }
	String& operator =(String str) { std::string::operator=(str); return *this; }
	String& operator =(std::string str) { std::string::operator=(str); return *this; }
	String() = default;
	String(const char* str) : std::string(str) {}
	String(const std::string& str) : std::string(str) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Array : public std::vector<T>
{
public:
	Array() : std::vector<T>() {}
	int size() { return std::vector<T>::size(); }
	//Array(std::initializer_list<T> val) : std::vector<T>(val) {}
	Array(size_t size, ...) : std::vector<T>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (T)va_arg(vl, T);
		va_end(vl);
	}
	Array(const std::vector<T>& v) : std::vector<T>(v) {}
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
	Array<T> slice(int first, int last)
	{
		return Array<T>(std::vector<T>(std::vector<T>::begin() + first, std::vector<T>::begin() + last));
	}
	void splice(int index, int count)
	{
		std::vector<T>::erase(std::vector<T>::begin() + index, std::vector<T>::begin() + index + count);
	}
	Array<T>& operator()(T v)
	{
		this->push(v);
		return *this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class Array<bool> : public std::vector<bool>
{
public:
	Array() : std::vector<bool>() {}
	int size() { return std::vector<bool>::size(); }
	//Array(std::initializer_list<T> val) : std::vector<T>(val) {}
	Array(size_t size, ...) : std::vector<bool>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (bool)va_arg(vl, int);
		va_end(vl);
	}
	Array(const std::vector<bool>& v) : std::vector<bool>(v) {}
	void push(const bool& v)
	{
		std::vector<bool>::push_back(v);
	};
	bool pop()
	{
		bool ret = std::vector<bool>::back();
		std::vector<bool>::pop_back();
		return ret;
	}
	Array<bool> slice(int first, int last)
	{
		return Array<bool>(std::vector<bool>(std::vector<bool>::begin() + first, std::vector<bool>::begin() + last));
	}
	void splice(int index, int count)
	{
		std::vector<bool>::erase(std::vector<bool>::begin() + index, std::vector<bool>::begin() + index + count);
	}
	Array<bool>& operator()(bool v)
	{
		this->push(v);
		return *this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class Array<float> : public std::vector<float>
{
public:
	Array() : std::vector<float>() {}
	int size() { return std::vector<float>::size(); }
	//Array(std::initializer_list<float> val) : std::vector<float>(val) {}
	Array(size_t size, ...) : std::vector<float>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (float)va_arg(vl, double);
		va_end(vl);
	}
	Array(const std::vector<float>& v) : std::vector<float>(v) {}
	void push(const float& v)
	{
		std::vector<float>::push_back(v);
	};
	float pop()
	{
		float ret = std::vector<float>::back();
		std::vector<float>::pop_back();
		return ret;
	}
	Array<float> slice(int first, int last)
	{
		return Array<float>(std::vector<float>(std::vector<float>::begin() + first, std::vector<float>::begin() + last));
	}
	void splice(int index, int count)
	{
		std::vector<float>::erase(std::vector<float>::begin() + index, std::vector<float>::begin() + index + count);
	}
	Array<float>& operator()(float v)
	{
		this->push(v);
		return *this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_PNG_SUPPORT
#include <png.h>
#elif !DISABLE_PNG_SUPPORT
#warning "Building without PNG support!"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_JPG_SUPPORT
#undef FALSE
#undef TRUE
#include <jpeglib.h>
#elif !DISABLE_JPG_SUPPORT
#warning "Building without JPG support!"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_OGG_SUPPORT
#define AUDIO_SAMPLE_SIZE 2
#define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
#define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16
#include <tremor/ivorbisfile.h>
#elif !DISABLE_OGG_SUPPORT
#warning "Building without Vorbis OGG support!"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_FREETYPE_SUPPORT
#include <ft2build.h>
#include FT_FREETYPE_H
#elif !DISABLE_FREETYPE_SUPPORT
#warning "Building without Font support!"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_CURL_SUPPORT
#include <curl.h>
#elif !DISABLE_CURL_SUPPORT
#warning "Building without XMLHttpRequest support!"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
#define JSINTERVAL_MIN 4
#define JSTOUCHLIST_MAX_LENGTH 5
#define SHADER_SOURCE_BUFFER_SIZE 4096
#define INFO_LOG_BUFFER_SIZE 4096
#define fxObjectUID size_t

#endif

