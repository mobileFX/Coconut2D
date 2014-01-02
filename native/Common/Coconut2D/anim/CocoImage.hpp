#ifndef __COCOIMAGE_HPP__
#define __COCOIMAGE_HPP__

#include "Coconut2D.hpp"
#include "CocoImageSibling.hpp"
#include "CocoSequence.hpp"
#include "WebGLRenderingContext.hpp"
#include "HTMLImageElement.hpp"
#include "WebGLTexture.hpp"
#include "WebGLBuffer.hpp"

class CocoImage
{
public:
	std::string symbolName;
	Image* image;
	WebGLTexture* texture;
	float textureCellWidth;
	float textureCellHeight;
	Float32Array* textureGrid;
	Float32Array* color;
	Float32Array* texSize;
	WebGLBuffer* buffer;
	bool isSpriteSheet;
	Array<CocoSequence*> sequences;
	std::string baseUrl;
	int viewOptimalWidth;
	int viewOptimalHeight;
	Array<CocoImageSibling*> viewSiblings;
	float pixelRatio;
	virtual CocoImage();
	virtual ~CocoImage();
	CocoImageSibling* addSibling(CocoImageSibling* sibling);
	CocoSequence* addSequence(CocoSequence* sequence);
	CocoSequence* getSequence(std::string name);
	void prepare(WebGLRenderingContext* gl);
};

#endif
