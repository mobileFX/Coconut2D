#ifndef __COCOSOUND_HPP__
#define __COCOSOUND_HPP__

#include "Coconut2D.hpp"

class CocoSound
{
public:
	String symbolName;
	CocoSound();
	void createFromFile(String filename, Function* onloadCallBack);
};

#endif
