#ifndef __SCENETITLE_HPP__
#define __SCENETITLE_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"

class SceneTitle : public CocoScene
{
public:
	SceneTitle();
	void waitForAction();
	void goPlayOnClick();
};

#endif
