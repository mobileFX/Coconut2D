#ifndef __TOUCHLIST_HPP__
#define __TOUCHLIST_HPP__

#include "Coconut2D.hpp"
#include "Touch.hpp"

class TouchList : public Array<Touch*>
{
public:
	int length;
	TouchList();
	Touch* item(int index);
};

#endif
