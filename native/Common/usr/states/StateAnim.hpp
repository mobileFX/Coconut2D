#ifndef __STATEANIM_HPP__
#define __STATEANIM_HPP__

#include "Coconut2D.hpp"
#include "CocoEngineState.hpp"
#include "CocoEngine.hpp"
#include "WebGLRenderingContext.hpp"
#include "Animation1.hpp"

class StateAnim : public CocoEngineState
{
public:
	Animation1* scene;
	StateAnim();
	void tick(CocoEngine* engine, WebGLRenderingContext* gl, float time);
};

#endif
