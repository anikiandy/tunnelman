#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//function for thing class
void thing::doSomething()
{

}

//thing::~thing(){}

//~~~~~~~~~~~~~~functions for Earth class~~~~~~~~~~~~~~~~
Earth::Earth(int x, int y, StudentWorld* here) :thing(TID_EARTH, here, x, y, right, 0.25, 3)
{
	setVisible(true);
}

//~~~~~~~~~~~~functions for tunnelMan class~~~~~~~~~~~~~~~~~
Tunnelman::Tunnelman (StudentWorld * here) : thing(TID_PLAYER, here, 30, 60, right, 1, 0)
{
	setVisible(true);
	hp = 10;
	waters = 5;
	sonars = 10;
	nugs = 0;
}

void Tunnelman::move(const int direction)
{
	//get current position 
	int x = this->getX();
	int y = this->getY();
	switch (direction)
	{
	case KEY_PRESS_UP:
		if (this->getDirection() != up) this->setDirection(up);
		else if (y <=60) this->moveTo(x, y + 1);
		break;
	case KEY_PRESS_DOWN:
		if (this->getDirection() != down) this->setDirection(down);
		else if (y > 0) this->moveTo(x, y - 1);
		break;
	case KEY_PRESS_LEFT:
		if (this->getDirection() != left) this->setDirection(left);
		else if (x > 0) this->moveTo(x - 1, y);
		break;
	case KEY_PRESS_RIGHT :
		if (this->getDirection() != right) this->setDirection(right);
		else if (x < 57) this->moveTo(x + 1, y);
		break;
	default:
		break;
	}

}
void Tunnelman::dig() //asks to clear 4x4 earth at tunnel mans position
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			getWorld()->ClearEarth(getX() + c, getY() + r);
		}
	}
}
bool Tunnelman::amAlive() {
	if (hp > 0) return true;
	else return false;
}
 void Tunnelman::doSomething() {
	 int input;
	 //move or whatever 
	 if (getWorld()->getKey(input))move(input);
	 //clear earth
	 dig();

 }
