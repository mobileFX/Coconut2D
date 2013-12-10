#ifndef __COCOKEYFRAME_HPP__
#define __COCOKEYFRAME_HPP__

class CocoKeyFrame
{
public:
	int frameIndex = 0;
	COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation = COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN;
	bool handleEvents = false;
	bool calcBoundingBox = true;
	float alpha = 1;
	bool visible = true;
	float x = 0;
	float y = 0;
	float pivotX = 0;
	float pivotY = 0;
	float scaleX = 1;
	float scaleY = 1;
	float rotation = 0;
	Function* action = NULL;
	float __lastActionExecutionTime = 0;
	CocoKeyFrame();
	CocoKeyFrame* clone();
	void reset();
	void execute(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoScene* scene, CocoClip* clip);
	void interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s);
	void combine(CocoKeyFrame* Frame);
	void apply(CocoMatrix* matrix);
};

#endif
