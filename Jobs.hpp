#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"

using namespace std;

class Jobs {
public:
	virtual string getNameJob() = 0;
	virtual string getDescJob() = 0;
	virtual string getSpellName() = 0;
	virtual string jobSpell(Creatures& foe, map<string, int> selfStat) = 0;
	virtual map<string, int> getStatRequiredJob() = 0;
};