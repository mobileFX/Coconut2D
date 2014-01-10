#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

#include "Coconut2D.hpp"
#include "DeviceEvent.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoState.hpp"

class CocoEngine
{
public:
	State* __currentState;
	State* __nextState;
	DeviceEvent* __deviceEvent;
	CocoEngine();
	~CocoEngine();
	void __setTouchEvent(DeviceEvent* e);
	void run(WebGLRenderingContext* gl, float time);
	void setNextState(State* s);
};

#endif
