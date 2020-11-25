#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//function for thing class
void thing::doSomething()
{
	std::cout << "hi";
}

//thing::~thing(){}

//functions for Earth class
//constructor


//functions for tunnelMan class
void Tunnelman::move(const int direction)
{
	//get current position 
	int x = this->getX();
	int y = this->getY();
	switch (direction)
	{
	case KEY_PRESS_UP:
		if (this->getDirection() != up) this->setDirection(up);
		else if (y < 60) this->moveTo(x, y + 4);
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
		else if (x < 60) this->moveTo(x + 4, y);
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
	 

 }