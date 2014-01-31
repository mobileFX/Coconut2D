#include "GameEngine.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
GameEngine::GameEngine()
{
	selectedAvatar = -1;
	selAvatarAppearances = 0;
	counter = 0;
	TICKET_price = 5;
	TICKET_winCount = 3;
	WIN_PRIZES = Array<int> ()(0)(0)(0)(5)(50)(100)(500)(5000);
	setNextState(STATE_TITLE_SCREEN);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GameEngine::~GameEngine()
{
	if(scene)
	{
		scene = (delete scene, nullptr);
	}
}

//=======================================================
// State: STATE_TITLE_SCREEN
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_TITLE_SCREEN::enter()
{
	self->scene = new SceneTitle();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_TITLE_SCREEN::exit()
{
	if(self->scene)
	{
		self->scene = (delete self->scene, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_TITLE_SCREEN::tick(Time time)
{
	if(self->scene->__finished)
	{
		self->setNextState(self->STATE_GAME_BOARD);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_TITLE_SCREEN::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD::enter()
{
	self->scene = new SceneGameBoard();
	self->avatar_leo = self->scene->__root->getChildByName("Avatar_Leonidas");
	self->avatar_xerxes = self->scene->__root->getChildByName("Avatar_Xerxes");
	self->avatar_spartan = self->scene->__root->getChildByName("Avatar_Spartan");
	self->avatar_persian = self->scene->__root->getChildByName("Avatar_Persian");
	self->avatar_swords = self->scene->__root->getChildByName("Avatar_Swords");
	self->avatar_armor = self->scene->__root->getChildByName("Avatar_Armor");
	self->btnBuyTicket = self->scene->__root->getChildByName("BuyTicketButton");
	self->btnOpenAll = self->scene->__root->getChildByName("OpenAllButton");
	self->cells = self->scene->__root->getChildByName("Grid")->__children.slice(0, 12);
	self->cellsOpen = Array<bool> ()(false)(false)(false)(false)(false)(false)(false)(false)(false)(false)(false)(false);
	self->avatars = Array<CocoClip*> ()(self->avatar_leo)(self->avatar_xerxes)(self->avatar_spartan)(self->avatar_persian)(self->avatar_swords)(self->avatar_armor);
	self->balance = 5000;
	self->TICKET_TicketID = self->createGUID();
	self->TICKET_cells.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD::exit()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD::tick(Time time)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_JUMPING_AVATARS
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_JUMPING_AVATARS::enter()
{
	self->scene->gotoAndPlayByName("JumpingAvatars");
	for(int i = self->avatars.size(); i--;)
		if(i != self->selectedAvatar)
		{
			self->avatars[i]->gotoFrameByName("Enable", false);
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_JUMPING_AVATARS::tick(Time time)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_JUMPING_AVATARS::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_CHOOSE_AVATAR
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_CHOOSE_AVATAR::enter()
{
	self->scene->stop();
	if(self->selectedAvatar != -1)
	{
		self->btnBuyTicket->gotoFrameByName("Enabled", true);
	}
	self->selAvatarAppearances = 0;
	self->TICKET_cells.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_CHOOSE_AVATAR::exit()
{
	self->scene->__root->getChildByName("PrizeTable")->gotoFrameByName("Show", false);
	for(int i = self->cells.size(); i--;)
	{
		self->cells[i]->gotoFrameByName("closed", true);
		self->cellsOpen[i] = false;
		CocoClip* back = self->cells[i]->getChildByName("Back");
		back->removeChild(back->getChildByName("Placeholder"));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_CHOOSE_AVATAR::tick(Time time)
{
	if(self->selectedAvatar != -1 && engine->isClicked(Array<CocoClip*> ()(self->btnBuyTicket)) != -1)
	{
		for(int i = self->avatars.size(); i--;)
			if(i != self->selectedAvatar)
			{
				self->avatars[i]->gotoFrameByName("Disable", false);
			}
		self->balance -= self->TICKET_price;
		self->setNextState(self->STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL);
	}
	Number clickedAvatar = engine->isClicked(self->avatars);
	if(clickedAvatar != -1)
	{
		if(self->selectedAvatar == clickedAvatar)
		{
			for(int i = self->avatars.size(); i--;)
				if(i != self->selectedAvatar)
				{
					self->avatars[i]->gotoFrameByName("Disable", false);
				}
		}
		else
		{
			for(int i = self->avatars.size(); i--;)
			{
				self->avatars[i]->gotoFrameByName((i == clickedAvatar ? "Select" : "Disable"), false);
			}
		}
		self->selectedAvatar = clickedAvatar;
		self->setNextState(self->STATE_GAME_BOARD_BUY_TICKET);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_CHOOSE_AVATAR::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_BUY_TICKET
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_BUY_TICKET::enter()
{
	self->scene->gotoAndStopByName("WaitToBuyTicket");
	self->btnBuyTicket->gotoFrameByName("Enabled", true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_BUY_TICKET::exit()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_BUY_TICKET::tick(Time time)
{
	if(engine->isClicked(Array<CocoClip*> ()(self->btnBuyTicket)) != -1)
	{
		self->TICKET_TicketID = self->createGUID();
		self->balance -= self->TICKET_price;
		Number blnce = self->balance;
		self->setNextState(self->STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_BUY_TICKET::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL::enter()
{
	gridSymbol = new GridSymbol(self->scene);
	self->scene->gotoAndStopByName("WaitToScratch");
	self->btnBuyTicket->gotoFrameByName("Disable", false);
	self->btnOpenAll->gotoFrameByName("Enabled", true);
	Leonidas = self->scene->__root->getChildByName("Leonidas");
	Xerxes = self->scene->__root->getChildByName("Xerxes");
	Leonidas->gotoFrameByName("Animate", false);
	Xerxes->gotoFrameByName("Animate", false);
	self->TICKET_cells.clear();
	for(int i = 0; i < self->cells.size(); i++)
	{
		self->TICKET_cells.push(gridSymbol->getRandom());
		self->cells[i]->getChildByName("Back")->addChild(gridSymbol->createSymbol(self->TICKET_cells[i]));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL::exit()
{
	self->btnOpenAll->gotoFrameByName("Disable", false);
	Leonidas->gotoFrameByIndex(0, true);
	Xerxes->gotoFrameByIndex(0, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL::tick(Time time)
{
	if(engine->isClicked(Array<CocoClip*> ()(self->btnOpenAll)) != -1)
	{
		self->setNextState(self->STATE_GAME_BOARD_OPEN_ALL);
	}
	self->OpenCell(engine->isClicked(self->cells));
	if(self->TICKET_winCount == self->selAvatarAppearances)
	{
		self->setNextState(self->STATE_GAME_BOARD_OPEN_ALL);
	}
	if(!self->hasClosedCells())
	{
		if(self->selAvatarAppearances >= 3)
		{
			self->setNextState(self->STATE_GAME_BOARD_WIN);
		}
		else
		{
			self->setNextState(self->STATE_GAME_BOARD_LOSE);
		}
		int noWinningAvatars = self->selAvatarAppearances;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_SCRATCH_OR_OPEN_ALL::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_OPEN_ALL
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_OPEN_ALL::enter()
{
	openTicks = 5;
	count = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_OPEN_ALL::exit()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_OPEN_ALL::tick(Time time)
{
	if(!((int)count % (int)openTicks))
	{
		int i = (float)(count) / (float)(openTicks);
		switch(i)
		{
			case 0:
			{
				self->OpenCell(11);
				break;
			}
			break;
			case 1:
			{
				self->OpenCell(1);
				self->OpenCell(2);
				break;
			}
			break;
			case 2:
			{
				self->OpenCell(3);
				self->OpenCell(4);
				self->OpenCell(5);
				break;
			}
			break;
			case 3:
			{
				self->OpenCell(6);
				self->OpenCell(7);
				self->OpenCell(8);
				break;
			}
			break;
			case 4:
			{
				self->OpenCell(9);
				self->OpenCell(10);
				break;
			}
			break;
			case 5:
			{
				self->OpenCell(0);
				break;
			}
			break;
			default:
			{
				if(self->selAvatarAppearances >= 3)
				{
					self->setNextState(self->STATE_GAME_BOARD_WIN);
				}
				else
				{
					self->setNextState(self->STATE_GAME_BOARD_LOSE);
				}
			}
			break;
		}
	}
	count++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_OPEN_ALL::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_WIN
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_WIN::enter()
{
	self->setTexts();
	self->scene->gotoAndStopByName("WinAnim");
	for(int i = self->cells.size(); i--;)
	{
		if(self->selectedAvatar == (self->TICKET_cells[i] - 1))
		{
			self->cells[i]->gotoFrameByName("Winner", false);
		}
		else
		{
			self->cells[i]->gotoFrameByName("Looser", false);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_WIN::exit()
{
	CocoClip* win = self->scene->__root->getChildByName("YouWin");
	win->gotoFrameByIndex(0, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_WIN::tick(Time time)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_WIN::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

//=======================================================
// State: STATE_GAME_BOARD_LOSE
//=======================================================

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_LOSE::enter()
{
	self->setNextState(self->STATE_JUMPING_AVATARS);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_LOSE::exit()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_LOSE::tick(Time time)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::STATE_GAME_BOARD_LOSE::paint(WebGLRenderingContext* gl, Time time)
{
	self->scene->paint(gl, time);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::setTexts()
{
	balance += WIN_PRIZES[selAvatarAppearances];
	Number blnce = balance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String GameEngine::createGUID()
{
	Array<String> list = null()("87D2C004-1441-4CD5-AEB3-E221BA96C9B8")("23FCC6FD-2E17-49ED-85E3-21AFB67A9FA5")("F09FEBCF-7541-43F3-BFE5-EE48EC44A3AD")("F6C2F6D2-5B47-4E0F-A6EC-DAE78AADCE47")("7798C232-4859-4FF8-93BD-8CE68D1F0718")("46F61FE6-A48A-45D6-A96E-2E2E83D9A21A");
	return list[floor(((float)rand() / (float)RAND_MAX) * list.size())];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameEngine::hasClosedCells()
{
	for(int c = cellsOpen.size(); c--;)
		if(!cellsOpen[c])
		{
			return true;
		}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::OpenCell(int i)
{
	if(i != -1 && !cellsOpen[i])
	{
		cells[i]->gotoFrameByName("flip", false);
		cellsOpen[i] = true;
		if(selectedAvatar == (TICKET_cells[i] - 1))
		{
			selAvatarAppearances++;
		}
	}
}
