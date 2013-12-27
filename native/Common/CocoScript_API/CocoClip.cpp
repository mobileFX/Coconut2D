#include "CocoClip.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip::CocoClip(CocoImage* image, CocoSound* audio, std::string sequence)
{
	__symbolLoop = COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS;
	__currentSequenceFrameIndex = 0;
	__timeline = new CocoTimeline();
	__parent = NULL;
	__firstTickTime = -1.0;
	__currentFrame = NULL;
	__hasBoundingBox = false;
	__vTOP_LEFT = new CocoVector();
	__vTOP_RIGHT = new CocoVector();
	__vBOTTOM_LEFT = new CocoVector();
	__vBOTTOM_RIGHT = new CocoVector();
	__childWithMaxTimelineDuration = NULL;
	__currentSequence = NULL;
	if(image)
	{
		__image = image;
	}
	if(audio)
	{
		__audio = audio;
	}
	if(image && sequence)
	{
		__currentSequence = image->getSequence(sequence);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::reset()
{
	if(__currentFrame)
	{
		delete __currentFrame;
	}
	__currentFrame = NULL;
	__firstTickTime = -1;
	__timeline->reset();
	for(int i = __children.size() - 1; i >= 0; i--)
	{
		__children[i]->reset();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* CocoClip::addChild(CocoClip* clipInstance)
{
	if(!clipInstance)
	{
		return NULL;
	}
	if(!clipInstance->__instanceName)
	{
		throw CocoException("Invalid instance name.");
	}
	__children.push(clipInstance);
	normalize();
	return clipInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* CocoClip::removeChild(CocoClip* clipInstance)
{
	if(!clipInstance)
	{
		return NULL;
	}
	__children.splice(getChildIndex(clipInstance), 1);
	normalize();
	return clipInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::normalize()
{
	__childWithMaxTimelineDuration = NULL;
	for(int i = __children.size() - 1; i >= 0; i--)
	{
		if(!__childWithMaxTimelineDuration)
		{
			__childWithMaxTimelineDuration = __children[i];
			continue;
		}
		if(__children[i]->__timeline->__durationInTime > __childWithMaxTimelineDuration->__timeline->__durationInTime)
		{
			__childWithMaxTimelineDuration = __children[i];
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* CocoClip::getChildByName(std::string instanceName)
{
	for(int i = __children.size() - 1; i >= 0; i--)
	{
		if(__children[i]->__instanceName == instanceName)
		{
			return __children[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoClip::getChildIndex(CocoClip* child)
{
	if(child)
	{
		for(int i = __children.size() - 1; i >= 0; i--)
		{
			if(__children[i] == child)
			{
				return i;
			}
		}
	}
	return  -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoClip::gotoFrameByName(std::string LabelName, bool pause, bool deep)
{
	CocoTimeLabel* Label = __timeline->findLabelByName(LabelName);
	if(!Label)
	{
		return false;
	}
	return gotoFrameByIndex(Label->frameIndex, pause, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoClip::gotoFrameByIndex(int FrameIndex, bool pause, bool deep)
{
	CocoClip* clip;
	for(int i = __children.size() - 1; i >= 0; i--)
	{
		clip = __children[i];
		if(FrameIndex == COCO_STOP_ON_CURRENT_FRAME)
		{
			clip->__timeline->jumpBy(0, pause);
		}
		else
		{
			int frames = (FrameIndex - clip->__currentFrame->frameIndex);
			clip->__timeline->jumpBy(frames, pause);
		}
		if(deep)
		{
			clip->gotoFrameByIndex(COCO_STOP_ON_CURRENT_FRAME, pause, deep);
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::render(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, bool picking)
{
	float __currentTime = scene->__currentTime + __timeline->__skipTime;
	if(__firstTickTime == -1)
	{
		__firstTickTime = __currentTime;
	}
	float parentClipsDuration = (parentClip ? parentClip->__childWithMaxTimelineDuration->__timeline->__durationInTime : __timeline->__durationInTime);
	float clippingTime = std::floor((float)((__currentTime - __firstTickTime)) / (float)(parentClipsDuration)) * parentClipsDuration;
	float __loopTime = (__currentTime - __firstTickTime) - clippingTime;
	if(!__timeline->__paused && __currentFrame)
	{
		delete __currentFrame;
	}
	switch(__symbolLoop)
	{
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS:
		{
			__currentFrame = __timeline->interpolateByTime(__loopTime);
			break;
		}
		break;
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_SYNCHRONIZED_WITH_PARENT:
		{
			__currentFrame = __timeline->interpolateByTime(__loopTime);
			break;
		}
		break;
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_ONCE:
		{
			if(clippingTime > 0)
			{
				__currentFrame = __timeline->lastKeyFrame().clone();
			}
			else
			{
				__currentFrame = __timeline->interpolateByTime(__loopTime);
			}
			break;
		}
		break;
	}
	if(parentClip)
	{
		__currentFrame->combine(parentClip->__currentFrame);
		if(__currentFrame->calcBoundingBox)
		{
			parentClip->__currentFrame->calcBoundingBox = true;
		}
	}
	if(__currentFrame->alpha != 0 && __currentFrame->visible)
	{
		if(__image)
		{
			float c = (float)(scene->__view_pixel_ratio) / (float)(__image->pixelRatio);
			__currentFrame->scaleX *= c;
			__currentFrame->scaleY *= c;
			__currentFrame->apply(scene->__modelViewMatrix);
			__currentFrame->scaleX /= c;
			__currentFrame->scaleY /= c;
			if(__image->isSpriteSheet && __currentSequence)
			{
				__currentSequenceFrameIndex = __timeline->__paused ? 0 : (int)std::floor((float)((__currentTime - __firstTickTime)) / (float)(GLOBAL_FPS)) % (int)__currentSequence->frames.size();
				int frame = __currentSequence->frames[__currentSequenceFrameIndex];
				scene->drawFrame(gl, __image, frame, __currentFrame->alpha);
			}
			else
			{
				scene->drawFrame(gl, __image, 0, __currentFrame->alpha);
			}
		}
		else
		{
			scene->__levelParents.push(this);
			__currentFrame->apply(scene->__modelViewMatrix);
			for(int i = 0,  L = __children.size(); i < L; i++)
			{
				scene->__modelViewMatrix->push();
				__children[i]->render(gl, scene, this, picking);
				scene->__modelViewMatrix->pop();
			}
			scene->__levelParents.pop();
		}
	}
	if(!__timeline->__paused && __currentFrame->action)
	{
		this->__parent = parentClip;
		__currentFrame->execute(gl, __currentTime, __loopTime, scene, this);
		this->__parent = NULL;
	}
}
