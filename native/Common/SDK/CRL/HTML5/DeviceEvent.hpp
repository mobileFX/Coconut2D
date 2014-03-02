#ifndef __DEVICEEVENT_HPP__
#define __DEVICEEVENT_HPP__

#include "Coconut2D.hpp"
#include "HTMLWindow.hpp"
#include "TouchList.hpp"
#include "EventTarget.hpp"
#include "Touch.hpp"

class DeviceEvent
{
public:
	const int CAPTURING_PHASE = 1;
	const int AT_TARGET = 2;
	const int BUBBLING_PHASE = 3;
	String type;
	EventTarget* target;
	EventTarget* currentTarget;
	int eventPhase;
	bool bubbles;
	bool cancelable;
	int timeStamp;
	bool defaultPrevented;
	HTMLWindow* view;
	int detail;
	TouchList* touches;
	TouchList* targetTouches;
	TouchList* changedTouches;
	float scale;
	float rotation;
	int clientX;
	int clientY;
	int __clientX;
	int __clientY;
	DeviceEvent();
	~DeviceEvent();
	void stopPropagation();
	void preventDefault();
	void initEvent(String type, bool canBubble, bool cancelable);
	void initUIEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail);
	void initTouchEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail, int screenX, int screenY, int clientX, int clientY, bool ctrlKey, bool altKey, bool shiftKey, bool metaKey, TouchList* touches, TouchList* targetTouches, TouchList* changedTouches, float scale, float rotation);
};

#endif
