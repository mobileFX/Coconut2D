#include "CocoTimeline.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::CocoTimeline()
{
	__singleFrameDurationTime = 0.0;
	__durationInTime = 0.0;
	__durationInFrames = 0;
	__skipTime = 0.0;
	__paused = false;
	__pausedKeyFrame = NULL;
	__fps = 30;
	addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::~CocoTimeline()
{
	delete __labels;
	delete __keyFrames;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::clear()
{
	reset();
	normalizetimeline();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::reset()
{
	__skipTime = 0;
	__paused = false;
	for(int i = __keyFrames.size() - 1; i >= 0; i--)
	{
		__keyFrames[i]->reset();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeLabel* CocoTimeline::addLabel(CocoTimeLabel* Label)
{
	if(Label)
	{
		__labels.push(Label);
	}
	return Label;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeLabel* CocoTimeline::addLabelEx(int FrameIndex, std::string LabelName)
{
	CocoTimeLabel* Label = new CocoTimeLabel(FrameIndex, LabelName);
	return addLabel(Label);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeLabel* CocoTimeline::findLabelByName(std::string LabelName)
{
	for(int i = __labels.size() - 1; i >= 0; i--)
	{
		if(__labels[i]->name == LabelName)
		{
			return __labels[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::keyFrame(int frameIndex)
{
	for(int i = __keyFrames.size() - 1; i >= 0; i--)
	{
		if(__keyFrames[i]->frameIndex == frameIndex)
		{
			return __keyFrames[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::firstKeyFrame()
{
	return __keyFrames[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::lastKeyFrame()
{
	return __keyFrames[__keyFrames.size() - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::addKeyFrame(CocoKeyFrame* KeyFrame)
{
	if(KeyFrame)
	{
		KeyFrame->frameIndex = std::floor(KeyFrame->frameIndex);
		__keyFrames.push(KeyFrame);
		normalizetimeline();
	}
	return KeyFrame;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::addKeyFrameEx(Function* actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, float alpha)
{
	CocoKeyFrame* KeyFrame = new CocoKeyFrame();
	KeyFrame->action = actionCallback;
	KeyFrame->frameIndex = frameIndex;
	KeyFrame->frameInterpolation = frameInterpolation;
	KeyFrame->handleEvents = handleEvents;
	KeyFrame->visible = visible;
	KeyFrame->x = x;
	KeyFrame->y = y;
	KeyFrame->scaleX = scaleX;
	KeyFrame->scaleY = scaleY;
	KeyFrame->rotation = rotation;
	KeyFrame->pivotX = pivotX;
	KeyFrame->pivotY = pivotY;
	KeyFrame->alpha = alpha;
	return addKeyFrame(KeyFrame);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::prepare(CocoScene* scene, CocoClip* clip)
{
	__fps = scene->__fps;
	normalizetimeline();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::normalizetimeline()
{
	reset();
	__durationInFrames = 0;
	__durationInTime = 0;
	__singleFrameDurationTime = 0;
	if(__keyFrames.size() > 0)
	{
		__durationInFrames = __keyFrames[__keyFrames.size() - 1]->frameIndex + 1;
		__durationInTime = ((float)(__durationInFrames) / (float)(__fps)) * 1000;
		__singleFrameDurationTime = (float)(__durationInTime) / (float)(__durationInFrames);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::jumpBy(float frames, bool paused)
{
	__paused = paused;
	if(frames != 0)
	{
		__skipTime += (frames * __singleFrameDurationTime);
		__pausedKeyFrame = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::findKeyFrameBeforeframeIndex(float frameIndex, bool inclusive, float excludeListIndex)
{
	CocoKeyFrame* KeyFrame;
	for(int i = __keyFrames.size() - 1; i >= 0; i--)
	{
		if(i != excludeListIndex)
		{
			KeyFrame = __keyFrames[i];
			if(inclusive)
			{
				if(KeyFrame->frameIndex <= frameIndex)
				{
					return KeyFrame;
				}
			}
			else
			{
				if(KeyFrame->frameIndex < frameIndex)
				{
					return KeyFrame;
				}
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::findKeyFrameAfterframeIndex(float frameIndex, bool inclusive, float excludeListIndex)
{
	CocoKeyFrame* KeyFrame;
	for(int i = 0,  L = __keyFrames.size(); i < L; i++)
	{
		if(i != excludeListIndex)
		{
			KeyFrame = __keyFrames[i];
			if(inclusive)
			{
				if(KeyFrame->frameIndex >= frameIndex)
				{
					return KeyFrame;
				}
			}
			else
			{
				if(KeyFrame->frameIndex > frameIndex)
				{
					return KeyFrame;
				}
			}
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::interpolateByTime(float LoopTime)
{
	float T = ((float)(LoopTime) / (float)(__singleFrameDurationTime));
	return interpolateByFrame(T);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::interpolateByFrame(float frameIndex)
{
	if(__paused && __pausedKeyFrame)
	{
		return __pausedKeyFrame;
	}
	CocoKeyFrame* F = NULL;
	CocoKeyFrame* F1 = NULL;
	CocoKeyFrame* F2 = NULL;
	float s = 1.0;
	float FrameIndex = std::floor(frameIndex);
	if(__keyFrames.size() == 0)
	{
		F = new CocoKeyFrame();
		F->frameIndex = FrameIndex;
		F->visible = false;
		return (__pausedKeyFrame = F);
	}
	F1 = keyFrame(FrameIndex);
	if(F1)
	{
		return (__pausedKeyFrame = F1->clone());
	}
	F1 = findKeyFrameBeforeframeIndex(FrameIndex, false,  -1);
	if(!F1)
	{
		F = new CocoKeyFrame();
		F->frameIndex = FrameIndex;
		F->visible = false;
		return (__pausedKeyFrame = F);
	}
	else
	{
		switch(F1->frameInterpolation)
		{
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO:
			{
				F = F1->clone();
				F->frameIndex = FrameIndex;
				F->action = NULL;
				return (__pausedKeyFrame = F);
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE:
			{
				F = F1->clone();
				F->frameIndex = FrameIndex;
				F->action = NULL;
				F->visible = false;
				return (__pausedKeyFrame = F);
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN:
			{
				F2 = findKeyFrameAfterframeIndex(FrameIndex, false,  -1);
				if(!F2)
				{
					F = F1->clone();
					F->frameIndex = FrameIndex;
					F->action = NULL;
					return (__pausedKeyFrame = F);
				}
				else
				{
					F = F1->clone();
					F->frameIndex = FrameIndex;
					F->action = NULL;
					s = (float)((frameIndex - F1->frameIndex)) / (float)((F2->frameIndex - F1->frameIndex));
					F->interpolate(F1, F2, s);
					return (__pausedKeyFrame = F);
				}
			}
			break;
		}
	}
	return NULL;
}
