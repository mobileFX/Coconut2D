/*
 * fxDeviceWrapper.h
 *
 *  Created on: Apr 25, 2013
 *      Author: mobileFX
 */

#ifndef FXDEVICEWRAPPER_H_
#define FXDEVICEWRAPPER_H_

class fxDeviceWrapper;

#include "fxAsset.h"
#include "fxCRL.h"
#include "fxGLWrap.h"
#include "fxAudio.h"

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

#endif /* FXDEVICEWRAPPER_H_ */
