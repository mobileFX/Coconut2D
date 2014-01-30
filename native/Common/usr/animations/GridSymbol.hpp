#ifndef __GRIDSYMBOL_HPP__
#define __GRIDSYMBOL_HPP__

#include "Coconut2D.hpp"
#include "CocoClip.hpp"
#include "CocoScene.hpp"

class GridSymbol
{
public:
	enum SYMBOL_ENUM {
		SYMBOL_LEONIDAS = 1,
		SYMBOL_XERXES = 2,
		SYMBOL_SPARTAN = 3,
		SYMBOL_PERSIAN = 4,
		SYMBOL_SWORDS = 5,
		SYMBOL_ARMOR = 6
	};
	CocoScene* scene;
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
