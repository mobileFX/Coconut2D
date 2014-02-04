#include "SceneTitle.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
SceneTitle::SceneTitle()
{
	__sceneName = String("SceneTitle");
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* Image_INTRO_PAPYRI = newResourceImage(String("INTRO_PAPYRI"), String("./assets/images/"));
	{
		Image_INTRO_PAPYRI->viewOptimalWidth = 0;
		Image_INTRO_PAPYRI->viewOptimalHeight = 0;
		Image_INTRO_PAPYRI->addSibling(new CocoImageSibling(String("INTRO_PAPYRI_mdpi.png"), 1, 1024, 768));
		Image_INTRO_PAPYRI->addSibling(new CocoImageSibling(String("INTRO_PAPYRI_xhdpi.png"), 2, 2048, 1536));
		Image_INTRO_PAPYRI->textureCellWidth = 1024;
		Image_INTRO_PAPYRI->textureCellHeight = 768;
		Image_INTRO_PAPYRI->textureGrid = new Float32Array(Array<float> ()(0)(0));
	}
	CocoImage* Image_INTRO_SHIELD = newResourceImage(String("INTRO_SHIELD"), String("./assets/images/"));
	{
		Image_INTRO_SHIELD->viewOptimalWidth = 0;
		Image_INTRO_SHIELD->viewOptimalHeight = 0;
		Image_INTRO_SHIELD->addSibling(new CocoImageSibling(String("INTRO_SHIELD_mdpi.png"), 1, 1024, 768));
		Image_INTRO_SHIELD->addSibling(new CocoImageSibling(String("INTRO_SHIELD_xhdpi.png"), 2, 2048, 1536));
		Image_INTRO_SHIELD->textureCellWidth = 1024;
		Image_INTRO_SHIELD->textureCellHeight = 768;
		Image_INTRO_SHIELD->textureGrid = new Float32Array(Array<float> ()(0)(0));
	}
	CocoImage* Image_title_screen = newResourceImage(String("title_screen"), String("./assets/images/"));
	{
		Image_title_screen->viewOptimalWidth = 0;
		Image_title_screen->viewOptimalHeight = 0;
		Image_title_screen->addSibling(new CocoImageSibling(String("title_screen_mdpi.png"), 1, 1024, 768));
		Image_title_screen->addSibling(new CocoImageSibling(String("title_screen_xhdpi.png"), 2, 2048, 1536));
		Image_title_screen->textureCellWidth = 1024;
		Image_title_screen->textureCellHeight = 768;
		Image_title_screen->textureGrid = new Float32Array(Array<float> ()(0)(0));
	}
	CocoImage* Image_TITLE_SCREEN_LOGO = newResourceImage(String("TITLE_SCREEN_LOGO"), String("./assets/images/"));
	{
		Image_TITLE_SCREEN_LOGO->viewOptimalWidth = 0;
		Image_TITLE_SCREEN_LOGO->viewOptimalHeight = 0;
		Image_TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling(String("TITLE_SCREEN_LOGO_mdpi.png"), 1, 542, 638));
		Image_TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling(String("TITLE_SCREEN_LOGO_xhdpi.png"), 2, 1084, 1276));
		Image_TITLE_SCREEN_LOGO->textureCellWidth = 542;
		Image_TITLE_SCREEN_LOGO->textureCellHeight = 638;
		Image_TITLE_SCREEN_LOGO->textureGrid = new Float32Array(Array<float> ()(0)(0));
	}
	__root = new CocoClip();
	__root->__instanceName = String("root");
	__root->__scene = this;
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst1 = new CocoClip(nullptr);
		inst1->__instanceName = String("wooshSound");
		__root->addChild(inst1);
		inst1->__scene = this;
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 4, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, new CocoAudio(String("./assets/sounds/Fast woosh.ogg"), true, 1), false, false, String(""));
		CocoClip* inst2 = new CocoClip(nullptr);
		inst2->__instanceName = String("IntroBackground");
		__root->addChild(inst2);
		inst2->__scene = this;
		inst2->__timeline->clear();
		inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 2, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 95, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 0, nullptr, false, false, String(""));
		{
			CocoClip* inst3 = new CocoClip(Image_INTRO_PAPYRI);
			inst3->__instanceName = String(":: Intro_Background");
			inst2->addChild(inst3);
			inst3->__scene = this;
			inst3->__timeline->clear();
			inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst4 = new CocoClip(nullptr);
		inst4->__instanceName = String("IntroShield");
		__root->addChild(inst4);
		inst4->__scene = this;
		inst4->__timeline->clear();
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.008594, 0.008594, 0, 0, 0, 2, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 18, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.508594, 0.508594, 0, 0, 0, 2, 1, 1, 1, 0.7, nullptr, false, false, String(""));
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 24, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 89, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 0.408594, 0.408594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst5 = new CocoClip(Image_INTRO_SHIELD);
			inst5->__instanceName = String(":: Intro_Shield");
			inst4->addChild(inst5);
			inst5->__scene = this;
			inst5->__timeline->clear();
			inst5->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst6 = new CocoClip(nullptr);
		inst6->__instanceName = String("TitleScreenBackground");
		__root->addChild(inst6);
		inst6->__scene = this;
		inst6->__timeline->clear();
		inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 2, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 214, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 223, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0, 1, 1, 1, 0, nullptr, false, false, String(""));
		{
			CocoClip* inst7 = new CocoClip(Image_title_screen);
			inst7->__instanceName = String(":: TitleScreen_Background");
			inst6->addChild(inst7);
			inst7->__scene = this;
			inst7->__timeline->clear();
			inst7->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst8 = new CocoClip(nullptr);
		inst8->__instanceName = String("Logo");
		__root->addChild(inst8);
		inst8->__scene = this;
		inst8->__timeline->clear();
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.458594, 0.458594, 0, 0, 0, 2, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 18, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.208594, 0.208594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 24, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -10, 0.308594, 0.308594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.308594, 0.308594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 116, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 125, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 135, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 145, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 155, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 164, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 174, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 183, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 193, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 202, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 212, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 223, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 0, 0, 0, 0, 1, 1, 1, 0, nullptr, false, false, String(""));
		{
			CocoClip* inst9 = new CocoClip(Image_TITLE_SCREEN_LOGO);
			inst9->__instanceName = String(":: Logo");
			inst8->addChild(inst9);
			inst9->__scene = this;
			inst9->__timeline->clear();
			inst9->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
	}
}
