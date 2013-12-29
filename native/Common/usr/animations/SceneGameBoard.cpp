#include "SceneGameBoard.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
SceneGameBoard::SceneGameBoard()
{
	__sceneName = "SceneGameBoard";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* ImageSymbol_gsBackground = newResourceImage("ImageSymbol_gsBackground", "./assets/images/");
	{
		ImageSymbol_gsBackground->viewOptimalWidth = 568;
		ImageSymbol_gsBackground->viewOptimalHeight = 360;
		ImageSymbol_gsBackground->addSibling(new CocoImageSibling("gsBackground_mdpi.png", 1, 1136, 720));
		ImageSymbol_gsBackground->addSibling(new CocoImageSibling("gsBackground_xhdpi.png", 2, 2272, 1440));
		ImageSymbol_gsBackground->textureCellWidth = 1136;
		ImageSymbol_gsBackground->textureCellHeight = 720;
		ImageSymbol_gsBackground->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_BalanceBar = newResourceImage("ImageSymbol_BalanceBar", "./assets/images/");
	{
		ImageSymbol_BalanceBar->viewOptimalWidth = 112;
		ImageSymbol_BalanceBar->viewOptimalHeight = 51;
		ImageSymbol_BalanceBar->addSibling(new CocoImageSibling("BalanceBar_mdpi.png", 1, 225, 113));
		ImageSymbol_BalanceBar->addSibling(new CocoImageSibling("BalanceBar_xhdpi.png", 2, 450, 226));
		ImageSymbol_BalanceBar->textureCellWidth = 225;
		ImageSymbol_BalanceBar->textureCellHeight = 113;
		ImageSymbol_BalanceBar->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_WinningsBar = newResourceImage("ImageSymbol_WinningsBar", "./assets/images/");
	{
		ImageSymbol_WinningsBar->viewOptimalWidth = 111;
		ImageSymbol_WinningsBar->viewOptimalHeight = 51;
		ImageSymbol_WinningsBar->addSibling(new CocoImageSibling("WinningsBar_mdpi.png", 1, 222, 113));
		ImageSymbol_WinningsBar->addSibling(new CocoImageSibling("WinningsBar_xhdpi.png", 2, 444, 226));
		ImageSymbol_WinningsBar->textureCellWidth = 222;
		ImageSymbol_WinningsBar->textureCellHeight = 113;
		ImageSymbol_WinningsBar->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_Red_LASER = newResourceImage("ImageSymbol_Red_LASER", "./assets/images/");
	{
		ImageSymbol_Red_LASER->viewOptimalWidth = 481;
		ImageSymbol_Red_LASER->viewOptimalHeight = 361;
		ImageSymbol_Red_LASER->addSibling(new CocoImageSibling("Red_LASER_mdpi.png", 1, 1024, 768));
		ImageSymbol_Red_LASER->addSibling(new CocoImageSibling("Red_LASER_xhdpi.png", 2, 2048, 1536));
		ImageSymbol_Red_LASER->textureCellWidth = 1024;
		ImageSymbol_Red_LASER->textureCellHeight = 768;
		ImageSymbol_Red_LASER->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_body = newResourceImage("ImageSymbol_body", "./assets/images/");
	{
		ImageSymbol_body->viewOptimalWidth = 56;
		ImageSymbol_body->viewOptimalHeight = 34;
		ImageSymbol_body->addSibling(new CocoImageSibling("body_mdpi.png", 1, 126, 75));
		ImageSymbol_body->addSibling(new CocoImageSibling("body_xhdpi.png", 2, 251, 149));
		ImageSymbol_body->textureCellWidth = 126;
		ImageSymbol_body->textureCellHeight = 75;
		ImageSymbol_body->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_arm = newResourceImage("ImageSymbol_arm", "./assets/images/");
	{
		ImageSymbol_arm->viewOptimalWidth = 102;
		ImageSymbol_arm->viewOptimalHeight = 39;
		ImageSymbol_arm->addSibling(new CocoImageSibling("arm_mdpi.png", 1, 233, 87));
		ImageSymbol_arm->addSibling(new CocoImageSibling("arm_xhdpi.png", 2, 466, 174));
		ImageSymbol_arm->textureCellWidth = 233;
		ImageSymbol_arm->textureCellHeight = 87;
		ImageSymbol_arm->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_glove = newResourceImage("ImageSymbol_glove", "./assets/images/");
	{
		ImageSymbol_glove->viewOptimalWidth = 35;
		ImageSymbol_glove->viewOptimalHeight = 20;
		ImageSymbol_glove->addSibling(new CocoImageSibling("glove_mdpi.png", 1, 88, 45));
		ImageSymbol_glove->addSibling(new CocoImageSibling("glove_xhdpi.png", 2, 175, 90));
		ImageSymbol_glove->textureCellWidth = 88;
		ImageSymbol_glove->textureCellHeight = 45;
		ImageSymbol_glove->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_legs = newResourceImage("ImageSymbol_legs", "./assets/images/");
	{
		ImageSymbol_legs->viewOptimalWidth = 97;
		ImageSymbol_legs->viewOptimalHeight = 52;
		ImageSymbol_legs->addSibling(new CocoImageSibling("legs_mdpi.png", 1, 226, 116));
		ImageSymbol_legs->addSibling(new CocoImageSibling("legs_xhdpi.png", 2, 452, 232));
		ImageSymbol_legs->textureCellWidth = 226;
		ImageSymbol_legs->textureCellHeight = 116;
		ImageSymbol_legs->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_shoe = newResourceImage("ImageSymbol_shoe", "./assets/images/");
	{
		ImageSymbol_shoe->viewOptimalWidth = 26;
		ImageSymbol_shoe->viewOptimalHeight = 39;
		ImageSymbol_shoe->addSibling(new CocoImageSibling("shoe_mdpi.png", 1, 64, 87));
		ImageSymbol_shoe->addSibling(new CocoImageSibling("shoe_xhdpi.png", 2, 128, 173));
		ImageSymbol_shoe->textureCellWidth = 64;
		ImageSymbol_shoe->textureCellHeight = 87;
		ImageSymbol_shoe->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* SpriteSymbol_thiefHead = newResourceImage("SpriteSymbol_thiefHead", "./assets/images/");
	{
		SpriteSymbol_thiefHead->viewOptimalWidth = 43;
		SpriteSymbol_thiefHead->viewOptimalHeight = 63;
		SpriteSymbol_thiefHead->addSibling(new CocoImageSibling("thiefHead_mdpi.png", 1, 107, 140));
		SpriteSymbol_thiefHead->addSibling(new CocoImageSibling("thiefHead_xhdpi.png", 2, 214, 280));
		SpriteSymbol_thiefHead->textureCellWidth = 107;
		SpriteSymbol_thiefHead->textureCellHeight = 140;
		SpriteSymbol_thiefHead->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 1, 1, 1, 2, 1, 3, 2, 0, 2, 1, 2, 2});
		SpriteSymbol_thiefHead->addSequence(new CocoSequence("idle", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 6, 7}));
	}
	CocoImage* SpriteSymbol_thiefBusted = newResourceImage("SpriteSymbol_thiefBusted", "./assets/images/");
	{
		SpriteSymbol_thiefBusted->viewOptimalWidth = 43;
		SpriteSymbol_thiefBusted->viewOptimalHeight = 56;
		SpriteSymbol_thiefBusted->addSibling(new CocoImageSibling("thiefBusted_mdpi.png", 1, 107, 140));
		SpriteSymbol_thiefBusted->addSibling(new CocoImageSibling("thiefBusted_xhdpi.png", 2, 214, 280));
		SpriteSymbol_thiefBusted->textureCellWidth = 107;
		SpriteSymbol_thiefBusted->textureCellHeight = 140;
		SpriteSymbol_thiefBusted->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 1, 0, 1, 1, 1, 2, 1, 3, 2, 0, 2, 1, 2, 2, 2, 3, 3, 0, 3, 1, 3, 2, 3, 3, 4, 0, 4, 1, 4, 2});
		SpriteSymbol_thiefBusted->addSequence(new CocoSequence("busted", {0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18}));
		SpriteSymbol_thiefBusted->addSequence(new CocoSequence("busted_last", {18}));
	}
	CocoImage* ImageSymbol_busted_fasa = newResourceImage("ImageSymbol_busted_fasa", "./assets/images/");
	{
		ImageSymbol_busted_fasa->viewOptimalWidth = 181;
		ImageSymbol_busted_fasa->viewOptimalHeight = 50;
		ImageSymbol_busted_fasa->addSibling(new CocoImageSibling("busted_fasa_mdpi.png", 1, 453, 126));
		ImageSymbol_busted_fasa->textureCellWidth = 453;
		ImageSymbol_busted_fasa->textureCellHeight = 126;
		ImageSymbol_busted_fasa->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_blackBlank_0001 = newResourceImage("ImageSymbol_blackBlank_0001", "./assets/images/");
	{
		ImageSymbol_blackBlank_0001->viewOptimalWidth = 1024;
		ImageSymbol_blackBlank_0001->viewOptimalHeight = 512;
		ImageSymbol_blackBlank_0001->addSibling(new CocoImageSibling("blackBlank_mdpi.png", 1, 2048, 1024));
		ImageSymbol_blackBlank_0001->addSibling(new CocoImageSibling("blackBlank_xhdpi.png", 2, 4096, 2048));
		ImageSymbol_blackBlank_0001->textureCellWidth = 2048;
		ImageSymbol_blackBlank_0001->textureCellHeight = 1024;
		ImageSymbol_blackBlank_0001->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_HANDCOUGHS = newResourceImage("ImageSymbol_HANDCOUGHS", "./assets/images/");
	{
		ImageSymbol_HANDCOUGHS->viewOptimalWidth = 29;
		ImageSymbol_HANDCOUGHS->viewOptimalHeight = 10;
		ImageSymbol_HANDCOUGHS->addSibling(new CocoImageSibling("HANDCOUGHS_mdpi.png", 1, 65, 23));
		ImageSymbol_HANDCOUGHS->addSibling(new CocoImageSibling("HANDCOUGHS_xhdpi.png", 2, 130, 46));
		ImageSymbol_HANDCOUGHS->textureCellWidth = 65;
		ImageSymbol_HANDCOUGHS->textureCellHeight = 23;
		ImageSymbol_HANDCOUGHS->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_busted = newResourceImage("ImageSymbol_busted", "./assets/images/");
	{
		ImageSymbol_busted->viewOptimalWidth = 225;
		ImageSymbol_busted->viewOptimalHeight = 28;
		ImageSymbol_busted->addSibling(new CocoImageSibling("busted_mdpi.png", 1, 512, 64));
		ImageSymbol_busted->addSibling(new CocoImageSibling("busted_xhdpi.png", 2, 1024, 128));
		ImageSymbol_busted->textureCellWidth = 512;
		ImageSymbol_busted->textureCellHeight = 64;
		ImageSymbol_busted->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_security = newResourceImage("ImageSymbol_security", "./assets/images/");
	{
		ImageSymbol_security->viewOptimalWidth = 176;
		ImageSymbol_security->viewOptimalHeight = 200;
		ImageSymbol_security->addSibling(new CocoImageSibling("security_mdpi.png", 1, 441, 491));
		ImageSymbol_security->addSibling(new CocoImageSibling("security_xhdpi.png", 2, 882, 982));
		ImageSymbol_security->textureCellWidth = 441;
		ImageSymbol_security->textureCellHeight = 491;
		ImageSymbol_security->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_guardHandcoughs = newResourceImage("ImageSymbol_guardHandcoughs", "./assets/images/");
	{
		ImageSymbol_guardHandcoughs->viewOptimalWidth = 52;
		ImageSymbol_guardHandcoughs->viewOptimalHeight = 131;
		ImageSymbol_guardHandcoughs->addSibling(new CocoImageSibling("guardHandcoughs_mdpi.png", 1, 128, 320));
		ImageSymbol_guardHandcoughs->addSibling(new CocoImageSibling("guardHandcoughs_xhdpi.png", 2, 256, 1024));
		ImageSymbol_guardHandcoughs->textureCellWidth = 128;
		ImageSymbol_guardHandcoughs->textureCellHeight = 320;
		ImageSymbol_guardHandcoughs->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_FINGERTIP = newResourceImage("ImageSymbol_FINGERTIP", "./assets/images/");
	{
		ImageSymbol_FINGERTIP->viewOptimalWidth = 20;
		ImageSymbol_FINGERTIP->viewOptimalHeight = 16;
		ImageSymbol_FINGERTIP->addSibling(new CocoImageSibling("FINGERTIP_mdpi.png", 1, 49, 39));
		ImageSymbol_FINGERTIP->addSibling(new CocoImageSibling("FINGERTIP_xhdpi.png", 2, 98, 78));
		ImageSymbol_FINGERTIP->textureCellWidth = 49;
		ImageSymbol_FINGERTIP->textureCellHeight = 39;
		ImageSymbol_FINGERTIP->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_safe_closed_idle = newResourceImage("ImageSymbol_safe_closed_idle", "./assets/images/");
	{
		ImageSymbol_safe_closed_idle->viewOptimalWidth = 97;
		ImageSymbol_safe_closed_idle->viewOptimalHeight = 127;
		ImageSymbol_safe_closed_idle->addSibling(new CocoImageSibling("safe_closed_idle_mdpi.png", 1, 138, 182));
		ImageSymbol_safe_closed_idle->addSibling(new CocoImageSibling("safe_closed_idle_xhdpi.png", 2, 277, 364));
		ImageSymbol_safe_closed_idle->textureCellWidth = 138;
		ImageSymbol_safe_closed_idle->textureCellHeight = 182;
		ImageSymbol_safe_closed_idle->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* SpriteSymbol_Safe_WinOnly = newResourceImage("SpriteSymbol_Safe_WinOnly", "./assets/images/");
	{
		SpriteSymbol_Safe_WinOnly->viewOptimalWidth = 224;
		SpriteSymbol_Safe_WinOnly->viewOptimalHeight = 169;
		SpriteSymbol_Safe_WinOnly->addSibling(new CocoImageSibling("Safe_WinOnly_mdpi.png", 1, 320, 241));
		SpriteSymbol_Safe_WinOnly->addSibling(new CocoImageSibling("Safe_WinOnly_xhdpi.png", 2, 641, 481));
		SpriteSymbol_Safe_WinOnly->textureCellWidth = 320;
		SpriteSymbol_Safe_WinOnly->textureCellHeight = 241;
		SpriteSymbol_Safe_WinOnly->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 3, 0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 6, 0, 6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 7, 0, 7, 1, 7, 2, 7, 3});
		SpriteSymbol_Safe_WinOnly->addSequence(new CocoSequence("win", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 45, 45}));
	}
	CocoImage* SpriteSymbol_Safe_Lose = newResourceImage("SpriteSymbol_Safe_Lose", "./assets/images/");
	{
		SpriteSymbol_Safe_Lose->viewOptimalWidth = 225;
		SpriteSymbol_Safe_Lose->viewOptimalHeight = 168;
		SpriteSymbol_Safe_Lose->addSibling(new CocoImageSibling("Safe_Lose_mdpi.png", 1, 321, 240));
		SpriteSymbol_Safe_Lose->addSibling(new CocoImageSibling("Safe_Lose_xhdpi.png", 2, 641, 481));
		SpriteSymbol_Safe_Lose->textureCellWidth = 321;
		SpriteSymbol_Safe_Lose->textureCellHeight = 240;
		SpriteSymbol_Safe_Lose->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 1, 0, 1, 1, 1, 2, 2, 0, 2, 1, 2, 2, 3, 0, 3, 1, 3, 2, 4, 0});
		SpriteSymbol_Safe_Lose->addSequence(new CocoSequence("lose", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}));
	}
	CocoImage* ImageSymbol_rope = newResourceImage("ImageSymbol_rope", "./assets/images/");
	{
		ImageSymbol_rope->viewOptimalWidth = 2;
		ImageSymbol_rope->viewOptimalHeight = 115;
		ImageSymbol_rope->addSibling(new CocoImageSibling("rope_mdpi.png", 1, 4, 256));
		ImageSymbol_rope->addSibling(new CocoImageSibling("rope_xhdpi.png", 2, 8, 512));
		ImageSymbol_rope->textureCellWidth = 4;
		ImageSymbol_rope->textureCellHeight = 256;
		ImageSymbol_rope->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_florr = newResourceImage("ImageSymbol_florr", "./assets/images/");
	{
		ImageSymbol_florr->viewOptimalWidth = 315;
		ImageSymbol_florr->viewOptimalHeight = 53;
		ImageSymbol_florr->addSibling(new CocoImageSibling("florr_mdpi.png", 1, 630, 106));
		ImageSymbol_florr->addSibling(new CocoImageSibling("florr_xhdpi.png", 2, 1260, 212));
		ImageSymbol_florr->textureCellWidth = 630;
		ImageSymbol_florr->textureCellHeight = 106;
		ImageSymbol_florr->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_sack = newResourceImage("ImageSymbol_sack", "./assets/images/");
	{
		ImageSymbol_sack->viewOptimalWidth = 80;
		ImageSymbol_sack->viewOptimalHeight = 105;
		ImageSymbol_sack->addSibling(new CocoImageSibling("sack_mdpi.png", 1, 160, 209));
		ImageSymbol_sack->addSibling(new CocoImageSibling("sack_xhdpi.png", 2, 319, 417));
		ImageSymbol_sack->textureCellWidth = 160;
		ImageSymbol_sack->textureCellHeight = 209;
		ImageSymbol_sack->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_money1 = newResourceImage("ImageSymbol_money1", "./assets/images/");
	{
		ImageSymbol_money1->viewOptimalWidth = 64;
		ImageSymbol_money1->viewOptimalHeight = 64;
		ImageSymbol_money1->addSibling(new CocoImageSibling("money1_mdpi.png", 1, 128, 128));
		ImageSymbol_money1->addSibling(new CocoImageSibling("money1_xhdpi.png", 2, 256, 256));
		ImageSymbol_money1->textureCellWidth = 128;
		ImageSymbol_money1->textureCellHeight = 128;
		ImageSymbol_money1->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_money2 = newResourceImage("ImageSymbol_money2", "./assets/images/");
	{
		ImageSymbol_money2->viewOptimalWidth = 64;
		ImageSymbol_money2->viewOptimalHeight = 64;
		ImageSymbol_money2->addSibling(new CocoImageSibling("money2_mdpi.png", 1, 128, 128));
		ImageSymbol_money2->addSibling(new CocoImageSibling("money2_xhdpi.png", 2, 256, 256));
		ImageSymbol_money2->textureCellWidth = 128;
		ImageSymbol_money2->textureCellHeight = 128;
		ImageSymbol_money2->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_money3 = newResourceImage("ImageSymbol_money3", "./assets/images/");
	{
		ImageSymbol_money3->viewOptimalWidth = 64;
		ImageSymbol_money3->viewOptimalHeight = 64;
		ImageSymbol_money3->addSibling(new CocoImageSibling("money3_mdpi.png", 1, 128, 128));
		ImageSymbol_money3->addSibling(new CocoImageSibling("money3_xhdpi.png", 2, 256, 256));
		ImageSymbol_money3->textureCellWidth = 128;
		ImageSymbol_money3->textureCellHeight = 128;
		ImageSymbol_money3->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_youwin = newResourceImage("ImageSymbol_youwin", "./assets/images/");
	{
		ImageSymbol_youwin->viewOptimalWidth = 355;
		ImageSymbol_youwin->viewOptimalHeight = 94;
		ImageSymbol_youwin->addSibling(new CocoImageSibling("youwin_mdpi.png", 1, 646, 171));
		ImageSymbol_youwin->addSibling(new CocoImageSibling("youwin_xhdpi.png", 2, 1292, 341));
		ImageSymbol_youwin->textureCellWidth = 646;
		ImageSymbol_youwin->textureCellHeight = 171;
		ImageSymbol_youwin->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_thiefGlow = newResourceImage("ImageSymbol_thiefGlow", "./assets/images/");
	{
		ImageSymbol_thiefGlow->viewOptimalWidth = 512;
		ImageSymbol_thiefGlow->viewOptimalHeight = 384;
		ImageSymbol_thiefGlow->addSibling(new CocoImageSibling("thiefGlow_mdpi.png", 1, 1024, 768));
		ImageSymbol_thiefGlow->addSibling(new CocoImageSibling("thiefGlow_xhdpi.png", 2, 2048, 1536));
		ImageSymbol_thiefGlow->textureCellWidth = 1024;
		ImageSymbol_thiefGlow->textureCellHeight = 768;
		ImageSymbol_thiefGlow->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MetalDoorHalf = newResourceImage("ImageSymbol_MetalDoorHalf", "./assets/images/");
	{
		ImageSymbol_MetalDoorHalf->viewOptimalWidth = 256;
		ImageSymbol_MetalDoorHalf->viewOptimalHeight = 256;
		ImageSymbol_MetalDoorHalf->addSibling(new CocoImageSibling("MetalDoorHalf_mdpi.png", 1, 512, 512));
		ImageSymbol_MetalDoorHalf->addSibling(new CocoImageSibling("MetalDoorHalf_xhdpi.png", 2, 1024, 1024));
		ImageSymbol_MetalDoorHalf->textureCellWidth = 512;
		ImageSymbol_MetalDoorHalf->textureCellHeight = 512;
		ImageSymbol_MetalDoorHalf->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MetalDoorShadow = newResourceImage("ImageSymbol_MetalDoorShadow", "./assets/images/");
	{
		ImageSymbol_MetalDoorShadow->viewOptimalWidth = 256;
		ImageSymbol_MetalDoorShadow->viewOptimalHeight = 256;
		ImageSymbol_MetalDoorShadow->addSibling(new CocoImageSibling("MetalDoorShadow_mdpi.png", 1, 512, 512));
		ImageSymbol_MetalDoorShadow->addSibling(new CocoImageSibling("MetalDoorShadow_xhdpi.png", 2, 1024, 1024));
		ImageSymbol_MetalDoorShadow->textureCellWidth = 512;
		ImageSymbol_MetalDoorShadow->textureCellHeight = 512;
		ImageSymbol_MetalDoorShadow->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MetalDoorHalfBack = newResourceImage("ImageSymbol_MetalDoorHalfBack", "./assets/images/");
	{
		ImageSymbol_MetalDoorHalfBack->viewOptimalWidth = 8;
		ImageSymbol_MetalDoorHalfBack->viewOptimalHeight = 256;
		ImageSymbol_MetalDoorHalfBack->addSibling(new CocoImageSibling("MetalDoorHalfBack_mdpi.png", 1, 16, 512));
		ImageSymbol_MetalDoorHalfBack->addSibling(new CocoImageSibling("MetalDoorHalfBack_xhdpi.png", 2, 32, 1024));
		ImageSymbol_MetalDoorHalfBack->textureCellWidth = 16;
		ImageSymbol_MetalDoorHalfBack->textureCellHeight = 512;
		ImageSymbol_MetalDoorHalfBack->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MetalDoorHalfHoles = newResourceImage("ImageSymbol_MetalDoorHalfHoles", "./assets/images/");
	{
		ImageSymbol_MetalDoorHalfHoles->viewOptimalWidth = 16;
		ImageSymbol_MetalDoorHalfHoles->viewOptimalHeight = 256;
		ImageSymbol_MetalDoorHalfHoles->addSibling(new CocoImageSibling("MetalDoorHalfHoles_mdpi.png", 1, 32, 512));
		ImageSymbol_MetalDoorHalfHoles->addSibling(new CocoImageSibling("MetalDoorHalfHoles_xhdpi.png", 2, 64, 1024));
		ImageSymbol_MetalDoorHalfHoles->textureCellWidth = 32;
		ImageSymbol_MetalDoorHalfHoles->textureCellHeight = 512;
		ImageSymbol_MetalDoorHalfHoles->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_stageLeftSide = newResourceImage("ImageSymbol_stageLeftSide", "./assets/images/");
	{
		ImageSymbol_stageLeftSide->viewOptimalWidth = 128;
		ImageSymbol_stageLeftSide->viewOptimalHeight = 512;
		ImageSymbol_stageLeftSide->addSibling(new CocoImageSibling("stageLeftSide_mdpi.png", 1, 256, 1024));
		ImageSymbol_stageLeftSide->addSibling(new CocoImageSibling("stageLeftSide_xhdpi.png", 2, 512, 2048));
		ImageSymbol_stageLeftSide->textureCellWidth = 256;
		ImageSymbol_stageLeftSide->textureCellHeight = 1024;
		ImageSymbol_stageLeftSide->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_stageRightSide = newResourceImage("ImageSymbol_stageRightSide", "./assets/images/");
	{
		ImageSymbol_stageRightSide->viewOptimalWidth = 128;
		ImageSymbol_stageRightSide->viewOptimalHeight = 512;
		ImageSymbol_stageRightSide->addSibling(new CocoImageSibling("stageRightSide_mdpi.png", 1, 256, 1024));
		ImageSymbol_stageRightSide->addSibling(new CocoImageSibling("stageRightSide_xhdpi.png", 2, 512, 2048));
		ImageSymbol_stageRightSide->textureCellWidth = 256;
		ImageSymbol_stageRightSide->textureCellHeight = 1024;
		ImageSymbol_stageRightSide->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MedalDoorLeftHalf = newResourceImage("ImageSymbol_MedalDoorLeftHalf", "./assets/images/");
	{
		ImageSymbol_MedalDoorLeftHalf->viewOptimalWidth = 256;
		ImageSymbol_MedalDoorLeftHalf->viewOptimalHeight = 256;
		ImageSymbol_MedalDoorLeftHalf->addSibling(new CocoImageSibling("MedalDoorLeftHalf_mdpi.png", 1, 512, 512));
		ImageSymbol_MedalDoorLeftHalf->addSibling(new CocoImageSibling("MedalDoorLeftHalf_xhdpi.png", 2, 1024, 1024));
		ImageSymbol_MedalDoorLeftHalf->textureCellWidth = 512;
		ImageSymbol_MedalDoorLeftHalf->textureCellHeight = 512;
		ImageSymbol_MedalDoorLeftHalf->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MedalDoorLeftShadow = newResourceImage("ImageSymbol_MedalDoorLeftShadow", "./assets/images/");
	{
		ImageSymbol_MedalDoorLeftShadow->viewOptimalWidth = 256;
		ImageSymbol_MedalDoorLeftShadow->viewOptimalHeight = 256;
		ImageSymbol_MedalDoorLeftShadow->addSibling(new CocoImageSibling("MedalDoorLeftShadow_mdpi.png", 1, 512, 512));
		ImageSymbol_MedalDoorLeftShadow->addSibling(new CocoImageSibling("MedalDoorLeftShadow_xhdpi.png", 2, 1024, 1024));
		ImageSymbol_MedalDoorLeftShadow->textureCellWidth = 512;
		ImageSymbol_MedalDoorLeftShadow->textureCellHeight = 512;
		ImageSymbol_MedalDoorLeftShadow->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_MetalDoorHalfHolesR = newResourceImage("ImageSymbol_MetalDoorHalfHolesR", "./assets/images/");
	{
		ImageSymbol_MetalDoorHalfHolesR->viewOptimalWidth = 16;
		ImageSymbol_MetalDoorHalfHolesR->viewOptimalHeight = 256;
		ImageSymbol_MetalDoorHalfHolesR->addSibling(new CocoImageSibling("MetalDoorHalfHolesR_mdpi.png", 1, 32, 512));
		ImageSymbol_MetalDoorHalfHolesR->addSibling(new CocoImageSibling("MetalDoorHalfHolesR_xhdpi.png", 2, 64, 1024));
		ImageSymbol_MetalDoorHalfHolesR->textureCellWidth = 32;
		ImageSymbol_MetalDoorHalfHolesR->textureCellHeight = 512;
		ImageSymbol_MetalDoorHalfHolesR->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_bettingBar = newResourceImage("ImageSymbol_bettingBar", "./assets/images/");
	{
		ImageSymbol_bettingBar->viewOptimalWidth = 461;
		ImageSymbol_bettingBar->viewOptimalHeight = 90;
		ImageSymbol_bettingBar->addSibling(new CocoImageSibling("bettingBar_mdpi.png", 1, 512, 128));
		ImageSymbol_bettingBar->addSibling(new CocoImageSibling("bettingBar_xhdpi.png", 2, 1024, 256));
		ImageSymbol_bettingBar->textureCellWidth = 512;
		ImageSymbol_bettingBar->textureCellHeight = 128;
		ImageSymbol_bettingBar->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_btnBuyTicket = newResourceImage("ImageSymbol_btnBuyTicket", "./assets/images/");
	{
		ImageSymbol_btnBuyTicket->viewOptimalWidth = 89;
		ImageSymbol_btnBuyTicket->viewOptimalHeight = 69;
		ImageSymbol_btnBuyTicket->addSibling(new CocoImageSibling("btnBuyTicket_mdpi.png", 1, 99, 98));
		ImageSymbol_btnBuyTicket->addSibling(new CocoImageSibling("btnBuyTicket_xhdpi.png", 2, 197, 195));
		ImageSymbol_btnBuyTicket->textureCellWidth = 99;
		ImageSymbol_btnBuyTicket->textureCellHeight = 98;
		ImageSymbol_btnBuyTicket->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_btnOpenAll = newResourceImage("ImageSymbol_btnOpenAll", "./assets/images/");
	{
		ImageSymbol_btnOpenAll->viewOptimalWidth = 89;
		ImageSymbol_btnOpenAll->viewOptimalHeight = 69;
		ImageSymbol_btnOpenAll->addSibling(new CocoImageSibling("btnOpenAll_mdpi.png", 1, 99, 98));
		ImageSymbol_btnOpenAll->addSibling(new CocoImageSibling("btnOpenAll_xhdpi.png", 2, 197, 195));
		ImageSymbol_btnOpenAll->textureCellWidth = 99;
		ImageSymbol_btnOpenAll->textureCellHeight = 98;
		ImageSymbol_btnOpenAll->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_open_safe = newResourceImage("ImageSymbol_open_safe", "./assets/images/");
	{
		ImageSymbol_open_safe->viewOptimalWidth = 0;
		ImageSymbol_open_safe->viewOptimalHeight = 0;
		ImageSymbol_open_safe->addSibling(new CocoImageSibling("open_safe_mdpi.png", 1, 128, 16));
		ImageSymbol_open_safe->addSibling(new CocoImageSibling("open_safe_xhdpi.png", 2, 256, 32));
		ImageSymbol_open_safe->textureCellWidth = 128;
		ImageSymbol_open_safe->textureCellHeight = 16;
		ImageSymbol_open_safe->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_arrow = newResourceImage("ImageSymbol_arrow", "./assets/images/");
	{
		ImageSymbol_arrow->viewOptimalWidth = 53;
		ImageSymbol_arrow->viewOptimalHeight = 28;
		ImageSymbol_arrow->addSibling(new CocoImageSibling("arrow_mdpi.png", 1, 64, 32));
		ImageSymbol_arrow->addSibling(new CocoImageSibling("arrow_xhdpi.png", 2, 128, 64));
		ImageSymbol_arrow->textureCellWidth = 64;
		ImageSymbol_arrow->textureCellHeight = 32;
		ImageSymbol_arrow->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_BetText = newResourceImage("ImageSymbol_BetText", "./assets/images/");
	{
		ImageSymbol_BetText->viewOptimalWidth = 58;
		ImageSymbol_BetText->viewOptimalHeight = 26;
		ImageSymbol_BetText->addSibling(new CocoImageSibling("BetText_mdpi.png", 1, 64, 32));
		ImageSymbol_BetText->addSibling(new CocoImageSibling("BetText_xhdpi.png", 2, 128, 64));
		ImageSymbol_BetText->textureCellWidth = 64;
		ImageSymbol_BetText->textureCellHeight = 32;
		ImageSymbol_BetText->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_rectangleText = newResourceImage("ImageSymbol_rectangleText", "./assets/images/");
	{
		ImageSymbol_rectangleText->viewOptimalWidth = 64;
		ImageSymbol_rectangleText->viewOptimalHeight = 32;
		ImageSymbol_rectangleText->addSibling(new CocoImageSibling("rectangleText_mdpi.png", 1, 64, 32));
		ImageSymbol_rectangleText->addSibling(new CocoImageSibling("rectangleText_xhdpi.png", 2, 128, 64));
		ImageSymbol_rectangleText->textureCellWidth = 64;
		ImageSymbol_rectangleText->textureCellHeight = 32;
		ImageSymbol_rectangleText->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_no1 = newResourceImage("ImageSymbol_no1", "./assets/images/");
	{
		ImageSymbol_no1->viewOptimalWidth = 32;
		ImageSymbol_no1->viewOptimalHeight = 39;
		ImageSymbol_no1->addSibling(new CocoImageSibling("no1_mdpi.png", 1, 40, 49));
		ImageSymbol_no1->addSibling(new CocoImageSibling("no1_xhdpi.png", 2, 80, 98));
		ImageSymbol_no1->textureCellWidth = 40;
		ImageSymbol_no1->textureCellHeight = 49;
		ImageSymbol_no1->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_no2 = newResourceImage("ImageSymbol_no2", "./assets/images/");
	{
		ImageSymbol_no2->viewOptimalWidth = 32;
		ImageSymbol_no2->viewOptimalHeight = 39;
		ImageSymbol_no2->addSibling(new CocoImageSibling("no2_mdpi.png", 1, 40, 49));
		ImageSymbol_no2->addSibling(new CocoImageSibling("no2_xhdpi.png", 2, 80, 98));
		ImageSymbol_no2->textureCellWidth = 40;
		ImageSymbol_no2->textureCellHeight = 49;
		ImageSymbol_no2->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_no3 = newResourceImage("ImageSymbol_no3", "./assets/images/");
	{
		ImageSymbol_no3->viewOptimalWidth = 32;
		ImageSymbol_no3->viewOptimalHeight = 39;
		ImageSymbol_no3->addSibling(new CocoImageSibling("no3_mdpi.png", 1, 40, 49));
		ImageSymbol_no3->addSibling(new CocoImageSibling("no3_xhdpi.png", 2, 80, 98));
		ImageSymbol_no3->textureCellWidth = 40;
		ImageSymbol_no3->textureCellHeight = 49;
		ImageSymbol_no3->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_no4 = newResourceImage("ImageSymbol_no4", "./assets/images/");
	{
		ImageSymbol_no4->viewOptimalWidth = 32;
		ImageSymbol_no4->viewOptimalHeight = 39;
		ImageSymbol_no4->addSibling(new CocoImageSibling("no4_mdpi.png", 1, 40, 49));
		ImageSymbol_no4->addSibling(new CocoImageSibling("no4_xhdpi.png", 2, 80, 98));
		ImageSymbol_no4->textureCellWidth = 40;
		ImageSymbol_no4->textureCellHeight = 49;
		ImageSymbol_no4->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* ImageSymbol_btnPlayAgain = newResourceImage("ImageSymbol_btnPlayAgain", "./assets/images/");
	{
		ImageSymbol_btnPlayAgain->viewOptimalWidth = 59;
		ImageSymbol_btnPlayAgain->viewOptimalHeight = 59;
		ImageSymbol_btnPlayAgain->addSibling(new CocoImageSibling("btnPlayAgain_mdpi.png", 1, 99, 99));
		ImageSymbol_btnPlayAgain->addSibling(new CocoImageSibling("btnPlayAgain_xhdpi.png", 2, 198, 198));
		ImageSymbol_btnPlayAgain->textureCellWidth = 99;
		ImageSymbol_btnPlayAgain->textureCellHeight = 99;
		ImageSymbol_btnPlayAgain->textureGrid = new Float32Array({0, 0});
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addLabelEx(0, "Intro");
	__root->__timeline->addLabelEx(26, "openEnabled01");
	__root->__timeline->addLabelEx(51, "Busted");
	__root->__timeline->addLabelEx(27, "Win");
	__root->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
	{
		CocoClip* inst1 = new CocoClip();
		inst1->__instanceName = "gsBackground1";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst2 = new CocoClip(ImageSymbol_gsBackground, NULL, NULL);
			inst2->__instanceName = ":: ImageSymbol_gsBackground";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst3 = new CocoClip();
		inst3->__instanceName = "SlidingDoorLeft";
		__root->addChild(inst3);
		inst3->__timeline->clear();
		inst3->__timeline->addLabelEx(1, "busted");
		inst3->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -236, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -236, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -236, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst3->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -236, 6, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst4 = new CocoClip();
			inst4->__instanceName = "MedalDoorLeftShadow1";
			inst3->addChild(inst4);
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst4->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 2.352905, 0, 1, 1, 0, 0, 0, 1);
			inst4->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 331, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst5 = new CocoClip(ImageSymbol_MedalDoorLeftShadow, NULL, NULL);
				inst5->__instanceName = ":: ImageSymbol_MedalDoorLeftShadow";
				inst4->addChild(inst5);
				inst5->__timeline->clear();
				inst5->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst6 = new CocoClip();
			inst6->__instanceName = "MedalDoorLeftHalf1";
			inst3->addChild(inst6);
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst6->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 2.352905, 0, 1, 1, 0, 0, 0, 1);
			inst6->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 331, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst7 = new CocoClip(ImageSymbol_MedalDoorLeftHalf, NULL, NULL);
				inst7->__instanceName = ":: ImageSymbol_MedalDoorLeftHalf";
				inst6->addChild(inst7);
				inst7->__timeline->clear();
				inst7->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst8 = new CocoClip();
			inst8->__instanceName = "MetalDoorHalfBack1";
			inst3->addChild(inst8);
			inst8->__timeline->clear();
			inst8->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 146.5,  -1, 1, 1, 0, 0, 0, 1);
			inst8->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 146.5,  -3, 0.495, 0.495, 0, 0, 0, 0);
			{
				CocoClip* inst9 = new CocoClip(ImageSymbol_MetalDoorHalfBack, NULL, NULL);
				inst9->__instanceName = ":: ImageSymbol_MetalDoorHalfBack";
				inst8->addChild(inst9);
				inst9->__timeline->clear();
				inst9->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst10 = new CocoClip();
			inst10->__instanceName = "MetalDoorHalfBack2";
			inst3->addChild(inst10);
			inst10->__timeline->clear();
			inst10->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 81,  -1.559982, 1, 1, 0, 0, 0, 1);
			inst10->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 81,  -1.559982, 1, 1, 0, 0, 0, 0);
			{
				CocoClip* inst11 = new CocoClip(ImageSymbol_MetalDoorHalfBack, NULL, NULL);
				inst11->__instanceName = ":: ImageSymbol_MetalDoorHalfBack";
				inst10->addChild(inst11);
				inst11->__timeline->clear();
				inst11->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst12 = new CocoClip();
			inst12->__instanceName = "MetalDoorHalfHoles1";
			inst3->addChild(inst12);
			inst12->__timeline->clear();
			inst12->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 66.83333,  -5, 1, 1, 0, 0, 0, 0);
			inst12->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 95,  -5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst13 = new CocoClip(ImageSymbol_MetalDoorHalfHoles, NULL, NULL);
				inst13->__instanceName = ":: ImageSymbol_MetalDoorHalfHoles";
				inst12->addChild(inst13);
				inst13->__timeline->clear();
				inst13->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst14 = new CocoClip();
			inst14->__instanceName = "Actions";
			inst3->addChild(inst14);
			inst14->__timeline->clear();
			inst14->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			inst14->__timeline->addKeyFrameEx(stop, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst15 = new CocoClip();
		inst15->__instanceName = "SlidingDoorRight";
		__root->addChild(inst15);
		inst15->__timeline->clear();
		inst15->__timeline->addLabelEx(0, "idle");
		inst15->__timeline->addLabelEx(2, "busted");
		inst15->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 292, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst15->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 292, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst15->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 292, 6, 0.5, 0.5, 0, 0, 0, 1);
		inst15->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 292, 6, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst16 = new CocoClip();
			inst16->__instanceName = "MetalDoorShadow1";
			inst15->addChild(inst16);
			inst16->__timeline->clear();
			inst16->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst16->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst16->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst16->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -329, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst17 = new CocoClip(ImageSymbol_MetalDoorShadow, NULL, NULL);
				inst17->__instanceName = ":: ImageSymbol_MetalDoorShadow";
				inst16->addChild(inst17);
				inst17->__timeline->clear();
				inst17->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst18 = new CocoClip();
			inst18->__instanceName = "MetalDoorHalf1";
			inst15->addChild(inst18);
			inst18->__timeline->clear();
			inst18->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.5, 0, 1, 1, 0, 0, 0, 1);
			inst18->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.5, 0, 1, 1, 0, 0, 0, 1);
			inst18->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.5, 0, 1, 1, 0, 0, 0, 1);
			inst18->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -329, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst19 = new CocoClip(ImageSymbol_MetalDoorHalf, NULL, NULL);
				inst19->__instanceName = ":: ImageSymbol_MetalDoorHalf";
				inst18->addChild(inst19);
				inst19->__timeline->clear();
				inst19->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst20 = new CocoClip();
			inst20->__instanceName = "MetalDoorHalfBack1";
			inst15->addChild(inst20);
			inst20->__timeline->clear();
			inst20->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -261.6667,  -1, 1, 1, 0, 0, 0, 1);
			inst20->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -261.6667,  -1, 1, 1, 0, 0, 0, 1);
			inst20->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -530, 0, 1, 1, 0, 0, 0, 0);
			{
				CocoClip* inst21 = new CocoClip(ImageSymbol_MetalDoorHalfBack, NULL, NULL);
				inst21->__instanceName = ":: ImageSymbol_MetalDoorHalfBack";
				inst20->addChild(inst21);
				inst21->__timeline->clear();
				inst21->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst22 = new CocoClip();
			inst22->__instanceName = "MetalDoorHalfBack2";
			inst15->addChild(inst22);
			inst22->__timeline->clear();
			inst22->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -196.6667,  -1, 1, 1, 0, 0, 0, 1);
			inst22->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -196.6667,  -1, 1, 1, 0, 0, 0, 1);
			inst22->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -196.6667,  -1, 1, 1, 0, 0, 0, 0);
			{
				CocoClip* inst23 = new CocoClip(ImageSymbol_MetalDoorHalfBack, NULL, NULL);
				inst23->__instanceName = ":: ImageSymbol_MetalDoorHalfBack";
				inst22->addChild(inst23);
				inst23->__timeline->clear();
				inst23->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst24 = new CocoClip();
			inst24->__instanceName = "MetalDoorHalfHolesR1";
			inst15->addChild(inst24);
			inst24->__timeline->clear();
			inst24->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -200,  -5, 1, 1, 0, 0, 0, 0);
			inst24->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -200,  -5, 1, 1, 0, 0, 0, 0);
			inst24->__timeline->addKeyFrameEx(NULL, 3, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -202,  -5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst25 = new CocoClip(ImageSymbol_MetalDoorHalfHolesR, NULL, NULL);
				inst25->__instanceName = ":: ImageSymbol_MetalDoorHalfHolesR";
				inst24->addChild(inst25);
				inst25->__timeline->clear();
				inst25->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst26 = new CocoClip();
			inst26->__instanceName = "Actions";
			inst15->addChild(inst26);
			inst26->__timeline->clear();
			inst26->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			inst26->__timeline->addKeyFrameEx(stop, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst27 = new CocoClip();
		inst27->__instanceName = "stageLeftSide1";
		__root->addChild(inst27);
		inst27->__timeline->clear();
		inst27->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -220, 75.1, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst28 = new CocoClip(ImageSymbol_stageLeftSide, NULL, NULL);
			inst28->__instanceName = ":: ImageSymbol_stageLeftSide";
			inst27->addChild(inst28);
			inst28->__timeline->clear();
			inst28->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst29 = new CocoClip();
		inst29->__instanceName = "stageRightSide1";
		__root->addChild(inst29);
		inst29->__timeline->clear();
		inst29->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 259, 76, 0.5, 0.5, 0, 0, 0, 1);
		{
			CocoClip* inst30 = new CocoClip(ImageSymbol_stageRightSide, NULL, NULL);
			inst30->__instanceName = ":: ImageSymbol_stageRightSide";
			inst29->addChild(inst30);
			inst30->__timeline->clear();
			inst30->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst31 = new CocoClip();
		inst31->__instanceName = "LaserAnimFull";
		__root->addChild(inst31);
		inst31->__timeline->clear();
		inst31->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -5, 0.47, 0.47, 0, 0, 0, 1);
		inst31->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -5, 0.47, 0.47, 0, 0, 0, 1);
		{
			CocoClip* inst32 = new CocoClip();
			inst32->__instanceName = "Red_LASER1";
			inst31->addChild(inst32);
			inst32->__timeline->clear();
			inst32->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst32->__timeline->addKeyFrameEx(NULL, 7, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst32->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 0);
			inst32->__timeline->addKeyFrameEx(NULL, 24, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst33 = new CocoClip(ImageSymbol_Red_LASER, NULL, NULL);
				inst33->__instanceName = ":: ImageSymbol_Red_LASER";
				inst32->addChild(inst33);
				inst33->__timeline->clear();
				inst33->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
		}
		CocoClip* inst34 = new CocoClip();
		inst34->__instanceName = "thiefFullAnimation";
		__root->addChild(inst34);
		inst34->__timeline->clear();
		inst34->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -258, 0.35, 0.45, 0, 0, 0, 1);
		inst34->__timeline->addKeyFrameEx(NULL, 13, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -139.45, 0.3, 0.4, 0, 0, 0, 1);
		inst34->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -98, 0.4, 0.4, 0, 0, 0, 1);
		inst34->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -98, 0.4, 0.4, 0, 0, 0, 1);
		inst34->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -98, 0.4, 0.4, 0, 0, 0, 0);
		{
			CocoClip* inst35 = new CocoClip();
			inst35->__instanceName = "rope1";
			inst34->addChild(inst35);
			inst35->__timeline->clear();
			inst35->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 3.75,  -64.49994, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst36 = new CocoClip(ImageSymbol_rope, NULL, NULL);
				inst36->__instanceName = ":: ImageSymbol_rope";
				inst35->addChild(inst36);
				inst36->__timeline->clear();
				inst36->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst37 = new CocoClip();
			inst37->__instanceName = "shoe2";
			inst34->addChild(inst37);
			inst37->__timeline->clear();
			inst37->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 107.5, 129.5, 1, 1, 0, 0, 0, 1);
			inst37->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 108.5, 120.5, 1, 1, 0, 0, 0, 1);
			inst37->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 101.5, 140.5, 1, 1, 0, 0, 0, 1);
			inst37->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 107.5, 129.5, 1, 1, 0, 0, 0, 1);
			inst37->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 107.5, 129.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst38 = new CocoClip(ImageSymbol_shoe, NULL, NULL);
				inst38->__instanceName = ":: ImageSymbol_shoe";
				inst37->addChild(inst38);
				inst38->__timeline->clear();
				inst38->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst39 = new CocoClip();
			inst39->__instanceName = "shoe1";
			inst34->addChild(inst39);
			inst39->__timeline->clear();
			inst39->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -115.5, 129.5, 1, 1, 0, 0, 0, 1);
			inst39->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -105.5, 136.5, 1, 1, 0, 0, 0, 1);
			inst39->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -113.5, 118.5, 1, 1, 0, 0, 0, 1);
			inst39->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -115.5, 129.5, 1, 1, 0, 0, 0, 1);
			inst39->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -115.5, 129.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst40 = new CocoClip(ImageSymbol_shoe, NULL, NULL);
				inst40->__instanceName = ":: ImageSymbol_shoe";
				inst39->addChild(inst40);
				inst40->__timeline->clear();
				inst40->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst41 = new CocoClip();
			inst41->__instanceName = "legs1";
			inst34->addChild(inst41);
			inst41->__timeline->clear();
			inst41->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -3.5, 87.5, 1, 1, 0, 0, 0, 1);
			inst41->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.5, 87.5, 1, 1,  -3.2, 0, 0, 1);
			inst41->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -1.5, 87.5, 1, 1, 5.2, 0, 0, 1);
			inst41->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -3.5, 87.5, 1, 1, 0, 0, 0, 1);
			inst41->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -3.5, 87.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst42 = new CocoClip(ImageSymbol_legs, NULL, NULL);
				inst42->__instanceName = ":: ImageSymbol_legs";
				inst41->addChild(inst42);
				inst42->__timeline->clear();
				inst42->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst43 = new CocoClip();
			inst43->__instanceName = "body1";
			inst34->addChild(inst43);
			inst43->__timeline->clear();
			inst43->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -2, 31, 1, 1, 0, 0, 0, 1);
			inst43->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -2, 31, 1, 1,  -5.7, 0, 0, 1);
			inst43->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -1, 31, 1, 1, 1.9, 0, 0, 1);
			inst43->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -2, 31, 1, 1, 0, 0, 0, 1);
			inst43->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -2, 31, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst44 = new CocoClip(ImageSymbol_body, NULL, NULL);
				inst44->__instanceName = ":: ImageSymbol_body";
				inst43->addChild(inst44);
				inst44->__timeline->clear();
				inst44->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst45 = new CocoClip();
			inst45->__instanceName = "glove1";
			inst34->addChild(inst45);
			inst45->__timeline->clear();
			inst45->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -218,  -9.5, 1, 1, 0, 0, 0, 1);
			inst45->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -220, 41.5, 1, 1,  -15, 0, 0, 1);
			inst45->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -219,  -30.5, 1, 1,  -6.8, 0, 0, 1);
			inst45->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -218,  -9.5, 1, 1, 0, 0, 0, 1);
			inst45->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -218,  -9.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst46 = new CocoClip(ImageSymbol_glove, NULL, NULL);
				inst46->__instanceName = ":: ImageSymbol_glove";
				inst45->addChild(inst46);
				inst46->__timeline->clear();
				inst46->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst47 = new CocoClip();
			inst47->__instanceName = "glove2";
			inst34->addChild(inst47);
			inst47->__timeline->clear();
			inst47->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 203,  -12.5, 1, 1, 0, 0, 0, 1);
			inst47->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 208,  -61.5, 1, 1,  -15, 0, 0, 1);
			inst47->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 219,  -7.5, 1, 1,  -6.8, 0, 0, 1);
			inst47->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 203,  -12.5, 1, 1, 0, 0, 0, 1);
			inst47->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 203,  -12.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst48 = new CocoClip(ImageSymbol_glove, NULL, NULL);
				inst48->__instanceName = ":: ImageSymbol_glove";
				inst47->addChild(inst48);
				inst48->__timeline->clear();
				inst48->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst49 = new CocoClip();
			inst49->__instanceName = "arm1";
			inst34->addChild(inst49);
			inst49->__timeline->clear();
			inst49->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 62, 5.5, 1, 1, 0, 0, 0, 1);
			inst49->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 73,  -6.5, 1, 1,  -15, 0, 0, 1);
			inst49->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 74, 9.5, 1, 1, 3.2, 0, 0, 1);
			inst49->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 62, 5.5, 1, 1, 0, 0, 0, 1);
			inst49->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 62, 5.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst50 = new CocoClip(ImageSymbol_arm, NULL, NULL);
				inst50->__instanceName = ":: ImageSymbol_arm";
				inst49->addChild(inst50);
				inst50->__timeline->clear();
				inst50->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst51 = new CocoClip();
			inst51->__instanceName = "arm2";
			inst34->addChild(inst51);
			inst51->__timeline->clear();
			inst51->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -76, 10, 1, 1, 0, 0, 0, 1);
			inst51->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -76, 22, 1, 1,  -15, 0, 0, 1);
			inst51->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -79,  -1, 1, 1, 8.2, 0, 0, 1);
			inst51->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -76, 10, 1, 1, 0, 0, 0, 1);
			inst51->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -76, 10, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst52 = new CocoClip(ImageSymbol_arm, NULL, NULL);
				inst52->__instanceName = ":: ImageSymbol_arm";
				inst51->addChild(inst52);
				inst52->__timeline->clear();
				inst52->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst53 = new CocoClip();
			inst53->__instanceName = "thiefHead1";
			inst34->addChild(inst53);
			inst53->__timeline->clear();
			inst53->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 3, 20.12286, 1, 1, 0, 0, 0, 1);
			inst53->__timeline->addKeyFrameEx(NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 3, 26.3, 1, 1, 0, 0, 0, 1);
			inst53->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 3, 17, 1, 1, 0, 0, 0, 1);
			inst53->__timeline->addKeyFrameEx(NULL, 105, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 3, 20.12286, 1, 1, 0, 0, 0, 1);
			inst53->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 3, 20.12286, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst54 = new CocoClip(SpriteSymbol_thiefHead, NULL, NULL);
				inst54->__instanceName = ":: SpriteSymbol_thiefHead";
				inst53->addChild(inst54);
				inst54->__timeline->clear();
				inst54->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
		}
		CocoClip* inst55 = new CocoClip();
		inst55->__instanceName = "thiefBustedAnimation";
		__root->addChild(inst55);
		inst55->__timeline->clear();
		inst55->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -1,  -85, 0.4, 0.4, 0, 0, 0, 1);
		inst55->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -1,  -85, 0.4, 0.4, 0, 0, 0, 1);
		{
			CocoClip* inst56 = new CocoClip();
			inst56->__instanceName = "rope1";
			inst55->addChild(inst56);
			inst56->__timeline->clear();
			inst56->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 4.5,  -95.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst57 = new CocoClip(ImageSymbol_rope, NULL, NULL);
				inst57->__instanceName = ":: ImageSymbol_rope";
				inst56->addChild(inst57);
				inst57->__timeline->clear();
				inst57->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst58 = new CocoClip();
			inst58->__instanceName = "shoe2";
			inst55->addChild(inst58);
			inst58->__timeline->clear();
			inst58->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 110.5, 98.5, 1, 1, 0, 0, 0, 1);
			inst58->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 112.5, 88.5, 1, 1, 0, 0, 0, 1);
			inst58->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 110.5, 97.5, 1, 1, 0, 0, 0, 1);
			inst58->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 110.5, 97.5, 1, 1, 0, 0, 0, 1);
			inst58->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 110.5, 97.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst59 = new CocoClip(ImageSymbol_shoe, NULL, NULL);
				inst59->__instanceName = ":: ImageSymbol_shoe";
				inst58->addChild(inst59);
				inst59->__timeline->clear();
				inst59->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst60 = new CocoClip();
			inst60->__instanceName = "shoe1";
			inst55->addChild(inst60);
			inst60->__timeline->clear();
			inst60->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -111.5, 97.5, 1, 1, 0, 0, 0, 1);
			inst60->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -103.5, 105.5, 1, 1, 0, 0, 0, 1);
			inst60->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -112.5, 98.5, 1, 1, 0, 0, 0, 1);
			inst60->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -112.5, 98.5, 1, 1, 0, 0, 0, 1);
			inst60->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -112.5, 98.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst61 = new CocoClip(ImageSymbol_shoe, NULL, NULL);
				inst61->__instanceName = ":: ImageSymbol_shoe";
				inst60->addChild(inst61);
				inst61->__timeline->clear();
				inst61->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst62 = new CocoClip();
			inst62->__instanceName = "legs1";
			inst55->addChild(inst62);
			inst62->__timeline->clear();
			inst62->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.5, 55.5, 1, 1, 0, 0, 0, 1);
			inst62->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 2.5, 57.5, 1, 1,  -3.2, 0, 0, 1);
			inst62->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.5, 57.5, 1, 1, 0, 0, 0, 1);
			inst62->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.5, 57.5, 1, 1, 0, 0, 0, 1);
			inst62->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.5, 57.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst63 = new CocoClip(ImageSymbol_legs, NULL, NULL);
				inst63->__instanceName = ":: ImageSymbol_legs";
				inst62->addChild(inst63);
				inst63->__timeline->clear();
				inst63->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst64 = new CocoClip();
			inst64->__instanceName = "body1";
			inst55->addChild(inst64);
			inst64->__timeline->clear();
			inst64->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst64->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1,  -5.7, 0, 0, 1);
			inst64->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst64->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst64->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst65 = new CocoClip(ImageSymbol_body, NULL, NULL);
				inst65->__instanceName = ":: ImageSymbol_body";
				inst64->addChild(inst65);
				inst65->__timeline->clear();
				inst65->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst66 = new CocoClip();
			inst66->__instanceName = "glove1";
			inst55->addChild(inst66);
			inst66->__timeline->clear();
			inst66->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -214.5,  -41.5, 1, 1, 0, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -217.5, 10.5, 1, 1,  -15, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -210.5, 69.5, 1, 1,  -15, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -154.5, 153.5, 1, 1,  -47.6, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 22, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -88.5, 182.5, 1, 1,  -61.4, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -19.5, 201.5, 1, 1,  -75, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -19.5, 201.5, 1, 1,  -75, 0, 0, 1);
			inst66->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -19.5, 201.5, 1, 1,  -75, 0, 0, 1);
			{
				CocoClip* inst67 = new CocoClip(ImageSymbol_glove, NULL, NULL);
				inst67->__instanceName = ":: ImageSymbol_glove";
				inst66->addChild(inst67);
				inst67->__timeline->clear();
				inst67->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst68 = new CocoClip();
			inst68->__instanceName = "glove2";
			inst55->addChild(inst68);
			inst68->__timeline->clear();
			inst68->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 205.5,  -44.5, 1, 1, 0, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 209.5,  -93.5, 1, 1,  -15, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 225.5,  -2.5, 1, 1,  -15, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 177.5, 134.5, 1, 1, 33.8, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 22, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 104.5, 177.5, 1, 1, 54.4, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 22.5, 200.5, 1, 1, 75, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 22.5, 200.5, 1, 1, 75, 0, 0, 1);
			inst68->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 22.5, 200.5, 1, 1, 75, 0, 0, 1);
			{
				CocoClip* inst69 = new CocoClip(ImageSymbol_glove, NULL, NULL);
				inst69->__instanceName = ":: ImageSymbol_glove";
				inst68->addChild(inst69);
				inst69->__timeline->clear();
				inst69->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst70 = new CocoClip();
			inst70->__instanceName = "arm1";
			inst55->addChild(inst70);
			inst70->__timeline->clear();
			inst70->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 63.5,  -26.5, 1, 1, 0, 0, 0, 1);
			inst70->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 75.5,  -38.5, 1, 1,  -15, 0, 0, 1);
			inst70->__timeline->addKeyFrameEx(NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 75.5, 30.5, 1, 1, 58.2, 0, 0, 1);
			inst70->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 25.5, 52.5, 1, 1, 104.5, 0, 0, 1);
			inst70->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 25.5, 52.5, 1, 1, 104.5, 0, 0, 1);
			inst70->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 25.5, 52.5, 1, 1, 104.5, 0, 0, 1);
			{
				CocoClip* inst71 = new CocoClip(ImageSymbol_arm, NULL, NULL);
				inst71->__instanceName = ":: ImageSymbol_arm";
				inst70->addChild(inst71);
				inst71->__timeline->clear();
				inst71->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst72 = new CocoClip();
			inst72->__instanceName = "arm2";
			inst55->addChild(inst72);
			inst72->__timeline->clear();
			inst72->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -73.5,  -23.5, 1, 1, 0, 0, 0, 1);
			inst72->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -73.5,  -10.5, 1, 1,  -15, 0, 0, 1);
			inst72->__timeline->addKeyFrameEx(NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -67.5, 35.5, 1, 1,  -63.9, 0, 0, 1);
			inst72->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -21.5, 52.5, 1, 1,  -105, 0, 0, 1);
			inst72->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -21.5, 52.5, 1, 1,  -105, 0, 0, 1);
			inst72->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -21.5, 52.5, 1, 1,  -105, 0, 0, 1);
			{
				CocoClip* inst73 = new CocoClip(ImageSymbol_arm, NULL, NULL);
				inst73->__instanceName = ":: ImageSymbol_arm";
				inst72->addChild(inst73);
				inst73->__timeline->clear();
				inst73->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst74 = new CocoClip();
			inst74->__instanceName = "busted_fasa";
			inst55->addChild(inst74);
			inst74->__timeline->clear();
			inst74->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 997.4999,  -220, 1, 1,  -1080, 0, 0, 1);
			inst74->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 42.49994, 92.49998, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst75 = new CocoClip(ImageSymbol_busted_fasa, NULL, NULL);
				inst75->__instanceName = ":: ImageSymbol_busted_fasa";
				inst74->addChild(inst75);
				inst75->__timeline->clear();
				inst75->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst76 = new CocoClip();
			inst76->__instanceName = "busted";
			inst55->addChild(inst76);
			inst76->__timeline->clear();
			inst76->__timeline->addKeyFrameEx(NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 12.49994, 91.15009, 1, 1, 156.5,  -107.5, 0, 0);
			inst76->__timeline->addKeyFrameEx(NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 17.49994, 93.65009, 1, 1, 0,  -107.5, 0, 1);
			inst76->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 17.49994, 93.65009, 1.1, 1.1, 0,  -107.5, 0, 1);
			inst76->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 17.49994, 93.65009, 1, 1, 0,  -107.5, 0, 1);
			{
				CocoClip* inst77 = new CocoClip(ImageSymbol_busted, NULL, NULL);
				inst77->__instanceName = ":: ImageSymbol_busted";
				inst76->addChild(inst77);
				inst77->__timeline->clear();
				inst77->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst78 = new CocoClip();
			inst78->__instanceName = "thiefBusted1";
			inst55->addChild(inst78);
			inst78->__timeline->clear();
			inst78->__timeline->addKeyFrameEx(changeSequence, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 5.833313,  -10.83334, 1, 1, 0, 0, 0, 1);
			inst78->__timeline->addKeyFrameEx(changeSequence, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 5.833313,  -4.16668, 1, 1, 0, 0, 0, 1);
			inst78->__timeline->addKeyFrameEx(changeSequence, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 5.833313,  -9.166679, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst79 = new CocoClip(SpriteSymbol_thiefBusted, NULL, NULL);
				inst79->__instanceName = ":: SpriteSymbol_thiefBusted";
				inst78->addChild(inst79);
				inst79->__timeline->clear();
				inst79->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst80 = new CocoClip();
			inst80->__instanceName = "HANDCOUGHS1";
			inst55->addChild(inst80);
			inst80->__timeline->clear();
			inst80->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.1, 166.06, 1.1, 1.1, 0, 0, 0, 1);
			inst80->__timeline->addKeyFrameEx(NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.1, 166.06, 1.1, 1.1, 0, 0, 0, 1);
			{
				CocoClip* inst81 = new CocoClip(ImageSymbol_HANDCOUGHS, NULL, NULL);
				inst81->__instanceName = ":: ImageSymbol_HANDCOUGHS";
				inst80->addChild(inst81);
				inst81->__timeline->clear();
				inst81->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst82 = new CocoClip();
			inst82->__instanceName = "Actions";
			inst55->addChild(inst82);
			inst82->__timeline->clear();
			inst82->__timeline->addKeyFrameEx(stop, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst83 = new CocoClip();
		inst83->__instanceName = "Safes";
		__root->addChild(inst83);
		inst83->__timeline->clear();
		inst83->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -38,  -13, 0.7, 0.7, 0, 0, 0, 1);
		inst83->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -38,  -13, 0.7, 0.7, 0, 0, 0, 1);
		{
			CocoClip* inst84 = new CocoClip();
			inst84->__instanceName = "SafeAnimationFull1";
			inst83->addChild(inst84);
			inst84->__timeline->clear();
			inst84->__timeline->addLabelEx(0, "idle");
			inst84->__timeline->addLabelEx(1, "win");
			inst84->__timeline->addLabelEx(2, "lose");
			inst84->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -225.5, 40.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst85 = new CocoClip();
				inst85->__instanceName = "safe_closed_idle1";
				inst84->addChild(inst85);
				inst85->__timeline->clear();
				inst85->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 55.5, 16.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst86 = new CocoClip(ImageSymbol_safe_closed_idle, NULL, NULL);
					inst86->__instanceName = ":: ImageSymbol_safe_closed_idle";
					inst85->addChild(inst86);
					inst86->__timeline->clear();
					inst86->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst87 = new CocoClip();
				inst87->__instanceName = "Safe_WinOnly1";
				inst84->addChild(inst87);
				inst87->__timeline->clear();
				inst87->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 309.119,  -53.14287, 1, 1, 0, 0, 0, 0);
				inst87->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 309.119,  -53.14287, 1, 1, 0, 0, 0, 1);
				inst87->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 309.119,  -53.14287, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst88 = new CocoClip(SpriteSymbol_Safe_WinOnly, NULL, NULL);
					inst88->__instanceName = ":: SpriteSymbol_Safe_WinOnly";
					inst87->addChild(inst88);
					inst88->__timeline->clear();
					inst88->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst89 = new CocoClip();
				inst89->__instanceName = "Safe_Lose1";
				inst84->addChild(inst89);
				inst89->__timeline->clear();
				inst89->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 307.1429,  -52.21429, 1, 1, 0, 0, 0, 0);
				inst89->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 307.1429,  -52.21429, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst90 = new CocoClip(SpriteSymbol_Safe_Lose, NULL, NULL);
					inst90->__instanceName = ":: SpriteSymbol_Safe_Lose";
					inst89->addChild(inst90);
					inst90->__timeline->clear();
					inst90->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst91 = new CocoClip();
				inst91->__instanceName = "Actions";
				inst84->addChild(inst91);
				inst91->__timeline->clear();
				inst91->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst91->__timeline->addKeyFrameEx(stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
				inst91->__timeline->addKeyFrameEx(stop, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst92 = new CocoClip();
			inst92->__instanceName = "SafeAnimationFull2";
			inst83->addChild(inst92);
			inst92->__timeline->clear();
			inst92->__timeline->addLabelEx(0, "idle");
			inst92->__timeline->addLabelEx(1, "win");
			inst92->__timeline->addLabelEx(2, "lose");
			inst92->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -76.16666, 40.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst93 = new CocoClip();
				inst93->__instanceName = "safe_closed_idle1";
				inst92->addChild(inst93);
				inst93->__timeline->clear();
				inst93->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 55.5, 16.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst94 = new CocoClip(ImageSymbol_safe_closed_idle, NULL, NULL);
					inst94->__instanceName = ":: ImageSymbol_safe_closed_idle";
					inst93->addChild(inst94);
					inst94->__timeline->clear();
					inst94->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst95 = new CocoClip();
				inst95->__instanceName = "Safe_WinOnly1";
				inst92->addChild(inst95);
				inst95->__timeline->clear();
				inst95->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 159.3095,  -51.7143, 1, 1, 0, 0, 0, 0);
				inst95->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 159.3095,  -51.7143, 1, 1, 0, 0, 0, 1);
				inst95->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 159.3095,  -51.7143, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst96 = new CocoClip(SpriteSymbol_Safe_WinOnly, NULL, NULL);
					inst96->__instanceName = ":: SpriteSymbol_Safe_WinOnly";
					inst95->addChild(inst96);
					inst96->__timeline->clear();
					inst96->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst97 = new CocoClip();
				inst97->__instanceName = "Safe_Lose1";
				inst92->addChild(inst97);
				inst97->__timeline->clear();
				inst97->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 157.8095,  -52.21429, 1, 1, 0, 0, 0, 0);
				inst97->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 157.8095,  -52.21429, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst98 = new CocoClip(SpriteSymbol_Safe_Lose, NULL, NULL);
					inst98->__instanceName = ":: SpriteSymbol_Safe_Lose";
					inst97->addChild(inst98);
					inst98->__timeline->clear();
					inst98->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst99 = new CocoClip();
				inst99->__instanceName = "Actions";
				inst92->addChild(inst99);
				inst99->__timeline->clear();
				inst99->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst99->__timeline->addKeyFrameEx(stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
				inst99->__timeline->addKeyFrameEx(stop, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst100 = new CocoClip();
			inst100->__instanceName = "SafeAnimationFull3";
			inst83->addChild(inst100);
			inst100->__timeline->clear();
			inst100->__timeline->addLabelEx(0, "idle");
			inst100->__timeline->addLabelEx(1, "win");
			inst100->__timeline->addLabelEx(2, "lose");
			inst100->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 73.16666, 40.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst101 = new CocoClip();
				inst101->__instanceName = "safe_closed_idle1";
				inst100->addChild(inst101);
				inst101->__timeline->clear();
				inst101->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 55.5, 16.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst102 = new CocoClip(ImageSymbol_safe_closed_idle, NULL, NULL);
					inst102->__instanceName = ":: ImageSymbol_safe_closed_idle";
					inst101->addChild(inst102);
					inst102->__timeline->clear();
					inst102->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst103 = new CocoClip();
				inst103->__instanceName = "Safe_WinOnly1";
				inst100->addChild(inst103);
				inst103->__timeline->clear();
				inst103->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 9.976205,  -51.7143, 1, 1, 0, 0, 0, 0);
				inst103->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 9.976205,  -51.7143, 1, 1, 0, 0, 0, 1);
				inst103->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 9.976205,  -51.7143, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst104 = new CocoClip(SpriteSymbol_Safe_WinOnly, NULL, NULL);
					inst104->__instanceName = ":: SpriteSymbol_Safe_WinOnly";
					inst103->addChild(inst104);
					inst104->__timeline->clear();
					inst104->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst105 = new CocoClip();
				inst105->__instanceName = "Safe_Lose1";
				inst100->addChild(inst105);
				inst105->__timeline->clear();
				inst105->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 8.4762,  -52.21429, 1, 1, 0, 0, 0, 0);
				inst105->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 8.4762,  -52.21429, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst106 = new CocoClip(SpriteSymbol_Safe_Lose, NULL, NULL);
					inst106->__instanceName = ":: SpriteSymbol_Safe_Lose";
					inst105->addChild(inst106);
					inst106->__timeline->clear();
					inst106->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst107 = new CocoClip();
				inst107->__instanceName = "Actions";
				inst100->addChild(inst107);
				inst107->__timeline->clear();
				inst107->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst107->__timeline->addKeyFrameEx(stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
				inst107->__timeline->addKeyFrameEx(stop, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst108 = new CocoClip();
			inst108->__instanceName = "SafeAnimationFull4";
			inst83->addChild(inst108);
			inst108->__timeline->clear();
			inst108->__timeline->addLabelEx(0, "idle");
			inst108->__timeline->addLabelEx(1, "win");
			inst108->__timeline->addLabelEx(2, "lose");
			inst108->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 222.5, 40.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst109 = new CocoClip();
				inst109->__instanceName = "safe_closed_idle1";
				inst108->addChild(inst109);
				inst109->__timeline->clear();
				inst109->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 55.5, 16.5, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst110 = new CocoClip(ImageSymbol_safe_closed_idle, NULL, NULL);
					inst110->__instanceName = ":: ImageSymbol_safe_closed_idle";
					inst109->addChild(inst110);
					inst110->__timeline->clear();
					inst110->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst111 = new CocoClip();
				inst111->__instanceName = "Safe_WinOnly1";
				inst108->addChild(inst111);
				inst111->__timeline->clear();
				inst111->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false,  -139.3571,  -51.7143, 1, 1, 0, 0, 0, 0);
				inst111->__timeline->addKeyFrameEx(NULL, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false,  -139.3571,  -51.7143, 1, 1, 0, 0, 0, 1);
				inst111->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false,  -139.3571,  -51.7143, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst112 = new CocoClip(SpriteSymbol_Safe_WinOnly, NULL, NULL);
					inst112->__instanceName = ":: SpriteSymbol_Safe_WinOnly";
					inst111->addChild(inst112);
					inst112->__timeline->clear();
					inst112->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst113 = new CocoClip();
				inst113->__instanceName = "Safe_Lose1";
				inst108->addChild(inst113);
				inst113->__timeline->clear();
				inst113->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false,  -140.8571,  -52.21429, 1, 1, 0, 0, 0, 0);
				inst113->__timeline->addKeyFrameEx(NULL, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false,  -140.8571,  -52.21429, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst114 = new CocoClip(SpriteSymbol_Safe_Lose, NULL, NULL);
					inst114->__instanceName = ":: SpriteSymbol_Safe_Lose";
					inst113->addChild(inst114);
					inst114->__timeline->clear();
					inst114->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst115 = new CocoClip();
				inst115->__instanceName = "Actions";
				inst108->addChild(inst115);
				inst115->__timeline->clear();
				inst115->__timeline->addKeyFrameEx(stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst115->__timeline->addKeyFrameEx(stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
				inst115->__timeline->addKeyFrameEx(stop, 2, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
			}
		}
		CocoClip* inst116 = new CocoClip();
		inst116->__instanceName = "WinningsBar1";
		__root->addChild(inst116);
		inst116->__timeline->clear();
		inst116->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 178,  -125, 0.5, 0.45, 0, 0, 0, 1);
		{
			CocoClip* inst117 = new CocoClip(ImageSymbol_WinningsBar, NULL, NULL);
			inst117->__instanceName = ":: ImageSymbol_WinningsBar";
			inst116->addChild(inst117);
			inst117->__timeline->clear();
			inst117->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst118 = new CocoClip();
		inst118->__instanceName = "BalanceBar1";
		__root->addChild(inst118);
		inst118->__timeline->clear();
		inst118->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -178,  -125, 0.5, 0.45, 0, 0, 0, 1);
		{
			CocoClip* inst119 = new CocoClip(ImageSymbol_BalanceBar, NULL, NULL);
			inst119->__instanceName = ":: ImageSymbol_BalanceBar";
			inst118->addChild(inst119);
			inst119->__timeline->clear();
			inst119->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst121 = new CocoClip();
		inst121->__instanceName = "GuardLayer";
		__root->addChild(inst121);
		inst121->__timeline->clear();
		inst121->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -438, 86, 0.4, 0.4,  -21, 0, 0, 1);
		inst121->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -172, 27, 0.4, 0.4, 11.2, 0, 0, 1);
		inst121->__timeline->addKeyFrameEx(NULL, 74, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -146, 21, 0.4, 0.4, 0.8, 0, 0, 1);
		inst121->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -146, 21, 0.4, 0.4, 0.8, 0, 0, 1);
		{
			CocoClip* inst122 = new CocoClip();
			inst122->__instanceName = "GuardAnim";
			inst121->addChild(inst122);
			inst122->__timeline->clear();
			inst122->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 38.75, 246.25, 1, 1, 0, 38.75, 246.25, 1);
			inst122->__timeline->addKeyFrameEx(NULL, 28, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 38.75, 246.25, 1, 1.02, 0, 38.75, 246.25, 1);
			inst122->__timeline->addKeyFrameEx(NULL, 54, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 38.75, 246.25, 1, 1, 0, 38.75, 246.25, 1);
			inst122->__timeline->addKeyFrameEx(NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 38.75, 246.25, 1, 1, 0, 38.75, 246.25, 1);
			{
				CocoClip* inst123 = new CocoClip();
				inst123->__instanceName = "security1";
				inst122->addChild(inst123);
				inst123->__timeline->clear();
				inst123->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst124 = new CocoClip(ImageSymbol_security, NULL, NULL);
					inst124->__instanceName = ":: ImageSymbol_security";
					inst123->addChild(inst124);
					inst124->__timeline->clear();
					inst124->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst125 = new CocoClip();
				inst125->__instanceName = "guardHandcoughs1";
				inst122->addChild(inst125);
				inst125->__timeline->clear();
				inst125->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216.4757,  -46.13897, 1, 1,  -1440,  -24.11423,  -127.1809, 1);
				inst125->__timeline->addKeyFrameEx(NULL, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216.4757,  -46.13897, 1, 1, 0,  -24.11423,  -127.1809, 1);
				inst125->__timeline->addKeyFrameEx(NULL, 58, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 216.4757,  -46.13897, 1, 1, 71.2,  -24.11423,  -127.1809, 1);
				inst125->__timeline->addKeyFrameEx(NULL, 65, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 217.8128,  -39.90703, 1, 1,  -33.2,  -24.11423,  -127.1809, 1);
				inst125->__timeline->addKeyFrameEx(NULL, 73, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 196.722,  -28.36143, 1, 1, 14.4,  -38.38013,  -112.9424, 1);
				inst125->__timeline->addKeyFrameEx(NULL, 120, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 199.117,  -35.8956, 1, 1, 14.4,  -38.38013,  -112.9424, 1);
				{
					CocoClip* inst126 = new CocoClip(ImageSymbol_guardHandcoughs, NULL, NULL);
					inst126->__instanceName = ":: ImageSymbol_guardHandcoughs";
					inst125->addChild(inst126);
					inst126->__timeline->clear();
					inst126->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
				CocoClip* inst127 = new CocoClip();
				inst127->__instanceName = "FINGERTIP1";
				inst122->addChild(inst127);
				inst127->__timeline->clear();
				inst127->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 224.1667,  -47.08329, 1, 1, 0, 0, 0, 1);
				{
					CocoClip* inst128 = new CocoClip(ImageSymbol_FINGERTIP, NULL, NULL);
					inst128->__instanceName = ":: ImageSymbol_FINGERTIP";
					inst127->addChild(inst128);
					inst128->__timeline->clear();
					inst128->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
			}
		}
		CocoClip* inst130 = new CocoClip();
		inst130->__instanceName = "bettingBar1";
		__root->addChild(inst130);
		inst130->__timeline->clear();
		inst130->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4, 138.5, 0.88, 0.7, 0, 0, 0, 1);
		{
			CocoClip* inst131 = new CocoClip(ImageSymbol_bettingBar, NULL, NULL);
			inst131->__instanceName = ":: ImageSymbol_bettingBar";
			inst130->addChild(inst131);
			inst131->__timeline->clear();
			inst131->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst132 = new CocoClip();
		inst132->__instanceName = "btnBuyTicket1";
		__root->addChild(inst132);
		inst132->__timeline->clear();
		inst132->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -191, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		inst132->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -191, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		inst132->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -191, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		{
			CocoClip* inst133 = new CocoClip(ImageSymbol_btnBuyTicket, NULL, NULL);
			inst133->__instanceName = ":: ImageSymbol_btnBuyTicket";
			inst132->addChild(inst133);
			inst133->__timeline->clear();
			inst133->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst134 = new CocoClip();
		inst134->__instanceName = "btnOpenAll1";
		__root->addChild(inst134);
		inst134->__timeline->clear();
		inst134->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		inst134->__timeline->addKeyFrameEx(NULL, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		inst134->__timeline->addKeyFrameEx(NULL, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 0);
		{
			CocoClip* inst135 = new CocoClip(ImageSymbol_btnOpenAll, NULL, NULL);
			inst135->__instanceName = ":: ImageSymbol_btnOpenAll";
			inst134->addChild(inst135);
			inst135->__timeline->clear();
			inst135->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst136 = new CocoClip();
		inst136->__instanceName = "btnPlayAgain1";
		__root->addChild(inst136);
		inst136->__timeline->clear();
		inst136->__timeline->addKeyFrameEx(btnPlayAgainClicked, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		inst136->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 0);
		inst136->__timeline->addKeyFrameEx(btnPlayAgainClicked, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193, 125.5, 0.6, 0.6, 0, 0, 0, 1);
		{
			CocoClip* inst137 = new CocoClip(ImageSymbol_btnPlayAgain, NULL, NULL);
			inst137->__instanceName = ":: ImageSymbol_btnPlayAgain";
			inst136->addChild(inst137);
			inst137->__timeline->clear();
			inst137->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst138 = new CocoClip();
		inst138->__instanceName = "YouWin";
		__root->addChild(inst138);
		inst138->__timeline->clear();
		inst138->__timeline->addKeyFrameEx(NULL, 27, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -6, 28, 0.5, 0.5, 0, 0, 0, 1);
		inst138->__timeline->addKeyFrameEx(NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -6, 28, 0.5, 0.5, 0, 0, 0, 0);
		{
			CocoClip* inst139 = new CocoClip();
			inst139->__instanceName = "Glow";
			inst138->addChild(inst139);
			inst139->__timeline->clear();
			inst139->__timeline->addKeyFrameEx(NULL, 34, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			inst139->__timeline->addKeyFrameEx(NULL, 110, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst140 = new CocoClip();
				inst140->__instanceName = "thiefGlow1";
				inst139->addChild(inst140);
				inst140->__timeline->clear();
				inst140->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -62, 1, 1, 0, 0, 0, 0);
				inst140->__timeline->addKeyFrameEx(NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -62, 1, 1, 0, 0, 0, 1);
				inst140->__timeline->addKeyFrameEx(NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -62, 1, 1, 0, 0, 0, 0);
				{
					CocoClip* inst141 = new CocoClip(ImageSymbol_thiefGlow, NULL, NULL);
					inst141->__instanceName = ":: ImageSymbol_thiefGlow";
					inst140->addChild(inst141);
					inst141->__timeline->clear();
					inst141->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				}
			}
			CocoClip* inst142 = new CocoClip();
			inst142->__instanceName = "disk";
			inst138->addChild(inst142);
			inst142->__timeline->clear();
			inst142->__timeline->addKeyFrameEx(NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 610.5, 0, 1, 1, 0, 0, 0, 1);
			inst142->__timeline->addKeyFrameEx(NULL, 34, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst143 = new CocoClip(ImageSymbol_florr, NULL, NULL);
				inst143->__instanceName = ":: ImageSymbol_florr";
				inst142->addChild(inst143);
				inst143->__timeline->clear();
				inst143->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst144 = new CocoClip();
			inst144->__instanceName = "money11";
			inst138->addChild(inst144);
			inst144->__timeline->clear();
			inst144->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 36.53, 1.5, 0.5, 0.5, 0, 0, 0, 1);
			inst144->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 72.53,  -228.5, 0.7, 0.7, 135, 0, 0, 1);
			inst144->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 100.53,  -222.5, 0.71, 0.71, 165, 0, 0, 1);
			inst144->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 226.53, 39.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst145 = new CocoClip(ImageSymbol_money1, NULL, NULL);
				inst145->__instanceName = ":: ImageSymbol_money1";
				inst144->addChild(inst145);
				inst145->__timeline->clear();
				inst145->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst146 = new CocoClip();
			inst146->__instanceName = "money12";
			inst138->addChild(inst146);
			inst146->__timeline->clear();
			inst146->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 36.53, 1.5, 0.5, 0.5, 0, 0, 0, 1);
			inst146->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 170.53,  -251.5, 1, 1, 0, 0, 0, 1);
			inst146->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 170.53,  -251.5, 1, 1, 0, 0, 0, 1);
			inst146->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 226.53, 39.5, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst147 = new CocoClip(ImageSymbol_money1, NULL, NULL);
				inst147->__instanceName = ":: ImageSymbol_money1";
				inst146->addChild(inst147);
				inst147->__timeline->clear();
				inst147->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst148 = new CocoClip();
			inst148->__instanceName = "money21";
			inst138->addChild(inst148);
			inst148->__timeline->clear();
			inst148->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -24.47, 0, 0.5, 0.5, 0, 0, 0, 1);
			inst148->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -3.470004,  -203, 0.6, 0.6,  -150, 0, 0, 1);
			inst148->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 50.52999,  -227, 0.7, 0.7,  -45, 0, 0, 1);
			inst148->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -48.47001, 24, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst149 = new CocoClip(ImageSymbol_money2, NULL, NULL);
				inst149->__instanceName = ":: ImageSymbol_money2";
				inst148->addChild(inst149);
				inst149->__timeline->clear();
				inst149->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst150 = new CocoClip();
			inst150->__instanceName = "money22";
			inst138->addChild(inst150);
			inst150->__timeline->clear();
			inst150->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -24.47, 0, 0.5, 0.5, 0, 0, 0, 1);
			inst150->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -36.47001,  -251, 1, 1, 0, 0, 0, 1);
			inst150->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -36.47001,  -251, 1, 1, 0, 0, 0, 1);
			inst150->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -48.47001, 24, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst151 = new CocoClip(ImageSymbol_money2, NULL, NULL);
				inst151->__instanceName = ":: ImageSymbol_money2";
				inst150->addChild(inst151);
				inst151->__timeline->clear();
				inst151->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst152 = new CocoClip();
			inst152->__instanceName = "money31";
			inst138->addChild(inst152);
			inst152->__timeline->clear();
			inst152->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -70,  -6.5, 0.5, 0.5, 0, 0, 0, 1);
			inst152->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -139,  -223.5, 0.5, 0.5, 180, 0, 0, 1);
			inst152->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -154,  -228.5, 0.5, 0.5, 0, 0, 0, 1);
			inst152->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -220, 35.49998, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst153 = new CocoClip(ImageSymbol_money3, NULL, NULL);
				inst153->__instanceName = ":: ImageSymbol_money3";
				inst152->addChild(inst153);
				inst153->__timeline->clear();
				inst153->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst154 = new CocoClip();
			inst154->__instanceName = "money32";
			inst138->addChild(inst154);
			inst154->__timeline->clear();
			inst154->__timeline->addKeyFrameEx(NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -70,  -6.5, 0.5, 0.5, 0, 0, 0, 1);
			inst154->__timeline->addKeyFrameEx(NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -192,  -249.5, 1, 1, 0, 0, 0, 1);
			inst154->__timeline->addKeyFrameEx(NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -192,  -249.5, 1, 1, 0, 0, 0, 1);
			inst154->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -220, 35.49998, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst155 = new CocoClip(ImageSymbol_money3, NULL, NULL);
				inst155->__instanceName = ":: ImageSymbol_money3";
				inst154->addChild(inst155);
				inst155->__timeline->clear();
				inst155->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst156 = new CocoClip();
			inst156->__instanceName = "sack1";
			inst138->addChild(inst156);
			inst156->__timeline->clear();
			inst156->__timeline->addKeyFrameEx(NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -78,  -241.5, 1, 1, 0, 0, 0, 1);
			inst156->__timeline->addKeyFrameEx(NULL, 47, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -163,  -90, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst157 = new CocoClip(ImageSymbol_sack, NULL, NULL);
				inst157->__instanceName = ":: ImageSymbol_sack";
				inst156->addChild(inst157);
				inst157->__timeline->clear();
				inst157->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst158 = new CocoClip();
			inst158->__instanceName = "sack2";
			inst138->addChild(inst158);
			inst158->__timeline->clear();
			inst158->__timeline->addKeyFrameEx(NULL, 44, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -25,  -263.51, 1, 1, 0, 0, 0, 1);
			inst158->__timeline->addKeyFrameEx(NULL, 52, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -65,  -65, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst159 = new CocoClip(ImageSymbol_sack, NULL, NULL);
				inst159->__instanceName = ":: ImageSymbol_sack";
				inst158->addChild(inst159);
				inst159->__timeline->clear();
				inst159->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst160 = new CocoClip();
			inst160->__instanceName = "sack4";
			inst138->addChild(inst160);
			inst160->__timeline->clear();
			inst160->__timeline->addKeyFrameEx(NULL, 52, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 90,  -242.51, 1, 1, 0, 0, 0, 1);
			inst160->__timeline->addKeyFrameEx(NULL, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 144,  -85, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst161 = new CocoClip(ImageSymbol_sack, NULL, NULL);
				inst161->__instanceName = ":: ImageSymbol_sack";
				inst160->addChild(inst161);
				inst161->__timeline->clear();
				inst161->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst162 = new CocoClip();
			inst162->__instanceName = "sack3";
			inst138->addChild(inst162);
			inst162->__timeline->clear();
			inst162->__timeline->addKeyFrameEx(NULL, 48, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -262.51, 1, 1, 0, 0, 0, 1);
			inst162->__timeline->addKeyFrameEx(NULL, 56, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 39,  -64, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst163 = new CocoClip(ImageSymbol_sack, NULL, NULL);
				inst163->__instanceName = ":: ImageSymbol_sack";
				inst162->addChild(inst163);
				inst163->__timeline->clear();
				inst163->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst164 = new CocoClip();
			inst164->__instanceName = "youwin1";
			inst138->addChild(inst164);
			inst164->__timeline->clear();
			inst164->__timeline->addKeyFrameEx(NULL, 83, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 85, 0.6, 0.6, 0, 0, 0, 0);
			inst164->__timeline->addKeyFrameEx(NULL, 90, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 85, 1.1, 1.1, 0, 0, 0, 1);
			inst164->__timeline->addKeyFrameEx(NULL, 93, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 85, 1, 1, 0, 0, 0, 1);
			{
				CocoClip* inst165 = new CocoClip(ImageSymbol_youwin, NULL, NULL);
				inst165->__instanceName = ":: ImageSymbol_youwin";
				inst164->addChild(inst165);
				inst165->__timeline->clear();
				inst165->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			}
			CocoClip* inst166 = new CocoClip();
			inst166->__instanceName = "Actions";
			inst138->addChild(inst166);
			inst166->__timeline->clear();
			inst166->__timeline->addKeyFrameEx(waitForAction, 110, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst167 = new CocoClip();
		inst167->__instanceName = "BetText1";
		__root->addChild(inst167);
		inst167->__timeline->clear();
		inst167->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 40.99997, 130.5, 0.8, 0.8, 0, 0, 0, 1);
		{
			CocoClip* inst168 = new CocoClip(ImageSymbol_BetText, NULL, NULL);
			inst168->__instanceName = ":: ImageSymbol_BetText";
			inst167->addChild(inst168);
			inst168->__timeline->clear();
			inst168->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst169 = new CocoClip();
		inst169->__instanceName = "rectangleText1";
		__root->addChild(inst169);
		inst169->__timeline->clear();
		inst169->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 112, 127.5, 1, 1, 0, 0, 0, 1);
		{
			CocoClip* inst170 = new CocoClip(ImageSymbol_rectangleText, NULL, NULL);
			inst170->__instanceName = ":: ImageSymbol_rectangleText";
			inst169->addChild(inst170);
			inst170->__timeline->clear();
			inst170->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst171 = new CocoClip();
		inst171->__instanceName = "arrowDown";
		__root->addChild(inst171);
		inst171->__timeline->clear();
		inst171->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 70, 117.5, 0.9, 0.8,  -90, 0, 0, 1);
		inst171->__timeline->addKeyFrameEx(changeBettingText, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 70, 117.5, 0.9, 0.8,  -90, 0, 0, 1);
		{
			CocoClip* inst172 = new CocoClip(ImageSymbol_arrow, NULL, NULL);
			inst172->__instanceName = ":: ImageSymbol_arrow";
			inst171->addChild(inst172);
			inst172->__timeline->clear();
			inst172->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst173 = new CocoClip();
		inst173->__instanceName = "arrowUp";
		__root->addChild(inst173);
		inst173->__timeline->clear();
		inst173->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 136, 132.5, 0.9, 0.8, 90, 0, 0, 1);
		inst173->__timeline->addKeyFrameEx(changeBettingText, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 136, 132.5, 0.9, 0.8, 90, 0, 0, 1);
		{
			CocoClip* inst174 = new CocoClip(ImageSymbol_arrow, NULL, NULL);
			inst174->__instanceName = ":: ImageSymbol_arrow";
			inst173->addChild(inst174);
			inst174->__timeline->clear();
			inst174->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst175 = new CocoClip();
		inst175->__instanceName = "no1";
		__root->addChild(inst175);
		inst175->__timeline->clear();
		inst175->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 102, 121.72, 0.8, 0.8, 0, 0, 0, 0);
		{
			CocoClip* inst176 = new CocoClip(ImageSymbol_no1, NULL, NULL);
			inst176->__instanceName = ":: ImageSymbol_no1";
			inst175->addChild(inst176);
			inst176->__timeline->clear();
			inst176->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst177 = new CocoClip();
		inst177->__instanceName = "no2";
		__root->addChild(inst177);
		inst177->__timeline->clear();
		inst177->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 101, 123.72, 0.8, 0.8, 0, 0, 0, 0);
		{
			CocoClip* inst178 = new CocoClip(ImageSymbol_no2, NULL, NULL);
			inst178->__instanceName = ":: ImageSymbol_no2";
			inst177->addChild(inst178);
			inst178->__timeline->clear();
			inst178->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst179 = new CocoClip();
		inst179->__instanceName = "no3";
		__root->addChild(inst179);
		inst179->__timeline->clear();
		inst179->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 101, 124.72, 0.8, 0.8, 0, 0, 0, 0);
		{
			CocoClip* inst180 = new CocoClip(ImageSymbol_no3, NULL, NULL);
			inst180->__instanceName = ":: ImageSymbol_no3";
			inst179->addChild(inst180);
			inst180->__timeline->clear();
			inst180->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst181 = new CocoClip();
		inst181->__instanceName = "no4";
		__root->addChild(inst181);
		inst181->__timeline->clear();
		inst181->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 101, 120.72, 0.8, 0.8, 0, 0, 0, 1);
		{
			CocoClip* inst182 = new CocoClip(ImageSymbol_no4, NULL, NULL);
			inst182->__instanceName = ":: ImageSymbol_no4";
			inst181->addChild(inst182);
			inst182->__timeline->clear();
			inst182->__timeline->addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		}
		CocoClip* inst183 = new CocoClip();
		inst183->__instanceName = "Actions";
		__root->addChild(inst183);
		inst183->__timeline->clear();
		inst183->__timeline->addKeyFrameEx(btnBuyTicketClicked, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		inst183->__timeline->addKeyFrameEx(btnOpenAllClicked, 26, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		inst183->__timeline->addKeyFrameEx(NULL, 27, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		inst183->__timeline->addKeyFrameEx(waitForAction, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		inst183->__timeline->addKeyFrameEx(playBustedAnim, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
		inst183->__timeline->addKeyFrameEx(waitForAction, 75, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::btnBuyTicketClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
	stop();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::btnOpenAllClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::btnPlayAgainClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::changeSequence(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::waitForAction(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
	stop();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::playBustedAnim(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void SceneGameBoard::changeBettingText(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame)
{
}
