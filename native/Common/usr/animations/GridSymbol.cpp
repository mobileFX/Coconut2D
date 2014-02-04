#include "GridSymbol.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
GridSymbol::GridSymbol(CocoScene* scene)
{
	this->scene = scene;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GridSymbol::~GridSymbol()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int GridSymbol::getRandom()
{
	return (floor(((float)rand() / (float)RAND_MAX) * 6) + 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::createSymbol(int symbol)
{
	CocoClip* placeholder = initPlaceholder();
	switch(symbol)
	{
		case SYMBOL_LEONIDAS:
		{
			placeholder->addChild(initLeonidas());
			break;
		}
		break;
		case SYMBOL_XERXES:
		{
			placeholder->addChild(initXerxes());
			break;
		}
		break;
		case SYMBOL_SPARTAN:
		{
			placeholder->addChild(initSpartan());
			break;
		}
		break;
		case SYMBOL_PERSIAN:
		{
			placeholder->addChild(initPersian());
			break;
		}
		break;
		case SYMBOL_SWORDS:
		{
			placeholder->addChild(initSwords());
			break;
		}
		break;
		case SYMBOL_ARMOR:
		{
			placeholder->addChild(initArmor());
			break;
		}
		break;
	}
	return placeholder;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initPlaceholder()
{
	CocoClip* inst170 = new CocoClip(nullptr);
	inst170->__instanceName = String("Placeholder");
	inst170->__timeline->clear();
	inst170->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 0.35, 0.35, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	return inst170;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initLeonidas()
{
	CocoClip* inst45 = new CocoClip(nullptr);
	inst45->__instanceName = String("LeonidasAvatar");
	inst45->__timeline->clear();
	inst45->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 5, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String("idle"));
	{
		CocoClip* inst46 = new CocoClip(scene->getImageSymbol(String("SpriteSymbol_LeonidasAvatar")));
		inst46->__instanceName = String(":: avatarLeonidas");
		inst45->addChild(inst46);
		inst46->__timeline->clear();
		inst46->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	}
	return inst45;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initXerxes()
{
	CocoClip* inst39 = new CocoClip(nullptr);
	inst39->__instanceName = String("XerxesAvatar");
	inst39->__timeline->clear();
	inst39->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -5, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String("idle"));
	{
		CocoClip* inst40 = new CocoClip(scene->getImageSymbol(String("SpriteSymbol_XerxesAvatar")));
		inst40->__instanceName = String(":: avatarXerxes");
		inst39->addChild(inst40);
		inst40->__timeline->clear();
		inst40->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	}
	return inst39;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initSpartan()
{
	CocoClip* inst33 = new CocoClip(nullptr);
	inst33->__instanceName = String("SpartanAvatar");
	inst33->__timeline->clear();
	inst33->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst34 = new CocoClip(nullptr);
		inst34->__instanceName = String("avatarSpartan1");
		inst33->addChild(inst34);
		inst34->__timeline->clear();
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183,  -15, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1.183, 1.183, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 30, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 36, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.166, 1.166, 15, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 40, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst34->__timeline->addKeyFrameEx(nullptr, nullptr, 82, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst35 = new CocoClip(scene->getImageSymbol(String("ImageSymbol_avatarSpartan")));
			inst35->__instanceName = String(":: ImageSymbol_avatarSpartan");
			inst34->addChild(inst35);
			inst35->__timeline->clear();
			inst35->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
	}
	return inst33;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initPersian()
{
	CocoClip* inst28 = new CocoClip(nullptr);
	inst28->__instanceName = String("PersianAvatar");
	inst28->__timeline->clear();
	inst28->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst29 = new CocoClip(nullptr);
		inst29->__instanceName = String("avatarPersian1");
		inst28->addChild(inst29);
		inst29->__timeline->clear();
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 5, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183, 6.5, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 10, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 15, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.167, 1.167,  -7.7, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 44, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 50, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.183, 1.183, 6.5, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 55, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1.167, 1.167,  -7.7, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 60, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst29->__timeline->addKeyFrameEx(nullptr, nullptr, 84, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst30 = new CocoClip(scene->getImageSymbol(String("ImageSymbol_avatarPersian")));
			inst30->__instanceName = String(":: ImageSymbol_avatarPersian");
			inst29->addChild(inst30);
			inst30->__timeline->clear();
			inst30->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
	}
	return inst28;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initSwords()
{
	CocoClip* inst22 = new CocoClip(nullptr);
	inst22->__instanceName = String("SwordsAvatar");
	inst22->__timeline->clear();
	inst22->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String("idle"));
	{
		CocoClip* inst23 = new CocoClip(scene->getImageSymbol(String("SpriteSymbol_SwordsAvatar")));
		inst23->__instanceName = String(":: avatarSwords");
		inst22->addChild(inst23);
		inst23->__timeline->clear();
		inst23->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	}
	return inst22;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* GridSymbol::initArmor()
{
	CocoClip* inst11 = new CocoClip(nullptr);
	inst11->__instanceName = String("ArmorAvatar");
	inst11->__timeline->clear();
	inst11->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 0, 13, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
	{
		CocoClip* inst12 = new CocoClip(nullptr);
		inst12->__instanceName = String("avatarArmor1");
		inst11->addChild(inst12);
		inst12->__timeline->clear();
		inst12->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0,  -13, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		{
			CocoClip* inst13 = new CocoClip(scene->getImageSymbol(String("ImageSymbol_avatarArmor")));
			inst13->__instanceName = String(":: avatarArmor");
			inst12->addChild(inst13);
			inst13->__timeline->clear();
			inst13->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst14 = new CocoClip(nullptr);
		inst14->__instanceName = String("inst1_grWhiteStar");
		inst11->addChild(inst14);
		inst14->__timeline->clear();
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 1.686667, 1.686667, 135, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 2.22, 2.22, 180, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 66, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.969333, 0.969333, 135, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 1.478, 1.478, 180, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst14->__timeline->addKeyFrameEx(nullptr, nullptr, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 28,  -37, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		{
			CocoClip* inst15 = new CocoClip(scene->getImageSymbol(String("grWhiteStar")));
			inst15->__instanceName = String(":: grWhiteStar");
			inst14->addChild(inst15);
			inst15->__timeline->clear();
			inst15->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
		CocoClip* inst16 = new CocoClip(nullptr);
		inst16->__instanceName = String("inst2_grWhiteStar");
		inst11->addChild(inst16);
		inst16->__timeline->clear();
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 12, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 1.047333, 1.047333, 135, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 20, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 29, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 1.316667, 1.316667, 180, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 39, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 66, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 77, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 1.922, 1.922, 135, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 87, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 96, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 2.548, 2.548, 180, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		inst16->__timeline->addKeyFrameEx(nullptr, nullptr, 106, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true,  -26, 28, 0.666667, 0.666667, 0, 0, 0, 1, 1, 1, 1, 0, nullptr, false, false, String(""));
		{
			CocoClip* inst17 = new CocoClip(scene->getImageSymbol(String("grWhiteStar")));
			inst17->__instanceName = String(":: grWhiteStar");
			inst16->addChild(inst17);
			inst17->__timeline->clear();
			inst17->__timeline->addKeyFrameEx(nullptr, nullptr, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, nullptr, false, false, String(""));
		}
	}
	return inst11;
}
