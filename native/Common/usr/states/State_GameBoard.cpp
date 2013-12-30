#include "State_GameBoard.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
State_GameBoard::State_GameBoard()
{
	scene = new SceneGameBoard();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void State_GameBoard::tick(CocoEngine* engine, WebGLRenderingContext* gl, Number time)
{
	super->tick(engine, gl, time);
	if(scene != NULL)
	{
		gl->clearColor(0.0, 0.0, 0.0, 1.0);
		gl->clear(gl->COLOR_BUFFER_BIT);
		scene->tick(gl, time);
	}
}
