#ifndef _fxDeviceWrapper_h
#define _fxDeviceWrapper_h

class fxDeviceWrapper;
class fxGLWrap;

#include "Coconut2D.hpp"
#include "fxFile.h"
#include "fxArgs.h"
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
	WebGLRenderingContext* gl;

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
