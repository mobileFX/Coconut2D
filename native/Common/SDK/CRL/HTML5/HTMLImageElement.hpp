//
//  HTMLImageElement.hpp
//  CocoEngine
//
//  Created by Administrator on 12/6/13.
//
//

#ifndef __CocoEngine__HTMLImageElement__
#define __CocoEngine__HTMLImageElement__

#include <string>
#include "ArrayBuffer.hpp"

//class HTMLImageElement;
//typedef HTMLImageElement Image;

class ImageData
{
public:
	ImageData(std::string str);
	~ImageData();
	ArrayBuffer* buffer;
	int width;
	int height;
};

class Image
{
public:
	Image() {}
	~Image();
	void load(std::string str);
	ImageData* data;
	std::string src;
	int width;
	int height;
	int naturalWidth;
	int naturalHeight;
};

#endif /* defined(__CocoEngine__HTMLImageElement__) */
