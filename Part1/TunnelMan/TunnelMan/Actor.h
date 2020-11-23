#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class thing : public GraphObject
{
public:
	thing(int imageID, int x, int y, Direction dir, double size, unsigned int depth) :
		GraphObject(imageID, x, y, dir, size, depth)
	{
		setVisible(true);
	}
	virtual ~thing() {}
	virtual void doSomething();

};

class Earth : thing
{
public:
	Earth(int x, int y) :thing(TID_EARTH, x, y, right, 0.25, 3)
		{setVisible(true);}
	
	virtual ~Earth() {};
};

class tunnelMan : thing
{
public:
	tunnelMan() : thing(TID_PLAYER, 30 , 60, right, 1, 0) { setVisible(true); }
	~tunnelMan();
	void doSomething();
	void move(const char &direction);
private:
	
};
#endif // ACTOR_H_
