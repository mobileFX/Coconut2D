#include "CocoClip.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip::CocoClip(CocoImage* image, String sequence)
{
	__symbolLoop = COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS;
	__currentSequenceFrameIndex = 0;
	__timeline = new CocoTimeline();
	__parent = NULL;
	__firstTickTime = -1.0;
	__currentFrame = NULL;
	__hasBoundingBox = false;
	__vABS_TOP_LEFT = new CocoVector();
	__vABS_TOP_RIGHT = new CocoVector();
	__vABS_BOTTOM_LEFT = new CocoVector();
	__vABS_BOTTOM_RIGHT = new CocoVector();
	__vREL_TOP_LEFT = new CocoVector();
	__vREL_TOP_RIGHT = new CocoVector();
	__vREL_BOTTOM_LEFT = new CocoVector();
	__vREL_BOTTOM_RIGHT = new CocoVector();
	__vTemp = new CocoVector();
	__mTemp = new CocoMatrix();
	__childWithMaxTimelineDuration = NULL;
	__currentSequence = NULL;
	__image = image;
	if(image && sequence)
	{
		__currentSequence = image->getSequence(sequence);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip::~CocoClip()
{
	if(__image)
	{
		__image = (delete __image, NULL);
	}
	if(__timeline)
	{
		__timeline = (delete __timeline, NULL);
	}
	if(__vABS_TOP_LEFT)
	{
		__vABS_TOP_LEFT = (delete __vABS_TOP_LEFT, NULL);
	}
	if(__vABS_TOP_RIGHT)
	{
		__vABS_TOP_RIGHT = (delete __vABS_TOP_RIGHT, NULL);
	}
	if(__vABS_BOTTOM_LEFT)
	{
		__vABS_BOTTOM_LEFT = (delete __vABS_BOTTOM_LEFT, NULL);
	}
	if(__vABS_BOTTOM_RIGHT)
	{
		__vABS_BOTTOM_RIGHT = (delete __vABS_BOTTOM_RIGHT, NULL);
	}
	if(__vREL_TOP_LEFT)
	{
		__vREL_TOP_LEFT = (delete __vREL_TOP_LEFT, NULL);
	}
	if(__vREL_TOP_RIGHT)
	{
		__vREL_TOP_RIGHT = (delete __vREL_TOP_RIGHT, NULL);
	}
	if(__vREL_BOTTOM_LEFT)
	{
		__vREL_BOTTOM_LEFT = (delete __vREL_BOTTOM_LEFT, NULL);
	}
	if(__vREL_BOTTOM_RIGHT)
	{
		__vREL_BOTTOM_RIGHT = (delete __vREL_BOTTOM_RIGHT, NULL);
	}
	if(__vTemp)
	{
		__vTemp = (delete __vTemp, NULL);
	}
	if(__mTemp)
	{
		__mTemp = (delete __mTemp, NULL);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::prepare(CocoScene* scene)
{
	__timeline->prepare(scene, this);
	for(int i = __children.size() - 1; i >= 0; i--)
	{
		__children[i]->prepare(scene);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::reset()
{
	if(__currentFrame)
		if(__currentFrame)
		{
			__currentFrame = (delete __currentFrame, NULL);
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
CocoClip* CocoClip::getChildByName(String instanceName)
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
bool CocoClip::gotoFrameByName(String LabelName, bool pause, bool deep)
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
void CocoClip::paint(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip)
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
		if(__currentFrame)
		{
			__currentFrame = (delete __currentFrame, NULL);
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
				__currentFrame = __timeline->lastKeyFrame()->clone(false);
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
			__currentFrame->scaleX *= __image->__pixelRatioScale;
			__currentFrame->scaleY *= __image->__pixelRatioScale;
			__currentFrame->apply(scene->__modelViewMatrix);
			__currentFrame->scaleX /= __image->__pixelRatioScale;
			__currentFrame->scaleY /= __image->__pixelRatioScale;
			if(__image->isSpriteSheet && __currentSequence)
			{
				__currentSequenceFrameIndex = __timeline->__paused ? 0 : (int)std::floor((float)((__currentTime - __firstTickTime)) / (float)(((float)(1000.0) / (float)(scene->__fps)))) % (int)__currentSequence->frames.size();
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
				__children[i]->paint(gl, scene, this);
				scene->__modelViewMatrix->pop();
			}
			scene->__levelParents.pop();
		}
		if(__currentFrame->alpha != 0 && __currentFrame->visible && engine->__deviceEvent && this != scene->__root)
		{
			if(__image)
			{
				initBoundingBoxFromTexture(scene, (float)(__image->textureCellWidth) / (float)(2), (float)(__image->textureCellHeight) / (float)(2));
			}
			else if(__children.size() > 0)
			{
				initBoundingBoxFromChildren(scene);
			}
			if(!__image)
			{
				Number x = (float)((engine->__deviceEvent->__clientX - (float)(gl->canvas->width) / (float)(2.0))) / (float)(scene->__view_scale);
				Number y = (float)((engine->__deviceEvent->__clientY - (float)(gl->canvas->height) / (float)(2.0))) / (float)(scene->__view_scale);
				if(hitTest(x, y))
				{
					drawBoundingBox(scene, gl);
				}
			}
		}
	}
	if(!__timeline->__paused)
	{
		bool pulse = false;
		if(__currentFrame->action || __currentFrame->nextState || __currentFrame->audio)
		{
			this->__parent = parentClip;
			pulse = __currentFrame->execute(gl, __currentTime, __loopTime, scene, this);
			if(pulse && __currentFrame->audio != NULL)
			{
				__currentAudio = __currentFrame->audio;
			}
			this->__parent = NULL;
		}
		if(__childWithMaxTimelineDuration && __childWithMaxTimelineDuration->__currentFrame && __childWithMaxTimelineDuration->__currentFrame->frameIndex == __childWithMaxTimelineDuration->__timeline->lastKeyFrame()->frameIndex)
		{
		}
	}
	if(__currentAudio)
	{
		__currentAudio->tick();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoClip::hitTest(float wx, float wy)
{
	return ((((wx - __vABS_TOP_LEFT->X) * (__vABS_TOP_RIGHT->Y - __vABS_TOP_LEFT->Y) - (__vABS_TOP_RIGHT->X - __vABS_TOP_LEFT->X) * (wy - __vABS_TOP_LEFT->Y)) * ((wx - __vABS_BOTTOM_RIGHT->X) * (__vABS_BOTTOM_LEFT->Y - __vABS_BOTTOM_RIGHT->Y) - (__vABS_BOTTOM_LEFT->X - __vABS_BOTTOM_RIGHT->X) * (wy - __vABS_BOTTOM_RIGHT->Y))) > 0 && (((wx - __vABS_TOP_RIGHT->X) * (__vABS_BOTTOM_RIGHT->Y - __vABS_TOP_RIGHT->Y) - (__vABS_BOTTOM_RIGHT->X - __vABS_TOP_RIGHT->X) * (wy - __vABS_TOP_RIGHT->Y)) * ((wx - __vABS_BOTTOM_LEFT->X) * (__vABS_TOP_LEFT->Y - __vABS_BOTTOM_LEFT->Y) - (__vABS_TOP_LEFT->X - __vABS_BOTTOM_LEFT->X) * (wy - __vABS_BOTTOM_LEFT->Y))) > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::initBoundingBoxFromTexture(CocoScene* scene, float W2, float H2)
{
	__mTemp->identity();
	__currentFrame->scaleX *= __image->__pixelRatioScale;
	__currentFrame->scaleY *= __image->__pixelRatioScale;
	__currentFrame->apply(__mTemp);
	__currentFrame->scaleX /= __image->__pixelRatioScale;
	__currentFrame->scaleY /= __image->__pixelRatioScale;
	__vTemp->reset(-W2,  -H2, 0, 1);
	__vREL_TOP_LEFT = __mTemp->multiplyByVector(__vTemp);
	__vABS_TOP_LEFT = scene->__modelViewMatrix->multiplyByVector(__vTemp);
	__vTemp->reset(W2,  -H2, 0, 1);
	__vREL_TOP_RIGHT = __mTemp->multiplyByVector(__vTemp);
	__vABS_TOP_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vTemp);
	__vTemp->reset(-W2, H2, 0, 1);
	__vREL_BOTTOM_LEFT = __mTemp->multiplyByVector(__vTemp);
	__vABS_BOTTOM_LEFT = scene->__modelViewMatrix->multiplyByVector(__vTemp);
	__vTemp->reset(W2, H2, 0, 1);
	__vREL_BOTTOM_RIGHT = __mTemp->multiplyByVector(__vTemp);
	__vABS_BOTTOM_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vTemp);
	__hasBoundingBox = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::initBoundingBoxFromChildren(CocoScene* scene)
{
	__hasBoundingBox = false;
	if(__children.size() == 0)
	{
		return;
	}
	CocoClip* Child;
	int i = 0;
	String vClip = "";
	__vREL_TOP_LEFT->X = 100000;
	__vREL_TOP_RIGHT->X = -100000;
	__vREL_TOP_LEFT->Y = 100000;
	__vREL_BOTTOM_LEFT->Y = -100000;
	for(vClip : __children)
	{
		Child = __children[vClip];
		if(Child->__hasBoundingBox)
		{
			if(Child->__vREL_TOP_LEFT->X < __vREL_TOP_LEFT->X)
			{
				__vREL_TOP_LEFT->X = Child->__vREL_TOP_LEFT->X;
			}
			if(Child->__vREL_TOP_LEFT->X > __vREL_TOP_RIGHT->X)
			{
				__vREL_TOP_RIGHT->X = Child->__vREL_TOP_LEFT->X;
			}
			if(Child->__vREL_TOP_LEFT->Y < __vREL_TOP_LEFT->Y)
			{
				__vREL_TOP_LEFT->Y = Child->__vREL_TOP_LEFT->Y;
			}
			if(Child->__vREL_TOP_LEFT->Y > __vREL_BOTTOM_LEFT->Y)
			{
				__vREL_BOTTOM_LEFT->Y = Child->__vREL_TOP_LEFT->Y;
			}
			if(Child->__vREL_TOP_RIGHT->X < __vREL_TOP_LEFT->X)
			{
				__vREL_TOP_LEFT->X = Child->__vREL_TOP_RIGHT->X;
			}
			if(Child->__vREL_TOP_RIGHT->X > __vREL_TOP_RIGHT->X)
			{
				__vREL_TOP_RIGHT->X = Child->__vREL_TOP_RIGHT->X;
			}
			if(Child->__vREL_TOP_RIGHT->Y < __vREL_TOP_LEFT->Y)
			{
				__vREL_TOP_LEFT->Y = Child->__vREL_TOP_RIGHT->Y;
			}
			if(Child->__vREL_TOP_RIGHT->Y > __vREL_BOTTOM_LEFT->Y)
			{
				__vREL_BOTTOM_LEFT->Y = Child->__vREL_TOP_RIGHT->Y;
			}
			if(Child->__vREL_BOTTOM_LEFT->X < __vREL_TOP_LEFT->X)
			{
				__vREL_TOP_LEFT->X = Child->__vREL_BOTTOM_LEFT->X;
			}
			if(Child->__vREL_BOTTOM_LEFT->X > __vREL_TOP_RIGHT->X)
			{
				__vREL_TOP_RIGHT->X = Child->__vREL_BOTTOM_LEFT->X;
			}
			if(Child->__vREL_BOTTOM_LEFT->Y < __vREL_TOP_LEFT->Y)
			{
				__vREL_TOP_LEFT->Y = Child->__vREL_BOTTOM_LEFT->Y;
			}
			if(Child->__vREL_BOTTOM_LEFT->Y > __vREL_BOTTOM_LEFT->Y)
			{
				__vREL_BOTTOM_LEFT->Y = Child->__vREL_BOTTOM_LEFT->Y;
			}
			if(Child->__vREL_BOTTOM_RIGHT->X < __vREL_TOP_LEFT->X)
			{
				__vREL_TOP_LEFT->X = Child->__vREL_BOTTOM_RIGHT->X;
			}
			if(Child->__vREL_BOTTOM_RIGHT->X > __vREL_TOP_RIGHT->X)
			{
				__vREL_TOP_RIGHT->X = Child->__vREL_BOTTOM_RIGHT->X;
			}
			if(Child->__vREL_BOTTOM_RIGHT->Y < __vREL_TOP_LEFT->Y)
			{
				__vREL_TOP_LEFT->Y = Child->__vREL_BOTTOM_RIGHT->Y;
			}
			if(Child->__vREL_BOTTOM_RIGHT->Y > __vREL_BOTTOM_LEFT->Y)
			{
				__vREL_BOTTOM_LEFT->Y = Child->__vREL_BOTTOM_RIGHT->Y;
			}
		}
	}
	__vREL_TOP_RIGHT->Y = __vREL_TOP_LEFT->Y;
	__vREL_BOTTOM_LEFT->X = __vREL_TOP_LEFT->X;
	__vREL_BOTTOM_RIGHT->X = __vREL_TOP_RIGHT->X;
	__vREL_BOTTOM_RIGHT->Y = __vREL_BOTTOM_LEFT->Y;
	__vABS_TOP_LEFT = scene->__modelViewMatrix->multiplyByVector(__vREL_TOP_LEFT);
	__vABS_TOP_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vREL_TOP_RIGHT);
	__vABS_BOTTOM_LEFT = scene->__modelViewMatrix->multiplyByVector(__vREL_BOTTOM_LEFT);
	__vABS_BOTTOM_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vREL_BOTTOM_RIGHT);
	__mTemp->identity();
	__currentFrame->apply(__mTemp);
	__vREL_TOP_LEFT = __mTemp->multiplyByVector(__vREL_TOP_LEFT);
	__vREL_TOP_RIGHT = __mTemp->multiplyByVector(__vREL_TOP_RIGHT);
	__vREL_BOTTOM_LEFT = __mTemp->multiplyByVector(__vREL_BOTTOM_LEFT);
	__vREL_BOTTOM_RIGHT = __mTemp->multiplyByVector(__vREL_BOTTOM_RIGHT);
	__hasBoundingBox = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::drawBoundingBox(CocoScene* scene, WebGLRenderingContext* gl)
{
	if(!__hasBoundingBox)
	{
		return;
	}
	gl->disableVertexAttribArray(scene->__glProgram->GLSLiTexCoords);
	gl->disableVertexAttribArray(scene->__glProgram->GLSLiVecCoords);
	gl->useProgram(scene->__boundingBoxProgram);
	gl->enableVertexAttribArray(scene->__boundingBoxProgram->GLSLiVec2Coords);
	gl->bindBuffer(gl->ARRAY_BUFFER, scene->__boundingBoxBuffer);
	gl->bufferSubData(gl->ARRAY_BUFFER, 0, new Float32Array({__vABS_TOP_LEFT->X, __vABS_TOP_LEFT->Y, __vABS_TOP_RIGHT->X, __vABS_TOP_RIGHT->Y, __vABS_BOTTOM_RIGHT->X, __vABS_BOTTOM_RIGHT->Y, __vABS_BOTTOM_LEFT->X, __vABS_BOTTOM_LEFT->Y}));
	gl->vertexAttribPointer(scene->__boundingBoxProgram->GLSLiVec2Coords, 2, gl->FLOAT, false, 0, 0);
	scene->__projectionMatrix->update(gl, scene->__boundingBoxProgram->GLSLuProjMat);
	gl->drawArrays(gl->LINE_LOOP, 0, 4);
	gl->bindBuffer(gl->ARRAY_BUFFER, NULL);
	gl->disableVertexAttribArray(scene->__boundingBoxProgram->GLSLiVec2Coords);
	gl->useProgram(scene->__glProgram);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiTexCoords);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiVecCoords);
}
