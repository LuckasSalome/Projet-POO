#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"


using namespace std;

class Race {
public :
	virtual string getNameRace() = 0;
	virtual string getDescRace() = 0;
	virtual string getSpellName() = 0;
	virtual string basicAttack(Creatures& foe, map<string, int> selfStat) = 0;
	virtual map<string, int> getStat() = 0;
	virtual map<string, int> raceSpell(Creatures& foe, map<string, int> selfStat) = 0;

};