//
//  HTMLEvent.hpp
//  CocoEngine
//
//  Created by Administrator on 12/6/13.
//
//

#ifndef __CocoEngine__HTMLEvent__
#define __CocoEngine__HTMLEvent__

#include <string>

class HTMLEvent
{
public:
	std::string type;
	bool bubbles;
	bool cancelable;
	int clientX;
	int clientY;
	int pageX;
	int pageY;
	int screenX;
	int screenY;
	bool defaultPrevented;
};

#endif /* defined(__CocoEngine__HTMLEvent__) */
