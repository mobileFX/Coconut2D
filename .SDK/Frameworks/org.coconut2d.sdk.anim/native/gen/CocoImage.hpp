#ifndef __COCOIMAGE_HPP__
#define __COCOIMAGE_HPP__

#include "Coconut2D.hpp"
#include "CocoImageSibling.hpp"
#include "CocoSequence.hpp"
#include "CocoScene.hpp"
#include "WebGLRenderingContext.hpp"
#include "HTMLImageElement.hpp"

class CocoImage
{
public:
	String symbolName;
	Image* image;
	float textureCellWidth;
	float textureCellHeight;
	Float32Array* textureGrid;
	Float32Array* color;
	Float32Array* texSize;
	bool isSpriteSheet;
	float __pixelRatioScale;
	WebGLTexture* texture;
	WebGLBuffer* buffer;
	Array<CocoSequence*>* sequences;
	String baseUrl;
	int viewOptimalWidth;
	int viewOptimalHeight;
	Array<CocoImageSibling*>* viewSiblings;
	float pixelRatio;
	CocoImage();
	~CocoImage();
	CocoImageSibling* addSibling(CocoImageSibling* sibling);
	CocoSequence* addSequence(CocoSequence* sequence);
	CocoSequence* getSequence(String name);
	void prepare(CocoScene* scene, WebGLRenderingContext* gl);
};

#endif
