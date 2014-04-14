#include "NewAnimation.hpp"
#include "CocoImage.hpp"
#include "CocoClip.hpp"
#include "CocoImageSibling.hpp"
#include "CocoSequence.hpp"
#include "TypedArray.hpp"
#include "CocoTimeline.hpp"
#include "CocoKeyFrame.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
NewAnimation::NewAnimation()
{
	__sceneName = String("NewAnimation");
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* Image_SpriteSymbol_metal_slug = newResourceImage(String("SpriteSymbol_metal_slug"), String("./images/"));
	{
		Image_SpriteSymbol_metal_slug->viewOptimalWidth = 36;
		Image_SpriteSymbol_metal_slug->viewOptimalHeight = 42;
		Image_SpriteSymbol_metal_slug->addSibling(new CocoImageSibling(String("metal_slug_mdpi.png"), 1, 36, 42));
		Image_SpriteSymbol_metal_slug->addSibling(new CocoImageSibling(String("metal_slug_xhdpi.png"), 2, 72, 84));
		Image_SpriteSymbol_metal_slug->textureCellWidth = 36;
		Image_SpriteSymbol_metal_slug->textureCellHeight = 42;
		Image_SpriteSymbol_metal_slug->textureGrid = new Float32Array((new Array<float> ())->push(0)->push(0)->push(0)->push(1)->push(0)->push(2)->push(0)->push(3)->push(0)->push(4)->push(0)->push(5)->push(0)->push(6)->push(0)->push(7)->push(0)->push(8));
		Image_SpriteSymbol_metal_slug->addSequence(new CocoSequence(String("Walk"), (new Array<int> ())->push(0)->push(1)->push(2)->push(3)->push(4)->push(5)->push(6)->push(7)->push(8)));
	}
	CocoImage* Image_SpriteSymbol_Sparrow = newResourceImage(String("SpriteSymbol_Sparrow"), String("./images/"));
	{
		Image_SpriteSymbol_Sparrow->viewOptimalWidth = 48;
		Image_SpriteSymbol_Sparrow->viewOptimalHeight = 48;
		Image_SpriteSymbol_Sparrow->addSibling(new CocoImageSibling(String("Sparrow.png"), 1, 48, 48));
		Image_SpriteSymbol_Sparrow->textureCellWidth = 48;
		Image_SpriteSymbol_Sparrow->textureCellHeight = 48;
		Image_SpriteSymbol_Sparrow->textureGrid = new Float32Array((new Array<float> ())->push(0)->push(0)->push(0)->push(1)->push(0)->push(2)->push(0)->push(3)->push(0)->push(4)->push(0)->push(5)->push(0)->push(6)->push(0)->push(7)->push(1)->push(0)->push(1)->push(1)->push(1)->push(2)->push(1)->push(3)->push(1)->push(4)->push(1)->push(5)->push(1)->push(6)->push(1)->push(7)->push(2)->push(0)->push(2)->push(1)->push(2)->push(2)->push(2)->push(3)->push(2)->push(4)->push(2)->push(5)->push(2)->push(6)->push(2)->push(7)->push(3)->push(0)->push(3)->push(1)->push(3)->push(2)->push(3)->push(3)->push(3)->push(4)->push(3)->push(5)->push(3)->push(6)->push(3)->push(7)->push(4)->push(0)->push(4)->push(1)->push(4)->push(2)->push(4)->push(3)->push(4)->push(4)->push(4)->push(5)->push(4)->push(6)->push(4)->push(7)->push(5)->push(0)->push(5)->push(1)->push(5)->push(2)->push(5)->push(3)->push(5)->push(4)->push(5)->push(5)->push(5)->push(6)->push(5)->push(7)->push(6)->push(0)->push(6)->push(1)->push(6)->push(2)->push(6)->push(3));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fly"), (new Array<int> ())->push(22)->push(23)->push(24)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fire"), (new Array<int> ())->push(25)->push(26)->push(27)->push(28)->push(29)->push(30)->push(31)->push(32)->push(33)->push(34)->push(35)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Die"), (new Array<int> ())->push(37)->push(38)->push(39)->push(40)->push(41)->push(42)->push(41)->push(42)->push(41)->push(42)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Eat"), (new Array<int> ())->push(0)->push(44)->push(44)->push(45)->push(45)->push(46)->push(46)->push(47)->push(47)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Burb"), (new Array<int> ())->push(0)->push(48)->push(48)->push(48)->push(49)->push(49)->push(49)->push(48)->push(48)->push(48)->push(49)->push(49)->push(49)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)->push(50)->push(51)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Borred"), (new Array<int> ())->push(0)->push(1)->push(2)->push(1)->push(0)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Jump"), (new Array<int> ())->push(10)->push(11)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)->push(12)->push(13)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Walk"), (new Array<int> ())->push(3)->push(4)->push(5)->push(6)->push(7)->push(8)->push(9)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fall"), (new Array<int> ())->push(14)->push(15)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Happy"), (new Array<int> ())->push(16)->push(17)->push(18)->push(19)->push(20)->push(21)));
	}
	__root = new CocoClip();
	__root->__instanceName = String("root");
	__root->__scene = this;
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst1 = new CocoClip(nullptr);
		inst1->__instanceName = String("metal_slug1");
		__root->addChild(inst1);
		inst1->__scene = this;
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -171.5,  -59.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 189.5, 5.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
		{
			CocoClip* inst2 = new CocoClip(Image_SpriteSymbol_metal_slug);
			inst2->__instanceName = String(":: SpriteSymbol_metal_slug");
			inst1->addChild(inst2);
			inst2->__scene = this;
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst3 = new CocoClip(nullptr);
		inst3->__instanceName = String("Sparrow1");
		__root->addChild(inst3);
		inst3->__scene = this;
		inst3->__timeline->clear();
		inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -167.5, 54.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
		inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 193.5, 119.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
		{
			CocoClip* inst4 = new CocoClip(Image_SpriteSymbol_Sparrow);
			inst4->__instanceName = String(":: SpriteSymbol_Sparrow");
			inst3->addChild(inst4);
			inst4->__scene = this;
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst5 = new CocoClip(nullptr);
		inst5->__instanceName = String("metal_slug2");
		__root->addChild(inst5);
		inst5->__scene = this;
		inst5->__timeline->clear();
		inst5->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 103.5,  -67.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst6 = new CocoClip(Image_SpriteSymbol_metal_slug);
			inst6->__instanceName = String(":: SpriteSymbol_metal_slug");
			inst5->addChild(inst6);
			inst6->__scene = this;
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst7 = new CocoClip(nullptr);
		inst7->__instanceName = String("Sparrow2");
		__root->addChild(inst7);
		inst7->__scene = this;
		inst7->__timeline->clear();
		inst7->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 105.5, 45.5, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst8 = new CocoClip(Image_SpriteSymbol_Sparrow);
			inst8->__instanceName = String(":: SpriteSymbol_Sparrow");
			inst7->addChild(inst8);
			inst8->__scene = this;
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
	}
}
