//
//  ArrayBufferView.cpp
//  CocoEngine
//
//  Created by Administrator on 12/4/13.
//
//

#include "ArrayBufferView.hpp"

void* ArrayBufferView::get()
{
	return reinterpret_cast<void*>(reinterpret_cast<char*>(buffer->data) + byteOffset);
}