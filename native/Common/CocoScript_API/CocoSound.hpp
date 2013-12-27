#ifndef __COCOSOUND_HPP__
#define __COCOSOUND_HPP__

#include "Coconut2D.hpp"

class CocoSound
{
public:
	std::string symbolName;
	CocoSound();
	void createFromFile(std::string filename, Function* onloadCallBack);
};

#endif
