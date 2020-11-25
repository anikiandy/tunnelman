#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <memory>
#include <iostream>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
void StudentWorld::initEarth(Earth *board[59][59])
{
	for (int c = 0; c < 60; c++)
	{
		for (int r = 0; r < 60; r++)
		{
			board[r][c] = new Earth(r+1,c+1,this);
			//if (r == 59) board[r][c]->setVisible(false);
		}
	}
	board[3][1]->setVisible(false);
}
void StudentWorld::ClearEarth(int x, int y)
{
	//std::cout << "clearing :" << x << "  " << y << endl;
	if (x<=59 && x>=0 && y >=0 && y <=59)
		GameBoard[x][y]->setVisible(false);
}

