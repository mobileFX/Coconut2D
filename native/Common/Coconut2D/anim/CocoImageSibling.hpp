#ifndef __COCOIMAGESIBLING_HPP__
#define __COCOIMAGESIBLING_HPP__

#include "Coconut2D.hpp"

class CocoImageSibling
{
public:
	std::string url;
	float pixelRatio;
	float textureWidth;
	float textureHeight;
	virtual CocoImageSibling(std::string url, float pixelRatio, float textureWidth, float textureHeight);
};

#endif
