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
	CocoVector();
	void set(float x, float y, float z, float w);
};

#endif
