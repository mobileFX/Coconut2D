#include "SceneTitle.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
SceneTitle::SceneTitle()
{
	__sceneName = "SceneTitle";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* ImageSymbol_Background = newResourceImage("ImageSymbol_Background", "./assets/images/");
	{
		ImageSymbol_Background->viewOptimalWidth = 568;
		ImageSymbol_Background->viewOptimalHeight = 360;
		ImageSymbol_Background->addSibling(new CocoImageSibling("Background_mdpi.png", 1, 1136, 720));
		ImageSymbol_Background->addSibling(new CocoImageSibling("Background_xhdpi.png", 2, 2272, 1440));
		ImageSymbol_Background->textureCellWidth = 1136;
		ImageSymbol_Background->textureCellHeight = 720;
		ImageSymbol_Background->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_RedLaserSingle = newResourceImage("ImageSymbol_RedLaserSingle", "./assets/images/");
	{
		ImageSymbol_RedLaserSingle->viewOptimalWidth = 915;
		ImageSymbol_RedLaserSingle->viewOptimalHeight = 83;
		ImageSymbol_RedLaserSingle->addSibling(new CocoImageSibling("RedLaserSingle_mdpi.png", 1, 915, 83));
		ImageSymbol_RedLaserSingle->addSibling(new CocoImageSibling("RedLaserSingle_xhdpi.png", 2, 1829, 165));
		ImageSymbol_RedLaserSingle->textureCellWidth = 915;
		ImageSymbol_RedLaserSingle->textureCellHeight = 83;
		ImageSymbol_RedLaserSingle->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_BankJobLogo = newResourceImage("ImageSymbol_BankJobLogo", "./assets/images/");
	{
		ImageSymbol_BankJobLogo->viewOptimalWidth = 212;
		ImageSymbol_BankJobLogo->viewOptimalHeight = 118;
		ImageSymbol_BankJobLogo->addSibling(new CocoImageSibling("BankJobLogo_mdpi.png", 1, 470, 263));
		ImageSymbol_BankJobLogo->addSibling(new CocoImageSibling("BankJobLogo_xhdpi.png", 2, 940, 526));
		ImageSymbol_BankJobLogo->textureCellWidth = 470;
		ImageSymbol_BankJobLogo->textureCellHeight = 263;
		ImageSymbol_BankJobLogo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_CashLogo = newResourceImage("ImageSymbol_CashLogo", "./assets/images/");
	{
		ImageSymbol_CashLogo->viewOptimalWidth = 109;
		ImageSymbol_CashLogo->viewOptimalHeight = 63;
		ImageSymbol_CashLogo->addSibling(new CocoImageSibling("CashLogo_mdpi.png", 1, 268, 156));
		ImageSymbol_CashLogo->addSibling(new CocoImageSibling("CashLogo_xhdpi.png", 2, 536, 311));
		ImageSymbol_CashLogo->textureCellWidth = 268;
		ImageSymbol_CashLogo->textureCellHeight = 156;
		ImageSymbol_CashLogo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_SackLogo = newResourceImage("ImageSymbol_SackLogo", "./assets/images/");
	{
		ImageSymbol_SackLogo->viewOptimalWidth = 62;
		ImageSymbol_SackLogo->viewOptimalHeight = 53;
		ImageSymbol_SackLogo->addSibling(new CocoImageSibling("SackLogo_mdpi.png", 1, 138, 117));
		ImageSymbol_SackLogo->addSibling(new CocoImageSibling("SackLogo_xhdpi.png", 2, 275, 233));
		ImageSymbol_SackLogo->textureCellWidth = 138;
		ImageSymbol_SackLogo->textureCellHeight = 117;
		ImageSymbol_SackLogo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_BlueGlowLogo = newResourceImage("ImageSymbol_BlueGlowLogo", "./assets/images/");
	{
		ImageSymbol_BlueGlowLogo->viewOptimalWidth = 109;
		ImageSymbol_BlueGlowLogo->viewOptimalHeight = 68;
		ImageSymbol_BlueGlowLogo->addSibling(new CocoImageSibling("BlueGlowLogo_mdpi.png", 1, 243, 150));
		ImageSymbol_BlueGlowLogo->addSibling(new CocoImageSibling("BlueGlowLogo_xhdpi.png", 2, 486, 300));
		ImageSymbol_BlueGlowLogo->textureCellWidth = 243;
		ImageSymbol_BlueGlowLogo->textureCellHeight = 150;
		ImageSymbol_BlueGlowLogo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_RedGlowLogo = newResourceImage("ImageSymbol_RedGlowLogo", "./assets/images/");
	{
		ImageSymbol_RedGlowLogo->viewOptimalWidth = 109;
		ImageSymbol_RedGlowLogo->viewOptimalHeight = 68;
		ImageSymbol_RedGlowLogo->addSibling(new CocoImageSibling("RedGlowLogo_mdpi.png", 1, 243, 150));
		ImageSymbol_RedGlowLogo->addSibling(new CocoImageSibling("RedGlowLogo_xhdpi.png", 2, 486, 300));
		ImageSymbol_RedGlowLogo->textureCellWidth = 243;
		ImageSymbol_RedGlowLogo->textureCellHeight = 150;
		ImageSymbol_RedGlowLogo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_goPlay = newResourceImage("ImageSymbol_goPlay", "./assets/images/");
	{
		ImageSymbol_goPlay->viewOptimalWidth = 128;
		ImageSymbol_goPlay->viewOptimalHeight = 64;
		ImageSymbol_goPlay->addSibling(new CocoImageSibling("goPlay_mdpi.png", 1, 256, 128));
		ImageSymbol_goPlay->addSibling(new CocoImageSibling("goPlay_xhdpi.png", 2, 512, 256));
		ImageSymbol_goPlay->textureCellWidth = 256;
		ImageSymbol_goPlay->textureCellHeight = 128;
		ImageSymbol_goPlay->textureGrid = new Float32Array({0, 0});
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	{
		CocoClip* inst1 = new CocoClip();
		inst1->__instanceName = "Background1";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1);
		inst1->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst2 = new CocoClip(ImageSymbol_Background, NULL, NULL);
			inst2->__instanceName = ":: ImageSymbol_Background";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst3 = new CocoClip();
		inst3->__instanceName = "Lasers";
		__root->addChild(inst3);
		inst3->__timeline->clear();
		inst3->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 318, 204, 1, 1, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 318, 204, 1, 1, 0, 0, 0, 1);
		{
			CocoClip* inst4 = new CocoClip();
			inst4->__instanceName = "RedLaserSingle1";
			inst3->addChild(inst4);
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 138,  -434, 1, 1,  -72.2, 455.4101,  -1.277932, 1);
			inst4->__timeline->addKeyFrameEx(NULL, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 138,  -434, 1, 1,  -44.8, 455.4101,  -1.277932, 1);
			inst4->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 138,  -434, 1, 1,  -37.6, 455.4101,  -1.277932, 1);
			inst4->__timeline->addKeyFrameEx(NULL, 150, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 138,  -434, 1, 1,  -72.2, 455.4101,  -1.277932, 1);
			{
				CocoClip* inst5 = new CocoClip(ImageSymbol_RedLaserSingle, NULL, NULL);
				inst5->__instanceName = ":: ImageSymbol_RedLaserSingle";
				inst4->addChild(inst5);
				inst5->__timeline->clear();
				inst5->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst6 = new CocoClip();
			inst6->__instanceName = "RedLaserSingle2";
			inst3->addChild(inst6);
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216,  -300, 1, 1,  -30.3, 459.2341, 0.251726, 1);
			inst6->__timeline->addKeyFrameEx(NULL, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216,  -300, 1, 1,  -19.8, 459.2341, 0.251726, 1);
			inst6->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216,  -300, 1, 1,  -36, 459.2341, 0.251726, 1);
			inst6->__timeline->addKeyFrameEx(NULL, 150, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216,  -300, 1, 1,  -30.3, 459.2341, 0.251726, 1);
			{
				CocoClip* inst7 = new CocoClip(ImageSymbol_RedLaserSingle, NULL, NULL);
				inst7->__instanceName = ":: ImageSymbol_RedLaserSingle";
				inst6->addChild(inst7);
				inst7->__timeline->clear();
				inst7->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst8 = new CocoClip();
			inst8->__instanceName = "RedLaserSingle3";
			inst3->addChild(inst8);
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 172,  -398, 1, 1,  -34.3, 457.6549,  -0.120526, 1);
			inst8->__timeline->addKeyFrameEx(NULL, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 172,  -398, 1, 1,  -45.2, 457.6549,  -0.120526, 1);
			inst8->__timeline->addKeyFrameEx(NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 172,  -398, 1, 1,  -26.8, 457.6549,  -0.120526, 1);
			inst8->__timeline->addKeyFrameEx(NULL, 150, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 172,  -398, 1, 1,  -34.3, 457.6549,  -0.120526, 1);
			{
				CocoClip* inst9 = new CocoClip(ImageSymbol_RedLaserSingle, NULL, NULL);
				inst9->__instanceName = ":: ImageSymbol_RedLaserSingle";
				inst8->addChild(inst9);
				inst9->__timeline->clear();
				inst9->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
		}
		CocoClip* inst10 = new CocoClip();
		inst10->__instanceName = "Title";
		__root->addChild(inst10);
		inst10->__timeline->clear();
		inst10->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -80, 0.45, 0.45, 0, 0, 0, 1);
		inst10->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -80, 0.45, 0.45, 0, 0, 0, 1);
		{
			CocoClip* inst11 = new CocoClip();
			inst11->__instanceName = "BankJobLogo";
			inst10->addChild(inst11);
			inst11->__timeline->clear();
			inst11->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -915, 0, 1, 1, 0, 0, 0, 1);
			inst11->__timeline->addKeyFrameEx(NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -182,  -6, 1, 1, 0, 0, 0, 1);
			inst11->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -182,  -6, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst12 = new CocoClip();
				inst12->__instanceName = "BankJobLogo1";
				inst11->addChild(inst12);
				inst12->__timeline->clear();
				inst12->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst12->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst13 = new CocoClip(ImageSymbol_BankJobLogo, NULL, NULL);
					inst13->__instanceName = ":: ImageSymbol_BankJobLogo";
					inst12->addChild(inst13);
					inst13->__timeline->clear();
					inst13->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst14 = new CocoClip();
				inst14->__instanceName = "BlueGlowLogo1";
				inst11->addChild(inst14);
				inst14->__timeline->clear();
				inst14->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -16.66656,  -111.7333, 1, 1, 0, 0, 0, 1);
				inst14->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -198.8888,  -122.8445, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst15 = new CocoClip(ImageSymbol_BlueGlowLogo, NULL, NULL);
					inst15->__instanceName = ":: ImageSymbol_BlueGlowLogo";
					inst14->addChild(inst15);
					inst15->__timeline->clear();
					inst15->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst16 = new CocoClip();
				inst16->__instanceName = "RedGlowLogo1";
				inst11->addChild(inst16);
				inst16->__timeline->clear();
				inst16->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -96.66664,  -105.0667, 1, 1, 0, 0, 0, 1);
				inst16->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -101.1111,  -102.8445, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst17 = new CocoClip(ImageSymbol_RedGlowLogo, NULL, NULL);
					inst17->__instanceName = ":: ImageSymbol_RedGlowLogo";
					inst16->addChild(inst17);
					inst17->__timeline->clear();
					inst17->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
			}
			CocoClip* inst18 = new CocoClip();
			inst18->__instanceName = "CashLogo1";
			inst10->addChild(inst18);
			inst18->__timeline->clear();
			inst18->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 815.965, 65, 0.9, 0.9, 0, 0, 0, 1);
			inst18->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -56.97949, 58.33333, 0.9, 0.9, 0, 0, 0, 1);
			inst18->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -56.97949, 58.33333, 0.9, 0.9, 0, 0, 0, 1);
			{
				CocoClip* inst19 = new CocoClip(ImageSymbol_CashLogo, NULL, NULL);
				inst19->__instanceName = ":: ImageSymbol_CashLogo";
				inst18->addChild(inst19);
				inst19->__timeline->clear();
				inst19->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst20 = new CocoClip();
			inst20->__instanceName = "SackLogo1";
			inst10->addChild(inst20);
			inst20->__timeline->clear();
			inst20->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 245,  -502, 1, 1, 0, 0, 0, 1);
			inst20->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 60.55554,  -14.16667, 1, 1, 0, 0, 0, 1);
			inst20->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 60.55554,  -14.16667, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst21 = new CocoClip(ImageSymbol_SackLogo, NULL, NULL);
				inst21->__instanceName = ":: ImageSymbol_SackLogo";
				inst20->addChild(inst21);
				inst21->__timeline->clear();
				inst21->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst22 = new CocoClip();
			inst22->__instanceName = "Actions";
			inst10->addChild(inst22);
			inst22->__timeline->clear();
			inst22->__timeline->addKeyFrameEx(waitForAction, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst23 = new CocoClip();
		inst23->__instanceName = "goPlay1";
		__root->addChild(inst23);
		inst23->__timeline->clear();
		inst23->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 187.5, 136.5, 0.5, 0.5, 0, 0, 0, 1);
		inst23->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 187.5, 136.5, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst24 = new CocoClip(ImageSymbol_goPlay, NULL, NULL);
			inst24->__instanceName = ":: ImageSymbol_goPlay";
			inst23->addChild(inst24);
			inst24->__timeline->clear();
			inst24->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst25 = new CocoClip();
		inst25->__instanceName = "Actions";
		__root->addChild(inst25);
		inst25->__timeline->clear();
		inst25->__timeline->addKeyFrameEx(goPlayOnClick, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneTitle::waitForAction()
{
	stop(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneTitle::goPlayOnClick()
{
	CocoEngineState* s;
	s = new State_GameBoard();
	engine->setState(s);
}
