#include "SceneTitle.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
SceneTitle::SceneTitle()
{
	__sceneName = "SceneTitle";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* INTRO_PAPYRI = newResourceImage("INTRO_PAPYRI", "./assets/images/");
	{
		INTRO_PAPYRI->viewOptimalWidth = 572;
		INTRO_PAPYRI->viewOptimalHeight = 429;
		INTRO_PAPYRI->addSibling(new CocoImageSibling("INTRO_PAPYRI_mdpi.png", 1, 1024, 768));
		INTRO_PAPYRI->addSibling(new CocoImageSibling("INTRO_PAPYRI_xhdpi.png", 2, 2048, 1536));
		INTRO_PAPYRI->textureCellWidth = 1024;
		INTRO_PAPYRI->textureCellHeight = 768;
		INTRO_PAPYRI->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* INTRO_SHIELD = newResourceImage("INTRO_SHIELD", "./assets/images/");
	{
		INTRO_SHIELD->viewOptimalWidth = 521;
		INTRO_SHIELD->viewOptimalHeight = 391;
		INTRO_SHIELD->addSibling(new CocoImageSibling("INTRO_SHIELD_mdpi.png", 1, 1024, 768));
		INTRO_SHIELD->addSibling(new CocoImageSibling("INTRO_SHIELD_xhdpi.png", 2, 2048, 1536));
		INTRO_SHIELD->textureCellWidth = 1024;
		INTRO_SHIELD->textureCellHeight = 768;
		INTRO_SHIELD->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* title_screen = newResourceImage("title_screen", "./assets/images/");
	{
		title_screen->viewOptimalWidth = 572;
		title_screen->viewOptimalHeight = 429;
		title_screen->addSibling(new CocoImageSibling("title_screen_mdpi.png", 1, 1024, 768));
		title_screen->addSibling(new CocoImageSibling("title_screen_xhdpi.png", 2, 2048, 1536));
		title_screen->textureCellWidth = 1024;
		title_screen->textureCellHeight = 768;
		title_screen->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* TITLE_SCREEN_LOGO = newResourceImage("TITLE_SCREEN_LOGO", "./assets/images/");
	{
		TITLE_SCREEN_LOGO->viewOptimalWidth = 257;
		TITLE_SCREEN_LOGO->viewOptimalHeight = 293;
		TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling("TITLE_SCREEN_LOGO_mdpi.png", 1, 561, 638));
		TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling("TITLE_SCREEN_LOGO_xhdpi.png", 2, 1122, 1276));
		TITLE_SCREEN_LOGO->textureCellWidth = 561;
		TITLE_SCREEN_LOGO->textureCellHeight = 638;
		TITLE_SCREEN_LOGO->textureGrid = new Float32Array({0, 0});
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	{
		CocoClip* inst1 = new CocoClip();
		inst1->__instanceName = "inst1_INTRO_PAPYRI";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 1);
		inst1->__timeline->addKeyFrameEx(NULL, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 1);
		inst1->__timeline->addKeyFrameEx(NULL, 95, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0);
		inst1->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0);
		{
			CocoClip* inst2 = new CocoClip(INTRO_PAPYRI, NULL, NULL);
			inst2->__instanceName = ":: INTRO_PAPYRI";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst3 = new CocoClip();
		inst3->__instanceName = "inst1_INTRO_SHIELD";
		__root->addChild(inst3);
		inst3->__timeline->clear();
		inst3->__timeline->addKeyFrameEx(NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.008594, 0.008594, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 18, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.508594, 0.508594, 0, 0, 0, 0.7);
		inst3->__timeline->addKeyFrameEx(NULL, 24, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.408594, 0.408594, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 89, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 0.408594, 0.408594, 0, 0, 0, 1);
		{
			CocoClip* inst4 = new CocoClip(INTRO_SHIELD, NULL, NULL);
			inst4->__instanceName = ":: INTRO_SHIELD";
			inst3->addChild(inst4);
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst5 = new CocoClip();
		inst5->__instanceName = "inst1_title_screen";
		__root->addChild(inst5);
		inst5->__timeline->clear();
		inst5->__timeline->addKeyFrameEx(NULL, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0);
		inst5->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 1);
		inst5->__timeline->addKeyFrameEx(NULL, 214, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 1);
		inst5->__timeline->addKeyFrameEx(NULL, 223, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.558594, 0.558594, 0, 0, 0, 0);
		{
			CocoClip* inst6 = new CocoClip(title_screen, NULL, NULL);
			inst6->__instanceName = ":: title_screen";
			inst5->addChild(inst6);
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst7 = new CocoClip();
		inst7->__instanceName = "inst1_TITLE_SCREEN_LOGO";
		__root->addChild(inst7);
		inst7->__timeline->clear();
		inst7->__timeline->addKeyFrameEx(NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.458594, 0.458594, 0, 0, 0, 0);
		inst7->__timeline->addKeyFrameEx(NULL, 18, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.208594, 0.208594, 0, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 24, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -10, 0.308594, 0.308594, 0, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 88, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.308594, 0.308594, 0, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 0, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 116, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 125, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 135, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 145, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 155, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 164, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 174, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 183, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 193, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 202, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594,  -5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 212, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 5, 0, 0, 1);
		inst7->__timeline->addKeyFrameEx(NULL, 223, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 168,  -79, 0.258594, 0.258594, 0, 0, 0, 0);
		{
			CocoClip* inst8 = new CocoClip(TITLE_SCREEN_LOGO, NULL, NULL);
			inst8->__instanceName = ":: TITLE_SCREEN_LOGO";
			inst7->addChild(inst8);
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
	}
}
