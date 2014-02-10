//
//  ArrayBufferView.hpp
//  CocoEngine
//
//  Created by Administrator on 12/4/13.
//
//

#ifndef __CocoEngine__ArrayBufferView__
#define __CocoEngine__ArrayBufferView__

#include "ArrayBuffer.hpp"

class ArrayBufferView
{
public:
	void* get();
	ArrayBuffer* buffer;
	unsigned long byteOffset;
	unsigned long byteLength;
};

#endif /* defined(__CocoEngine__ArrayBufferView__) */
