#include "CocoEngine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::CocoEngine()
{
	__deviceEvent = NULL;
	window->addEventListener("touchstart", (CocoAction)&CocoEngine::__setTouchEvent);
	window->addEventListener("touchmove", (CocoAction)&CocoEngine::__setTouchEvent);
	window->addEventListener("touchend", (CocoAction)&CocoEngine::__setTouchEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::~CocoEngine()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__setTouchEvent(DeviceEvent* e)
{
	__deviceEvent = e;
	__deviceEvent->__clientX = (*e->touches)[0]->clientX;
	__deviceEvent->__clientY = (*e->touches)[0]->clientY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::run(WebGLRenderingContext* gl, float time)
{
	if(!__currentState && !__nextState)
	{
		__nextState = STATE_NULL;
	}
	if(__nextState != NULL)
	{
		if(__currentState && __currentState->exit)
		{
			__currentState->exit();
		}
		__currentState = __nextState;
		__currentState->enter();
		__nextState = NULL;
		trace("@@STATE " + __currentState->__name);
		return;
	}
	__currentState->tick(time);
	if(__nextState == NULL)
	{
		gl->clearColor(0, 0, 0, 1);
		gl->clear(gl->COLOR_BUFFER_BIT);
		__currentState->paint(gl, time);
	}
	__deviceEvent = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::setNextState(State* s)
{
	__nextState = s;
}

//=======================================================
// State: STATE_NULL
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::STATE_NULL::tick()
{
}
