/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2016 www.mobilefx.com
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

#ifndef __COCONUT2D_HPP__
#define __COCONUT2D_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////
// STL Includes
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <stdarg.h>

#include <cassert>
#include <cfloat>
#include <chrono>
#include <clocale>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <math.h>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <iomanip>
#include <stdint.h>

#ifndef MSVC_COMPILER
	#include <tgmath.h>
	#include <unistd.h>
#endif

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

#ifndef NULL_DATA_VALUE
#define NULL_DATA_VALUE   "FF707534-E45E-4294-A242-E7B798BF96A7"
#endif

#ifndef LNULL_DATA_VALUE
#define LNULL_DATA_VALUE   L"FF707534-E45E-4294-A242-E7B798BF96A7"
#endif
#ifndef DATA_STREAM_B64
#define DATA_STREAM_B64 "data:dataset/octet-stream;base64,"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor Macros
////////////////////////////////////////////////////////////////////////////////////////////////////

#define COCO_DELETE_OBJECT(O) if(O){delete O; O=nullptr;}

#define COCO_DELETE_ARRAY(A) 													\
if(A)                                                                       	\
{                                                                           	\
	for(int32_t _index= A->size()-1; _index>=0; _index--)                   	\
	{                                                                       	\
		delete (*A)[_index];                                                	\
	};                                                                      	\
	A->clear();                                                             	\
	delete A;                                                               	\
	A=nullptr;                                                              	\
}																				\

////////////////////////////////////////////////////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef bool Boolean;
typedef int32_t Color;
typedef int32_t CartesianX;
typedef int32_t CartesianY;
typedef int32_t Integer;
typedef float Float;
typedef float Time;
typedef float Number;
typedef void Function;
typedef void Object;

#ifdef MSVC_COMPILER

	#define strdup _strdup
	#define constexpr const
	#define FALSE 0
	#define NOMINMAX

	#define isnan(x) _isnan(x)
	#define isinf(x) (!_finite(x))

	#define trace(v)															\
	{                                   										\
		std::stringstream ss;           										\
		ss << v << "\n";                										\
		std::cout << ss.str();          										\
		OutputDebugStringA(ss.str().c_str());									\
	}                                   										\

#else

	#ifndef isnan
		#define isnan(x) std::isnan(x)
		#define isinf(x) std::isinf(x)
	#endif

	#define trace(v)															\
	{                                   										\
		std::stringstream ss;           										\
		ss << v;                												\
		fprintf(stderr, "%s\n", ss.str().c_str());          					\
		fflush(stderr);                                     					\
	}                                   										\

#endif

#if defined(_MSC_VER) && _MSC_VER < 1900
	#define snprintf _snprintf
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Math
////////////////////////////////////////////////////////////////////////////////////////////////////

#if ANDROID_APPLICATION
	#ifndef UINT
		#define UINT uint32_t
	#endif
#endif

#include <utility>

#if ANDROID_APPLICATION
	namespace std
	{
		int32_t round(float n);
		int32_t round(int32_t n);
	}
#endif

#ifndef math_floor
#define math_floor(n)		(int32_t)std::floor(n)
#endif

#ifndef math_ceil
#define math_ceil(n)        (int32_t)std::ceil(n)
#endif

#ifndef math_log
#define math_log(n)         (float)std::log(n)
#endif

#ifndef math_abs
#define math_abs(n)         std::abs(n)
#endif

#ifndef math_sqrt
#define math_sqrt(n)        (float)std::sqrt(n)
#endif

#ifndef math_round
#define math_round(n)       (int32_t)std::round(n)
#endif

#ifndef math_asin
#define math_asin(n)        (float)std::asin(n)
#endif

#ifndef math_acos
#define math_acos(n)        (float)std::acos(n)
#endif

#ifndef math_sin
#define math_sin(n)         (float)std::sin(n)
#endif

#ifndef math_cos
#define math_cos(n)         (float)std::cos(n)
#endif

#ifndef math_min
#define math_min(A,B)     	((float)(A) < (float)(B) ? (A) : (B) )
#endif

#ifndef math_max
#define math_max(A,B)     	((float)(A) > (float)(B) ? (A) : (B) )
#endif

#ifndef math_pow
#define math_pow(B,E)    	(int32_t) std::pow( (float)B, (float)E )
#endif

#ifndef math_random
#define math_random() 		(float) ((float)rand()/(float)RAND_MAX)
#endif

#ifndef sqrtd
#define sqrtd(D)  (double)(sqrtf((float)(D)))
#endif

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

    //#include <chrono>
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
	#include <WinGdi.h>

	#ifdef _MSC_VER
		#pragma comment(lib, "Msimg32.lib")
		#pragma comment(lib, "comctl32.lib")
		#pragma comment(lib, "comdlg32.lib")
	#endif

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
// Regular Expressions Support
////////////////////////////////////////////////////////////////////////////////////////////////////

// Boost RegEx are much faster than STL
#ifdef ENABLE_BOOST
	#include <boost/regex.hpp>
#else
	#include <regex>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// PNG Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <png.h>

#ifdef _MSC_VER
	#pragma comment(lib, "libpng.lib")
	#pragma comment(lib, "zlib.lib")
#endif

struct read_closure_t
{
	unsigned len;
	const uint8_t* buf;
};

extern bool isPNG(uint8_t* data);
extern uint8_t* pixels_from_png(const uint8_t* inBytes, const size_t inBytesLen, size_t& outPixelsBytesLen, uint32_t& width, uint32_t& height, bool premultiply = true);
extern std::vector<uint8_t>* pixels_to_png(const uint8_t* pixels, size_t width, size_t height, bool unpremultiply = true);

////////////////////////////////////////////////////////////////////////////////////////////////////
// JPEG Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FALSE
#undef FALSE
#endif

#ifdef TRUE
#undef TRUE
#endif

#include <jpeglib.h>

#ifdef _MSC_VER
	#pragma comment(lib, "jpeg.lib")
#endif

extern bool isJPEG(uint8_t* data);
extern uint8_t* pixels_from_jpeg(const uint8_t* inBytes, const size_t inBytesLen, size_t& outPixelsBytesLen, uint32_t& width, uint32_t& height, bool premultiply = true);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Freetype Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef _MSC_VER
	#pragma comment(lib, "freetype.lib")
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// Cairo Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>

#ifdef _WINDOWS_
	#include <cairo/cairo-win32.h>
#endif

#ifdef _MSC_VER
	#pragma comment(lib, "cairo.lib")
	#pragma comment(lib, "libfontconfig.a")
	#pragma comment(lib, "libpixman-1.a")
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////
// OpenAL Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef IOS_APPLICATION
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#else
    #include <al/al.h>
    #include <al/alc.h>
#endif

#ifdef _MSC_VER
	#pragma comment(lib, "OpenAL32.lib")
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// OGG Vorbis Tremolo Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#define AUDIO_SAMPLE_SIZE 2
#define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
#define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16

#ifdef WIN32_APPLICATION
	#include <vorbis/vorbisfile.h>
#else
	#include <tremor/ivorbisfile.h>
//	#include <tremolo/ivorbisfile.h>
#endif

#ifdef _MSC_VER
	#pragma comment(lib, "libogg_static.lib")
	#pragma comment(lib, "libvorbis_static.lib")
	#pragma comment(lib, "libvorbisfile_static.lib")
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// cURL Support
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <curl/curl.h>

#ifndef CURL_STATICLIB
    #define CURL_STATICLIB
#endif

#ifdef _MSC_VER
	#pragma comment(lib, "libcurl.lib")
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

	#ifdef _MSC_VER
		#pragma comment(lib, "opengl32.lib")
		#pragma comment(lib, "libglew32.dll.a")
	#endif

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

// ==================================================================================================================================
//	   __________  ______________
//	  / ____/ __ \/ ____/__  /__ \
//	 / /   / /_/ / /     /_ <__/ /
//	/ /___/ _, _/ /___ ___/ / __/
//	\____/_/ |_|\____//____/____/
//
// ==================================================================================================================================

static uint32_t crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long GetCRC(long buf, long BufSize);
std::string crc32(void* buf, long BufSize);

// ==================================================================================================================================
//	    __  _______  ______
//	   /  |/  / __ \/ ____/
//	  / /|_/ / / / /___ \
//	 / /  / / /_/ /___/ /
//	/_/  /_/_____/_____/
//
// ==================================================================================================================================

class MD5
{
public:
	typedef unsigned int size_type; // must be 32bit

	MD5();
	MD5(const std::string& text);
	void update(const unsigned char *buf, size_type length);
	void update(const char *buf, size_type length);
	MD5& finalize();
	std::string hexdigest() const;
	friend std::ostream& operator<<(std::ostream&, MD5 md5);

private:
	void init();
	typedef unsigned char uint1; //  8bit
	typedef unsigned int uint4;  // 32bit
	enum {
		blocksize = 64
	}; // VC6 won't eat a const static int here

	void transform(const uint1 block[blocksize]);
	static void decode(uint4 output[], const uint1 input[], size_type len);
	static void encode(uint1 output[], const uint4 input[], size_type len);

	bool finalized;
	uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
	uint4 count[2];   // 64bit counter for number of bits (lo, hi)
	uint4 state[4];   // digest so far
	uint1 digest[16]; // the result

	// low level logic operations
	static inline uint4 F(uint4 x, uint4 y, uint4 z);
	static inline uint4 G(uint4 x, uint4 y, uint4 z);
	static inline uint4 H(uint4 x, uint4 y, uint4 z);
	static inline uint4 I(uint4 x, uint4 y, uint4 z);
	static inline uint4 rotate_left(uint4 x, int n);
	static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

// ==================================================================================================================================
//	    ___
//	   /   |  ______________ ___  __
//	  / /| | / ___/ ___/ __ `/ / / /
//	 / ___ |/ /  / /  / /_/ / /_/ /
//	/_/  |_/_/  /_/   \__,_/\__, /
//	                       /____/
// ==================================================================================================================================
template<typename T>
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
        //if(owner)
        //    __destroy__();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array() : std::vector<T>()
	{
		__className = "Array";
		owner = false;
	}

	//////////////////////////////////////////////////////////////////////////////////
    Array(std::initializer_list<T> list)
    {
        for(size_t i=0; i<list.size(); i++)
        {
            push(*(list.begin()+i));
        }
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

////////////////////////////////////////////////////////////////////
class String : public std::string
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
    inline bool __naive_string(const std::string& a, const std::string& b)
    {
        if (a.length() == b.length())
        {
            return __naive_char(a.c_str(), b.c_str());
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////
    std::string	__ucase(std::string& s)
    {
        if (s.size() == 0) return "";
        for (unsigned int i = 0, L = (unsigned int) s.length(); i < L; i++)
        {
            s[i] = (char) toupper(s[i]);
        }
        return s;
    }

    ////////////////////////////////////////////////////////////////////
    std::string __lcase(std::string& s)
    {
        if (s.size() == 0) return "";
        for (unsigned int i = 0, L = (unsigned int) s.length(); i < L; i++)
        {
            s[i] = (char) tolower(s[i]);
        }
        return s;
    }

    /////////////////////////////////////////////////////////////////////////////
    std::string __replace(std::string& s, const std::string& from, const std::string& to)
    {
        if (s.size() == 0) return "";
        size_t start_pos = 0;
        while ((start_pos = s.find(from, start_pos)) != std::string::npos)
        {
            s.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return s;
    }

	std::wstring wcache;

public:

    //////////////////////////////////////////////////////////////////////////////////
    String() = default;

    //////////////////////////////////////////////////////////////////////////////////
    String(const char* str) : std::string(str)
    {
    }

    //////////////////////////////////////////////////////////////////////////////////
	String(const std::wstring& w)
	{
    	wcache = std::wstring(w);
		UTF8::wstring_to_utf8(wcache, *this);
	}

    //////////////////////////////////////////////////////////////////////////////////
	String(const wchar_t* wb)
	{
		wcache = std::wstring(wb);
        UTF8::wstring_to_utf8( (std::wstring&) wcache, *this);
	}

    //////////////////////////////////////////////////////////////////////////////////
    String(const char* str, const std::initializer_list<String> list) : std::string(str)
    {
        for (uint32_t i = 0, L = (uint32_t) list.size(); i < L; i+=2)
        {
            __replace(*this, *(list.begin() + i), *(list.begin() + i + 1));
        }
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const std::string & str) : std::string(str)
    {
    }

    //////////////////////////////////////////////////////////////////////////////////
    String(const String::const_iterator begin, const String::const_iterator end)
    {
        *this = std::string(begin, end);
    }

	//////////////////////////////////////////////////////////////////////////////////
	String(const char* str, size_t start, size_t length) : std::string(str,start,length)
	{
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
             *this = std::string((const char*)buffer, length);
             free(buffer);
             */
            *this = std::string(*(v8::String::Utf8Value(arg->ToString())));
        }
        else if (arg->IsArrayBufferView())
        {
            v8::Local<v8::ArrayBufferView> ab = v8::Local<v8::ArrayBufferView>::Cast(arg);
            uint32_t length = ab->ByteLength();
            void* buffer = malloc(length*sizeof(char));
            ab->CopyContents(buffer, length);
            *this = std::string((const char*)buffer, length);
            free(buffer);
        }
        else
        {
            *this = std::string(*(v8::String::Utf8Value(arg->ToString())));
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
        return (int32_t) (wcache.length()>0 ? wcache.length() : std::string::size());
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
        std::string ss(std::string::substr( (size_t) start, length==-1 ? std::string::npos : (size_t) length));
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
	const int32_t lastIndexOf(const String& str, const size_t pos = 0) const
	{
		std::size_t found = find_last_of(str);
		return found == std::string::npos ? -1 : (int32_t) found;
	}

	//////////////////////////////////////////////////////////////////////////////////
    const uint16_t charCodeAt(const int32_t index) const
    {
    	if(index<0) return 0;
    	if(wcache.size()==0)
    	{
            std::string s = *this;
            UTF8::utf8_to_wstring(s, (std::wstring&) wcache);
    	}
		return (uint16_t) (index>=(int32_t)wcache.length() ? 0 : wcache.at((size_t)index));
    }

    //////////////////////////////////////////////////////////////////////////////////
    static String fromCharCode(const int32_t c)
    {
        if (c < (uint16_t) 128)
            return String(std::string(1, (char) c));

        // Depending on the compiler and C runtime, wcstombs() might fail.

        const wchar_t wstr = (wchar_t)c;
        char mbstr[3] = { 0, 0, 0 };

        #ifdef __UTF8_HPP__
            int ret = (int) UTF8::wcstombs(mbstr, &wstr, 2);
        #else
            std::setlocale(LC_ALL, "en_US.utf-8");
            int ret = std::wcstombs(mbstr, &wstr, 2);
        #endif

        if (ret == -1) return String(std::string(1, '?'));
        return String(mbstr);
    }

	//////////////////////////////////////////////////////////////////////////////////
	static String fromUTF8(const char* utf8)
	{
		return String(utf8);

		/*
		std::setlocale(LC_ALL, "en_US.utf8");
		const wchar_t* wstr = (const wchar_t*) utf8;
		size_t cb = UTF8::wcstombs(nullptr, wstr, 0);
		char* mbstr = new char[cb];
		cb = std::wcstombs(mbstr, wstr, cb);
		return String(mbstr);
		*/
	}

	const char* toUTF8() const
	{
		return c_str();
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<String>* split(const String& separator, int32_t max = -1) const
	{
		Array<String>* ret = new Array<String>();
		int32_t pos = 0, end, sz = separator.size();
		size_t next = 0;
		while ((max == -1 || (max > 0 && ret->size() < max)) && next != std::string::npos)
		{
			next = find(separator, (size_t) pos);
			end = next == std::string::npos ? -1 : (int32_t) next;
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
    	wcache.clear();

    	#ifdef ENABLE_BOOST
        	*this = boost::regex_replace(*this, boost::regex("^\\s+"), std::string(""));
        #else
        	*this = std::regex_replace(*this, std::regex("^\\s+"), std::string(""));
        #endif
    }

    //////////////////////////////////////////////////////////////////////////////////
    void trimRight()
    {
       	wcache.clear();

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
    String trim()
    {
        trimLeft();
        trimRight();
		return *this;
    }

    //////////////////////////////////////////////////////////////////////////////////
    void makeLower()
    {
        wcache.clear();
        *this = __lcase(*this);
    }

    //////////////////////////////////////////////////////////////////////////////////
    void makeUpper()
    {
        wcache.clear();
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
        wcache.clear();
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

    bool operator==(const std::string & rhs)
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
        wcache.clear();
        std::string::operator=(c_str);
        return *this;
    }

    String& operator =(const String str)
    {
        wcache.clear();
        std::string::operator=(str);
        return *this;
    }

    String& operator =(const std::string str)
    {
        wcache.clear();
        std::string::operator=(str);
        return *this;
    }
};

/////////////////////////////////////////////////////////////////////////////
template <typename T>
std::string join_vector(std::vector<T>& v, const T& delim)
{
	std::stringstream ss;
	for (typename std::vector<T>::iterator i = v.begin(), L = v.end(); i != L; i++)
	{
		if (*i != v[0])
		{
			ss << delim;
		}
		ss << *i;
	}
	std::string s = std::string("") + ss.str();
	return s;
}

/////////////////////////////////////////////////////////////////////////////
extern String LOCAL_EMPTY_STRING;

// ==================================================================================================================================
//	   ______                 ___                   __  _______ __
//	  / ____/___  _________  /   |  _____________  / /_/ ____(_) /__
//	 / /   / __ \/ ___/ __ \/ /| | / ___/ ___/ _ \/ __/ /_  / / / _ \
//	/ /___/ /_/ / /__/ /_/ / ___ |(__  |__  )  __/ /_/ __/ / / /  __/
//	\____/\____/\___/\____/_/  |_/____/____/\___/\__/_/   /_/_/\___/
//
// ==================================================================================================================================

class CocoAssetFile
{
public:

	// ==================================================================================================================================
	//	   _____ __        __  _
	//	  / ___// /_____ _/ /_(_)____
	//	  \__ \/ __/ __ `/ __/ / ___/
	//	 ___/ / /_/ /_/ / /_/ / /__
	//	/____/\__/\__,_/\__/_/\___/
	//
	// ==================================================================================================================================

	static String filesPath;
	static String assetPath;

	#if ANDROID_APPLICATION
		static AAssetManager* manager;
		static void init(AAssetManager* i_manager, String FilesPath);
	#endif

	static void init(String FilesPath, String AssetPath);
	static void quit();
	static CocoAssetFile* open(String src);

	// ==================================================================================================================================
	//	    ____           __
	//	   /  _/___  _____/ /_____ _____  ________
	//	   / // __ \/ ___/ __/ __ `/ __ \/ ___/ _ \
	//	 _/ // / / (__  ) /_/ /_/ / / / / /__/  __/
	//	/___/_/ /_/____/\__/\__,_/_/ /_/\___/\___/
	//
	// ==================================================================================================================================

private:

	FILE* hFile;
	size_t length;
	unsigned char* data;

	#ifdef ANDROID_APPLICATION
		AAsset* ad;
	#endif

	CocoAssetFile(String src);

public:

	String fileName;

	virtual ~CocoAssetFile();
	int seek(long int offset, int origin);
	long int tell();
	size_t read(void* dest, size_t size);
	uint8_t* getData();
	size_t bytesLength();
};

// ==================================================================================================================================
//	    ___                          ____        ________
//	   /   |  ______________ ___  __/ __ )__  __/ __/ __/__  _____
//	  / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/
//	 / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /
//	/_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/
//	                       /____/
// ==================================================================================================================================

class ArrayBuffer
{
public:

    void* data;
    int32_t byteLength;

	//////////////////////////////////////////////////////////////////////////////////
	ArrayBuffer(void* data, const int32_t length) : data(nullptr)
	{
		byteLength = length;
		this->data = malloc((size_t) byteLength);

		if (byteLength)
			memcpy(this->data, data, (size_t) byteLength);
	}

	//////////////////////////////////////////////////////////////////////////////////
	ArrayBuffer(const int32_t length) : data(nullptr)
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

		if(!preserve)
			delete v;
	}

    //////////////////////////////////////////////////////////////////////////////////
    TypedArray(std::initializer_list<T> list)
    {
        owner = true;

        BYTES_PER_ELEMENT = sizeof(T);
        length = (int32_t) list.size();
        byteOffset = 0;
        byteLength = length * BYTES_PER_ELEMENT;

        buffer = new ArrayBuffer(byteLength);
        assert(byteLength==buffer->byteLength);

        void* vector_data = (void*) &(*(list.begin()));
        memcpy(buffer->data, vector_data, (size_t) byteLength);
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

	int32_t 	getInt8(int32_t offset) 								{ return (int32_t) *get<int8_t>(offset); }
	int32_t 	getInt16(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<int16_t>(offset), littleEndian); }
	int32_t 	getInt32(int32_t offset, bool littleEndian = false) 	{ return (int32_t) flip(*get<int32_t>(offset), littleEndian); }

	float 		getFloat32(int32_t offset, bool littleEndian = false) 	{ return (float) flip(*get<float>(offset), littleEndian); }
	float		getFloat64(int32_t offset, bool littleEndian = false) 	{ return (float) flip(*get<double>(offset), littleEndian); }

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
		global = false;
		multiline = false;
		ignoreCase = false;

		// The i flag is used to specify that pattern is non case sensitive (ignore case)
		if(flags.find("i")!=std::string::npos) ignoreCase = true;

		// The m flag is used to specify that a multiline input string should be treated as multiple lines.
		// If the m flag is used, ^ and $ match at the start or end of any line within the input string
		// instead of the start or end of the entire string.
		if (flags.find("m") != std::string::npos) multiline = true;

		// The g flag is used to specify that pattern must be matched anywhere throughout the string.
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
		flags |= global ? boost::regex_constants::match_any : boost::regex_constants::match_continuous;
        if(!multiline)  flags |= boost::regex_constants::match_single_line; /* treat text as single line and ignore any \n's when matching ^ and $. */

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
	String pattern;
	std::regex rx;
	Array<String>* matches;

	//////////////////////////////////////////////////////////////////////////////////
	RegExp() : matches(nullptr)
	{
	}

	//////////////////////////////////////////////////////////////////////////////////
	RegExp(String pattern, String flags = "") : matches(nullptr)
	{
		compile(pattern, flags);
	}

	//////////////////////////////////////////////////////////////////////////////////
	virtual ~RegExp()
	{
		if (matches)
		{
			delete matches;
			matches = nullptr;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////
	long Parse(String& sBuffer, String& sPattern)
	{
		if (matches)
		{
			delete matches;
			matches = nullptr;
		}
		compile(sPattern, "g");
		matches = exec(sBuffer);
		return matches ? matches->size() : 0;
	}

	//////////////////////////////////////////////////////////////////////////////////
	String SubMatch(long MatchIndex, long SubMatchIndex)
	{
		return "";
	}

	//////////////////////////////////////////////////////////////////////////////////
	void compile(const String& pattern, const String& flags = "")
	{
		global = false;
		multiline = false;
		ignoreCase = false;

		// The i flag is used to specify that pattern is non case sensitive (ignore case)
		if (flags.find("i") != std::string::npos) ignoreCase = true;

		// The m flag is used to specify that a multiline input string should be treated as multiple lines.
		// If the m flag is used, ^ and $ match at the start or end of any line within the input string
		// instead of the start or end of the entire string.
		if (flags.find("m") != std::string::npos) multiline = true;

		// The g flag is used to specify that pattern must be matched anywhere throughout the string.
		if (flags.find("g") != std::string::npos) global = true;

		this->pattern = pattern;

		auto iflags = std::regex_constants::ECMAScript | std::regex_constants::optimize;
		if (ignoreCase) iflags |= std::regex_constants::icase;

		rx.assign(pattern, iflags);
	}

	//////////////////////////////////////////////////////////////////////////////////
	Array<String>* exec(const String& buff)
	{
		Array<String> *out = new Array<String>;

		auto flags = std::regex_constants::match_not_null;
		flags |= global ? std::regex_constants::match_any : std::regex_constants::match_continuous;
		//if (!multiline)  flags |= std::regex_constants::match_single_line; /* treat text as single line and ignore any \n's when matching ^ and $. */

		std::sregex_iterator it_end;
		std::sregex_iterator it(buff.begin(), buff.end(), rx, flags);
		while (it != it_end)
		{
			std::smatch match = *it;
			std::string match_str = match.str();
			for (size_t i = 0, L = match.size(); i < L; i++)
			{
				std::ssub_match sub_match = match[i];
				out->push_back(sub_match.str());
			}
			++it;
			if (!global) break;
		}

		if (out->size() == 0)
		{
			delete out;
			out = nullptr;
		}

		return out;
	}

	//////////////////////////////////////////////////////////////////////////////////
	bool test(const String& buff)
	{
		std::smatch match;
		std::regex_search(buff, match, rx);
		return match.size() > 0 ? true : false;
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
class CanvasGradient;
class CanvasRenderingContext2D;
class CocoAudioSource;
class CocoAudioSystem;
class CocoDataStream;
class CocoDataset;
class CocoDatasetField;
class CocoDatasetIndex;
class CocoDatasetIndexTable;
class CocoDatasetRow;
class CocoEventConnectionPoint;
class CocoEventSource;
class CocoJSON;
class HTMLCanvasElement;
class HTMLFontFace;
class HTMLTextMetrics;
class HTMLVideoElement;
class HTMLWindow;
class IEventListener;
class Image;
class ImageData;
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
struct ContextArguments;
struct Fts5Context;
struct Fts5ExtensionApi;
struct Fts5PhraseIter;
struct Fts5Tokenizer;
struct GLany;
struct Mem;
struct _SYSTEMTIME;
struct fts5_api;
struct fts5_tokenizer;
struct fxScreen;
struct native_context_state_t;
struct sqlite3;
struct sqlite3_api_routines;
struct sqlite3_backup;
struct sqlite3_blob;
struct sqlite3_changegroup;
struct sqlite3_changeset_iter;
struct sqlite3_context;
struct sqlite3_file;
struct sqlite3_index_constraint;
struct sqlite3_index_constraint_usage;
struct sqlite3_index_info;
struct sqlite3_index_orderby;
struct sqlite3_io_methods;
struct sqlite3_mem_methods;
struct sqlite3_module;
struct sqlite3_mutex;
struct sqlite3_mutex_methods;
struct sqlite3_pcache;
struct sqlite3_pcache_methods2;
struct sqlite3_pcache_methods;
struct sqlite3_pcache_page;
struct sqlite3_rtree_geometry;
struct sqlite3_rtree_query_info;
struct sqlite3_session;
struct sqlite3_snapshot;
struct sqlite3_stmt;
struct sqlite3_vfs;
struct sqlite3_vtab;
struct sqlite3_vtab_cursor;
struct tagDBDATE;
struct tagDBTIME;
struct tagDBTIMESTAMP;
struct tagDB_NUMERIC;
struct tagDEC;
//# Native Classes End #//

//# Generated Classes Begin #//
class CocoAudio;
class CocoBezier;
class CocoClip;
class CocoDOMDocument;
class CocoDOMNode;
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
class CocoTextClip;
class CocoTextStyle;
class CocoTimeLabel;
class CocoTimeline;
class CocoTimer;
class CocoTokenizer;
class CocoUUID;
class CocoVector;
class CocoVideo;
class CocoXMLParser;
class CocoXPathParser;
class GameEngine;
class GridSymbol;
class HTMLAnchorElement;
class HTMLDivElement;
class HTMLDocument;
class HTMLElement;
class HTMLEvent;
class HTMLLocation;
class HTMLNavigator;
class HTMLScreen;
class HTMLStyleElement;
class ICocoImageRenderData;
class ICocoRenderContext;
class IEventTarget;
class ITickable;
class IWG_API_ACTION;
class IWG_API_CONFIGURATION;
class IWG_API_DEVICE;
class IWG_API_GAME;
class IWG_API_HEADER;
class IWG_API_PAYTABLE;
class IWG_API_PLAYER;
class IWG_API_PRIZE;
class IWG_API_PRIZELINE;
class IWG_API_SETTING;
class IWG_API_SYMBOL;
class IWG_API_SYMBOLDISTRIBUTION;
class IWG_API_TICKET;
class IWG_API_WAGER;
class SceneGameBoard;
class SceneTitle;
class Touch;
class TouchList;
class iRGS_REST_API_GAME_CONFIG;
class iRGS_REST_API_GAME_TICKET;
class iRGS_REST_API_GAME_TICKET_SAVE;
class iRGS_REST_API_LOBBY_GAMES_HISTORY;
class iRGS_REST_API_LOBBY_GAMES_LIST;
class iRGS_SYMBOL;
struct COCO_PARSER_STATE;
struct CocoDOMAttribute;
struct CocoHVAlign;
struct CocoImageCacheItem;
struct CocoKeyFrame;
struct CocoMatrixData;
struct CocoPoint;
struct CocoRect;
struct CocoVariant;
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
//#define parseTime(S)   (float)(atof((S).c_str()))

// ==================================================================================================================================
//	   ______      ______               __
//	  / ____/___ _/ / / /_  ____ ______/ /_______
//	 / /   / __ `/ / / __ \/ __ `/ ___/ //_/ ___/
//	/ /___/ /_/ / / / /_/ / /_/ / /__/ ,< (__  )
//	\____/\__,_/_/_/_.___/\__,_/\___/_/|_/____/
//
// ==================================================================================================================================

typedef std::function<void()> CocoAction;
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
extern CocoScene* ____debugger_current_scene;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Utils
extern String getexepath();
extern void fixTouch(Touch* touch);
extern void alert(String msg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Strings
extern String md5(const String& data);
extern String btoa(const String& binary);
extern String encodeURIComponent(const String& uri);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Numbers
extern bool isFinite(const String& value);
extern int32_t parseInt(const String& s);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Facebook SDK

extern void __Facebook_Initialize(String AppID, int ImageSize);
extern void __Facebook_Login(String Permissions, int ImageSize);
extern void __Facebook_Post(String toUserID, String URL);
extern void __Facebook_Share(String URL);
extern void __Facebook_Invite(String message);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Colors

struct rgba_t
{
	double r, g, b, a;
};

extern uint8_t CLAMPTOBYTE(int n);
extern rgba_t rgba_create(uint32_t rgba);
extern int32_t rgba_from_string(const char *str, short *ok);
extern void rgba_to_string(rgba_t rgba, char *buf, size_t len);
extern void rgba_inspect(int32_t rgba);
extern int multiply_alpha(int alpha, int color);
extern void rgba_to_argb(png_structp png, png_row_infop row_info, png_bytep data);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Base64 Encoding / Decoding

extern String toBase64(const unsigned char* bytes_to_encode, unsigned int in_len);
extern std::vector<uint8_t>* fromBase64(const char* str);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Animation Debugger

#define __cococlip_debugger_tick(CP)
#define __cococlip_debugger_paint(CP)
#define __cococlip_debugger_keyframe(CP,FI)
#define __cococlip_debugger_interpolation(CP)

#endif //__COCONUT2D_HPP__

