#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class thing : public GraphObject
{
private:
	
public:
	thing(int imageID, int x, int y, Direction dir, double size, unsigned int depth);
	~thing();
	virtual void doSomething();

};

class Earth : thing
{
public:
	Earth(int x, int y);
	~Earth();
	void doSomething();
private:

};

class tunnelMan : thing
{
public:
	tunnelMan(int x, int y);
	~tunnelMan();
	void doSomething();
private:

};
#endif // ACTOR_H_
