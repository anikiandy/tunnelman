#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
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

	 int init();
	 int move()
	{
		int G = getLevel() * 25 + 300; //random number
		int match = rand() % G;
		G = rand() % G;
		if (G == match)
		{
			int img;
			G = G % 5;
			img = (G == 0) ? TID_SONAR : TID_WATER_POOL;
			addCollectibles(img, 1, std::max<int>(100, 300 - 10 * getLevel()));
		}
		if (pTicker >= pInterval)
		{
			//add protester
			if (P < pMax)
			{
				tempParts.emplace_back(std::shared_ptr<thing>(new Protester(this))); // put a new protester
				P++; //increment protester count 
			}

			//reset ticker 
			pTicker = 0;
		}
		else pTicker++; 
		//
		int pieceCount = 0;
		if (!player->amAlive())return GWSTATUS_PLAYER_DIED;
		else
		{
			std::vector<std::shared_ptr<thing>>::iterator it = parts.begin();
			while (it != parts.end())
			{
				(*it)->doSomething();
				it++;
			}
			std::vector<std::shared_ptr<Collectible>>::iterator it2 = goodies.begin();
			while (it2 != goodies.end())
			{
				(*it2)->doSomething();
				it2++;
			}
	
			removeDead(parts);
			
			removeDeadCollectibles(goodies);
			
		}
		mergeTempParts();
		setGameStatText(getInfo());
		//check dead
		if (getLives() == 0)return GWSTATUS_PLAYER_DIED;
		else if (!oilsLeft()) return GWSTATUS_FINISHED_LEVEL;
		return GWSTATUS_CONTINUE_GAME;
		//return GWSTATUS_PLAYER_DIED;
	}

	void removeDead(std::vector<std::shared_ptr<thing>> &parts);
	void removeDeadCollectibles(std::vector<std::shared_ptr<Collectible>>&goodie);
	bool boulderClash(int x, int y);
	bool isEarth(int x, int y);

	void cleanUp();
	bool ClearEarth(int x, int y);
	void incSonar() { player->incSonar(); }
	void echo();
	void decOil() { oils--; }
	bool oilsLeft();
	void incGold() { player->incGold(); }
	void incWater() { player->incWater(); }
	void makeRocks(int b);
	void hitPlayer() { player->decHp(); }
	void addCollectibles(int IMID, int num, int option);
	void addPart(std::shared_ptr<thing> part);
	void mergeTempParts();
	void playerPosition(int &x, int &y);
	string getInfo();
private:
	std::shared_ptr<Tunnelman>player;
	std::vector<std::shared_ptr<thing>> tempParts;
	std::vector<std::shared_ptr<Collectible>>goodies;
	//int B; //number of boulders
	int oils;
	int P, pMax, pInterval, pTicker;
	Earth * GameBoard[BOARDSIZE][BOARDSIZE];
	std::vector<std::shared_ptr<thing>> parts;//the things which need to doSomething
};

#endif // STUDENTWORLD_H_
