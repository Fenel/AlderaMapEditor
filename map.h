#ifndef __MAP_H__
#define __MAP_H__

#include "tile.h"


typedef std::deque<Creature*> CreatureVector;

class Map
{
public:    
	Map();
	~Map(){};
    
	bool deleteTopThingOnTile(unsigned int x, unsigned int y, unsigned char z);
    
    unsigned int posToIndex(unsigned int x, unsigned int y, unsigned char z);
    void indexToPos(unsigned int &x, unsigned int &y, unsigned char &z, unsigned int index);

    void setTile(Position pos, Tile *tile);
	void setTile(unsigned short x, unsigned short y, unsigned char z, Tile *tile);
    
    Tile *getTile(Position pos);
	Tile *getTile(unsigned short x, unsigned short y, unsigned char z);
	
	//sf::Packet returnTileItemsPacket(unsigned short x, unsigned short y, unsigned char z);

	void render();
	void mouse(unsigned char type, int x, int y);
	void removeCreatureFromTiles(unsigned int cid);
	int posx, posy;

    void load();
	void save();
private:
    Tile *tiles_tab[6144000];
};

#endif
