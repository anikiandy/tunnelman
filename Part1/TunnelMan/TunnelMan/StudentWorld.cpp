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
	player = new Tunnelman(this);//make player
	pieces.emplace_back(player);
	initEarth(GameBoard); //make Earths
	for (int i = 0; i < B; i++)
	{
		Boulder* temp = (new Boulder(rand() % 59, rand() % 59, this));
		pieces.emplace_back(temp);
	}
	return GWSTATUS_CONTINUE_GAME;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
void StudentWorld::initEarth(Earth *board[BOARDSIZE][BOARDSIZE])
{
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			board[r][c] = new Earth(r,c,this);
			int Y = board[r][c]->getY();
			//if (r == 59) board[r][c]->setVisible(false);
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
	//std::cout << "clearing :" << x << "  " << y << endl;
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
	player->~Tunnelman();
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
	player->~Tunnelman();
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}
