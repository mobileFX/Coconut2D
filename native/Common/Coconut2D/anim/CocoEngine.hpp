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
	struct STATE_NULL : State
	{
		CocoEngine* self;
		STATE_NULL(CocoEngine* self) : self(self) {}
		void tick();
	}* STATE_NULL = new struct STATE_NULL(this);
};

#endif
