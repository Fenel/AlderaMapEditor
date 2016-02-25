#ifndef ITEM_H
#define ITEM_H

#include "thing.h"
#include "enums.h"

class Container;
class ItemType;

struct ItemAbilities
{
	ItemAbilities();

	uint16_t uniqueid;
	uint16_t actionid;

	std::string text;
	std::string corpseOwner;

	uint8_t upgradeLevel;
	uint8_t resistance[10];

	CombatType elementType;
	uint8_t elementDamage;

	uint8_t addSkillDex;
	uint8_t addSkillStr;
	uint8_t addSkillInt;
	uint8_t addSkillMPW;
	uint8_t addSpeed;
	uint16_t addHealth;
	uint16_t addMana;

	uint8_t charges;

	uint16_t destPosX;
	uint16_t destPosY;
	uint8_t destPosZ;

	void parse(std::string &text);
	std::string serialize();
};

class Item : public Thing
{
 public:
  unsigned int mID;
  unsigned short count;
  ItemType *baseItem;
  ItemAbilities *abilities;

  virtual Item* getItem() {return this;};
  virtual const Item* getItem() const {return this;};
  virtual Container* getContainer() {return 0;};
  virtual const Container* getContainer() const {return 0;};

  bool isTeleport();
  bool isGroundTile();
  bool isSplash();
  bool isStackable();
  bool isRune();
  bool isFluidContainer();
  bool hasHeight();
  bool isAlwaysOnTop();
  bool isCollision();

  Item(std::string serializedText);
  Item(unsigned int id, unsigned short _count = 1);
  Item(unsigned int id, unsigned short _count, std::string textAbilities);
  Item(unsigned int id, unsigned short _count, ItemAbilities *refAbilities);
  ~Item();
  void randomize();
  std::string serialize();
  void parse(std::string text);
};




#endif
