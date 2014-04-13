#include "CocoTimeline.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::CocoTimeline()
{
	__labels = new Array<CocoTimeLabel*> ();
	__keyFrames = new Array<CocoKeyFrame*> ();
	__singleFrameDurationTime = 0.0;
	__durationInTime = 0.0;
	__durationInFrames = 0;
	__paused = false;
	__fps = 30;
	__currentFrameIndex = -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeline::~CocoTimeline()
{
	if(__labels)
	{
		__labels = (delete __labels, nullptr);
	}
	if(__keyFrames)
	{
		__keyFrames = (delete __keyFrames, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::prepare(CocoScene* scene, CocoClip* clip)
{
	__fps = scene->__fps;
	normalizetimeline();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::clear()
{
	reset();
	if(__labels)
	{
		__labels = (delete __labels, nullptr);
	}
	if(__keyFrames)
	{
		__keyFrames = (delete __keyFrames, nullptr);
	}
	__labels = new Array<CocoTimeLabel*> ();
	__keyFrames = new Array<CocoKeyFrame*> ();
	normalizetimeline();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoTimeline::reset()
{
	__paused = false;
	__currentFrameIndex = -1;
	for(int i = __keyFrames->size() - 1; i >= 0; i--)
	{
		(*__keyFrames)[i]->reset();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoTimeLabel* CocoTimeline::addLabel(CocoTimeLabel* Label)
{
	if(Label)
	{
		__labels->push(Label);
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
	for(int i = __labels->size() - 1; i >= 0; i--)
	{
		if((*__labels)[i]->name == LabelName)
		{
			return (*__labels)[i];
		}
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::keyFrame(int frameIndex)
{
	for(int i = __keyFrames->size() - 1; i >= 0; i--)
	{
		if((*__keyFrames)[i]->frameIndex == frameIndex)
		{
			return (*__keyFrames)[i];
		}
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::firstKeyFrame()
{
	return (*__keyFrames)[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::lastKeyFrame()
{
	return (*__keyFrames)[__keyFrames->size() - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::addKeyFrame(CocoKeyFrame* KeyFrame)
{
	if(KeyFrame)
	{
		KeyFrame->frameIndex = floor(KeyFrame->frameIndex);
		__keyFrames->push(KeyFrame);
		normalizetimeline();
	}
	return KeyFrame;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::addKeyFrameEx(State* nextState, CocoAction actionCallback, int frameIndex, COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation, bool handleEvents, bool visible, float x, float y, float scaleX, float scaleY, float rotation, float pivotX, float pivotY, int filter, float red, float green, float blue, float alpha, CocoAudio* audio, bool flipH, bool flipV, String spriteSequenceName)
{
	CocoKeyFrame* KeyFrame = new CocoKeyFrame();
	KeyFrame->nextState = nextState;
	KeyFrame->action = actionCallback;
	KeyFrame->frameIndex = frameIndex;
	KeyFrame->frameInterpolation = frameInterpolation;
	KeyFrame->handleEvents = handleEvents;
	KeyFrame->visible = visible;
	KeyFrame->filter = filter;
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
void CocoTimeline::normalizetimeline()
{
	__durationInFrames = 0;
	__durationInTime = 0;
	__singleFrameDurationTime = 0;
	if(__keyFrames->size() > 0)
	{
		__durationInFrames = (*__keyFrames)[__keyFrames->size() - 1]->frameIndex + 1;
		__singleFrameDurationTime = (float)(1000.0) / (float)(__fps);
		__durationInTime = ((Time)__durationInFrames) * __singleFrameDurationTime;
		__firstKeyFrameIndex = firstKeyFrame()->frameIndex;
		__lastKeyFrameIndex = lastKeyFrame()->frameIndex;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoTimeline::findKeyFrameBeforeframeIndex(float frameIndex, bool inclusive, float excludeListIndex)
{
	CocoKeyFrame* KeyFrame;
	for(int i = __keyFrames->size() - 1; i >= 0; i--)
	{
		if(i != excludeListIndex)
		{
			KeyFrame = (*__keyFrames)[i];
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
CocoKeyFrame* CocoTimeline::findKeyFrameAfterframeIndex(float frameIndex, bool inclusive, float excludeListIndex)
{
	CocoKeyFrame* KeyFrame;
	for(int i = 0,  L = __keyFrames->size(); i < L; i++)
	{
		if(i != excludeListIndex)
		{
			KeyFrame = (*__keyFrames)[i];
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
	float s = 1.0;
	if(frameIndex <= 0)
	{
		frameIndex = 0;
	}
	int iFrameIndex = floor(frameIndex);
	if(__keyFrames->size() == 0)
	{
		F = new CocoKeyFrame();
		F->frameIndex = iFrameIndex;
		F->visible = false;
		return F;
	}
	F1 = findKeyFrameBeforeframeIndex(frameIndex, true,  -1);
	if(!F1)
	{
		F = new CocoKeyFrame();
		F->frameIndex = iFrameIndex;
		F->__frameIndex = frameIndex;
		F->visible = false;
		return F;
	}
	else
	{
		bool exact = !__paused && ((__currentFrameIndex == -1) || (__currentFrameIndex != F1->frameIndex));
		__currentFrameIndex = F1->frameIndex;
		if(F1->frameIndex == iFrameIndex)
		{
			F1 = F1->clone(exact);
			F1->__frameIndex = frameIndex;
			return F1;
		}
		switch(F1->frameInterpolation)
		{
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO:
			{
				F = F1->clone(exact);
				F->frameIndex = iFrameIndex;
				F->__frameIndex = frameIndex;
				return F;
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE:
			{
				F = F1->clone(exact);
				F->frameIndex = iFrameIndex;
				F->__frameIndex = frameIndex;
				F->visible = false;
				return F;
			}
			break;
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN:
			{
				F2 = findKeyFrameAfterframeIndex(frameIndex, (frameIndex > iFrameIndex),  -1);
				if(!F2)
				{
					F = F1->clone(exact);
					F->frameIndex = iFrameIndex;
					F->__frameIndex = frameIndex;
					return F;
				}
				else
				{
					F = F1->clone(exact);
					F->frameIndex = iFrameIndex;
					F->__frameIndex = frameIndex;
					s = (float)((frameIndex - ((float)F1->frameIndex))) / (float)(((float)F2->frameIndex - F1->frameIndex));
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
