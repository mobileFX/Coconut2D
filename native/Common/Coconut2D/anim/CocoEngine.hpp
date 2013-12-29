#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

#include "Coconut2D.hpp"
#include "TouchEvent.hpp"
#include "CocoEngineState.hpp"
#include "WebGLRenderingContext.hpp"

class CocoEngine
{
public:
	CocoEngineState* __currentState;
	CocoEngineState* __nextState;
	float __stateStart;
	TouchEvent* __touchEvent;
	CocoEngine();
	void __setTouchEvent(TouchEvent* e);
	CocoEngineState* currentState();
	void setState(CocoEngineState* state);
	void tick(WebGLRenderingContext* gl, float time);
};

#endif
