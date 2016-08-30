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

// ==================================================================================================================================
//	   ______                             __     ___   ____     ___    ____  ____
//	  / ____/___  _________  ____  __  __/ /_   |__ \ / __ \   /   |  / __ \/  _/
//	 / /   / __ \/ ___/ __ \/ __ \/ / / / __/   __/ // / / /  / /| | / /_/ // /
//	/ /___/ /_/ / /__/ /_/ / / / / /_/ / /_    / __// /_/ /  / ___ |/ ____// /
//	\____/\____/\___/\____/_/ /_/\__,_/\__/   /____/_____/  /_/  |_/_/   /___/
//
// ==================================================================================================================================

#include "Coconut2D.hpp"
#include "Data/CocoDataset.hpp"

#ifdef COCONUT2D_NET
#include "CocoHttpRequest.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////

String CocoAssetFile::filesPath;
String CocoAssetFile::assetPath;
String LOCAL_EMPTY_STRING;

#ifdef ANDROID_APPLICATION

AAssetManager* CocoAssetFile::manager;

void CocoAssetFile::init(AAssetManager* i_manager, String FilesPath)
{
	filesPath = FilesPath;
	manager = i_manager;
}

#endif

void CocoAssetFile::init(String FilesPath, String AssetPath)
{
	filesPath = FilesPath;
	assetPath = AssetPath;
}

void CocoAssetFile::quit()
{
	#if ANDROID_APPLICATION
	manager = nullptr;
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAssetFile* CocoAssetFile::open(String src)
{
	return new CocoAssetFile(src);
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAssetFile::CocoAssetFile(String src)
{
	hFile = nullptr;
	length = 0;
	data = nullptr;

	#ifdef IOS_APPLICATION
	#endif

	#ifdef ANDROID_APPLICATION
	if (src.charCodeAt(0) == '.')
	{
		src = src.substr(2);
	}
	ad = AAssetManager_open(manager, src.c_str(), AASSET_MODE_BUFFER);
	if (ad)
	{
		length = AAsset_getLength(ad);
		fileName = src;
	}
	#endif

	#ifdef WIN32_APPLICATION
	if (src.charCodeAt(0) == '.')
	{
		src = CocoAssetFile::filesPath + src.substr(2);
	}
	hFile = fopen(src.c_str(), "rb");
	if (hFile)
	{
		fseek(hFile, 0, SEEK_END);
		length = ftell(hFile);
		rewind(hFile);
		fileName = src;
	}
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAssetFile::~CocoAssetFile()
{
	if (data)
	{
		delete data;
		data = nullptr;
	}

	if (hFile)
	{
		fclose(hFile);
		hFile = nullptr;
	}

	#ifdef ANDROID_APPLICATION
	if (ad) AAsset_close(ad);
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CocoAssetFile::seek(long int offset, int origin)
{
	#ifdef IOS_APPLICATION
	#endif

	#ifdef ANDROID_APPLICATION
	return AAsset_seek(ad, offset, origin);
	#endif

	#ifdef WIN32_APPLICATION
	return fseek(hFile, offset, origin);
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
long int CocoAssetFile::tell()
{
	#ifdef IOS_APPLICATION
	#endif

	#ifdef ANDROID_APPLICATION
	return length - AAsset_getRemainingLength(ad);
	#endif

	#ifdef WIN32_APPLICATION
	return ftell(hFile);
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
size_t CocoAssetFile::read(void* dest, size_t size)
{
	#ifdef IOS_APPLICATION
	#endif

	#ifdef ANDROID_APPLICATION
	return AAsset_read(ad, dest, size);
	#endif

	#ifdef WIN32_APPLICATION
	return fread(dest, 1, size, hFile);
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
uint8_t* CocoAssetFile::getData()
{
	if (!data)
	{
		data = new unsigned char[length + 1];
		data[length] = 0;
		seek(0, SEEK_SET);
		read(data, length);
	}
	return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////
size_t CocoAssetFile::bytesLength()
{
	return length;
}

//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32_APPLICATION
	String getexepath()
	{
		char result[MAX_PATH];
		size_t sz = GetModuleFileNameA(NULL, result, MAX_PATH);
		String exe(result);
		return exe.substr(0, exe.lastIndexOf("\\")).replace("\\", "/");
	}
#else
	String getexepath()
	{
		char result[ PATH_MAX ];
		ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
		std::string exe(result, (count > 0) ? count : 0);
		String s(exe);
		return s.substr(0, s.lastIndexOf("\\")).replace("\\", "/");
	}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ANDROID_APPLICATION
	#include <android/log.h>
#elif IOS_APPLICATION

#else

#endif


#if ANDROID_APPLICATION
namespace std
{
	int32_t round(float n)		{ return (int32_t) ::round(n); }
	int32_t round(int32_t n)	{ return (int32_t) ::round(n); }
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
int32_t parseInt(const String& s)
{
	if (s.charCodeAt(0) == '0' && s.charCodeAt(1) == 'x')
	{
		auto number = strtoll(s.c_str(), NULL, 0);
		return (int32_t) number;
	}
	else
	{
		auto number = atoi((s).c_str());
		return (int32_t) number;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
String md5(const String& data)
{
    MD5 md5 = MD5(data);
    return md5.hexdigest();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t CLAMPTOBYTE(int n)
{
	if ((n) & (~255))
	{
		n = (uint8_t) ((-(n)) >> 31);
	}
	return (uint8_t) n;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
static T clip(T value, T minValue, T maxValue)
{
	if (value > maxValue)
		value = maxValue;
	if (value < minValue)
		value = minValue;
	return value;
}

//////////////////////////////////////////////////////////////////////////////////////////////
String btoa(const String& binary)
{
	return binary;
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool isFinite(const String& value)
{
    double d = std::atof(value.c_str());
    std::ostringstream ss;
    ss << d;
    std::string t(ss.str());
    return (t==value ? std::isfinite(d) : false);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void alert(String msg)
{
	#if WIN32_APPLICATION
	MessageBoxA(NULL, msg.c_str(), NULL, 0);
	#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////
void clearInterval(int handle)
{
	/*
	if(!handle) return;
	try
	{
		TimerThread* t = reinterpret_cast<TimerThread*>(handle);
		t->stop();
		delete t;
	}
	catch(...)
	{
	}
	*/
}

//////////////////////////////////////////////////////////////////////////////////////////////
void __Facebook_Initialize(String AppID, int ImageSize)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
void __Facebook_Login(String Permissions, int ImageSize)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
void __Facebook_Post(String toUserID, String URL)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
void __Facebook_Share(String URL)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
void __Facebook_Invite(String message)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fixTouch(Touch* touch)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
extern String encodeURIComponent(String uri)
{
	return uri;
}

// ==================================================================================================================================
//	   ______      __
//	  / ____/___  / /___  __________
//	 / /   / __ \/ / __ \/ ___/ ___/
//	/ /___/ /_/ / / /_/ / /  (__  )
//	\____/\____/_/\____/_/  /____/
//
// ==================================================================================================================================

template <typename parsed_t>
static bool parse_integer(const char** pStr, parsed_t *pParsed)
{
	parsed_t& c = *pParsed;
	const char*& str = *pStr;
	int8_t sign = 1;

	c = 0;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;

	if (*str >= '0' && *str <= '9')
	{
		do
		{
			c *= 10;
			c += *str++ - '0';
		} while (*str >= '0' && *str <= '9');
	}
	else
	{
		return false;
	}
	if (sign < 0)
		c = -c;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool parse_rgb_channel(const char** pStr, uint8_t *pChannel)
{
	int channel;
	if (parse_integer(pStr, &channel))
	{
		*pChannel = clip(channel, 0, 255);
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WHITESPACE \
				while (' ' == *str) ++str;

#define WHITESPACE_OR_COMMA \
				while (' ' == *str || ',' == *str) ++str;

#define CHANNEL(NAME) \
	if (!parse_rgb_channel(&str, &NAME)) \
	return 0; \

#define ALPHA(NAME) \
  if (*str >= '1' && *str <= '9') { \
      NAME = 1; \
          } else { \
      if ('0' == *str) ++str; \
      if ('.' == *str) { \
        ++str; \
        float n = .1f; \
						        while (*str >= '0' && *str <= '9') { \
          NAME += (*str++ - '0') * n; \
          n *= .1f; \
																		        } \
	  	  	        } \
          } \
    do {} while (0) // require trailing semicolon


/////////////////////////////////////////////////////////////////////////////
rgba_t	rgba_create(uint32_t rgba)
{
	rgba_t color;
	color.r = (double) (rgba >> 24) / 255;
	color.g = (double) (rgba >> 16 & 0xff) / 255;
	color.b = (double) (rgba >> 8 & 0xff) / 255;
	color.a = (double) (rgba & 0xff) / 255;
	return color;
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return r << 24 | g << 16 | b << 8 | a;
}

/////////////////////////////////////////////////////////////////////////////
int h(char c)
{
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return c - '0';

	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return (c - 'a') + 10;

	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		return (c - 'A') + 10;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
static int32_t rgba_from_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return rgba_from_rgba(r, g, b, 255);
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_hex6_string(const char *str)
{
	return rgba_from_rgb((h(str[0]) << 4) + h(str[1]), (h(str[2]) << 4) + h(str[3]), (h(str[4]) << 4) + h(str[5]));
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_hex8_string(const char *str)
{
	return rgba_from_rgba((h(str[2]) << 4) + h(str[3]), (h(str[4]) << 4) + h(str[5]), (h(str[6]) << 4) + h(str[7]), (h(str[0]) << 4) + h(str[1]));
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_hex3_string(const char *str)
{
	return rgba_from_rgb((h(str[0]) << 4) + h(str[0]), (h(str[1]) << 4) + h(str[1]), (h(str[2]) << 4) + h(str[2]));
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_hex_string(const char *str, short *ok)
{
	size_t len = strlen(str);
	*ok = 1;
	if (8 == len) return rgba_from_hex8_string(str);
	if (6 == len) return rgba_from_hex6_string(str);
	if (3 == len) return rgba_from_hex3_string(str);
	return *ok = 0;
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_rgba_string(const char *str, short *ok)
{
	if (str == strstr(str, "rgba("))
	{
		str += 5;
		WHITESPACE;
		uint8_t r = 0, g = 0, b = 0;
		float a = 0;
		CHANNEL(r);
		WHITESPACE_OR_COMMA;
		CHANNEL(g);
		WHITESPACE_OR_COMMA;
		CHANNEL(b);
		WHITESPACE_OR_COMMA;
		ALPHA(a);
		WHITESPACE;
		return *ok = 1, rgba_from_rgba(r, g, b, (int) (a * 255));
	}
	return *ok = 0;
}

/////////////////////////////////////////////////////////////////////////////
int32_t rgba_from_rgb_string(const char *str, short *ok)
{
	if (str == strstr(str, "rgb("))
	{
		str += 4;
		WHITESPACE;
		uint8_t r = 0, g = 0, b = 0;
		CHANNEL(r);
		WHITESPACE_OR_COMMA;
		CHANNEL(g);
		WHITESPACE_OR_COMMA;
		CHANNEL(b);
		WHITESPACE;
		return *ok = 1, rgba_from_rgb(r, g, b);
	}
	return *ok = 0;
}

/////////////////////////////////////////////////////////////////////////////
int32_t	rgba_from_string(const char *str, short *ok)
{
	if ('#' == str[0])
		return rgba_from_hex_string(++str, ok);
	if ('0' == str[0] && 'x' == str[1])
	{
		str++;
		return rgba_from_hex_string(++str, ok);
	}
	if (str == strstr(str, "rgba"))
		return rgba_from_rgba_string(str, ok);
	if (str == strstr(str, "rgb"))
		return rgba_from_rgb_string(str, ok);

	return 0x00000000;
}

/////////////////////////////////////////////////////////////////////////////
void rgba_to_string(rgba_t rgba, char *buf, size_t len)
{
	if (1 == rgba.a)
	{
		snprintf(buf, len, "#%.2x%.2x%.2x", (int) (rgba.r * 255), (int) (rgba.g * 255), (int) (rgba.b * 255));
	}
	else
	{
		snprintf(buf, len, "rgba(%d, %d, %d, %.2f)", (int) (rgba.r * 255), (int) (rgba.g * 255), (int) (rgba.b * 255), rgba.a);
	}
}

// ==================================================================================================================================
//	    ___          ____
//	   /   |  ____  / / /_  ____ _
//	  / /| | / __ \/ / __ \/ __ `/
//	 / ___ |/ /_/ / / / / / /_/ /
//	/_/  |_/ .___/_/_/ /_/\__,_/
//	      /_/
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
int multiply_alpha(int alpha, int color)
{
	int temp = (alpha * color) + 0x80;
	return ((temp + (temp >> 8)) >> 8);
}

/////////////////////////////////////////////////////////////////////////////
// Premultiplies data and converts RGBA bytes => ARGB (native endian)
void premultiply_data(png_structp   png, png_row_infop row_info, png_bytep data)
{
	size_t i;

	for (i = 0; i < row_info->rowbytes; i += 4)
	{
		uint8_t *base = &data[i];
		uint8_t  alpha = base[3];
		uint32_t p;

		if (alpha == 0)
		{
			p = 0;
		}
		else
		{
			uint8_t  red = base[0];
			uint8_t  green = base[1];
			uint8_t  blue = base[2];

			if (alpha != 0xff)
			{
				red = multiply_alpha(alpha, red);
				green = multiply_alpha(alpha, green);
				blue = multiply_alpha(alpha, blue);
			}
			p = (alpha << 24) | (red << 16) | (green << 8) | (blue << 0);
		}
		memcpy(base, &p, sizeof(uint32_t));
	}
}

/////////////////////////////////////////////////////////////////////////////
// Unpremultiplies data and converts native endian ARGB => RGBA bytes
void unpremultiply_data(png_structp png, png_row_infop row_info, png_bytep data)
{
	size_t i;

	for (i = 0; i < row_info->rowbytes; i += 4)
	{
		uint8_t *b = &data[i];
		uint32_t pixel;
		uint8_t  alpha;

		memcpy(&pixel, b, sizeof(uint32_t));
		alpha = (pixel & 0xff000000) >> 24;
		if (alpha == 0)
		{
			b[0] = b[1] = b[2] = b[3] = 0;
		}
		else
		{
			b[0] = ((((pixel & 0xff0000) >> 16) * 255 + alpha / 2) / alpha) & 0xFF;
			b[1] = ((((pixel & 0x00ff00) >> 8) * 255 + alpha / 2) / alpha) & 0xFF;
			b[2] = ((((pixel & 0x0000ff) >> 0) * 255 + alpha / 2) / alpha) & 0xFF;
			b[3] = alpha;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Converts native endian xRGB => RGBx bytes
void rgba_to_argb(png_structp png, png_row_infop row_info, png_bytep data)
{
	size_t i;

	for (i = 0; i < row_info->rowbytes; i += 4)
	{
		uint8_t *b = &data[i];
		uint32_t pixel;

		memcpy(&pixel, b, sizeof(uint32_t));

		b[0] = (pixel & 0x0000ff) >> 24;
		b[1] = (pixel & 0x0000ff) >> 0;
		b[2] = (pixel & 0x00ff00) >> 8;
		b[3] = 0;// (pixel & 0xff0000) >> 16;
	}
}

// ==================================================================================================================================
//	   __________  ______________
//	  / ____/ __ \/ ____/__  /__ \
//	 / /   / /_/ / /     /_ <__/ /
//	/ /___/ _, _/ /___ ___/ / __/
//	\____/_/ |_|\____//____/____/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long GetCRC(long buf, long BufSize)
{
	uint32_t crc = 0xFFFFFFFF;
	size_t size = (size_t) BufSize;

	const uint8_t *p = (uint8_t*) buf;
	//crc = ~crc;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return ~crc;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string crc32(void* buf, long BufSize)
{
	std::stringstream ss;
	ss << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << GetCRC((long) buf, BufSize);
	return ss.str();
}

// ==================================================================================================================================
//	    __  _______  ______
//	   /  |/  / __ \/ ____/
//	  / /|_/ / / / /___ \
//	 / /  / / /_/ /___/ /
//	/_/  /_/_____/_____/
//
// ==================================================================================================================================

// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// F, G, H and I are basic MD5 functions.
inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) {
	return (x&y) | (~x&z);
}

inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) {
	return (x&z) | (y&~z);
}

inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) {
	return x^y^z;
}

inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) {
	return y ^ (x | ~z);
}

// rotate_left rotates x left n bits.
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) {
	return (x << n) | (x >> (32 - n));
}

// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
// Rotation is separate from addition to prevent recomputation.
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + F(b, c, d) + x + ac, (int) s) + b;
}

inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + G(b, c, d) + x + ac, (int) s) + b;
}

inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + H(b, c, d) + x + ac, (int) s) + b;
}

inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
	a = rotate_left(a + I(b, c, d) + x + ac, (int) s) + b;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Default ctor, just initialize
MD5::MD5()
{
	init();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Nifty shortcut ctor, compute MD5 for string and finalize it right away
MD5::MD5(const std::string &text)
{
	init();
	update(text.c_str(), (size_type) text.length());
	finalize();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void MD5::init()
{
	finalized = false;

	count[0] = 0;
	count[1] = 0;

	// load magic initialization constants.
	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
void MD5::decode(uint4 output[], const uint1 input[], size_type len)
{
	for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint4) input[j]) | (((uint4) input[j + 1]) << 8) |
		(((uint4) input[j + 2]) << 16) | (((uint4) input[j + 3]) << 24);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Encodes input (uint4) into output (unsigned char). Assumes len is a multiple of 4.
void MD5::encode(uint1 output[], const uint4 input[], size_type len)
{
	for (size_type i = 0, j = 0; j < len; i++, j += 4) {
		output[j] = input[i] & 0xff;
		output[j + 1] = (input[i] >> 8) & 0xff;
		output[j + 2] = (input[i] >> 16) & 0xff;
		output[j + 3] = (input[i] >> 24) & 0xff;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Apply MD5 algo on a block
void MD5::transform(const uint1 block[blocksize])
{
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
	decode(x, block, blocksize);

	/* Round 1 */
	FF(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */
	FF(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
	FF(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
	FF(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
	FF(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
	FF(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
	FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
	FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
	FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
	FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

	/* Round 2 */
	GG(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
	GG(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
	GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
	GG(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
	GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
	GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
	GG(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
	GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
	GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

	/* Round 3 */
	HH(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
	HH(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
	HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
	HH(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
	HH(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
	HH(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */

	/* Round 4 */
	II(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
	II(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
	II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
	II(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */
	II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
	II(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
	II(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */
	II(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
	II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
	II(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
	II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
	II(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	// Zeroize sensitive information.
	memset(x, 0, sizeof x);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD5 block update operation. Continues an MD5 message-digest
// operation, processing another message block
void MD5::update(const unsigned char input[], size_type length)
{
	// compute number of bytes mod 64
	size_type index = count[0] / 8 % blocksize;

	// Update number of bits
	if ((count[0] += (length << 3)) < (length << 3))
		count[1]++;
	count[1] += (length >> 29);

	// number of bytes we need to fill in buffer
	size_type firstpart = 64 - index;

	size_type i;

	// transform as many times as possible.
	if (length >= firstpart)
	{
		// fill buffer first, transform
		memcpy(&buffer[index], input, firstpart);
		transform(buffer);

		// transform chunks of blocksize (64 bytes)
		for (i = firstpart; i + blocksize <= length; i += blocksize)
			transform(&input[i]);

		index = 0;
	}
	else
		i = 0;

	// buffer remaining input
	memcpy(&buffer[index], &input[i], length - i);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// for convenience provide a verson with signed char
void MD5::update(const char input[], size_type length)
{
	update((const unsigned char*) input, length);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MD5 finalization. Ends an MD5 message-digest operation, writing the
// the message digest and zeroizing the context.
MD5& MD5::finalize()
{
	static unsigned char padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	if (!finalized) {
		// Save number of bits
		unsigned char bits[8];
		encode(bits, count, 8);

		// pad out to 56 mod 64.
		size_type index = count[0] / 8 % 64;
		size_type padLen = (index < 56) ? (56 - index) : (120 - index);
		update(padding, padLen);

		// Append length (before padding)
		update(bits, 8);

		// Store state in digest
		encode(digest, state, 16);

		// Zeroize sensitive information.
		memset(buffer, 0, sizeof buffer);
		memset(count, 0, sizeof count);

		finalized = true;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return hex representation of digest as string
std::string MD5::hexdigest() const
{
	if (!finalized)
		return "";

	char buf[33];
	for (int i = 0; i < 16; i++)
		sprintf(buf + i * 2, "%02x", digest[i]);
	buf[32] = 0;

	return std::string(buf);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& out, MD5 md5)
{
	return out << md5.hexdigest();
}

// ==================================================================================================================================
//	    ____                  _____ __ __
//	   / __ )____ _________  / ___// // /
//	  / __  / __ `/ ___/ _ \/ __ \/ // /_
//	 / /_/ / /_/ (__  )  __/ /_/ /__  __/
//	/_____/\__,_/____/\___/\____/  /_/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////////////////////////////////
String toBase64(const unsigned char* bytes_to_encode, unsigned int in_len)
{
	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	String ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////
std::vector<uint8_t>* fromBase64(const char* str)
{
	static const unsigned char unb64[] = { 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

	size_t len = strlen(str);
	if (len < 2) return nullptr;
	int pad = 0;
	if (str[len - 1] == '=') pad++;
	if (str[len - 2] == '=') pad++;

	size_t pixelsByteLen = 3 * len / 4 - pad;
	std::vector<uint8_t>* bytes = new std::vector<uint8_t>;
	bytes->resize(pixelsByteLen);
	uint8_t* pixels = bytes->data();

	size_t i, c = 0;
	unsigned char A, B, C, D;
	for (i = 0; i < len - 4 - pad; i += 4)
	{
		A = unb64[str[i] - 43];
		B = unb64[str[i + 1] - 43];
		C = unb64[str[i + 2] - 43];
		D = unb64[str[i + 3] - 43];

		pixels[c++] = ((A << 2) | (B >> 4)) & 0xFF;
		pixels[c++] = ((B << 4) | (C >> 2)) & 0xFF;
		pixels[c++] = ((C << 6) | (D)) & 0xFF;
	}
	if (pad == 1)
	{
		A = unb64[str[i] - 43];
		B = unb64[str[i + 1] - 43];
		C = unb64[str[i + 2] - 43];

		pixels[c++] = ((A << 2) | (B >> 4)) & 0xFF;
		pixels[c++] = ((B << 4) | (C >> 2)) & 0xFF;
	}
	else if (pad == 2)
	{
		A = unb64[str[i] - 43];
		B = unb64[str[i + 1] - 43];

		pixels[c++] = ((A << 2) | (B >> 4)) & 0xFF;
	}

	return bytes;
}

// ==================================================================================================================================
//	    ____  _   ________
//	   / __ \/ | / / ____/
//	  / /_/ /  |/ / / __
//	 / ____/ /|  / /_/ /
//	/_/   /_/ |_/\____/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
bool isPNG(uint8_t* data)
{
	return data && ('P' == data[1] && 'N' == data[2] && 'G' == data[3]);
}

/////////////////////////////////////////////////////////////////////////////
void png_from_memory(png_structp png_ptr, png_bytep readBytes, png_size_t readCount)
{
	read_closure_t* t = (read_closure_t*) png_get_io_ptr(png_ptr);
	memcpy(readBytes, t->buf + t->len, readCount);
	t->len += readCount;
}

/////////////////////////////////////////////////////////////////////////////
uint8_t* pixels_from_png(const uint8_t* inBytes, const size_t inBytesLen, size_t& outPixelsBytesLen, uint32_t& width, uint32_t& height, bool premultiply)
{
	width = 0;
	height = 0;
	outPixelsBytesLen = 0;

	read_closure_t t;
	t.buf = inBytes;
	t.len = 0;

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);
	png_set_read_fn(png_ptr, (png_voidp) &t, png_from_memory);

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return nullptr;
	}

	// Read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	// Get info about PNG
	int color_type;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, (png_uint_32*) &width, (png_uint_32*) &height, &bit_depth, &color_type, 0, 0, 0);

	// Convert RGBA to ARGB
	if (premultiply)
		png_set_read_user_transform_fn(png_ptr, premultiply_data);

	// Make sure we already end up reading PNG24 RGBA bytes
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_expand(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_expand(png_ptr);
	if (bit_depth == 16) png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) png_set_gray_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_RGB) png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);

	// Update the PNG info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Get row size in bytes (should be aligned to 4 bytes)
	int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	row_bytes += 3 - ((row_bytes - 1) % 4); // unnecessary hack to align to 4 bytes

	// Initialize raw pixels storage
	outPixelsBytesLen = row_bytes*height;
	uint8_t* outPixels = new uint8_t[outPixelsBytesLen];

	// Read PNG image into storage using row pointers
	std::vector<png_byte*> rowData(height);
	for (size_t i = 0; i < height; i++)	rowData[i] = i * row_bytes + (png_byte*) (outPixels);
	png_read_image(png_ptr, &rowData.front());

	// Done
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return outPixels;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static void png_to_memory(png_structp png_ptr, png_bytep data, png_size_t length)
{
	std::vector<uint8_t>* buffer = (std::vector<uint8_t>*) png_get_io_ptr(png_ptr);
	buffer->resize(buffer->size() + length);
	memcpy(buffer->data() + buffer->size() - length, data, length);
}

//////////////////////////////////////////////////////////////////////////////////////////////
std::vector<uint8_t>* pixels_to_png(const uint8_t* pixels, size_t width, size_t height, bool unpremultiply)
{
	if (pixels == nullptr)
		return nullptr;

	std::vector<uint8_t>* buffer = new std::vector<uint8_t>;

	const int bit_depth = 8;
	const size_t bytes_per_pixel = 4; // RGBA
	#define Z_DEFAULT_STRATEGY    0	  // zlib 0 = Super Fast

	// Allocate PNG write structures
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop info_ptr = png_create_info_struct(png_ptr);

	// Set defaults
	png_set_compression_strategy(png_ptr, Z_DEFAULT_STRATEGY);
	png_set_compression_mem_level(png_ptr, 8);
	png_set_compression_window_bits(png_ptr, 15);
	png_set_compression_method(png_ptr, 8);

	// Shift the pixels up to a legal bit depth and fill in as appropriate to correctly scale the image.
	png_color_8 sig_bit;
	sig_bit.red = bit_depth;
	sig_bit.green = bit_depth;
	sig_bit.blue = bit_depth;
	sig_bit.alpha = bit_depth;
	png_set_shift(png_ptr, &sig_bit);

	// Pack pixels into bytes
	png_set_packing(png_ptr);

	if (unpremultiply)
		png_set_write_user_transform_fn(png_ptr, unpremultiply_data);

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		// PNG Write Error
		png_destroy_write_struct(&png_ptr, NULL);
		return nullptr;
	}
	else
	{
		// Write PNG Header
		png_set_IHDR(png_ptr, info_ptr, (png_uint_32) width, (png_uint_32) height, bit_depth, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_DEFAULT);

		// Allocate PNG rows buffer
		int32_t bytes_per_row = (int32_t) bytes_per_pixel * width;
		png_bytepp rows = (png_bytepp) png_malloc(png_ptr, (size_t) height * sizeof(png_bytep));

		// Write image data to PNG rows
		for (int32_t y = height; y--;)
		{
			rows[y] = (png_bytep) png_malloc(png_ptr, (size_t) bytes_per_row * sizeof(png_byte));
			memcpy(rows[y], pixels + y * bytes_per_row, (size_t) bytes_per_row);
		}
		png_set_rows(png_ptr, info_ptr, rows);

		// Write PNG to Array Buffer
		png_set_write_fn(png_ptr, buffer, png_to_memory, NULL);
		png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
		png_write_end(png_ptr, NULL);

		// Free PNG rows
		for (int32_t y = height; y--;)
			png_free(png_ptr, rows[y]);

		png_free(png_ptr, rows);
	}

	// Done
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return buffer;
}

// ==================================================================================================================================
//	       ______  ____________
//	      / / __ \/ ____/ ____/
//	 __  / / /_/ / __/ / / __
//	/ /_/ / ____/ /___/ /_/ /
//	\____/_/   /_____/\____/
//
// ==================================================================================================================================

/////////////////////////////////////////////////////////////////////////////
bool isJPEG(uint8_t* data)
{
	return data && (0xff == data[0] && 0xd8 == data[1]);
}

/////////////////////////////////////////////////////////////////////////////
void jpg_error(j_common_ptr cInfo)
{
	char pszMessage[JMSG_LENGTH_MAX];
	(*cInfo->err->format_message)(cInfo, pszMessage);
}

/////////////////////////////////////////////////////////////////////////////
uint8_t* pixels_from_jpeg(const uint8_t* inBytes, const size_t inBytesLen, size_t& outPixelsBytesLen, uint32_t& width, uint32_t& height, bool premultiply)
{
	size_t rowBytesIn, rowBytesOut;
	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jError;
	cInfo.err = jpeg_std_error(&jError);
	jError.error_exit = jpg_error;
	jpeg_create_decompress(&cInfo);
	jpeg_mem_src(&cInfo, (unsigned char*) inBytes, inBytesLen);
	jpeg_read_header(&cInfo, TRUE);
	jpeg_start_decompress(&cInfo);
	width = cInfo.output_width;
	height = cInfo.output_height;
	rowBytesIn = width * cInfo.output_components;
	rowBytesOut = width * sizeof(uint32_t);
	outPixelsBytesLen = height * rowBytesOut;
	uint8_t* outPixels = new uint8_t[outPixelsBytesLen];
	JSAMPLE* pSample = (JSAMPLE*) malloc(rowBytesIn);
	JSAMPROW pRow[1];
	pRow[0] = pSample;
	unsigned char* ptrRow;
	unsigned char* ptr = (unsigned char*) outPixels;
	uint8_t R;
	for (uint32_t i = height; i--;)
	{
		jpeg_read_scanlines(&cInfo, pRow, 1);
		ptrRow = (unsigned char*) (&(pRow[0][0]));
		for (uint32_t r = width; r--; ptr += 4, ptrRow += 3)
		{
			if (premultiply)
			{
				memcpy(ptr, ptrRow, 3);
				R = ptr[0];
				ptr[0] = ptr[2];
				ptr[2] = R;
				ptr[3] = 0xFF;
			}
			else
			{
				memcpy(ptr, ptrRow, 3);
				ptr[3] = 0xFF;
			}
		}
	}
	free(pSample);
	jpeg_finish_decompress(&cInfo);
	jpeg_destroy_decompress(&cInfo);
	return outPixels;
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine* engine;
HTMLWindow* window;
HTMLWindow* global;
HTMLDocument* document;
CocoScene* ____debugger_current_scene;
