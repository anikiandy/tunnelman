#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//function for thing class
void thing::doSomething()
{
	std::cout << "hi";
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
		else if (y < 56) this->moveTo(x, y + 4);
		break;
	case KEY_PRESS_DOWN:
		if (this->getDirection() != down) this->setDirection(down);
		else if (y > 0) this->moveTo(x, y - 4);
		break;
	case KEY_PRESS_LEFT:
		if (this->getDirection() != left) this->setDirection(left);
		else if (x > 0) this->moveTo(x - 4, y);
		break;
	case KEY_PRESS_RIGHT :
		if (this->getDirection() != right) this->setDirection(right);
		else if (x < 56) this->moveTo(x + 4, y);
		break;
	default:
		break;
	}

}

bool Tunnelman::amAlive() {
	if (hp > 0) return true;
	else return false;
}
 void Tunnelman::doSomething() {
	 int input;
	 if (getWorld()->getKey(input))move(input);

 }