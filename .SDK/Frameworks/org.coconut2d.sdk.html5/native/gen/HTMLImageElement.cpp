/* Generated by Coconut2D C++ Compiler from file HTMLImageElement.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "HTMLImageElement.hpp"
#include "ImageData.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Image::Image()
{
	__imageData = nullptr;
	src = String("");
	width = 0;
	height = 0;
	naturalWidth = 0;
	naturalHeight = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Image::~Image()
{
	if(__imageData)
	{
		__imageData = (delete __imageData, nullptr);
	}
	trace((String("Image buffer deleted: ") + src).c_str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Image::load(String url)
{
	__imageData = new ImageData(url);
	src = __imageData->src;
	width = __imageData->width;
	height = __imageData->height;
	naturalWidth = __imageData->width;
	naturalHeight = __imageData->height;
	__complete = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Image::__get_complete()
{
	return __complete;
}
