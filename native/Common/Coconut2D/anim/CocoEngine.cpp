#include "CocoEngine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::CocoEngine()
{
	__stateStart = 0.0;
	__deviceEvent = NULL;
	window->addEventListener("touchstart", __setTouchEvent);
	window->addEventListener("touchmove", __setTouchEvent);
	window->addEventListener("touchend", __setTouchEvent);
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
	gl->clearColor(0, 0, 0, 1);
	gl->clear(gl->COLOR_BUFFER_BIT);
	if(!__currentState && !__nextState)
	{
		__nextState = STATE_NULL;
	}
	if(__nextState != NULL)
	{
		if(__currentState)
		{
			__currentState->exit();
		}
		__currentState = __nextState;
		__currentState->enter();
		__stateStart = time;
		__nextState = NULL;
		return;
	}
	__currentState->tick(time - __stateStart);
	if(__nextState == NULL)
	{
		__currentState->paint(gl, time - __stateStart);
	}
	__deviceEvent = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::setNextState(State* s)
{
	__nextState = s;
}
