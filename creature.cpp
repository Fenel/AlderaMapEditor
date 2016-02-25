#include "thing.h"
#include "creature.h"
#include "system.h"

extern System System;

Creature::Creature()
{
	id = currentId;
	currentId++;
	direction = 2;
	startedWalking = 0;
	this->parent = NULL;

	broken = false;
}

unsigned int Creature::currentId = 0;

/*
Creature::~Creature()
{
      id = 0;
}
*/

void Creature::setName(string _name)
{ 
	 name = _name; 
	 formattedName.setFont(System.font);
	 formattedName.setString(name);
	 formattedName.setCharacterSize(11);
	 formattedName.setColor(sf::Color::White);
	 formattedName.setPosition(0.0,0.0);
	 //sf::FloatRect rect = formattedName.getLocalBounds();!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 //formattedName.setOrigin(int(rect.getSize().x/2), 0);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void Creature::setPos(unsigned int _posX, unsigned int _posY, unsigned char _posZ)
{
	posX = _posX;
	posY = _posY;
	posZ = _posZ;
}

void Creature::setStartedWalking()
{
    startedWalking = clock();
}

bool Creature::isWalking()
{
	if(startedWalking + speed <= clock())
		return false;
	else
		return true;
}
 
void Creature::addHealth(int _health)
{
	if(health + _health > 0)
		health += _health;
	if(health + _health <= 0)
		health = 0;
	if(health + _health > maxHealth)
		health = maxHealth;
}


void Creature::addPosX(int _posX)
{
	posX += _posX;
}

void Creature::addPosY(int _posY)
{
	posY += _posY;
}

void Creature::addPosZ(int _posZ)
{
	posZ += _posZ;
}