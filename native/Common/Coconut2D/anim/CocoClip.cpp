#include "CocoClip.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip::CocoClip(CocoImage* image)
{
	__symbolLoop = COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS;
	__timeline = new CocoTimeline();
	__parent = nullptr;
	__currentTime = 0.0;
	__currentFrame = nullptr;
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
	__childWithMaxTimelineDuration = nullptr;
	__currentSequence = nullptr;
	__currentAudio = nullptr;
	__clipPath = "";
	__image = image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip::~CocoClip()
{
	if(__image)
	{
		__image = (delete __image, nullptr);
	}
	if(__timeline)
	{
		__timeline = (delete __timeline, nullptr);
	}
	if(__vABS_TOP_LEFT)
	{
		__vABS_TOP_LEFT = (delete __vABS_TOP_LEFT, nullptr);
	}
	if(__vABS_TOP_RIGHT)
	{
		__vABS_TOP_RIGHT = (delete __vABS_TOP_RIGHT, nullptr);
	}
	if(__vABS_BOTTOM_LEFT)
	{
		__vABS_BOTTOM_LEFT = (delete __vABS_BOTTOM_LEFT, nullptr);
	}
	if(__vABS_BOTTOM_RIGHT)
	{
		__vABS_BOTTOM_RIGHT = (delete __vABS_BOTTOM_RIGHT, nullptr);
	}
	if(__vREL_TOP_LEFT)
	{
		__vREL_TOP_LEFT = (delete __vREL_TOP_LEFT, nullptr);
	}
	if(__vREL_TOP_RIGHT)
	{
		__vREL_TOP_RIGHT = (delete __vREL_TOP_RIGHT, nullptr);
	}
	if(__vREL_BOTTOM_LEFT)
	{
		__vREL_BOTTOM_LEFT = (delete __vREL_BOTTOM_LEFT, nullptr);
	}
	if(__vREL_BOTTOM_RIGHT)
	{
		__vREL_BOTTOM_RIGHT = (delete __vREL_BOTTOM_RIGHT, nullptr);
	}
	if(__vTemp)
	{
		__vTemp = (delete __vTemp, nullptr);
	}
	if(__mTemp)
	{
		__mTemp = (delete __mTemp, nullptr);
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
void CocoClip::createTextTexture(String text, String fontName, int fontSizePixels, COCO_TEXT_ALIGN_ENUM hAlign, COCO_TEXT_ALIGN_ENUM vAlign, bool multiline, COCO_TEXT_TRIMMING_ENUM trimming, String CSSColor, int textRectWidth, int textRectHeight)
{
	if(__image)
	{
		__image = (delete __image, nullptr);
	}
	HTMLCanvasElement* canvas = document->createElement("canvas");
	canvas->width = int(pow(2, ceil((float)(log(textRectWidth)) / (float)(log(2)))));
	canvas->height = int(pow(2, ceil((float)(log(textRectHeight)) / (float)(log(2)))));
	CanvasRenderingContext2D* ctx = (CanvasRenderingContext2D*)canvas->getContext("2d");
	ctx->__font = new CocoFont(fontSizePixels, fontName, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()/.,?><';\":]|[}{\\}]`~");//"normal normal normal " + std::to_string(fontSizePixels) + "px / normal " + fontName;
	ctx->__fillStyle = "red";
	ctx->fillText(text, 0, float(fontSizePixels));
	ctx->strokeRect(0, 0, float(textRectWidth), float(textRectHeight));
	__image = new CocoImage();
	__image->image = new Image();
	__image->image->load(canvas->toDataURL());
	__image->textureCellWidth = float(textRectWidth);
	__image->textureCellHeight = float(textRectHeight);
	__image->textureGrid = new Float32Array({0, 0});
	__image->prepare(__scene, gl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::reset()
{
	if(__currentFrame)
		if(__currentFrame)
		{
			__currentFrame = (delete __currentFrame, nullptr);
		}
	__currentFrame = nullptr;
	__currentTime = 0.0;
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
		return nullptr;
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
		return nullptr;
	}
	__children.splice(getChildIndex(clipInstance), 1);
	normalize();
	return clipInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::normalize()
{
	__childWithMaxTimelineDuration = nullptr;
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
	return nullptr;
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
		clip->__timeline->__paused = pause;
		if(FrameIndex != COCO_STOP_ON_CURRENT_FRAME)
		{
			clip->__currentTime = Time(FrameIndex) * clip->__timeline->__singleFrameDurationTime;
		}
		if(deep)
		{
			clip->gotoFrameByIndex(COCO_STOP_ON_CURRENT_FRAME, pause, deep);
		}
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::paint(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, bool calcBoundingBox, int level)
{
	__scene = scene;
	__clipPath = (parentClip ? parentClip->__clipPath : "") + "/" + this->__instanceName;
	if(parentClip)
	{
		Time parentClipsDuration = parentClip->__childWithMaxTimelineDuration->__timeline->__durationInTime;
		Time __loopTime = __currentTime - std::floor((float)(__currentTime) / (float)(parentClipsDuration)) * parentClipsDuration;
		float frameIndex = ((float)(__loopTime) / (float)(__timeline->__singleFrameDurationTime));
		if(__currentFrame)
			if(__currentFrame)
			{
				__currentFrame = (delete __currentFrame, nullptr);
			}
		__currentFrame = __timeline->interpolate(frameIndex);
		__currentFrame->combine(parentClip->__currentFrame);
		if(__currentFrame->alpha == 0 || !__currentFrame->visible)
		{
			if(!__timeline->__paused)
			{
				__currentTime += engine->TICK_TIME;
			}
			return;
		}
		calcBoundingBox = (__currentFrame->handleEvents || calcBoundingBox) && (engine->getTouchEvent() != nullptr);
	}
	if(__image)
	{
		__currentFrame->scaleX *= __image->__pixelRatioScale;
		__currentFrame->scaleY *= __image->__pixelRatioScale;
		__currentFrame->apply(scene->__modelViewMatrix);
		__currentFrame->scaleX /= __image->__pixelRatioScale;
		__currentFrame->scaleY /= __image->__pixelRatioScale;
		String sequenceName = parentClip && parentClip->__currentFrame ? parentClip->__currentFrame->spriteSequenceName : "";
		if(!sequenceName)
		{
			__currentSequence = nullptr;
		}
		else if(!__currentSequence || (__currentSequence && __currentSequence->name != sequenceName))
		{
			__currentSequence = __image->getSequence(sequenceName);
			__currentSequence->sequenceStartTime = __currentTime;
		}
		if(__image->isSpriteSheet && __currentSequence)
		{
			int sequenceFrameIndex = __timeline->__paused ? 0 : (int)std::floor((float)((__currentTime - __currentSequence->sequenceStartTime)) / (float)(((float)(1000.0) / (float)(scene->__fps)))) % (int)__currentSequence->frames.size();
			int frame = __currentSequence->frames[sequenceFrameIndex];
			scene->drawFrame(gl, __image, frame, __currentFrame->red, __currentFrame->green, __currentFrame->blue, __currentFrame->alpha, __currentFrame->flipH, __currentFrame->flipV);
		}
		else
		{
			scene->drawFrame(gl, __image, 0, __currentFrame->red, __currentFrame->green, __currentFrame->blue, __currentFrame->alpha, __currentFrame->flipH, __currentFrame->flipV);
		}
	}
	else
	{
		int childrenCound = __children.size();
		if(childrenCound > 0)
		{
			CocoClip* child;
			scene->__levelParents.push(this);
			if(__currentFrame)
			{
				__currentFrame->apply(scene->__modelViewMatrix);
			}
			for(int i = 0; i < childrenCound; i++)
			{
				scene->__modelViewMatrix->push();
				child = __children[i];
				child->paint(gl, scene, this, calcBoundingBox, level + 1);
				scene->__modelViewMatrix->pop();
			}
			scene->__levelParents.pop();
		}
	}
	if(this != scene->__root)
	{
		if(calcBoundingBox)
		{
			if(__image)
			{
				initBoundingBoxFromTexture(scene, (float)(__image->textureCellWidth) / (float)(2), (float)(__image->textureCellHeight) / (float)(2));
			}
			else if(__children.size() > 0)
			{
				initBoundingBoxFromChildren(scene);
			}
		}
		DeviceEvent* touchEvent = engine->getTouchEvent();
		if(__currentFrame->handleEvents && touchEvent && touchEvent->type == "touchend")
		{
			Number x = (float)((touchEvent->__clientX - (float)(gl->canvas->width) / (float)(2.0))) / (float)(scene->__view_scale);
			Number y = (float)((touchEvent->__clientY - (float)(gl->canvas->height) / (float)(2.0))) / (float)(scene->__view_scale);
			if(hitTest(x, y))
			{
				engine->pushTouched(this);
			}
		}
		if(!__timeline->__paused)
		{
			bool pulse = false;
			if(__currentFrame->action || __currentFrame->nextState || __currentFrame->audio)
			{
				this->__parent = parentClip;
				pulse = __currentFrame->execute(gl, scene, this);
				if(pulse && __currentFrame->audio)
				{
					__currentAudio = __currentFrame->audio;
				}
				this->__parent = nullptr;
			}
		}
		if(__currentAudio)
		{
			__currentAudio->tick();
		}
	}
	if(!__timeline->__paused)
	{
		__currentTime += engine->TICK_TIME;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoClip::setText(String text)
{
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
	__vREL_TOP_LEFT->X = 100000;
	__vREL_TOP_RIGHT->X = -100000;
	__vREL_TOP_LEFT->Y = 100000;
	__vREL_BOTTOM_LEFT->Y = -100000;
	CocoClip* Child;
	for(int i = 0,  L = __children.size(); i < L; i++)
	{
		Child = __children[i];
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
	gl->bindBuffer(gl->ARRAY_BUFFER, nullptr);
	gl->disableVertexAttribArray(scene->__boundingBoxProgram->GLSLiVec2Coords);
	gl->useProgram(scene->__glProgram);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiTexCoords);
	gl->enableVertexAttribArray(scene->__glProgram->GLSLiVecCoords);
}
