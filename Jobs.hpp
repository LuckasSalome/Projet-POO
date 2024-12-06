#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"

class Creatures;

class Jobs {
public:
	virtual std::string getNameJob() = 0;
	virtual std::string getDescJob() = 0;
	virtual std::string getSpellName() = 0;
	virtual std::string jobSpell(std::shared_ptr<Entity> foe, std::map<std::string, int> selfStat) = 0;
	virtual std::map<std::string, int> getStatRequiredJob() = 0;
};