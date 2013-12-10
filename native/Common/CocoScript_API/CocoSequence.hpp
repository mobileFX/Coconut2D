#ifndef __COCOSEQUENCE_HPP__
#define __COCOSEQUENCE_HPP__

class CocoSequence
{
public:
	std::string name;
	Array<int> frames;
	CocoSequence(std::string name, Array<int> framesArray);
};

#endif
