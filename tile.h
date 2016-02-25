#ifndef __TILE_H__
#define __TILE_H__

#include <deque>
#include <string>
#include "item.h"
#include "creature.h"
#include "enums.h"

using namespace std;
typedef std::deque<Item*> ItemVector;
typedef std::deque<Creature*> CreatureVector;

class Tile : public Thing
{
public:
	Tile(Position _tilePos){pos.x = _tilePos.x; pos.y = _tilePos.y; pos.z = _tilePos.z; ground = NULL; offsetx = 0; offsety = 0; type = 0;};
	Tile(int Px, int Py, unsigned char Pz) {pos.x = Px; pos.y = Py, pos.z = Pz; ground = NULL; offsetx = 0; offsety = 0; type = 0;};
	Tile() { ground = NULL; offsetx = 0; offsety = 0; type = 0;};

    void addThing(Thing *thing);
    void transformThing(unsigned char stackpos, Thing *thing);
    bool removeThing(unsigned char stackpos);
	bool removeTopItem(unsigned short count = 1);
	bool removeTopThing();
    bool removeCreatureByID(unsigned int id);    
    Thing* getThing(unsigned char stackpos);
	Item* getTopItem();
    unsigned char getIndexOfThing(Thing* thing);
	Thing* getTopThing();
	void render(int startWidth, int startHeight, int camera_x, int camera_y, unsigned char step);
	std::string returnSaveString();

	bool isCollision();
    
    CreatureVector& getCreatures();

	Position pos;
	int offsetx, offsety;
	bool hasHeight;
	unsigned char type;
private:
	Item* ground;
	ItemVector topItems;
	ItemVector downItems;
	CreatureVector creatures;
};


#endif
