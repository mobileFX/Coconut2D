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

#ifndef DEVICE_WRAPPER_H
#define DEVICE_WRAPPER_H

class fxDeviceWrapper;

#include "Coconut2D.hpp"
#include "HTMLWindow.hpp"
#include "AssetFile.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "WebGLRenderingContext.hpp"
#include "GameEngine.hpp"

class fxDeviceWrapper
{
public:
	fxScreen screen;
	HINSTANCE m_hInstance;
	HWND m_glHWND;
	HDC m_glHDC;
	HGLRC m_OpenGLContext;
	MSG msg;
	bool alive;

	fxDeviceWrapper(int width, int height);
	~fxDeviceWrapper();

	void EventLoop();
	void HandleDeviceEvents();
	void tick();
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif // DEVICE_WRAPPER_H