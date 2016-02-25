#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <list>
#include "item.h"

typedef std::list<Item*> ItemList;

class Container : public Item
{
public:
	Container(unsigned int _type);
	virtual ~Container();

	virtual Container* getContainer() {return this;};
	virtual const Container* getContainer() const {return this;};

	unsigned int size() const {return itemList.size();};
	unsigned int capacity() const {return maxSize;};

	ItemList::const_iterator getItems() const {return itemList.begin();}
	ItemList::const_iterator getEnd() const {return itemList.end();}
	ItemList::const_reverse_iterator getReversedItems() const {return itemList.rbegin();}
	ItemList::const_reverse_iterator getReversedEnd() const {return itemList.rend();}

	void addItem(Item* item);
	Item* getItem(unsigned char index);
	Item* getItemId(unsigned int id, unsigned short count);
	bool isHoldingItem(Item* item);
	bool isHoldingItemId(unsigned int id, unsigned short count = 1);
	void eraseItem(unsigned char index);
	void eraseItem(Item *item);
	void eraseItemId(unsigned int id, unsigned short count = 1);
	unsigned char getItemIndex(Item *item);

	unsigned char getItemHoldingCount() const;
	unsigned int getWeight() const;

	ItemList itemList;
private:
	Container* getParentContainer();
	void updateItemWeight(double diff);
protected:
	//Container* parent;
	unsigned char maxSize;
	unsigned int totalWeight;
};

#endif