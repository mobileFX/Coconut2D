#ifndef __COCOKEYFRAME_HPP__
#define __COCOKEYFRAME_HPP__

#include "Coconut2D.hpp"
#include "CocoKeyFrame.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "CocoMatrix.hpp"
//#include "CocoState.hpp"
#include "CocoAudio.hpp"
#include "CocoEngine.hpp"

class CocoKeyFrame
{
public:
	int frameIndex;
	COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation;
	bool handleEvents;
	bool visible;
	float red;
	float green;
	float blue;
	float alpha;
	float x;
	float y;
	float pivotX;
	float pivotY;
	float scaleX;
	float scaleY;
	float rotation;
	CocoAction action;
	State* nextState;
	CocoAudio* audio;
	bool flipH;
	bool flipV;
	String spriteSequenceName;
	Time __lastActionExecutionTime;
	bool __isCloned;
	CocoKeyFrame();
	~CocoKeyFrame();
	CocoKeyFrame* clone();
	void reset();
	bool execute(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* clip);
	void interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s);
	void combine(CocoKeyFrame* Frame);
	void apply(CocoMatrix* matrix);
};

#endif
