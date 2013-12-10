#ifndef __COCOIMAGESIBLING_HPP__
#define __COCOIMAGESIBLING_HPP__

class CocoImageSibling
{
public:
	std::string url;
	float pixelRatio;
	float textureWidth;
	float textureHeight;
	CocoImageSibling(std::string url, float pixelRatio, float textureWidth, float textureHeight);
};

#endif
