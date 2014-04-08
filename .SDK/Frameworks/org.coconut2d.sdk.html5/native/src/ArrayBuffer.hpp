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
#include "AssetFile.h"

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

	#ifdef ENABLE_PNG_SUPPORT
	static ArrayBuffer* NewFromImage_PNG(AssetFile* file, uint32_t& width, uint32_t& height);
	#endif

	#ifdef ENABLE_JPG_SUPPORT
	static ArrayBuffer* NewFromImage_JPG(AssetFile* file, uint32_t& width, uint32_t& height);
	#endif
};

#endif /* defined(__CocoEngine__ArrayBuffer__) */
