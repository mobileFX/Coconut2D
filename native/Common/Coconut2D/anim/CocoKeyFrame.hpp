#ifndef __COCOKEYFRAME_HPP__
#define __COCOKEYFRAME_HPP__

#include "Coconut2D.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoMatrix.hpp"
#include "CocoAudio.hpp"

class CocoKeyFrame
{
public:
	int frameIndex;
	float __frameIndex;
	COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation;
	bool handleEvents;
	bool visible;
	int filter;
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
	bool __isCloned;
	CocoKeyFrame();
	~CocoKeyFrame();
	CocoKeyFrame* clone(bool exact);
	void reset();
	void interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s);
	void combine(CocoKeyFrame* Frame);
	void apply(CocoMatrix* matrix);
};

#endif
