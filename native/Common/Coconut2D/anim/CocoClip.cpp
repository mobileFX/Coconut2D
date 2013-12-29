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
				__currentFrame = __timeline->lastKeyFrame()->clone();
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
				__children[i]->render(gl, scene, this, picking);
				scene->__modelViewMatrix->pop();
			}
			scene->__levelParents.pop();
		}
		if(engine->__touchEvent && this != scene->__root)
		{
			if(__image)
			{
				initBoundingBoxFromTexture(scene, (float)(__image->textureCellWidth) / (float)(2), (float)(__image->textureCellHeight) / (float)(2));
			}
			else if(__children.size() > 0)
			{
				initBoundingBoxFromChildren(scene);
			}
			if(engine->__touchEvent && !__image)
			{
				Number x = (float)((engine->__touchEvent->__clientX - (float)(gl->canvas->width) / (float)(2.0))) / (float)(scene->__view_scale);
				Number y = (float)((engine->__touchEvent->__clientY - (float)(gl->canvas->height) / (float)(2.0))) / (float)(scene->__view_scale);
				if(engine->__touchEvent && hitTest(x, y))
				{
					engine->__touchEvent->currentTarget = this;
					engine->__touchEvent->target = this;
					engine->__touchEvent->__targets.push(this);
				}
			}
		}
	}
	if(!__timeline->__paused && __currentFrame->action)
	{
		this->__parent = parentClip;
		__currentFrame->execute(gl, __currentTime, __loopTime, scene, this);
		this->__parent = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoClip::hitTest(float wx, float wy)
{
	return ((((wx - __vTOP_LEFT->X) * (__vTOP_RIGHT->Y - __vTOP_LEFT->Y) - (__vTOP_RIGHT->X - __vTOP_LEFT->X) * (wy - __vTOP_LEFT->Y)) * ((wx - __vBOTTOM_RIGHT->X) * (__vBOTTOM_LEFT->Y - __vBOTTOM_RIGHT->Y) - (__vBOTTOM_LEFT->X - __vBOTTOM_RIGHT->X) * (wy - __vBOTTOM_RIGHT->Y))) > 0 && (((wx - __vTOP_RIGHT->X) * (__vBOTTOM_RIGHT->Y - __vTOP_RIGHT->Y) - (__vBOTTOM_RIGHT->X - __vTOP_RIGHT->X) * (wy - __vTOP_RIGHT->Y)) * ((wx - __vBOTTOM_LEFT->X) * (__vTOP_LEFT->Y - __vBOTTOM_LEFT->Y) - (__vTOP_LEFT->X - __vBOTTOM_LEFT->X) * (wy - __vBOTTOM_LEFT->Y))) > 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::initBoundingBoxFromTexture(CocoScene* scene, float W2, float H2)
{
	__vTOP_LEFT->set(-W2,  -H2, 0, 1);
	__vTOP_RIGHT->set(W2,  -H2, 0, 1);
	__vBOTTOM_LEFT->set(-W2, H2, 0, 1);
	__vBOTTOM_RIGHT->set(W2, H2, 0, 1);
	__vTOP_LEFT = scene->__modelViewMatrix->multiplyByVector(__vTOP_LEFT);
	__vTOP_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vTOP_RIGHT);
	__vBOTTOM_LEFT = scene->__modelViewMatrix->multiplyByVector(__vBOTTOM_LEFT);
	__vBOTTOM_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vBOTTOM_RIGHT);
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
	CocoMatrix* MI;
	CocoClip* Child;
	CocoRect* Rc;
	int i = 0;
	CocoVector* v1;
	CocoVector* v2;
	std::string vClip = "";
	Array<CocoVector*> v;
	Rc = new CocoRect();
	Rc->left = 100000;
	Rc->right = -100000;
	Rc->top = 100000;
	Rc->bottom = -100000;
	MI = new CocoMatrix(scene->__modelViewMatrix);
	MI->invert();
	for(vClip : __children)
	{
		Child = __children[vClip];
		if(Child->__hasBoundingBox)
		{
			v[0] = MI->multiplyByVector(Child->__vTOP_LEFT);
			v[1] = MI->multiplyByVector(Child->__vTOP_RIGHT);
			v[2] = MI->multiplyByVector(Child->__vBOTTOM_LEFT);
			v[3] = MI->multiplyByVector(Child->__vBOTTOM_RIGHT);
			for(int i = 0; i < 4; i++)
			{
				if(v[i]->X < Rc->left)
				{
					Rc->left = v[i]->X;
				}
				if(v[i]->X > Rc->right)
				{
					Rc->right = v[i]->X;
				}
				if(v[i]->Y < Rc->top)
				{
					Rc->top = v[i]->Y;
				}
				if(v[i]->Y > Rc->bottom)
				{
					Rc->bottom = v[i]->Y;
				}
			}
		}
	}
	__vTOP_LEFT->X = Rc->left;
	__vTOP_LEFT->Y = Rc->top;
	__vTOP_RIGHT->X = Rc->right;
	__vTOP_RIGHT->Y = Rc->top;
	__vBOTTOM_LEFT->X = Rc->left;
	__vBOTTOM_LEFT->Y = Rc->bottom;
	__vBOTTOM_RIGHT->X = Rc->right;
	__vBOTTOM_RIGHT->Y = Rc->bottom;
	MI = scene->__modelViewMatrix;
	__vTOP_LEFT = MI->multiplyByVector(__vTOP_LEFT);
	__vTOP_RIGHT = MI->multiplyByVector(__vTOP_RIGHT);
	__vBOTTOM_LEFT = MI->multiplyByVector(__vBOTTOM_LEFT);
	__vBOTTOM_RIGHT = MI->multiplyByVector(__vBOTTOM_RIGHT);
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
	gl->bufferSubData(gl->ARRAY_BUFFER, 0, new Float32Array({__vTOP_LEFT->X, __vTOP_LEFT->Y, __vTOP_RIGHT->X, __vTOP_RIGHT->Y, __vBOTTOM_RIGHT->X, __vBOTTOM_RIGHT->Y, __vBOTTOM_LEFT->X, __vBOTTOM_LEFT->Y}));
	gl->vertexAttribPointer(scene->__boundingBoxProgram->GLSLiVec2Coords, 2, gl->FLOAT, false, 0, 0);
	scene->__projectionMatrix->update(gl, scene->__boundingBoxProgram->GLSLuProjMat);
	gl->drawArrays(gl->LINE_LOOP, 0, 4);
	gl->bindBuffer(gl->ARRAY_BUFFER, NULL);
	gl->disableVertexAttribArray(scene->__boundingBoxProgram->GLSLiVec2Coords);
	gl->useProgram(scene->__glProgram);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiTexCoords);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiVecCoords);
}
