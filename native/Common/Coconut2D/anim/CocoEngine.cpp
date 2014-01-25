#include "CocoEngine.hpp"

CocoEngine* engine;

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::CocoEngine()
{
	__currentState = nullptr;
	__deviceEvent = nullptr;
	__clock = 0;
	window->addEventListener("touchstart", &CocoEngine::__setTouchEvent);
	window->addEventListener("touchmove", &CocoEngine::__setTouchEvent);
	window->addEventListener("touchend", &CocoEngine::__setTouchEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEngine::~CocoEngine()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::setNextState(State* s)
{
	__nextState = s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::run(WebGLRenderingContext* gl, Time time)
{
	if(!__currentState && !__nextState)
	{
		return;
	}
	if(__nextState != nullptr)
	{
		if(__currentState)
		{
			__currentState->exit();
		}
		__currentState = __nextState;
		__nextState = nullptr;
		trace("\n@@STATE " + __currentState->__name);
		if(__currentState)
		{
			__currentState->enter();
		}
	}
	if(__currentState)
	{
		__currentState->tick(__clock);
	}
	if(__nextState == nullptr && __currentState != nullptr)
	{
		gl->clearColor(0, 0, 0, 1);
		gl->clear(gl->COLOR_BUFFER_BIT);
		__currentState->paint(gl, __clock);
	}
	__deviceEvent = nullptr;
	__clock += TICK_TIME;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__setTouchEvent(DeviceEvent* e)
{
	__deviceEvent = e;
	__deviceEvent->__clientX = (*e->touches)[0]->clientX;
	__deviceEvent->__clientY = (*e->touches)[0]->clientY;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceEvent* CocoEngine::getTouchEvent()
{
	return __deviceEvent;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::pushTouched(CocoClip* clip)
{
	trace("click: " + clip->__instanceName);
	__clicked.push(clip);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoEngine::isClicked(Array<CocoClip*> check)
{
	for(int i = __clicked.size() - 1; i >= 0; i--)
		for(int r = check.size() - 1; r >= 0; r--)
			if(check[r] == __clicked[i])
			{
				return r;
			}
	return  -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEngine::__trace(CocoScene* scene, CocoClip* clip, String message)
{
	return;
	/*if(scene && clip)
	{
		Time ct = scene->__root->__children[0]->__currentTime;
		Time t = (float)(1000) / (float)(scene->__fps);
		float rf = std::floor((float)(ct) / (float)(t));
		float rc = std::floor((float)(ct) / (float)(t));
		message = "\n" + message + ": state=" + __currentState->__name + ", clip=" + scene->__sceneName + clip->__clipPath + ", root_frame=" + String(rf) + ", clip_frame=" + String(rc) + ", root_time=" + scene->__root->__currentTime->toFixed(2) + ", clip_time=" + clip->__currentTime->toFixed(2);
	}
	trace(message);*/
}
