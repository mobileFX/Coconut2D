#ifndef __HTMLWINDOW_HPP__
#define __HTMLWINDOW_HPP__

#include "Coconut2D.hpp"
#include "HTMLDocument.hpp"
#include "DeviceEvent.hpp"
#include "CocoEngine.hpp"

extern class HTMLWindow
{
public:
	int __uid;
	HTMLDocument* document;
	int innerHeight;
	int innerWidth;
	float devicePixelRatio;
	float deviceRotation;
	fxScreen::Rotation screenRotation;
	DeviceEvent* __deviceEvent;
	CocoEventAction touchstart;
	CocoEventAction	touchmove;
	CocoEventAction touchend;
	Array<Function*> __elements;
	HTMLWindow();
	~HTMLWindow();
	void setScreen(fxScreen screen);
	void addEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void removeEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void dispatchEvent(int uid, String eventType);
	void handleEvent(fxObjectUID uid, fxEvent type, void* data = nullptr);
}* window;

#endif
