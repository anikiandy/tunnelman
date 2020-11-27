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
	initEarth(GameBoard); //make Earths
	parts.emplace_back(std::shared_ptr<thing>(new Tunnelman(this)));
	//vector<shared_ptr<thing>>::iterator i = parts.begin();
	//(*i)->doSomething();
	//gamePieces.emplace_back(std::unique_ptr<thing>(new Tunnelman(this)));//add tunnel man to gamepieces vector
	

	for (int i = 0; i < B; i++)//adding boulders to pieces vector (need to finalize)
	{
		parts.emplace_back(std::shared_ptr<thing>(new Boulder(rand() % 59, rand() % 59, this)));
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

StudentWorld::~StudentWorld()
{
	//player->~Tunnelman();
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
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}
