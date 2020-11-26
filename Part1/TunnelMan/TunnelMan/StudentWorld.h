#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <memory>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	void initEarth(Earth *board[BOARDSIZE][BOARDSIZE]);
	~StudentWorld();
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	
	}

	virtual int init()
	{
		 player = new Tunnelman(this);//make player
		 initEarth(GameBoard); //make Earths
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		//decLives();
		player->doSomething();
		return GWSTATUS_CONTINUE_GAME;
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp();

	bool ClearEarth(int x, int y);
	
private:
	Tunnelman* player;

	Earth * GameBoard[BOARDSIZE][BOARDSIZE];

};

#endif // STUDENTWORLD_H_
