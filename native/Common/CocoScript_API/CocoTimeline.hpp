#ifndef __COCOTIMELINE_HPP__
#define __COCOTIMELINE_HPP__

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
	CocoTimeline();
	void clear();
	void reset();
	CocoTimeLabel* addLabel(CocoTimeLabel* Label);
	CocoTimeLabel* addLabelEx(int FrameIndex, std::string LabelName);
	CocoTimeLabel* findLabelByName(std::string LabelName);
	CocoKeyFrame* keyFrame(int frameIndex);
	CocoKeyFrame* firstKeyFrame();
	CocoKeyFrame* lastKeyFrame();
	CocoKeyFrame* addKeyFrame(CocoKeyFrame* KeyFrame);
	CocoKeyFrame* addKeyFrameEx(Function* actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, float alpha);
	void normalizetimeline();
	void jumpBy(float frames, bool paused);
	CocoKeyFrame* findKeyFrameBeforeframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* findKeyFrameAfterframeIndex(float frameIndex, bool inclusive, float excludeListIndex);
	CocoKeyFrame* interpolateByTime(float LoopTime);
	CocoKeyFrame* interpolateByFrame(float frameIndex);
};

#endif
