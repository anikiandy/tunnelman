#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//function for thing class
thing::thing(int imageID, int x, int y, Direction dir,double size ,unsigned int depth) : 
	GraphObject(imageID, x, y,  dir, size,  depth)
	{}

//thing::~thing(){}

//functions for Earth class
//constructor
//Earth::Earth(int x, int y):thing(TID_EARTH,x,y, right, 0.25, 3)
//{}

//Earth::~Earth()
//{}

 void Earth::doSomething()
{//do what the earth do

}
//functions for tunnelMan class
 //constructor
 //tunnelMan::tunnelMan(int x, int y) :thing(TID_PLAYER, x, y)
 //{}
 void tunnelMan::doSomething() {
	 //do what the man do

 }