#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	int x, y;
	initEarth(GameBoard); //make Earths
	parts.emplace_back(std::shared_ptr<thing>(new Tunnelman(this)));
	
	for (int i = 0; i < B; i++)//adding boulders to pieces vector (need to finalize)
	{
		y = ((rand() + 1) % 59);
		do {//avoid boulders in mine shaft
			x = rand() % 59;
		} while (x > 30 && x < 35);
		parts.emplace_back(std::shared_ptr<thing>(new Boulder(x, y, this)));
	}
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
bool StudentWorld::ClearEarth(int x, int y)
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

void StudentWorld::removeDead(std::vector<shared_ptr<thing>> &parts)
{
	std::vector<shared_ptr<thing>>::iterator it = parts.begin();
	while (it != parts.end())
	{
		if (!(*it)->amAlive())
			it = parts.erase(it);
		else it++;
	}

}

bool StudentWorld::isEarth(int x, int y)
{
	if (GameBoard[x][y]->isVisible())return true;
	else return false;
}

StudentWorld::~StudentWorld()
{
	parts.clear();
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}

void StudentWorld::cleanUp()
{	
	parts.clear();
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}
