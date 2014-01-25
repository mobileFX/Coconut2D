//
//  ArrayBuffer.hpp
//  CocoEngine
//
//  Created by Administrator on 12/4/13.
//
//

#ifndef __CocoEngine__ArrayBuffer__
#define __CocoEngine__ArrayBuffer__

#include "Coconut2D.hpp"
#include "fxFile.h"

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
	static ArrayBuffer* NewFromImage_PNG(fxFile* file, uint32_t& width, uint32_t& height);
	static ArrayBuffer* NewFromImage_JPG(fxFile* file, uint32_t& width, uint32_t& height);
};

#endif /* defined(__CocoEngine__ArrayBuffer__) */
