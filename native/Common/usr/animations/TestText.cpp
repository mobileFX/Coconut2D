#include "TestText.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
TestText::TestText()
{
	__sceneName = String("TestText");
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	__root = new CocoClip();
	__root->__instanceName = String("root");
	__root->__scene = this;
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst1 = new CocoClip(nullptr);
		inst1->__instanceName = String("Text1");
		__root->addChild(inst1);
		inst1->__scene = this;
		inst1->createTextTexture(String("Text"), String("Helvetica"), 24, COCO_TEXT_ALIGN_ENUM::TEXT_ALIGN_NEAR, COCO_TEXT_ALIGN_ENUM::TEXT_ALIGN_NEAR, false, COCO_TEXT_TRIMMING_ENUM::StringTrimmingNone, String(""), 144, 125);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -107.5, 49, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
	}
}
