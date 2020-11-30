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
		do
		{
			y = ((rand() ) % 59)+5;
			do {//avoid boulders in mine shaft
				x = rand() % 59;
			} while (x > 26 && x < 35);
			for (int c = 0; c < 4; c++) //clear earth behind boulder
			{
				for (int r = 0; r < 4; r++)
				{
					ClearEarth(r + x, c + y);
				}
			}
		} while (boulderClash(x, y) || boulderClash(x + 3, y) ||
			boulderClash(x, y + 3) || boulderClash(x + 3, y + 3));
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
