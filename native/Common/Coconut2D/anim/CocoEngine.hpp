#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

#include "Coconut2D.hpp"
//#include "CocoState.hpp"
#include "WebGLRenderingContext.hpp"
#include "DeviceEvent.hpp"
#include "CocoClip.hpp"
#include "CocoScene.hpp"

extern class CocoEngine
{
public:
	const Time TICK_TIME = (1000.0/60.0);
	State* __currentState;
	State* __nextState;
	DeviceEvent* __deviceEvent;
	Array<CocoClip*> __clicked;
	Time __clock;
	CocoEngine();
	virtual ~CocoEngine();
	void setNextState(State* s);
	void run(WebGLRenderingContext* gl, Time time);
	void __setTouchEvent(DeviceEvent* e);
	DeviceEvent* getTouchEvent();
	void pushTouched(CocoClip* clip);
	int isClicked(Array<CocoClip*> check);
	void __trace(CocoScene* scene, CocoClip* clip, String message);
}* engine;

#endif
