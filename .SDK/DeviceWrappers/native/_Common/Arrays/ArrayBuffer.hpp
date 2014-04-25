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

#ifndef __CocoEngine__ArrayBuffer__
#define __CocoEngine__ArrayBuffer__

#include "Coconut2D.hpp"

class AssetFile;

class ArrayBuffer
{
public:
	void* data;
	unsigned long byteLength;

	ArrayBuffer(unsigned long length)
	{
		data = malloc(length);
		byteLength = length;
	}
	~ArrayBuffer()
	{
		free(data);
	}
	void* operator[](unsigned long i)
	{
		assert(i < byteLength);
		return reinterpret_cast<void*>(reinterpret_cast<char*>(data) + i);
	}

	static ArrayBuffer* NewFromImage(std::string str, uint32_t& width, uint32_t& height);
	String encodeAsBase64();

	#ifdef ENABLE_PNG_SUPPORT
	static ArrayBuffer* NewFromImage_PNG(AssetFile* file, uint32_t& width, uint32_t& height);
	ArrayBuffer* encodeAsPNG(size_t width, size_t height);
	#endif

	#ifdef ENABLE_JPG_SUPPORT
	static ArrayBuffer* NewFromImage_JPG(AssetFile* file, uint32_t& width, uint32_t& height);
	#endif
};

#endif /* defined(__CocoEngine__ArrayBuffer__) */
