#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "creature.h"
#include "map.h"
#include "container.h"
#include "creaturesManager.h"
#include "game.h"

extern Game Game;
extern Map Map;
using namespace std;

CreaturesManager::CreaturesManager()
{
}


bool CreaturesManager::loadCreature(string creatureName, bool reload, unsigned int id)
{
	vector<std::string> lines;
	vector<std::string> names;
	vector<std::string> values;
	string tmp;

    std::string extension = ".mon";
    std::string filename = "monsters\\";
    filename += creatureName;
    filename += extension;

	std::ifstream file(filename.c_str());
    if(file.is_open())
    {
       while(file)
       {
	      tmp.clear();
          getline(file, tmp,'\n');
		  if(!tmp.empty())
             lines.push_back(tmp);
       }   
       file.close(); 
	}
	else
		return false;

	for(unsigned int i = 0; i < lines.size(); i++)
	{
	   string name = lines[i];
	   name.erase(name.find_first_of("="));
	   names.push_back(name);

	   string value = lines[i];
	   value.erase(0,value.find_first_of("=")+1);
	   values.push_back(value);
	}


	Creature *monster = NULL;
	if(!reload)
	{
		creaturesList.push_back(Creature());
		monster = &creaturesList.back();
	}
	else
	{
		monster = this->getCreature(id);
	}

	for(unsigned int i = 0; i < names.size(); i++)
	{
		if(names[i] == "name")
			monster->setName(values[i]);	
		if(names[i] == "looktype")
		{
			monster->setLooktype(atoi(values[i].c_str()));
		}
		if(names[i] == "corpse")
		{
			//monster->setCorpseId(atoi(values[i].c_str()));
		}
		if(names[i] == "health")
			monster->setHealth(atoi(values[i].c_str()));
		if(names[i] == "maxHealth")
			monster->setMaxHealth(atoi(values[i].c_str()));
		if(names[i] == "level")
			//monster->setLevel(atoi(values[i].c_str()));
		if(names[i] == "experience")
			//monster->setExperience(atoi(values[i].c_str()));
		if(names[i] == "speed")
			monster->setSpeed(atoi(values[i].c_str()));
		if(names[i] == "loot")
		{
			/*
			std::string token, charek;
			for(unsigned int n = 0; n < values[i].length(); n++)
			{
				charek = values[i].at(n);
				if(charek != "|")
				{
					token += charek;
				}
				if(charek == "|")
				{    
					charek = values[i].erase(0, values[i].find_last_of("=")+1);
					unsigned int chance = rand() % 100000;
					if(chance <= atoi(charek.c_str()))
					{
						monster->items.push_back(new Item(token));
						monster->items.at(monster->items.size()-1)->randomize();
						std::cout << monster->getName() << ", " << chance << "/" << charek << ", added " << token << std::endl;
					}
					else
					{
						std::cout << monster->getName() << ", " << chance << "/" << charek << ", DONT " << token << std::endl;
					}
					token.clear();
				}    
			}
			*/
		}
	}
	
	return true;
}

Creature* CreaturesManager::getCreature(unsigned int _id)
{
   for (deque<Creature>::iterator it = creaturesList.begin(); it < creaturesList.end(); it++)
   {
      if (it->getId() == _id)
	  {
		return &(*it);
	  }
   }
   return NULL;
}

unsigned int CreaturesManager::createCreature(string name, unsigned int posx, unsigned int posy, unsigned int posz, unsigned int respawn_time)
{
	if(loadCreature(name,false))
	{
		creaturesList[creaturesList.size()-1].setPos(posx, posy, posz);
		creaturesList[creaturesList.size()-1].setRespawnTime(respawn_time);
		return creaturesList[creaturesList.size()-1].getId();
	}
	return 0;
}

bool CreaturesManager::removeCreature(unsigned int _id)
{
   for (deque<Creature>::iterator it = creaturesList.begin(); it < creaturesList.end(); it++)
   {
      if (it->getId() == _id)
	  {
		 std::cout << it->getName() << std::endl;
		 it->broken = true;
		 //creaturesList.erase(it);
		 return true;
	  }
   }  
   return false;
}

void CreaturesManager::loadSpawn()
{        
    int licznik = 1;
    std::ifstream spawnfile("map/spawn.txt"); 
   	if (spawnfile.is_open())
    {
       std::string bufor;
       while(getline(spawnfile, bufor))
       {
          std::string c;
          std::string name;
          int posx, posy, posz, respawn_time;
          std::string ss = "";
          int n = bufor.length();
          int licznik = 1;
          for(int i = 0; i <= n; i++)
          {
             c = bufor[i];
             if(c != "|")
             {
                ss += c;
             }
             if(c == "|")
             {
                if( licznik == 1)
                {      
                   name = ss;
                }    
                else if( licznik == 2)
                {      
                   posx = atoi(ss.c_str());
                }  
                else if( licznik == 3)
                {      
                   posy = atoi(ss.c_str());
                }
                else if( licznik == 4)
                {       
                   posz = atoi(ss.c_str());
                }
                else if( licznik == 5)
                {      
                   respawn_time = atoi(ss.c_str());
				   respawn_time *= 1000;
                }                                       
                licznik++;
                ss = "";
             }
          }
		  unsigned int monId = this->createCreature(name, posx, posy, posz, respawn_time);
        
		  if(monId != 0)
		  {
			  Tile *tilet = Map.getTile(posx, posy, char(posz));
			  tilet->addThing(this->getCreature(monId));
		  }
       }
    }
	spawnfile.close();
}

void CreaturesManager::saveSpawn()
{     
	remove("map/spawn backup.txt");
	rename("map/spawn.txt", "map/spawn backup.txt");

    std::ofstream spawnfile("map/spawn.txt", std::ios_base::trunc);
   	if (spawnfile.is_open())
    {    
         for(deque<Creature>::iterator it = creaturesList.begin() ; it < creaturesList.end(); it++)
         {
			 if(!it->broken)
			 {
				spawnfile << it->getName() << "|" << it->getPosX() << "|" << it->getPosY() << "|" << int(it->getPosZ()) << "|" << (it->getRespawnTime()/1000) << "|" << std::endl;
			 }
         }	
         spawnfile.close();
    }
}