#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>

#include "thing.h"

using namespace std;

class Creature : public Thing
{
 public:
 Creature();
 bool broken;
 //~Creature();

 string getName()				{ return name; };
 unsigned int getId()			{ return id; };
 unsigned int getHealth()		{ return health; };
 unsigned int getMaxHealth()	{ return maxHealth; };
 unsigned int getPosX()			{ return posX; };
 unsigned int getPosY()			{ return posY; }
 unsigned char getPosZ()		{ return posZ; };
 unsigned char getLooktype()	{ return looktype; };
 unsigned char getDirection()	{ return direction; };
 clock_t getStartedWalking()	{ return startedWalking; };
 unsigned int getSpeed()		{ return speed; };
 unsigned int getRespawnTime()  { return respawnTime; };

 void setName(string _name);
 void setId(unsigned int _id)                                { id = _id; };
 void setPos(unsigned int _posX, unsigned int _posY, unsigned char _posZ);
 void setPosX(unsigned int _posX)							{ posX = _posX; };
 void setPosY(unsigned int _posY)							{ posY = _posY; };
 void setPosZ(unsigned char _posZ)							{ posZ = _posZ; };
 void setLooktype(unsigned char _looktype)					{ looktype = _looktype; };
 void setDirection(unsigned char _direction)				{ direction = _direction; };
 void setHealth(unsigned int _health)						{ health = _health; };
 void setMaxHealth(unsigned int _maxHealth)					{ maxHealth = _maxHealth; };
 void setSpeed(unsigned int _speed)							{ speed = _speed; };
 void setStartedWalking();
 void setRespawnTime(unsigned int time)                     { respawnTime = time; };

 bool isWalking();
 
 void addHealth(int _health);
 void addPosX(int _posX);
 void addPosY(int _posY);
 void addPosZ(int _posZ);

 sf::Text formattedName;
protected:
 unsigned int id;
 std::string name;

 unsigned char looktype, direction;
 unsigned int posX, posY;
 unsigned char posZ;
 unsigned int health, maxHealth;
 unsigned int speed;
 unsigned int respawnTime;

 clock_t startedWalking;

 static unsigned int currentId;
};

#endif //__CREATURE_H__
