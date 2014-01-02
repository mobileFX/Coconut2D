#include "CocoKeyFrame.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame::CocoKeyFrame()
{
	frameIndex = 0;
	frameInterpolation = COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN;
	handleEvents = false;
	calcBoundingBox = false;
	visible = true;
	x = 0.0;
	y = 0.0;
	scaleX = 1.0;
	scaleY = 1.0;
	rotation = 0.0;
	pivotX = 0.0;
	pivotY = 0.0;
	alpha = 1.0;
	action = NULL;
	__lastActionExecutionTime = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame::~CocoKeyFrame()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoKeyFrame* CocoKeyFrame::clone()
{
	CocoKeyFrame* c = new CocoKeyFrame();
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
	c->action = action;
	c->calcBoundingBox = calcBoundingBox;
	c->__lastActionExecutionTime = __lastActionExecutionTime;
	return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::reset()
{
	__lastActionExecutionTime = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::execute(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoScene* scene, CocoClip* clip)
{
	if((currentTime == 0) || (currentTime - __lastActionExecutionTime > clip->__timeline->__singleFrameDurationTime))
	{
		__lastActionExecutionTime = currentTime;
		if(action)
		{
			Array* args = {gl, currentTime, loopTime, clip, this};
			action->apply(scene, args);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoKeyFrame::interpolate(CocoKeyFrame* F1, CocoKeyFrame* F2, float s)
{
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
	alpha = alpha * Frame->alpha;
	visible = visible && Frame->visible;
	handleEvents = handleEvents && Frame->handleEvents;
	calcBoundingBox = calcBoundingBox && Frame->calcBoundingBox;
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
