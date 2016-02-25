#ifndef _ENUMS_H
#define _ENUMS_H

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

struct KeyStorage
{
	//sf::Keyboard::Key code;
	bool alt;
	bool control;
	bool shift;
	bool used;
	unsigned int unicode;
};

struct Looktype
{
	unsigned int id;
	unsigned char type;
	std::string name;
	unsigned int north, south, west, east;
};

typedef signed long long int64_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned char uint8_t;
typedef signed char int8_t;

#define SLOTP_NONE 0        //special
#define SLOTP_LEARRING 1    //1
#define SLOTP_HEAD 2        //2
#define SLOTP_REARRING 4    //3
#define	SLOTP_NECKLACE 8    //4
#define	SLOTP_ARMOR 16      //5
#define	SLOTP_BACKPACK 32   //6
#define	SLOTP_WEAPON 64     //7
#define	SLOTP_BELT 128      //8
#define	SLOTP_SHIELD 256    //9
#define	SLOTP_LRING 512     //10
#define	SLOTP_LEGS 1024     //11
#define	SLOTP_RRING 2048    //12
#define	SLOTP_GLOVES 4096   //13
#define	SLOTP_BOOTS 8192    //14
#define	SLOTP_ARROWS 16384  //15
#define	SLOTP_TWOHAND 32768 //special

#define TILETYPE_NONE     0
#define TILETYPE_PZ       1
#define TILETYPE_HOUSE    2

#define TILE_TELEPORT                2
#define TILE_FLOOR_CHANGE_DOWN       3
#define TILE_FLOOR_CHANGE_DOWN_NORTH 4
#define TILE_FLOOR_CHANGE_DOWN_SOUTH 5
#define	TILE_FLOOR_CHANGE_DOWN_EAST  6
#define	TILE_FLOOR_CHANGE_DOWN_WEST  7
#define	TILE_FLOOR_CHANGE_NORTH		 8
#define	TILE_FLOOR_CHANGE_SOUTH		 9
#define	TILE_FLOOR_CHANGE_EAST		 10
#define	TILE_FLOOR_CHANGE_WEST		 11

class Game;

enum MagicEffectClasses {
	NM_ME_DRAW_BLOOD       = 1,
	NM_ME_PUFF             = 2,
	NM_ME_BLOCKHIT         = 3,
	NM_ME_FIRE			   = 4,
	NM_ME_ICE	           = 5,
	NM_ME_ENERGY	       = 6,
	NM_ME_EARTH			   = 7,
	NM_ME_WATER			   = 8,
	NM_ME_HOLY	           = 9,
	NM_ME_DEATH			   = 10,
	NM_ME_TELEPORT         = 11,
	NM_ME_STUN             = 12,
	NM_ME_NONE             = 0
};

enum ShootType
{
	NM_SHOOT_BOLT           = 1,
	NM_SHOOT_ARROW          = 2,
	NM_SHOOT_FIRE           = 3,
	NM_SHOOT_ICE            = 4,
	NM_SHOOT_ENERGY         = 5,
	NM_SHOOT_EARTH          = 6, 
	NM_SHOOT_WATER          = 7, 
	NM_SHOOT_HOLY           = 8,
	NM_SHOOT_DEATH          = 9,
	NM_SHOOT_POISONARROW    = 10,
	NM_SHOOT_BURSTARROW     = 11,
	NM_SHOOT_STONE          = 12,
	NM_SHOOT_POWERBOLT      = 13,
	NM_SHOOT_POWERARROW     = 14,
	NM_SHOOT_WHIRLWINDSWORD = 15,
	NM_SHOOT_WHIRLWINDAXE	= 16,
	NM_SHOOT_WHIRLWINDCLUB	= 17,
	NM_SHOOT_NONE           = 0
};

enum AmmoType
{
	AMMO_NONE           = 0,
	AMMO_BOLT           = 1,
	AMMO_ARROW          = 2,
	AMMO_STONE          = 3
};

enum AmmoAction
{
	AMMOACTION_NONE = 0,
	AMMOACTION_REMOVECOUNT = 1,
	AMMOACTION_REMOVECHARGE = 2
};

enum CombatType 
{
	COMBAT_NONE             = 0,
	COMBAT_PHYSICALDAMAGE	= 1,
	COMBAT_FIREDAMAGE		= 2,
	COMBAT_ICEDAMAGE        = 4,
	COMBAT_ENERGYDAMAGE		= 8,
	COMBAT_EARTHDAMAGE		= 16,
	COMBAT_WATERDAMAGE		= 32,
	COMBAT_HOLYDAMAGE       = 64,
	COMBAT_DEATHDAMAGE      = 128,
	COMBAT_LIFEDRAIN		= 256,
	COMBAT_MANADRAIN		= 512,
	COMBAT_HEALING			= 1024,
};

enum RaceType
{
	RACE_NONE   = 0,
	RACE_BLOOD	= 1,
	RACE_UNDEAD	= 2,
	RACE_FIRE	= 3,
	RACE_ENERGY	= 4,
	RACE_WATER  = 5,
};

enum BlockType 
{
	BLOCK_NONE = 0,
	BLOCK_DEFENSE = 1,
	BLOCK_ARMOR = 2,
	BLOCK_IMMUNITY = 3
};

enum Vocation 
{
	VOCATION_NONE = 0,
	VOCATION_WARRIOR = 1,
	VOCATION_ROGUE = 2,
	VOCATION_MAGE = 4,
	VOCATION_PRIEST = 8
};

enum Playersex
{
	PLAYERSEX_MALE = 0,
	PLAYERSEX_FEMALE = 1
};

enum ItemGroup{
	ITEM_GROUP_NONE = 0,
	ITEM_GROUP_GROUND = 1,
	ITEM_GROUP_CONTAINER = 2,
	ITEM_GROUP_WEAPON = 3,
	ITEM_GROUP_AMMUNITION = 4,
	ITEM_GROUP_ARMOR = 5,
	ITEM_GROUP_RUNE = 6,
	ITEM_GROUP_TELEPORT = 7,
	ITEM_GROUP_MAGICFIELD = 8,
	ITEM_GROUP_WRITEABLE = 9,
	ITEM_GROUP_KEY = 10,
	ITEM_GROUP_SPLASH = 11,
	ITEM_GROUP_FLUID = 12,
	ITEM_GROUP_DOOR = 13,
	ITEM_GROUP_LAST = 14
};

enum WeaponType
{
	WEAPON_NONE = 0,
	WEAPON_SWORD = 1,
	WEAPON_CLUB = 2,
	WEAPON_AXE = 3,
	WEAPON_SHIELD = 4,
	WEAPON_DIST = 5,
	WEAPON_STAFF = 6,
	WEAPON_DAGGER = 6,
	WEAPON_AMMO = 7
};

enum WieldInfo{
	WIELDINFO_NONE     = 1,
	WIELDINFO_DEX     = 1,
	WIELDINFO_STR     = 2,
	WIELDINFO_INT     = 4,
	WIELDINFO_MPW     = 8,
};

struct Position
{
    unsigned int x;
    unsigned int y;
    unsigned char z;
};

struct SpriteProperties
{
    unsigned int id;
    unsigned int graphicId;
    unsigned char type;
};

#endif
