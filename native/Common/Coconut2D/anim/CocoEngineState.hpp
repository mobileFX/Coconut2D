#ifndef __COCOENGINESTATE_HPP__
#define __COCOENGINESTATE_HPP__

#include "Coconut2D.hpp"
#include "CocoEngine.hpp"
#include "WebGLRenderingContext.hpp"

class CocoEngineState
{
public:
	CocoEngineState();
	virtual void tick(CocoEngine* engine, WebGLRenderingContext* gl, float time);
};

#endif
