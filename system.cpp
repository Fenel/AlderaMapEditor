#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "item.h"
#include "baseItems.h"
#include "creature.h"
#include "game.h"

extern sf::RenderWindow App;
extern sf::RenderTexture renderedMapTexture;
extern BaseItems BaseItems;
extern Game Game;

System::System(unsigned int _width, unsigned int _height, unsigned int _res)
{
	windowWidth = _width;
	windowHeight = _height;
	res = _res;
	App.create(sf::VideoMode(windowWidth, windowHeight, 32), "Aldera Map Editor");
	icon = new sf::Image();
	if(icon->loadFromFile("data/icon.png"))
		App.setIcon(32, 32, icon->getPixelsPtr());

    gameState = 0;
    
    activeTextbox = 0;
    globalTextboxesCount = 0;    
    hold = false;
	keyProcessed = true;

    font.loadFromFile("data/courier.ttf");
   

	modiferX = 0;
	modiferY = 0;
	animationCounter = clock();

	pzRect.setSize(sf::Vector2f(float(32), float(32)));
	pzRect.setFillColor(sf::Color(16, 164, 192, 164));
	houseRect.setSize(sf::Vector2f(float(32), float(32)));
	houseRect.setFillColor(sf::Color(64, 192, 16, 164));
}

System::~System()
{
}

void System::renderItem(int x, int y, Item *item, bool mapTexture)
{
	if(item->mID > 1)
	{	
		unsigned int animid = 0;
		if(BaseItems.getItemType(item->mID)->animcount == 2)
			animid = getAnimationFrame();
		if(BaseItems.getItemType(item->mID)->animcount == 1)
			animid = getAnimationFrame()%2;
		if(BaseItems.getItemType(item->mID)->numsprites > 0)
		{
			if(item->count== 1)
				animid = 0;
			if(item->count == 2)
				animid = 1;
			if(item->count == 3)
				animid = 2;
			if(item->count == 4)
				animid = 3;
			if(item->count >= 5 && item->count < 10)
				animid = 4;
			if(item->count >= 10 && item->count < 25)
				animid = 5;
			if(item->count >= 25 && item->count < 50)
				animid = 6;
			if(item->count >= 50 && item->count <= 100)
				animid = 7;
		}

		sf::Vector2u size = BaseItems.getTexture(BaseItems.getItemType(item->mID)->spriteID + animid)->getSize();

		if(size.x == 32 && size.y == 32)
			BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid)->setPosition(float(x),float(y));
		else if(size.x == 64 && size.y == 32)
			BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid)->setPosition(float(x-32),float(y));
		else if(size.x == 32 && size.y == 64)
			BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid)->setPosition(float(x),float(y-32));
		if(size.x == 64 && size.y == 64)
			BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid)->setPosition(float(x-32),float(y-32));

		if(!mapTexture)
			App.draw(*BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid));
		else
			renderedMapTexture.draw(*BaseItems.getSprite(BaseItems.getItemType(item->mID)->spriteID + animid));
	}
}

void System::renderCreature(int x, int y, Creature *creature, bool mapTexture)
{
	int finalX = 0, finalY = 0, finalLooktype = 0;

	int dir_modifer = 0;

	if(creature->getDirection() == 8)
		dir_modifer = 0;
	if(creature->getDirection() == 2)
		dir_modifer = 3;
	if(creature->getDirection() == 4)
		dir_modifer = 6;
	if(creature->getDirection() == 6)
		dir_modifer = 9;

	finalX = x ;//- modiferX;
	finalY = y ;//- modiferY;
	finalLooktype = int(finalLooktype = Game.looktypes[creature->getLooktype()].north + dir_modifer + getAnimationFrame());
	//BaseItems.getSprite(finalLooktype)->setPosition(float(finalX),float(finalY));
	//if(!mapTexture)
	//	App.draw(*BaseItems.getSprite(finalLooktype));
	//else
	//	renderedMapTexture.draw(*BaseItems.getSprite(finalLooktype));

	sf::Vector2u size = BaseItems.getTexture(finalLooktype)->getSize();

	if(size.x == 32 && size.y == 32)
		BaseItems.getSprite(finalLooktype)->setPosition(float(x),float(y));
	else if(size.x == 64 && size.y == 32)
		BaseItems.getSprite(finalLooktype)->setPosition(float(x-32),float(y));
	else if(size.x == 32 && size.y == 64)
		BaseItems.getSprite(finalLooktype)->setPosition(float(x),float(y-32));
	if(size.x == 64 && size.y == 64)
		BaseItems.getSprite(finalLooktype)->setPosition(float(x-32),float(y-32));

	if(!mapTexture)
		App.draw(*BaseItems.getSprite(finalLooktype));
	else
		renderedMapTexture.draw(*BaseItems.getSprite(finalLooktype));
}

void System::renderCreatureName(int x, int y, Creature *creature, bool mapTexture)
{
	if(creature)
	{		
		x-=24;

		creature->formattedName.setColor(sf::Color::Black);
		creature->formattedName.setPosition(float(x+7),float(y-14));
		if(!mapTexture)
			App.draw(creature->formattedName);
		else
			renderedMapTexture.draw(creature->formattedName);
		creature->formattedName.setPosition(float(x+9),float(y-14));
		if(!mapTexture)
			App.draw(creature->formattedName);
		else
			renderedMapTexture.draw(creature->formattedName);
		creature->formattedName.setPosition(float(x+8),float(y-15));
		if(!mapTexture)
			App.draw(creature->formattedName);
		else
			renderedMapTexture.draw(creature->formattedName);
		creature->formattedName.setPosition(float(x+8),float(y-13));
		if(!mapTexture)
			App.draw(creature->formattedName);
		else
			renderedMapTexture.draw(creature->formattedName);

		creature->formattedName.setColor(sf::Color::White);
		creature->formattedName.setPosition(float(x+8),float(y-14));
		if(!mapTexture)
			App.draw(creature->formattedName);
		else
			renderedMapTexture.draw(creature->formattedName);
	}
}

void System::renderShade(int x, int y, unsigned char type)
{
	if(type == 1)
	{
		pzRect.setPosition(float(x),float(y));
		renderedMapTexture.draw(pzRect);
	}
	if(type == 2)
	{
		houseRect.setPosition(float(x),float(y));
		renderedMapTexture.draw(houseRect);
	}
}

unsigned char System::getAnimationFrame()
{
	if(this->animationCounter + 500 >= clock())
		return 0;
	if(this->animationCounter + 1000 >= clock())
	{
		return 1;
	}
	if(this->animationCounter + 1500 >= clock())
	{
		return 2;
	}
	if(this->animationCounter + 1500 < clock())
	{
		this->animationCounter = clock();
		return 0;
	}
	return 0;
}

 

 

 

 

 

 

 

 

 

