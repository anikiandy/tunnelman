#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <string>
#include <memory>
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//function for thing class
void thing::doSomething()
{

}
bool thing::checkEarthSpan(int x, int y, char dir)
{
	switch (dir)
	{
	case 'y':
		for (int i = 0; i <= 3; i++) if (getWorld()->isEarth(x, y + i)) return true;
		return false;
		break;
	default:
		for (int i = 0; i <= 3; i++) if (getWorld()->isEarth(x + i, y)) return true;
		return false;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~Collectable~~~~~~~~~~~~~~~~~~~
Collectible::Collectible(int IMID, StudentWorld* here) : thing(IMID, here, rand() %(59-4), rand()%(59-4) , right, 1, 2) 
{
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~OIL~~~~~~~~~~~~~~~~~~~~~~~

Oil::Oil( StudentWorld* here) : Collectible(TID_BARREL, here)
{
	setVisible(true);
	alive = true; 
}

void Oil::doSomething()
{

}

//~~~~~~~~~~~~~~functions for Earth class~~~~~~~~~~~~~~~~
Earth::Earth(int x, int y, StudentWorld* here) :thing(TID_EARTH, here, x, y, right, 0.25, 3)
{
	setVisible(true);
}

//~~~~~~~~~~~~functions for tunnelMan class~~~~~~~~~~~~~~~~~
Tunnelman::Tunnelman (StudentWorld * here) : thing(TID_PLAYER, here, 30, 60, right, 1, 0) //constructor
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
		else if (y < 60)
		{
			for (int i = 0; i < 4; i++)
			{
				if (getWorld()->boulderClash(x + i , y +4))return;
			}
			this->moveTo(x, y + 1);
		}
		break;
	case KEY_PRESS_DOWN:
		if (this->getDirection() != down) this->setDirection(down);
		else if (y > 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (getWorld()->boulderClash(x + i, y-1)) return;
			}
			this->moveTo(x, y - 1);
		}
		break;
	case KEY_PRESS_LEFT:
		if (this->getDirection() != left) this->setDirection(left);
		else if (x > 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (getWorld()->boulderClash(x-1, y + i))return;
			}
			this->moveTo(x - 1, y);
		}
		break;
	case KEY_PRESS_RIGHT :
		if (this->getDirection() != right) this->setDirection(right);
		else if (x < 56)
		{
			for (int i = 0; i < 4; i++)
			{
				if (getWorld()->boulderClash(x+4, y + i)) return;
			}
			if(getWorld())
			this->moveTo(x + 1, y);
		}
		break;
	case KEY_PRESS_ESCAPE:
		getWorld()->decLives();
		break;
	case KEY_PRESS_SPACE:
	{
		//if (waters > 0)
		
			int x = getX(); int y = getY();
			Direction dir = getDirection();
			//waters--; // dec waters
			getWorld()->playSound(SOUND_PLAYER_SQUIRT); //play sound
			if (dir == right) { x += 4;
				if (x > 59) return; //if out of bounds
				else if (checkEarthSpan(x, y, 'y')) return; //if there is eath 
			}
			else if (dir == left) { x -= 4; 
				if (x < 0) return; //if out of bounds
				else if (checkEarthSpan(x, y, 'y')) return; //if there is eath 		
			}
			else if (dir == up) {  y  += 4; 
				if (y > 59) return;
				else if (checkEarthSpan(x, y, 'x')) return;
			}
			else if (dir == down) { y -= 4; 
				if (y < 0) return;
				else if (checkEarthSpan(x, y, 'x')) return;
			}
			this->getWorld()->addPart(std::shared_ptr<thing>(new Squirt(x, y, dir, getWorld())));
			
		
	}
		break;
	
	default:
		break;
	}
	//dig area, if it was dug play dig sound
	dig();
}
void Tunnelman::dig() //asks to clear 4x4 earth at tunnel mans position
{
	bool dug = false;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (getWorld()->ClearEarth(getX() + c, getY() + r)) dug = true;
		}
	}
	if (dug) getWorld()->playSound(SOUND_DIG);
}
bool Tunnelman::amAlive() {
	if (hp > 0) return true;
	else return false;
}
 void Tunnelman::doSomething() {
	 int input;
	 //move or whatever 
	 if (getWorld()->getKey(input))move(input);
 }

 //~~~~~~~~~~~~~~~~~~~~BOULDER stuFFF~~~~~~~~~~~~~~~~~~~~~~~~~
Boulder::Boulder(int x, int y, StudentWorld* here) : thing(TID_BOULDER, here, x, y, down, 1, 1)
 {
	setVisible(true);
	alive = true;
	state = 0; 
	ticker = 0;
 }
	
void Boulder::doSomething()
{
	//get current position
	int x = getX();
	int y = getY();
	if (y == 0) return;
	bool supported = false;
	switch (state)
	{
	case 0://static state check 4 squares under for earth
		for (int i = 0; i < 4; i++)
		{
			if (getWorld()->isEarth(x + i, y - 1)) supported = true;
		}
		if (supported == false) state = 1;
		break;
	case 1:
		if (ticker == 30) {
			state = 2;
			getWorld()->playSound(SOUND_FALLING_ROCK);
		}
		else ticker++;
		break;
	case 2:
		//check for earth before moving 
		for (int i = 0; i < 4; i++)
		{
			if (getWorld()->isEarth(x + i, y - 1))
			{
				state = 0;
				ticker = 0;
				alive = false;
				return;
			}
		}
		moveTo(x, y - 1);
		break;
	}
}

//~~~~~~~~~~~~~~~~SQUIRT~~~~~~~~~~~~~~~~~~~
Squirt::Squirt(int x, int y, Direction dir, StudentWorld* here) : thing(TID_WATER_SPURT, here, x, y, dir, 1, 1)
{
	setVisible(true); 
	alive = true; 
	ticks = 4;

}

void Squirt::doSomething()
{
	Direction dir = getDirection();
	int x = getX(); int y = getY();
	switch (dir)
	{
	case right:
		if (checkEarthSpan(x + 4, y, 'y')) alive = false;
		else if (ticks == 0 || x + 4 > 59 ) alive = false;
		//else if )
		else moveTo(getX() + 1, getY()); ticks--;
		break;
	case left:
		if (checkEarthSpan(x , y, 'y')) alive = false;
		else if (ticks == 0 || x - 1 < 0) alive = false; 
		else moveTo(getX() - 1, getY()); ticks--;
		break;
	case up:
		if (getY() >= 59 || ticks == 0 || (checkEarthSpan(x , y+4, 'x'))) alive = false;
		else moveTo(getX(), getY() + 1); ticks--;
		break;
	case down:
		if (getY() <= 0 || ticks == 0 || (checkEarthSpan(x, y  , 'x'))) alive = false;
		else moveTo(getX(), getY() - 1); ticks--;
		break;
	}
	return;
}


