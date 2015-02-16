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
#define NGLDEBUG

#ifndef M_PI
#define M_PI				3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2				1.57079632679489661923
#endif

#ifndef RADIANS
#define RADIANS				0.01745329251994329576
#endif

#ifndef DEGREES
#define DEGREES			   57.29577951308232087679
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Common Includes
////////////////////////////////////////////////////////////////////////////////////////////////////

extern void trace(const char* fmt, ...);

#include "Structs.h"

#include <cmath>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <cstring>
#include <clocale>

#include <algorithm>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "UTF8/UTF8.hpp"

#ifdef __CPP_0X__
	#include <initializer_list>
#endif

#if ANDROID_APPLICATION
	#ifndef UINT
		#define UINT unsigned int
	#endif
#endif

#if IOS_APPLICATION
	#ifndef UINT
		#define UINT unsigned int
	#endif
#endif

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
	std::string __className;

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<T>()
	{
		__className = "Array";
	}

	//////////////////////////////////////////////////////////////////////////////////
	size_t size()
	{
		return std::vector<T>::size();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array(size_t size, ...) : std::vector<T>(size)
	{
		// This fails with Enums even in C++11.
		va_list vl;
		va_start(vl, size);
		for(size_t i=0; i<size; i++)
		{
			T v = (T) va_arg(vl, T);
			this->at(i) = v;
		}
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
	Array<T>* concat(Array<T>* arr)
	{
		Array<T>* n = new Array<T>(std::vector<T>(std::vector<T>::begin(), std::vector<T>::end()));
		n->insert(n->end(), arr->begin(), arr->end());
		return n;
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
	Array<T>* reverse()
	{
		std::reverse(std::vector<T>::begin(), std::vector<T>::end());
		return this;
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
	String slice(size_t start, size_t end = std::string::npos)
	{
		if(end==0) end = this->size();
		size_t length = end - start;
		return std::string::substr(start, length);
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
	unsigned char charCodeAt(size_t index)
	{
		return std::string::at(index);
	}

	//////////////////////////////////////////////////////////////////////////////////
	static String fromCharCode(int c)
	{
		if(c<128) return std::string(1,c);

		// Depending on the compiler and C runtime, wcstombs() might fail.

	    const wchar_t wstr = (wchar_t) c;
	    char mbstr[3] = {0,0,0};

	    #ifdef __UTF8_HPP__
	    	int ret = UTF8::wcstombs(mbstr, &wstr, 2);
	    #else
		    std::setlocale(LC_ALL, "en_US.utf-8");
	    	int ret = std::wcstombs(mbstr, &wstr, 2);
	    #endif

		if(ret==-1) return std::string(1,'?');
	    return std::string(mbstr);
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

class CocoAssetFile;

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
		if(i>=byteLength) return reinterpret_cast<void*>(0);
		return reinterpret_cast<void*>(reinterpret_cast<char*>(data) + i);
	}

	//////////////////////////////////////////////////////////////////////////////////
	static ArrayBuffer* NewFromImage(std::string str, uint32_t& width, uint32_t& height);
	static ArrayBuffer* NewFromImage_PNG(CocoAssetFile* file, uint32_t& width, uint32_t& height);
	static ArrayBuffer* NewFromImage_JPG(CocoAssetFile* file, uint32_t& width, uint32_t& height);
	String encodeAsBase64();
	ArrayBuffer* encodeAsPNG(size_t width, size_t height);
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
	void clear()
	{
		memset((*buffer)[byteOffset], 0, byteLength);
	}

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
	unsigned long BYTES_PER_ELEMENT;
	unsigned long length;
	bool owner;

	TypedArray(size_t size)
	{
		int cb = BYTES_PER_ELEMENT = sizeof(T);
		owner = true;
		length = size;
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memset(buffer->data, 0, buffer->byteLength);
	}

	TypedArray(ArrayBuffer* i_buffer, size_t i_byteOffset = 0, size_t i_length = -1)
	{
		BYTES_PER_ELEMENT = sizeof(T);
		owner = false;
		buffer = i_buffer;
		byteOffset = i_byteOffset;
		size_t t = (i_buffer->byteLength - i_byteOffset) / sizeof(T);
		length = t < i_length ? t : i_length;
		byteLength = length * sizeof(T);
	}

	TypedArray(Array<T>* val, bool preserve = false)
	{
		BYTES_PER_ELEMENT = sizeof(T);
		owner = true;
		length = val->size();
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memcpy(buffer->data, val->data(), buffer->byteLength);
		if(!preserve) delete val;
	}

	void set(TypedArray<T>* val, unsigned long offset = 0)
	{
		if(val->length + offset > this->length) return;
		memcpy((*this->buffer)[this->byteOffset + offset * BYTES_PER_ELEMENT], (*val->buffer)[val->byteOffset], val->length * BYTES_PER_ELEMENT);
	}

	~TypedArray() { if(owner) delete buffer; }

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

typedef TypedArray<unsigned char> Uint8Array;
typedef TypedArray<unsigned short> Uint16Array;
typedef TypedArray<unsigned int> Uint32Array;
typedef TypedArray<unsigned int> Uint64Array;

typedef TypedArray<char> Int8Array;
typedef TypedArray<short> Int16Array;
typedef TypedArray<int> Int32Array;
typedef TypedArray<int> Int64Array;

typedef TypedArray<float> Float32Array;
typedef TypedArray<double> Float64Array;

typedef TypedArray<unsigned char> Uint8ClampedArray;


// ==================================================================================================================================
//	    ____        __       _    ___
//	   / __ \____ _/ /_____ | |  / (_)__ _      __
//	  / / / / __ `/ __/ __ `/ | / / / _ \ | /| / /
//	 / /_/ / /_/ / /_/ /_/ /| |/ / /  __/ |/ |/ /
//	/_____/\__,_/\__/\__,_/ |___/_/\___/|__/|__/
//
// ==================================================================================================================================
class DataView : ArrayBufferView
{
public:
	DataView(ArrayBuffer* i_buffer, unsigned long i_byteOffset = 0, unsigned long i_byteLength = -1)
	{
		buffer = i_buffer;
		byteOffset = i_byteOffset;
		byteLength = std::min(i_byteLength, buffer->byteLength);
	}

	template<class T> T* get(unsigned long offset) { return reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(ArrayBufferView::get()) + offset); }
	template<class T> T flip(T val, bool littleEndian)
	{
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			if(littleEndian) return val;
		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			if(!littleEndian) return val;
		#else
			#error "Platform not supported!"
		#endif
		unsigned char t;
		unsigned char* v = reinterpret_cast<unsigned char*>(&val);
		for(uint8_t i = 0; i < sizeof(T) / 2; i++)
		{
			t = *(v + i);
			*(v + i) = *(v + sizeof(T) - 1 - i);
			*(v + sizeof(T) - 1 - i) = t;
		}
		return val;
	}

	char getInt8(unsigned long offset) { return *get<char>(offset); }
	unsigned char getUint8(unsigned long offset) { return *get<unsigned char>(offset); }
	short getInt16(unsigned long offset, bool littleEndian = false) { return flip(*get<short>(offset), littleEndian); }
	unsigned short getUint16(unsigned long offset, bool littleEndian = false) { return flip(*get<short>(offset), littleEndian); }
	long getInt32(unsigned long offset, bool littleEndian = false) { return flip(*get<long>(offset), littleEndian); }
	unsigned long getUint32(unsigned long offset, bool littleEndian = false) { return flip(*get<unsigned long>(offset), littleEndian); }
	float getFloat32(unsigned long offset, bool littleEndian = false) { return flip(*get<float>(offset), littleEndian); }
	double getFloat64(unsigned long offset, bool littleEndian = false) { return flip(*get<double>(offset), littleEndian); }

	void setInt8(unsigned long offset, char val) { *get<char>(offset) = val; }
	void setUint8(unsigned long offset, unsigned char val) { *get<unsigned char>(offset) = val; }
	void setInt16(unsigned long offset, short val, bool littleEndian = false) { *get<short>(offset) = flip(val, littleEndian); }
	void setUint16(unsigned long offset, unsigned short val, bool littleEndian = false) { *get<unsigned short>(offset) = flip(val, littleEndian); }
	void setInt32(unsigned long offset, long val, bool littleEndian = false) { *get<long>(offset) = flip(val, littleEndian); }
	void setUint32(unsigned long offset, unsigned long val, bool littleEndian = false) { *get<unsigned long>(offset) = flip(val, littleEndian); }
	void setFloat32(unsigned long offset, float val, bool littleEndian = false) { *get<float>(offset) = flip(val, littleEndian); }
	void setFloat64(unsigned long offset, double val, bool littleEndian = false) { *get<double>(offset) = flip(val, littleEndian); }

};

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
class CocoAssetFile;
class CocoAudioStream;
class CocoDeviceWrapper;
class CocoEventConnectionPoint;
class CocoEventSource;
class CocoFont;
class CocoFontsCache;
class CocoJSON;
class GameEngine;
class HTMLVideoElement;
class HTMLWindow;
class IEventListener;
class ImageData;
class ReservationsForm;
class UTF8;
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
struct GLEWContextStruct;
struct GLany;
struct STATE_DATASET_TEST;
struct STATE_SHOW_FORM;
struct STATE_START_APP;
struct __GLsync;
struct _cl_context;
struct _cl_event;
struct fxScreen;
//# Native Classes End #//

//# Generated Classes Begin #//
class CanvasRenderingContext2D;
class CocoAppController;
class CocoAudio;
class CocoBezier;
class CocoClip;
class CocoDataField;
class CocoDataRow;
class CocoDataSource;
class CocoDataStream;
class CocoDataset;
class CocoDevice;
class CocoEngine;
class CocoEvent;
class CocoGraphics;
class CocoHttpRequest;
class CocoImage;
class CocoImageRenderData2D;
class CocoImageRenderDataGL;
class CocoImageResolution;
class CocoLocalStorage;
class CocoMaskClip;
class CocoMatrix;
class CocoRenderContext2D;
class CocoRenderContext;
class CocoRenderContextCSS3;
class CocoRenderContextGL;
class CocoScene;
class CocoSelfTexturedClip;
class CocoSequence;
class CocoShader;
class CocoShaderBoundingBox;
class CocoShaderCommon;
class CocoShaderParallaxHor;
class CocoShaderSaturationWithAlpha;
class CocoShaderSimple;
class CocoShaderSimpleWithAlpha;
class CocoText;
class CocoTextBlock;
class CocoTextClip;
class CocoTextStyle;
class CocoTimeLabel;
class CocoTimeline;
class CocoUIButton;
class CocoUICheckBox;
class CocoUIComboBox;
class CocoUIControl;
class CocoUIFormView;
class CocoUILabel;
class CocoUINavBar;
class CocoUIPictureList;
class CocoUIScrollView;
class CocoUITabBar;
class CocoUITextEdit;
class CocoUIView;
class CocoVector;
class CocoVideo;
class Data;
class GameEngine;
class HTMLAnchorElement;
class HTMLCanvasElement;
class HTMLCanvasGradient;
class HTMLCanvasPattern;
class HTMLDivElement;
class HTMLDocument;
class HTMLElement;
class HTMLEvent;
class HTMLLocation;
class HTMLNavigator;
class HTMLScreen;
class HTMLStyleElement;
class HTMLTextMetrics;
class ICocoImageRenderData;
class ICocoRenderContext;
class IEventTarget;
class ITickable;
class Image;
class NewAnimation;
class OnClickHandler;
class PathLine;
class ReservationsForm;
class Touch;
class TouchList;
struct CocoHVAlign;
struct CocoKeyFrame;
struct CocoMatrixData;
struct CocoPoint;
struct CocoRect;
struct CocoRequestNameValuePair;
struct CocoSkinCacheItem;
struct ContextArguments;
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

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T> std::string toString(T v)
{
	std::stringstream ss;
	ss<<v;
	return ss.str();
}

typedef String Gradient;

#ifndef __CPP_0X__

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
		//this->resize(size);
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
		//this->resize(size);
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

#endif

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
	long long millis;
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
			millis = (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
		#endif
	}
	long long getTime() { return millis; }
};


// ==================================================================================================================================
//	    ______     __
//	   / ____/  __/ /____  _________  _____
//	  / __/ | |/_/ __/ _ \/ ___/ __ \/ ___/
//	 / /____>  </ /_/  __/ /  / / / (__  )
//	/_____/_/|_|\__/\___/_/  /_/ /_/____/
//
// =================================================================================================================================

extern CocoEngine* engine;
extern HTMLWindow* window;
extern HTMLDocument* document;
extern HTMLWindow* global;

extern void __Facebook_Initialize(String AppID, int ImageSize);
extern void __Facebook_Login(String Permissions, int ImageSize);
extern void __Facebook_Post(String toUserID, String URL);
extern void __Facebook_Share(String URL);
extern void __Facebook_Invite(String message);
extern String md5(String data);

extern String encodeURIComponent(String uri);
extern void fixTouch(Touch* touch);

#endif //__COCONUT2D_HPP__

