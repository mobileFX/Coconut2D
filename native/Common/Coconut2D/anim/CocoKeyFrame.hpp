#ifndef __COCOKEYFRAME_HPP__
#define __COCOKEYFRAME_HPP__

#include "Coconut2D.hpp"
#include "CocoKeyFrame.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "CocoMatrix.hpp"
#include "CocoState.hpp"
#include "CocoAudio.hpp"

class CocoKeyFrame
{
public:
	int frameIndex;
	COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation;
	bool handleEvents;
	bool calcBoundingBox;
	bool visible;
	float alpha;
	float x;
	float y;
	float pivotX;
	float pivotY;
	float scaleX;
	float scaleY;
	float rotation;
	Function* action;
	State* nextState;
	CocoAudio* audio;
	float __lastActionExecutionTime;
	CocoKeyFrame();
	~CocoKeyFrame();
	CocoKeyFrame* clone(bool exact);
	void reset();
	bool execute(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoScene* scene, CocoClip* clip);
	void interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s);
	void combine(CocoKeyFrame* Frame);
	void apply(CocoMatrix* matrix);
};

#endif
