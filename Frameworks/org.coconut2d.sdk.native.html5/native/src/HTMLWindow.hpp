/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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

// ==================================================================================================================================
//	    __  __________  _____ _       ___           __
//	   / / / /_  __/  |/  / /| |     / (_)___  ____/ /___ _      __
//	  / /_/ / / / / /|_/ / / | | /| / / / __ \/ __  / __ \ | /| / /
//	 / __  / / / / /  / / /__| |/ |/ / / / / / /_/ / /_/ / |/ |/ /
//	/_/ /_/ /_/ /_/  /_/_____/__/|__/_/_/ /_/\__,_/\____/|__/|__/
//
// ==================================================================================================================================

#ifndef __HTMLWINDOW_HPP__
#define __HTMLWINDOW_HPP__

#include "HTMLDocument.hpp"
#include "HTMLWindowHelpers.hpp"

#include "engine/DeviceMessage.hpp"
#include "engine/CocoEngine.hpp"

class HTMLWindow
{
public:
	uint32_t __uid;
	const bool __native = true;
	const bool __Coconut2DPlayer = false;
	bool __touchEvents;
	bool __webAudio;
	String opera;
	HTMLWindow* parent;
	HTMLWindow* top;
	HTMLDocument* document;
	HTMLLocation* location;
	HTMLNavigator* navigator;
	HTMLScreen* screen;
	int32_t innerHeight;
	int32_t innerWidth;
	float devicePixelRatio;
	float deviceRotation;
	float deviceZoom;
	fxScreen::Rotation screenRotation;
	int32_t orientation;
	HTMLEvent* e;
	CocoEventAction touchstart;
	CocoEventAction	touchmove;
	CocoEventAction touchend;
	HTMLWindow();
	~HTMLWindow();
	void setScreen(fxScreen screen);
	void addEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void removeEventListener(String eventType, CocoEventAction listener, bool useCapture = false);
	void dispatchEvent(int uid, String eventType);
	void handleEvent(fxObjectUID uid, fxEvent type, void* data = nullptr);
	void open(String url, String name, String params);
	void postMessage(void* transfer, String domain);
};

#endif
