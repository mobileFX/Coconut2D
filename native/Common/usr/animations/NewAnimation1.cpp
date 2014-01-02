#include "NewAnimation1.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
NewAnimation1::NewAnimation1()
{
	__sceneName = "NewAnimation1";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* ImageSymbol_TITLE_SCREEN_LOGO = newResourceImage("ImageSymbol_TITLE_SCREEN_LOGO", "./assets/images/");
	{
		ImageSymbol_TITLE_SCREEN_LOGO->viewOptimalWidth = 0;
		ImageSymbol_TITLE_SCREEN_LOGO->viewOptimalHeight = 0;
		ImageSymbol_TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling("TITLE_SCREEN_LOGO_mdpi.png", 1, 561, 638));
		ImageSymbol_TITLE_SCREEN_LOGO->addSibling(new CocoImageSibling("TITLE_SCREEN_LOGO_xhdpi.png", 2, 1122, 1276));
		ImageSymbol_TITLE_SCREEN_LOGO->textureCellWidth = 561;
		ImageSymbol_TITLE_SCREEN_LOGO->textureCellHeight = 638;
		ImageSymbol_TITLE_SCREEN_LOGO->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_WIN_Shield = newResourceImage("ImageSymbol_WIN_Shield", "./assets/images/");
	{
		ImageSymbol_WIN_Shield->viewOptimalWidth = 85;
		ImageSymbol_WIN_Shield->viewOptimalHeight = 81;
		ImageSymbol_WIN_Shield->addSibling(new CocoImageSibling("WIN_Shield_mdpi.png", 1, 357, 321));
		ImageSymbol_WIN_Shield->addSibling(new CocoImageSibling("WIN_Shield_xhdpi.png", 2, 714, 642));
		ImageSymbol_WIN_Shield->textureCellWidth = 357;
		ImageSymbol_WIN_Shield->textureCellHeight = 321;
		ImageSymbol_WIN_Shield->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_SpartanOnly = newResourceImage("ImageSymbol_SpartanOnly", "./assets/images/");
	{
		ImageSymbol_SpartanOnly->viewOptimalWidth = 48;
		ImageSymbol_SpartanOnly->viewOptimalHeight = 49;
		ImageSymbol_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_ldpi.png", 0.75, 36, 37));
		ImageSymbol_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_mdpi.png", 1, 48, 49));
		ImageSymbol_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_tvdpi.png", 1.25, 60, 61));
		ImageSymbol_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_hdpi.png", 1.5, 72, 74));
		ImageSymbol_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_xhdpi.png", 2, 96, 98));
		ImageSymbol_SpartanOnly->textureCellWidth = 48;
		ImageSymbol_SpartanOnly->textureCellHeight = 49;
		ImageSymbol_SpartanOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_XerxesOnly = newResourceImage("ImageSymbol_XerxesOnly", "./assets/images/");
	{
		ImageSymbol_XerxesOnly->viewOptimalWidth = 50;
		ImageSymbol_XerxesOnly->viewOptimalHeight = 51;
		ImageSymbol_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_ldpi.png", 0.75, 38, 38));
		ImageSymbol_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_mdpi.png", 1, 50, 51));
		ImageSymbol_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_tvdpi.png", 1.25, 62, 64));
		ImageSymbol_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_hdpi.png", 1.5, 75, 76));
		ImageSymbol_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_xhdpi.png", 2, 100, 102));
		ImageSymbol_XerxesOnly->textureCellWidth = 50;
		ImageSymbol_XerxesOnly->textureCellHeight = 51;
		ImageSymbol_XerxesOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_WIN_Logo = newResourceImage("ImageSymbol_WIN_Logo", "./assets/images/");
	{
		ImageSymbol_WIN_Logo->viewOptimalWidth = 96;
		ImageSymbol_WIN_Logo->viewOptimalHeight = 88;
		ImageSymbol_WIN_Logo->addSibling(new CocoImageSibling("WIN_Logo_mdpi.png", 1, 334, 300));
		ImageSymbol_WIN_Logo->addSibling(new CocoImageSibling("WIN_Logo_xhdpi.png", 2, 668, 600));
		ImageSymbol_WIN_Logo->textureCellWidth = 334;
		ImageSymbol_WIN_Logo->textureCellHeight = 300;
		ImageSymbol_WIN_Logo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_openunpressed = newResourceImage("ImageSymbol_openunpressed", "./assets/images/");
	{
		ImageSymbol_openunpressed->viewOptimalWidth = 69;
		ImageSymbol_openunpressed->viewOptimalHeight = 69;
		ImageSymbol_openunpressed->addSibling(new CocoImageSibling("openunpressed_ldpi.png", 0.75, 52, 52));
		ImageSymbol_openunpressed->addSibling(new CocoImageSibling("openunpressed_mdpi.png", 1, 69, 69));
		ImageSymbol_openunpressed->addSibling(new CocoImageSibling("openunpressed_tvdpi.png", 1.25, 86, 86));
		ImageSymbol_openunpressed->addSibling(new CocoImageSibling("openunpressed_hdpi.png", 1.5, 104, 104));
		ImageSymbol_openunpressed->addSibling(new CocoImageSibling("openunpressed_xhdpi.png", 2, 138, 138));
		ImageSymbol_openunpressed->textureCellWidth = 69;
		ImageSymbol_openunpressed->textureCellHeight = 69;
		ImageSymbol_openunpressed->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_LeoOnly2 = newResourceImage("ImageSymbol_LeoOnly2", "./assets/images/");
	{
		ImageSymbol_LeoOnly2->viewOptimalWidth = 50;
		ImageSymbol_LeoOnly2->viewOptimalHeight = 51;
		ImageSymbol_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_ldpi.png", 0.75, 38, 38));
		ImageSymbol_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_mdpi.png", 1, 50, 51));
		ImageSymbol_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_tvdpi.png", 1.25, 62, 64));
		ImageSymbol_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_hdpi.png", 1.5, 75, 76));
		ImageSymbol_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_xhdpi.png", 2, 100, 102));
		ImageSymbol_LeoOnly2->textureCellWidth = 50;
		ImageSymbol_LeoOnly2->textureCellHeight = 51;
		ImageSymbol_LeoOnly2->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_TileOnly = newResourceImage("ImageSymbol_TileOnly", "./assets/images/");
	{
		ImageSymbol_TileOnly->viewOptimalWidth = 48;
		ImageSymbol_TileOnly->viewOptimalHeight = 49;
		ImageSymbol_TileOnly->addSibling(new CocoImageSibling("TileOnly_ldpi.png", 0.75, 36, 37));
		ImageSymbol_TileOnly->addSibling(new CocoImageSibling("TileOnly_mdpi.png", 1, 48, 49));
		ImageSymbol_TileOnly->addSibling(new CocoImageSibling("TileOnly_tvdpi.png", 1.25, 60, 61));
		ImageSymbol_TileOnly->addSibling(new CocoImageSibling("TileOnly_hdpi.png", 1.5, 72, 74));
		ImageSymbol_TileOnly->addSibling(new CocoImageSibling("TileOnly_xhdpi.png", 2, 96, 98));
		ImageSymbol_TileOnly->textureCellWidth = 48;
		ImageSymbol_TileOnly->textureCellHeight = 49;
		ImageSymbol_TileOnly->textureGrid = new Float32Array({0, 0});
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	{
		CocoClip* inst1 = new CocoClip();
		inst1->__instanceName = "ClipSymbol_00011";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -399.5, 5.5, 1, 1, 0, 0, 0, 1);
		{
			CocoClip* inst2 = new CocoClip();
			inst2->__instanceName = "Layer1";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 1, 0, 1, 1, 0, 466, 51, 1);
			{
				CocoClip* inst3 = new CocoClip();
				inst3->__instanceName = "SpartanOnly1";
				inst2->addChild(inst3);
				inst3->__timeline->clear();
				inst3->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 371.5,  -75.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst4 = new CocoClip(ImageSymbol_SpartanOnly, NULL, NULL);
					inst4->__instanceName = ":: ImageSymbol_SpartanOnly";
					inst3->addChild(inst4);
					inst4->__timeline->clear();
					inst4->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst5 = new CocoClip();
				inst5->__instanceName = "XerxesOnly1";
				inst2->addChild(inst5);
				inst5->__timeline->clear();
				inst5->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 444.5,  -78.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst6 = new CocoClip(ImageSymbol_XerxesOnly, NULL, NULL);
					inst6->__instanceName = ":: ImageSymbol_XerxesOnly";
					inst5->addChild(inst6);
					inst6->__timeline->clear();
					inst6->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst8 = new CocoClip();
				inst8->__instanceName = "WIN_Logo1";
				inst2->addChild(inst8);
				inst8->__timeline->clear();
				inst8->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 373.5, 8.5, 0.287425, 0.293333, 0, 0, 0, 1);
				{
					CocoClip* inst9 = new CocoClip(ImageSymbol_WIN_Logo, NULL, NULL);
					inst9->__instanceName = ":: ImageSymbol_WIN_Logo";
					inst8->addChild(inst9);
					inst9->__timeline->clear();
					inst9->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst10 = new CocoClip();
				inst10->__instanceName = "WIN_Shield1";
				inst2->addChild(inst10);
				inst10->__timeline->clear();
				inst10->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 480.5, 7.5, 0.238095, 0.252336, 0, 0, 0, 1);
				{
					CocoClip* inst11 = new CocoClip(ImageSymbol_WIN_Shield, NULL, NULL);
					inst11->__instanceName = ":: ImageSymbol_WIN_Shield";
					inst10->addChild(inst11);
					inst11->__timeline->clear();
					inst11->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst14 = new CocoClip();
				inst14->__instanceName = "openunpressed1";
				inst2->addChild(inst14);
				inst14->__timeline->clear();
				inst14->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 368.5, 102.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst15 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst15->__instanceName = ":: ImageSymbol_openunpressed";
					inst14->addChild(inst15);
					inst15->__timeline->clear();
					inst15->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst16 = new CocoClip();
				inst16->__instanceName = "openunpressed2";
				inst2->addChild(inst16);
				inst16->__timeline->clear();
				inst16->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 456.5, 103.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst17 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst17->__instanceName = ":: ImageSymbol_openunpressed";
					inst16->addChild(inst17);
					inst17->__timeline->clear();
					inst17->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst18 = new CocoClip();
				inst18->__instanceName = "openunpressed3";
				inst2->addChild(inst18);
				inst18->__timeline->clear();
				inst18->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 541.5, 101.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst19 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst19->__instanceName = ":: ImageSymbol_openunpressed";
					inst18->addChild(inst19);
					inst19->__timeline->clear();
					inst19->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst21 = new CocoClip();
				inst21->__instanceName = "LeoOnly21";
				inst2->addChild(inst21);
				inst21->__timeline->clear();
				inst21->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 366.5, 178.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst22 = new CocoClip(ImageSymbol_LeoOnly2, NULL, NULL);
					inst22->__instanceName = ":: ImageSymbol_LeoOnly2";
					inst21->addChild(inst22);
					inst22->__timeline->clear();
					inst22->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst23 = new CocoClip();
				inst23->__instanceName = "LeoOnly22";
				inst2->addChild(inst23);
				inst23->__timeline->clear();
				inst23->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 437.5, 178.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst24 = new CocoClip(ImageSymbol_LeoOnly2, NULL, NULL);
					inst24->__instanceName = ":: ImageSymbol_LeoOnly2";
					inst23->addChild(inst24);
					inst24->__timeline->clear();
					inst24->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst26 = new CocoClip();
				inst26->__instanceName = "TileOnly1";
				inst2->addChild(inst26);
				inst26->__timeline->clear();
				inst26->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 501.5, 172.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst27 = new CocoClip(ImageSymbol_TileOnly, NULL, NULL);
					inst27->__instanceName = ":: ImageSymbol_TileOnly";
					inst26->addChild(inst27);
					inst27->__timeline->clear();
					inst27->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst28 = new CocoClip();
				inst28->__instanceName = "TileOnly2";
				inst2->addChild(inst28);
				inst28->__timeline->clear();
				inst28->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 575.5, 169.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst29 = new CocoClip(ImageSymbol_TileOnly, NULL, NULL);
					inst29->__instanceName = ":: ImageSymbol_TileOnly";
					inst28->addChild(inst29);
					inst29->__timeline->clear();
					inst29->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
			}
		}
		CocoClip* inst30 = new CocoClip();
		inst30->__instanceName = "ClipSymbol_00012";
		__root->addChild(inst30);
		inst30->__timeline->clear();
		inst30->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 399.5, 1.5, 1, 1, 0, 0, 0, 1);
		{
			CocoClip* inst31 = new CocoClip();
			inst31->__instanceName = "Layer1";
			inst30->addChild(inst31);
			inst31->__timeline->clear();
			inst31->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 1, 0, 1, 1, 0, 466, 51, 1);
			{
				CocoClip* inst32 = new CocoClip();
				inst32->__instanceName = "SpartanOnly1";
				inst31->addChild(inst32);
				inst32->__timeline->clear();
				inst32->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 371.5,  -75.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst33 = new CocoClip(ImageSymbol_SpartanOnly, NULL, NULL);
					inst33->__instanceName = ":: ImageSymbol_SpartanOnly";
					inst32->addChild(inst33);
					inst33->__timeline->clear();
					inst33->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst34 = new CocoClip();
				inst34->__instanceName = "XerxesOnly1";
				inst31->addChild(inst34);
				inst34->__timeline->clear();
				inst34->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 444.5,  -78.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst35 = new CocoClip(ImageSymbol_XerxesOnly, NULL, NULL);
					inst35->__instanceName = ":: ImageSymbol_XerxesOnly";
					inst34->addChild(inst35);
					inst35->__timeline->clear();
					inst35->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst37 = new CocoClip();
				inst37->__instanceName = "WIN_Logo1";
				inst31->addChild(inst37);
				inst37->__timeline->clear();
				inst37->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 373.5, 8.5, 0.287425, 0.293333, 0, 0, 0, 1);
				{
					CocoClip* inst38 = new CocoClip(ImageSymbol_WIN_Logo, NULL, NULL);
					inst38->__instanceName = ":: ImageSymbol_WIN_Logo";
					inst37->addChild(inst38);
					inst38->__timeline->clear();
					inst38->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst39 = new CocoClip();
				inst39->__instanceName = "WIN_Shield1";
				inst31->addChild(inst39);
				inst39->__timeline->clear();
				inst39->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 480.5, 7.5, 0.238095, 0.252336, 0, 0, 0, 1);
				{
					CocoClip* inst40 = new CocoClip(ImageSymbol_WIN_Shield, NULL, NULL);
					inst40->__instanceName = ":: ImageSymbol_WIN_Shield";
					inst39->addChild(inst40);
					inst40->__timeline->clear();
					inst40->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst43 = new CocoClip();
				inst43->__instanceName = "openunpressed1";
				inst31->addChild(inst43);
				inst43->__timeline->clear();
				inst43->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 368.5, 102.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst44 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst44->__instanceName = ":: ImageSymbol_openunpressed";
					inst43->addChild(inst44);
					inst44->__timeline->clear();
					inst44->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst45 = new CocoClip();
				inst45->__instanceName = "openunpressed2";
				inst31->addChild(inst45);
				inst45->__timeline->clear();
				inst45->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 456.5, 103.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst46 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst46->__instanceName = ":: ImageSymbol_openunpressed";
					inst45->addChild(inst46);
					inst46->__timeline->clear();
					inst46->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst47 = new CocoClip();
				inst47->__instanceName = "openunpressed3";
				inst31->addChild(inst47);
				inst47->__timeline->clear();
				inst47->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 541.5, 101.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst48 = new CocoClip(ImageSymbol_openunpressed, NULL, NULL);
					inst48->__instanceName = ":: ImageSymbol_openunpressed";
					inst47->addChild(inst48);
					inst48->__timeline->clear();
					inst48->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst50 = new CocoClip();
				inst50->__instanceName = "LeoOnly21";
				inst31->addChild(inst50);
				inst50->__timeline->clear();
				inst50->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 366.5, 178.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst51 = new CocoClip(ImageSymbol_LeoOnly2, NULL, NULL);
					inst51->__instanceName = ":: ImageSymbol_LeoOnly2";
					inst50->addChild(inst51);
					inst51->__timeline->clear();
					inst51->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst52 = new CocoClip();
				inst52->__instanceName = "LeoOnly22";
				inst31->addChild(inst52);
				inst52->__timeline->clear();
				inst52->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 437.5, 178.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst53 = new CocoClip(ImageSymbol_LeoOnly2, NULL, NULL);
					inst53->__instanceName = ":: ImageSymbol_LeoOnly2";
					inst52->addChild(inst53);
					inst53->__timeline->clear();
					inst53->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst55 = new CocoClip();
				inst55->__instanceName = "TileOnly1";
				inst31->addChild(inst55);
				inst55->__timeline->clear();
				inst55->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 501.5, 172.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst56 = new CocoClip(ImageSymbol_TileOnly, NULL, NULL);
					inst56->__instanceName = ":: ImageSymbol_TileOnly";
					inst55->addChild(inst56);
					inst56->__timeline->clear();
					inst56->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst57 = new CocoClip();
				inst57->__instanceName = "TileOnly2";
				inst31->addChild(inst57);
				inst57->__timeline->clear();
				inst57->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 575.5, 169.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst58 = new CocoClip(ImageSymbol_TileOnly, NULL, NULL);
					inst58->__instanceName = ":: ImageSymbol_TileOnly";
					inst57->addChild(inst58);
					inst58->__timeline->clear();
					inst58->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
			}
		}
	}
}
