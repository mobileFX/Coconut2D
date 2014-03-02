#ifndef __TOUCH_HPP__
#define __TOUCH_HPP__

#include "Coconut2D.hpp"
#include "EventTarget.hpp"

class Touch
{
public:
	int identifier;
	int screenX;
	int screenY;
	int clientX;
	int clientY;
	int pageX;
	int pageY;
	EventTarget* target;
	Touch();
	~Touch();
	void initTouch(int identifier, EventTarget* target, int screenX, int screenY, int clientX, int clientY, int pageX, int pageY);
};

#endif
