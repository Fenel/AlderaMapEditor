#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SFML/Graphics.hpp>
#include "enums.h"
                                                     
class ItemType
{
public:
	ItemType();
	~ItemType(){}

	uint16_t	   miniMapColor;
    uint8_t		   height;
	uint8_t		   animcount;
	uint8_t		   numsprites;
    uint16_t	   spriteID;
	uint16_t       id;
    ItemGroup      group;
	std::string    name;
	std::string    pluralName;
	std::string    description;
	uint16_t       maxItems;
	uint16_t       weight;
	bool           showCount;
	WeaponType     weaponType;
	AmmoType       ammoType;
	ShootType      shootType;
	MagicEffectClasses magicEffect;
	uint16_t	   attack;
	uint16_t       defence;
	uint16_t       armor;
	uint16_t	   slotPosition;
	bool           isVertical;
	bool           isHorizontal;
	bool           allowDistRead;
	bool           clientCharges;
	uint16_t       speed;
	int32_t        decayTo;
	uint32_t       decayTime;
	bool		   stopTime;

	bool           canReadText;
	bool           canWriteText;
	uint16_t       maxTextLen;

	bool           stackable;
	bool           useable;
	bool           moveable;
	bool           alwaysOnTop;
	int8_t         alwaysOnTopOrder;
	bool           pickupable;
	bool		   hasHeight;
	bool           rotable;
	int32_t        rotateTo;

	int32_t        runeIntelligence;

	uint32_t       wieldInfo;
	Vocation       vocation;
	uint32_t       minReqDex;
	uint32_t       minReqStr;
	uint32_t       minReqInt;
	uint32_t       minReqMPW;

	int32_t        lightLevel;
	int32_t        lightColor;

	bool 		   floorChangeDown;
	bool 		   floorChangeNorth;
	bool 		   floorChangeSouth;
	bool 		   floorChangeEast;
	bool 		   floorChangeWest;

	bool		   blockSolid;
	bool		   blockProjectile;
	bool		   blockPathFind;

	uint32_t	   transformEquipTo;
	uint32_t	   transformDeEquipTo;
	bool		   showCharges;
	uint32_t	   charges;
	uint16_t	   shootRange;
	AmmoAction	   ammoAction;
	CombatType     combatType;

	bool isAlwaysOnTop() const {return alwaysOnTop;}

	bool isGroundTile() const {return (group == ITEM_GROUP_GROUND);}
	bool isContainer() const {return (group == ITEM_GROUP_CONTAINER);}
	bool isSplash() const {return (group == ITEM_GROUP_SPLASH);}
	bool isFluidContainer() const {return (group == ITEM_GROUP_FLUID);}

	bool isDoor() const {return( group == ITEM_GROUP_DOOR);}
	bool isMagicField() const {return ( group == ITEM_GROUP_MAGICFIELD);}
	bool isTeleport() const {return ( group == ITEM_GROUP_TELEPORT);}
	bool isKey() const {return ( group == ITEM_GROUP_KEY);}
	bool hasSubType() const {return ( stackable || charges != 0);}
	bool isRune() const {return (group == ITEM_GROUP_RUNE);}
};



#endif
