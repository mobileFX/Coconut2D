#include "HTMLWindow.hpp"

HTMLWindow* window;

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLWindow::HTMLWindow()
{
	touchstart = nullptr;
	touchmove = nullptr;
	touchend = nullptr;
	__uid = 0;
	document = new HTMLDocument();
	__deviceEvent = new DeviceEvent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLWindow::~HTMLWindow()
{
	if(document)
	{
		document = (delete document, nullptr);
	}
	if(__deviceEvent)
	{
		__deviceEvent = (delete __deviceEvent, nullptr);
	}
}

void HTMLWindow::setScreen(fxScreen screen)
{
	innerWidth = screen.width;
	innerHeight = screen.height;
	devicePixelRatio = screen.pixelRatio;
	screenRotation = screen.rotation;
	switch(screenRotation) {
		case fxScreen::Rotation::NONE: deviceRotation = 0.0f; break;
		case fxScreen::Rotation::RCW: deviceRotation = M_PI_2; break;
		case fxScreen::Rotation::RCCW: deviceRotation = -M_PI_2; break;
		case fxScreen::Rotation::FULL: deviceRotation = M_PI; break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::addEventListener(String eventType, CocoEventAction listener, bool useCapture)
{
	if(eventType == "touchstart")
		touchstart = listener;
	else if(eventType == "touchmove")
		touchmove = listener;
	else if(eventType == "touchend")
		touchend = listener;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::removeEventListener(String eventType, CocoEventAction listener, bool useCapture)
{
	if(eventType == "touchstart")
		touchstart = nullptr;
	else if(eventType == "touchmove")
		touchmove = nullptr;
	else if(eventType == "touchend")
		touchend = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::dispatchEvent(int uid, String eventType)
{
	__deviceEvent->type = eventType;
	if(eventType == "touchstart")
		(engine->*touchstart)(__deviceEvent);
	else if(eventType == "touchmove")
		(engine->*touchmove)(__deviceEvent);
	else if(eventType == "touchend")
		(engine->*touchend)(__deviceEvent);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void HTMLWindow::handleEvent(fxObjectUID uid, fxEvent type, void* data)
{
	String eventType;

	switch(type)
	{
		case fxEvent::LOAD:
		{
			eventType = "load";
			break;
		}

		case fxEvent::FOCUS:
		{
			eventType = "focus";
			break;
		}

		case fxEvent::BLUR:
		{
			//saveStorage();
			eventType = "blur";
			break;
		}

		case fxEvent::UNLOAD:
		{
			//saveStorage();
			eventType = "unload";
			break;
		}

		case fxEvent::RESIZE:
		{
			eventType = "resize";
			break;
		}

		case fxEvent::CLICK:
		{
			eventType = "click";
			int x, y;
			switch(screenRotation)
			{
				case fxScreen::Rotation::NONE: x = fxAPIGetMouseEventX(data); y = fxAPIGetMouseEventY(data); break;
				case fxScreen::Rotation::FULL: x = -fxAPIGetMouseEventX(data); y = -fxAPIGetMouseEventY(data); break;
				case fxScreen::Rotation::RCW: x = -fxAPIGetMouseEventY(data); y = fxAPIGetMouseEventX(data); break;
				case fxScreen::Rotation::RCCW: x = fxAPIGetMouseEventY(data); y = -fxAPIGetMouseEventX(data); break;
			}
			__deviceEvent->__clientX = x;
			__deviceEvent->__clientY = y;
			break;
		}

		case fxEvent::KEYDOWN:
		{
			eventType = "keydown";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::KEYPRESS:
		{
			eventType = "keypress";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::KEYUP:
		{
			eventType = "keyup";
			//fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
			break;
		}

		case fxEvent::TOUCHSTART:
		case fxEvent::TOUCHMOVE:
		case fxEvent::TOUCHEND:
		case fxEvent::TOUCHCANCEL:
		{
			switch(type)
			{
				case fxEvent::TOUCHSTART: eventType = "touchstart"; break;
				case fxEvent::TOUCHMOVE: eventType = "touchmove"; break;
				case fxEvent::TOUCHEND: eventType = "touchend"; break;
				case fxEvent::TOUCHCANCEL: eventType = "touchcancel"; break;
				default: break;
			}
			int x, y;
			__deviceEvent->touches->length = fxAPIGetTouchesLength(data);
			for(size_t i = __deviceEvent->touches->length; i--;)
			{
				switch(screenRotation)
				{
						/*
						 case fxScreen::Rotation::NONE: x = fxAPIGetTouchEventX(data, i); y = fxAPIGetTouchEventY(data, i) - screen->top; break;
						 case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetTouchEventX(data, i); y = innerHeight - fxAPIGetTouchEventY(data, i); break;
						 case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetTouchEventY(data, i); y = fxAPIGetTouchEventX(data, i) - screen->top; break;
						 case fxScreen::Rotation::RCCW: x = fxAPIGetTouchEventY(data, i); y = innerHeight - fxAPIGetTouchEventX(data, i); break;
						 */
					case fxScreen::Rotation::NONE: x = fxAPIGetTouchEventX(data, i); y = fxAPIGetTouchEventY(data, i); break;
					case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetTouchEventX(data, i); y = innerHeight - fxAPIGetTouchEventY(data, i); break;
					case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetTouchEventY(data, i); y = fxAPIGetTouchEventX(data, i); break;
					case fxScreen::Rotation::RCCW: x = fxAPIGetTouchEventY(data, i); y = innerHeight - fxAPIGetTouchEventX(data, i); break;
				}
				__deviceEvent->touches->item(i)->clientX = x;
				__deviceEvent->touches->item(i)->clientY = y;
				__deviceEvent->touches->item(i)->screenX = x;
				__deviceEvent->touches->item(i)->screenY = y;
			}

			__deviceEvent->changedTouches->length = fxAPIGetChangedTouchesLength(data);
			for(size_t i = __deviceEvent->changedTouches->length; i--;)
			{
				switch(screenRotation)
				{
						/*
						 case fxScreen::Rotation::NONE: x = fxAPIGetChangedTouchEventX(data, i); y = fxAPIGetChangedTouchEventY(data, i) - screen->top; break;
						 case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetChangedTouchEventX(data, i); y = innerHeight - fxAPIGetChangedTouchEventY(data, i); break;
						 case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetChangedTouchEventY(data, i); y = fxAPIGetChangedTouchEventX(data, i) - screen->top; break;
						 case fxScreen::Rotation::RCCW: x = fxAPIGetChangedTouchEventY(data, i); y = innerHeight - fxAPIGetChangedTouchEventX(data, i); break;
						 */
					case fxScreen::Rotation::NONE: x = fxAPIGetChangedTouchEventX(data, i); y = fxAPIGetChangedTouchEventY(data, i); break;
					case fxScreen::Rotation::FULL: x = innerWidth - fxAPIGetChangedTouchEventX(data, i); y = innerHeight - fxAPIGetChangedTouchEventY(data, i); break;
					case fxScreen::Rotation::RCW: x = innerWidth - fxAPIGetChangedTouchEventY(data, i); y = fxAPIGetChangedTouchEventX(data, i); break;
					case fxScreen::Rotation::RCCW: x = fxAPIGetChangedTouchEventY(data, i); y = innerHeight - fxAPIGetChangedTouchEventX(data, i); break;
				}
				__deviceEvent->changedTouches->item(i)->clientX = x;
				__deviceEvent->changedTouches->item(i)->clientY = y;
				__deviceEvent->changedTouches->item(i)->screenX = x;
				__deviceEvent->changedTouches->item(i)->screenY = y;
			}
			break;
		}

		default:
			LOGW("Event not implemented!\n");
	}

	dispatchEvent(uid, eventType);
}