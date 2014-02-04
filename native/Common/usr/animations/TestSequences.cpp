#include "TestSequences.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
TestSequences::TestSequences()
{
	__sceneName = String("TestSequences");
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* Image_SpriteSymbol_Sparrow = newResourceImage(String("SpriteSymbol_Sparrow"), String("./assets/images/"));
	{
		Image_SpriteSymbol_Sparrow->viewOptimalWidth = 0;
		Image_SpriteSymbol_Sparrow->viewOptimalHeight = 0;
		Image_SpriteSymbol_Sparrow->addSibling(new CocoImageSibling(String("Sparrow.png"), 1, 48, 48));
		Image_SpriteSymbol_Sparrow->textureCellWidth = 48;
		Image_SpriteSymbol_Sparrow->textureCellHeight = 48;
		Image_SpriteSymbol_Sparrow->textureGrid = new Float32Array(Array<float> ()(0)(0)(0)(1)(0)(2)(0)(3)(0)(4)(0)(5)(0)(6)(0)(7)(1)(0)(1)(1)(1)(2)(1)(3)(1)(4)(1)(5)(1)(6)(1)(7)(2)(0)(2)(1)(2)(2)(2)(3)(2)(4)(2)(5)(2)(6)(2)(7)(3)(0)(3)(1)(3)(2)(3)(3)(3)(4)(3)(5)(3)(6)(3)(7)(4)(0)(4)(1)(4)(2)(4)(3)(4)(4)(4)(5)(4)(6)(4)(7)(5)(0)(5)(1)(5)(2)(5)(3)(5)(4)(5)(5)(5)(6)(5)(7)(6)(0)(6)(1)(6)(2)(6)(3));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fly"), Array<int> ()(22)(23)(24)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fire"), Array<int> ()(25)(26)(27)(28)(29)(30)(31)(32)(33)(34)(35)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Die"), Array<int> ()(37)(38)(39)(40)(41)(42)(41)(42)(41)(42)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Eat"), Array<int> ()(0)(44)(44)(45)(45)(46)(46)(47)(47)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Burb"), Array<int> ()(0)(48)(48)(48)(49)(49)(49)(48)(48)(48)(49)(49)(49)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)(50)(51)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Borred"), Array<int> ()(0)(1)(2)(1)(0)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Jump"), Array<int> ()(10)(11)(12)(13)(12)(13)(12)(13)(12)(13)(12)(13)(12)(13)(12)(13)(12)(13)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Walk"), Array<int> ()(3)(4)(5)(6)(7)(8)(9)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Fall"), Array<int> ()(14)(15)));
		Image_SpriteSymbol_Sparrow->addSequence(new CocoSequence(String("Happy"), Array<int> ()(16)(17)(18)(19)(20)(21)));
	}
	__root = new CocoClip();
	__root->__instanceName = String("root");
	__root->__scene = this;
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst1 = new CocoClip(nullptr);
		inst1->__instanceName = String("Sparrows");
		__root->addChild(inst1);
		inst1->__scene = this;
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -188.5,  -30.00001, 1, 1, 0,  -157, 14, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst2 = new CocoClip(nullptr);
			inst2->__instanceName = String("ClipSymbol1");
			inst1->addChild(inst2);
			inst2->__scene = this;
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -155.75,  -65.99999, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
			{
				CocoClip* inst3 = new CocoClip(nullptr);
				inst3->__instanceName = String("Sparrow1");
				inst2->addChild(inst3);
				inst3->__scene = this;
				inst3->__timeline->clear();
				inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fly"));
				inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
				inst3->__timeline->addKeyFrameEx(nullptr, nullptr, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fire"));
				{
					CocoClip* inst4 = new CocoClip(Image_SpriteSymbol_Sparrow);
					inst4->__instanceName = String(":: SpriteSymbol_Sparrow");
					inst3->addChild(inst4);
					inst4->__scene = this;
					inst4->__timeline->clear();
					inst4->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
				}
			}
			CocoClip* inst5 = new CocoClip(nullptr);
			inst5->__instanceName = String("ClipSymbol2");
			inst1->addChild(inst5);
			inst5->__scene = this;
			inst5->__timeline->clear();
			inst5->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -154.75, 3.000015, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
			{
				CocoClip* inst6 = new CocoClip(nullptr);
				inst6->__instanceName = String("Sparrow1");
				inst5->addChild(inst6);
				inst6->__scene = this;
				inst6->__timeline->clear();
				inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fly"));
				inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
				inst6->__timeline->addKeyFrameEx(nullptr, nullptr, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fire"));
				{
					CocoClip* inst7 = new CocoClip(Image_SpriteSymbol_Sparrow);
					inst7->__instanceName = String(":: SpriteSymbol_Sparrow");
					inst6->addChild(inst7);
					inst7->__scene = this;
					inst7->__timeline->clear();
					inst7->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
				}
			}
			CocoClip* inst8 = new CocoClip(nullptr);
			inst8->__instanceName = String("ClipSymbol3");
			inst1->addChild(inst8);
			inst8->__scene = this;
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -162.25, 88.00002, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
			{
				CocoClip* inst9 = new CocoClip(nullptr);
				inst9->__instanceName = String("Sparrow1");
				inst8->addChild(inst9);
				inst9->__scene = this;
				inst9->__timeline->clear();
				inst9->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fly"));
				inst9->__timeline->addKeyFrameEx(nullptr, nullptr, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Walk"));
				inst9->__timeline->addKeyFrameEx(nullptr, nullptr, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String("Fire"));
				{
					CocoClip* inst10 = new CocoClip(Image_SpriteSymbol_Sparrow);
					inst10->__instanceName = String(":: SpriteSymbol_Sparrow");
					inst9->addChild(inst10);
					inst10->__scene = this;
					inst10->__timeline->clear();
					inst10->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, nullptr, false, false, String(""));
				}
			}
		}
	}
}
