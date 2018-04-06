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
//	    __  __________  _____    ______                            ________                          __
//	   / / / /_  __/  |/  / /   / ____/___ _____ _   ______ ______/ ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /   / __ `/ __ \ | / / __ `/ ___/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ /___/ /_/ / / / / |/ / /_/ (__  ) /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/\____/\__,_/_/ /_/|___/\__,_/____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

#include "HTMLCanvasElement.hpp"

#include "CanvasRenderingContext2D.hpp"
#include "WebGLRenderingContext.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLImageData.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasElement::HTMLCanvasElement()
{
	__className = String("HTMLCanvasElement");
	width = 0;
	height = 0;
	gl = nullptr;
	c2d = nullptr;
	_surface = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasElement::~HTMLCanvasElement()
{
	COCO_DELETE_OBJECT(c2d);
	COCO_DELETE_OBJECT(gl);

	if (_surface)
	{
		cairo_surface_destroy(_surface);
		_surface = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLCanvasElement::__resurface()
{
	if (_surface)
	{
		if (cairo_image_surface_get_width(_surface) == width && cairo_image_surface_get_height(_surface) == height) return;

		// Destroy Cairo context
		if (c2d)
			cairo_destroy(c2d->cairo_ctx);

		// Destroy Cairo surface
		cairo_surface_destroy(_surface);
	}

	// Create new Cairo surface
	_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

	// Create new Cairo context
	if (c2d && _surface)
	{
		c2d->cairo_ctx = cairo_create(_surface);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void* HTMLCanvasElement::getContext(const String& ctx_type, ContextArguments* args)
{
	if (ctx_type == "2d")
	{
		if (!c2d)
		{
			__resurface();

			c2d = new CanvasRenderingContext2D(this);
			c2d->__setFilter("best");
			c2d->__setPatternQuality("best");
			c2d->__setTextDrawingMode("glyph");
			c2d->__setAntiAlias("subpixel");
		}
		return (c2d);
	}
	else
	{
		if (!gl)
		{
			gl = new WebGLRenderingContext(this);
		}
		return (gl);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
ImageData* HTMLCanvasElement::toImageData()
{
	if (!_surface) return nullptr;
	cairo_surface_flush(_surface);
	return new ImageData(cairo_image_surface_get_data(_surface), width, height, false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t* HTMLCanvasElement::data()
{
	if (!_surface) return nullptr;
	cairo_surface_flush(_surface);
	return cairo_image_surface_get_data(_surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int HTMLCanvasElement::stride()
{
	if (!_surface) return 0;
	return cairo_image_surface_get_stride(_surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
size_t HTMLCanvasElement::bytesLen()
{
	return height * stride();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<uint8_t>* HTMLCanvasElement::toPNG24()
{
	if (!_surface) return nullptr;
	return pixels_to_png(data(), width, height);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
String HTMLCanvasElement::toDataURL(String mime)
{
	String data = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAALUlEQVRYR+3QQREAAAABQfqXFsNnFTizzXk99+MAAQIECBAgQIAAAQIECBAgMBo/ACHo7lH9AAAAAElFTkSuQmCC";
	if (c2d)
	{
		std::vector<uint8_t>* png = toPNG24();
		if (png)
		{
			data = "data:image/png;base64," + toBase64(png->data(), png->size());
			delete png;
		}
	}
	return data;
}

