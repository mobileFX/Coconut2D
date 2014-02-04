#ifndef __COCOSEQUENCE_HPP__
#define __COCOSEQUENCE_HPP__

#include "Coconut2D.hpp"

class CocoSequence
{
public:
	String name;
	Array<int> frames;
	Time sequenceStartTime;
	CocoSequence(String name, Array<int> framesArray);
	~CocoSequence();
};

#endif
