#include <sstream>
#include <deque>
#include "item.h"
#include "baseItems.h"

extern BaseItems BaseItems;
using namespace std;

ItemAbilities::ItemAbilities()
{
	uniqueid    = 0;
	actionid    = 0;

	text        = "";
	corpseOwner = "";

	upgradeLevel = 0;

	for(unsigned int i = 0; i < 10; i++)
	   resistance[i] = 0;

	elementType   = COMBAT_NONE;
	elementDamage = 0;

	addSkillDex = 0;
	addSkillStr = 0;
	addSkillInt = 0;
	addSkillMPW = 0;
	addSpeed    = 0;
	addHealth   = 0;
	addMana     = 0;

	charges     = 0;

	destPosX    = 0;
	destPosY    = 0;
	destPosZ    = 0;
}

void ItemAbilities::parse(std::string &text)
{    
	deque<std::string> elements;
	deque<std::string> names;
	deque<std::string> values;

	string element;
	while(text.find_first_of(";") != string::npos) //je¿eli linia zawiera ";"
	{
		element = text.substr(0,text.find_first_of(";")); //element =zbiór nazwa+wartoœæ
		text.erase(0,text.find_first_of(";")+2);

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
	for(unsigned int i = 0; i < names.size(); i++)
	{
		if(names[i] == "uniqueid")
			this->uniqueid = atoi(values[i].c_str());
		if(names[i] == "actionid")
			this->actionid = atoi(values[i].c_str());
		if(names[i] == "text")
			this->text = values[i].c_str();
		if(names[i] == "corpseOwner")
			this->corpseOwner = values[i].c_str();
		if(names[i] == "upgradeLevel")
			this->upgradeLevel = int(atoi(values[i].c_str()));
		if(names[i] == "resistancePhysical")
			this->resistance[0] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceFire")
			this->resistance[1] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceIce")
			this->resistance[2] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceEnergy")
			this->resistance[3] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceEarth")
			this->resistance[4] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceWater")
			this->resistance[5] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceHoly")
			this->resistance[6] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceDeath")
			this->resistance[7] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceLifeDrain")
			this->resistance[8] = int(atoi(values[i].c_str()));
		if(names[i] == "resistanceManaDrain")
			this->resistance[9] = int(atoi(values[i].c_str()));
		if(names[i] == "elementType")
			this->elementType = CombatType(atoi(values[i].c_str()));
		if(names[i] == "elementDamage")
			this->elementDamage = int(atoi(values[i].c_str()));
		if(names[i] == "addSkillDex")
			this->addSkillDex = int(atoi(values[i].c_str()));
		if(names[i] == "addSkillStr")
			this->addSkillStr = int(atoi(values[i].c_str()));
		if(names[i] == "addSkillInt")
			this->addSkillInt = int(atoi(values[i].c_str()));
		if(names[i] == "addSkillMPW")
			this->addSkillMPW = int(atoi(values[i].c_str()));
		if(names[i] == "addSpeed")
			this->addSpeed = int(atoi(values[i].c_str()));
		if(names[i] == "addHealth")
			this->addHealth = atoi(values[i].c_str());
		if(names[i] == "addMana")
			this->addMana = atoi(values[i].c_str());
		if(names[i] == "charges")
			this->charges = int(atoi(values[i].c_str()));
		if(names[i] == "destPosX")
			this->destPosX = atoi(values[i].c_str());
		if(names[i] == "destPosY")
			this->destPosY = atoi(values[i].c_str());
		if(names[i] == "destPosZ")
			this->destPosZ = int(atoi(values[i].c_str()));
	}
}

std::string ItemAbilities::serialize()
{
	std::stringstream file;

	if(this->uniqueid != 0)
		file<<"uniqueid="<<this->uniqueid<<"; ";
	if(this->actionid != 0)
		file<<"actionid="<<this->actionid<<"; ";
	if(this->text != "")
		file<<"text="<<this->text<<"; ";
	if(this->corpseOwner != "")
		file<<"corpseOwner="<<this->corpseOwner<<"; ";
	if(this->upgradeLevel != 0)
		file<<"upgradeLevel="<<int(this->upgradeLevel)<<"; ";
	if(this->resistance[0] != 0)
		file<<"resistancePhysical="<<int(this->resistance[0])<<"; ";
	if(this->resistance[1] != 0)
		file<<"resistanceFire="<<int(this->resistance[1])<<"; ";
	if(this->resistance[2] != 0)
		file<<"resistanceIce="<<int(this->resistance[2])<<"; ";
	if(this->resistance[3] != 0)
		file<<"resistanceEnergy="<<int(this->resistance[3])<<"; ";
	if(this->resistance[4] != 0)
		file<<"resistanceEarth="<<int(this->resistance[4])<<"; ";
	if(this->resistance[5] != 0)
		file<<"resistanceWater="<<int(this->resistance[5])<<"; ";
	if(this->resistance[6] != 0)
		file<<"resistanceHoly="<<int(this->resistance[6])<<"; ";
	if(this->resistance[7] != 0)
		file<<"resistanceDeath="<<int(this->resistance[7])<<"; ";
	if(this->resistance[8] != 0)
		file<<"resistanceLifeDrain="<<int(this->resistance[8])<<"; ";
	if(this->resistance[9] != 0)
		file<<"resistanceManaDrain="<<int(this->resistance[9])<<"; ";
	if(this->elementType != COMBAT_NONE)
		file<<"elementType="<<int(this->elementType)<<"; ";
	if(this->elementDamage != 0)
		file<<"elementDamage="<<int(this->elementDamage)<<"; ";
	if(this->addSkillDex != 0)
		file<<"addSkillDex="<<int(this->addSkillDex)<<"; ";
	if(this->addSkillStr != 0)
		file<<"addSkillStr="<<int(this->addSkillStr)<<"; ";
	if(this->addSkillInt != 0)
		file<<"addSkillInt="<<int(this->addSkillInt)<<"; ";
	if(this->addSkillMPW != 0)
		file<<"addSkillMPW="<<int(this->addSkillMPW)<<"; ";
	if(this->addSpeed != 0)
		file<<"addSpeed="<<int(this->addSpeed)<<"; ";
	if(this->addHealth != 0)
		file<<"addHealth="<<this->addHealth<<"; ";
	if(this->addMana != 0)
		file<<"addMana="<<this->addMana<<"; ";
	if(this->charges != 0)
		file<<"charges="<<int(this->charges)<<"; ";
	if(this->destPosX != 0)
		file<<"destPosX="<<this->destPosX<<"; ";
	if(this->destPosY != 0)
		file<<"destPosY="<<this->destPosY<<"; ";
	if(this->destPosZ != 0)
		file<<"destPosZ="<<int(this->destPosZ)<<"; ";

	return file.str();
}

Item::Item(std::string serializedText)
{
	this->abilities = NULL;
	this->parent = NULL;
	this->parse(serializedText);
}

Item::Item(unsigned int id, unsigned short _count)
{
    this->mID = id;
    this->baseItem = BaseItems.getItemType(id);
    this->count = _count;
	this->abilities = NULL;
	this->parent = NULL;
}

Item::Item(unsigned int id, unsigned short _count, std::string textAbilities)
{
    this->mID = id;
    this->baseItem = BaseItems.getItemType(id);
    this->count = _count;
	this->abilities = new ItemAbilities;
	this->abilities->parse(textAbilities);
	this->parent = NULL;
}

Item::Item(unsigned int id, unsigned short _count, ItemAbilities *refAbilities)
{
    this->mID = id;
    this->baseItem = BaseItems.getItemType(id);
    this->count = _count;
	this->abilities = refAbilities;
	this->parent = NULL;
}

Item::~Item()
{

}

std::string Item::serialize()
{
	std::stringstream file;
	file << this->mID << "." << this->count;
	if(abilities)
		file << "`" << this->abilities->serialize();

	return file.str();
}

void Item::parse(std::string text)
{
	std::string token, charek;
	if(text.find("`") != string::npos)
	{
		for(unsigned int n = 0; n < text.length(); n++)
		{
			charek = text.at(n);
			if(charek != "|" && charek != "." && charek != "!")
			{
				token += charek;
			}
			if(charek == ".")
			{
				this->mID = atoi(token.c_str());
				this->baseItem = BaseItems.getItemType(this->mID);
				token.clear();
			}
			if(charek == "`")
			{
				this->count = atoi(token.c_str());
				token.clear();

				token = text;
				token.erase(0, n);
				this->abilities = new ItemAbilities;
				this->abilities->parse(token);
				break;
			}  
		}
	}
	else
	{
		for(unsigned int n = 0; n < text.length(); n++)
		{
			charek = text.at(n);
			if(charek != "|" && charek != ".")
			{
				token += charek;
			}
			if(charek == ".")
			{
				this->mID = atoi(token.c_str());
				this->baseItem = BaseItems.getItemType(this->mID);
				token.clear();
				if(text.find("|") == string::npos)
				{
					text.erase(0, n+1);
					this->count = atoi(text.c_str());
				}
			}
			if(charek == "|")
			{
				this->count = atoi(token.c_str());
				token.clear();
				break;
			}  
		}
	}
}

/*
void Item::setItemCountOrSubType(unsigned char n)
{
    {
        count = n;
        if(count == 1)
            subType = 0;
        else if (count == 2)
            subType = 1;
        else if (count == 3)
            subType = 2;
        else if (count == 4)
            subType = 3;
        else if (count > 4 && count < 10)
            subType = 4;
        else if (count > 10 && count < 25)
            subType = 5;
        else if (count > 24 && count < 50)
            subType = 6;
        else
            subType = 7;
    }
}
*/

bool Item::isTeleport()
{
    return (baseItem && baseItem->group == ITEM_GROUP_TELEPORT);
}

bool Item::isGroundTile()
{
    return (baseItem && baseItem->group == ITEM_GROUP_GROUND);
}

bool Item::isSplash()
{
    return (baseItem && baseItem->group == ITEM_GROUP_SPLASH);
}

bool Item::hasHeight()
{
    return (baseItem && baseItem->hasHeight);
}

bool Item::isStackable()
{
    return (baseItem && baseItem->stackable);
}

bool Item::isRune()
{
    return (baseItem && baseItem->group == ITEM_GROUP_RUNE);
}

bool Item::isFluidContainer()
{
    return (baseItem && baseItem->group == ITEM_GROUP_FLUID);
}

bool Item::isAlwaysOnTop()
{
    return (baseItem && baseItem->alwaysOnTop);
}

bool Item::isCollision()
{
     return (baseItem && baseItem->blockSolid);
}

uint32_t random(uint32_t min,uint32_t max)
{
	uint32_t chance = rand() % (max-min) + min;
	if(chance <= max)
	{
		return chance;
	}
	else
	{
		return random(min, max);
	}
}

void Item::randomize()
{
	if(this->count > 1)
		this->count = char(random(1,this->count));
	if(abilities)
	{
		if(this->abilities->upgradeLevel != 0)
			this->abilities->upgradeLevel = char(random(1,this->abilities->upgradeLevel));
		if(this->abilities->resistance[0] != 0)
			this->abilities->resistance[0] = char(random(1,this->abilities->resistance[0]));
		if(this->abilities->resistance[1] != 0)
			this->abilities->resistance[1] = char(random(1,this->abilities->resistance[1]));
		if(this->abilities->resistance[2] != 0)
			this->abilities->resistance[2] = char(random(1,this->abilities->resistance[2]));
		if(this->abilities->resistance[3] != 0)
			this->abilities->resistance[3] = char(random(1,this->abilities->resistance[3]));
		if(this->abilities->resistance[4] != 0)
			this->abilities->resistance[4] = char(random(1,this->abilities->resistance[4]));
		if(this->abilities->resistance[5] != 0)
			this->abilities->resistance[5] = char(random(1,this->abilities->resistance[5]));
		if(this->abilities->resistance[6] != 0)
			this->abilities->resistance[6] = char(random(1,this->abilities->resistance[6]));
		if(this->abilities->resistance[7] != 0)
			this->abilities->resistance[7] = char(random(1,this->abilities->resistance[7]));
		if(this->abilities->resistance[8] != 0)
			this->abilities->resistance[8] = char(random(1,this->abilities->resistance[8]));
		if(this->abilities->resistance[9] != 0)
			this->abilities->resistance[9] = char(random(1,this->abilities->resistance[9]));
		if(this->abilities->elementDamage != 0)
			this->abilities->elementDamage = char(random(1,this->abilities->elementDamage));
		if(this->abilities->addSkillDex != 0)
			this->abilities->addSkillDex = char(random(1,this->abilities->addSkillDex));
		if(this->abilities->addSkillStr != 0)
			this->abilities->addSkillStr = char(random(1,this->abilities->addSkillStr));
		if(this->abilities->addSkillInt != 0)
			this->abilities->addSkillInt = char(random(1,this->abilities->addSkillInt));
		if(this->abilities->addSkillMPW != 0)
			this->abilities->addSkillMPW = char(random(1,this->abilities->addSkillMPW));
		if(this->abilities->addSpeed != 0)
			this->abilities->addSpeed = char(random(1,this->abilities->addSpeed));
		if(this->abilities->addHealth != 0)
			this->abilities->addHealth = random(1,this->abilities->addHealth);
		if(this->abilities->addMana != 0)
			this->abilities->addMana = random(1,this->abilities->addMana);
		if(this->abilities->charges != 0)
			this->abilities->charges = uint8_t(random(1,this->abilities->charges));
	}
}