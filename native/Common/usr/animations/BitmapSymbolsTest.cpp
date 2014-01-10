#include "BitmapSymbolsTest.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
BitmapSymbolsTest::BitmapSymbolsTest()
{
	__sceneName = "BitmapSymbolsTest";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* Image_SpriteSymbol_metal_slug = newResourceImage("SpriteSymbol_metal_slug", "./assets/images/");
	{
		Image_SpriteSymbol_metal_slug->viewOptimalWidth = 36;
		Image_SpriteSymbol_metal_slug->viewOptimalHeight = 42;
		Image_SpriteSymbol_metal_slug->addSibling(new CocoImageSibling("metal_slug_mdpi.png", 1, 36, 42));
		Image_SpriteSymbol_metal_slug->addSibling(new CocoImageSibling("metal_slug_xhdpi.png", 2, 72, 84));
		Image_SpriteSymbol_metal_slug->textureCellWidth = 36;
		Image_SpriteSymbol_metal_slug->textureCellHeight = 42;
		Image_SpriteSymbol_metal_slug->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8});
		Image_SpriteSymbol_metal_slug->addSequence(new CocoSequence("Walk", {0, 1, 2, 3, 4, 5, 6, 7, 8}));
	}
	CocoImage* Image_SpriteSymbol_Sparrow = newResourceImage("SpriteSymbol_Sparrow", "./assets/images/");
	{
		Image_SpriteSymbol_Sparrow->viewOptimalWidth = 48;
		Image_SpriteSymbol_Sparrow->viewOptimalHeight = 48;
		Image_SpriteSymbol_Sparrow->addSibling(new CocoImageSibling("Sparrow.png", 1, 48, 48));
		Image_SpriteSymbol_Sparrow->textureCellWidth = 48;
		Image_SpriteSymbol_Sparrow->textureCellHeight = 48;
		Image_SpriteSymbol_Sparrow->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 3, 0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 4, 7, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 5, 6, 5, 7, 6, 0, 6, 1, 6, 2, 6, 3});
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Fly", {22, 23, 24}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Fire", {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Die", {37, 38, 39, 40, 41, 42, 41, 42, 41, 42}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Eat", {0, 44, 44, 45, 45, 46, 46, 47, 47}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Burb", {0, 48, 48, 48, 49, 49, 49, 48, 48, 48, 49, 49, 49, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Borred", {0, 1, 2, 1, 0}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Jump", {10, 11, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Walk", {3, 4, 5, 6, 7, 8, 9}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Fall", {14, 15}));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence("Happy", {16, 17, 18, 19, 20, 21}));
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
	{
		CocoClip* inst1 = new CocoClip(nullptr, "");
		inst1->__instanceName = "metal_slug1";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -207.5,  -116.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst2 = new CocoClip(Image_SpriteSymbol_metal_slug, "Walk");
			inst2->__instanceName = ":: SpriteSymbol_metal_slug";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 38, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
		CocoClip* inst3 = new CocoClip(nullptr, "");
		inst3->__instanceName = "metal_slug3";
		__root->addChild(inst3);
		inst3->__timeline->clear();
		inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -174,  -30.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst4 = new CocoClip(Image_SpriteSymbol_metal_slug, "Walk");
			inst4->__instanceName = ":: SpriteSymbol_metal_slug";
			inst3->addChild(inst4);
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
		CocoClip* inst5 = new CocoClip(nullptr, "");
		inst5->__instanceName = "metal_slug4";
		__root->addChild(inst5);
		inst5->__timeline->clear();
		inst5->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -30.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst6 = new CocoClip(Image_SpriteSymbol_metal_slug, "Walk");
			inst6->__instanceName = ":: SpriteSymbol_metal_slug";
			inst5->addChild(inst6);
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
		CocoClip* inst7 = new CocoClip(nullptr, "");
		inst7->__instanceName = "Sparrow1";
		__root->addChild(inst7);
		inst7->__timeline->clear();
		inst7->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -180.5, 47.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst8 = new CocoClip(Image_SpriteSymbol_Sparrow, "Fly");
			inst8->__instanceName = ":: SpriteSymbol_Sparrow";
			inst7->addChild(inst8);
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
		CocoClip* inst9 = new CocoClip(nullptr, "");
		inst9->__instanceName = "Sparrow2";
		__root->addChild(inst9);
		inst9->__timeline->clear();
		inst9->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -102.5, 47.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst10 = new CocoClip(Image_SpriteSymbol_Sparrow, "Fly");
			inst10->__instanceName = ":: SpriteSymbol_Sparrow";
			inst9->addChild(inst10);
			inst10->__timeline->clear();
			inst10->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
		CocoClip* inst11 = new CocoClip(nullptr, "");
		inst11->__instanceName = "Sparrow3";
		__root->addChild(inst11);
		inst11->__timeline->clear();
		inst11->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -100.5,  -121.5, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		{
			CocoClip* inst12 = new CocoClip(Image_SpriteSymbol_Sparrow, "Walk");
			inst12->__instanceName = ":: SpriteSymbol_Sparrow";
			inst11->addChild(inst12);
			inst12->__timeline->clear();
			inst12->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, nullptr, false, false);
		}
	}
}
