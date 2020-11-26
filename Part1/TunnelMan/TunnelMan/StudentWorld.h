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

	virtual int init();
	virtual int move()
	{
		int pieceCount = 0;
		//decLives();
		for (std::unique_ptr<thing> &i : gamePieces)
		{
			if (i == nullptr)
			{
				break;
			}
			i->doSomething();
			if (!i->amAlive())
			{
				gamePieces.erase(gamePieces.begin() + pieceCount);
				
			}
			else pieceCount++;
		}
		return GWSTATUS_CONTINUE_GAME;
		return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp();
	bool ClearEarth(int x, int y);

	
private:
	Tunnelman* player;
	int B = 3; //number of boulders
	Earth * GameBoard[BOARDSIZE][BOARDSIZE];

	std::vector<std::unique_ptr<thing>> gamePieces;
};

#endif // STUDENTWORLD_H_
