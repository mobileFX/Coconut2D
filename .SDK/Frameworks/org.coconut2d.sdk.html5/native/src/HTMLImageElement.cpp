//
//  HTMLImageElement.cpp
//  CocoEngine
//
//  Created by Administrator on 12/6/13.
//
//

#include "HTMLImageElement.hpp"

ImageData::ImageData(std::string str)
{
	uint32_t w, h;
	buffer = ArrayBuffer::NewFromImage(str, w, h);
	assert(buffer);
	width = w;
	height = h;
	src = str;
}

ImageData::~ImageData()
{
	delete buffer;
	trace("Image buffer deleted: %s", src.c_str());
}

void Image::load(std::string str)
{
	data = new ImageData(str);
	width = data->width;
	height = data->height;
	naturalWidth = data->width;
	naturalHeight = data->height;
	src=str;
}

Image::~Image()
{
	delete data;
}