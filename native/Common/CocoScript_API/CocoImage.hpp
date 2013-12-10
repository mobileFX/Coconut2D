#ifndef __COCOIMAGE_HPP__
#define __COCOIMAGE_HPP__

class CocoImage
{
public:
	std::string symbolName;
	HTMLImageElement* image;
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
	CocoImage();
	void addSibling(CocoImageSibling* sibling);
	CocoSequence* addSequence(CocoSequence* sequence);
	CocoSequence* getSequence(std::string name);
	void prepare(WebGLRenderingContext* gl);
};

#endif
