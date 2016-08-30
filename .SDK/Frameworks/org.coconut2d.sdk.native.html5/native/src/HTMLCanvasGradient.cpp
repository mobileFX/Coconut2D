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
//	   ______                            ______               ___            __
//	  / ____/___ _____ _   ______ ______/ ____/________ _____/ (_)__  ____  / /_
//	 / /   / __ `/ __ \ | / / __ `/ ___/ / __/ ___/ __ `/ __  / / _ \/ __ \/ __/
//	/ /___/ /_/ / / / / |/ / /_/ (__  ) /_/ / /  / /_/ / /_/ / /  __/ / / / /_
//	\____/\__,_/_/ /_/|___/\__,_/____/\____/_/   \__,_/\__,_/_/\___/_/ /_/\__/
//
// ==================================================================================================================================

#include "HTMLCanvasGradient.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
CanvasGradient::CanvasGradient(double x0, double y0, double r0, double x1, double y1, double r1)
{
	isPattern = false;
	_pattern = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CanvasGradient::CanvasGradient(double x0, double y0, double x1, double y1)
{
	isPattern = false;
	_pattern = cairo_pattern_create_linear(x0, y0, x1, y1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CanvasGradient::CanvasGradient(cairo_surface_t *surface, int w, int h, const String& repetition)
{
	isPattern = true;
	_repetition = repetition; // "repeat",	"repeat-x",	"repeat-y",	"no-repeat"
	_pattern = cairo_pattern_create_for_surface(surface);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
CanvasGradient::~CanvasGradient()
{
	cairo_pattern_destroy(_pattern);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void CanvasGradient::addColorStop(float x, String color)
{
	if (isPattern) return;
	short ok;
	uint32_t rgba = rgba_from_string(color.c_str(), &ok);
	if (ok)
	{
		rgba_t color = rgba_create(rgba);
		cairo_pattern_add_color_stop_rgba(_pattern, x, color.r, color.g, color.b, color.a);
	}
}
