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

#include "Coconut2D.hpp"
#include "CocoAssetFile.h" // <- Device Specific

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


/*

int32_t 	math_floor(int32_t n)				{ return std::floor(n); }
int32_t 	math_floor(float n)					{ return std::floor( (int32_t) n); }

int32_t 	math_ceil(int32_t n)				{ return std::ceil(n); }
int32_t 	math_ceil(float n)					{ return std::ceil( (int32_t) n); }

int32_t 	math_log(int32_t n)					{ return std::log(n); }
int32_t 	math_log(float n)					{ return std::log( (int32_t) n); }

int32_t 	math_abs(int32_t n)					{ return std::abs(n); }
int32_t 	math_abs(float n)					{ return std::abs( (int32_t) n); }

float 		math_sqrt(float n)					{ return std::sqrt(n); }
float 		math_sqrt(int32_t n)				{ return std::sqrt( (float) n); }

int32_t 	math_round(int32_t n)				{ return (int32_t) round( (float) n); }
int32_t 	math_round(float n)					{ return (int32_t) round( (float) n); }

float 		math_asin(float n)					{ return std::asin(n); }
float 		math_asin(int32_t n)				{ return std::asin( (float) n); }

float 		math_acos(float n)					{ return std::acos(n); }
float 		math_acos(int32_t n)				{ return std::acos( (float) n); }

float 		math_sin(float n)					{ return std::sin(n); }
float 		math_sin(int32_t n)					{ return std::sin( (float) n); }

float 		math_cos(float n)					{ return std::cos(n); }
float 		math_cos(int32_t n)					{ return std::cos( (float) n); }

*/


//////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine* engine;
HTMLWindow* window;
HTMLWindow* global;
HTMLDocument* document;

//////////////////////////////////////////////////////////////////////////////////////////////
String md5(String data)
{
    MD5 md5 = MD5(data);
    return md5.hexdigest();
}

//////////////////////////////////////////////////////////////////////////////////////////////
String btoa(String binary)
{
	return binary;
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool isFinite(String value)
{
    double d = std::atof(value.c_str());
    std::ostringstream ss;
    ss << d;
    std::string t(ss.str());
    return (t==value ? std::isfinite(d) : false);
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

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage(const String str, int32_t& width, int32_t& height)
{
	CocoAssetFile* file = CocoAssetFile::open(str.c_str());
    if(!file)
    {
        std::cout << "Error Loading Image: " << str << "\n";
        return NULL;
    }
	switch(file->mime)
	{
		case CocoAssetFile::MIME::IMAGE_PNG: return NewFromImage_PNG(file, width, height);
		case CocoAssetFile::MIME::IMAGE_JPG: return NewFromImage_JPG(file, width, height);
		default:
			return NULL;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////
String ArrayBuffer::encodeAsBase64()
{
	static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
	STD_STRING ret;

	int32_t pad = (3 - (byteLength % 3)) % 3;
	int32_t len = 4 * (byteLength + pad) / 3;
	ret.resize( (size_t)len );

    size_t c = 0;
    int32_t i = 0;
	unsigned char b0, b1, b2;

	for(i = 0; i < byteLength - 2; i += 3 )
	{
		b0 = *((unsigned char*)(data) + i);
		b1 = *((unsigned char*)(data) + i + 1);
		b2 = *((unsigned char*)(data) + i + 2);
		ret[c++] = b64[b0 >> 2];
		ret[c++] = b64[((b0 & 0x03) << 4) | (b1 >> 4)];
		ret[c++] = b64[((b1 & 0x0F) << 2) | (b2 >> 6)];
		ret[c++] = b64[b2 & 0x3F];
	}

	if(pad == 1)
	{
		b0 = *((unsigned char*)(data) + i);
		b1 = *((unsigned char*)(data) + i + 1);
		ret[c++] = b64[b0 >> 2];
		ret[c++] = b64[((b0 & 0x03) << 4) | (b1 >> 4)];
		ret[c++] = b64[((b1 & 0x0F) << 2)];
		ret[c++] = b64[64];
	}
	else if(pad == 2)
	{
		b0 = *((unsigned char*)(data) + i);
		ret[c++] = b64[b0 >> 2];
		ret[c++] = b64[((b0 & 0x03) << 4)];
		ret[c++] = b64[64];
		ret[c++] = b64[64];
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static void png_from_memory(png_structp png_ptr, png_bytep readBytes, png_size_t readCount)
{
	CocoAssetFile* file = (CocoAssetFile*)png_get_io_ptr(png_ptr);
	file->read(readBytes, readCount);
}

//////////////////////////////////////////////////////////////////////////////////////////////
static void png_to_memory(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ArrayBuffer* buffer = (ArrayBuffer*)png_get_io_ptr(png_ptr);
	buffer->byteLength += length;
	buffer->data = realloc(buffer->data, (size_t) buffer->byteLength);
	memcpy((*buffer)[buffer->byteLength - (int32_t)length], data, length);
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage_PNG(CocoAssetFile* file, int32_t& width, int32_t& height)
{
    width = 0;
    height = 0;

    if(!file) return nullptr;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_set_read_fn(png_ptr, (png_voidp)file, png_from_memory);

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        // PNG Read Error
        width = 0;
        height = 0;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        //free(png_ptr);
        //free(info_ptr);
        return nullptr;
    }

    // Read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // Get info about PNG
    int color_type;
    int bit_depth;
    png_get_IHDR( png_ptr, info_ptr, (png_uint_32*)&width, (png_uint_32*)&height, &bit_depth, &color_type, 0, 0, 0 );

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
    png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    row_bytes += 3 - ((row_bytes-1) % 4); // unnecessary hack to align to 4 bytes

    // Initialize raw pixels storage
    int32_t size = (int32_t)row_bytes * height;
    ArrayBuffer* t = new ArrayBuffer(size);

    // Read PNG image into storage using row pointers
    std::vector<png_byte*> rowData((size_t)height);
    for(png_size_t i=0; i<(png_size_t)height; i++)
        rowData[i] = (png_byte*) (i * row_bytes + (png_byte*)(t->data));
    png_read_image(png_ptr, &rowData.front());

    // Done
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    //free(png_ptr);
    //free(info_ptr);

    return t;
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::encodeAsPNG(int32_t width, int32_t height)
{
    const int bit_depth = 8;
	const size_t bytes_per_pixel = 4; //RGBA
    #define Z_DEFAULT_STRATEGY    0

    ArrayBuffer* buffer = nullptr;

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

    if(setjmp(png_jmpbuf(png_ptr)))
    {
        // PNG Write Error
        png_destroy_write_struct(&png_ptr, NULL);
        //free(png_ptr);
        //free(info_ptr);
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
        for(int32_t y = height; y--;)
        {
            rows[y] = (png_bytep) png_malloc(png_ptr, (size_t) bytes_per_row * sizeof(png_byte));
            memcpy(rows[y], (*this)[y * bytes_per_row], (size_t) bytes_per_row);
        }
        png_set_rows(png_ptr, info_ptr, rows);

        // Write PNG to Array Buffer
        buffer = new ArrayBuffer(0);
        png_set_write_fn(png_ptr, buffer, png_to_memory, NULL);
        png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
        png_write_end(png_ptr, NULL);

        // Free PNG rows
        for(int32_t y = height; y--;)
            png_free(png_ptr, rows[y]);

        png_free(png_ptr, rows);
    }

    // Done
    png_destroy_write_struct(&png_ptr, &info_ptr);
    //free(png_ptr);
    //free(info_ptr);

    return buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////
static void jpeg_error(j_common_ptr cInfo)
{
	char pszMessage[JMSG_LENGTH_MAX];
	(*cInfo->err->format_message)(cInfo, pszMessage);
	trace(pszMessage);
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage_JPG(CocoAssetFile* file, int32_t& width, int32_t& height)
{
	ArrayBuffer* ret = NULL;

	if(!file) return ret;

	size_t rowBytesIn, rowBytesOut;
	jpeg_decompress_struct cInfo;
	jpeg_error_mgr jError;
	cInfo.err = jpeg_std_error(&jError);
	jError.error_exit = jpeg_error;
	jpeg_create_decompress(&cInfo);
	jpeg_mem_src(&cInfo, (unsigned char*)file->getData(), file->getLength());
	jpeg_read_header(&cInfo, TRUE);
	jpeg_start_decompress(&cInfo);
	width = (int32_t) cInfo.output_width;
	height = (int32_t) cInfo.output_height;
	rowBytesIn = (size_t)width * (size_t)cInfo.output_components;
	rowBytesOut = (size_t) width * sizeof(uint32_t);

	ArrayBuffer* t = new ArrayBuffer( height * (int32_t)rowBytesOut);

	JSAMPLE* pSample = (JSAMPLE*)malloc(rowBytesIn);

	JSAMPROW pRow[1];
	pRow[0] = pSample;
	unsigned char* ptrRow;

	unsigned char* ptr = (unsigned char*)((*t)[0]);
	for(int32_t i = height; i--;)
	{
		jpeg_read_scanlines(&cInfo, pRow, 1);
		ptrRow = (unsigned char*)(&(pRow[0][0]));
		for(int32_t r = width; r--; ptr += 4, ptrRow += 3)
		{
			memcpy(ptr, ptrRow, 3);
			ptr[3] = 0xFF;
		}
	}

	free(pSample);
	jpeg_finish_decompress(&cInfo);
	jpeg_destroy_decompress(&cInfo);
	ret = t;

	delete file;
	return ret;
}
