#ifndef __HTMLWINDOW_HPP__
#define __HTMLWINDOW_HPP__

#include "Coconut2D.hpp"
#include "HTMLDocument.hpp"
#include "DeviceEvent.hpp"

extern class HTMLWindow
{
public:
	int __uid;
	HTMLDocument* document;
	int innerHeight;
	int innerWidth;
	float devicePixelRatio;
	float deviceRotation;
	DeviceEvent* __deviceEvent;
	Array<Function*> __elements;
	HTMLWindow();
	~HTMLWindow();
	void addEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void removeEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void dispatchEvent(int uid, String eventType);
}* window;

#endif
