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

#include "DeviceEvent.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceEvent::DeviceEvent()
{
	type = "";
	target = nullptr;
	currentTarget = nullptr;
	eventPhase = CAPTURING_PHASE;
	bubbles = true;
	cancelable = true;
	timeStamp = 0;
	defaultPrevented = false;
	scale = 0.0;
	rotation = 0.0;
	__clientX = 0;
	__clientY = 0;
	touches = new TouchList();
	targetTouches = new TouchList();
	changedTouches = new TouchList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
DeviceEvent::~DeviceEvent()
{
	if(touches)
	{
		touches = (delete touches, nullptr);
	}
	if(targetTouches)
	{
		targetTouches = (delete targetTouches, nullptr);
	}
	if(changedTouches)
	{
		changedTouches = (delete changedTouches, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceEvent::stopPropagation()
{
	bubbles = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceEvent::preventDefault()
{
	defaultPrevented = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceEvent::initEvent(String type, bool canBubble, bool cancelable)
{
	eventPhase = CAPTURING_PHASE;
	this->type = type;
	this->bubbles = canBubble;
	this->cancelable = cancelable;
	//this->timeStamp = std::chrono::steady_clock::now().time_since_epoch().count();// (new Date()).getTime();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceEvent::initUIEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail)
{
	this->initEvent(type, canBubble, cancelable);
	this->view = view;
	this->detail = detail;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void DeviceEvent::initTouchEvent(String type, bool canBubble, bool cancelable, HTMLWindow* view, int detail, int screenX, int screenY, int clientX, int clientY, bool ctrlKey, bool altKey, bool shiftKey, bool metaKey, TouchList* touches, TouchList* targetTouches, TouchList* changedTouches, float scale, float rotation)
{
	this->initUIEvent(type, canBubble, cancelable, view, detail);
	this->scale = scale;
	this->rotation = rotation;
	this->touches = touches;
	this->targetTouches = targetTouches;
	this->changedTouches = changedTouches;
}
