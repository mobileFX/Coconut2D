#include "NewAnimation.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
NewAnimation::NewAnimation()
{
	__sceneName = "NewAnimation";
	__fps = 30;
	__view_width = 0;
	__view_height = 0;
	__view_pixel_ratio = 0;
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
}
