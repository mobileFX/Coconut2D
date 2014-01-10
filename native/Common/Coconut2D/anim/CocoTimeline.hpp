#ifndef __COCOTIMELINE_HPP__
#define __COCOTIMELINE_HPP__

#include "Coconut2D.hpp"
#include "CocoTimeLabel.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoState.hpp"
#include "CocoAudio.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"

class CocoTimeline
{
public:
	Array<CocoTimeLabel*> __labels;
	Array<CocoKeyFrame*> __keyFrames;
	float __singleFrameDurationTime;
	float __durationInTime;
	int __durationInFrames;
	float __skipTime;
	bool __paused;
	CocoKeyFrame* __pausedKeyFrame;
	float __fps;
	CocoTimeline();
	~CocoTimeline();
	void clear();
	void reset();
	CocoTimeLabel* addLabel(CocoTimeLabel* Label);
	CocoTimeLabel* addLabelEx(int FrameIndex, String LabelName);
	CocoTimeLabel* findLabelByName(String LabelName);
	CocoKeyFrame* keyFrame(int frameIndex);
	CocoKeyFrame* firstKeyFrame();
	CocoKeyFrame* lastKeyFrame();
	CocoKeyFrame* addKeyFrame(CocoKeyFrame* KeyFrame);
	CocoKeyFrame* addKeyFrameEx(State* nextState, Function* actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, float alpha, CocoAudio* audio, bool flipH, bool flipV);
	void prepare(CocoScene* scene, CocoClip* clip);
	void normalizetimeline();
	void jumpBy(float frames, bool paused);
	CocoKeyFrame* findKeyFrameBeforeframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* findKeyFrameAfterframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* interpolateByTime(float LoopTime);
	CocoKeyFrame* interpolateByFrame(float frameIndex);
};

#endif
