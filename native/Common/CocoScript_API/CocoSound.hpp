#ifndef __COCOSOUND_HPP__
#define __COCOSOUND_HPP__

class CocoSound
{
public:
	std::string symbolName;
	CocoSound();
	void createFromFile(std::string filename, Function* onloadCallBack);
};

#endif