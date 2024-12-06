#pragma once

#include "Heroes.hpp"
#include <string>
#include <map>

class Heroes; // Déclaration avancée

class Boss {
public:
	virtual std::string getBossName() = 0;
	virtual std::string getBossDesc() = 0;
	virtual std::string getSpellName1(bool midlife) = 0;
	virtual std::string getSpellName2(bool midlife) = 0;
	virtual std::map<std::string, int> getBossStat() = 0;
	virtual std::map<std::string, int> bossSpell1(std::shared_ptr<Entity> ennemy, std::map<std::string, int> creatureStat, bool midlife) = 0;
	virtual std::map<std::string, int> bossSpell2(std::shared_ptr<Entity> ennemy, std::map<std::string, int> creatureStat, bool midlife) = 0;
};