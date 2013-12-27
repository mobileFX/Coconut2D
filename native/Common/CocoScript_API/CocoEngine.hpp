#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

#include "Coconut2D.hpp"
#include "CocoEngineState.hpp"
#include "WebGLRenderingContext.hpp"

class CocoEngine
{
public:
	CocoEngineState* __currentState;
	CocoEngineState* __nextState;
	float __stateStart;
	CocoEngine();
	CocoEngineState* currentState();
	void setState(CocoEngineState* state);
	void tick(WebGLRenderingContext* gl, float time);
};

#endif
