//
//  TypedArray.hpp
//  CocoEngine
//
//  Created by Administrator on 12/4/13.
//
//

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

	TypedArray(Array<T>* val)
	{
		length = val->size();
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memcpy(buffer->data, val->data(), buffer->byteLength);
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
