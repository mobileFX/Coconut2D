//
//  HTMLCanvasElement.hpp
//  CocoEngine
//
//  Created by Administrator on 12/6/13.
//
//

#ifndef __CocoEngine__HTMLCanvasElement__
#define __CocoEngine__HTMLCanvasElement__

#include "Coconut2D.hpp"
#include "CanvasRenderingContext2D.hpp"
#include "WebGLRenderingContext.hpp"

class HTMLCanvasGradient {};
class HTMLCanvasPattern {};
class HTMLTextMetrics {};

class HTMLCanvasElement
{
public:
	unsigned long width;
	unsigned long height;

	HTMLCanvasElement();
	HTMLCanvasContext* getContext(String contextId);
	String toDataURL();
};

#endif /* defined(__CocoEngine__HTMLCanvasElement__) */
