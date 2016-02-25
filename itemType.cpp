#include <string>
#include "itemType.h"
#include "enums.h"


ItemType::ItemType()
{
	miniMapColor          = 0;
	height                = 0;
	animcount             = 0;
	numsprites            = 0;
	spriteID              = 0;
	id                    = 0;
	group                 = ITEM_GROUP_NONE;
	name                  = "Unnamed Item";
	pluralName            = "";
	description           = "";
	maxItems              = 8;
	weight                = 1;
	showCount             = false;
	weaponType            = WEAPON_NONE;
	ammoType              = AMMO_NONE;
	shootType             = NM_SHOOT_NONE;
	magicEffect           = NM_ME_NONE;
	attack                = 0;
	defence               = 0;
	armor                 = 0;
	slotPosition          = 0;
	isVertical            = false;
	isHorizontal          = false;
	allowDistRead         = false;
	clientCharges         = false;
	speed                 = 0;
	decayTo               = -1;
	decayTime             = 0;
	stopTime              = false;

	canReadText           = false;
	canWriteText          = false;
	maxTextLen            = 255;

	stackable             = false;
	useable               = false;
	moveable              = false;
	alwaysOnTop           = false;
	alwaysOnTopOrder      = false;
	pickupable            = false;
	hasHeight             = false;
	rotable               = false;
	rotateTo              = 0;

	runeIntelligence      = 0;

	wieldInfo             = WIELDINFO_NONE;
	vocation              = VOCATION_NONE;
	minReqDex             = 0;
	minReqStr             = 0;
	minReqInt             = 0;
	minReqMPW             = 0;

	lightLevel            = 0;
	lightColor            = 0;

	floorChangeDown       = false;
	floorChangeNorth	  = false;
	floorChangeSouth	  = false;
	floorChangeEast		  = false;
	floorChangeWest		  = false;

	blockSolid			  = false;
	blockProjectile		  = false;
	blockPathFind		  = false;

	transformEquipTo	  = 0;
	transformDeEquipTo	  = 0;
	showCharges			  = false;
	charges				  = 0;
	shootRange			  = 1;
	ammoAction			  = AMMOACTION_NONE;
	combatType			  = COMBAT_NONE;
}
