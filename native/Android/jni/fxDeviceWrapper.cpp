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
	if(app->activity->vm->AttachCurrentThread(&jenv, &jvmArgs) == JNI_ERR) { LOGW("Could not AttachCurrentThread to JavaVM!\n"); }
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

	//LOGI("Window Init!\n");
	//glwrap = new fxGLWrap(app->window);
	//fxCRL::init(fxArgs::Args->getArgc(), fxArgs::Args->getArgv(), glwrap->GetScreen());
	//fxCRL::handleEvent(0, fxCRL::fxEvent::LOAD, nullptr);

	LOGI("Preloop\n");
	EventLoop();
	LOGI("Done!\n");

	//fxCRL::quit();
	//delete glwrap;
	//glwrap = nullptr;
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
		//LOGI("Loop!\n");
		while((ident = ALooper_pollAll(2, &fd, &event, (void**)&source)) >= 0)
		{
			if(source) source->process(app, source);
			else LOGW("error source\n");
			/*if(ident == LOOPER_ID_MAIN)
			{
				int8_t cmd = android_app_read_cmd(app);
				android_app_pre_exec_cmd(app, cmd);
				android_app_post_exec_cmd(app, cmd);
			}*/
		}
		tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	} while(!app->destroyRequested);
}

void fxDeviceWrapper::StateHandler(android_app* app, int32_t state)
{
	fxDeviceWrapper* t = (fxDeviceWrapper*)app->userData;
	switch(state)
	{
		case APP_CMD_INIT_WINDOW:
			LOGI("Window Init!\n");
			t->glwrap = new fxGLWrap(app->window, t);
			fxCRL::init(fxArgs::Args->getArgc(), fxArgs::Args->getArgv(), t->glwrap->GetScreen(), t);
			fxCRL::handleEvent(0, fxCRL::fxEvent::LOAD, nullptr);
			break;
		case APP_CMD_WINDOW_REDRAW_NEEDED:
			LOGI("Redraw Needed!\n");
			break;
		case APP_CMD_TERM_WINDOW:
			fxCRL::handleEvent(0, fxCRL::fxEvent::UNLOAD);
			fxCRL::quit();
			delete t->glwrap;
			t->glwrap = nullptr;
			break;
		case APP_CMD_GAINED_FOCUS:
			fxCRL::handleEvent(0, fxCRL::fxEvent::FOCUS);
			break;
		case APP_CMD_LOST_FOCUS:
			fxCRL::handleEvent(0, fxCRL::fxEvent::BLUR);
			break;
		case APP_CMD_STOP:
			ANativeActivity_finish(app->activity);
			break;
		default:
			LOGW("State not handled(0x%08X)!!!", state);
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
					//t->KeyboardShow();
					//t->jenv->CallVoidMethod(app->activity->clazz, t->jmID_PlayVideo);
					//t->video = true;
					fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHSTART, event);
					break;
				case AMOTION_EVENT_ACTION_MOVE:
					fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHMOVE, event);
					break;
				case AMOTION_EVENT_ACTION_UP:
				case AMOTION_EVENT_ACTION_POINTER_UP:
					//t->KeyboardHide();
					fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHEND, event);
					break;
				case AMOTION_EVENT_ACTION_CANCEL:
					fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHCANCEL, event);
					break;
				default:
					break;
			}
			break;
		}
		case AINPUT_EVENT_TYPE_KEY:
		{
			uint16_t key_val = AKeyEvent_getKeyCode(event);
			//fxCRL::keyboardInput(reinterpret_cast<const char*>(&key_val));
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
        updateGL();

        now = std::chrono::steady_clock::steady_clock::now();
        //LOGI("draw_diff: %llf\n", draw_dif.count());
    }

    //LOGI("tick_diff: %llf\n", tick_dif.count());
    // Tick the HTML5 timers
    last_tick = now;
    fxCRL::tick();
}

void fxDeviceWrapper::updateGL()
{
	if(!glwrap) return;
	fxCRL::paint();
	glwrap->SwapBuffers();
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
