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

//////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine* engine;
HTMLWindow* window;
HTMLWindow* global;
HTMLDocument* document;

void trace(const char* fmt, ...)
{
	char* buff = (char*) malloc(65535);
	va_list vl;
	va_start(vl, fmt);
	vsprintf(buff, fmt, vl);
	va_end(vl);

	#ifdef ANDROID_APPLICATION
		__android_log_print(ANDROID_LOG_INFO, APPNAME, buff,"");

	#elif IOS_APPLICATION
        NSString *string = [NSString stringWithUTF8String:buff];
        NSLog(@"%@", string);

	#elif WIN32_APPLICATION
		printf("%s\n", buff);
		fflush(stdout);
	#else

	#endif

	free(buff);
}

//////////////////////////////////////////////////////////////////////////////////////////////
String md5(String data)
{
	return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////
String btoa(String binary)
{
	return binary;
}

//////////////////////////////////////////////////////////////////////////////////////////////
bool isFinite(String value)
{
	return true;
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
ArrayBuffer* ArrayBuffer::NewFromImage(std::string str, uint32_t& width, uint32_t& height)
{
	CocoAssetFile* file = CocoAssetFile::open(str.c_str());
	switch(file->mime)
	{
		#ifdef ENABLE_PNG_SUPPORT
		case CocoAssetFile::MIME::IMAGE_PNG: return NewFromImage_PNG(file, width, height);
		#endif

		#ifdef ENABLE_JPG_SUPPORT
		case CocoAssetFile::MIME::IMAGE_JPG: return NewFromImage_JPG(file, width, height);
		#endif
		default:
			return NULL;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////
String ArrayBuffer::encodeAsBase64()
{
	static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
	String ret;

	int pad = (3 - (byteLength % 3)) % 3;
	size_t len = 4 * (byteLength + pad) / 3;
	ret.resize(len);

	size_t c = 0, i = 0;
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

#ifdef ENABLE_PNG_SUPPORT

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
	buffer->data = realloc(buffer->data, buffer->byteLength);
	memcpy((*buffer)[buffer->byteLength - length], data, length);
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage_PNG(CocoAssetFile* file, uint32_t& width, uint32_t& height)
{
	ArrayBuffer* ret = NULL;
	unsigned char sig[8];
	size_t rowbytes;
	png_bytepp rows;

	if(!file) return ret;

	file->read(sig, 8);

	if(!png_sig_cmp(sig, 0, 8))
	{
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if(png_ptr && info_ptr && !setjmp(png_jmpbuf(png_ptr)))
		{
			png_set_read_fn(png_ptr, (png_voidp)file, png_from_memory);
			png_set_sig_bytes(png_ptr, 8);
			png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB | PNG_TRANSFORM_PACKING, nullptr);
			width = png_get_image_width(png_ptr, info_ptr);
			height = png_get_image_height(png_ptr, info_ptr);
			rows = png_get_rows(png_ptr, info_ptr);
			rowbytes = png_get_rowbytes(png_ptr, info_ptr);

			ArrayBuffer* t = new ArrayBuffer(height * rowbytes);

			for(uint32_t i = height; i--;)
				memcpy((*t)[rowbytes * i], rows[i], rowbytes);

			ret = t;
		}
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	}
	delete file;
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::encodeAsPNG(size_t width, size_t height)
{
	const size_t bytes_per_pixel = 4;
    ArrayBuffer* ret = new ArrayBuffer(0);

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr)
	{
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if(info_ptr)
		{
			if(!setjmp(png_jmpbuf(png_ptr)))
			{
				png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
				size_t bytes_per_row = bytes_per_pixel * width;
				png_bytepp rows = (png_bytepp)png_malloc(png_ptr, sizeof(png_bytep) * height);
				for(size_t y = height; y--;)
				{
					rows[y] = (png_bytep)png_malloc(png_ptr, sizeof(png_byte) * bytes_per_row);
					memcpy(rows[y], (*this)[y * bytes_per_row], bytes_per_row);
				}
				png_set_rows(png_ptr, info_ptr, rows);
				png_set_write_fn(png_ptr, ret, png_to_memory, NULL);
				png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
				for(size_t y = height; y--;)
					png_free(png_ptr, rows[y]);
				png_free(png_ptr, rows);
			}
			png_destroy_write_struct(&png_ptr, &info_ptr);
		}
		else
			png_destroy_write_struct(&png_ptr, NULL);
	}
	return ret;
}

#endif /* ENABLE_PNG_SUPPORT */

#ifdef ENABLE_JPG_SUPPORT

//////////////////////////////////////////////////////////////////////////////////////////////
static void jpeg_error(j_common_ptr cInfo)
{
	char pszMessage[JMSG_LENGTH_MAX];

	(*cInfo->err->format_message)(cInfo, pszMessage);

	trace("Jpeg Lib error: %s", pszMessage);
}

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage_JPG(CocoAssetFile* file, uint32_t& width, uint32_t& height)
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
	width = cInfo.output_width;
	height = cInfo.output_height;
	rowBytesIn = width * cInfo.output_components;
	rowBytesOut = width * sizeof(uint32_t);

	ArrayBuffer* t = new ArrayBuffer(height * rowBytesOut);

	JSAMPLE* pSample = (JSAMPLE*)malloc(rowBytesIn);

	JSAMPROW pRow[1];
	pRow[0] = pSample;
	unsigned char* ptrRow;

	unsigned char* ptr = (unsigned char*)((*t)[0]);
	for(uint32_t i = height; i--;)
	{
		jpeg_read_scanlines(&cInfo, pRow, 1);
		ptrRow = (unsigned char*)(&(pRow[0][0]));
		for(uint32_t r = width; r--; ptr += 4, ptrRow += 3)
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

#endif /* ENABLE_JPG_SUPPORT */

