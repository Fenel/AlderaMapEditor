#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <Windows.h>
#include <iostream>
#include <fstream>

#include "game.h"
#include "system.h"
#include "BaseItems.h"
#include "creaturesManager.h"
#include "map.h"

extern sf::RenderWindow App;
extern System System;
extern BaseItems BaseItems;
extern Map Map;
extern CreaturesManager CreaturesManager;
extern struct KeyStorage keyStorage;
extern std::string intToStr(int n);
extern sf::RenderTexture renderedMapTexture;

using namespace std;

Game::Game()
{
	Map.posx = 32;
	Map.posy = 32;

	//renderedMapTexture.create(21*32,18*32);
	renderedMapTexture.create(1920,1080);
	renderedMap.setTexture(renderedMapTexture.getTexture());
	renderedMap.setPosition(128,24);

	currentX      = 0;
	currentY      =	0;
	currentZ      =	7;
	currentScale  =	1;
	brushSize     =	1;
	maxX          =	21;
	maxY          =	18;
	lastTileX     =	0;
	lastTileY     =	0;

	randomizeFactor = 1;

	this->loadLooktypes();
	this->loadMonsterList();
	this->loadItemList();
	Map.load();
	CreaturesManager.loadSpawn();

	itemListScroller = 2;
	monsterListScroller = 0;
	mouseHolding = &itemList.at(2);

	rectItemList1.setSize(sf::Vector2f(float(128), float(64)));
	rectItemList1.setFillColor(sf::Color(64,64,64));
	rectItemList1.setOutlineThickness(0);
	rectItemList1.setPosition(float(0), float(0));

	rectItemList2.setSize(sf::Vector2f(float(128), float(64)));
	rectItemList2.setFillColor(sf::Color(78,78,78));
	rectItemList2.setOutlineThickness(0);
	rectItemList2.setPosition(float(0), float(0));

	rectCurrentItem.setSize(sf::Vector2f(float(127), float(64)));
	rectCurrentItem.setFillColor(sf::Color(50,150,255));
	//rectCurrentItem.setOutlineColor(sf::Color(255,255,255));
	rectCurrentItem.setOutlineThickness(0);

	rectCurrentItemOnMap.setSize(sf::Vector2f(float(32), float(32)));
	rectCurrentItemOnMap.setFillColor(sf::Color(0,0,255,48));
	rectCurrentItemOnMap.setOutlineColor(sf::Color(255,255,255));
	rectCurrentItemOnMap.setOutlineThickness(1);

	rectFloorShade.setSize(sf::Vector2f(1920.0, 1080.0));
	rectFloorShade.setPosition(sf::Vector2f(0.0, 0.0));
	rectFloorShade.setFillColor(sf::Color(0,0,0,160));
	rectFloorShade.setOutlineThickness(0);
	this->isDrawShade = true;
	this->isRenderMonsterList = false;

	this->itemNumber.setFont(System.font);
	this->itemNumber.setCharacterSize(12);
	this->itemNumber.setStyle(sf::Text::Bold);

	srand(time(NULL));

	App.setFramerateLimit(30);
}

void Game::loadLooktypes()
{
	#ifdef _DEBUG
		std::cout << "::Loading outfitData.txt...";
	#endif

	vector<std::string> lines;
	vector<std::string> elements;
	vector<std::string> names;
	vector<std::string> values;
	string tmp;

	std::ifstream file ("data/outfitData.txt");
    if(file.is_open())
    {
       while(file)
       {
	      tmp.clear();
          getline(file, tmp,'\n');
          lines.push_back(tmp);
       }   
       file.close(); 
	}
	else
    {
		#ifdef _DEBUG
			std::cout << "\n::Error while opening outfitData.txt\n";
		#endif
    }

	for(unsigned int i = 0; i < lines.size(); i++) //dla wszystkich linii
	{
		string element;
		while(lines[i].find_first_of(";") != string::npos) //je¿eli linia zawiera ";"
		{
			element = lines[i].substr(0,lines[i].find_first_of(";")); //element =zbiór nazwa+wartoœæ
			lines[i].erase(0,lines[i].find_first_of(";")+2);

			elements.push_back(element);
			element.clear();
		}
		for(unsigned int j = 0; j < elements.size(); j++)
		{
			string name = elements[j];
			name.erase(name.find_first_of("="));
			names.push_back(name);

			string value = elements[j];
			value.erase(0,value.find_first_of("=")+1);
			values.push_back(value);
		}

		looktypes.push_back(Looktype());
		for(unsigned int i = 0; i < names.size(); i++)
		{
			if(names[i] == "id")
				looktypes.at(looktypes.size()-1).id = atoi(values[i].c_str());
			if(names[i] == "name")
				looktypes.at(looktypes.size()-1).name = values[i].c_str();
			if(names[i] == "type")
				looktypes.at(looktypes.size()-1).type = char(atoi(values[i].c_str()));
			if(names[i] == "north")
				looktypes.at(looktypes.size()-1).north = atoi(values[i].c_str());
			if(names[i] == "south")
				looktypes.at(looktypes.size()-1).south = atoi(values[i].c_str());
			if(names[i] == "west")
				looktypes.at(looktypes.size()-1).west = atoi(values[i].c_str());
			if(names[i] == "east")
				looktypes.at(looktypes.size()-1).east = atoi(values[i].c_str());
		}

		elements.clear();
		names.clear();
		values.clear();
	}
	#ifdef _DEBUG
		std::cout << " Done! ";
		std::cout << "Loaded " << looktypes.size() << " looktypes.\n";
	#endif
}

void Game::loadMonsterList()
{
	#ifdef _DEBUG
		std::cout << "::Loading monsterList.txt...";
	#endif

	vector<std::string> lines;
	vector<std::string> elements;
	vector<std::string> names;
	vector<std::string> values;
	string tmp;

	std::ifstream file ("data/monsterList.txt");
    if(file.is_open())
    {
       while(file)
       {
	      tmp.clear();
          getline(file, tmp,'\n');
          lines.push_back(tmp);
       }   
       file.close(); 
	}
	else
    {
		#ifdef _DEBUG
			std::cout << "\n::Error while opening monsterList.txt\n";
		#endif
    }

	for(unsigned int i = 0; i < lines.size(); i++) //dla wszystkich linii
	{
		string element;
		while(lines[i].find_first_of(";") != string::npos) //je¿eli linia zawiera ";"
		{
			element = lines[i].substr(0,lines[i].find_first_of(";")); //element =zbiór nazwa+wartoœæ
			lines[i].erase(0,lines[i].find_first_of(";")+2);

			elements.push_back(element);
			element.clear();
		}
		for(unsigned int j = 0; j < elements.size(); j++)
		{
			string name = elements[j];
			name.erase(name.find_first_of("="));
			names.push_back(name);

			string value = elements[j];
			value.erase(0,value.find_first_of("=")+1);
			values.push_back(value);
		}

		monsterList.push_back(Creature());
		for(unsigned int i = 0; i < names.size(); i++)
		{
			if(names[i] == "name")
				monsterList.at(monsterList.size()-1).setName(values[i].c_str());
			if(names[i] == "looktype")
				monsterList.at(monsterList.size()-1).setLooktype(atoi((values[i].c_str())));
		}

		elements.clear();
		names.clear();
		values.clear();
	}
	monsterList.erase(monsterList.end()-1);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	#ifdef _DEBUG
		std::cout << " Done! ";
		std::cout << "Loaded " << monsterList.size() << " monsters.\n";
	#endif
}

void Game::loadItemList()
{
	#ifdef _DEBUG
		std::cout << "::Loading itemList...";
	#endif

	for(unsigned int i = 0; i < BaseItems.getItemsCount(); i++)
	{
		this->itemList.push_back(Item(i));
	}

	#ifdef _DEBUG
		std::cout << " Done! ";
		std::cout << "Loaded " << this->itemList.size() << " items.\n";
	#endif
}

inline unsigned int Game::getFrameRate()
{
	static sf::Time thetime;
	static sf::Clock elapsed;
	static int frameCounter = 0;
	static int fps = 0;
	frameCounter++;
	thetime = elapsed.getElapsedTime();
	if(thetime.asMilliseconds() > 999)
	{
	   fps = frameCounter;
	   std::string title = "Aldera Map Editor: ";
	   title += intToStr(fps);
	   title += " FPS  X:";
	   title += intToStr(this->currentMouseX);
	   title += " Y:";
	   title += intToStr(this->currentMouseY);
	   title += " Z:";
	   title += intToStr(this->currentZ);
	   App.setTitle(title);
	   frameCounter = 0;
	   elapsed.restart();
	}
	return fps;
}

void Game::renderItemList()
{
	for(int i = 0; i < (App.getSize().y/64)+2; i++)
	{  
		if(i%2 == 0)
		{
			rectItemList1.setPosition(0, i * 64);
			App.draw(rectItemList1);
		}
		else
		{
			rectItemList2.setPosition(0, i * 64);
			App.draw(rectItemList2);
		}
		Item *item = dynamic_cast<Item*>(mouseHolding);
		if(item && i+itemListScroller == item->mID)
		{
			rectCurrentItem.setPosition(0, i * 64);
			App.draw(rectCurrentItem);
		}
		
		if(i+itemListScroller < itemList.size())
		{
			System.renderItem(32, i * 64 + 32, &itemList.at(i+itemListScroller), false);
			this->itemNumber.setPosition(68,i * 64 + 52);
			this->itemNumber.setString(intToStr(i+itemListScroller));
			App.draw(itemNumber);
		}
	}
}

void Game::renderMonsterList()
{
	for(int i = 0; i < (App.getSize().y/64)+2; i++)
	{  
		if(i%2 == 0)
		{
			rectItemList1.setPosition(0, i * 64);
			App.draw(rectItemList1);
		}
		else
		{
			rectItemList2.setPosition(0, i * 64);
			App.draw(rectItemList2);
		}
		Creature *monster = dynamic_cast<Creature*>(mouseHolding);
		if(monster && i+monsterListScroller == monster->getId())
		{
			rectCurrentItem.setPosition(0, i * 64);
			App.draw(rectCurrentItem);
		}
		
		if(i+monsterListScroller < monsterList.size())
		{
			System.renderCreature(32, i * 64 + 32, &monsterList.at(i+monsterListScroller), false);
			monsterList.at(i+monsterListScroller).formattedName.setPosition(68,i * 64 + 52);
			App.draw(monsterList.at(i+monsterListScroller).formattedName);
		}
	}
}

void Game::showCurrentItem(sf::Vector2i pos)
{
	mouse_x = pos.x;
	mouse_y = pos.y;
	Item *item = dynamic_cast<Item*>(mouseHolding);
	Creature *creature = dynamic_cast<Creature*>(mouseHolding);
    if(((item && item->mID >= 1) || creature) && mouse_x > 128 && mouse_y > 24)
    {   
		for(int y = 24; y <= 24+(this->maxY*32); y+=32)
		for(int x = 128; x <= 128+(this->maxX*32); x+=32)
		{
			if(mouse_x > x && mouse_x <= x+32
			&& mouse_y > y && mouse_y <= y+32)
			{
				if(brushSize == 1 && item)
				{
				   System.renderItem(x, y, item, false);
				   rectCurrentItemOnMap.setSize(sf::Vector2f(float(32), float(32)));
				}   
				if(brushSize == 1 && creature)
				{
				   System.renderCreature(x, y, creature, false);
				   rectCurrentItemOnMap.setSize(sf::Vector2f(float(32), float(32)));
				}  
				if(brushSize == 2 && item)
				{
					for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						System.renderItem(x + i*32, y + j*32, item, false);    

					rectCurrentItemOnMap.setSize(sf::Vector2f(float(32*3), float(32*3)));
				}
				if(brushSize == 3 && item)
				{           
				   for (int i = -2; i <= 2; i++)
				   for (int j = -2; j <= 2; j++)
						System.renderItem(x + i*32, y + j*32, item, false);  

				   rectCurrentItemOnMap.setSize(sf::Vector2f(float(32*5), float(32*5)));
				}
				rectCurrentItemOnMap.setPosition(float(x+32-(brushSize*32)),float(y+32-(brushSize*32)));
				App.draw(rectCurrentItemOnMap);
			}
		}
    }    
}

void Game::loop()
{ 
	while(App.isOpen())
	{		
		sf::Event Event;
        while (App.pollEvent(Event))
        {
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			mouse_b = 1;
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
			mouse_b = 2;
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			mouse_b = 3;
			if (Event.type == Event.MouseButtonReleased)
			{
				mouse_b = 0;
				System.hold = false;
			}
			if (Event.type == Event.MouseMoved)
			{
				mouse_x = Event.mouseButton.x;
				mouse_y = Event.mouseButton.y;
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F))  
			{
				Map.save();
				CreaturesManager.saveSpawn();
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::L))
			{
				static bool setted = true;
				if(!setted)
				{
					App.setFramerateLimit(30);
					setted = true;
				}
				else
				{
					App.setFramerateLimit(0);
					setted = false;
				}
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::K))  
				this->isDrawShade = !this->isDrawShade;
			if (Event.type == Event.MouseWheelMoved && Event.mouseWheel.x > 0 && Event.mouseWheel.x < 128 && Event.mouseWheel.y > 0)
			{
				if(Event.mouseWheel.delta < 0 && isRenderMonsterList == false && itemListScroller < (itemList.size()-(App.getSize().y/64)))
				{
					this->itemListScroller++;
				}
				else if(Event.mouseWheel.delta > 0 && isRenderMonsterList == false && itemListScroller > 0)
				{
					this->itemListScroller--;
				}
				else if(Event.mouseWheel.delta < 0 && isRenderMonsterList == true && monsterListScroller < (monsterList.size()-(App.getSize().y/64)))
				{
					this->monsterListScroller++;
				}
				else if(Event.mouseWheel.delta > 0 && isRenderMonsterList == true && monsterListScroller > 0)
				{
					this->monsterListScroller--;
				}
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageUp))
			{
				if(isRenderMonsterList == false && itemListScroller > 0)  
					this->itemListScroller--;
				else if(isRenderMonsterList == true && monsterListScroller > 0)
					this->monsterListScroller--;
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageDown))
			{
				if(isRenderMonsterList == false && itemListScroller < (itemList.size()-(App.getSize().y/64))) 
					this->itemListScroller++;
				else if(isRenderMonsterList == true && monsterListScroller < (itemList.size()-(App.getSize().y/64)))
					this->monsterListScroller++;
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Right) && this->currentX < 600)
				this->currentX++;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Left) && this->currentX > 0)
				this->currentX--;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Up) && this->currentY > 0)
				this->currentY--;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Down) && this->currentY < 600)
				this->currentY++;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Z) && this->currentZ > 1)
				this->currentZ--;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::X) && this->currentZ < 14)
				this->currentZ++;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A) && this->brushSize > 1)
				this->brushSize--;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S) && this->brushSize < 3)
				this->brushSize++;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::R) && this->randomizeFactor < 10)
				this->randomizeFactor++;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::T) && this->randomizeFactor > 1)
				this->randomizeFactor--;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::M))
				this->isRenderMonsterList = !isRenderMonsterList;
	        if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::P))
			{
				if((sf::Mouse::getPosition(App).x > 128) && (sf::Mouse::getPosition(App).y > 24))
				{
					for(int y = 0; y <= this->maxY*32; y+=32)
					for(int x = 0; x <= this->maxX*32; x+=32)
					{
						if(mouse_x-128 > x && mouse_x-128 < x+32
						&& mouse_y-24 > y && mouse_y-24 < y+32)
						{ 
							Tile *tile = Map.getTile(this->currentX+x/32, this->currentY+y/32, this->currentZ);
							if(tile)
							{
								if(tile->type >= 2)
									tile->type = 0;
								else
									tile->type += 1;
							}
						}
					}
				}
			}
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num0 || Event.key.code == sf::Keyboard::Numpad0))
				this->itemListScroller = 1;
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num1 || Event.key.code == sf::Keyboard::Numpad1))
				this->itemListScroller = 101;
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num2 || Event.key.code == sf::Keyboard::Numpad2))
				this->itemListScroller = 201;
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num3 || Event.key.code == sf::Keyboard::Numpad3))
				this->itemListScroller = 301;
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Num4 || Event.key.code == sf::Keyboard::Numpad4))
				this->itemListScroller = 401;
			if((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Return))//ENTER
	        {  
	        }
			if((Event.type == sf::Event::MouseButtonPressed || System.hold) //wciœniêcie przycisku myszki na mapie
				&& (sf::Mouse::getPosition(App).x > 128) && (sf::Mouse::getPosition(App).y > 24) )
	        {
				#ifdef _DEBUG
					std::cout << "MB Pressed, Map." << std::endl;
				#endif

				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			       Map.mouse(1,sf::Mouse::getPosition(App).x-128,sf::Mouse::getPosition(App).y-24);
				if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
			       Map.mouse(2,sf::Mouse::getPosition(App).x-128,sf::Mouse::getPosition(App).y-24);
				if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			       Map.mouse(3,sf::Mouse::getPosition(App).x-128,sf::Mouse::getPosition(App).y-24);
	        } 
			if((Event.type == sf::Event::MouseButtonPressed) //wciœniêcie przycisku myszki na liœcie itemów
				&& (Event.mouseButton.x > 0) && (Event.mouseButton.x < 128) && (Event.mouseButton.y > 0))
	        {
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) )//&& !System.hold)
				{
				    System.hold = true;
					
					for(unsigned int x = 0; x < (App.getSize().x/32) + 1; x++)
					{
					   if(Event.mouseButton.y >= x*64 && Event.mouseButton.y < x*64 + 64)
					   {
						   if(this->isRenderMonsterList)
							   this->mouseHolding = &monsterList[x + this->monsterListScroller];
						   else
							   this->mouseHolding = &itemList[x + this->itemListScroller];
					   }
					}	

					#ifdef _DEBUG
						std::cout << "Item/Monster list" << std::endl;
					#endif
				}
	        } 
			if(Event.type == sf::Event::Resized)
			{
				sf::Vector2u size = App.getSize();
				if(size.y < 600)
				{
					size.y = 600;
					App.setSize(size);
				}
				if(size.x < 800)
				{
					size.x = 800;
					App.setSize(size);
				}
				this->maxX = (size.x-128)/32;
				this->maxY = (size.y-24)/32;
				//renderedMapTexture.create(size.x-128,size.y-24);
				//renderedMapTexture.setView(sf::View(sf::FloatRect(0,0,size.x-128,size.y-24)));
				//sf::View xx = renderedMapTexture.getView();
				App.create(sf::VideoMode(size.x, size.y,32),"Aldera Map Editor");
				App.setIcon(32, 32, System.icon->getPixelsPtr());
			}
			if(Event.type == sf::Event::Closed)
			{
				Map.save();
			    App.close();
			}
        }

		App.clear();
		renderedMapTexture.clear();
		Map.render();
		renderedMapTexture.display();

		if(isRenderMonsterList)
			renderMonsterList();
		else
			renderItemList();

		App.draw(renderedMap);
		showCurrentItem(sf::Mouse::getPosition(App));

		App.display();

		this->getFrameRate();
	}
}

void Game::addItem(unsigned short x, unsigned short y, unsigned char z, Item *item)
{
	if(this->randomizeFactor > 1)
	{
		if(item && item->mID == 2)
		{
			unsigned int randomizedNumber = rand()%10 + 1;
			if(randomizedNumber < randomizeFactor/3)
				item->mID = 4;
		}
		  ///////////////////////////////////////////////////////////////////////////////////
		 //................. randomizes itemID, make dynamic, not only static in c++ code///
		///////////////////////////////////////////////////////////////////////////////////
	}
	Tile* tile;
	tile = Map.getTile(x, y, z);
	if(item)
		tile->addThing(item);
}