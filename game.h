#ifndef __GAME__H
#define __GAME__H

#include <SFML/Network.hpp>
#include <deque>
#include "tile.h"

class Thing;

extern int mouse_x, mouse_y, mouse_b;

class Game
{
public:
  Game();
  ~Game(){	};
  void loadLooktypes();
  void loadItemList();
  void loadMonsterList();
  void renderItemList();
  void renderMonsterList();
  void showCurrentItem(sf::Vector2i pos);
  unsigned int getFrameRate();
  void loop();  

  void addItem(unsigned short x, unsigned short y, unsigned char z, Item *item);

  std::deque<Looktype>looktypes;
  std::deque<Item>itemList;
  std::deque<Creature>monsterList;
  unsigned int currentX, currentMouseX;
  unsigned int currentY, currentMouseY;
  unsigned char currentZ;
  unsigned int currentScale;
  unsigned char brushSize;
  unsigned int maxX;
  unsigned int maxY;
  unsigned int lastTileX;
  unsigned int lastTileY;

  unsigned int randomizeFactor;

  unsigned int itemListScroller;
  unsigned int monsterListScroller;
  Thing *mouseHolding;
  sf::RectangleShape rectFloorShade;
  bool isDrawShade;
  bool isRenderMonsterList;
private:  
  sf::Sprite renderedMap;
  sf::RectangleShape rectItemList1;
  sf::RectangleShape rectItemList2;
  sf::RectangleShape rectCurrentItem;
  sf::RectangleShape rectCurrentItemOnMap;
  sf::Text itemNumber;
};


#endif

