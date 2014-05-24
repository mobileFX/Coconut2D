/* Generated by Coconut2D C++ Compiler from file ITickable.jspp */

#ifndef __ITICKABLE_HPP__
#define __ITICKABLE_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ITickable
{
public:
	virtual void RegisterTickable() = 0;
	virtual void UnregisterTickable() = 0;
	virtual void tick(float time) = 0;
};

#endif // __ITICKABLE_HPP__
