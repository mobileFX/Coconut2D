#ifndef __COCOENGINESTATE_HPP__
#define __COCOENGINESTATE_HPP__

class CocoEngineState
{
public:
	CocoEngineState();
	void tick(CocoEngine* engine, WebGLRenderingContext* gl, float time);
};

#endif
