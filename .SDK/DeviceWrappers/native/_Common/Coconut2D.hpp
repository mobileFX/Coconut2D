/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ***** END LICENSE BLOCK ***** */

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
#include <cassert>
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////////

//# Generated Classes Begin #//
class CanvasRenderingContext2D;
class CocoAudio;
class CocoClip;
class CocoEngine;
class CocoEvent;
class CocoEventConnectionPoint;
class CocoEventSource;
class CocoImage;
class CocoImageSibling;
class CocoMatrix;
class CocoScene;
class CocoSequence;
class CocoText;
class CocoTextStyle;
class CocoTickable;
class CocoTimeLabel;
class CocoTimeline;
class CocoVector;
class DeviceMessage;
class GameEngine;
class GridSymbol;
class HTMLCanvasElement;
class HTMLCanvasGradient;
class HTMLCanvasPattern;
class HTMLDocument;
class HTMLElement;
class HTMLTextMetrics;
class IEventListener;
class IEventTarget;
class ITickable;
class PathLine;
class SceneGameBoard;
class SceneTitle;
class Touch;
class TouchList;
struct CocoKeyFrame;
//# Generated Classes End #//

//# Native Classes Begin #//
class Audio;
class HTMLEvent;
class Image;
class HTMLWindow;
class ImageData;
struct GLany;
class WebGLObject;
class WebGLBuffer;
class WebGLFramebuffer;
class WebGLRenderbuffer;
class WebGLShader;
class WebGLTexture;
class WebGLUniformLocation;
class WebGLProgram;
class WebGLRenderingContext;
//# Native Classes End #//

template<typename T> struct TYPE_STRING { static constexpr char const* c_str() { return "undefined"; } };
#define DEF_TYPE(T) template<> struct TYPE_STRING<T> { static constexpr char const* c_str() { return #T; } };
DEF_TYPE(char);
DEF_TYPE(unsigned char);
DEF_TYPE(short);
DEF_TYPE(unsigned short);
DEF_TYPE(int);
DEF_TYPE(unsigned int);
DEF_TYPE(float);
DEF_TYPE(double);

template<typename T> class TypedArray;
typedef TypedArray<char> Int8Array;
typedef TypedArray<unsigned char> Uint8Array;
typedef TypedArray<unsigned char> Uint8ClampedArray;
typedef TypedArray<short> Int16Array;
typedef TypedArray<unsigned short> Uint16Array;
typedef TypedArray<int> Int32Array;
typedef TypedArray<unsigned int> Uint32Array;
typedef TypedArray<float> Float32Array;
typedef TypedArray<double> Float64Array;

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

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (CocoScene::*CocoAction)();
typedef void (CocoEngine::*CocoEventAction)(DeviceMessage* e);

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> using Stack = std::stack<T>;
template<class T> using Dictionary = std::map<std::string, T>;
template<class T> using Index = std::map<size_t, T>;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> class Array : public std::vector<T>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<T>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	int size()
	{
		return std::vector<T>::size();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(size_t size, ...) : std::vector<T>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (T)va_arg(vl, T);
		va_end(vl);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(const std::vector<T>& v) : std::vector<T>(v)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* push(const T& v)
	{
		std::vector<T>::push_back(v);
		return this;
	};

	//////////////////////////////////////////////////////////////////////////////////
	T pop()
	{
		T ret = std::vector<T>::back();
		std::vector<T>::pop_back();
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* slice(int first)
	{
		return new Array<T>(std::vector<T>(std::vector<T>::begin() + first, std::vector<T>::end()));
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* slice(int first, int last)
	{
		return new Array<T>(std::vector<T>(std::vector<T>::begin() + first, (last > 0 ? std::vector<T>::begin() : std::vector<T>::end()) + last));
	}

	//////////////////////////////////////////////////////////////////////////////////
	std::string join(std::string str)
	{
		std::stringstream ss;
		for(size_t i = 0; i < size(); i++)
		{
			ss<<this->at(i);
			if(i + 1 != size())
				ss<<str;
		}
		return ss.str();
	}

	//////////////////////////////////////////////////////////////////////////////////
	void splice(int index, int count)
	{
		std::vector<T>::erase(std::vector<T>::begin() + index, std::vector<T>::begin() + index + count);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* operator()(T v)
	{
		this->push(v);
		return this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class Array<bool> : public std::vector<bool>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<bool>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	int size()
	{
		return std::vector<bool>::size();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(size_t size, ...) : std::vector<bool>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (bool)va_arg(vl, int);
		va_end(vl);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(const std::vector<bool>& v) : std::vector<bool>(v)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<bool>* push(const bool& v)
	{
		std::vector<bool>::push_back(v);
		return this;
	}

	//////////////////////////////////////////////////////////////////////////////////
	bool pop()
	{
		bool ret = std::vector<bool>::back();
		std::vector<bool>::pop_back();
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<bool>* slice(int first, int last)
	{
		return new Array<bool>(std::vector<bool>(std::vector<bool>::begin() + first, std::vector<bool>::begin() + last));
	}

	//////////////////////////////////////////////////////////////////////////////////
	void splice(int index, int count)
	{
		std::vector<bool>::erase(std::vector<bool>::begin() + index, std::vector<bool>::begin() + index + count);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<bool>* operator()(bool v)
	{
		this->push(v);
		return this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> class Array<float> : public std::vector<float>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<float>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	int size()
	{
		return std::vector<float>::size();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(size_t size, ...) : std::vector<float>(size)
	{
		va_list vl;
		va_start(vl, size);
		for(size_t i = 0; i < size; i++)
			this->at(i) = (float)va_arg(vl, double);
		va_end(vl);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(const std::vector<float>& v) : std::vector<float>(v)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<float>* push(const float& v)
	{
		std::vector<float>::push_back(v);
		return this;
	}

	//////////////////////////////////////////////////////////////////////////////////
	float pop()
	{
		float ret = std::vector<float>::back();
		std::vector<float>::pop_back();
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<float>* slice(int first, int last)
	{
		return new Array<float>(std::vector<float>(std::vector<float>::begin() + first, std::vector<float>::begin() + last));
	}

	//////////////////////////////////////////////////////////////////////////////////
	void splice(int index, int count)
	{
		std::vector<float>::erase(std::vector<float>::begin() + index, std::vector<float>::begin() + index + count);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<float>* operator()(float v)
	{
		this->push(v);
		return this;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class String : public std::string
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	operator bool() const
	{
		return !empty();
	}

	//////////////////////////////////////////////////////////////////////////////////
	String& operator =(const char* c_str)
	{
		std::string::operator=(c_str);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////
	String& operator =(String str)
	{
		std::string::operator=(str);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////
	String& operator =(std::string str)
	{
		std::string::operator=(str);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////
	String() = default;

	//////////////////////////////////////////////////////////////////////////////////
	String(const char* str) : std::string(str)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	String(const std::string& str) : std::string(str)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	String substr(size_t start, size_t length = std::string::npos)
	{
		return std::string::substr(start, length);
	}

	//////////////////////////////////////////////////////////////////////////////////
	String substring(size_t start, size_t end = 0)
	{
		return std::string::substr(start, end - start);
	}

	//////////////////////////////////////////////////////////////////////////////////
	size_t indexOf(const String& str, size_t pos = 0)
	{
		return find(str, pos);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<String>* split(const String& str, size_t max = -1)
	{
		Array<String>* ret = new Array<String>();
		size_t pos = 0, next = 0;
		while(ret->size() < max && next != std::string::npos)
		{
			next = find(str, pos);
			ret->push(substring(pos, next));
			pos = next + str.size();
		}
		return ret;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> std::string toString(T v)
{
	std::stringstream ss;
	ss<<v;
	return ss.str();
}

typedef int Color;
typedef String Gradient;
#define parseFloat(S) atof((S).c_str())

////////////////////////////////////////////////////////////////////////////////////////////////////
struct State
{
	String __name;
	virtual void enter() {}
	virtual void exit() {}
	virtual void tick(float time) = 0;
	virtual void paint(WebGLRenderingContext* gl, float time) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef IOS_APPLICATION

	#define PLATFORM "iOS"

	#include <UIKit/UIEvent.h>
	#include <UIKit/UITouch.h>
	#include <sys/time.h>

	#define fxAPIGetKey(E) (*(const uint32_t*)(E))
	#define fxAPIGetMouseEventX(E) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].x)
	#define fxAPIGetMouseEventY(E) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].y)
	#define fxAPIGetTouchEventX(E, I) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
	#define fxAPIGetTouchEventY(E, I) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
	#define fxAPIGetChangedTouchEventX(E, I) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
	#define fxAPIGetChangedTouchEventY(E, I) ([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
	#define fxAPIGetTouchesLength(E) ([[(__bridge UIEvent*)E allTouches] count])
	#define fxAPIGetChangedTouchesLength(E) ([[(__bridge UIEvent*)E allTouches] count])

////////////////////////////////////////////////////////////////////////////////////////////////////
#elif ANDROID_APPLICATION

	#define PLATFORM "Android"

	#include <chrono>
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

class Date
{
	unsigned long long millis;
public:
	Date()
	{
		struct timeval tv;
		gettimeofday(&tv, nullptr);
		millis = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
	}
	unsigned long long getTime() { return millis; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Externs for global objects
////////////////////////////////////////////////////////////////////////////////////////////////////

extern void trace(const char* fmt, ...);
extern CocoEngine* engine;
extern HTMLWindow* window;
extern HTMLDocument* document;

#endif //__COCONUT2D_HPP__

