#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

#include "Coconut2D.hpp"
#include "DeviceEvent.hpp"
#include "CocoClip.hpp"
#include "WebGLRenderingContext.hpp"
#include "Touch.hpp"
#include "HTMLWindow.hpp"

class CocoEngine
{
public:
	const Time TICK_TIME = ((float)(1000.0) / (float)(60.0));
	bool debugbreak;
	State* __currentState;
	State* __nextState;
	DeviceEvent* __deviceEvent;
	Array<CocoClip*> __clicked;
	Time __clock;
	CocoEngine();
	~CocoEngine();
	void setNextState(State* s);
	void run(WebGLRenderingContext* gl, Time time);
	void __setTouchEvent(DeviceEvent* e);
	DeviceEvent* getTouchEvent();
	void pushTouched(CocoClip* clip);
	int isClicked(Array<CocoClip*> check);
	void __trace(CocoScene* scene, CocoClip* clip, String message);
};

#endif
