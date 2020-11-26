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

class Boulder : public thing
{
public:
	Boulder(int x, int y, StudentWorld* here);
	void doSomething();
	virtual ~Boulder() {}

private:
	StudentWorld* world;
	int state; //use for boulder state stable:0, Waiting:1, falling: 2
	int ticker; //used to delay fall
	
};





#endif // ACTOR_H_
