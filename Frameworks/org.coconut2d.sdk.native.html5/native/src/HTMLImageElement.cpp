/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (C) 2013-2017 www.mobilefx.com
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
//	    ____
//	   /  _/___ ___  ____ _____ ____
//	   / // __ `__ \/ __ `/ __ `/ _ \
//	 _/ // / / / / / /_/ / /_/ /  __/
//	/___/_/ /_/ /_/\__,_/\__, /\___/
//	                    /____/
// ==================================================================================================================================

#include "HTMLImageElement.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
Image::Image(uint32_t width, uint32_t height)
{
	__BGRA = false;
	pixels = nullptr;
	_surface = nullptr;
	fileName = "";
	this->naturalWidth = this->naturalHeight = this->width = this->height = 0;

	_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	complete = (cairo_surface_status(_surface) == CAIRO_STATUS_SUCCESS);
	{
		this->naturalWidth = this->width = cairo_image_surface_get_width(_surface);
		this->naturalHeight = this->height = cairo_image_surface_get_height(_surface);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Image::Image()
{
	__BGRA = false;
	pixels = nullptr;
	_surface = nullptr;
	fileName = "";
	naturalWidth = naturalHeight = width = height = 0;
	complete = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Image::~Image()
{
	clearData();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Image::clearData()
{
	if (_surface)
	{
		cairo_surface_destroy(_surface);
		_surface = NULL;
	}

	if (pixels)
	{
		delete pixels;
		pixels = nullptr;
	}

	fileName = "";
	width = height = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t * Image::data()
{
	if (!_surface) return pixels;
	cairo_surface_flush(_surface);
	return pixels ? pixels : cairo_image_surface_get_data(_surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int Image::stride()
{
	if (!_surface) return 0;
	return cairo_image_surface_get_stride(_surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
size_t Image::bytesLen()
{
	if (!_surface) return 0;
	return height * cairo_image_surface_get_stride(_surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::loadFromFile(String fileName)
{
	complete = false;
	std::vector<uint8_t>* bytes;

	static String b64("data:image/png;base64,");
	if (fileName.size() > b64.size() && String(fileName.begin(), fileName.begin() + b64.size()) == b64)
	{
		// Read image from Base64 encoded URL
		bytes = fromBase64(fileName.c_str() + b64.size());
		complete = loadFromBuffer(bytes->data(), bytes->size());
		delete bytes;
		__BGRA = false;
	}
	else
	{
		CocoAssetFile* file = CocoAssetFile::open(fileName);
		if (file)
		{
			complete = loadFromBuffer(file->getData(), file->bytesLength());
			delete file;
		}
	}

	if (complete)
		src = fileName;

	return complete;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::loadFromBuffer(uint8_t* buf, size_t len)
{
	clearData();
	size_t pixelsByteLen = 0;

	if (isPNG(buf))
	{
		pixels = pixels_from_png(buf, len, pixelsByteLen, width, height);
		__BGRA = true;
	}

	else if (isJPEG(buf))
	{
		pixels = pixels_from_jpeg(buf, len, pixelsByteLen, width, height);
		__BGRA = false;
	}

	if (pixels && pixelsByteLen)
	{
		_surface = cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, width, height, 4 * width);
		cairo_surface_flush(_surface);
	}

	cairo_status_t status = cairo_surface_status(_surface);
	if (status == CAIRO_STATUS_SUCCESS)
	{
		naturalWidth = width = cairo_image_surface_get_width(_surface);
		naturalHeight = height = cairo_image_surface_get_height(_surface);
	}

	return (status == CAIRO_STATUS_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::loadFromImageData(ImageData* im)
{
	complete = false;
	_surface = cairo_image_surface_create_for_data(im->data, CAIRO_FORMAT_ARGB32, im->width, im->height, 4 * im->width);
	cairo_surface_flush(_surface);
	complete = (cairo_surface_status(_surface) == CAIRO_STATUS_SUCCESS);
	if (complete)
	{
		naturalWidth = width = cairo_image_surface_get_width(_surface);
		naturalHeight = height = cairo_image_surface_get_height(_surface);
	}
	return complete;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::load(String src, CocoImage* img)
{
	return loadFromFile(src);
}
