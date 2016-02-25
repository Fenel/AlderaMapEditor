#ifndef __CREATURESMANAGER_H__
#define __CREATURESMANAGER_H__

#include <string>
#include <deque>
#include <SFML/Network.hpp>

#include "creature.h"

using namespace std;

class CreaturesManager
{
public:
	CreaturesManager();
	~CreaturesManager()
    {
    }
	bool loadCreature(string creatureName, bool reload, unsigned int id = 0);

	Creature* getCreature(unsigned int _id);
	unsigned int getCreaturesCount() { return creaturesList.size(); };
	unsigned int createCreature(string name, unsigned int posx, unsigned int posy, unsigned int posz, unsigned int respawn_time);
	bool removeCreature(unsigned int _id);

	void loadSpawn();
	void saveSpawn();
private:
	deque<Creature> creaturesList;
};




#endif