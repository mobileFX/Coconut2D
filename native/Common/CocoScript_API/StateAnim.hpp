#ifndef __STATEANIM_HPP__
#define __STATEANIM_HPP__

class StateAnim : public CocoEngineState
{
public:
	Animation1* scene;
	StateAnim();
	void tick(CocoEngine* engine, WebGLRenderingContext* gl, float time);
};

#endif
