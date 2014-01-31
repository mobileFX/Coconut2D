#ifndef __GRIDSYMBOL_HPP__
#define __GRIDSYMBOL_HPP__

#include "Coconut2D.hpp"
#include "CocoClip.hpp"
#include "CocoScene.hpp"
#include "CocoTimeline.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoImage.hpp"

class GridSymbol
{
public:
	CocoScene* scene;
	const int SYMBOL_LEONIDAS = 1;
	const int SYMBOL_XERXES = 2;
	const int SYMBOL_SPARTAN = 3;
	const int SYMBOL_PERSIAN = 4;
	const int SYMBOL_SWORDS = 5;
	const int SYMBOL_ARMOR = 6;
	GridSymbol(CocoScene* scene);
	~GridSymbol();
	int getRandom();
	CocoClip* createSymbol(int symbol);
	CocoClip* initPlaceholder();
	CocoClip* initLeonidas();
	CocoClip* initXerxes();
	CocoClip* initSpartan();
	CocoClip* initPersian();
	CocoClip* initSwords();
	CocoClip* initArmor();
};

#endif
