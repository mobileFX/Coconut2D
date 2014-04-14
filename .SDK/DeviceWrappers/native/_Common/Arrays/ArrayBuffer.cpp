//
//  ArrayBuffer.cpp
//  CocoEngine
//
//  Created by Administrator on 12/4/13.
//
//

#include "ArrayBuffer.hpp"
#include "AssetFile.h"

//////////////////////////////////////////////////////////////////////////////////////////////
ArrayBuffer* ArrayBuffer::NewFromImage(std::string str, uint32_t& width, uint32_t& height)
{
	AssetFile* file = AssetFile::open(str.c_str());
	switch(file->mime)
	{
		#ifdef ENABLE_PNG_SUPPORT
		case AssetFile::MIME::IMAGE_PNG: return NewFromImage_PNG(file, width, height);
		#endif

		#ifdef ENABLE_JPEG_SUPPORT
		case AssetFile::MIME::IMAGE_JPG: return NewFromImage_JPG(file, width, height);
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
// ==================================================================================================================================
//	    ____  _   ________
//	   / __ \/ | / / ____/
//	  / /_/ /  |/ / / __
//	 / ____/ /|  / /_/ /
//	/_/   /_/ |_/\____/
//
// ==================================================================================================================================

static void png_from_memory(png_structp png_ptr, png_bytep readBytes, png_size_t readCount)
{
	AssetFile* file = (AssetFile*)png_get_io_ptr(png_ptr);
	file->read(readBytes, readCount);
}

static void png_to_memory(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ArrayBuffer* buffer = (ArrayBuffer*)png_get_io_ptr(png_ptr);
	buffer->byteLength += length;
	buffer->data = realloc(buffer->data, buffer->byteLength);
	memcpy((*buffer)[buffer->byteLength - length], data, length);
}

ArrayBuffer* ArrayBuffer::NewFromImage_PNG(AssetFile* file, uint32_t& width, uint32_t& height)
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
// ==================================================================================================================================
//	       ______  ____________
//	      / / __ \/ ____/ ____/
//	 __  / / /_/ / __/ / / __
//	/ /_/ / ____/ /___/ /_/ /
//	\____/_/   /_____/\____/
//
// ==================================================================================================================================

static void jpeg_error(j_common_ptr cInfo)
{
	char pszMessage[JMSG_LENGTH_MAX];

	(*cInfo->err->format_message)(cInfo, pszMessage);

	trace("Jpeg Lib error: %s", pszMessage);
}

ArrayBuffer* ArrayBuffer::NewFromImage_JPG(AssetFile* file, uint32_t& width, uint32_t& height)
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