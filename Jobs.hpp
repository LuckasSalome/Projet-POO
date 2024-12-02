#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"
#include "Heroes.hpp"

using namespace std;

class Jobs {
public:
	virtual string getNameJob() = 0;
	virtual string getDescJob() = 0;
	virtual map<string, int> getStatRequiredJob() = 0;
	virtual string jobSpell(Creatures& foe, Heroes& self) = 0;
	virtual string jobSpell(Creatures& foe1, Creatures& foe2, Heroes& self ) = 0;
	virtual string jobSpell(Creatures& foe1, Creatures& foe2, Creatures& foe3, Heroes& self ) = 0;
	virtual string jobSpell(Creatures& foe1, Creatures& foe2, Creatures& foe3, Creatures& foe4, Heroes& self) = 0;
};