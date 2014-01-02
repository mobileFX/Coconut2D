#ifndef __COCOVECTOR_HPP__
#define __COCOVECTOR_HPP__

#include "Coconut2D.hpp"

class CocoVector
{
public:
	float X;
	float Y;
	float Z;
	float W;
	virtual CocoVector();
	void reset(float x, float y, float z, float w);
};

#endif
