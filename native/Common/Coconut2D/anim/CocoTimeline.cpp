#include "CocoTimeline.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::CocoTimeline()
{
	__singleFrameDurationTime = 0.0;
	__durationInTime = 0.0;
	__durationInFrames = 0;
	__paused = false;
	__fps = 30;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::~CocoTimeline()
{
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
CocoTimeLabel* CocoTimeline::addLabelEx(int FrameIndex, String LabelName)
{
	CocoTimeLabel* Label = new CocoTimeLabel(FrameIndex, LabelName);
	return addLabel(Label);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeLabel* CocoTimeline::findLabelByName(String LabelName)
{
	for(int i = __labels.size() - 1; i >= 0; i--)
	{
		if(__labels[i]->name == LabelName)
		{
			return __labels[i];
		}
	}
	return nullptr;
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
	return nullptr;
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
CocoKeyFrame* CocoTimeline::addKeyFrameEx(State* nextState, CocoAction actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, float red, float green, float blue, float alpha, CocoAudio* audio, bool flipH, bool flipV, String spriteSequenceName)
{
	CocoKeyFrame* KeyFrame = new CocoKeyFrame();
	KeyFrame->nextState = nextState;
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
	KeyFrame->red = red;
	KeyFrame->green = green;
	KeyFrame->blue = blue;
	KeyFrame->alpha = alpha;
	KeyFrame->audio = audio;
	KeyFrame->flipH = flipH;
	KeyFrame->flipV = flipV;
	KeyFrame->spriteSequenceName = spriteSequenceName;
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
		__durationInTime = Time(((float)(__durationInFrames) / (float)(__fps)) * 1000);
		__singleFrameDurationTime = (float)(__durationInTime) / (float)(Time(__durationInFrames));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::findKeyFrameBeforeframeIndex(int frameIndex, bool inclusive, float excludeListIndex)
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
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::findKeyFrameAfterframeIndex(int frameIndex, bool inclusive, float excludeListIndex)
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
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::interpolate(float frameIndex)
{
	CocoKeyFrame* F = nullptr;
	CocoKeyFrame* F1 = nullptr;
	CocoKeyFrame* F2 = nullptr;
	int FrameIndex = floor(frameIndex);
	float s = 1.0;
	if(__keyFrames.size() == 0)
	{
		F = new CocoKeyFrame();
		F->frameIndex = FrameIndex;
		F->visible = false;
		return F;
	}
	F1 = keyFrame(FrameIndex);
	if(F1)
	{
		return F1->clone();
	}
	F1 = findKeyFrameBeforeframeIndex(FrameIndex, false,  -1);
	if(!F1)
	{
		F = new CocoKeyFrame();
		F->frameIndex = FrameIndex;
		F->visible = false;
		return F;
	}
	else
	{
		switch(F1->frameInterpolation)
		{
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO:
			{
				F = F1->clone();
				F->action = nullptr;
				F->audio = nullptr;
				F->nextState = nullptr;
				F->frameIndex = FrameIndex;
				return F;
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE:
			{
				F = F1->clone();
				F->action = nullptr;
				F->audio = nullptr;
				F->nextState = nullptr;
				F->frameIndex = FrameIndex;
				F->visible = false;
				return F;
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN:
			{
				F2 = findKeyFrameAfterframeIndex(FrameIndex, false,  -1);
				if(!F2)
				{
					F = F1->clone();
					F->action = nullptr;
					F->audio = nullptr;
					F->nextState = nullptr;
					F->frameIndex = FrameIndex;
					return F;
				}
				else
				{
					F = F1->clone();
					F->action = nullptr;
					F->audio = nullptr;
					F->nextState = nullptr;
					F->frameIndex = FrameIndex;
					s = float((float)((frameIndex - F1->frameIndex)) / (float)((F2->frameIndex - F1->frameIndex)));
					F->interpolate(F1, F2, s);
					return F;
				}
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_PHYSICS:
			{
				break;
			}
			break;
		}
	}
	return nullptr;
}
