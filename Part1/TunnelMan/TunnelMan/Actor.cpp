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
void Tunnelman::move(const int &direction)
{
	//get current position 
	int x = this->getX();
	int y = this->getY();
	switch (direction)
	{
	case 1002:
		if (y < 55) this->moveTo(x, y + 4);
		return;
	case 1003:
		if (y > 0) this->moveTo(x, y - 4);
		return;
	case 1000:
		if (x > 0) this->moveTo(x - 4, y);
		return;
	case 1001 :
		if (x < 55) this->moveTo(x + 4, y);
		return;
	default:
		return;
	}

}

bool Tunnelman::amAlive() {
	if (hp > 0) return true;
	else return false;
}
 void Tunnelman::doSomething() {
	 //do what the man do

 }