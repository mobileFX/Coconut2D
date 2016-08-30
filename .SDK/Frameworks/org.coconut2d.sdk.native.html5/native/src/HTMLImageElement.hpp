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
//	    ____
//	   /  _/___ ___  ____ _____ ____
//	   / // __ `__ \/ __ `/ __ `/ _ \
//	 _/ // / / / / / /_/ / /_/ /  __/
//	/___/_/ /_/ /_/\__,_/\__, /\___/
//	                    /____/
// ==================================================================================================================================

#ifndef __HTMLImageElement_H__
#define __HTMLImageElement_H__

#include "Coconut2D.hpp"
#include "HTMLElement.hpp"
#include "HTMLImageData.hpp"

class Image	: public HTMLElement
{
public:

	String src;
	bool complete;
	uint8_t* pixels;
	cairo_surface_t* _surface;
	String fileName;
	uint32_t width;
	uint32_t height;
	uint32_t naturalWidth;
	uint32_t naturalHeight;
	bool __BGRA;

	Image();
	Image(uint32_t width, uint32_t height);
	~Image();
	void clearData();
	uint8_t *data();
	int stride();
	size_t bytesLen();
	bool loadFromFile(String fileName);
	bool loadFromBuffer(uint8_t* buf, size_t len);
	bool loadFromImageData(ImageData* im);
	bool load(String src, CocoImage* img = 0);
};

#endif
