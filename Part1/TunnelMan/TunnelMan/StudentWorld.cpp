#include "StudentWorld.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <algorithm> 
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	oils = std::min<int>(2 + getLevel(), 21);
	pMax = std::min<int>(15, 2 + getLevel() * 1.5);
	pInterval = std::max<int>(25, 200 - getLevel());
	pTicker = 0; 
	P = 1;
	initEarth(GameBoard); //make Earths
	player.reset(new Tunnelman(this)); //make player
	parts.emplace_back(player); // put player into parts vector
	parts.emplace_back(std::shared_ptr<thing>(new Protester(this)));
	
	makeRocks(std::min<int>(getLevel() / 2 + 2, 9));//construct rocks in parts vector
	addCollectibles(TID_BARREL, oils,0);//make oil
	addCollectibles(TID_GOLD, std::max<int>(5 - getLevel() / 2, 2),1);

	return (player->amAlive()) ? GWSTATUS_CONTINUE_GAME : GWSTATUS_PLAYER_DIED;

}

void StudentWorld::initEarth(Earth *board[BOARDSIZE][BOARDSIZE])
{
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			board[r][c] = new Earth(r,c,this);
			int Y = board[r][c]->getY();
		}
	}
	//cut shaft
	for (int c = 4; c < 60; c++)
	{
		for (int r = 30; r < 34; r++)
		{
			board[r][c]->setVisible(false);
		}
	}
}
bool StudentWorld::ClearEarth(int x, int y) //turns visibilty off of earth 
{
	bool dug = false;
	if (x <= 59 && x >= 0 && y >= 0 && y <= 59)
	{
		if (GameBoard[x][y]->isVisible())
		{
			GameBoard[x][y]->setVisible(false);
			dug = true;
		}
	}
	return dug;
}

void StudentWorld::makeRocks(int b) //places b boulders randomly, avoiding clashing eachother and the mine shaft
{
	int x, y;
	for (int i = 0; i < b; i++)//adding boulders to pieces vector (need to finalize)
	{
		do
		{
			do {
				y =rand() % 59;// lowest boulder at y=4
			} while (y > 59 || y < 5);
			do {//avoid boulders in mine shaft
				x = rand() % 59;
			} while ((x > 26 && x < 35) || x > 56);
			for (int c = 0; c < 4; c++) //clear earth behind boulder
			{
				for (int r = 0; r < 4; r++)
				{
					ClearEarth(r + x, c + y);
				}
			}
		} while (boulderClash(x, y) || boulderClash(x + 3, y) ||
			boulderClash(x, y + 3) || boulderClash(x + 3, y + 3));//dont overlap boulders 
		parts.emplace_back(std::shared_ptr<thing>(new Boulder(x, y, this)));
	}
}
void StudentWorld::removeDead(std::vector<shared_ptr<thing>> &parts) //removes any thing objects which report to be not alive
{
	std::vector<shared_ptr<thing>>::iterator it = parts.begin();
	while (it != parts.end())
	{
		if (!(*it)->amAlive())
			it = parts.erase(it);
		else it++;
	}

}
void StudentWorld::removeDeadCollectibles(std::vector<std::shared_ptr<Collectible>>& goodies)
{
	std::vector<shared_ptr<Collectible>>::iterator it = goodies.begin();
	while (it != goodies.end())
	{
		if (!(*it)->amAlive())
			it = goodies.erase(it);
		else it++;
	}

}

void StudentWorld::mergeTempParts()//merge anything in temp parts to parts list
{
	std::vector<std::shared_ptr<thing>>::iterator it = tempParts.begin();
	while (it != tempParts.end())
	{
		parts.emplace_back(*it);
		it++; 
	}
	tempParts.clear(); //clear vector
}
bool StudentWorld::isEarth(int x, int y) // returns true if designated x,y coord is a piece of earth which is set to visible
{
	if (y < 0) return true;
	if (y > 59&& y < 64 && ( x > -1 ) && (x < 59) && y >= 0) return false;
	if (y > 63)return true;
	else if (x < 0 || x > 59) return true;
	else if (GameBoard[x][y]->isVisible())return true;
	else return false;
}
void StudentWorld::addCollectibles(int IMID, int num, int option = 0)
{
	for (int i = 0; i < num; i++)
	{
		switch (IMID)
		{
		case TID_BARREL:
			goodies.emplace_back(std::shared_ptr<Collectible>(new Oil(this)));
			break;
		case TID_GOLD:
			goodies.emplace_back(std::shared_ptr<Collectible>(new Gold(this, option)));
			break;

		case TID_SONAR:
			goodies.emplace_back(std::shared_ptr<Collectible>(new Sonar(this, option)));
			break;

		case TID_WATER_POOL:
			goodies.emplace_back(std::shared_ptr<Collectible>(new Water(this, option)));
			break;
		}
	}

}

bool StudentWorld::oilsLeft()
{
	std::vector<shared_ptr<Collectible>>::iterator it = goodies.begin();
	while (it != goodies.end())
	{
		if ((*it)->getID() == TID_BARREL) return true;
		it++;
	}
	return false;
}

void StudentWorld::playerPosition(int& x, int& y)
{
	x = player->getX();
	y = player->getY();
}
bool StudentWorld::boulderClash(int x, int y) //Pass a point to it, return true if that point is within a boulder image
{
	int bx, by;
	std::vector<std::shared_ptr<thing>>::iterator it = parts.begin();
	while (it != parts.end())
	{
		if ((*it)->getID() == TID_BOULDER) // is the object a boulder
		{
			bx = (*it)->getX();
			by = (*it)->getY();
			if ((x >= bx && x <= bx + 3) && (y >= by && y <= by + 3)) return true; //pixel is within image
		}
		it++; //iterate 
	}
	return false; // if we cycle through the whole array of parts without clash return false
}

void StudentWorld::echo()
{
	std::vector<shared_ptr<Collectible>>::iterator it = goodies.begin();
	while (it != goodies.end())
	{
		if ((*it)->distanceFromMe(player->getX(), player->getY()) <= 12) (*it)->setVisible(true);
		it++;
	}
}

StudentWorld::~StudentWorld()
{
	player.reset();
	parts.clear(); //clears parts vector of all the <things>
	goodies.clear();
	for (int c = 0; c < BOARDSIZE; c++) // delete earths
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}

void StudentWorld::cleanUp()
{	
	player.reset();
	parts.clear();
	goodies.clear();
	for (int c = 0; c < BOARDSIZE; c++)
	{
		for (int r = 0; r < BOARDSIZE; r++)
		{
			GameBoard[r][c]->~Earth();
		}
	}
}

void StudentWorld::addPart(std::shared_ptr<thing> part) //put part into tempParts vector
{
	tempParts.emplace_back(part);
}

string StudentWorld::getInfo()
{

	ostringstream oss;
	//get level
	oss << "Lvl:" << setw(3) << getLevel() << " ";
	//lives
	oss << "Lives:" << setw(2) << getLives() << " ";
	//health
	oss << "Hlth: " << setw(3) << player->getHp() << "% ";
	//water
	oss << "Wtr:" << setw(2) << player->getWater()<< " ";
	//golds
	oss << "Gld:" << setw(2) << player->getGold() << " ";
	//oils
	oss << "Oil Left:" << setw(2) << oils << " ";
	//sonar
	oss << "Sonar:" << setw(2) << player->getSonar() << " ";
	//score
	oss << "Scr: " << setw(5) << getScore(); 
	return oss.str();
}