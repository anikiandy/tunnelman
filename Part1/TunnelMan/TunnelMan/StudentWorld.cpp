#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	
	initEarth(GameBoard); //make Earths
	player.reset(new Tunnelman(this)); //make player
	parts.emplace_back(player); // put player into parts vector
	makeRocks(std::min<int>(getLevel() / 2 + 2, 9));//construct rocks in parts vector
	addCollectibles(TID_BARREL, std::min<int>(2 + getLevel(), 21));

	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::initEarth(Earth *board[BOARDSIZE][BOARDSIZE])
{
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			board[r][c] = new Earth(r,c,this);
			int Y = board[r][c]->getY();
		}
	}
	//cut shaft
	for (int c = 4; c < 60; c++)
	{
		for (int r = 30; r < 34; r++)
		{
			board[r][c]->setVisible(false);
		}
	}
}
bool StudentWorld::ClearEarth(int x, int y) //turns visibilty off of earth 
{
	bool dug = false;
	if (x <= 59 && x >= 0 && y >= 0 && y <= 59)
	{
		if (GameBoard[x][y]->isVisible())
		{
			GameBoard[x][y]->setVisible(false);
			dug = true;
		}
	}
	return dug;
}

void StudentWorld::makeRocks(int b) //places b boulders randomly, avoiding clashing eachother and the mine shaft
{
	int x, y;
	for (int i = 0; i < b; i++)//adding boulders to pieces vector (need to finalize)
	{
		do
		{
			do {
				y =rand() % 59;// lowest boulder at y=4
			} while (y > 59 || y < 5);
			do {//avoid boulders in mine shaft
				x = rand() % 59;
			} while ((x > 26 && x < 35) || x > 56);
			for (int c = 0; c < 4; c++) //clear earth behind boulder
			{
				for (int r = 0; r < 4; r++)
				{
					ClearEarth(r + x, c + y);
				}
			}
		} while (boulderClash(x, y) || boulderClash(x + 3, y) ||
			boulderClash(x, y + 3) || boulderClash(x + 3, y + 3));//dont overlap boulders 
		parts.emplace_back(std::shared_ptr<thing>(new Boulder(x, y, this)));
	}
}
void StudentWorld::removeDead(std::vector<shared_ptr<thing>> &parts) //removes any thing objects which report to be not alive
{
	std::vector<shared_ptr<thing>>::iterator it = parts.begin();
	while (it != parts.end())
	{
		if (!(*it)->amAlive())
			it = parts.erase(it);
		else it++;
	}

}

void StudentWorld::mergeTempParts()//merge anything in temp parts to parts list
{
	std::vector<std::shared_ptr<thing>>::iterator it = tempParts.begin();
	while (it != tempParts.end())
	{
		parts.emplace_back(*it);
		it++; 
	}
	tempParts.clear(); //clear vector
}
bool StudentWorld::isEarth(int x, int y) // returns true if designated x,y coord is a piece of earth which is set to visible
{
	if (y > 59) return false;
	else if (x < 0 || x > 59) return true;
	else if (GameBoard[x][y]->isVisible())return true;
	else return false;
}
void StudentWorld::addCollectibles(int IMID, int num)
{
	for (int i = 0; i < num; i++)
	{
		switch (IMID)
		{
		case TID_BARREL:
			goodies.emplace_back(std::shared_ptr<Collectible>(new Oil(this)));
			break;
		}
	}

}

void StudentWorld::playerPosition(int& x, int& y)
{
	x = player->getX();
	y = player->getY();
}
bool StudentWorld::boulderClash(int x, int y) //Pass a point to it, return true if that point is within a boulder image
{
	int bx, by;
	std::vector<std::shared_ptr<thing>>::iterator it = parts.begin();
	while (it != parts.end())
	{
		if ((*it)->getID() == TID_BOULDER) // is the object a boulder
		{
			bx = (*it)->getX();
			by = (*it)->getY();
			if ((x >= bx && x <= bx + 3) && (y >= by && y <= by + 3)) return true; //pixel is within image
		}
		it++; //iterate 
	}
	return false; // if we cycle through the whole array of parts without clash return false
}

StudentWorld::~StudentWorld()
{
	player.reset();
	parts.clear(); //clears parts vector of all the <things>
	for (int c = 0; c < BOARDSIZE; c++) // delete earths
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}

void StudentWorld::cleanUp()
{	
	player.reset();
	parts.clear();
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}

void StudentWorld::addPart(std::shared_ptr<thing> part) //put part into tempParts vector
{
	tempParts.emplace_back(part);
}
