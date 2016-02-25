#ifndef CSYSTEM_H
#define CSYSTEM_H

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

class Item;
class Creature;

class System
{
public:  
  System(unsigned int _width, unsigned int _height, unsigned int _res);
  ~System();
  void renderItem(int x, int y, Item *item, bool mapTexture = false);
  void renderCreature(int x, int y, Creature *creature, bool mapTexture = false);
  void renderCreatureName(int x, int y, Creature *creature, bool mapTexture = false);
  void renderShade(int x, int y, unsigned char type);

  unsigned int gameState;
  unsigned int windowWidth, windowHeight, res;
  unsigned int activeTextbox;
  unsigned int globalTextboxesCount;
  bool keyProcessed;

  bool hold;
  bool welcome;
  bool connected;
  int modiferX, modiferY;
  clock_t animationCounter;
  unsigned char getAnimationFrame();

  sf::Font font;

  sf::RectangleShape pzRect;
  sf::RectangleShape houseRect;

  sf::Image *icon;
private:
};



#endif
