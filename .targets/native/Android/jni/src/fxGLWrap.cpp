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

#include "fxGLWrap.h"
#include "fxDeviceWrapper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
fxGLWrap::fxGLWrap(ANativeWindow* window, fxDeviceWrapper* dev)
{
	EGLint numConfigs, format;
	EGLConfig config;

	const EGLint attribs[] = {
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_ALPHA_SIZE, 0,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_NONE
	};

	const EGLint contextAttribs[] = {
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
	};

	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(window, 0, 0, format);

	surface = eglCreateWindowSurface(display, config, window, nullptr);

	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

	SetContext();

	GLint w, h;
	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	screen.width = w;
	screen.height = h;
	screen.pixelRatio = 1.0;
	screen.rotation = dev->GetScreenRotation();
	screen.isPortrait = dev->GetScreenIsPortrait();
	screen.top = dev->GetScreenTop();

    glViewport(0, 0, screen.width * screen.pixelRatio, screen.height * screen.pixelRatio);
}

fxGLWrap::~fxGLWrap()
{
    if(display != EGL_NO_DISPLAY)
    {
    	ClearContext();
    	if(context != EGL_NO_CONTEXT)
    		eglDestroyContext(display, context);
    	if(surface != EGL_NO_SURFACE)
    		eglDestroySurface(display, surface);
    	eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
}

void fxGLWrap::SetContext()
{
	if(eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		trace("ERROR(fxGLWrap.cpp): eglMakeCurrent(%d)", eglGetError());
	}
}

void fxGLWrap::ClearContext()
{
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
}

void fxGLWrap::SetBuffers()
{
}

void fxGLWrap::SwapBuffers()
{
	eglSwapBuffers(display, surface);
}
