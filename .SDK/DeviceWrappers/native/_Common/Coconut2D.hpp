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

///Applications/Xcode.app/Contents/Frameworks/IDEKit.framework/Resources/IDETextKeyBindingSet.plist

#ifndef __COCONUT2D_HPP__
#define __COCONUT2D_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Application-wide constants
///////////////////////////////////////////////////////////////////////////////////////////////////

#define APPNAME                         "Coconut2D"
#define GLOBAL_FPS                      30.0f
#define COCO_STOP_ON_CURRENT_FRAME      -1

#ifndef M_PI
#define M_PI                            3.14159265358979323846f
#endif

#ifndef M_PI_2
#define M_PI_2                          1.57079632679489661923f
#endif

#ifndef RADIANS
#define RADIANS                         0.01745329251994329576f
#endif

#ifndef DEGREES
#define DEGREES                         57.29577951308232087679f
#endif

#define COCO_DELETE_OBJECT(O) if(O){delete O; O=nullptr;}
#define COCO_DELETE_ARRAY(A) if(A){delete A; A=nullptr;}

#define trace(v)					\
{                                   \
	std::stringstream ss;           \
	ss << v << "\n";                \
	std::cout << ss.str();          \
}                                   \

////////////////////////////////////////////////////////////////////////////////////////////////////
// STL Includes
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <stdarg.h>

#include <clocale>
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <tgmath.h>
#include <algorithm>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <stdio.h>
#include <typeinfo>
#include <memory>
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <initializer_list>

#define ENABLE_BOOST 1

// Boost RegEx are much faster than STL
#ifdef ENABLE_BOOST

	#include <boost/locale/encoding_utf.hpp>
	#include <boost/regex.hpp>

	using boost::locale::conv::utf_to_utf;

	std::wstring utf8_to_wstring(const std::string& str)
	{
	    return utf_to_utf<wchar_t>(str.c_str(), str.c_str() + str.size());
	}

	std::string wstring_to_utf8(const std::wstring& str)
	{
	    return utf_to_utf<char>(str.c_str(), str.c_str() + str.size());
	}

#else

	#include <regex>

	std::wstring utf8_to_wstring(const std::string& str)
	{
	    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	    return conv.from_bytes(str);
	}

	std::string wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		return conv.to_bytes(w);
	}

#endif

//////////////////////////////////////////////////////////////////////////////////
// UINT definition
#if ANDROID_APPLICATION
#ifndef UINT
#define UINT uint32_t
#endif
#endif

typedef uint32_t Color;

#include <utility>

#if ANDROID_APPLICATION
	namespace std
	{
		int32_t round(float n);
		int32_t round(int32_t n);
	}
#endif

#define math_floor(n)		(int32_t)std::floor(n)
#define math_ceil(n)        (int32_t)std::ceil(n)
#define math_log(n)         (float)std::log(n)
#define math_abs(n)         std::abs(n)
#define math_sqrt(n)        (float)std::sqrt(n)
#define math_round(n)       (int32_t)std::round(n)
#define math_asin(n)        (float)std::asin(n)
#define math_acos(n)        (float)std::acos(n)
#define math_sin(n)         (float)std::sin(n)
#define math_cos(n)         (float)std::cos(n)

#define math_min(A,B)     	((float)(A) < (float)(B) ? (A) : (B) )
#define math_max(A,B)     	((float)(A) > (float)(B) ? (A) : (B) )

#define math_pow(B,E)    	(int32_t) std::pow( (float)B, (float)E )
#define math_random() 		(float) ((float)rand()/(float)RAND_MAX)

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

    #define fxAPIGetKey(E)                          (int32_t)(*(const uint32_t*)(E))
    #define fxAPIGetMouseEventX(E)                  (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].x)
    #define fxAPIGetMouseEventY(E)                  (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].y)
    #define fxAPIGetTouchEventX(E, I)               (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: (size_t)I] locationInView:nil].x)
    #define fxAPIGetTouchEventY(E, I)               (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: (size_t)I] locationInView:nil].y)
    #define fxAPIGetChangedTouchEventX(E, I)        (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: (size_t)I] locationInView:nil].x)
    #define fxAPIGetChangedTouchEventY(E, I)        (int32_t)([[[[(__bridge UIEvent*)E allTouches] allObjects] objectAtIndex: (size_t)I] locationInView:nil].y)
    #define fxAPIGetTouchesLength(E)                (int32_t)([[(__bridge UIEvent*)E allTouches] count])
    #define fxAPIGetChangedTouchesLength(E)         (int32_t)([[(__bridge UIEvent*)E allTouches] count])

////////////////////////////////////////////////////////////////////////////////////////////////////
#elif ANDROID_APPLICATION

    #define PLATFORM "Android"

    #include <chrono>
    #include <jni.h>
    #include <android_native_app_glue.h>

    #define fxAPIGetMouseEventX(E)                  (AMotionEvent_getX((AInputEvent*)E, 0) * engine->device->pixelRatio)
    #define fxAPIGetMouseEventY(E)                  (AMotionEvent_getY((AInputEvent*)E, 0) * engine->device->pixelRatio)
    #define fxAPIGetTouchEventX(E, I)               (AMotionEvent_getX((AInputEvent*)E, I) * engine->device->pixelRatio)
    #define fxAPIGetTouchEventY(E, I)               (AMotionEvent_getY((AInputEvent*)E, I) * engine->device->pixelRatio)
    #define fxAPIGetChangedTouchEventX(E, I)        (AMotionEvent_getX((AInputEvent*)E, I) * engine->device->pixelRatio)
    #define fxAPIGetChangedTouchEventY(E, I)        (AMotionEvent_getY((AInputEvent*)E, I) * engine->device->pixelRatio)
    #define fxAPIGetTouchesLength(E)                AMotionEvent_getPointerCount((AInputEvent*)E)
    #define fxAPIGetChangedTouchesLength(E)         AMotionEvent_getPointerCount((AInputEvent*)E)

////////////////////////////////////////////////////////////////////////////////////////////////////
#elif WIN32_APPLICATION

    #include <windows.h>
    #include <windowsx.h>

    #undef near
    #undef far

    #define fxAPIGetMouseEventX(E)                  GET_X_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetMouseEventY(E)                  GET_Y_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetTouchEventX(E, I)               GET_X_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetTouchEventY(E, I)               GET_Y_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetChangedTouchEventX(E, I)        GET_X_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetChangedTouchEventY(E, I)        GET_Y_LPARAM(((MSG*)E)->lParam)
    #define fxAPIGetTouchesLength(E)                1
    #define fxAPIGetChangedTouchesLength(E)         1

////////////////////////////////////////////////////////////////////////////////////////////////////
#else

    #define PLATFORM "General"

    #define fxAPIGetKey(E)                          (*(const uint32_t*)(E))
    #define fxAPIGetMouseEventX(E)                  (((QMouseEvent*)(E))->x())
    #define fxAPIGetMouseEventY(E)                  (((QMouseEvent*)(E))->y())
    #define fxAPIGetTouchEventX(E, I)               (((QMouseEvent*)(E))->x())
    #define fxAPIGetTouchEventY(E, I)               (((QMouseEvent*)(E))->y())
    #define fxAPIGetChangedTouchEventX(E, I)        (((QMouseEvent*)(E))->x())
    #define fxAPIGetChangedTouchEventY(E, I)        (((QMouseEvent*)(E))->y())
    #define fxAPIGetTouchesLength(E)                (((QEvent*)(E))->type() == QEvent::MouseButtonRelease ? 0 : 1)
    #define fxAPIGetChangedTouchesLength(E)         1

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// PNG Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <png.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// JPEG Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#undef FALSE
#undef TRUE

#include <jpeglib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// OGG Vorbis Tremolo Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#define AUDIO_SAMPLE_SIZE 2
#define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
#define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16
#include <tremor/ivorbisfile.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenAL Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef IOS_APPLICATION
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#else
    #include <AL/al.h>
    #include <AL/alc.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Freetype Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ft2build.h>
#include FT_FREETYPE_H

////////////////////////////////////////////////////////////////////////////////////////////////////
// cURL Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <curl/curl.h>

#ifndef CURL_STATICLIB
    #define CURL_STATICLIB
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Support
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
// Common Includes
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Structs.h"


//////////////////////////////////////////////////////////////////////////////////
// UTF8 Support for MinGW Compiler
//////////////////////////////////////////////////////////////////////////////////

#include "UTF8/UTF8.hpp"

//////////////////////////////////////////////////////////////////////////////////
// MD5 Support
//////////////////////////////////////////////////////////////////////////////////

#include "MD5/MD5.h"

// ==================================================================================================================================
//	    ___
//	   /   |  ______________ ___  __
//	  / /| | / ___/ ___/ __ `/ / / /
//	 / ___ |/ /  / /  / /_/ / /_/ /
//	/_/  |_/_/  /_/   \__,_/\__, /
//	                       /____/
// ==================================================================================================================================
template<class T>
class Array : public std::vector<T>
{
public:

	std::string __className;

	bool owner;

	//////////////////////////////////////////////////////////////////////////////////
	template<typename U = T, typename std::enable_if<std::is_pointer<U>::value, int>::type = 0>
	void __destroy__()
	{
        typename std::vector<T>::iterator it = this->begin();
    	for(; it != this->end();)
		{
            delete *it;
            it = this->erase(it);
		}
        this->clear();
	}

	//////////////////////////////////////////////////////////////////////////////////
	template<typename U = T, typename std::enable_if<!std::is_pointer<U>::value, int>::type = 0>
	void __destroy__()
	{
        typename std::vector<T>::iterator it = this->begin();
    	for(; it != this->end();)
		{
	    	it = this->erase(it);
		}
        this->clear();
	}

	//////////////////////////////////////////////////////////////////////////////////
	virtual ~Array()
	{
        if(owner)
            __destroy__();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<T>()
	{
		__className = "Array";
		owner = false;
	}

    //////////////////////////////////////////////////////////////////////////////////
	Array(const size_t size, ...) : std::vector<T>(size)
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
    const int32_t size() const
	{
		return (const int32_t) std::vector<T>::size();
	}

	//////////////////////////////////////////////////////////////////////////////////
	T pop()
	{
		T ret = std::vector<T>::back();
		std::vector<T>::pop_back();
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* push(const T& v)
	{
		std::vector<T>::push_back(v);
		return this;
	};

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* slice(const int32_t first)
	{
		return new Array<T>(std::vector<T>(std::vector<T>::begin() + first, std::vector<T>::end()));
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* slice(const size_t first, const size_t last) const
	{
		return new Array<T>(std::vector<T>(std::vector<T>::begin() + first, (last > 0 ? std::vector<T>::begin() : std::vector<T>::end()) + last));
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<T>* concat(const Array<T>* arr) const
	{
		Array<T>* n = new Array<T>(std::vector<T>(std::vector<T>::begin(), std::vector<T>::end()));
		n->insert(n->end(), arr->begin(), arr->end());
		return n;
	}

	//////////////////////////////////////////////////////////////////////////////////
	std::string join(const std::string& str) const
	{
		std::stringstream ss;
        for(size_t i = 0, L = (size_t) size(); i<L; i++)
		{
			ss << this->at(i);
            if(i + 1 != L)
				ss << str;
		}
		return ss.str();
	}

	//////////////////////////////////////////////////////////////////////////////////
	void splice(const int32_t index, const int32_t count)
	{
        auto from = std::vector<T>::begin() + index;
        auto to = std::vector<T>::begin() + index + count;
		std::vector<T>::erase(from, to);
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

    //////////////////////////////////////////////////////////////////////////////////
    T& operator [](int32_t index)
    {
        assert(index>=0 && index<size());
        return this->at( (size_t) index);
    }

	//////////////////////////////////////////////////////////////////////////////////
	const int32_t indexOf(T& v) const
	{
        for(size_t i = 0, L = (size_t) size(); i<L; i++)
			if(this->at(i)==v)
				return (int32_t) i;

        return -1;
	}
};

// ==================================================================================================================================
//	   _____ __       _                ________
//	  / ___// /______(_)___  ____ _   / ____/ /___ ___________
//	  \__ \/ __/ ___/ / __ \/ __ `/  / /   / / __ `/ ___/ ___/
//	 ___/ / /_/ /  / / / / / /_/ /  / /___/ / /_/ (__  |__  )
//	/____/\__/_/  /_/_/ /_/\__, /   \____/_/\__,_/____/____/
//	                      /____/
// ==================================================================================================================================

#define STD_STRING std::string

////////////////////////////////////////////////////////////////////
class String : public STD_STRING
{

private:

    //////////////////////////////////////////////////////////////////////////////////
    inline bool __naive_char(const char *a, const char *b)
    {
        while (*a || *b)
        {
            if (*a != *b)
            {
                return false;
            }
            ++a;
            ++b;
        }
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////
    inline bool __naive_string(const STD_STRING& a, const STD_STRING& b)
    {
        if (a.length() == b.length())
        {
            return __naive_char(a.c_str(), b.c_str());
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////
    STD_STRING	__ucase(STD_STRING& s)
    {
        if (s.size() == 0) return "";
        for (unsigned int i = 0, L = (unsigned int) s.length(); i < L; i++)
        {
            s[i] = (char) toupper(s[i]);
        }
        return s;
    }

    ////////////////////////////////////////////////////////////////////
    STD_STRING __lcase(STD_STRING& s)
    {
        if (s.size() == 0) return "";
        for (unsigned int i = 0, L = (unsigned int) s.length(); i < L; i++)
        {
            s[i] = (char) tolower(s[i]);
        }
        return s;
    }

    /////////////////////////////////////////////////////////////////////////////
    STD_STRING __replace(STD_STRING& s, const STD_STRING& from, const STD_STRING& to)
    {
        if (s.size() == 0) return "";
        size_t start_pos = 0;
        while ((start_pos = s.find(from, start_pos)) != STD_STRING::npos)
        {
            s.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return s;
    }

public:

    //////////////////////////////////////////////////////////////////////////////////
    String() = default;

    //////////////////////////////////////////////////////////////////////////////////
    String(const char* str) : STD_STRING(str)
    {
    }

    //////////////////////////////////////////////////////////////////////////////////
	String(const std::wstring& w)
	{
		std::string utf8 = wstring_to_utf8(w);
		*this = STD_STRING(utf8);
	}

    //////////////////////////////////////////////////////////////////////////////////
	String(const wchar_t* wb)
	{
		std::wstring w(wb);
		std::string utf8 = wstring_to_utf8(w);
		*this = STD_STRING(utf8);
	}

    //////////////////////////////////////////////////////////////////////////////////
    String(const char* str, const std::initializer_list<String> list) : STD_STRING(str)
    {
        for (uint32_t i = 0, L = (uint32_t) list.size(); i < L; i+=2)
        {
            __replace(*this, *(list.begin() + i), *(list.begin() + i + 1));
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const STD_STRING & str) : STD_STRING(str)
    {
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const String::const_iterator begin, const String::const_iterator end)
    {
        *this = STD_STRING(begin, end);
    }

    //////////////////////////////////////////////////////////////////////////////////
    #ifdef V8_ENABLED
    String(const v8::Local<v8::Value>& arg)
    {
        if (arg->IsString())
        {
            /*
             v8::Local<v8::String> string = arg->ToString();
             const int length = string->Utf8Length() + 1;
             uint8_t* buffer = (uint8_t*) malloc(length*sizeof(uint8_t));
             string->WriteOneByte(buffer, 0, length);
             *this = STD_STRING((const char*)buffer, length);
             free(buffer);
             */
            *this = STD_STRING(*(v8::String::Utf8Value(arg->ToString())));
        }
        else if (arg->IsArrayBufferView())
        {
            v8::Local<v8::ArrayBufferView> ab = v8::Local<v8::ArrayBufferView>::Cast(arg);
            uint32_t length = ab->ByteLength();
            void* buffer = malloc(length*sizeof(char));
            ab->CopyContents(buffer, length);
            *this = STD_STRING((const char*)buffer, length);
            free(buffer);
        }
        else
        {
            *this = STD_STRING(*(v8::String::Utf8Value(arg->ToString())));
        }
    }
    #endif

    //////////////////////////////////////////////////////////////////////////////////
    String(const int32_t arg)
    {
        char buff[100];
        sprintf(buff, "%d", arg);
        *this = String(buff);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const uint32_t arg)
    {
        char buff[100];
        sprintf(buff, "%d", arg);
        *this = String(buff);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const float arg)
    {
        char buff[100];
        sprintf(buff, "%g", arg);
        *this = String(buff);
    }

    //////////////////////////////////////////////////////////////////////////////////
    const int32_t size() const
    {
        return (int32_t) STD_STRING::size();
    }

    //////////////////////////////////////////////////////////////////////////////////
    String slice(const int32_t start, int32_t end = -1)
    {
        if (end == -1)
            end = this->size();

        assert(end - start < 0);

        int32_t length = end - start;

        return String(substr(start, length));
    }

    //////////////////////////////////////////////////////////////////////////////////
    String substr(const int32_t start, const int32_t length = -1) const
    {
        STD_STRING ss(STD_STRING::substr( (size_t) start, length==-1 ? std::string::npos : (size_t) length));
        return String(ss);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String substring(const int32_t start, int32_t end = -1) const
    {
        if (end == -1) end = size();
        return String(substr(start, end - start));
    }

    //////////////////////////////////////////////////////////////////////////////////
    const int32_t indexOf(const String& str, const size_t pos = 0) const
    {
        std::size_t found = find(str, pos);
        return found==std::string::npos ? -1 : (int32_t) found;
    }

    //////////////////////////////////////////////////////////////////////////////////
    const uint16_t charCodeAt(const int32_t index) const
    {
    	uint16_t c = 0;
		#ifdef ENABLE_BOOST
		#else
			std::string s = *this;
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			std::wstring w = converter.from_bytes(s);
			c = w.at(index);
		#endif
		return c;
    }

    //////////////////////////////////////////////////////////////////////////////////
    static String fromCharCode(const int32_t c)
    {
        if (c < (uint16_t) 128)
            return String(STD_STRING(1, (char) c));

        // Depending on the compiler and C runtime, wcstombs() might fail.

        const wchar_t wstr = (wchar_t)c;
        char mbstr[3] = { 0, 0, 0 };

        #ifdef __UTF8_HPP__
            int ret = (int) UTF8::wcstombs(mbstr, &wstr, 2);
        #else
            std::setlocale(LC_ALL, "en_US.utf-8");
            int ret = std::wcstombs(mbstr, &wstr, 2);
        #endif

        if (ret == -1) return String(STD_STRING(1, '?'));
        return String(mbstr);
    }

    //////////////////////////////////////////////////////////////////////////////////
    Array<String>* split(const String& separator, int32_t max = -1)
    {
        Array<String>* ret = new Array<String>();
        int32_t pos = 0, end, sz = separator.size();
        size_t next = 0;
        while((max==-1 || (max > 0 && ret->size() < max)) && next != STD_STRING::npos)
        {
            next = find(separator, (size_t) pos);
            end = next==STD_STRING::npos ? -1 : (int32_t) next;
            ret->push(substring(pos, end));
            pos = (int32_t) next + sz;
        }
        return ret;
    }

    //////////////////////////////////////////////////////////////////////////////////
    String charAt(const int32_t index) const
    {
        return (*this).substr(index, 1);
    }

    //////////////////////////////////////////////////////////////////////////////////
    void trimLeft()
    {
    	#ifdef ENABLE_BOOST
        	*this = boost::regex_replace(*this, boost::regex("^\\s+"), STD_STRING(""));
        #else
        	*this = std::regex_replace(*this, std::regex("^\\s+"), STD_STRING(""));
        #endif
    }

    //////////////////////////////////////////////////////////////////////////////////
    void trimRight()
    {
        int32_t i = size() - 1;
        for(; i>=0; i--)
        {
            switch (charCodeAt(i))
            {
                case 10:
                case 13:
                case 32:
                case 9:
                    break;

                default:
                    i++;
                    goto exit_for;
            }
        }
    exit_for:

        if (i >= 0)
            *this = substr(0, i);
    }

    //////////////////////////////////////////////////////////////////////////////////
    void trim()
    {
        trimLeft();
        trimRight();
    }

    //////////////////////////////////////////////////////////////////////////////////
    void makeLower()
    {
        *this = __lcase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    void makeUpper()
    {
        *this = __ucase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String toLowerCase()
    {
        return __lcase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String toLocaleLowerCase()
    {
        return __lcase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String toUpperCase()
    {
        return __ucase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String toLocaleUpperCase()
    {
        return __ucase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    String replace(const String& find, const String& replace)
    {
        *this = __replace(*this, find, replace);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////////////
    bool contains(const String& substr) const
    {
        return (this->find(substr)) != String::npos;
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Comparison Operators
    bool operator==(const String & rhs)
    {
        return __naive_string(*this, rhs);
    }

    bool operator==(const STD_STRING & rhs)
    {
        return __naive_string(*this, rhs);
    }

    bool operator==(const char* rhs)
    {
        return __naive_char(this->c_str(), rhs);
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Type Cast Operators

    operator bool() const
    {
        return !empty();
    }

    operator int32_t() const
    {
        return (int32_t) atoi(this->c_str());
    }

    operator uint32_t() const
    {
        return (uint32_t)atoi(this->c_str());
    }

    operator float() const
    {
        return (float)atof(this->c_str());
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Array Index operator

    String operator [](int32_t index)
    {
        return charAt(index);
    }

    //////////////////////////////////////////////////////////////////////////////////
    // Assignment Operators

    String& operator =(const char* c_str)
    {
        STD_STRING::operator=(c_str);
        return *this;
    }

    String& operator =(const String str)
    {
        STD_STRING::operator=(str);
        return *this;
    }

    String& operator =(const STD_STRING str)
    {
        STD_STRING::operator=(str);
        return *this;
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
    int32_t byteLength;


    //////////////////////////////////////////////////////////////////////////////////
    ArrayBuffer(const int32_t length)
	{
        byteLength = length;
        data = malloc( (size_t) byteLength );

        if(byteLength)
            memset(data, 0, (size_t) byteLength);
	}

	//////////////////////////////////////////////////////////////////////////////////
	~ArrayBuffer()
	{
        if(data)
        {
            free(data);
            data = nullptr;
        }
	}

	//////////////////////////////////////////////////////////////////////////////////
	void* operator[](const int32_t i) const
	{
		if(i>=byteLength)
        {
            std::cout << "array index out of bounds\n";
            return nullptr;
        }

		return reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(data) + i);
	}

    //////////////////////////////////////////////////////////////////////////////////
    String encodeAsBase64();
    ArrayBuffer* encodeAsPNG(const int32_t width, const int32_t height);

    //////////////////////////////////////////////////////////////////////////////////
    static ArrayBuffer* NewFromImage(const String str, int32_t& width, int32_t& height);
	static ArrayBuffer* NewFromImage_PNG(CocoAssetFile* file, int32_t& width, int32_t& height);
	static ArrayBuffer* NewFromImage_JPG(CocoAssetFile* file, int32_t& width, int32_t& height);
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
	int32_t byteOffset;
	int32_t byteLength;

	//////////////////////////////////////////////////////////////////////////////////
	void clear()
	{
        if(byteLength)
            memset((*buffer)[byteOffset], 0, (size_t) byteLength);
	}

	//////////////////////////////////////////////////////////////////////////////////
	void* get()
	{
		return reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(buffer->data) + byteOffset);
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
template<typename T>
class TypedArray : public ArrayBufferView
{
public:
	int32_t BYTES_PER_ELEMENT;
	int32_t length;
	bool owner;

    TypedArray(const int32_t size)
	{
		owner = true;

        BYTES_PER_ELEMENT = sizeof(T);
        length = size;
        byteOffset = 0;
        byteLength = length * BYTES_PER_ELEMENT;

		buffer = new ArrayBuffer(byteLength);
        assert(byteLength==buffer->byteLength);
	}

	//////////////////////////////////////////////////////////////////////////////////
	TypedArray(ArrayBuffer* i_buffer, const int32_t i_byteOffset = 0, const int32_t i_elements = -1)
	{
        assert(i_buffer!=nullptr);

        owner = false;
		buffer = i_buffer;

        BYTES_PER_ELEMENT = sizeof(T);

        int32_t _length = (i_buffer->byteLength - i_byteOffset) / BYTES_PER_ELEMENT;
        length = i_elements != -1 ? i_elements : _length;
        assert(length!=-1);

        byteOffset = i_byteOffset;
        byteLength = length * BYTES_PER_ELEMENT;
	}

	//////////////////////////////////////////////////////////////////////////////////
	TypedArray(Array<T>* v, bool preserve = false)
	{
		assert(v!=nullptr);

        owner = true;

        BYTES_PER_ELEMENT = sizeof(T);
		length = v->size();
        byteOffset = 0;
        byteLength = length * BYTES_PER_ELEMENT;

		buffer = new ArrayBuffer(byteLength);
        assert(byteLength==buffer->byteLength);

        void* vector_data = v->data();
		memcpy(buffer->data, vector_data, (size_t) byteLength);
		if(!preserve) delete v;
	}

    //////////////////////////////////////////////////////////////////////////////////
    virtual ~TypedArray()
    {
        if(owner)
            delete buffer;
    }

	//////////////////////////////////////////////////////////////////////////////////
	void set(TypedArray<T>* v, const int32_t offset = 0)
	{
		if(v->length + offset >= this->length)
        {
            std::cout << "array index out of bounds\n";
            return;
        }

        int32_t addr = (this->byteOffset + offset) * BYTES_PER_ELEMENT;
        void* dst = (*this->buffer)[addr];

        const void* src = (*v->buffer)[v->byteOffset];
        int32_t cbSize = v->length * BYTES_PER_ELEMENT;

        memcpy(dst, src, (size_t)cbSize);
	}

	//////////////////////////////////////////////////////////////////////////////////
	T* get()
    {
        return reinterpret_cast<T*>(ArrayBufferView::get());
    }

	//////////////////////////////////////////////////////////////////////////////////
    T& operator [](const int32_t index)
    {
        assert(index>=0 && index<(int32_t)length);
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

typedef TypedArray<uint8_t> Uint8Array;
typedef TypedArray<uint16_t> Uint16Array;
typedef TypedArray<uint32_t> Uint32Array;
typedef TypedArray<uint64_t> Uint64Array;

typedef TypedArray<int8_t> Int8Array;
typedef TypedArray<int16_t> Int16Array;
typedef TypedArray<int32_t> Int32Array;
typedef TypedArray<int64_t> Int64Array;

typedef TypedArray<float> Float32Array;
typedef TypedArray<double> Float64Array;

typedef TypedArray<uint8_t> Uint8ClampedArray;

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

	//////////////////////////////////////////////////////////////////////////////////
	DataView(ArrayBuffer* i_buffer, int32_t i_byteOffset = 0, int32_t i_byteLength = -1)
	{
		buffer = i_buffer;
		byteOffset = i_byteOffset;
        byteLength = i_byteLength!=-1 ? i_byteLength : buffer->byteLength;
        assert(byteLength!=-1);
	}

	//////////////////////////////////////////////////////////////////////////////////
	template<class T>
    T* get(int32_t offset)
    {
        return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(ArrayBufferView::get()) + offset);
    }

	//////////////////////////////////////////////////////////////////////////////////
	template<class T>
    T flip(T val, bool littleEndian)
	{
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            if(littleEndian) return val;
        #elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			if(!littleEndian) return val;
		#else
			#error "Platform not supported!"
		#endif

        size_t sz = sizeof(T);
        size_t sz_over_2 = sz / 2;
		uint8_t t;
		uint8_t* v = reinterpret_cast<uint8_t*>(&val);
		for(size_t i = 0; i < sz_over_2; i++)
		{
			t = *(v + i);
			*(v + i) = *(v + sz - 1 - i);
			*(v + sz - 1 - i) = t;
		}
		return val;
	}

	//////////////////////////////////////////////////////////////////////////////////

	int32_t 	getUint8(int32_t offset) 								{ return (int32_t) *get<uint8_t>(offset); }
	int32_t 	getUint16(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<uint16_t>(offset), littleEndian); }
	int32_t     getUint32(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<uint32_t>(offset), littleEndian); }

	int32_t 	getInt8(int32_t offset) 									{ return (int32_t) *get<int8_t>(offset); }
	int32_t 	getInt16(int32_t offset, bool littleEndian = false) 		{ return (int32_t) flip(*get<int16_t>(offset), littleEndian); }
	int32_t 	getInt32(int32_t offset, bool littleEndian = false) 		{ return (int32_t) flip(*get<int32_t>(offset), littleEndian); }

	float 		getFloat32(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<float>(offset), littleEndian); }
	float		getFloat64(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<double>(offset), littleEndian); }

	//////////////////////////////////////////////////////////////////////////////////

	void setUint8	(int32_t offset, int32_t val) 								{ *get<uint8_t>(offset) = (uint8_t)val; }
	void setUint16	(int32_t offset, int32_t val, bool littleEndian = false) 	{ *get<uint16_t>(offset) = flip((uint16_t)val, littleEndian); }
	void setUint32	(int32_t offset, int32_t val, bool littleEndian = false) 	{ *get<uint32_t>(offset) = flip((uint32_t)val, littleEndian); }

	void setInt8	(int32_t offset, int32_t val) 								{ *get<int8_t>(offset) = (int8_t)val; }
	void setInt16	(int32_t offset, int32_t val, bool littleEndian = false)		{ *get<int16_t>(offset) = flip((int16_t)val, littleEndian); }
	void setInt32	(int32_t offset, int32_t val, bool littleEndian = false) 	{ *get<int32_t>(offset) = flip((int32_t)val, littleEndian); }

	void setFloat32	(int32_t offset, float val, bool littleEndian = false) 		{ *get<float>(offset) = flip(val, littleEndian); }
	void setFloat64	(int32_t offset, float val, bool littleEndian = false) 		{ *get<double>(offset) = flip((double)val, littleEndian); }

};

// ==================================================================================================================================
//	    ____             ______
//	   / __ \___  ____ _/ ____/  ______
//	  / /_/ / _ \/ __ `/ __/ | |/_/ __ \
//	 / _, _/  __/ /_/ / /____>  </ /_/ /
//	/_/ |_|\___/\__, /_____/_/|_/ .___/
//	           /____/          /_/
// ==================================================================================================================================

#ifdef ENABLE_BOOST

class RegExp
{
public:
    bool global;
	bool ignoreCase;
	bool multiline;
	int lastIndex;
	String source;
    String pattern;
	boost::regex rx;

	//////////////////////////////////////////////////////////////////////////////////
	RegExp(String pattern, String flags="")
	{
		compile(pattern, flags);
	}

	//////////////////////////////////////////////////////////////////////////////////
	virtual ~RegExp()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	void compile(String pattern, String flags="")
	{
        if(flags.find("i")!=std::string::npos) ignoreCase = true;
        if(flags.find("m")!=std::string::npos) multiline = true;
        if(flags.find("g")!=std::string::npos) global = true;

        this->pattern = pattern;

        uint32_t iflags = boost::regex_constants::ECMAScript;
        if(ignoreCase) iflags |= boost::regex_constants::icase;

        rx.assign(pattern, iflags);
	}

	//////////////////////////////////////////////////////////////////////////////////
 	Array<String>* exec(String& buff)
 	{
        Array<String> *out = new Array<String>;

        auto flags = boost::regex_constants::match_not_null;

        if(!multiline)  flags |= boost::regex_constants::match_single_line; /* treat text as single line and ignor any \n's when matching ^ and $. */
        if(!global)     flags |= boost::regex_constants::match_continuous;

        boost::sregex_iterator it_end;
        boost::sregex_iterator it(buff.begin(), buff.end(), rx, flags);

        while(it != it_end)
        {
            boost::smatch match = *it;
            std::string match_str = match.str();
            out->push_back(match_str);
            ++it;
            if(!global) break;
        }
        if(out->size()==0)
        {
        	delete out;
        	out = nullptr;
        }
 		return out;
 	}

	//////////////////////////////////////////////////////////////////////////////////
	bool test(String& buff)
	{
        boost::smatch match;
        boost::regex_search(buff, match, rx);
		return match.size()>0 ? true : false;
	}
};

#else

class RegExp
{
public:
    bool global;
	bool ignoreCase;
	bool multiline;
	int lastIndex;
	String source;
	std::regex rx;

	//////////////////////////////////////////////////////////////////////////////////
	RegExp(String pattern, String flags="")
	{
		compile(pattern, flags);
	}

	//////////////////////////////////////////////////////////////////////////////////
	virtual ~RegExp()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	void compile(String pattern, String flags="")
	{
        if(flags.find("i")!=std::string::npos) ignoreCase = true;
        if(flags.find("m")!=std::string::npos) multiline = true;
        if(flags.find("g")!=std::string::npos) global = true;

        if(ignoreCase)
	        rx.assign(pattern, std::regex_constants::ECMAScript|std::regex_constants::icase);
        else
            rx.assign(pattern, std::regex_constants::ECMAScript);
	}

	//////////////////////////////////////////////////////////////////////////////////
 	Array<String>* exec(String buff)
 	{
        Array<String> *out = new Array<String>;
        std::sregex_iterator it(buff.begin(), buff.end(), rx);
        std::sregex_iterator it_end;
        while(it != it_end)
        {
            std::smatch match = *it;
            std::string match_str = match.str();
            out->push_back(match_str);
            ++it;
            if(!global) break;
        }
        if(out->size()==0)
        {
        	delete out;
        	out = nullptr;
        }
 		return out;
 	}

	//////////////////////////////////////////////////////////////////////////////////
	bool test(String buff)
	{
        std::smatch match;
        std::regex_search(buff, match, rx);
		return match.size()>0 ? true : false;
	}
};

#endif

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
class HTMLVideoElement;
class HTMLWindow;
class IEventListener;
class ImageData;
class MD5;
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
class CocoDOMDocument;
class CocoDOMNode;
class CocoDataField;
class CocoDataRow;
class CocoDataSource;
class CocoDataStream;
class CocoDataset;
class CocoDevice;
class CocoEncode;
class CocoEngine;
class CocoEvent;
class CocoGraphics;
class CocoHttpRequest;
class CocoImage;
class CocoImageRenderData2D;
class CocoImageRenderDataGL;
class CocoImageResolution;
class CocoJSONParser;
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
class CocoTimer;
class CocoTokenizer;
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
class CocoXMLParser;
class CocoXPathParser;
class DefaultForm;
class FormViewer;
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
class LoginForm;
class OnClickHandler;
class PathLine;
class ReservationsForm;
class Touch;
class TouchList;
class UUID;
struct COCO_PARSER_STATE;
struct CocoDOMAttribute;
struct CocoHVAlign;
struct CocoKeyFrame;
struct CocoMatrixData;
struct CocoPoint;
struct CocoRect;
struct CocoRequestNameValuePair;
struct CocoSkinCacheItem;
struct CocoVariant;
struct ContextArguments;
struct DEVICE_MESSAGE;
struct TOKEN;
struct TOKEN_RULE;
//# Generated Classes End #//

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
#define fxObjectUID     uint32_t
#define parseFloat(S)   (float)(atof((S).c_str()))
#define parseInt(S)     (int32_t)(atoi((S).c_str()))

template<typename T>
struct TYPE_STRING
{
    static constexpr char const* c_str()
    {
        return "undefined";
    }
};

#define DEF_TYPE(T)                                 \
template<>                                          \
struct TYPE_STRING<T>                               \
{                                                   \
    static constexpr char const* c_str()            \
    {                                               \
        return #T;                                  \
    }                                               \
};                                                  \

DEF_TYPE(int8_t);
DEF_TYPE(uint8_t);
DEF_TYPE(int16_t);
DEF_TYPE(uint16_t);
DEF_TYPE(int32_t);
DEF_TYPE(uint32_t);
DEF_TYPE(float);
DEF_TYPE(double);

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
template<class T> using Index = std::map<uint32_t, T>;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
std::string toString(T v)
{
	std::stringstream ss;
	ss<<v;
	return ss.str();
}

typedef String Gradient;

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
	int32_t getTime() { return (int32_t) millis; }
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
extern String btoa(String binary);
extern bool isFinite(String value);
extern String encodeURIComponent(String uri);
extern void fixTouch(Touch* touch);

// ==================================================================================================================================
//	  _______
//	 /_  __(_)___ ___  ___  __________
//	  / / / / __ `__ \/ _ \/ ___/ ___/
//	 / / / / / / / / /  __/ /  (__  )
//	/_/ /_/_/ /_/ /_/\___/_/  /____/
//
// ==================================================================================================================================

//class TimerThreadInterruptException;
//class TimerThread;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interruptible Timer Thread
/*
class TimerThread
{
public:

	std::atomic<bool> _running;
	std::thread _thread;

	template <typename Function, typename... Args>
	TimerThread(Function&& fn, Args&&... args) :
		_thread([](std::atomic<bool>& f, Function&& fn, Args&&... args)
		{
			fn(std::forward<Args>(args)...);
		},
		std::forward<Function>(fn),
		std::forward<Args>(args)...)
	{
		_running.store(true);
	}

	bool running() const
	{
		return _running.load();
	}

	void stop()
	{
		_running.store(false);
	}
};
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
using setIntervalCallback = void(T::*)();

template<typename T>
int setInterval(T* _this, setIntervalCallback<T> fn, int interval)
{
	/*
	if (interval < 0) return 0;

	std::thread* t = new std::thread([&]()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		(_this->*fn)();
	});

	return (INT_PTR) t;
	*/

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void clearInterval(int handle);

#endif //__COCONUT2D_HPP__

