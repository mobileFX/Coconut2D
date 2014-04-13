#ifndef __COCOIMAGESIBLING_HPP__
#define __COCOIMAGESIBLING_HPP__

#include "Coconut2D.hpp"

class CocoImageSibling
{
public:
	String url;
	float pixelRatio;
	float textureWidth;
	float textureHeight;
	CocoImageSibling(String url, float pixelRatio, float textureWidth, float textureHeight);
};

#endif
