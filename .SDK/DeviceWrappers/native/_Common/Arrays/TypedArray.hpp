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

#ifndef __CocoEngine__TypedArray__
#define __CocoEngine__TypedArray__

#include <vector>
//#include <cassert>
#include "ArrayBufferView.hpp"

template<typename T>
class TypedArray : public ArrayBufferView
{
public:
	const unsigned long BYTES_PER_ELEMENT = sizeof(T);
	unsigned long length;

	TypedArray(size_t size)
	{
		length = size;
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memset(buffer->data, 0, buffer->byteLength);
	}

	TypedArray(ArrayBuffer* i_buffer, size_t i_byteOffset = 0, size_t i_length = -1)
	{
		buffer = i_buffer;
		byteOffset = i_byteOffset;
		length = std::min(size_t((i_buffer->byteLength - i_byteOffset) / sizeof(T)), i_length);
		byteLength = length * sizeof(T);
	}

	TypedArray(Array<T>* val, bool preserve = false)
	{
		length = val->size();
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memcpy(buffer->data, val->data(), buffer->byteLength);
		if(!preserve) delete val;
	}

	~TypedArray() { delete buffer; }

	T* get() { return reinterpret_cast<T*>(ArrayBufferView::get()); }
	T& operator [](unsigned long index)
	{
		assert(index < length);
		return get()[index];
	}
};

#endif /* defined(__CocoEngine__TypedArray__) */
