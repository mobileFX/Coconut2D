#ifndef __STATE_TITLESCREEN_HPP__
#define __STATE_TITLESCREEN_HPP__

#include "Coconut2D.hpp"
#include "CocoEngineState.hpp"
#include "CocoEngine.hpp"
#include "WebGLRenderingContext.hpp"
#include "SceneTitle.hpp"

class State_TitleScreen : public CocoEngineState
{
public:
	SceneTitle* scene;
	State_TitleScreen();
	void tick(CocoEngine* engine, WebGLRenderingContext* gl, Number time);
};

#endif
