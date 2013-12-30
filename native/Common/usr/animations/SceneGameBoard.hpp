#ifndef __SCENEGAMEBOARD_HPP__
#define __SCENEGAMEBOARD_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"
#include "WebGLRenderingContext.hpp"

class SceneGameBoard : public CocoScene
{
public:
	SceneGameBoard();
	void tick(WebGLRenderingContext* gl, float time);
	void waitForAction();
	void hint();
};

#endif
