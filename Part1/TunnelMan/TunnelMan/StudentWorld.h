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
		if (!player->amAlive())return GWSTATUS_PLAYER_DIED;
		else
		{
			std::vector<std::shared_ptr<thing>>::iterator it = parts.begin();
			while (it != parts.end())
			{
				(*it)->doSomething();
				it++;
			}
			removeDead(parts);
		}
		mergeTempParts();
		//check dead
		if (getLives() == 0)return GWSTATUS_PLAYER_DIED;
		return GWSTATUS_CONTINUE_GAME;
		//return GWSTATUS_PLAYER_DIED;
	}

	void removeDead(std::vector<std::shared_ptr<thing>> &parts);
	bool boulderClash(int x, int y);
	bool isEarth(int x, int y);

	virtual void cleanUp();
	bool ClearEarth(int x, int y);
	void makeRocks(int b);
	void addPart(std::shared_ptr<thing> part);
	void mergeTempParts();
private:
	std::shared_ptr<Tunnelman>player;
	std::vector<std::shared_ptr<thing>> tempParts;
	int B = 3; //number of boulders
	Earth * GameBoard[BOARDSIZE][BOARDSIZE];
	std::vector<std::shared_ptr<thing>> parts;//the things which need to doSomething
};

#endif // STUDENTWORLD_H_
