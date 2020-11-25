#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <memory>
#include <iostream>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	void initEarth(Earth *board[59][59]);
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	
	}

	virtual int init()//I guess this is supposed to set up the board?
	{
		 player = new Tunnelman();
		 initEarth(GameBoard);
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		//decLives();
		int input; 
		if (getKey(input))
		{
			player->move(input);
			std::cout << input << std::endl;
		}
	
		return GWSTATUS_CONTINUE_GAME;
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{
	}

private:
	Tunnelman* player;
	Earth * GameBoard[59][59];

};

#endif // STUDENTWORLD_H_
