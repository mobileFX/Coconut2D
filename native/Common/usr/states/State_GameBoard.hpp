#ifndef __STATE_GAMEBOARD_HPP__
#define __STATE_GAMEBOARD_HPP__

#include "Coconut2D.hpp"
#include "CocoEngineState.hpp"
#include "CocoEngine.hpp"
#include "WebGLRenderingContext.hpp"
#include "SceneGameBoard.hpp"

class State_GameBoard : public CocoEngineState
{
public:
	SceneGameBoard* scene;
	State_GameBoard();
	void tick(CocoEngine* engine, WebGLRenderingContext* gl, Number time);
};

#endif
