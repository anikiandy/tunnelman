#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <memory>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
void StudentWorld::initEarth(Earth *board[59][59])
{
	for (int c = 0; c <= 59; c++)
	{
		for (int r = 0; r <= 59; r++)
		{
			board[c][r] = new Earth(c,r,this);
			//if (r >= 55) board[c][r]->setVisible(false);
		}
	}
	
}
void StudentWorld::ClearEarth(int x, int y)
{
	GameBoard[x][y]->setVisible(false);
}

