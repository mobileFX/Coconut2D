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

#ifndef _fxDeviceWrapper_h
#define _fxDeviceWrapper_h

class fxDeviceWrapper;
class fxGLWrap;

#include "Coconut2D.hpp"
#include "HTMLWindow.hpp"
#include "AssetFile.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "fxGLWrap.h"
#include "WebGLRenderingContext.hpp"
#include "GameEngine.hpp"

class fxDeviceWrapper
{
private:
protected:
	android_app* app;
	JNIEnv* jenv;
	fxGLWrap* glwrap;

	// Java Methods
	jmethodID jmID_KeyboardShow;
	jmethodID jmID_KeyboardHide;
	jmethodID jmID_KeyboardToggle;
	jmethodID jmID_PlayVideo;
	jmethodID jmID_GetScreenRotation;
	jmethodID jmID_GetScreenIsPortrait;
	jmethodID jmID_GetScreenTop;

	bool video;

	void EventLoop();
	void tick();
	void updateGL();

	static void StateHandler(android_app*, int32_t);
	static int32_t InputHandler(android_app*, AInputEvent*);
public:
	fxDeviceWrapper(android_app*);
	~fxDeviceWrapper();

	void KeyboardShow();
	void KeyboardHide();
	void KeyboardToggle();
	fxScreen::Rotation GetScreenRotation();
	bool GetScreenIsPortrait();
	int GetScreenTop();
};

#endif
