#include "CocoEngine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::CocoEngine()
{
	__currentState = NULL;
	__nextState = NULL;
	__stateStart = 0.0;
	__touchEvent = NULL;
	window->addEventListener("touchstart", __setTouchEvent);
	window->addEventListener("touchmove", __setTouchEvent);
	window->addEventListener("touchend", __setTouchEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__setTouchEvent(TouchEvent* e)
{
	__touchEvent = e;
	__touchEvent->__clientX = (*e->touches)[0]->clientX;
	__touchEvent->__clientY = (*e->touches)[0]->clientY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngineState* CocoEngine::currentState()
{
	return __currentState;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::setState(CocoEngineState* state)
{
	__nextState = state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::tick(WebGLRenderingContext* gl, float time)
{
	if(__nextState != NULL)
	{
		__currentState = __nextState;
		__stateStart = time;
		__nextState = NULL;
	}
	__currentState->tick(this, gl, time - __stateStart);
	__touchEvent = NULL;
}
