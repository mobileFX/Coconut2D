#include "SceneGameBoard.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
SceneGameBoard::SceneGameBoard()
{
	__sceneName = "SceneGameBoard";
	__fps = 30;
	__view_width = 480;
	__view_height = 320;
	__view_pixel_ratio = 1;
	CocoImage* Image_backround = newResourceImage("backround", "./assets/images/");
	{
		Image_backround->viewOptimalWidth = 572;
		Image_backround->viewOptimalHeight = 429;
		Image_backround->addSibling(new CocoImageSibling("backround_ldpi.png", 0.75, 429, 322));
		Image_backround->addSibling(new CocoImageSibling("backround_mdpi.png", 1, 572, 429));
		Image_backround->addSibling(new CocoImageSibling("backround_tvdpi.png", 1.25, 715, 536));
		Image_backround->addSibling(new CocoImageSibling("backround_hdpi.png", 1.5, 858, 644));
		Image_backround->addSibling(new CocoImageSibling("backround_xhdpi.png", 2, 1144, 858));
		Image_backround->textureCellWidth = 572;
		Image_backround->textureCellHeight = 429;
		Image_backround->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_AVATAR_BAR = newResourceImage("AVATAR_BAR", "./assets/images/");
	{
		Image_AVATAR_BAR->viewOptimalWidth = 222;
		Image_AVATAR_BAR->viewOptimalHeight = 41;
		Image_AVATAR_BAR->addSibling(new CocoImageSibling("AVATAR_BAR_ldpi.png", 0.75, 166, 31));
		Image_AVATAR_BAR->addSibling(new CocoImageSibling("AVATAR_BAR_mdpi.png", 1, 222, 41));
		Image_AVATAR_BAR->addSibling(new CocoImageSibling("AVATAR_BAR_tvdpi.png", 1.25, 278, 51));
		Image_AVATAR_BAR->addSibling(new CocoImageSibling("AVATAR_BAR_hdpi.png", 1.5, 333, 62));
		Image_AVATAR_BAR->addSibling(new CocoImageSibling("AVATAR_BAR_xhdpi.png", 2, 444, 82));
		Image_AVATAR_BAR->textureCellWidth = 222;
		Image_AVATAR_BAR->textureCellHeight = 41;
		Image_AVATAR_BAR->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_Balance = newResourceImage("Balance", "./assets/images/");
	{
		Image_Balance->viewOptimalWidth = 93;
		Image_Balance->viewOptimalHeight = 44;
		Image_Balance->addSibling(new CocoImageSibling("Balance_ldpi.png", 0.75, 69, 33));
		Image_Balance->addSibling(new CocoImageSibling("Balance_mdpi.png", 1, 92, 44));
		Image_Balance->addSibling(new CocoImageSibling("Balance_tvdpi.png", 1.25, 115, 55));
		Image_Balance->addSibling(new CocoImageSibling("Balance_hdpi.png", 1.5, 138, 66));
		Image_Balance->addSibling(new CocoImageSibling("Balance_xhdpi.png", 2, 184, 88));
		Image_Balance->textureCellWidth = 92;
		Image_Balance->textureCellHeight = 44;
		Image_Balance->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_winnings = newResourceImage("winnings", "./assets/images/");
	{
		Image_winnings->viewOptimalWidth = 93;
		Image_winnings->viewOptimalHeight = 44;
		Image_winnings->addSibling(new CocoImageSibling("winnings_ldpi.png", 0.75, 69, 33));
		Image_winnings->addSibling(new CocoImageSibling("winnings_mdpi.png", 1, 92, 44));
		Image_winnings->addSibling(new CocoImageSibling("winnings_tvdpi.png", 1.25, 115, 55));
		Image_winnings->addSibling(new CocoImageSibling("winnings_hdpi.png", 1.5, 138, 66));
		Image_winnings->addSibling(new CocoImageSibling("winnings_xhdpi.png", 2, 184, 88));
		Image_winnings->textureCellWidth = 92;
		Image_winnings->textureCellHeight = 44;
		Image_winnings->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_XerxesOnly = newResourceImage("XerxesOnly", "./assets/images/");
	{
		Image_XerxesOnly->viewOptimalWidth = 50;
		Image_XerxesOnly->viewOptimalHeight = 51;
		Image_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_ldpi.png", 0.75, 38, 38));
		Image_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_mdpi.png", 1, 50, 51));
		Image_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_tvdpi.png", 1.25, 62, 64));
		Image_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_hdpi.png", 1.5, 75, 76));
		Image_XerxesOnly->addSibling(new CocoImageSibling("XerxesOnly_xhdpi.png", 2, 100, 102));
		Image_XerxesOnly->textureCellWidth = 50;
		Image_XerxesOnly->textureCellHeight = 51;
		Image_XerxesOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_LeoEye = newResourceImage("LeoEye", "./assets/images/");
	{
		Image_LeoEye->viewOptimalWidth = 2;
		Image_LeoEye->viewOptimalHeight = 3;
		Image_LeoEye->addSibling(new CocoImageSibling("LeoEye_ldpi.png", 0.75, 2, 2));
		Image_LeoEye->addSibling(new CocoImageSibling("LeoEye_mdpi.png", 1, 2, 3));
		Image_LeoEye->addSibling(new CocoImageSibling("LeoEye_tvdpi.png", 1.25, 2, 4));
		Image_LeoEye->addSibling(new CocoImageSibling("LeoEye_hdpi.png", 1.5, 3, 4));
		Image_LeoEye->addSibling(new CocoImageSibling("LeoEye_xhdpi.png", 2, 4, 6));
		Image_LeoEye->textureCellWidth = 2;
		Image_LeoEye->textureCellHeight = 3;
		Image_LeoEye->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_SpartanOnly = newResourceImage("SpartanOnly", "./assets/images/");
	{
		Image_SpartanOnly->viewOptimalWidth = 48;
		Image_SpartanOnly->viewOptimalHeight = 49;
		Image_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_ldpi.png", 0.75, 36, 37));
		Image_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_mdpi.png", 1, 48, 49));
		Image_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_tvdpi.png", 1.25, 60, 61));
		Image_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_hdpi.png", 1.5, 72, 74));
		Image_SpartanOnly->addSibling(new CocoImageSibling("SpartanOnly_xhdpi.png", 2, 96, 98));
		Image_SpartanOnly->textureCellWidth = 48;
		Image_SpartanOnly->textureCellHeight = 49;
		Image_SpartanOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_PersianOnly = newResourceImage("PersianOnly", "./assets/images/");
	{
		Image_PersianOnly->viewOptimalWidth = 48;
		Image_PersianOnly->viewOptimalHeight = 49;
		Image_PersianOnly->addSibling(new CocoImageSibling("PersianOnly_ldpi.png", 0.75, 36, 37));
		Image_PersianOnly->addSibling(new CocoImageSibling("PersianOnly_mdpi.png", 1, 48, 49));
		Image_PersianOnly->addSibling(new CocoImageSibling("PersianOnly_tvdpi.png", 1.25, 60, 61));
		Image_PersianOnly->addSibling(new CocoImageSibling("PersianOnly_hdpi.png", 1.5, 72, 74));
		Image_PersianOnly->addSibling(new CocoImageSibling("PersianOnly_xhdpi.png", 2, 96, 98));
		Image_PersianOnly->textureCellWidth = 48;
		Image_PersianOnly->textureCellHeight = 49;
		Image_PersianOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_SwordLeft = newResourceImage("SwordLeft", "./assets/images/");
	{
		Image_SwordLeft->viewOptimalWidth = 49;
		Image_SwordLeft->viewOptimalHeight = 49;
		Image_SwordLeft->addSibling(new CocoImageSibling("SwordLeft_ldpi.png", 0.75, 37, 37));
		Image_SwordLeft->addSibling(new CocoImageSibling("SwordLeft_mdpi.png", 1, 49, 49));
		Image_SwordLeft->addSibling(new CocoImageSibling("SwordLeft_tvdpi.png", 1.25, 61, 61));
		Image_SwordLeft->addSibling(new CocoImageSibling("SwordLeft_hdpi.png", 1.5, 74, 74));
		Image_SwordLeft->addSibling(new CocoImageSibling("SwordLeft_xhdpi.png", 2, 98, 98));
		Image_SwordLeft->textureCellWidth = 49;
		Image_SwordLeft->textureCellHeight = 49;
		Image_SwordLeft->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_SwordRight = newResourceImage("SwordRight", "./assets/images/");
	{
		Image_SwordRight->viewOptimalWidth = 49;
		Image_SwordRight->viewOptimalHeight = 49;
		Image_SwordRight->addSibling(new CocoImageSibling("SwordRight_ldpi.png", 0.75, 37, 37));
		Image_SwordRight->addSibling(new CocoImageSibling("SwordRight_mdpi.png", 1, 49, 49));
		Image_SwordRight->addSibling(new CocoImageSibling("SwordRight_tvdpi.png", 1.25, 61, 61));
		Image_SwordRight->addSibling(new CocoImageSibling("SwordRight_hdpi.png", 1.5, 74, 74));
		Image_SwordRight->addSibling(new CocoImageSibling("SwordRight_xhdpi.png", 2, 98, 98));
		Image_SwordRight->textureCellWidth = 49;
		Image_SwordRight->textureCellHeight = 49;
		Image_SwordRight->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_grWhiteStar = newResourceImage("grWhiteStar", "./assets/images/");
	{
		Image_grWhiteStar->viewOptimalWidth = 24;
		Image_grWhiteStar->viewOptimalHeight = 24;
		Image_grWhiteStar->addSibling(new CocoImageSibling("grWhiteStar_ldpi.png", 0.75, 18, 18));
		Image_grWhiteStar->addSibling(new CocoImageSibling("grWhiteStar_mdpi.png", 1, 24, 24));
		Image_grWhiteStar->addSibling(new CocoImageSibling("grWhiteStar_tvdpi.png", 1.25, 30, 30));
		Image_grWhiteStar->addSibling(new CocoImageSibling("grWhiteStar_hdpi.png", 1.5, 36, 36));
		Image_grWhiteStar->addSibling(new CocoImageSibling("grWhiteStar_xhdpi.png", 2, 48, 48));
		Image_grWhiteStar->textureCellWidth = 24;
		Image_grWhiteStar->textureCellHeight = 24;
		Image_grWhiteStar->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_openunpressed = newResourceImage("openunpressed", "./assets/images/");
	{
		Image_openunpressed->viewOptimalWidth = 69;
		Image_openunpressed->viewOptimalHeight = 69;
		Image_openunpressed->addSibling(new CocoImageSibling("openunpressed_ldpi.png", 0.75, 52, 52));
		Image_openunpressed->addSibling(new CocoImageSibling("openunpressed_mdpi.png", 1, 69, 69));
		Image_openunpressed->addSibling(new CocoImageSibling("openunpressed_tvdpi.png", 1.25, 86, 86));
		Image_openunpressed->addSibling(new CocoImageSibling("openunpressed_hdpi.png", 1.5, 104, 104));
		Image_openunpressed->addSibling(new CocoImageSibling("openunpressed_xhdpi.png", 2, 138, 138));
		Image_openunpressed->textureCellWidth = 69;
		Image_openunpressed->textureCellHeight = 69;
		Image_openunpressed->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_LEONIDAS_body = newResourceImage("LEONIDAS_body", "./assets/images/");
	{
		Image_LEONIDAS_body->viewOptimalWidth = 294;
		Image_LEONIDAS_body->viewOptimalHeight = 330;
		Image_LEONIDAS_body->addSibling(new CocoImageSibling("LEONIDAS_body_ldpi.png", 0.75, 220, 248));
		Image_LEONIDAS_body->addSibling(new CocoImageSibling("LEONIDAS_body_mdpi.png", 1, 294, 330));
		Image_LEONIDAS_body->addSibling(new CocoImageSibling("LEONIDAS_body_tvdpi.png", 1.25, 368, 412));
		Image_LEONIDAS_body->addSibling(new CocoImageSibling("LEONIDAS_body_hdpi.png", 1.5, 441, 495));
		Image_LEONIDAS_body->addSibling(new CocoImageSibling("LEONIDAS_body_xhdpi.png", 2, 588, 659));
		Image_LEONIDAS_body->textureCellWidth = 294;
		Image_LEONIDAS_body->textureCellHeight = 330;
		Image_LEONIDAS_body->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_LEONIDAS_hand = newResourceImage("LEONIDAS_hand", "./assets/images/");
	{
		Image_LEONIDAS_hand->viewOptimalWidth = 43;
		Image_LEONIDAS_hand->viewOptimalHeight = 105;
		Image_LEONIDAS_hand->addSibling(new CocoImageSibling("LEONIDAS_hand_ldpi.png", 0.75, 32, 79));
		Image_LEONIDAS_hand->addSibling(new CocoImageSibling("LEONIDAS_hand_mdpi.png", 1, 43, 105));
		Image_LEONIDAS_hand->addSibling(new CocoImageSibling("LEONIDAS_hand_tvdpi.png", 1.25, 54, 131));
		Image_LEONIDAS_hand->addSibling(new CocoImageSibling("LEONIDAS_hand_hdpi.png", 1.5, 64, 158));
		Image_LEONIDAS_hand->addSibling(new CocoImageSibling("LEONIDAS_hand_xhdpi.png", 2, 86, 210));
		Image_LEONIDAS_hand->textureCellWidth = 43;
		Image_LEONIDAS_hand->textureCellHeight = 105;
		Image_LEONIDAS_hand->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_XERXES_Body = newResourceImage("XERXES_Body", "./assets/images/");
	{
		Image_XERXES_Body->viewOptimalWidth = 68;
		Image_XERXES_Body->viewOptimalHeight = 102;
		Image_XERXES_Body->addSibling(new CocoImageSibling("XERXES_Body_ldpi.png", 0.75, 51, 76));
		Image_XERXES_Body->addSibling(new CocoImageSibling("XERXES_Body_mdpi.png", 1, 68, 102));
		Image_XERXES_Body->addSibling(new CocoImageSibling("XERXES_Body_tvdpi.png", 1.25, 85, 128));
		Image_XERXES_Body->addSibling(new CocoImageSibling("XERXES_Body_hdpi.png", 1.5, 102, 153));
		Image_XERXES_Body->addSibling(new CocoImageSibling("XERXES_Body_xhdpi.png", 2, 136, 204));
		Image_XERXES_Body->textureCellWidth = 68;
		Image_XERXES_Body->textureCellHeight = 102;
		Image_XERXES_Body->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_Xerxes_Sleeve = newResourceImage("Xerxes_Sleeve", "./assets/images/");
	{
		Image_Xerxes_Sleeve->viewOptimalWidth = 12;
		Image_Xerxes_Sleeve->viewOptimalHeight = 11;
		Image_Xerxes_Sleeve->addSibling(new CocoImageSibling("Xerxes_Sleeve_ldpi.png", 0.75, 9, 8));
		Image_Xerxes_Sleeve->addSibling(new CocoImageSibling("Xerxes_Sleeve_mdpi.png", 1, 12, 11));
		Image_Xerxes_Sleeve->addSibling(new CocoImageSibling("Xerxes_Sleeve_tvdpi.png", 1.25, 15, 14));
		Image_Xerxes_Sleeve->addSibling(new CocoImageSibling("Xerxes_Sleeve_hdpi.png", 1.5, 18, 16));
		Image_Xerxes_Sleeve->addSibling(new CocoImageSibling("Xerxes_Sleeve_xhdpi.png", 2, 24, 22));
		Image_Xerxes_Sleeve->textureCellWidth = 12;
		Image_Xerxes_Sleeve->textureCellHeight = 11;
		Image_Xerxes_Sleeve->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_XERXES_hand = newResourceImage("XERXES_hand", "./assets/images/");
	{
		Image_XERXES_hand->viewOptimalWidth = 28;
		Image_XERXES_hand->viewOptimalHeight = 25;
		Image_XERXES_hand->addSibling(new CocoImageSibling("XERXES_hand_ldpi.png", 0.75, 21, 19));
		Image_XERXES_hand->addSibling(new CocoImageSibling("XERXES_hand_mdpi.png", 1, 28, 25));
		Image_XERXES_hand->addSibling(new CocoImageSibling("XERXES_hand_tvdpi.png", 1.25, 35, 31));
		Image_XERXES_hand->addSibling(new CocoImageSibling("XERXES_hand_hdpi.png", 1.5, 42, 38));
		Image_XERXES_hand->addSibling(new CocoImageSibling("XERXES_hand_xhdpi.png", 2, 56, 50));
		Image_XERXES_hand->textureCellWidth = 28;
		Image_XERXES_hand->textureCellHeight = 25;
		Image_XERXES_hand->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_XerxesClipHead2 = newResourceImage("XerxesClipHead2", "./assets/images/");
	{
		Image_XerxesClipHead2->viewOptimalWidth = 21;
		Image_XerxesClipHead2->viewOptimalHeight = 31;
		Image_XerxesClipHead2->addSibling(new CocoImageSibling("XerxesClipHead2_ldpi.png", 0.75, 16, 24));
		Image_XerxesClipHead2->addSibling(new CocoImageSibling("XerxesClipHead2_mdpi.png", 1, 21, 32));
		Image_XerxesClipHead2->addSibling(new CocoImageSibling("XerxesClipHead2_tvdpi.png", 1.25, 26, 40));
		Image_XerxesClipHead2->addSibling(new CocoImageSibling("XerxesClipHead2_hdpi.png", 1.5, 32, 48));
		Image_XerxesClipHead2->addSibling(new CocoImageSibling("XerxesClipHead2_xhdpi.png", 2, 42, 64));
		Image_XerxesClipHead2->textureCellWidth = 21;
		Image_XerxesClipHead2->textureCellHeight = 32;
		Image_XerxesClipHead2->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 3, 0, 3, 1, 3, 2});
		Image_XerxesClipHead2->addSequence(new CocoSequence("Idle", {0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26}));
	}
	CocoImage* Image_grid_tile = newResourceImage("grid_tile", "./assets/images/");
	{
		Image_grid_tile->viewOptimalWidth = 53;
		Image_grid_tile->viewOptimalHeight = 53;
		Image_grid_tile->addSibling(new CocoImageSibling("grid_tile_ldpi.png", 0.75, 40, 40));
		Image_grid_tile->addSibling(new CocoImageSibling("grid_tile_mdpi.png", 1, 53, 53));
		Image_grid_tile->addSibling(new CocoImageSibling("grid_tile_tvdpi.png", 1.25, 66, 66));
		Image_grid_tile->addSibling(new CocoImageSibling("grid_tile_hdpi.png", 1.5, 80, 80));
		Image_grid_tile->addSibling(new CocoImageSibling("grid_tile_xhdpi.png", 2, 106, 106));
		Image_grid_tile->textureCellWidth = 53;
		Image_grid_tile->textureCellHeight = 53;
		Image_grid_tile->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_LeonidasClipHead = newResourceImage("LeonidasClipHead", "./assets/images/");
	{
		Image_LeonidasClipHead->viewOptimalWidth = 32;
		Image_LeonidasClipHead->viewOptimalHeight = 31;
		Image_LeonidasClipHead->addSibling(new CocoImageSibling("LeonidasClipHead_ldpi.png", 0.75, 24, 23));
		Image_LeonidasClipHead->addSibling(new CocoImageSibling("LeonidasClipHead_mdpi.png", 1, 32, 31));
		Image_LeonidasClipHead->addSibling(new CocoImageSibling("LeonidasClipHead_tvdpi.png", 1.25, 40, 39));
		Image_LeonidasClipHead->addSibling(new CocoImageSibling("LeonidasClipHead_hdpi.png", 1.5, 48, 46));
		Image_LeonidasClipHead->addSibling(new CocoImageSibling("LeonidasClipHead_xhdpi.png", 2, 64, 62));
		Image_LeonidasClipHead->textureCellWidth = 32;
		Image_LeonidasClipHead->textureCellHeight = 31;
		Image_LeonidasClipHead->textureGrid = new Float32Array({0, 0, 0, 1, 0, 2, 1, 0});
		Image_LeonidasClipHead->addSequence(new CocoSequence("Idle", {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}));
	}
	CocoImage* Image_ticket_price = newResourceImage("ticket_price", "./assets/images/");
	{
		Image_ticket_price->viewOptimalWidth = 86;
		Image_ticket_price->viewOptimalHeight = 14;
		Image_ticket_price->addSibling(new CocoImageSibling("ticket_price_ldpi.png", 0.75, 64, 10));
		Image_ticket_price->addSibling(new CocoImageSibling("ticket_price_mdpi.png", 1, 86, 14));
		Image_ticket_price->addSibling(new CocoImageSibling("ticket_price_tvdpi.png", 1.25, 108, 18));
		Image_ticket_price->addSibling(new CocoImageSibling("ticket_price_hdpi.png", 1.5, 129, 21));
		Image_ticket_price->addSibling(new CocoImageSibling("ticket_price_xhdpi.png", 2, 172, 28));
		Image_ticket_price->textureCellWidth = 86;
		Image_ticket_price->textureCellHeight = 14;
		Image_ticket_price->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_PriceTable = newResourceImage("PriceTable", "./assets/images/");
	{
		Image_PriceTable->viewOptimalWidth = 89;
		Image_PriceTable->viewOptimalHeight = 92;
		Image_PriceTable->addSibling(new CocoImageSibling("PriceTable_ldpi.png", 0.75, 67, 69));
		Image_PriceTable->addSibling(new CocoImageSibling("PriceTable_mdpi.png", 1, 89, 92));
		Image_PriceTable->addSibling(new CocoImageSibling("PriceTable_tvdpi.png", 1.25, 111, 115));
		Image_PriceTable->addSibling(new CocoImageSibling("PriceTable_hdpi.png", 1.5, 134, 138));
		Image_PriceTable->addSibling(new CocoImageSibling("PriceTable_xhdpi.png", 2, 178, 184));
		Image_PriceTable->textureCellWidth = 89;
		Image_PriceTable->textureCellHeight = 92;
		Image_PriceTable->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_StoneTile_Back = newResourceImage("StoneTile_Back", "./assets/images/");
	{
		Image_StoneTile_Back->viewOptimalWidth = 63;
		Image_StoneTile_Back->viewOptimalHeight = 63;
		Image_StoneTile_Back->addSibling(new CocoImageSibling("StoneTile_Back_ldpi.png", 0.75, 47, 47));
		Image_StoneTile_Back->addSibling(new CocoImageSibling("StoneTile_Back_mdpi.png", 1, 63, 63));
		Image_StoneTile_Back->addSibling(new CocoImageSibling("StoneTile_Back_tvdpi.png", 1.25, 79, 79));
		Image_StoneTile_Back->addSibling(new CocoImageSibling("StoneTile_Back_hdpi.png", 1.5, 94, 94));
		Image_StoneTile_Back->addSibling(new CocoImageSibling("StoneTile_Back_xhdpi.png", 2, 126, 126));
		Image_StoneTile_Back->textureCellWidth = 63;
		Image_StoneTile_Back->textureCellHeight = 63;
		Image_StoneTile_Back->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_txtChooseAvatar = newResourceImage("ImageSymbol_txtChooseAvatar", "./assets/images/");
	{
		Image_ImageSymbol_txtChooseAvatar->viewOptimalWidth = 178;
		Image_ImageSymbol_txtChooseAvatar->viewOptimalHeight = 18;
		Image_ImageSymbol_txtChooseAvatar->addSibling(new CocoImageSibling("txtChooseAvatar_mdpi.png", 1, 178, 18));
		Image_ImageSymbol_txtChooseAvatar->addSibling(new CocoImageSibling("txtChooseAvatar_xhdpi.png", 2, 356, 36));
		Image_ImageSymbol_txtChooseAvatar->textureCellWidth = 178;
		Image_ImageSymbol_txtChooseAvatar->textureCellHeight = 18;
		Image_ImageSymbol_txtChooseAvatar->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_WIN_Shield = newResourceImage("ImageSymbol_WIN_Shield", "./assets/images/");
	{
		Image_ImageSymbol_WIN_Shield->viewOptimalWidth = 357;
		Image_ImageSymbol_WIN_Shield->viewOptimalHeight = 321;
		Image_ImageSymbol_WIN_Shield->addSibling(new CocoImageSibling("WIN_Shield_mdpi.png", 1, 357, 321));
		Image_ImageSymbol_WIN_Shield->addSibling(new CocoImageSibling("WIN_Shield_xhdpi.png", 2, 714, 642));
		Image_ImageSymbol_WIN_Shield->textureCellWidth = 357;
		Image_ImageSymbol_WIN_Shield->textureCellHeight = 321;
		Image_ImageSymbol_WIN_Shield->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_WIN_Logo = newResourceImage("ImageSymbol_WIN_Logo", "./assets/images/");
	{
		Image_ImageSymbol_WIN_Logo->viewOptimalWidth = 334;
		Image_ImageSymbol_WIN_Logo->viewOptimalHeight = 300;
		Image_ImageSymbol_WIN_Logo->addSibling(new CocoImageSibling("WIN_Logo_mdpi.png", 1, 334, 300));
		Image_ImageSymbol_WIN_Logo->addSibling(new CocoImageSibling("WIN_Logo_xhdpi.png", 2, 668, 600));
		Image_ImageSymbol_WIN_Logo->textureCellWidth = 334;
		Image_ImageSymbol_WIN_Logo->textureCellHeight = 300;
		Image_ImageSymbol_WIN_Logo->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_cloud2 = newResourceImage("ImageSymbol_cloud2", "./assets/images/");
	{
		Image_ImageSymbol_cloud2->viewOptimalWidth = 190;
		Image_ImageSymbol_cloud2->viewOptimalHeight = 58;
		Image_ImageSymbol_cloud2->addSibling(new CocoImageSibling("cloud2_mdpi.png", 1, 190, 58));
		Image_ImageSymbol_cloud2->addSibling(new CocoImageSibling("cloud2_xhdpi.png", 2, 380, 116));
		Image_ImageSymbol_cloud2->textureCellWidth = 190;
		Image_ImageSymbol_cloud2->textureCellHeight = 58;
		Image_ImageSymbol_cloud2->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_cloud1 = newResourceImage("ImageSymbol_cloud1", "./assets/images/");
	{
		Image_ImageSymbol_cloud1->viewOptimalWidth = 454;
		Image_ImageSymbol_cloud1->viewOptimalHeight = 157;
		Image_ImageSymbol_cloud1->addSibling(new CocoImageSibling("cloud1_mdpi.png", 1, 454, 157));
		Image_ImageSymbol_cloud1->addSibling(new CocoImageSibling("cloud1_xhdpi.png", 2, 908, 314));
		Image_ImageSymbol_cloud1->textureCellWidth = 454;
		Image_ImageSymbol_cloud1->textureCellHeight = 157;
		Image_ImageSymbol_cloud1->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ImageSymbol_cloud5 = newResourceImage("ImageSymbol_cloud5", "./assets/images/");
	{
		Image_ImageSymbol_cloud5->viewOptimalWidth = 102;
		Image_ImageSymbol_cloud5->viewOptimalHeight = 25;
		Image_ImageSymbol_cloud5->addSibling(new CocoImageSibling("cloud5_mdpi.png", 1, 102, 25));
		Image_ImageSymbol_cloud5->addSibling(new CocoImageSibling("cloud5_xhdpi.png", 2, 204, 50));
		Image_ImageSymbol_cloud5->textureCellWidth = 102;
		Image_ImageSymbol_cloud5->textureCellHeight = 25;
		Image_ImageSymbol_cloud5->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_TileOnly = newResourceImage("TileOnly", "./assets/images/");
	{
		Image_TileOnly->viewOptimalWidth = 48;
		Image_TileOnly->viewOptimalHeight = 49;
		Image_TileOnly->addSibling(new CocoImageSibling("TileOnly_ldpi.png", 0.75, 36, 37));
		Image_TileOnly->addSibling(new CocoImageSibling("TileOnly_mdpi.png", 1, 48, 49));
		Image_TileOnly->addSibling(new CocoImageSibling("TileOnly_tvdpi.png", 1.25, 60, 61));
		Image_TileOnly->addSibling(new CocoImageSibling("TileOnly_hdpi.png", 1.5, 72, 74));
		Image_TileOnly->addSibling(new CocoImageSibling("TileOnly_xhdpi.png", 2, 96, 98));
		Image_TileOnly->textureCellWidth = 48;
		Image_TileOnly->textureCellHeight = 49;
		Image_TileOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_ArmorOnly = newResourceImage("ArmorOnly", "./assets/images/");
	{
		Image_ArmorOnly->viewOptimalWidth = 53;
		Image_ArmorOnly->viewOptimalHeight = 49;
		Image_ArmorOnly->addSibling(new CocoImageSibling("ArmorOnly_ldpi.png", 0.75, 40, 37));
		Image_ArmorOnly->addSibling(new CocoImageSibling("ArmorOnly_mdpi.png", 1, 53, 49));
		Image_ArmorOnly->addSibling(new CocoImageSibling("ArmorOnly_tvdpi.png", 1.25, 66, 61));
		Image_ArmorOnly->addSibling(new CocoImageSibling("ArmorOnly_hdpi.png", 1.5, 80, 74));
		Image_ArmorOnly->addSibling(new CocoImageSibling("ArmorOnly_xhdpi.png", 2, 106, 98));
		Image_ArmorOnly->textureCellWidth = 53;
		Image_ArmorOnly->textureCellHeight = 49;
		Image_ArmorOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_SwordsOnly = newResourceImage("SwordsOnly", "./assets/images/");
	{
		Image_SwordsOnly->viewOptimalWidth = 48;
		Image_SwordsOnly->viewOptimalHeight = 49;
		Image_SwordsOnly->addSibling(new CocoImageSibling("SwordsOnly_ldpi.png", 0.75, 36, 37));
		Image_SwordsOnly->addSibling(new CocoImageSibling("SwordsOnly_mdpi.png", 1, 48, 49));
		Image_SwordsOnly->addSibling(new CocoImageSibling("SwordsOnly_tvdpi.png", 1.25, 60, 61));
		Image_SwordsOnly->addSibling(new CocoImageSibling("SwordsOnly_hdpi.png", 1.5, 72, 74));
		Image_SwordsOnly->addSibling(new CocoImageSibling("SwordsOnly_xhdpi.png", 2, 96, 98));
		Image_SwordsOnly->textureCellWidth = 48;
		Image_SwordsOnly->textureCellHeight = 49;
		Image_SwordsOnly->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_LeoOnly2 = newResourceImage("LeoOnly2", "./assets/images/");
	{
		Image_LeoOnly2->viewOptimalWidth = 50;
		Image_LeoOnly2->viewOptimalHeight = 51;
		Image_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_ldpi.png", 0.75, 38, 38));
		Image_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_mdpi.png", 1, 50, 51));
		Image_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_tvdpi.png", 1.25, 62, 64));
		Image_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_hdpi.png", 1.5, 75, 76));
		Image_LeoOnly2->addSibling(new CocoImageSibling("LeoOnly2_xhdpi.png", 2, 100, 102));
		Image_LeoOnly2->textureCellWidth = 50;
		Image_LeoOnly2->textureCellHeight = 51;
		Image_LeoOnly2->textureGrid = new Float32Array({0, 0});
	}
	CocoImage* Image_buyunpressed = newResourceImage("buyunpressed", "./assets/images/");
	{
		Image_buyunpressed->viewOptimalWidth = 125;
		Image_buyunpressed->viewOptimalHeight = 125;
		Image_buyunpressed->addSibling(new CocoImageSibling("buyunpressed_mdpi.png", 1, 125, 125));
		Image_buyunpressed->addSibling(new CocoImageSibling("buyunpressed_xhdpi.png", 2, 250, 250));
		Image_buyunpressed->textureCellWidth = 125;
		Image_buyunpressed->textureCellHeight = 125;
		Image_buyunpressed->textureGrid = new Float32Array({0, 0});
	}
	__root = new CocoClip();
	__root->__instanceName = "root";
	__root->__timeline->clear();
	__root->__timeline->addLabelEx(48, "IntroAnimationDone");
	__root->__timeline->addLabelEx(49, "JumpingAvatars");
	__root->__timeline->addLabelEx(71, "WaitToChooseAvatar");
	__root->__timeline->addLabelEx(72, "WaitToBuyTicket");
	__root->__timeline->addLabelEx(73, "WaitToScratch");
	__root->__timeline->addLabelEx(74, "WinAnim");
	__root->__timeline->addLabelEx(75, "EnterDemoMode");
	__root->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
	{
		CocoClip* inst1 = new CocoClip(NULL, "");
		inst1->__instanceName = "Background";
		__root->addChild(inst1);
		inst1->__timeline->clear();
		inst1->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, new CocoAudio("./assets/sounds/Background.ogg", true, 0));
		{
			CocoClip* inst2 = new CocoClip(Image_backround, "");
			inst2->__instanceName = ":: backround";
			inst1->addChild(inst2);
			inst2->__timeline->clear();
			inst2->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst3 = new CocoClip(NULL, "");
		inst3->__instanceName = "ChooseAvatar";
		__root->addChild(inst3);
		inst3->__timeline->clear();
		inst3->__timeline->addKeyFrameEx(NULL, NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 87, 1, 1, 0, 0, 0, 1, NULL);
		inst3->__timeline->addKeyFrameEx(NULL, NULL, 72, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 87, 1, 1, 0, 0, 0, 0, NULL);
		{
			CocoClip* inst4 = new CocoClip(NULL, "");
			inst4->__instanceName = "AVATAR_BAR1";
			inst3->addChild(inst4);
			inst4->__timeline->clear();
			inst4->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.901623, 0.868781, 0, 0, 0, 1, NULL);
			inst4->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.001803, 1.002439, 0, 0, 0, 1, NULL);
			inst4->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.901623, 0.868781, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst5 = new CocoClip(Image_AVATAR_BAR, "");
				inst5->__instanceName = ":: AVATAR_BAR";
				inst4->addChild(inst5);
				inst5->__timeline->clear();
				inst5->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst6 = new CocoClip(NULL, "");
			inst6->__instanceName = "text";
			inst3->addChild(inst6);
			inst6->__timeline->clear();
			inst6->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.883147, 0.866666, 0, 0, 0, 1, NULL);
			inst6->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.000899, 0.982222, 0, 0, 0, 1, NULL);
			inst6->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.883147, 0.866666, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst7 = new CocoClip(Image_ImageSymbol_txtChooseAvatar, "");
				inst7->__instanceName = ":: ImageSymbol_txtChooseAvatar";
				inst6->addChild(inst7);
				inst7->__timeline->clear();
				inst7->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
		}
		CocoClip* inst8 = new CocoClip(NULL, "");
		inst8->__instanceName = "Avatar_Armor";
		__root->addChild(inst8);
		inst8->__timeline->clear();
		inst8->__timeline->addLabelEx(0, "Init");
		inst8->__timeline->addLabelEx(10, "Enable");
		inst8->__timeline->addLabelEx(20, "Disable");
		inst8->__timeline->addLabelEx(30, "Select");
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 107.5, 242, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 34, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 107.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 58, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 64, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 107.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst8->__timeline->addKeyFrameEx(NULL, NULL, 70, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst9 = new CocoClip(NULL, "");
			inst9->__instanceName = "TileOnly1";
			inst8->addChild(inst9);
			inst9->__timeline->clear();
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst9->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst10 = new CocoClip(Image_TileOnly, "");
				inst10->__instanceName = ":: TileOnly";
				inst9->addChild(inst10);
				inst10->__timeline->clear();
				inst10->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst11 = new CocoClip(NULL, "");
			inst11->__instanceName = "inst1_ArmorOnly";
			inst8->addChild(inst11);
			inst11->__timeline->clear();
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst11->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.66, 0.6, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst12 = new CocoClip(NULL, "");
				inst12->__instanceName = "ArmorOnly1";
				inst11->addChild(inst12);
				inst12->__timeline->clear();
				inst12->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 6.037735, 6.530612, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst13 = new CocoClip(Image_ArmorOnly, "");
					inst13->__instanceName = ":: ArmorOnly";
					inst12->addChild(inst13);
					inst13->__timeline->clear();
					inst13->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 6.666667, 1, 1, 0, 0, 0, 1, NULL);
					inst13->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst14 = new CocoClip(NULL, "");
				inst14->__instanceName = "inst1_grWhiteStar";
				inst11->addChild(inst14);
				inst14->__timeline->clear();
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 1.686667, 1.686667, 135, 0, 0, 1, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 2.22, 2.22, 180, 0, 0, 1, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 66, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.969333, 0.969333, 135, 0, 0, 1, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 1.478, 1.478, 180, 0, 0, 1, NULL);
				inst14->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 65.1,  -85.25, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst15 = new CocoClip(Image_grWhiteStar, "");
					inst15->__instanceName = ":: grWhiteStar";
					inst14->addChild(inst15);
					inst15->__timeline->clear();
					inst15->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst16 = new CocoClip(NULL, "");
				inst16->__instanceName = "inst2_grWhiteStar";
				inst11->addChild(inst16);
				inst16->__timeline->clear();
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 1.047333, 1.047333, 135, 0, 0, 1, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 1.316667, 1.316667, 180, 0, 0, 1, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 66, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 1.922, 1.922, 135, 0, 0, 1, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 2.548, 2.548, 180, 0, 0, 1, NULL);
				inst16->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -56, 53.5, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst17 = new CocoClip(Image_grWhiteStar, "");
					inst17->__instanceName = ":: grWhiteStar";
					inst16->addChild(inst17);
					inst17->__timeline->clear();
					inst17->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
			}
			CocoClip* inst18 = new CocoClip(NULL, "");
			inst18->__instanceName = "Actions";
			inst8->addChild(inst18);
			inst18->__timeline->clear();
			inst18->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst18->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst18->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst18->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst19 = new CocoClip(NULL, "");
		inst19->__instanceName = "Avatar_Swords";
		__root->addChild(inst19);
		inst19->__timeline->clear();
		inst19->__timeline->addLabelEx(0, "Init");
		inst19->__timeline->addLabelEx(10, "Enable");
		inst19->__timeline->addLabelEx(20, "Disable");
		inst19->__timeline->addLabelEx(30, "Select");
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 64.5, 242, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 38, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 64.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 43, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 56, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 62, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 64.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst19->__timeline->addKeyFrameEx(NULL, NULL, 68, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst20 = new CocoClip(NULL, "");
			inst20->__instanceName = "TileOnly1";
			inst19->addChild(inst20);
			inst20->__timeline->clear();
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst20->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst21 = new CocoClip(Image_TileOnly, "");
				inst21->__instanceName = ":: TileOnly";
				inst20->addChild(inst21);
				inst21->__timeline->clear();
				inst21->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst22 = new CocoClip(NULL, "");
			inst22->__instanceName = "inst1_SwordsOnly";
			inst19->addChild(inst22);
			inst22->__timeline->clear();
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.333333, 0.5, 0.5, 0, 0, 0, 1, NULL);
			inst22->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.333333, 0.6, 0.6, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst23 = new CocoClip(NULL, "");
				inst23->__instanceName = "SwordsOnly1";
				inst22->addChild(inst23);
				inst23->__timeline->clear();
				inst23->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 6.666667, 6.530612, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst24 = new CocoClip(Image_SwordsOnly, "");
					inst24->__instanceName = ":: SwordsOnly";
					inst23->addChild(inst24);
					inst24->__timeline->clear();
					inst24->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
					inst24->__timeline->addKeyFrameEx(NULL, NULL, 32, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
					inst24->__timeline->addKeyFrameEx(NULL, NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
					inst24->__timeline->addKeyFrameEx(NULL, NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, false, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst25 = new CocoClip(NULL, "");
				inst25->__instanceName = "inst1_SwordRight";
				inst22->addChild(inst25);
				inst25->__timeline->clear();
				inst25->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 6.530612, 6.530612, 0, 0, 0, 1, NULL);
				inst25->__timeline->addKeyFrameEx(NULL, NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 153.1818, 14.54553, 6.530612, 6.530612,  -725, 0, 0, 1, NULL);
				inst25->__timeline->addKeyFrameEx(NULL, NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.454544, 0, 6.530612, 6.530612, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst26 = new CocoClip(Image_SwordRight, "");
					inst26->__instanceName = ":: SwordRight";
					inst25->addChild(inst26);
					inst26->__timeline->clear();
					inst26->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst27 = new CocoClip(NULL, "");
				inst27->__instanceName = "inst1_SwordLeft";
				inst22->addChild(inst27);
				inst27->__timeline->clear();
				inst27->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, false, 0, 0, 6.530612, 6.530612, 0, 0, 0, 1, NULL);
				inst27->__timeline->addKeyFrameEx(NULL, NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -209.5454, 0, 6.530612, 6.530612, 724, 0, 0, 1, NULL);
				inst27->__timeline->addKeyFrameEx(NULL, NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.454544,  -1.363678, 6.530612, 6.530612, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst28 = new CocoClip(Image_SwordLeft, "");
					inst28->__instanceName = ":: SwordLeft";
					inst27->addChild(inst28);
					inst28->__timeline->clear();
					inst28->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
			}
			CocoClip* inst29 = new CocoClip(NULL, "");
			inst29->__instanceName = "Actions";
			inst19->addChild(inst29);
			inst29->__timeline->clear();
			inst29->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst29->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst29->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst29->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst30 = new CocoClip(NULL, "");
		inst30->__instanceName = "Avatar_Persian";
		__root->addChild(inst30);
		inst30->__timeline->clear();
		inst30->__timeline->addLabelEx(0, "Init");
		inst30->__timeline->addLabelEx(10, "Enable");
		inst30->__timeline->addLabelEx(20, "Disable");
		inst30->__timeline->addLabelEx(30, "Select");
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 21.5, 243.1364, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 42, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 21.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 47, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 61, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 21.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst30->__timeline->addKeyFrameEx(NULL, NULL, 67, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst31 = new CocoClip(NULL, "");
			inst31->__instanceName = "TileOnly1";
			inst30->addChild(inst31);
			inst31->__timeline->clear();
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst31->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst32 = new CocoClip(Image_TileOnly, "");
				inst32->__instanceName = ":: TileOnly";
				inst31->addChild(inst32);
				inst32->__timeline->clear();
				inst32->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst33 = new CocoClip(NULL, "");
			inst33->__instanceName = "inst1_PersianOnly";
			inst30->addChild(inst33);
			inst33->__timeline->clear();
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst33->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -0.454529,  -0.454559, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst34 = new CocoClip(Image_PersianOnly, "");
				inst34->__instanceName = ":: PersianOnly";
				inst33->addChild(inst34);
				inst34->__timeline->clear();
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 6, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183, 6.5, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.167, 1.167,  -7.7, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 44, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183, 6.5, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 63, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst34->__timeline->addKeyFrameEx(NULL, NULL, 84, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst35 = new CocoClip(NULL, "");
			inst35->__instanceName = "Actions";
			inst30->addChild(inst35);
			inst35->__timeline->clear();
			inst35->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst35->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst35->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst35->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst36 = new CocoClip(NULL, "");
		inst36->__instanceName = "Avatar_Spartan";
		__root->addChild(inst36);
		inst36->__timeline->clear();
		inst36->__timeline->addLabelEx(10, "Enable");
		inst36->__timeline->addLabelEx(0, "Init");
		inst36->__timeline->addLabelEx(20, "Disable");
		inst36->__timeline->addLabelEx(30, "Select");
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 33, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -21.5, 243.1364, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 42, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -21.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 47, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 53, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 59, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -21.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst36->__timeline->addKeyFrameEx(NULL, NULL, 65, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -21.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst37 = new CocoClip(NULL, "");
			inst37->__instanceName = "TileOnly1";
			inst36->addChild(inst37);
			inst37->__timeline->clear();
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst37->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst38 = new CocoClip(Image_TileOnly, "");
				inst38->__instanceName = ":: TileOnly";
				inst37->addChild(inst38);
				inst38->__timeline->clear();
				inst38->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst39 = new CocoClip(NULL, "");
			inst39->__instanceName = "inst1_SpartanOnly";
			inst36->addChild(inst39);
			inst39->__timeline->clear();
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0.454529,  -0.454559, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst39->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0.454529,  -0.454559, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst40 = new CocoClip(Image_SpartanOnly, "");
				inst40->__instanceName = ":: SpartanOnly";
				inst39->addChild(inst40);
				inst40->__timeline->clear();
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183,  -15, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183, 0, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.166, 1.166, 15, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst40->__timeline->addKeyFrameEx(NULL, NULL, 82, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst41 = new CocoClip(NULL, "");
			inst41->__instanceName = "Actions";
			inst36->addChild(inst41);
			inst41->__timeline->clear();
			inst41->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst41->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst41->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst41->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst42 = new CocoClip(NULL, "");
		inst42->__instanceName = "Avatar_Xerxes";
		__root->addChild(inst42);
		inst42->__timeline->clear();
		inst42->__timeline->addLabelEx(0, "Init");
		inst42->__timeline->addLabelEx(10, "Enable");
		inst42->__timeline->addLabelEx(20, "Disable");
		inst42->__timeline->addLabelEx(30, "Select");
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -64.5, 243.96, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 38, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -64.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 43, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 56, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -64.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst42->__timeline->addKeyFrameEx(NULL, NULL, 62, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -64.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst43 = new CocoClip(NULL, "");
			inst43->__instanceName = "TileOnly1";
			inst42->addChild(inst43);
			inst43->__timeline->clear();
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst43->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst44 = new CocoClip(Image_TileOnly, "");
				inst44->__instanceName = ":: TileOnly";
				inst43->addChild(inst44);
				inst44->__timeline->clear();
				inst44->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst45 = new CocoClip(NULL, "");
			inst45->__instanceName = "inst1_XerxesOnly";
			inst42->addChild(inst45);
			inst45->__timeline->clear();
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.328, 3.262745, 0, 0, 0, 1, NULL);
			inst45->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.968, 3.890196, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst46 = new CocoClip(Image_XerxesOnly, "");
				inst46->__instanceName = ":: XerxesOnly";
				inst45->addChild(inst46);
				inst46->__timeline->clear();
				inst46->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst47 = new CocoClip(NULL, "");
			inst47->__instanceName = "Actions";
			inst42->addChild(inst47);
			inst47->__timeline->clear();
			inst47->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst47->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst47->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst47->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst48 = new CocoClip(NULL, "");
		inst48->__instanceName = "Avatar_Leonidas";
		__root->addChild(inst48);
		inst48->__timeline->clear();
		inst48->__timeline->addLabelEx(0, "Init");
		inst48->__timeline->addLabelEx(10, "Enable");
		inst48->__timeline->addLabelEx(20, "Disable");
		inst48->__timeline->addLabelEx(30, "Select");
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -107.5, 243.96, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 34, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -107.5, 110, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 49, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 54, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -107.5, 105, 0.251923, 0.256225, 0, 0, 0, 1, new CocoAudio("./assets/sounds/AvatarJump.ogg", true, 1));
		inst48->__timeline->addKeyFrameEx(NULL, NULL, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -107.5, 125, 0.251923, 0.256225, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst49 = new CocoClip(NULL, "");
			inst49->__instanceName = "TileOnly1";
			inst48->addChild(inst49);
			inst49->__timeline->clear();
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 3.333333, 3.265306, 0, 0, 0, 1, NULL);
			inst49->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 4, 3.918367, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst50 = new CocoClip(Image_TileOnly, "");
				inst50->__instanceName = ":: TileOnly";
				inst49->addChild(inst50);
				inst50->__timeline->clear();
				inst50->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 3.33333, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst51 = new CocoClip(NULL, "");
			inst51->__instanceName = "inst1_LeoOnly2";
			inst48->addChild(inst51);
			inst51->__timeline->clear();
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.52, 0.52, 0, 0, 0, 1, NULL);
			inst51->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.62, 0.62, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst52 = new CocoClip(NULL, "");
				inst52->__instanceName = "LeoOnly21";
				inst51->addChild(inst52);
				inst52->__timeline->clear();
				inst52->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 6.4, 6.27451, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst53 = new CocoClip(Image_LeoOnly2, "");
					inst53->__instanceName = ":: LeoOnly2";
					inst52->addChild(inst53);
					inst53->__timeline->clear();
					inst53->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst54 = new CocoClip(NULL, "");
				inst54->__instanceName = "inst1_LeoEye";
				inst51->addChild(inst54);
				inst54->__timeline->clear();
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -63.75,  -80.65, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 8, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -63.75,  -80.65, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 16, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -60.25,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -60.25,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -61.05,  -82.55, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -61.9,  -81.75, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -62.75,  -80.9, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 72, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -62.75,  -80.9, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -61.9,  -81.75, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 82, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -61.05,  -82.55, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -60.25,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 91, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -60.25,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 99, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -63.75,  -80.65, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst54->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -63.75,  -80.65, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst55 = new CocoClip(Image_LeoEye, "");
					inst55->__instanceName = ":: LeoEye";
					inst54->addChild(inst55);
					inst55->__timeline->clear();
					inst55->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst56 = new CocoClip(NULL, "");
				inst56->__instanceName = "inst2_LeoEye";
				inst51->addChild(inst56);
				inst56->__timeline->clear();
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -34.5,  -78.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 8, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -34.5,  -78.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 16, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -27,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -27,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26.9,  -82.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26.85,  -81.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -26.75,  -80.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 72, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26.75,  -80.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26.85,  -81.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 82, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26.9,  -82.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -27,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 91, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -27,  -83.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 99, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -34.5,  -78.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				inst56->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -34.5,  -78.4, 7.500019, 5.333333, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst57 = new CocoClip(Image_LeoEye, "");
					inst57->__instanceName = ":: LeoEye";
					inst56->addChild(inst57);
					inst57->__timeline->clear();
					inst57->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst58 = new CocoClip(NULL, "");
				inst58->__instanceName = "inst1_grWhiteStar";
				inst51->addChild(inst58);
				inst58->__timeline->clear();
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 1.047333, 1.047333, 135, 0, 0, 1, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 1.316667, 1.316667, 180, 0, 0, 1, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 65, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.969333, 0.969333, 135, 0, 0, 1, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 95, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 1.418, 1.418, 180, 0, 0, 1, NULL);
				inst58->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -4.1,  -33.35, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst59 = new CocoClip(Image_grWhiteStar, "");
					inst59->__instanceName = ":: grWhiteStar";
					inst58->addChild(inst59);
					inst59->__timeline->clear();
					inst59->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
			}
			CocoClip* inst60 = new CocoClip(NULL, "");
			inst60->__instanceName = "Actions";
			inst48->addChild(inst60);
			inst60->__timeline->clear();
			inst60->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst60->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst60->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst60->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst61 = new CocoClip(NULL, "");
		inst61->__instanceName = "Clouds";
		__root->addChild(inst61);
		inst61->__timeline->clear();
		inst61->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst62 = new CocoClip(NULL, "");
			inst62->__instanceName = "cloud21";
			inst61->addChild(inst62);
			inst62->__timeline->clear();
			inst62->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -388.5,  -110, 1, 1, 0, 0, 0, 1, NULL);
			inst62->__timeline->addKeyFrameEx(NULL, NULL, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 388.5,  -149, 1, 1, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst63 = new CocoClip(Image_ImageSymbol_cloud2, "");
				inst63->__instanceName = ":: ImageSymbol_cloud2";
				inst62->addChild(inst63);
				inst63->__timeline->clear();
				inst63->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst64 = new CocoClip(NULL, "");
			inst64->__instanceName = "cloud51";
			inst61->addChild(inst64);
			inst64->__timeline->clear();
			inst64->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -470.5,  -136, 1, 1, 0, 0, 0, 1, NULL);
			inst64->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 344.5,  -194, 1, 1, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst65 = new CocoClip(Image_ImageSymbol_cloud5, "");
				inst65->__instanceName = ":: ImageSymbol_cloud5";
				inst64->addChild(inst65);
				inst65->__timeline->clear();
				inst65->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst66 = new CocoClip(NULL, "");
			inst66->__instanceName = "cloud11";
			inst61->addChild(inst66);
			inst66->__timeline->clear();
			inst66->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -211.5,  -104.96, 1.001101, 1, 0, 0, 0, 0, NULL);
			{
				CocoClip* inst67 = new CocoClip(Image_ImageSymbol_cloud1, "");
				inst67->__instanceName = ":: ImageSymbol_cloud1";
				inst66->addChild(inst67);
				inst67->__timeline->clear();
				inst67->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
		}
		CocoClip* inst68 = new CocoClip(NULL, "");
		inst68->__instanceName = "Leonidas";
		__root->addChild(inst68);
		inst68->__timeline->clear();
		inst68->__timeline->addLabelEx(1, "Animate");
		inst68->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -77,  -28.5, 0.7, 0.7, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst69 = new CocoClip(NULL, "");
			inst69->__instanceName = "inst1_LEONIDAS_hand";
			inst68->addChild(inst69);
			inst69->__timeline->clear();
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -114.5,  -51.5, 1.437208, 1.434288, 0, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 22, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -50.5, 1.437208, 1.434288, 0, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 27, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -70.6, 1.437208, 1.434288,  -21.5, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 31, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -50.5, 1.437208, 1.434288, 0, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -70.6, 1.437208, 1.434288,  -21.5, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -114.5,  -50.5, 1.437208, 1.434288, 0, 0, 0, 1, NULL);
			inst69->__timeline->addKeyFrameEx(NULL, NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -114.5,  -51.5, 1.437208, 1.434288, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst70 = new CocoClip(Image_LEONIDAS_hand, "");
				inst70->__instanceName = ":: LEONIDAS_hand";
				inst69->addChild(inst70);
				inst70->__timeline->clear();
				inst70->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst71 = new CocoClip(NULL, "");
			inst71->__instanceName = "inst1_LEONIDAS_body";
			inst68->addChild(inst71);
			inst71->__timeline->clear();
			inst71->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -162.6429,  -19.21429, 1.428571, 1.263636, 0, 52.85714,  -30.71429, 1, NULL);
			inst71->__timeline->addKeyFrameEx(NULL, NULL, 22, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -162.6429,  -19.21429, 1.428571, 1.263636, 0, 52.85714,  -30.71429, 1, NULL);
			inst71->__timeline->addKeyFrameEx(NULL, NULL, 27, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -162.6429,  -29.21429, 1.428571, 1.427909, 0, 52.85714,  -30.71429, 1, NULL);
			inst71->__timeline->addKeyFrameEx(NULL, NULL, 31, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -162.6429,  -19.21429, 1.428571, 1.263636, 0, 52.85714,  -30.71429, 1, NULL);
			inst71->__timeline->addKeyFrameEx(NULL, NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -162.6429,  -19.21429, 1.428571, 1.263636, 0, 52.85714,  -30.71429, 1, NULL);
			{
				CocoClip* inst72 = new CocoClip(Image_LEONIDAS_body, "");
				inst72->__instanceName = ":: LEONIDAS_body";
				inst71->addChild(inst72);
				inst72->__timeline->clear();
				inst72->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 50.5,  -31.39999, 0.3, 0.3, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst73 = new CocoClip(NULL, "");
			inst73->__instanceName = "inst1_LeonidasClipHead";
			inst68->addChild(inst73);
			inst73->__timeline->clear();
			inst73->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -142.25,  -76.75, 1.434377, 1.412902, 0, 0, 0, 1, NULL);
			inst73->__timeline->addKeyFrameEx(NULL, NULL, 22, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -142.25,  -76.75, 1.434377, 1.412902, 0, 0, 0, 1, NULL);
			inst73->__timeline->addKeyFrameEx(NULL, NULL, 27, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -142.25,  -92.75, 1.434377, 1.412902, 0, 0, 0, 1, NULL);
			inst73->__timeline->addKeyFrameEx(NULL, NULL, 31, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -142.25,  -76.75, 1.434377, 1.412902, 0, 0, 0, 1, NULL);
			inst73->__timeline->addKeyFrameEx(NULL, NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -142.25,  -76.75, 1.434377, 1.412902, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst74 = new CocoClip(Image_LeonidasClipHead, "");
				inst74->__instanceName = ":: LeonidasClipHead";
				inst73->addChild(inst74);
				inst74->__timeline->clear();
				inst74->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst75 = new CocoClip(NULL, "");
			inst75->__instanceName = "Actions";
			inst68->addChild(inst75);
			inst75->__timeline->clear();
			inst75->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst76 = new CocoClip(NULL, "");
		inst76->__instanceName = "Xerxes";
		__root->addChild(inst76);
		inst76->__timeline->clear();
		inst76->__timeline->addLabelEx(1, "Animate");
		inst76->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 70.5,  -51, 0.7, 0.7, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst77 = new CocoClip(NULL, "");
			inst77->__instanceName = "inst1_Xerxes_Sleeve";
			inst76->addChild(inst77);
			inst77->__timeline->clear();
			inst77->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 170.1,  -29.1, 1.458334, 1.454545, 0, 0, 0, 1, NULL);
			inst77->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 170.1,  -35.1, 1.458334, 1.454545, 0, 0, 0, 1, NULL);
			inst77->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 170.1,  -29.1, 1.458334, 1.454545, 0, 0, 0, 1, NULL);
			inst77->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 170.1,  -29.1, 1.458334, 1.454545, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst78 = new CocoClip(Image_Xerxes_Sleeve, "");
				inst78->__instanceName = ":: Xerxes_Sleeve";
				inst77->addChild(inst78);
				inst78->__timeline->clear();
				inst78->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst79 = new CocoClip(NULL, "");
			inst79->__instanceName = "inst1_XERXES_hand";
			inst76->addChild(inst79);
			inst79->__timeline->clear();
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 163.25,  -23, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 164.25,  -28, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 163.25,  -23, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 37, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 161.25,  -30, 1.428571, 1.399999, 35.7, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 44, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 163.25,  -23, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 51, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 161.25,  -30, 1.428571, 1.399999, 35.7, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 59, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 163.25,  -23, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			inst79->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 163.25,  -23, 1.428571, 1.399999, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst80 = new CocoClip(Image_XERXES_hand, "");
				inst80->__instanceName = ":: XERXES_hand";
				inst79->addChild(inst80);
				inst80->__timeline->clear();
				inst80->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst81 = new CocoClip(NULL, "");
			inst81->__instanceName = "inst1_XERXES_Body";
			inst76->addChild(inst81);
			inst81->__timeline->clear();
			inst81->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 190.5, 2.5, 1.426472, 1.343136, 0, 0, 0, 1, NULL);
			inst81->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 190.5,  -1.5, 1.426472, 1.423725, 0, 0, 0, 1, NULL);
			inst81->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 190.5, 2.5, 1.426472, 1.343136, 0, 0, 0, 1, NULL);
			inst81->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 190.5, 2.5, 1.426472, 1.343136, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst82 = new CocoClip(Image_XERXES_Body, "");
				inst82->__instanceName = ":: XERXES_Body";
				inst81->addChild(inst82);
				inst82->__timeline->clear();
				inst82->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst83 = new CocoClip(NULL, "");
			inst83->__instanceName = "inst1_XerxesClipHead2";
			inst76->addChild(inst83);
			inst83->__timeline->clear();
			inst83->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 184.8,  -55.8, 1.452382, 1.406248, 0, 0, 0, 1, NULL);
			inst83->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 184.8,  -62.8, 1.452382, 1.406248, 0, 0, 0, 1, NULL);
			inst83->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 184.8,  -55.8, 1.452382, 1.406248, 0, 0, 0, 1, NULL);
			inst83->__timeline->addKeyFrameEx(NULL, NULL, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 184.8,  -55.8, 1.452382, 1.406248, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst84 = new CocoClip(Image_XerxesClipHead2, "");
				inst84->__instanceName = ":: XerxesClipHead2";
				inst83->addChild(inst84);
				inst84->__timeline->clear();
				inst84->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst85 = new CocoClip(NULL, "");
			inst85->__instanceName = "Actions";
			inst76->addChild(inst85);
			inst85->__timeline->clear();
			inst85->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst86 = new CocoClip(NULL, "");
		inst86->__instanceName = "PrizeTable";
		__root->addChild(inst86);
		inst86->__timeline->clear();
		inst86->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -192, 40, 0.4, 0.4, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst87 = new CocoClip(NULL, "");
			inst87->__instanceName = "PriceTable1";
			inst86->addChild(inst87);
			inst87->__timeline->clear();
			inst87->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.173483, 0.173043, 0, 0, 0, 1, NULL);
			inst87->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.493819, 2.487498, 0, 0, 0, 1, NULL);
			inst87->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.734831, 1.730433, 0, 0, 0, 1, NULL);
			inst87->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.168539, 2.163041, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst88 = new CocoClip(Image_PriceTable, "");
				inst88->__instanceName = ":: PriceTable";
				inst87->addChild(inst88);
				inst88->__timeline->clear();
				inst88->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
		}
		CocoClip* inst89 = new CocoClip(NULL, "");
		inst89->__instanceName = "OpenAllButton";
		__root->addChild(inst89);
		inst89->__timeline->clear();
		inst89->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 191.78, 243.96, 0.996377, 0.996377, 0, 0, 0, 1, NULL);
		inst89->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 191.78, 125, 0.996377, 0.996377, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst90 = new CocoClip(Image_openunpressed, "");
			inst90->__instanceName = ":: openunpressed";
			inst89->addChild(inst90);
			inst90->__timeline->clear();
			inst90->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst91 = new CocoClip(NULL, "");
		inst91->__instanceName = "BuyTicketButton";
		__root->addChild(inst91);
		inst91->__timeline->clear();
		inst91->__timeline->addKeyFrameEx(NULL, NULL, 25, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -192, 243.96, 1, 1, 0, 0, 0, 1, NULL);
		inst91->__timeline->addKeyFrameEx(NULL, NULL, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -192, 125, 1, 1, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst92 = new CocoClip(NULL, "");
			inst92->__instanceName = "buyunpressed1";
			inst91->addChild(inst92);
			inst92->__timeline->clear();
			inst92->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst93 = new CocoClip(Image_buyunpressed, "");
				inst93->__instanceName = ":: buyunpressed";
				inst92->addChild(inst93);
				inst93->__timeline->clear();
				inst93->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.55, 0.55, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst94 = new CocoClip(NULL, "");
			inst94->__instanceName = "inst1_ticket_price";
			inst91->addChild(inst94);
			inst94->__timeline->clear();
			inst94->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -38.20996, 0.994186, 1, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst95 = new CocoClip(Image_ticket_price, "");
				inst95->__instanceName = ":: ticket_price";
				inst94->addChild(inst95);
				inst95->__timeline->clear();
				inst95->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
		}
		CocoClip* inst96 = new CocoClip(NULL, "");
		inst96->__instanceName = "Winnings";
		__root->addChild(inst96);
		inst96->__timeline->clear();
		inst96->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 193.5,  -243, 1.005435, 1, 0, 0, 0, 1, NULL);
		inst96->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 193.5,  -134, 1.005435, 1, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst97 = new CocoClip(Image_winnings, "");
			inst97->__instanceName = ":: winnings";
			inst96->addChild(inst97);
			inst97->__timeline->clear();
			inst97->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst98 = new CocoClip(NULL, "");
		inst98->__instanceName = "Balance";
		__root->addChild(inst98);
		inst98->__timeline->clear();
		inst98->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -190.5,  -243, 1.005435, 1, 0, 0, 0, 1, NULL);
		inst98->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -190.5,  -134, 1.005435, 1, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst99 = new CocoClip(Image_Balance, "");
			inst99->__instanceName = ":: Balance";
			inst98->addChild(inst99);
			inst99->__timeline->clear();
			inst99->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst100 = new CocoClip(NULL, "");
		inst100->__instanceName = "Grid";
		__root->addChild(inst100);
		inst100->__timeline->clear();
		inst100->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -10, 0.05, 0.05, 0, 0, 0, 1, NULL);
		inst100->__timeline->addKeyFrameEx(NULL, NULL, 47, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0,  -10, 0.4, 0.4,  -90, 0, 0, 1, NULL);
		{
			CocoClip* inst101 = new CocoClip(NULL, "");
			inst101->__instanceName = "AnimationClip_Cell1";
			inst100->addChild(inst101);
			inst101->__timeline->clear();
			inst101->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110, 210, 1, 1, 180, 0, 0, 1, NULL);
			inst101->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110, 210, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst102 = new CocoClip(NULL, "");
				inst102->__instanceName = "Back";
				inst101->addChild(inst102);
				inst102->__timeline->clear();
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst102->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst103 = new CocoClip(Image_StoneTile_Back, "");
					inst103->__instanceName = ":: StoneTile_Back";
					inst102->addChild(inst103);
					inst103->__timeline->clear();
					inst103->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst104 = new CocoClip(NULL, "");
				inst104->__instanceName = "Front";
				inst101->addChild(inst104);
				inst104->__timeline->clear();
				inst104->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst104->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst104->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst104->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst104->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst105 = new CocoClip(Image_grid_tile, "");
					inst105->__instanceName = ":: grid_tile";
					inst104->addChild(inst105);
					inst105->__timeline->clear();
					inst105->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst106 = new CocoClip(NULL, "");
				inst106->__instanceName = "Actions";
				inst101->addChild(inst106);
				inst106->__timeline->clear();
				inst106->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst107 = new CocoClip(NULL, "");
			inst107->__instanceName = "AnimationClip_Cell2";
			inst100->addChild(inst107);
			inst107->__timeline->clear();
			inst107->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180,  -68.33332, 1, 1, 180, 0, 0, 1, NULL);
			inst107->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180,  -68.33332, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst108 = new CocoClip(NULL, "");
				inst108->__instanceName = "Back";
				inst107->addChild(inst108);
				inst108->__timeline->clear();
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst108->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst109 = new CocoClip(Image_StoneTile_Back, "");
					inst109->__instanceName = ":: StoneTile_Back";
					inst108->addChild(inst109);
					inst109->__timeline->clear();
					inst109->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst110 = new CocoClip(NULL, "");
				inst110->__instanceName = "Front";
				inst107->addChild(inst110);
				inst110->__timeline->clear();
				inst110->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst110->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst110->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst110->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst110->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst111 = new CocoClip(Image_grid_tile, "");
					inst111->__instanceName = ":: grid_tile";
					inst110->addChild(inst111);
					inst111->__timeline->clear();
					inst111->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst112 = new CocoClip(NULL, "");
				inst112->__instanceName = "Actions";
				inst107->addChild(inst112);
				inst112->__timeline->clear();
				inst112->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst113 = new CocoClip(NULL, "");
			inst113->__instanceName = "AnimationClip_Cell3";
			inst100->addChild(inst113);
			inst113->__timeline->clear();
			inst113->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999,  -207.5, 1, 1, 180, 0, 0, 1, NULL);
			inst113->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999,  -207.5, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst114 = new CocoClip(NULL, "");
				inst114->__instanceName = "Back";
				inst113->addChild(inst114);
				inst114->__timeline->clear();
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst114->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst115 = new CocoClip(Image_StoneTile_Back, "");
					inst115->__instanceName = ":: StoneTile_Back";
					inst114->addChild(inst115);
					inst115->__timeline->clear();
					inst115->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst116 = new CocoClip(NULL, "");
				inst116->__instanceName = "Front";
				inst113->addChild(inst116);
				inst116->__timeline->clear();
				inst116->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst116->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst116->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst116->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst116->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst117 = new CocoClip(Image_grid_tile, "");
					inst117->__instanceName = ":: grid_tile";
					inst116->addChild(inst117);
					inst117->__timeline->clear();
					inst117->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst118 = new CocoClip(NULL, "");
				inst118->__instanceName = "Actions";
				inst113->addChild(inst118);
				inst118->__timeline->clear();
				inst118->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst119 = new CocoClip(NULL, "");
			inst119->__instanceName = "AnimationClip_Cell4";
			inst100->addChild(inst119);
			inst119->__timeline->clear();
			inst119->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180, 70.83334, 1, 1, 180, 0, 0, 1, NULL);
			inst119->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180, 70.83334, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst120 = new CocoClip(NULL, "");
				inst120->__instanceName = "Back";
				inst119->addChild(inst120);
				inst120->__timeline->clear();
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst120->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst121 = new CocoClip(Image_StoneTile_Back, "");
					inst121->__instanceName = ":: StoneTile_Back";
					inst120->addChild(inst121);
					inst121->__timeline->clear();
					inst121->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst122 = new CocoClip(NULL, "");
				inst122->__instanceName = "Front";
				inst119->addChild(inst122);
				inst122->__timeline->clear();
				inst122->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst122->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst122->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst122->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst122->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst123 = new CocoClip(Image_grid_tile, "");
					inst123->__instanceName = ":: grid_tile";
					inst122->addChild(inst123);
					inst123->__timeline->clear();
					inst123->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst124 = new CocoClip(NULL, "");
				inst124->__instanceName = "Actions";
				inst119->addChild(inst124);
				inst124->__timeline->clear();
				inst124->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst125 = new CocoClip(NULL, "");
			inst125->__instanceName = "AnimationClip_Cell5";
			inst100->addChild(inst125);
			inst125->__timeline->clear();
			inst125->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999,  -68.33332, 1, 1, 180, 0, 0, 1, NULL);
			inst125->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999,  -68.33332, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst126 = new CocoClip(NULL, "");
				inst126->__instanceName = "Back";
				inst125->addChild(inst126);
				inst126->__timeline->clear();
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst126->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst127 = new CocoClip(Image_StoneTile_Back, "");
					inst127->__instanceName = ":: StoneTile_Back";
					inst126->addChild(inst127);
					inst127->__timeline->clear();
					inst127->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst128 = new CocoClip(NULL, "");
				inst128->__instanceName = "Front";
				inst125->addChild(inst128);
				inst128->__timeline->clear();
				inst128->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst128->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst128->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst128->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst128->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst129 = new CocoClip(Image_grid_tile, "");
					inst129->__instanceName = ":: grid_tile";
					inst128->addChild(inst129);
					inst129->__timeline->clear();
					inst129->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst130 = new CocoClip(NULL, "");
				inst130->__instanceName = "Actions";
				inst125->addChild(inst130);
				inst130->__timeline->clear();
				inst130->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst131 = new CocoClip(NULL, "");
			inst131->__instanceName = "AnimationClip_Cell6";
			inst100->addChild(inst131);
			inst131->__timeline->clear();
			inst131->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110,  -207.5, 1, 1, 180, 0, 0, 1, NULL);
			inst131->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110,  -207.5, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst132 = new CocoClip(NULL, "");
				inst132->__instanceName = "Back";
				inst131->addChild(inst132);
				inst132->__timeline->clear();
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst132->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst133 = new CocoClip(Image_StoneTile_Back, "");
					inst133->__instanceName = ":: StoneTile_Back";
					inst132->addChild(inst133);
					inst133->__timeline->clear();
					inst133->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst134 = new CocoClip(NULL, "");
				inst134->__instanceName = "Front";
				inst131->addChild(inst134);
				inst134->__timeline->clear();
				inst134->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst134->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst134->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst134->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst134->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst135 = new CocoClip(Image_grid_tile, "");
					inst135->__instanceName = ":: grid_tile";
					inst134->addChild(inst135);
					inst135->__timeline->clear();
					inst135->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst136 = new CocoClip(NULL, "");
				inst136->__instanceName = "Actions";
				inst131->addChild(inst136);
				inst136->__timeline->clear();
				inst136->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst137 = new CocoClip(NULL, "");
			inst137->__instanceName = "AnimationClip_Cell7";
			inst100->addChild(inst137);
			inst137->__timeline->clear();
			inst137->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180, 210, 1, 1, 180, 0, 0, 1, NULL);
			inst137->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180, 210, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst138 = new CocoClip(NULL, "");
				inst138->__instanceName = "Back";
				inst137->addChild(inst138);
				inst138->__timeline->clear();
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst138->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst139 = new CocoClip(Image_StoneTile_Back, "");
					inst139->__instanceName = ":: StoneTile_Back";
					inst138->addChild(inst139);
					inst139->__timeline->clear();
					inst139->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst140 = new CocoClip(NULL, "");
				inst140->__instanceName = "Front";
				inst137->addChild(inst140);
				inst140->__timeline->clear();
				inst140->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst140->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst140->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst140->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst140->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst141 = new CocoClip(Image_grid_tile, "");
					inst141->__instanceName = ":: grid_tile";
					inst140->addChild(inst141);
					inst141->__timeline->clear();
					inst141->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst142 = new CocoClip(NULL, "");
				inst142->__instanceName = "Actions";
				inst137->addChild(inst142);
				inst142->__timeline->clear();
				inst142->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst143 = new CocoClip(NULL, "");
			inst143->__instanceName = "AnimationClip_Cell8";
			inst100->addChild(inst143);
			inst143->__timeline->clear();
			inst143->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999, 70.83334, 1, 1, 180, 0, 0, 1, NULL);
			inst143->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999, 70.83334, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst144 = new CocoClip(NULL, "");
				inst144->__instanceName = "Back";
				inst143->addChild(inst144);
				inst144->__timeline->clear();
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst144->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst145 = new CocoClip(Image_StoneTile_Back, "");
					inst145->__instanceName = ":: StoneTile_Back";
					inst144->addChild(inst145);
					inst145->__timeline->clear();
					inst145->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst146 = new CocoClip(NULL, "");
				inst146->__instanceName = "Front";
				inst143->addChild(inst146);
				inst146->__timeline->clear();
				inst146->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst146->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst146->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst146->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst146->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst147 = new CocoClip(Image_grid_tile, "");
					inst147->__instanceName = ":: grid_tile";
					inst146->addChild(inst147);
					inst147->__timeline->clear();
					inst147->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst148 = new CocoClip(NULL, "");
				inst148->__instanceName = "Actions";
				inst143->addChild(inst148);
				inst148->__timeline->clear();
				inst148->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst149 = new CocoClip(NULL, "");
			inst149->__instanceName = "AnimationClip_Cell9";
			inst100->addChild(inst149);
			inst149->__timeline->clear();
			inst149->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110,  -68.33332, 1, 1, 180, 0, 0, 1, NULL);
			inst149->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110,  -68.33332, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst150 = new CocoClip(NULL, "");
				inst150->__instanceName = "Back";
				inst149->addChild(inst150);
				inst150->__timeline->clear();
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst150->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst151 = new CocoClip(Image_StoneTile_Back, "");
					inst151->__instanceName = ":: StoneTile_Back";
					inst150->addChild(inst151);
					inst151->__timeline->clear();
					inst151->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst152 = new CocoClip(NULL, "");
				inst152->__instanceName = "Front";
				inst149->addChild(inst152);
				inst152->__timeline->clear();
				inst152->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst152->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst152->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst152->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst152->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst153 = new CocoClip(Image_grid_tile, "");
					inst153->__instanceName = ":: grid_tile";
					inst152->addChild(inst153);
					inst153->__timeline->clear();
					inst153->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst154 = new CocoClip(NULL, "");
				inst154->__instanceName = "Actions";
				inst149->addChild(inst154);
				inst154->__timeline->clear();
				inst154->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 1, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst155 = new CocoClip(NULL, "");
			inst155->__instanceName = "AnimationClip_Cell10";
			inst100->addChild(inst155);
			inst155->__timeline->clear();
			inst155->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999, 210, 1, 1, 180, 0, 0, 1, NULL);
			inst155->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 34.99999, 210, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst156 = new CocoClip(NULL, "");
				inst156->__instanceName = "Back";
				inst155->addChild(inst156);
				inst156->__timeline->clear();
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst156->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst157 = new CocoClip(Image_StoneTile_Back, "");
					inst157->__instanceName = ":: StoneTile_Back";
					inst156->addChild(inst157);
					inst157->__timeline->clear();
					inst157->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst158 = new CocoClip(NULL, "");
				inst158->__instanceName = "Front";
				inst155->addChild(inst158);
				inst158->__timeline->clear();
				inst158->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst158->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst158->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst158->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst159 = new CocoClip(Image_grid_tile, "");
					inst159->__instanceName = ":: grid_tile";
					inst158->addChild(inst159);
					inst159->__timeline->clear();
					inst159->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst160 = new CocoClip(NULL, "");
				inst160->__instanceName = "Actions";
				inst155->addChild(inst160);
				inst160->__timeline->clear();
				inst160->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst161 = new CocoClip(NULL, "");
			inst161->__instanceName = "AnimationClip_Cell11";
			inst100->addChild(inst161);
			inst161->__timeline->clear();
			inst161->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110, 70.83334, 1, 1, 180, 0, 0, 1, NULL);
			inst161->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -110, 70.83334, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst162 = new CocoClip(NULL, "");
				inst162->__instanceName = "Back";
				inst161->addChild(inst162);
				inst162->__timeline->clear();
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst162->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst163 = new CocoClip(Image_StoneTile_Back, "");
					inst163->__instanceName = ":: StoneTile_Back";
					inst162->addChild(inst163);
					inst163->__timeline->clear();
					inst163->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst164 = new CocoClip(NULL, "");
				inst164->__instanceName = "Front";
				inst161->addChild(inst164);
				inst164->__timeline->clear();
				inst164->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst164->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst164->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst164->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst165 = new CocoClip(Image_grid_tile, "");
					inst165->__instanceName = ":: grid_tile";
					inst164->addChild(inst165);
					inst165->__timeline->clear();
					inst165->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst166 = new CocoClip(NULL, "");
				inst166->__instanceName = "Actions";
				inst161->addChild(inst166);
				inst166->__timeline->clear();
				inst166->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst167 = new CocoClip(NULL, "");
			inst167->__instanceName = "AnimationClip_Cell12";
			inst100->addChild(inst167);
			inst167->__timeline->clear();
			inst167->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180,  -207.5, 1, 1, 180, 0, 0, 1, NULL);
			inst167->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 180,  -207.5, 1, 1, 90, 0, 0, 1, NULL);
			{
				CocoClip* inst168 = new CocoClip(NULL, "");
				inst168->__instanceName = "Back";
				inst167->addChild(inst168);
				inst168->__timeline->clear();
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 9, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.211111, 2.111112, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 23, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.491112, 2.491112, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.111112, 2.111112, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 45, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 1, NULL);
				inst168->__timeline->addKeyFrameEx(NULL, NULL, 46, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.900001, 1.900001, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst169 = new CocoClip(Image_StoneTile_Back, "");
					inst169->__instanceName = ":: StoneTile_Back";
					inst168->addChild(inst169);
					inst169->__timeline->clear();
					inst169->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst170 = new CocoClip(NULL, "");
				inst170->__instanceName = "Front";
				inst167->addChild(inst170);
				inst170->__timeline->clear();
				inst170->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst170->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 2.509435, 2.509435, 0, 0, 0, 1, NULL);
				inst170->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 1, NULL);
				inst170->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.250944, 2.509435, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst171 = new CocoClip(Image_grid_tile, "");
					inst171->__instanceName = ":: grid_tile";
					inst170->addChild(inst171);
					inst171->__timeline->clear();
					inst171->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst172 = new CocoClip(NULL, "");
				inst172->__instanceName = "Actions";
				inst167->addChild(inst172);
				inst172->__timeline->clear();
				inst172->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst172->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst173 = new CocoClip(NULL, "");
			inst173->__instanceName = "Actions";
			inst100->addChild(inst173);
			inst173->__timeline->clear();
			inst173->__timeline->addKeyFrameEx(NULL, (CocoAction)&CocoScene::stop, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst174 = new CocoClip(NULL, "");
		inst174->__instanceName = "YouWin";
		__root->addChild(inst174);
		inst174->__timeline->clear();
		inst174->__timeline->addKeyFrameEx(NULL, NULL, 74, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		{
			CocoClip* inst175 = new CocoClip(NULL, "");
			inst175->__instanceName = "WIN_Shield";
			inst174->addChild(inst175);
			inst175->__timeline->clear();
			inst175->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.009356, 0.009346, 0, 0, 0, 1, NULL);
			inst175->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.001065, 1, 0, 0, 0, 1, NULL);
			inst175->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.74846, 0.747663, 0, 0, 0, 1, NULL);
			inst175->__timeline->addKeyFrameEx(NULL, NULL, 16, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 0.935575, 0.934579, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst176 = new CocoClip(Image_ImageSymbol_WIN_Shield, "");
				inst176->__instanceName = ":: ImageSymbol_WIN_Shield";
				inst175->addChild(inst176);
				inst176->__timeline->clear();
				inst176->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			}
			CocoClip* inst177 = new CocoClip(NULL, "");
			inst177->__instanceName = "AnimationClip_YouWinLogo1";
			inst174->addChild(inst177);
			inst177->__timeline->clear();
			inst177->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst177->__timeline->addKeyFrameEx(NULL, NULL, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.8, 0.8, 0, 0, 0, 1, NULL);
			inst177->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			inst177->__timeline->addKeyFrameEx(NULL, NULL, 16, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
			{
				CocoClip* inst178 = new CocoClip(NULL, "");
				inst178->__instanceName = "WIN_Logo1";
				inst177->addChild(inst178);
				inst178->__timeline->clear();
				inst178->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				inst178->__timeline->addKeyFrameEx(NULL, NULL, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				{
					CocoClip* inst179 = new CocoClip(Image_ImageSymbol_WIN_Logo, "");
					inst179->__instanceName = ":: ImageSymbol_WIN_Logo";
					inst178->addChild(inst179);
					inst179->__timeline->clear();
					inst179->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst180 = new CocoClip(NULL, "");
				inst180->__instanceName = "grWhiteStar1";
				inst177->addChild(inst180);
				inst180->__timeline->clear();
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -120.5,  -93, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -120.5,  -93, 0.866667, 0.866667,  -110.5, 0, 0, 1, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -120.5,  -93, 0.466667, 0.466667, 0, 0, 0, 1, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 21, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -120.5,  -93, 0.466667, 0.466667, 0, 0, 0, 0, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 52, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 118,  -100, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 57, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 118,  -100, 0.866667, 0.866667,  -110.5, 0, 0, 1, NULL);
				inst180->__timeline->addKeyFrameEx(NULL, NULL, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 118,  -100, 0.533333, 0.533333,  -110.5, 0, 0, 0, NULL);
				{
					CocoClip* inst181 = new CocoClip(Image_grWhiteStar, "");
					inst181->__instanceName = ":: grWhiteStar";
					inst180->addChild(inst181);
					inst181->__timeline->clear();
					inst181->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst182 = new CocoClip(NULL, "");
				inst182->__instanceName = "grWhiteStar2";
				inst177->addChild(inst182);
				inst182->__timeline->clear();
				inst182->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -115, 32, 1, 1, 0, 0, 0, 0, NULL);
				inst182->__timeline->addKeyFrameEx(NULL, NULL, 11, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -115, 32, 0.666667, 0.666667,  -12.3, 0, 0, 1, NULL);
				inst182->__timeline->addKeyFrameEx(NULL, NULL, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -115, 32, 0.8, 0.8,  -110.5, 0, 0, 1, NULL);
				inst182->__timeline->addKeyFrameEx(NULL, NULL, 19, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -115, 32, 0.466667, 0.466667, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst183 = new CocoClip(Image_grWhiteStar, "");
					inst183->__instanceName = ":: grWhiteStar";
					inst182->addChild(inst183);
					inst183->__timeline->clear();
					inst183->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst184 = new CocoClip(NULL, "");
				inst184->__instanceName = "grWhiteStar3";
				inst177->addChild(inst184);
				inst184->__timeline->clear();
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 18, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -16,  -95, 0.533333, 0.533333, 0, 0, 0, 0, NULL);
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 21, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -16,  -95, 0.8, 0.8,  -110.5, 0, 0, 1, NULL);
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 31, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -16,  -95, 0.533333, 0.533333, 0, 0, 0, 0, NULL);
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 125,  -95, 0.666667, 0.666667, 0, 0, 0, 0, NULL);
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 44, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 125,  -98, 1, 1,  -110.5, 0, 0, 1, NULL);
				inst184->__timeline->addKeyFrameEx(NULL, NULL, 49, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 125,  -95, 0.666667, 0.666667,  -110.5, 0, 0, 0, NULL);
				{
					CocoClip* inst185 = new CocoClip(Image_grWhiteStar, "");
					inst185->__instanceName = ":: grWhiteStar";
					inst184->addChild(inst185);
					inst185->__timeline->clear();
					inst185->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
				CocoClip* inst186 = new CocoClip(NULL, "");
				inst186->__instanceName = "grWhiteStar4";
				inst177->addChild(inst186);
				inst186->__timeline->clear();
				inst186->__timeline->addKeyFrameEx(NULL, NULL, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 7, 28, 0.533333, 0.533333, 0, 0, 0, 0, NULL);
				inst186->__timeline->addKeyFrameEx(NULL, NULL, 35, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 7, 25, 0.666667, 0.666667,  -110.5, 0, 0, 1, NULL);
				inst186->__timeline->addKeyFrameEx(NULL, NULL, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 7, 25, 0.6, 0.6,  -92, 0, 0, 1, NULL);
				inst186->__timeline->addKeyFrameEx(NULL, NULL, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 7, 25, 0.466667, 0.466667, 0, 0, 0, 0, NULL);
				{
					CocoClip* inst187 = new CocoClip(Image_grWhiteStar, "");
					inst187->__instanceName = ":: grWhiteStar";
					inst186->addChild(inst187);
					inst187->__timeline->clear();
					inst187->__timeline->addKeyFrameEx(NULL, NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
				}
			}
			CocoClip* inst188 = new CocoClip(NULL, "");
			inst188->__instanceName = "Actions";
			inst174->addChild(inst188);
			inst188->__timeline->clear();
			inst188->__timeline->addKeyFrameEx(engine->STATE_GAME_BOARD, NULL, 16, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		}
		CocoClip* inst189 = new CocoClip(NULL, "");
		inst189->__instanceName = "Actions";
		__root->addChild(inst189);
		inst189->__timeline->clear();
		inst189->__timeline->addKeyFrameEx(engine->STATE_GAME_BOARD_CHOOSE_AVATAR, NULL, 71, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, true, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
		inst189->__timeline->addKeyFrameEx(NULL, NULL, 74, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE, false, false, 0, 0, 1, 1, 0, 0, 0, 1, NULL);
	}
}
