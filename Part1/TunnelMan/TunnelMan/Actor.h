#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
class StudentWorld;
int const BOARDSIZE = 60;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class thing : public GraphObject
{
public:
	thing(int imageID, StudentWorld *here, int x, int y, Direction dir, double size, unsigned int depth) :
		GraphObject(imageID, x, y, dir, size, depth)
	{
		world = here;
		setVisible(true);
	}
	virtual ~thing() {}
	virtual bool amAlive() { return false; }
	virtual void doSomething();
	StudentWorld * getWorld() { return world; };
private:
	StudentWorld* world; 

};

class Earth : public thing
{
public:
	Earth(int x, int y, StudentWorld* here);
	virtual ~Earth() {};
};


class Tunnelman : public thing
{
public:
	Tunnelman(StudentWorld* here);
	virtual ~Tunnelman() {}
	void doSomething();
	void move(const int direction);
	bool amAlive();
	void dig();
	//void setWorld(StudentWorld* here);
private:
	int hp, waters, sonars, nugs;
	
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BOULDER STUFF~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Boulder : public thing
{
public:
	Boulder(int x, int y, StudentWorld* here);
	void doSomething();
	virtual ~Boulder() {}
	bool amAlive() { if (getY() > 0)return true; }
private:

	int state; //use for boulder state stable:0, Waiting:1, falling: 2
	int ticker; //used to delay fall
	
};

//~~~~~~~~~~~~~~~~SQUIRT~~~~~~~~~~~~~~~~~~
class Squirt : public thing
{
public:
	Squirt(int x, int y, StudentWorld * here);
	virtual ~Squirt(){}
};

#endif // ACTOR_H_
