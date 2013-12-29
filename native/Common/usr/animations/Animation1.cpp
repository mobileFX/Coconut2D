#include "Animation1.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
Animation1::Animation1()
{
	__sceneName = "Animation1";
	__fps = 9;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* SpriteSymbol_metal_slug = newResourceImage("SpriteSymbol_metal_slug", "./assets/images/");
	{
		SpriteSymbol_metal_slug->viewOptimalWidth = 36;
		SpriteSymbol_metal_slug->viewOptimalHeight = 42;
		SpriteSymbol_metal_slug->addSibling(new CocoImageSibling("metal_slug_mdpi.png", 1, 36, 42));
		SpriteSymbol_metal_slug->addSibling(new CocoImageSibling("metal_slug_xhdpi.png", 2, 72, 84));
		SpriteSymbol_metal_slug->textureCellWidth = 36;
		SpriteSymbol_metal_slug->textureCellHeight = 42;
		SpriteSymbol_metal_slug->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8});
		SpriteSymbol_metal_slug->addSequence(new CocoSequence("Walk", {0, 1, 2, 3, 4, 5, 6, 7, 8}));
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	{
		CocoClip* inst1 = new CocoClip();
		inst1->__instanceName = "metal_slug1";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -179.5,  -111, 1, 1, 0, 0, 0, 1);
		{
			CocoClip* inst2 = new CocoClip(SpriteSymbol_metal_slug, NULL, "Walk");
			inst2->__instanceName = ":: SpriteSymbol_metal_slug";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
	}
}
