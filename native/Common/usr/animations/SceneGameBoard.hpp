#ifndef __SCENEGAMEBOARD_HPP__
#define __SCENEGAMEBOARD_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"

class SceneGameBoard : public CocoScene
{
public:
	virtual SceneGameBoard();
	void waitForAction();
	void hint();
};

#endif
