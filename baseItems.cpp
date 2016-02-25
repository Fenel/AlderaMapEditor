#include <iostream>
#include <vector>
#include <fstream>
#include <deque>
#include <string>
#include <time.h>

#include <SFML/Graphics.hpp>
extern sf::RenderWindow App;

#include "baseItems.h"
#include "itemType.h"

using namespace std;

ItemType* BaseItems::getItemType(unsigned int mID)
{
	return &items[mID];
}

BaseItems::BaseItems()
{
	itemsCount = 0;
	this->loadSprites();
	this->load();
}

void BaseItems::load()
{  
	#ifdef _DEBUG
		clock_t time_started = clock(); 
		std::cout << "::Loading itemData.txt...";
	#endif

	vector<std::string> lines;
	vector<std::string> elements;
	vector<std::string> names;
	vector<std::string> values;
	string tmp;

	std::ifstream file ("data/itemData.txt");
    if(file.is_open())
    {
       while(file)
       {
	      tmp.clear();
          getline(file, tmp,'\n');
		  if(tmp != "")
			lines.push_back(tmp);
       }   
       file.close(); 
	}
	#ifdef _DEBUG
		else
		{
			std::cout << "\n::Error while opening itemData.txt\n";
		}
	#endif

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
			//value.erase(name.find_first_of(";"));
			values.push_back(value);
		}

		items.push_back(ItemType());
		for(unsigned int i = 0; i < names.size(); i++)
		{
			if(names[i] == "miniMapColor")
				items.at(items.size()-1).miniMapColor = atoi(values[i].c_str());
			if(names[i] == "height")
				items.at(items.size()-1).height = atoi(values[i].c_str());
			if(names[i] == "animcount")
				items.at(items.size()-1).animcount = atoi(values[i].c_str());
			if(names[i] == "numsprites")
				items.at(items.size()-1).numsprites = atoi(values[i].c_str());
			if(names[i] == "spriteID")
				items.at(items.size()-1).spriteID = atoi(values[i].c_str());
			if(names[i] == "id")
				items.at(items.size()-1).id = atoi(values[i].c_str());
			if(names[i] == "group")
				items.at(items.size()-1).group = ItemGroup(atoi(values[i].c_str()));
			if(names[i] == "name")
				items.at(items.size()-1).name = values[i].c_str();
			if(names[i] == "pluralName")
				items.at(items.size()-1).pluralName = values[i].c_str();
			if(names[i] == "description")
				items.at(items.size()-1).description = values[i].c_str();
			if(names[i] == "maxItems")
				items.at(items.size()-1).maxItems = atoi(values[i].c_str());
			if(names[i] == "weight")
				items.at(items.size()-1).weight = atoi(values[i].c_str());
			if(names[i] == "showCount")
				items.at(items.size()-1).showCount = bool(atoi(values[i].c_str()));
			if(names[i] == "weaponType")
				items.at(items.size()-1).weaponType = WeaponType(atoi(values[i].c_str()));
			if(names[i] == "ammoType")
				items.at(items.size()-1).ammoType = AmmoType(atoi(values[i].c_str()));
			if(names[i] == "shootType")
				items.at(items.size()-1).shootType = ShootType(atoi(values[i].c_str()));
			if(names[i] == "magicEffect")
				items.at(items.size()-1).magicEffect = MagicEffectClasses(atoi(values[i].c_str()));
			if(names[i] == "attack")
				items.at(items.size()-1).attack = atoi(values[i].c_str());
			if(names[i] == "defence")
				items.at(items.size()-1).defence = atoi(values[i].c_str());
			if(names[i] == "armor")
				items.at(items.size()-1).armor = atoi(values[i].c_str());
			if(names[i] == "slotPosition")
				items.at(items.size()-1).slotPosition = atoi(values[i].c_str());
			if(names[i] == "isVertical")
				items.at(items.size()-1).isVertical = bool(atoi(values[i].c_str()));
			if(names[i] == "isHorizontal")
				items.at(items.size()-1).isHorizontal = bool(atoi(values[i].c_str()));
			if(names[i] == "allowDistRead")
				items.at(items.size()-1).allowDistRead = bool(atoi(values[i].c_str()));
			if(names[i] == "clientCharges ")
				items.at(items.size()-1).clientCharges  = bool(atoi(values[i].c_str()));
			if(names[i] == "speed")
				items.at(items.size()-1).speed = atoi(values[i].c_str());
			if(names[i] == "decayTo")
				items.at(items.size()-1).decayTo = atoi(values[i].c_str());
			if(names[i] == "decayTime")
				items.at(items.size()-1).decayTime = atoi(values[i].c_str());
			if(names[i] == "stopTime")
				items.at(items.size()-1).stopTime  = bool(atoi(values[i].c_str()));
			if(names[i] == "canReadText")
				items.at(items.size()-1).canReadText  = bool(atoi(values[i].c_str()));
			if(names[i] == "canWriteText")
				items.at(items.size()-1).canWriteText  = bool(atoi(values[i].c_str()));
			if(names[i] == "maxTextLen")
				items.at(items.size()-1).maxTextLen = atoi(values[i].c_str());
			if(names[i] == "stackable")
				items.at(items.size()-1).stackable = bool(atoi(values[i].c_str()));
			if(names[i] == "useable")
				items.at(items.size()-1).useable = bool(atoi(values[i].c_str()));
			if(names[i] == "moveable")
				items.at(items.size()-1).moveable = bool(atoi(values[i].c_str()));
			if(names[i] == "alwaysOnTop")
				items.at(items.size()-1).alwaysOnTop = bool(atoi(values[i].c_str()));
			if(names[i] == "alwaysOnTopOrder")
				items.at(items.size()-1).alwaysOnTopOrder = atoi(values[i].c_str());
			if(names[i] == "pickupable")
				items.at(items.size()-1).pickupable = bool(atoi(values[i].c_str()));
			if(names[i] == "hasHeight")
				items.at(items.size()-1).hasHeight = bool(atoi(values[i].c_str()));
			if(names[i] == "rotable")
				items.at(items.size()-1).rotable = bool(atoi(values[i].c_str()));
			if(names[i] == "rotateTo")
				items.at(items.size()-1).rotateTo = atoi(values[i].c_str());         
			if(names[i] == "runeIntelligence")
				items.at(items.size()-1).runeIntelligence = atoi(values[i].c_str());
			if(names[i] == "wieldInfo")
				items.at(items.size()-1).wieldInfo = atoi(values[i].c_str());
			if(names[i] == "vocation")
				items.at(items.size()-1).vocation = Vocation(atoi(values[i].c_str()));
			if(names[i] == "minReqDex")
				items.at(items.size()-1).minReqDex = atoi(values[i].c_str());
			if(names[i] == "minReqStr")
				items.at(items.size()-1).minReqStr = atoi(values[i].c_str());
			if(names[i] == "minReqInt")
				items.at(items.size()-1).minReqInt = atoi(values[i].c_str());
			if(names[i] == "minReqMPW")
				items.at(items.size()-1).minReqMPW = atoi(values[i].c_str());
			if(names[i] == "lightLevel")
				items.at(items.size()-1).lightLevel = atoi(values[i].c_str());
			if(names[i] == "lightColor")
				items.at(items.size()-1).lightColor = atoi(values[i].c_str());
			if(names[i] == "floorChangeDown")
				items.at(items.size()-1).floorChangeDown = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeNorth")
				items.at(items.size()-1).floorChangeNorth = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeSouth")
				items.at(items.size()-1).floorChangeSouth = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeEast")
				items.at(items.size()-1).floorChangeEast = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeWest")
				items.at(items.size()-1).floorChangeWest = bool(atoi(values[i].c_str()));
			if(names[i] == "blockSolid")
				items.at(items.size()-1).blockSolid = bool(atoi(values[i].c_str()));
			if(names[i] == "blockProjectile")
				items.at(items.size()-1).blockProjectile = bool(atoi(values[i].c_str()));
			if(names[i] == "blockPathFind")
				items.at(items.size()-1).blockPathFind = bool(atoi(values[i].c_str()));
			if(names[i] == "transformEquipTo")
				items.at(items.size()-1).transformEquipTo = atoi(values[i].c_str());
			if(names[i] == "transformDeEquipTo")
				items.at(items.size()-1).transformDeEquipTo = atoi(values[i].c_str());
			if(names[i] == "showCharges")
				items.at(items.size()-1).showCharges = bool(atoi(values[i].c_str()));
			if(names[i] == "charges")
				items.at(items.size()-1).charges = atoi(values[i].c_str());
			if(names[i] == "shootRange ")
				items.at(items.size()-1).shootRange  = atoi(values[i].c_str());
			if(names[i] == "ammoAction")
				items.at(items.size()-1).ammoAction = AmmoAction(atoi(values[i].c_str()));
			if(names[i] == "combatType")
				items.at(items.size()-1).combatType = CombatType(atoi(values[i].c_str()));
		}
		elements.clear();
		names.clear();
		values.clear();
	}
	#ifdef _DEBUG
		std::cout << " Done! ";
		std::cout << "Loaded " << items.size() << " items.";
		std::cout<<" ( " << clock() - time_started << " ms )\n";
	#endif	
}

void BaseItems::loadSprites()
{
	char tempChar[25]; 
	bool proceed = true;
	unsigned int image = 0;

	while(proceed)
	{
		sprintf(tempChar,"data/sprites/%d.bmp",image);

		this->images.push_back(sf::Image());
		if(this->images.at(this->images.size()-1).loadFromFile(tempChar))
		{
			this->images.at(this->images.size()-1).createMaskFromColor(sf::Color(255,0,255));

			this->textures.push_back(sf::Texture());
			this->textures.at(this->textures.size()-1).loadFromImage(this->images.at(this->images.size()-1));

			this->sprites.push_back(sf::Sprite());
			this->sprites.at(sprites.size()-1).setTexture(this->textures.at(this->textures.size()-1));
			this->sprites.at(sprites.size()-1).setPosition(20.0,20.0);
		}
		else
		{
			proceed = false;
		}
		++image;
	}
}
