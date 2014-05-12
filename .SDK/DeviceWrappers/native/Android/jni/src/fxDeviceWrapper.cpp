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

#include "fxDeviceWrapper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
fxDeviceWrapper::fxDeviceWrapper(android_app* i_app) : app(i_app), jenv(nullptr), glwrap(nullptr), video(false)
{
	app->userData = this;
	app->onAppCmd = StateHandler;
	app->onInputEvent = InputHandler;

    JavaVMAttachArgs jvmArgs;
    jvmArgs.version = JNI_VERSION_1_6;
    jvmArgs.name = "NativeThread";
    jvmArgs.group = NULL;

	app->activity->vm->GetEnv((void**)&jenv, JNI_VERSION_1_6);
	if(app->activity->vm->AttachCurrentThread(&jenv, &jvmArgs) == JNI_ERR)
	{
		trace("ERROR(fxDeviceWrapper.cpp): Could not AttachCurrentThread to JavaVM");
	}
	else
	{
		jclass jcls = jenv->GetObjectClass(app->activity->clazz);
		jmID_KeyboardShow = jenv->GetMethodID(jcls, "KeyboardShow", "()V");
		jmID_KeyboardHide = jenv->GetMethodID(jcls, "KeyboardHide", "()V");
		jmID_KeyboardToggle = jenv->GetMethodID(jcls, "KeyboardToggle", "()V");
		jmID_PlayVideo = jenv->GetMethodID(jcls, "PlayVideo", "()V");
		jmID_GetScreenRotation = jenv->GetMethodID(jcls, "GetScreenRotation", "()I");
		jmID_GetScreenIsPortrait = jenv->GetMethodID(jcls, "GetScreenIsPortrait", "()Z");
		jmID_GetScreenTop = jenv->GetMethodID(jcls, "GetScreenTop", "()I");
	}
	EventLoop();
}

fxDeviceWrapper::~fxDeviceWrapper()
{
	app->activity->vm->DetachCurrentThread();
}

void fxDeviceWrapper::EventLoop()
{
	android_poll_source* source;
	int ident, event, fd;

	do
	{
		while((ident = ALooper_pollAll(2, &fd, &event, (void**)&source)) >= 0)
		{
			if(source)
				source->process(app, source);

			/*if(ident == LOOPER_ID_MAIN)
			{
				int8_t cmd = android_app_read_cmd(app);
				android_app_pre_exec_cmd(app, cmd);
				android_app_post_exec_cmd(app, cmd);
			}*/
		}
		tick();
	}
	while(!app->destroyRequested);
}

void fxDeviceWrapper::StateHandler(android_app* app, int32_t state)
{
	fxDeviceWrapper* t = (fxDeviceWrapper*)app->userData;
	switch(state)
	{
		case APP_CMD_INIT_WINDOW:
		{
			t->glwrap = new fxGLWrap(app->window, t);
			window = new HTMLWindow();
			window->innerWidth = t->glwrap->GetScreen().width;
			window->innerHeight = t->glwrap->GetScreen().height;
			window->devicePixelRatio = t->glwrap->GetScreen().pixelRatio;

			window->deviceRotation = 0.0f;
			document = new HTMLDocument();
			HTMLCanvasElement* canvas = document->createElement("canvas");
			gl = (WebGLRenderingContext*)canvas->getContext("webgl");
			gl->canvas->width = window->innerWidth;
			gl->canvas->height = window->innerHeight;
			engine = new GameEngine();
			break;
		}
		case APP_CMD_WINDOW_REDRAW_NEEDED:
			break;
		case APP_CMD_TERM_WINDOW:
			delete t->glwrap;
			t->glwrap = nullptr;
			break;
		case APP_CMD_GAINED_FOCUS:
			break;
		case APP_CMD_LOST_FOCUS:
			break;
		case APP_CMD_STOP:
			ANativeActivity_finish(app->activity);
			break;
		default:
			break;
	}
}

int32_t fxDeviceWrapper::InputHandler(android_app* app, AInputEvent* event)
{
	fxDeviceWrapper* t = (fxDeviceWrapper*)app->userData;
	int32_t type = AInputEvent_getType(event);
	switch(type)
	{
		case AINPUT_EVENT_TYPE_MOTION:
		{
			int32_t action = AMotionEvent_getAction(event);
			switch(action & AMOTION_EVENT_ACTION_MASK)
			{
				case AMOTION_EVENT_ACTION_DOWN:
				case AMOTION_EVENT_ACTION_POINTER_DOWN:
					window->handleEvent(0, fxEvent::TOUCHSTART, event);
					break;

				case AMOTION_EVENT_ACTION_MOVE:
					window->handleEvent(0, fxEvent::TOUCHMOVE, event);
					break;

				case AMOTION_EVENT_ACTION_UP:
				case AMOTION_EVENT_ACTION_POINTER_UP:
					window->handleEvent(0, fxEvent::TOUCHEND, event);
					break;

				case AMOTION_EVENT_ACTION_CANCEL:
					window->handleEvent(0, fxEvent::TOUCHCANCEL, event);
					break;
				default:
					break;
			}
			break;
		}
		case AINPUT_EVENT_TYPE_KEY:
		{
			uint16_t key_val = AKeyEvent_getKeyCode(event);
			break;
		}
		default:
			break;
	}
	return 0;
}

void fxDeviceWrapper::tick()
{
	if(video)
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glwrap->SwapBuffers();
		return;
	}
	static size_t count = 0;
	static double total = 0.0;
	static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    static std::chrono::steady_clock::time_point now, last_tick = std::chrono::steady_clock::now(), last_draw = std::chrono::steady_clock::now();
    static std::chrono::duration<double, std::milli> tick_dif = std::chrono::duration<double, std::milli>::zero();
    static std::chrono::duration<double, std::milli> draw_dif = std::chrono::duration<double, std::milli>::zero();

    // Mark time and calc difference since last call
    now = std::chrono::steady_clock::steady_clock::now();
    draw_dif = now - last_draw;
    tick_dif = now - last_tick;

    // If the time ellapsed is grater than 16ms we flush OpenGL trying to achieve 60 fps.
    if((draw_dif + tick_dif).count() > 16.0)
    {
        last_draw = now;
        if(glwrap)
        {
        	double td = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(now - start).count();
        	#ifdef __XMLHTTPREQUEST_HPP__
        	XMLHttpRequest::tick();
        	#endif
        	engine->run(gl, td);
        	glwrap->SwapBuffers();
        	if(count++ == 30)
        	{
        		count = 1;
        		total = draw_dif.count();
        	} else total += draw_dif.count();
        }

        now = std::chrono::steady_clock::steady_clock::now();
    }
    last_tick = now;
}

void fxDeviceWrapper::KeyboardShow()
{
	jenv->CallVoidMethod(app->activity->clazz, jmID_KeyboardShow);
}

void fxDeviceWrapper::KeyboardHide()
{
	jenv->CallVoidMethod(app->activity->clazz, jmID_KeyboardHide);
}

void fxDeviceWrapper::KeyboardToggle()
{
	jenv->CallVoidMethod(app->activity->clazz, jmID_KeyboardToggle);
}

fxScreen::Rotation fxDeviceWrapper::GetScreenRotation()
{
	return fxScreen::Rotation(jenv->CallIntMethod(app->activity->clazz, jmID_GetScreenRotation));
}

bool fxDeviceWrapper::GetScreenIsPortrait()
{
	return jenv->CallBooleanMethod(app->activity->clazz, jmID_GetScreenIsPortrait);
}

int fxDeviceWrapper::GetScreenTop()
{
	return jenv->CallIntMethod(app->activity->clazz, jmID_GetScreenTop);
}
