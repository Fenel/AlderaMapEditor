#ifndef __BASEITEMS_H__
#define __BASEITEMS_H__

#include <deque>
#include "itemType.h"
#include "enums.h"


class BaseItems
{
public:
	BaseItems();
	~BaseItems()
    {
    }
	void load();
	void loadSprites();
	sf::Sprite* getSprite(unsigned int id){return &sprites.at(id);};
	sf::Texture* getTexture(unsigned int id){return &textures.at(id);};
	unsigned int getItemsCount(){return items.size();};
	ItemType* getItemType(unsigned int mID);
private:
    int itemsCount;
	std::deque<ItemType> items;
	std::deque<sf::Image> images;
	std::deque<sf::Texture> textures;
    std::deque<sf::Sprite> sprites;
};
    
#endif
