#ifndef __HTMLCANVASELEMENT_HPP__
#define __HTMLCANVASELEMENT_HPP__

#include "Coconut2D.hpp"

class HTMLCanvasElement
{
public:
	float width;
	float height;
	ImageData* __imageData;
	HTMLCanvasElement();
	~HTMLCanvasElement();
	HTMLCanvasContext* getContext(String contextId);
	String toDataURL();
};

#endif
