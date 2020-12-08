#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <memory>
#include <string>
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
		alive = true;
	}
	virtual ~thing() {}
	void setAlive(bool b) { alive = b; }
	bool amAlive() { return alive ? true : false; }
	virtual void doSomething();
	int distanceFromMe(const float &x, const float &y); 
	StudentWorld * getWorld() { return world; };
	bool checkEarthSpan(int x, int y, char dir);
private:
	StudentWorld* world; 
	bool alive;
};

class Collectible : public thing
{
public:
	Collectible(int IMID, StudentWorld * here);
	virtual void doSomething() {}
	virtual ~Collectible() {}
};

class Oil : public Collectible
{
public:
	Oil( StudentWorld* here);
	void doSomething();
	virtual ~Oil() {}
};

class Gold : public Collectible
{
public:
	Gold(StudentWorld* here, int visibility);
	virtual ~Gold() {}
	void doSomething();
};


class Sonar : public Collectible
{
public:
	Sonar(StudentWorld* here, int Ticks);
	virtual ~Sonar() {}
	void doSomething();
private:
	int ticks;
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
	void incSonar() { sonars++; }
	void incWater() { waters++; }
	void incGold() { golds++;  }

	void dig();
	//void setWorld(StudentWorld* here);
private:
	int hp, waters, sonars,golds, nugs;
	
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~BOULDER STUFF~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Boulder : public thing
{
public:
	Boulder(int x, int y, StudentWorld* here);
	void doSomething();
	virtual ~Boulder() {}
private:
	int state; //use for boulder state stable:0, Waiting:1, falling: 2
	int ticker; //used to delay fall
	
};

//~~~~~~~~~~~~~~~~SQUIRT~~~~~~~~~~~~~~~~~~
class Squirt : public thing
{
public:
	Squirt(int x, int y, Direction dir, StudentWorld * here);
	void doSomething();
	virtual ~Squirt(){}
private:
	int ticks;
};

#endif // ACTOR_H_
