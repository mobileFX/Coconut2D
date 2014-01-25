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
	
	TypedArray<T>(std::vector<T> val)
	{
		length = val.size();
		buffer = new ArrayBuffer(length * BYTES_PER_ELEMENT);
		byteOffset = 0;
		byteLength = buffer->byteLength;
		memcpy(buffer->data, val.data(), buffer->byteLength);
	}
	~TypedArray<T>() { delete buffer; }
	
	T* get() { return reinterpret_cast<T*>(ArrayBufferView::get()); }
	T& operator [](unsigned long index)
	{
		assert(index < length);
		return get()[index];
	}
};

typedef TypedArray<signed char> Int8Array;
typedef TypedArray<unsigned char> Uint8Array;
typedef TypedArray<unsigned char> Uint8ClampedArray;
typedef TypedArray<short> Int16Array;
typedef TypedArray<unsigned short> Uint16Array;
typedef TypedArray<int> Int32Array;
typedef TypedArray<unsigned int> Uint32Array;
typedef TypedArray<float> Float32Array;
typedef TypedArray<double> Float64Array;

#endif /* defined(__CocoEngine__TypedArray__) */
