#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}


// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
void StudentWorld::initEarth(Earth *board[59][59])
{
	for (int c = 0; c < 59; c++)
	{
		for (int r = 0; r < 59; r++)
		{
			board[c][r] = new Earth(c,r);
		}
	}
}