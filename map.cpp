#include <SFML/Graphics.hpp>

#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

#include "map.h"
#include "game.h"
#include "baseItems.h"
#include "creature.h"
#include "system.h"
#include "creaturesManager.h"

extern Game Game;
extern BaseItems BaseItems;
extern System System;
extern CreaturesManager CreaturesManager;
extern sf::RenderWindow App;
extern std::string intToStr(int n);
extern sf::RenderTexture renderedMapTexture;

int MAP_MAX_DIMENSIONS = 640;

Map::Map()
{
	posx = 15;
	posy = 15;
}

bool Map::deleteTopThingOnTile(unsigned int x, unsigned int y, unsigned char z)
{
    if(tiles_tab[posToIndex(x, y, z)])
    {
       tiles_tab[posToIndex(x, y, z)]->removeTopThing();
       return true;
    }
    return false;
}     

unsigned int Map::posToIndex(unsigned int x, unsigned int y, unsigned char z)
{
   unsigned int R = 0, multiplier = 1;

   R += multiplier * x;
   multiplier *= MAP_MAX_DIMENSIONS;

   R += multiplier * y;
   multiplier *= MAP_MAX_DIMENSIONS;

   R += multiplier * int(z);
   multiplier *= 15;  
              
   return R;
}

void Map::indexToPos(unsigned int &x, unsigned int &y, unsigned char &z, unsigned int index)
{
   unsigned int R = 1;

   x = index % MAP_MAX_DIMENSIONS;
   index /= MAP_MAX_DIMENSIONS;
      
   y = index % MAP_MAX_DIMENSIONS;
   index /= MAP_MAX_DIMENSIONS;
      
   z = char(index%15);            
}

void Map::setTile(Position pos, Tile *tile)
{
    setTile(pos.x,pos.y,pos.z,tile);
}

void Map::setTile(unsigned short x, unsigned short y, unsigned char z, Tile *tile)
{
    if(tiles_tab[posToIndex(x, y, z)])
    {
       delete tiles_tab[posToIndex(x, y, z)];
    }
	tiles_tab[posToIndex(x, y, z)] = tile; 
}

Tile* Map::getTile(Position pos)
{
    return getTile(pos.x,pos.y,pos.z);
}

Tile* Map::getTile(unsigned short x, unsigned short y, unsigned char z)
{
    if(tiles_tab[posToIndex(x, y, z)])
    {
       return tiles_tab[posToIndex(x, y, z)];
    }
	else
	{
		Tile *tile = new Tile(x,y,z);
		this->setTile(x,y,z,tile);
		return tiles_tab[posToIndex(x, y, z)];
	}
}


void Map::render()
{
	if(Game.currentZ >= 7)
	{
		for(unsigned char zx = 7; zx <= Game.currentZ; zx++)
		{ 
			if(zx == Game.currentZ && Game.currentZ != 7 && Game.isDrawShade)
				renderedMapTexture.draw(Game.rectFloorShade);
			for(unsigned char step=0;step<=4;step++)    
			for(unsigned int x = Game.currentX; x <= Game.currentX+Game.maxX + 1 ;x++)
			for(unsigned int y = Game.currentY; y <= Game.currentY+Game.maxY + 1 ;y++)
				if(tiles_tab[posToIndex(x, y, zx)])
					tiles_tab[posToIndex(x, y, zx)]->render(0, 0, Game.currentX, Game.currentY, step);          
		}
	}
	else
	{
		for(unsigned char zx = 0; zx <= Game.currentZ; zx++)
		{ 
			if(zx == Game.currentZ && Game.currentZ != 0 && Game.isDrawShade)
				renderedMapTexture.draw(Game.rectFloorShade);
			for(unsigned char step=0;step<=4;step++)    
			for(unsigned int x = Game.currentX; x <= Game.currentX+Game.maxX + 1 ;x++)
			for(unsigned int y = Game.currentY; y <= Game.currentY+Game.maxY + 1; y++)
				if(tiles_tab[posToIndex(x, y, zx)])
					tiles_tab[posToIndex(x, y, zx)]->render(0, 0, Game.currentX, Game.currentY, step);       
		}
	}
}

void Map::mouse(unsigned char type, int mouse_x, int mouse_y)//x i y myszki na mapie
{    
	for(int y = 0; y <= Game.maxY*32; y+=32)
	for(int x = 0; x <= Game.maxX*32; x+=32)
	{
		if(mouse_x > x && mouse_x < x+32
		&& mouse_y > y && mouse_y < y+32)
		{ 
			Game.currentMouseX = Game.currentX+x/32;
			Game.currentMouseY = Game.currentY+y/32;
			if(Game.mouseHolding) //je¿eli gracz przeci¹gn¹³ item nad pole
			{
				Item *item = dynamic_cast<Item*>(Game.mouseHolding);
				Creature *creature = dynamic_cast<Creature*>(Game.mouseHolding);
				if(type == 1 && (item || creature)) //puszczenie lewego klawisza myszki
				{
                       if(((item && item->mID !=0 && item->mID != 1)|| creature) && (Game.lastTileX != Game.currentX+x/32 || Game.lastTileY != Game.currentY+y/32) || !System.hold)
                       {  
                           if(Game.brushSize == 1 && Game.currentX+x/32 >= 0 && Game.currentX+x/32 <= 600 && Game.currentY+y/32 >=0 && Game.currentY+y/32 <= 600)
                           {
                               if(item)
								   Game.addItem(Game.currentX+x/32, Game.currentY+y/32, Game.currentZ, new Item(item->mID));
							   else
							   {
								   unsigned int monId = CreaturesManager.createCreature(creature->getName(), Game.currentX+x/32, Game.currentY+y/32, Game.currentZ, 60000);
        
								   if(monId != 0)
								   {
									  Tile *tilet = this->getTile(Game.currentX+x/32, Game.currentY+y/32, Game.currentZ);
								      tilet->addThing(CreaturesManager.getCreature(monId));
							       }
							   }
                           }
                           if(Game.brushSize == 2 && item && Game.currentX+x/32 >= 1 && Game.currentX+x/32 <= 599 && Game.currentY+y/32 >=1 && Game.currentY+y/32 <= 599)
                           {
                               for( int i = -1; i <= 1; i++)
                               for( int j = -1; j <= 1; j++)
                               {
								  if(item)
									  Game.addItem(Game.currentX+x/32 + i, Game.currentY+y/32 + j, Game.currentZ, new Item(item->mID));
                               }
                           }
                           if(Game.brushSize == 3 && item && Game.currentX+x/32 >= 2 && Game.currentX+x/32 <= 598 && Game.currentY+y/32 >=2 && Game.currentY+y/32 <= 598)
                           {
                               for( int i = -2; i <= 2; i++)
                               for( int j = -2; j <= 2; j++)
                               {
								  if(item)
									  Game.addItem(Game.currentX+x/32 + i, Game.currentY+y/32 + j, Game.currentZ, new Item(item->mID));
                               }
                           }
                           Game.lastTileX = Game.currentX+x/32;
                           Game.lastTileY = Game.currentY+y/32;
                           System.hold = true; 
                       } 
                       if((item && item->mID == 1) && Game.brushSize == 1 && (( Game.lastTileX != Game.currentX+x/32 || Game.lastTileY != Game.currentY+y/32) || !System.hold)  && Game.currentX+x/32 >= 0 && Game.currentX+x/32 <= 600 && Game.currentY+y/32 >=0 && Game.currentY+y/32 <= 600) 
                       { 
                           this->deleteTopThingOnTile(Game.currentX+x/32, Game.currentY+y/32, Game.currentZ);
                           
                           Game.lastTileX = Game.currentX+x/32;
                           Game.lastTileY = Game.currentY+y/32;
                           System.hold = true; 
                       }
				}
			    if(type == 2 && Game.currentX+x/32 >= 0 && Game.currentX+x/32 <= 600 && Game.currentY+y/32 >=0 && Game.currentY+y/32 <= 600) 
			    {         
					if((( Game.lastTileX != Game.currentX+x/32 || Game.lastTileY != Game.currentY+y/32) || !System.hold)) 
					{  
						Tile* temp;
						temp = this->getTile(Game.currentX+x/32, Game.currentY+y/32, Game.currentZ);

						Item *item = dynamic_cast<Item*>(temp->getTopThing());
						Creature *creature = dynamic_cast<Creature*>(temp->getTopThing());
						if(item)
						{
							Game.mouseHolding = &Game.itemList[item->mID];
							Game.isRenderMonsterList = false;
						}
						else if(creature)
						{
							for(unsigned int i = 0; i <= Game.monsterList.size()-1; i++)
								if(Game.monsterList.at(i).getName() == creature->getName())
								{
									Game.mouseHolding = &Game.monsterList[i];
									Game.isRenderMonsterList = true;
									break;
								}
						}

						System.hold = true; 
					} 
                   
				}
				if(type == 3 && Game.currentX+x/32 >= 0 && Game.currentX+x/32 <= 600 && Game.currentY+y/32 >=0 && Game.currentY+y/32 <= 600) 
				{        
					if( Game.brushSize == 1 && (( Game.lastTileX != Game.currentX+x/32 || Game.lastTileY != Game.currentY+y/32) || !System.hold))
					{ 
						this->deleteTopThingOnTile(Game.currentX+x/32, Game.currentY+y/32, Game.currentZ);
						 
                        Game.lastTileX = Game.currentX+x/32;
                        Game.lastTileY = Game.currentY+y/32;
                        System.hold = true;  
					}                   
				} 
			}
		}
	}
}

void Map::removeCreatureFromTiles(unsigned int cid)
{
	/*
	for(unsigned int z = 0; z <= 14 ;z++)
	{
		for(unsigned int x = Game.myPlayerX - 9; x <= Game.myPlayerX + 10 ;x++)
		{
		   for(unsigned int y = Game.myPlayerY - 7; y <= Game.myPlayerY + 8; y++)
		   {                  
			   if(tiles_tab[posToIndex(x, y, z)])
			   {
				  tiles_tab[posToIndex(x, y, z)]->removeCreatureByID(cid);
			   }
			}
		}
	}
	*/
}

void Map::load()
{
    clock_t time_started = clock(); 
    
    std::string current_tile;
    
    std::cout<<"::Loading world.map...";
    std::ifstream plik_we("map\\world.map");
	if (plik_we.is_open())
    {
        for(int i = 0; i < 6144000 - 1; i++)
        {
	       if(tiles_tab[i])
	       {
              delete tiles_tab[i];     
           }          
        }        
        while(!plik_we.eof())
        {
            std::string x, y, z;
            current_tile.clear();

			std::getline(plik_we,current_tile);
                    
            current_tile.erase(0, 1);        

            x = current_tile.substr(0, current_tile.find_first_of("Y"));           
            current_tile.erase(0, current_tile.find_first_of("Y")+1);
                       
            y = current_tile.substr(0, current_tile.find_first_of("Z"));                   
            current_tile.erase(0, current_tile.find_first_of("Z")+1);

            z = current_tile.substr(0, current_tile.find_first_of("="));                       
            current_tile.erase(0, current_tile.find_first_of("=")+1);
         
            tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))] = new Tile(atoi(x.c_str()), atoi(y.c_str()), char(atoi(z.c_str())));
                       
            std::string token, charek;
            token.clear();

			unsigned int itemID = 0;
			unsigned short count = 1;
			bool abilities = false;

            for(unsigned int i = 0; i < current_tile.length(); i++)
            {
                charek = current_tile[i];
                if(charek != "|" && charek != ".")
                {
                    token += charek;
                }
                if(charek == ".")
                {
                    itemID = atoi(token.c_str());
                    token.clear();
                }
                if(charek == "`")
                {
					abilities = true;
					count = atoi(token.c_str());
                    token.clear();
                }
                if(charek == "|")
                {    
					if(abilities)
					{
						tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))]->addThing(new Item(itemID, count));
						tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))]->getTopItem()->abilities = new ItemAbilities;	
						tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))]->getTopItem()->abilities->parse(token);
					}
					else
						tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))]->addThing(new Item(itemID, count));

                    token.clear();                    
                }    
            }
        }
        std::cout<<" Done!";
    }
    else
    {
        std::cout << "\n::Error while opening world.map\n";
    }
	plik_we.close();

    std::cout<<"::Loading tilesProperties.txt...";
    std::ifstream tilesProperties("Map\\tilesProperties.txt");
	if (tilesProperties.is_open())
    {
		std::string current_tile;
        while(!tilesProperties.eof())
        {
            std::string x, y, z;
            current_tile.clear();

			std::getline(tilesProperties,current_tile);
                    
            current_tile.erase(0, 1);        

            x = current_tile.substr(0, current_tile.find_first_of("Y"));           
            current_tile.erase(0, current_tile.find_first_of("Y")+1);
                       
            y = current_tile.substr(0, current_tile.find_first_of("Z"));                   
            current_tile.erase(0, current_tile.find_first_of("Z")+1);

            z = current_tile.substr(0, current_tile.find_first_of("="));                       
            current_tile.erase(0, current_tile.find_first_of("=")+1);
         
			Tile *tile = tiles_tab[posToIndex(atoi(x.c_str()), atoi(y.c_str()), atoi(z.c_str()))];
                       
			if(tile && current_tile.size() > 0)
			{
				tile->type = atoi(current_tile.c_str());
			}
		}
        std::cout<<" Done!";
    }
    else
        std::cout << "\n::Error while opening tilesProperties.txt\n";

	tilesProperties.close();
	
    std::cout<<" ( " << clock() - time_started << " ms )\n";
}

void Map::save()
{
    std::string current_tile;
    
    std::cout<<"::Saving world.map...";

	remove("map/world backup.map");
	rename("map/world.map", "map/world backup.map");
	remove("map/tilesProperties backup.txt");
	rename("map/tilesProperties.txt", "map/tilesProperties backup.txt");

    std::ofstream plik("map/world.map");
	if (plik.is_open())
    {
        for(int i = 0; i < 6144000 - 1; i++)
        {
	       if(tiles_tab[i])
	       {
              plik << "X" << tiles_tab[i]->pos.x;
	          plik << "Y" << tiles_tab[i]->pos.y;
	          plik << "Z" << int(tiles_tab[i]->pos.z);   
              plik << "=";        
              plik << tiles_tab[i]->returnSaveString() << std::endl;     
           }          
        }
        std::cout<<" Done!";
    }
    else
    {
        std::cout << "\n::Error while saving world.map\n";
    }
	plik.close();

    std::ofstream tilesProperties("map/tilesProperties.txt");
	if (tilesProperties.is_open())
    {
        for(int i = 0; i < 6144000 - 1; i++)
        {
	       if(tiles_tab[i] && tiles_tab[i]->type != 0)
	       {
              tilesProperties << "X" << tiles_tab[i]->pos.x;
	          tilesProperties << "Y" << tiles_tab[i]->pos.y;
	          tilesProperties << "Z" << int(tiles_tab[i]->pos.z);   
              tilesProperties << "=";        
			  tilesProperties << int(tiles_tab[i]->type) << std::endl;     
           }          
        }
        std::cout<<" Done!";
    }
    else
    {
        std::cout << "\n::Error while saving tilesProperties.txt\n";
    }
	tilesProperties.close();
}
