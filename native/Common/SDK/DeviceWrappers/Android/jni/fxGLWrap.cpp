#include "fxGLWrap.h"
#include "fxDeviceWrapper.h"

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
