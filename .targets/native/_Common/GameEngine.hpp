#ifndef __GAMEENGINE_HPP__
#define __GAMEENGINE_HPP__

#include "Coconut2D.hpp"
#include "CocoEngine.hpp"

class GameEngine : public CocoEngine
{
public:
	CocoScene* scene;
	GameEngine();
	~GameEngine();
	struct STATE_GAME : State
	{
		GameEngine* self;
		STATE_GAME(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, Time time);
	}* STATE_GAME = new struct STATE_GAME(this);
};

#endif
