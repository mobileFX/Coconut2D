/* Generated by Coconut2D C++ Compiler from file CocoEngine.jspp */

#ifndef __COCOENGINE_HPP__
#define __COCOENGINE_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"
#include "ITickable.hpp"
#include "ICocoRenderContext.hpp"
#include "CocoClip.hpp"
#include "DeviceMessage.hpp"
#include "CocoScene.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CocoEngine
{
public:
	const float TICK_TIME = ((float)(1000.0) / (float)(60.0));
	bool debugbreak;
	State* __currentState;
	State* __nextState;
	Array<ITickable*>* __tickables;
	float __clock;
	ICocoRenderContext* __ctx;
	Array<DEVICE_MESSAGE*>* __deviceMessageQueue;
	Array<CocoClip*>* __clicked;
	int __device_message_index;
	bool __track_mouse;
	const String __className = String("CocoEngine");
	CocoEngine();
	virtual ~CocoEngine();
	void addTickListener(ITickable* tickable);
	int getTickableIndex(ITickable* tickable);
	void removeTickListener(ITickable* tickable);
	void setNextState(State* s);
	void run(float time);
	void __debug_trace(CocoScene* scene, CocoClip* clip, String message);
	void __attachDevice();
	void __translateDeviceMessage(HTMLEvent* e);
	DEVICE_MESSAGE* __peekDeviceMessage(DEVICE_MESSAGE_ENUM mask, bool first);
	void __clearDeviceMessageQueue();
	void __pushTouched(CocoClip* clip);
	int isClicked(Array<CocoClip*>* check);
};

#endif // __COCOENGINE_HPP__
