#include "State_TitleScreen.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
State_TitleScreen::State_TitleScreen()
{
	scene = new SceneTitle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void State_TitleScreen::tick(CocoEngine* engine, WebGLRenderingContext* gl, Number time)
{
	super.tick(engine, gl, time);
	if(scene != NULL)
	{
		gl->clearColor(0.0, 0.0, 0.0, 1.0);
		gl->clear(gl->COLOR_BUFFER_BIT);
		scene->tick(gl, time);
	}
}
