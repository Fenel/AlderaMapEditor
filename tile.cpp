#include <iostream>
#include <deque>
#include <algorithm>

#include "tile.h"
#include "thing.h"
#include "system.h"
#include "itemType.h"
#include "creaturesManager.h"

extern CreaturesManager CreaturesManager;
extern System System;
extern std::string intToStr(int n);

using namespace std;

CreatureVector& Tile::getCreatures()
{  
    return creatures;
}


bool Tile::isCollision()
{
    if(ground && ground->isCollision())
    {
        return true;
	}

    if(!ground)
    {
        return true;
	}
    
    ItemVector::const_iterator iit;
	for(iit = topItems.begin(); iit != topItems.end(); ++iit)
    {
		if((*iit)->isCollision())
		   return true;
	}
	
    if(!creatures.empty())
       return true;

	for(iit = downItems.begin(); iit != downItems.end(); ++iit)
    {
		if((*iit)->isCollision())
		   return true;
	}

	return false;
}

void Tile::addThing(Thing *thing)
{    
	thing->parent = this;

    Creature *creature = dynamic_cast<Creature *>(thing);
	if(creature)
	{
        creatures.insert(creatures.begin(), creature);
		creature->setPos(this->pos.x,this->pos.y,this->pos.z);
	}
    else
	{
        Item *item = dynamic_cast<Item *>(thing);
		if(!item)
			return;
		
        if(item->isGroundTile())
		{
            if(ground)
                delete ground;
            ground = item;
		}
		else if(item->isAlwaysOnTop())
		{
			topItems.push_back(item);
        } 
		else if(item->isSplash())
		{
			ItemVector::iterator it;
			for(it = downItems.begin(); it != downItems.end(); ++it)
			{
				if((*it)->isSplash())
				{
					downItems.erase(it);
					delete (*it);
					break;
				}
			}
			downItems.insert(downItems.begin(),item);
		}
		else
			downItems.push_back(item);
    }
}

unsigned char Tile::getIndexOfThing(Thing* thing)
{
	if(ground){
		if(ground == thing){
			return 0;
		}
	}

    unsigned char n = 0;
	ItemVector::const_iterator iit;
	for(iit = topItems.begin(); iit != topItems.end(); ++iit)
    {
		++n;
		if((*iit) == thing)
			return n;
	}

	CreatureVector::const_iterator cit;
	for(cit = creatures.begin(); cit != creatures.end(); ++cit)
    {
		++n;
		if((*cit) == thing)
			return n;
	}

	for(iit = downItems.begin(); iit != downItems.end(); ++iit)
    {
		++n;
		if((*iit) == thing)
			return n;
	}

	return 255;
}

Thing *Tile::getThing(unsigned char stackpos)
{
    if(ground)
    {
		if(stackpos == 0)
		{
			return ground;
		}

		--stackpos;
	}

	if(stackpos < topItems.size())
		return topItems[stackpos];

	stackpos -= (unsigned char)topItems.size();

	if(stackpos < creatures.size())
		return creatures[stackpos];

	stackpos -= (unsigned char)creatures.size();

	if(stackpos < downItems.size())
		return downItems[stackpos];
    return NULL;
}

Item* Tile::getTopItem()
{
	if(topItems.size() > 0)
	{
		return topItems[topItems.size()-1];
	}
	if(downItems.size() > 0)
	{
		return downItems[downItems.size()-1];
	}
	if(ground)
    {
		return ground;
	}
    return NULL;
}

void Tile::transformThing(unsigned char stackpos, Thing *thing)
{
	Item* item = dynamic_cast<Item *>(thing);
	if(item == NULL)
		return;

	Item* oldItem = NULL;

	if(ground){
		if(stackpos == 0){
			oldItem = ground;
			ground = item;
		}

		--stackpos;
	}

	if(stackpos < (unsigned char)topItems.size()){
		ItemVector::iterator it = topItems.begin();
		it += stackpos;
		stackpos = 0;

		oldItem = (*it);
		it = topItems.erase(it);
		topItems.insert(it, item);
	}

	stackpos -= (unsigned char)topItems.size();

	if(stackpos < (unsigned char)creatures.size()){
		return;
	}

	stackpos -= (unsigned char)creatures.size();

	if(stackpos < (unsigned char)downItems.size()){
		ItemVector::iterator it = downItems.begin();
		it += stackpos;
		stackpos = 0;

		oldItem = (*it);
		it = downItems.erase(it);
		downItems.insert(it, item);
	}

	if(stackpos == 0){
		delete oldItem;
	}
}

bool Tile::removeThing(unsigned char stackpos)
{
    Thing *thing = getThing(stackpos);
    if(!thing)
        return false;

    Creature* creature = dynamic_cast<Creature*>(thing);
	if(creature)
    {
		CreatureVector::iterator it = std::find(creatures.begin(), creatures.end(), thing);
    
		if(it != creatures.end())
            creatures.erase(it);
	}
	else 
    {
		Item* item = dynamic_cast<Item*>(thing);
        if(!item)
            return false;

		if(item == ground) 
        {
            delete ground;
			ground = NULL;
			return true;
		}

		ItemVector::iterator iit;

		if(item->baseItem->isAlwaysOnTop())
        {
			for(iit = topItems.begin(); iit != topItems.end(); ++iit)
            {
				if(*iit == item)
                {
					delete (*iit);
					topItems.erase(iit);
					return true;
				}
			}
		}		
		else 
        {
			for (iit = downItems.begin(); iit != downItems.end(); ++iit)
            {
				if(*iit == item)
                {
                    delete (*iit);
                    downItems.erase(iit);
					return true;
				}
			}
		}
	}
	return false;
}

bool Tile::removeTopItem(unsigned short count)
{
	if(topItems.size() > 0)
	{
		topItems.erase(topItems.end()-1);
		return true;
	}
	if(downItems.size() > 0)
	{
		downItems.erase(downItems.end()-1);
		return true;
	}
	if(ground)
    {
		ground = NULL;
		return true;
	}
    return false;
}

bool Tile::removeTopThing()
{
        if(!creatures.empty())
        {
			 unsigned int temp_mID = creatures[creatures.size()-1]->getId();
             creatures.erase(creatures.end()-1);

			 CreaturesManager.removeCreature(temp_mID);
          
             return true;
        }
        if(!topItems.empty())
        {
             topItems.erase(topItems.end()-1);
             return true;  
        }
        if(!downItems.empty())
        {
             downItems.erase(downItems.end()-1);
             return true;
        }
        if(ground)
        {
           delete ground;
           ground = NULL;
           return true;
        }
        return false;
}

bool Tile::removeCreatureByID(unsigned int _id)
{
   int temp = 0;
   for (deque<Creature*>::iterator it = creatures.begin(); it < creatures.end(); it++)
   {
      if(creatures[temp] && creatures[temp]->getId() == _id)
      {
		 creatures.erase(it);
		 CreaturesManager.removeCreature(_id);
         return true;
      }
      temp++;
   }    
   return false;
}

Thing* Tile::getTopThing()
{
	if(!creatures.empty())
	{
		return creatures.back();
	}
	if(!topItems.empty())
	{           
		 return topItems.back();  
	}
	if(!downItems.empty())
	{
		 return downItems.back();
	}
	if(ground)
	{
	   return ground;
	}
	return NULL;
}

void Tile::render(int startWidth, int startHeight, int camera_x, int camera_y, unsigned char step)
{
    if(step == 0) //ground
    {
		offsetx = 0;
		offsety = 0;
		hasHeight = false;
        if(ground)
			System.renderItem(startWidth - camera_x*32 + pos.x*32,startHeight - camera_y*32 + pos.y*32, ground, true);
		if(this->type != 0)
			System.renderShade(startWidth - camera_x*32 + pos.x*32,startHeight - camera_y*32 + pos.y*32, type);
    }
    else if(step == 1) //down items
    {
		for(ItemVector::iterator it = topItems.begin(); it != topItems.end(); ++it)
			if((*it)->baseItem->alwaysOnTopOrder == 1 && (*it)->hasHeight())
			{
				hasHeight = true;
				break;
			}
		for(ItemVector::iterator it = downItems.begin(); it != downItems.end(); ++it)
			if((*it)->hasHeight())
			{
				hasHeight = true;
				break;
			}

		if(!this->hasHeight)
			for(ItemVector::iterator it = downItems.begin(); it != downItems.end(); ++it)
			{
				System.renderItem(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
				if((*it)->hasHeight() && offsetx < 24 && offsety < 24)
				{
					offsetx += 8;
					offsety += 8;
				}
			}
    }
    else if(step == 2) //top items and creatures
    {
		if(this->hasHeight)
			for(ItemVector::iterator it = downItems.begin(); it != downItems.end(); ++it)
			{
				System.renderItem(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
				if((*it)->hasHeight() && offsetx < 24 && offsety < 24)
				{
					offsetx += 8;
					offsety += 8;
				}
			}
		for(ItemVector::iterator it = topItems.begin(); it != topItems.end(); ++it)
        {
			if((*it)->baseItem->alwaysOnTopOrder == 1)
			{
				System.renderItem(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
				if((*it)->hasHeight() && offsetx < 24 && offsety < 24)
				{
					offsetx += 8;
					offsety += 8;
				}
			}
        }
		for(CreatureVector::iterator it = creatures.begin(); it != creatures.end(); ++it)
            System.renderCreature(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
		for(ItemVector::iterator it = topItems.begin(); it != topItems.end(); ++it)
        {
			if((*it)->baseItem->alwaysOnTopOrder == 0)
			{
				System.renderItem(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
				if((*it)->hasHeight() && offsetx < 24 && offsety < 24)
				{
					offsetx += 8;
					offsety += 8;
				}
			}
        }
	}
    else if(step == 3)
	{
    }
    else if(step == 4) //creatures names
    {
			for(CreatureVector::iterator it = creatures.begin(); it != creatures.end(); ++it)
				System.renderCreatureName(startWidth - camera_x*32 + pos.x*32 - offsetx,startHeight - camera_y*32 + pos.y*32 - offsety, *it, true);
    }
}

std::string Tile::returnSaveString()
{
	std::string returning;

    if(ground)
    {
       returning = intToStr(ground->mID);
       returning += ".";
       
       int temp = (int)ground->count;
       returning += intToStr(temp);
	   if(ground->abilities)
	   {
		   returning += "`";
		   returning += ground->abilities->serialize();
	   }
       returning += "|";
    }
    for(int i = 0; i < topItems.size(); i++)
    {
       returning += intToStr(topItems[i]->mID);
       returning += "."; 
       
       int temp = (int)topItems[i]->count;
       returning += intToStr(temp);
	   if(topItems[i]->abilities)
	   {
		   returning += "`";
		   returning += topItems[i]->abilities->serialize();
	   }
       returning += "|";
    }
    for(int i = 0; i < downItems.size(); i++)    
    {
       returning += intToStr(downItems[i]->mID);       
       returning += "."; 
       
       int temp = (int)downItems[i]->count;
       returning += intToStr(temp);
	   if(downItems[i]->abilities)
	   {
		   returning += "`";
		   returning += downItems[i]->abilities->serialize();
	   }
       returning += "|";
    } 
    return returning;
}   