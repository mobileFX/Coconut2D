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
#include <cstdarg>

// ==================================================================================================================================
//	    ___
//	   /   |  ______________ ___  __
//	  / /| | / ___/ ___/ __ `/ / / /
//	 / ___ |/ /  / /  / /_/ / /_/ /
//	/_/  |_/_/  /_/   \__,_/\__, /
//	                       /____/
// ==================================================================================================================================
template<class T> class Array : public std::vector<T>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<T>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	size_t size()
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

// ==================================================================================================================================
//	   _____ __       _
//	  / ___// /______(_)___  ____ _
//	  \__ \/ __/ ___/ / __ \/ __ `/
//	 ___/ / /_/ /  / / / / / /_/ /
//	/____/\__/_/  /_/_/ /_/\__, /
//	                      /____/
// ==================================================================================================================================
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

// ==================================================================================================================================
//	    ___                          ____        ________
//	   /   |  ______________ ___  __/ __ )__  __/ __/ __/__  _____
//	  / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/
//	 / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /
//	/_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/
//	                       /____/
// ==================================================================================================================================

class AssetFile;

class ArrayBuffer
{
public:
	void* data;
	unsigned long byteLength;

	//////////////////////////////////////////////////////////////////////////////////
	ArrayBuffer(unsigned long length)
	{
		data = malloc(length);
		byteLength = length;
	}

	//////////////////////////////////////////////////////////////////////////////////
	~ArrayBuffer()
	{
		free(data);
	}

	//////////////////////////////////////////////////////////////////////////////////
	void* operator[](unsigned long i)
	{
		assert(i < byteLength);
		return reinterpret_cast<void*>(reinterpret_cast<char*>(data) + i);
	}

	//////////////////////////////////////////////////////////////////////////////////
	static ArrayBuffer* NewFromImage(std::string str, uint32_t& width, uint32_t& height);
	String encodeAsBase64();

	//////////////////////////////////////////////////////////////////////////////////
	#ifdef ENABLE_PNG_SUPPORT
		static ArrayBuffer* NewFromImage_PNG(AssetFile* file, uint32_t& width, uint32_t& height);
		ArrayBuffer* encodeAsPNG(size_t width, size_t height);
	#endif

	//////////////////////////////////////////////////////////////////////////////////
	#ifdef ENABLE_JPG_SUPPORT
		static ArrayBuffer* NewFromImage_JPG(AssetFile* file, uint32_t& width, uint32_t& height);
	#endif
};

// ==================================================================================================================================
//	    ___                          ____        ________         _    ___
//	   /   |  ______________ ___  __/ __ )__  __/ __/ __/__  ____| |  / (_)__ _      __
//	  / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/ | / / / _ \ | /| / /
//	 / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /   | |/ / /  __/ |/ |/ /
//	/_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/    |___/_/\___/|__/|__/
//	                       /____/
// ==================================================================================================================================
class ArrayBufferView
{
public:
	ArrayBuffer* buffer;
	unsigned long byteOffset;
	unsigned long byteLength;

	//////////////////////////////////////////////////////////////////////////////////
	void* get()
	{
		return reinterpret_cast<void*>(reinterpret_cast<char*>(buffer->data) + byteOffset);
	}
};

// ==================================================================================================================================
//	  ______                     _____
//	 /_  __/_  ______  ___  ____/ /   |  ______________ ___  __
//	  / / / / / / __ \/ _ \/ __  / /| | / ___/ ___/ __ `/ / / /
//	 / / / /_/ / /_/ /  __/ /_/ / ___ |/ /  / /  / /_/ / /_/ /
//	/_/  \__, / .___/\___/\__,_/_/  |_/_/  /_/   \__,_/\__, /
//	    /____/_/                                      /____/
// ==================================================================================================================================
template<typename T> class TypedArray : public ArrayBufferView
{
public:
	const unsigned long BYTES_PER_ELEMENT = sizeof(T);
	unsigned long length;

	TypedArray(size_t size)
	{
		length = size;
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memset(buffer->data, 0, buffer->byteLength);
	}

	TypedArray(ArrayBuffer* i_buffer, size_t i_byteOffset = 0, size_t i_length = -1)
	{
		buffer = i_buffer;
		byteOffset = i_byteOffset;
		length = std::min(size_t((i_buffer->byteLength - i_byteOffset) / sizeof(T)), i_length);
		byteLength = length * sizeof(T);
	}

	TypedArray(Array<T>* val, bool preserve = false)
	{
		length = val->size();
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memcpy(buffer->data, val->data(), buffer->byteLength);
		if(!preserve) delete val;
	}

	~TypedArray() { delete buffer; }

	T* get() { return reinterpret_cast<T*>(ArrayBufferView::get()); }
	T& operator [](unsigned long index)
	{
		return get()[index];
	}
};

// ==================================================================================================================================
//	  ______                     _____
//	 /_  __/_  ______  ___  ____/ /   |  ______________ ___  _______
//	  / / / / / / __ \/ _ \/ __  / /| | / ___/ ___/ __ `/ / / / ___/
//	 / / / /_/ / /_/ /  __/ /_/ / ___ |/ /  / /  / /_/ / /_/ (__  )
//	/_/  \__, / .___/\___/\__,_/_/  |_/_/  /_/   \__,_/\__, /____/
//	    /____/_/                                      /____/
// ==================================================================================================================================

typedef TypedArray<char> Int8Array;
typedef TypedArray<unsigned char> Uint8Array;
typedef TypedArray<unsigned char> Uint8ClampedArray;
typedef TypedArray<short> Int16Array;
typedef TypedArray<unsigned short> Uint16Array;
typedef TypedArray<int> Int32Array;
typedef TypedArray<unsigned int> Uint32Array;
typedef TypedArray<float> Float32Array;
typedef TypedArray<double> Float64Array;


// ==================================================================================================================================
//	    ______                                   __   ________                   ____            __                 __  _
//	   / ____/___  ______      ______ __________/ /  / ____/ /___ ___________   / __ \___  _____/ /___ __________ _/ /_(_)___  ____  _____
//	  / /_  / __ \/ ___/ | /| / / __ `/ ___/ __  /  / /   / / __ `/ ___/ ___/  / / / / _ \/ ___/ / __ `/ ___/ __ `/ __/ / __ \/ __ \/ ___/
//	 / __/ / /_/ / /   | |/ |/ / /_/ / /  / /_/ /  / /___/ / /_/ (__  |__  )  / /_/ /  __/ /__/ / /_/ / /  / /_/ / /_/ / /_/ / / / (__  )
//	/_/    \____/_/    |__/|__/\__,_/_/   \__,_/   \____/_/\__,_/____/____/  /_____/\___/\___/_/\__,_/_/   \__,_/\__/_/\____/_/ /_/____/
//
// ==================================================================================================================================

//# Native Classes Begin #//
class Audio;
class CocoEventConnectionPoint;
class CocoEventSource;
class CocoFont;
class EventTarget;
class HTMLWindow;
class IEventListener;
class ImageData;
class WebGLBuffer;
class WebGLFramebuffer;
class WebGLObject;
class WebGLProgram;
class WebGLRenderbuffer;
class WebGLRenderingContext;
class WebGLShader;
class WebGLTexture;
class WebGLUniformLocation;
class XMLHttpRequest;
struct CocoFontChar;
struct GLany;
//# Native Classes End #//

//# Generated Classes Begin #//
class CanvasRenderingContext2D;
class ClassTestInterfaces;
class CocoAudio;
class CocoClip;
class CocoClipOnClickEvent;
class CocoClipOnDblClickEvent;
class CocoClipOnTouchCancelEvent;
class CocoClipOnTouchEndEvent;
class CocoClipOnTouchMoveEvent;
class CocoClipOnTouchStartEvent;
class CocoEngine;
class CocoEvent;
class CocoGraphics;
class CocoImage;
class CocoImageRenderData2D;
class CocoImageRenderDataGL;
class CocoImageSibling;
class CocoMatrix;
class CocoRect;
class CocoRenderContext2D;
class CocoRenderContext;
class CocoRenderContextGL;
class CocoScene;
class CocoSequence;
class CocoText;
class CocoTextStyle;
class CocoTickable;
class CocoTimeLabel;
class CocoTimeline;
class CocoUIButton;
class CocoUICheckBox;
class CocoUIComboBox;
class CocoUIControl;
class CocoUILabel;
class CocoUIPageView;
class CocoUITextBox;
class CocoUIView;
class CocoVector;
class GameEngine;
class HTMLCanvasElement;
class HTMLCanvasGradient;
class HTMLCanvasPattern;
class HTMLDocument;
class HTMLElement;
class HTMLEvent;
class HTMLTextMetrics;
class ICocoImageRenderData;
class ICocoRenderContext;
class IEventTarget;
class ITest1;
class ITest2;
class ITest3;
class ITickable;
class Image;
class NewAnimation;
class Page1;
class PathLine;
class Touch;
class TouchList;
class UIButtonClass;
class UIFormClass;
class UITextBoxClass;
class UITextBoxClassOnChangeEvent;
struct CocoKeyFrame;
struct DEVICE_MESSAGE;
//# Generated Classes End #//

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

#define JSINTERVAL_MIN 4
#define JSTOUCHLIST_MAX_LENGTH 5
#define SHADER_SOURCE_BUFFER_SIZE 4096
#define INFO_LOG_BUFFER_SIZE 4096
#define fxObjectUID size_t

#define parseFloat(S) atof((S).c_str())
#define parseInt(S) atoi((S).c_str())
#define TODO() trace("TODO:%s @ %s:%d", __PRETTY_FUNCTION__, __FILE__, __LINE__)

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

typedef int Color;

// ==================================================================================================================================
//	   ______      ______               __
//	  / ____/___ _/ / / /_  ____ ______/ /_______
//	 / /   / __ `/ / / __ \/ __ `/ ___/ //_/ ___/
//	/ /___/ /_/ / / / /_/ / /_/ / /__/ ,< (__  )
//	\____/\__,_/_/_/_.___/\__,_/\___/_/|_/____/
//
// ==================================================================================================================================

typedef void (CocoScene::*CocoAction)();
typedef void (CocoEngine::*CocoEventAction)(HTMLEvent* e);

// ==================================================================================================================================
//	  ______                     __      __
//	 /_  __/__  ____ ___  ____  / /___ _/ /____  _____
//	  / / / _ \/ __ `__ \/ __ \/ / __ `/ __/ _ \/ ___/
//	 / / /  __/ / / / / / /_/ / / /_/ / /_/  __(__  )
//	/_/  \___/_/ /_/ /_/ .___/_/\__,_/\__/\___/____/
//	                  /_/
// ==================================================================================================================================

template<class T> using Stack = std::stack<T>;
template<class T> using Dictionary = std::map<std::string, T>;
template<class T> using Index = std::map<size_t, T>;



// ==================================================================================================================================
//	    ___                          __    __                ____
//	   /   |  ______________ ___  __/ /   / /_  ____  ____  / /\ \
//	  / /| | / ___/ ___/ __ `/ / / / /   / __ \/ __ \/ __ \/ /  \ \
//	 / ___ |/ /  / /  / /_/ / /_/ /\ \  / /_/ / /_/ / /_/ / /   / /
//	/_/  |_/_/  /_/   \__,_/\__, /  \_\/_.___/\____/\____/_/   /_/
//	                       /____/
// ==================================================================================================================================
template<> class Array<bool> : public std::vector<bool>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<bool>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	size_t size()
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

// ==================================================================================================================================
//	    ___                          __    ______            ____
//	   /   |  ______________ ___  __/ /   / __/ /___  ____ _/ /\ \
//	  / /| | / ___/ ___/ __ `/ / / / /   / /_/ / __ \/ __ `/ __/\ \
//	 / ___ |/ /  / /  / /_/ / /_/ /\ \  / __/ / /_/ / /_/ / /_  / /
//	/_/  |_/_/  /_/   \__,_/\__, /  \_\/_/ /_/\____/\__,_/\__/ /_/
//	                       /____/
// ==================================================================================================================================
template<> class Array<float> : public std::vector<float>
{
public:

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<float>()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	size_t size()
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
template<class T> std::string toString(T v)
{
	std::stringstream ss;
	ss<<v;
	return ss.str();
}

typedef String Gradient;

// ==================================================================================================================================
//	   _____ __        __
//	  / ___// /_____ _/ /____
//	  \__ \/ __/ __ `/ __/ _ \
//	 ___/ / /_/ /_/ / /_/  __/
//	/____/\__/\__,_/\__/\___/
//
// ==================================================================================================================================
struct State
{
	String __name;
	virtual void enter() {}
	virtual void exit() {}
	virtual void tick(float time) = 0;
	virtual void paint(ICocoRenderContext* ctx, float time) {}
};

// ==================================================================================================================================
//	  ______                      __     _____                 _ _____
//	 /_  __/___ __________ ____  / /_   / ___/____  ___  _____(_) __(_)____
//	  / / / __ `/ ___/ __ `/ _ \/ __/   \__ \/ __ \/ _ \/ ___/ / /_/ / ___/
//	 / / / /_/ / /  / /_/ /  __/ /_    ___/ / /_/ /  __/ /__/ / __/ / /__
//	/_/  \__,_/_/   \__, /\___/\__/   /____/ .___/\___/\___/_/_/ /_/\___/
//	               /____/                 /_/
// ==================================================================================================================================

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
#elif WIN32_APPLICATION
	#include <windows.h>
	#include <windowsx.h>

	#undef near
	#undef far

	#ifndef M_PI
	#define M_PI		3.14159265358979323846
	#endif

	#ifndef M_PI_2
	#define M_PI_2		1.57079632679489661923
	#endif

	#define fxAPIGetMouseEventX(E) GET_X_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetMouseEventY(E) GET_Y_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetTouchEventX(E, I) GET_X_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetTouchEventY(E, I) GET_Y_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetChangedTouchEventX(E, I) GET_X_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetChangedTouchEventY(E, I) GET_Y_LPARAM(((MSG*)E)->lParam)
	#define fxAPIGetTouchesLength(E) 1
	#define fxAPIGetChangedTouchesLength(E) 1

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
	#ifndef CURL_STATICLIB
	#define CURL_STATICLIB
	#endif
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
	#elif WIN32_APPLICATION
		#include <GL/glew.h>
		/*#include <GL/glut.h>*/
		#include <GL/gl.h>
	#else
		#include <QtOpenGL/QtOpenGL>
	#endif
#elif !DISABLE_OPENGL_SUPPORT
	#warning "Building without OpenGL support!"
#endif

// ==================================================================================================================================
//	    ____        __
//	   / __ \____ _/ /____
//	  / / / / __ `/ __/ _ \
//	 / /_/ / /_/ / /_/  __/
//	/_____/\__,_/\__/\___/
//
// ==================================================================================================================================
class Date
{
	unsigned long long millis;
public:
	Date()
	{
		#ifdef WIN32_APPLICATION
			FILETIME filetime;
			GetSystemTimeAsFileTime(&filetime);
			millis = ((LONGLONG)filetime.dwLowDateTime + ((LONGLONG)(filetime.dwHighDateTime) << 32LL)) / 10000 + 116444736000000000LL;
		#else
			struct timeval tv;
			gettimeofday(&tv, nullptr);
			millis = (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
		#endif
	}
	unsigned long long getTime() { return millis; }
};


// ==================================================================================================================================
//	    ______     __
//	   / ____/  __/ /____  _________  _____
//	  / __/ | |/_/ __/ _ \/ ___/ __ \/ ___/
//	 / /____>  </ /_/  __/ /  / / / (__  )
//	/_____/_/|_|\__/\___/_/  /_/ /_/____/
//
// =================================================================================================================================

extern void trace(const char* fmt, ...);
extern CocoEngine* engine;
extern HTMLWindow* window;
extern HTMLDocument* document;
extern HTMLWindow* global;

#endif //__COCONUT2D_HPP__

