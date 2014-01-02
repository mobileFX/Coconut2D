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
	virtual GameEngine();
	virtual ~GameEngine();
	struct STATE_TITLE_SCREEN : State
	{
		GameEngine* self;
		STATE_TITLE_SCREEN(GameEngine* self) : self(self) {}
		void enter()
		{
			self->scene = new SceneTitle();
		}
		void exit()
		{
			delete self->scene;
		}
		void tick(float time)
		{
			if(self->scene->__finished)
			{
				setNextState(STATE_GAME_BOARD);
			}
		}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_TITLE_SCREEN = new struct STATE_TITLE_SCREEN(this);
	struct STATE_GAME_BOARD : State
	{
		GameEngine* self;
		STATE_GAME_BOARD(GameEngine* self) : self(self) {}
		void enter()
		{
			self->scene = new SceneGameBoard();
			self->avatar_leo = self->scene->__root->getChildByName("Avatar_Leonidas");
			self->avatar_xerxes = self->scene->__root->getChildByName("Avatar_Xerxes");
			self->avatar_spartan = self->scene->__root->getChildByName("Avatar_Spartan");
			self->avatar_persian = self->scene->__root->getChildByName("Avatar_Persian");
			self->avatar_swords = self->scene->__root->getChildByName("Avatar_Swords");
			self->avatar_armor = self->scene->__root->getChildByName("Avatar_Armor");
			self->btnOpenAll = self->scene->__root->getChildByName("BuyTicketButton");
			self->btnBuyTicket = self->scene->__root->getChildByName("OpenAllButton");
			self->avatars = {self->avatar_leo, self->avatar_xerxes, self->avatar_spartan, self->avatar_persian, self->avatar_swords, self->avatar_armor};
		}
		void exit()
		{
			delete self->scene;
		}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD = new struct STATE_GAME_BOARD(this);
	struct STATE_GAME_BOARD_CHOOSE_AVATAR : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_CHOOSE_AVATAR(GameEngine* self) : self(self) {}
		void enter()
		{
			self->scene->stop();
		}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_CHOOSE_AVATAR = new struct STATE_GAME_BOARD_CHOOSE_AVATAR(this);
	struct STATE_GAME_BOARD_BUY_TICKET : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_BUY_TICKET(GameEngine* self) : self(self) {}
		void enter()
		{
			self->scene->gotoAndStopByName("WaitToBuyTicket");
		}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_BUY_TICKET = new struct STATE_GAME_BOARD_BUY_TICKET(this);
	struct STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL(GameEngine* self) : self(self) {}
		void enter()
		{
			self->scene->gotoAndStopByName("WaitToScratch");
		}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL = new struct STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL(this);
	struct STATE_GAME_BOARD_OPEN_ALL : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_OPEN_ALL(GameEngine* self) : self(self) {}
		void enter() {}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_OPEN_ALL = new struct STATE_GAME_BOARD_OPEN_ALL(this);
	struct STATE_GAME_BOARD_WIN : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_WIN(GameEngine* self) : self(self) {}
		void enter() {}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_WIN = new struct STATE_GAME_BOARD_WIN(this);
	struct STATE_GAME_BOARD_LOSE : State
	{
		GameEngine* self;
		STATE_GAME_BOARD_LOSE(GameEngine* self) : self(self) {}
		void enter() {}
		void exit() {}
		void tick(float time) {}
		void paint(WebGLRenderingContext* gl, float time)
		{
			self->scene->paint(gl, time);
		}
	}* STATE_GAME_BOARD_LOSE = new struct STATE_GAME_BOARD_LOSE(this);
};

#endif
