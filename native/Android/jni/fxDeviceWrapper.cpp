#include "fxDeviceWrapper.h"

extern AAssetManager* fxFile::manager;
extern char* fxFile::assetPath;
extern char* fxFile::filesPath;
extern fxArgs* fxArgs::Args;

////////////////////////////////////////////////////////////////////////////////////////////////////
fxGLWrap::fxGLWrap(ANativeWindow* window, fxDeviceWrapper* dev)
{
	LOGI("fxGLWrap();\n");
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

	LOGI("eglGetDisplay();\n");
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

	LOGI("ANativeWindow_setBuffersGeometry();\n");
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

	LOGI("glViewport();\n");
    glViewport(0, 0, screen.width * screen.pixelRatio, screen.height * screen.pixelRatio);
    LOGI("fxGLWrap Initialized successfully!\n");
}

fxGLWrap::~fxGLWrap()
{
	LOGW("DESTRUCTOR!\n");
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
		LOGW("ERROR eglMakeCurrent(%d)!\n", eglGetError());
	else LOGI("setContext OK!");
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
/*
////////////////////////////////////////////////////////////////////////////////////////////////////
fxSLWrap::fxSLWrap(ANativeWindow*) : engineObj(nullptr), outputObj(nullptr)
{
	LOGI("fxSLWrap();\n");

	if(slCreateEngine(&engineObj, 0, nullptr, 0, nullptr, nullptr) != SL_RESULT_SUCCESS)
		LOGW("Error creating the OpenSL ES Engine!\n");

	if(engineObj)
	{
		if((*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE) != SL_RESULT_SUCCESS)
			LOGW("Error realizing the OpenSL ES Engine!\n");

		if((*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engineItf) != SL_RESULT_SUCCESS)
			LOGW("Error getting the interface of OpenSL ES Engine!\n");

		if((*engineItf)->CreateOutputMix(engineItf, &outputObj, 0, nullptr, nullptr) != SL_RESULT_SUCCESS)
			LOGW("Error creating output mixer of OpenSL ES Engine!\n");

		if(outputObj)
		{
			if((*outputObj)->Realize(outputObj, SL_BOOLEAN_FALSE) != SL_RESULT_SUCCESS)
				LOGW("Error realizing the output mixer of OpenSL ES Engine!\n");

			if((*outputObj)->GetInterface(outputObj, SL_IID_VOLUME, &volumeItf) != SL_RESULT_SUCCESS)
				LOGW("Error getting the volume interface of OpenSL ES Engine!\n");

			LOGI("fxSLWrap Initialized successfully!\n");
		}
	}
}

fxSLWrap::~fxSLWrap()
{
	if(outputObj) (*outputObj)->Destroy(outputObj);
	if(engineObj) (*engineObj)->Destroy(engineObj);
}
*/
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

	LOGI("internalDataPath: %s\n", app->activity->internalDataPath);
	LOGI("externalDataPath: %s\n", app->activity->externalDataPath);
	fxFile::init(app->activity->assetManager, "/data/data/com.mobilefx.fxcore/files/");
	fxArgs::init("./args.txt");
	fxFontFace::init();
	fxAudio::init();

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
	fxAudio::quit();
	fxFontFace::quit();
	fxArgs::quit();
	fxFile::quit();

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
					t->KeyboardShow();
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
