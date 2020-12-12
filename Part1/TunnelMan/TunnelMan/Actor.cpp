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
int thing::distanceFromMe(const float &x, const  float &y)
{
	return sqrt(pow(getX() - x, 2) + pow(getY() - y, 2));
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
Collectible::Collectible(int IMID, StudentWorld* here) : thing(IMID, here, 
	(IMID == TID_SONAR) ? 0 : rand() %(59-4), (IMID == TID_SONAR) ? 60: rand()%(59-4) , right, 1, 2) 
{

}

//~~~~~~~~~~~~~~~~~~~~~~~~OIL~~~~~~~~~~~~~~~~~~~~~~~

Oil::Oil( StudentWorld* here) : Collectible(TID_BARREL, here)
{
	setVisible(false);
	//alive = true; 
}

void Oil::doSomething()
{
	//look for tunnel man
	int playerX, playerY;
	getWorld()->playerPosition(playerX, playerY);
	//if(sqrt(pow(myX - playerX , 2) + pow(myY - playerY , 2)) <= 6) setVisible(true); //radius <= 4 +2
	if (amAlive())
	{

		if (distanceFromMe(playerX, playerY) <= 4 && distanceFromMe(playerX, playerY) > 3)
		{
			setVisible(true);
			return;
		}
		else if (distanceFromMe(playerX, playerY) <= 3)
		{
			setAlive(false);
			getWorld()->decOil();
			getWorld()->increaseScore(1000);
			getWorld()->playSound(SOUND_FOUND_OIL);
			return;
		}
	}
}

//~!~~~~~~~~~~~~~~GOOOOOLD~~~~~~~~~~~

Gold::Gold(StudentWorld* here, int visibility): Collectible(TID_GOLD, here)
{
	(visibility == 0) ? setVisible(true) : setVisible(false);
}

void Gold::doSomething()
{
	int playerX, playerY;
	getWorld()->playerPosition(playerX, playerY);
	if (distanceFromMe(playerX, playerY) <= 4 && distanceFromMe(playerX, playerY) > 3)
	{
		setVisible(true);
		return;
	 }
	else if (distanceFromMe(playerX, playerY) <= 3)
	{
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->incGold();
		getWorld()->increaseScore(10);
		setAlive(false);
	}
}

//~~~~~~~~~~~~~~~~~~~~Sonar~~~~~~~~~~~~~~~~~~~~~~~~~~~
Sonar::Sonar(StudentWorld* here, int Ticks) : Collectible(TID_SONAR, here)
{
	setVisible(true);
	ticks = Ticks;
}

void Sonar::doSomething()
{
	int playerX, playerY;
	getWorld()->playerPosition(playerX, playerY);
	if (ticks <= 0) setAlive(false);
	else if (distanceFromMe(playerX, playerY) <= 3)
	{
		setAlive(false);
		getWorld()->incSonar();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(75);
	}
	else ticks--;

}

//~~~~~~~~~~~~~~~~~~~~~WATAH~~~~~~~~~~~~~~~~~~~
Water::Water(StudentWorld* here, int Ticks):Collectible(TID_WATER_POOL, here)
{
	setVisible(true);
	ticks = Ticks; 
}

void Water::doSomething()
{
	int x, y;
	getWorld()->playerPosition(x, y);
	if (ticks <= 0) setAlive(false);
	else if (distanceFromMe(x, y) <= 3)
	{
		setAlive(false);
		getWorld()->incWater();
		getWorld()->playSound(SOUND_GOT_GOODIE);
		getWorld()->increaseScore(100);
	}
	else ticks--;
}

//~~~~~~~~~~~~~~functions for Earth class~~~~~~~~~~~~~~~~
Earth::Earth(int x, int y, StudentWorld* here) :thing(TID_EARTH, here, x, y, right, 0.25, 3)
{
	setVisible(true);
}

//~~~~~~~~Function for Protester~~~~~~~~~~~~

Protester::Protester(StudentWorld * here):thing(TID_PROTESTER, here, 59,59, left, 1, 0)
{
	setVisible(true);
	hp = 5;
	restingTicks = max<int>(0, 3 - here->getLevel() / 4);
	ticks = restingTicks;
	spacesToMove = (rand() % 60) + 8; 
}
void Protester::doSomething()
{
	if (!amAlive())return;
	else if (ticks == 0)
	{
		if (spacesToMove >= 0)
		{
			if (!moveInDirection(getDirection()))//if move was blocked change stuffs
			{

			}
		}
		ticks = restingTicks; 
	}
	else
	{
		ticks--; 
	}
}

bool Protester::moveInDirection(int dir)
{
	switch (dir)
	{
	case right:

		return true;
		break;
	case left:

		return true;
		break;
	case up:

		return true;
		break;
	case down:

		return true;
		break;
	}

}
//~~~~~~~~~~~~functions for tunnelMan class~~~~~~~~~~~~~~~~~
Tunnelman::Tunnelman (StudentWorld * here) : thing(TID_PLAYER, here, 30, 60, right, 1, 0) //constructor
{
	setVisible(true);
	hp = 10;
	waters = 5;
	sonars = 1;
	nugs = 0;
	golds = 0;
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
		hp = 0;
		getWorld()->decLives();
		break;
	case KEY_PRESS_SPACE:
	{
		if (waters <= 0) return;
			int x = getX(); int y = getY();
			Direction dir = getDirection();
			waters--; // dec waters
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
	case 'z' :
	case 'Z':
		if (sonars > 0)
		{
			getWorld()->echo();
			getWorld()->playSound(SOUND_SONAR);
			sonars--;
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

 void Tunnelman::doSomething() {
	 int input;
	 //move or whatever 
	 if (hp <= 0) {
		 setAlive(false);
		 return;
	 }
	 if (getWorld()->getKey(input))move(input);
 }

 //~~~~~~~~~~~~~~~~~~~~BOULDER stuFFF~~~~~~~~~~~~~~~~~~~~~~~~~
Boulder::Boulder(int x, int y, StudentWorld* here) : thing(TID_BOULDER, here, x, y, down, 1, 1)
 {
	setVisible(true);
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
				setAlive(false);
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
	ticks = 4;
}

void Squirt::doSomething()
{
	Direction dir = getDirection();
	int x = getX(); int y = getY();
	switch (dir)
	{
	case right:
		if (checkEarthSpan(x + 4, y, 'y')) setAlive(false);
		else if (ticks == 0 || x + 4 > 59 ) setAlive(false);
		else moveTo(getX() + 1, getY()); ticks--;
		break;
	case left:
		if (checkEarthSpan(x , y, 'y')) setAlive(false);
		else if (ticks == 0 || x - 1 < 0) setAlive(false);
		else moveTo(getX() - 1, getY()); ticks--;
		break;
	case up:
		if (getY() >= 59 || ticks == 0 || (checkEarthSpan(x , y+4, 'x')))setAlive(false);
		else moveTo(getX(), getY() + 1); ticks--;
		break;
	case down:
		if (getY() <= 0 || ticks == 0 || (checkEarthSpan(x, y, 'x'))) setAlive(false);
		else moveTo(getX(), getY() - 1); ticks--;
		break;
	}
	return;
}


