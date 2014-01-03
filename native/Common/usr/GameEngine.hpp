#ifndef __GAMEENGINE_HPP__
#define __GAMEENGINE_HPP__

#include "Coconut2D.hpp"
#include "CocoEngine.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"

class GameEngine : public CocoEngine
{
public:
	CocoScene* scene;
	Number balance;
	Number winnings;
	Array<CocoClip*> avatars;
	CocoClip* avatar_leo;
	CocoClip* avatar_xerxes;
	CocoClip* avatar_spartan;
	CocoClip* avatar_persian;
	CocoClip* avatar_swords;
	CocoClip* avatar_armor;
	CocoClip* btnOpenAll;
	CocoClip* btnBuyTicket;
	Number selectedAvatar;
	GameEngine();
	~GameEngine();
	struct STATE_TITLE_SCREEN : State
	{
		GameEngine* self;
		STATE_TITLE_SCREEN(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_TITLE_SCREEN = new struct STATE_TITLE_SCREEN(this);
	struct STATE_GAME_BOARD : State
	{
		GameEngine* self;
		STATE_GAME_BOARD(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD = new struct STATE_GAME_BOARD(this);
	struct STATE_GAME_BOARD_CHOOSE_AVATAR : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_CHOOSE_AVATAR(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_CHOOSE_AVATAR = new struct STATE_GAME_BOARD_CHOOSE_AVATAR(this);
	struct STATE_GAME_BOARD_BUY_TICKET : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_BUY_TICKET(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_BUY_TICKET = new struct STATE_GAME_BOARD_BUY_TICKET(this);
	struct STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL = new struct STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL(this);
	struct STATE_GAME_BOARD_OPEN_ALL : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_OPEN_ALL(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_OPEN_ALL = new struct STATE_GAME_BOARD_OPEN_ALL(this);
	struct STATE_GAME_BOARD_WIN : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_WIN(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_WIN = new struct STATE_GAME_BOARD_WIN(this);
	struct STATE_GAME_BOARD_LOSE : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_LOSE(GameEngine* self) : self(self) {}
		void enter();
		void exit();
		void tick(float time);
		void paint(WebGLRenderingContext* gl, float time);
	}* STATE_GAME_BOARD_LOSE = new struct STATE_GAME_BOARD_LOSE(this);
};

#endif
