#ifndef __COCOTIMELINE_HPP__
#define __COCOTIMELINE_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "CocoTimeLabel.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoAudio.hpp"

class CocoTimeline
{
public:
	Array<CocoTimeLabel*> __labels;
	Array<CocoKeyFrame*> __keyFrames;
	Time __singleFrameDurationTime;
	Time __durationInTime;
	int __durationInFrames;
	bool __paused;
	float __fps;
	int __currentFrameIndex;
	int __firstKeyFrameIndex;
	int __lastKeyFrameIndex;
	CocoTimeline();
	~CocoTimeline();
	void prepare(CocoScene* scene, CocoClip* clip);
	void clear();
	void reset();
	CocoTimeLabel* addLabel(CocoTimeLabel* Label);
	CocoTimeLabel* addLabelEx(int FrameIndex, String LabelName);
	CocoTimeLabel* findLabelByName(String LabelName);
	CocoKeyFrame* keyFrame(int frameIndex);
	CocoKeyFrame* firstKeyFrame();
	CocoKeyFrame* lastKeyFrame();
	CocoKeyFrame* addKeyFrame(CocoKeyFrame* KeyFrame);
	CocoKeyFrame* addKeyFrameEx(State* nextState, CocoAction actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, int filter, float red, float green, float blue, float alpha, CocoAudio* audio, bool flipH, bool flipV, String spriteSequenceName);
	void normalizetimeline();
	CocoKeyFrame* findKeyFrameBeforeframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* findKeyFrameAfterframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* interpolate(float frameIndex);
};

#endif
