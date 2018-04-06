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

#ifndef __HTMLCanvasElement_H__
#define __HTMLCanvasElement_H__

#include "Coconut2D.hpp"

#include "HTMLElement.hpp"
#include "HTMLImageData.hpp"

class CanvasRenderingContext2D;
class WebGLRenderingContext;

class HTMLCanvasElement : public HTMLElement
{
public:

	int32_t width;
	int32_t height;
	cairo_surface_t* _surface;
	CanvasRenderingContext2D* c2d;
	WebGLRenderingContext* gl;

	HTMLCanvasElement();
	virtual ~HTMLCanvasElement();

	void* getContext(const String& ctx, ContextArguments* args = 0);
	String toDataURL(String mime);

	void fullScreen() {};

	void __resurface();
	ImageData* toImageData();
	uint8_t* data();
	int stride();
	size_t bytesLen();
	std::vector<uint8_t>* toPNG24();

};

#endif // __HTML_CANVAS_H__


