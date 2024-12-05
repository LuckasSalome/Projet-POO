#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"

class Creatures;

using namespace std;

class Race {
public :
	virtual string getNameRace() = 0;
	virtual string getDescRace() = 0;
	virtual string getSpellName() = 0;
	virtual void basicAttack(Entity& foe, map<string, int> selfStat) = 0;
	virtual map<string, int> getStat() = 0;
	virtual map<string, int> raceSpell(Entity& foe, map<string, int> selfStat) = 0;

};