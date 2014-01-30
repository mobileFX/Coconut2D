#include "CocoKeyFrame.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame::CocoKeyFrame()
{
	frameIndex = 0;
	__frameIndex = 0;
	frameInterpolation = COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN;
	handleEvents = false;
	visible = true;
	x = 0.0;
	y = 0.0;
	scaleX = 1.0;
	scaleY = 1.0;
	rotation = 0.0;
	pivotX = 0.0;
	pivotY = 0.0;
	red = 1.0;
	green = 1.0;
	blue = 1.0;
	alpha = 1.0;
	action = nullptr;
	nextState = nullptr;
	audio = nullptr;
	flipH = false;
	flipV = false;
	__isCloned = false;
	spriteSequenceName = "";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame::~CocoKeyFrame()
{
	if(audio && !__isCloned)
		if(audio)
		{
			audio = (delete audio, nullptr);
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoKeyFrame::clone(bool exact)
{
	CocoKeyFrame* c = new CocoKeyFrame();
	c->red = red;
	c->green = green;
	c->blue = blue;
	c->alpha = alpha;
	c->frameIndex = frameIndex;
	c->frameInterpolation = frameInterpolation;
	c->handleEvents = handleEvents;
	c->pivotX = pivotX;
	c->pivotY = pivotY;
	c->rotation = rotation;
	c->scaleX = scaleX;
	c->scaleY = scaleY;
	c->visible = visible;
	c->x = x;
	c->y = y;
	c->flipH = flipH;
	c->flipV = flipV;
	c->spriteSequenceName = spriteSequenceName;
	c->__frameIndex = float(frameIndex);
	c->__isCloned = true;
	if(exact && (action || nextState || audio))
	{
		c->action = action;
		c->nextState = nextState;
		c->audio = audio;
	}
	return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::reset()
{
	if(audio)
	{
		audio->reset();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::execute(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* clip)
{
	if(action)
	{
		engine->__trace(scene, clip, "@@ACTION");
		(scene->*action)(gl, scene, clip);
		//Array* args = {gl, clip, this};
		//action->apply(scene, args);
	}
	if(nextState)
	{
		engine->__trace(scene, clip, "@@NEXT_STATE");
		engine->setNextState(nextState);
	}
	if(audio)
	{
		engine->__trace(scene, clip, "@@AUDIO");
		audio->tick();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s)
{
	red = F1->red + s * (F2->red - F1->red);
	green = F1->green + s * (F2->green - F1->green);
	blue = F1->blue + s * (F2->blue - F1->blue);
	alpha = F1->alpha + s * (F2->alpha - F1->alpha);
	x = F1->x + s * (F2->x - F1->x);
	y = F1->y + s * (F2->y - F1->y);
	scaleX = F1->scaleX + s * (F2->scaleX - F1->scaleX);
	scaleY = F1->scaleY + s * (F2->scaleY - F1->scaleY);
	rotation = F1->rotation + s * (F2->rotation - F1->rotation);
	pivotX = F1->pivotX + s * (F2->pivotX - F1->pivotX);
	pivotY = F1->pivotY + s * (F2->pivotY - F1->pivotY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::combine(CocoKeyFrame* Frame)
{
	if(!Frame)
	{
		return;
	}
	red = red * Frame->red;
	green = green * Frame->green;
	blue = blue * Frame->blue;
	alpha = alpha * Frame->alpha;
	visible = visible && Frame->visible;
	flipH = (flipH && !Frame->flipH) || (!flipH && Frame->flipH);
	flipV = (flipV && !Frame->flipV) || (!flipV && Frame->flipV);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::apply(CocoMatrix* matrix)
{
	if(x != 0 || y != 0)
	{
		matrix->translate(x, y);
	}
	if(rotation != 0)
	{
		matrix->rotateZ(rotation * RADIANS);
	}
	if(scaleX != 1 || scaleY != 1)
	{
		matrix->scale(scaleX, scaleY);
	}
	if(pivotX != 0 || pivotY != 0)
	{
		matrix->translate(-pivotX,  -pivotY);
	}
}
