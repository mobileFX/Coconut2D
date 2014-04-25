/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ***** END LICENSE BLOCK ***** */

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
