#pragma once

#include <string>
#include <map>
#include "Heroes.hpp"

class Heroes; // Déclaration avancée

class Common {
public:
    virtual std::string getName() = 0;
    virtual std::string getDesc() = 0;
    virtual std::string getSpellName() = 0;
    virtual std::string basicAttack(Heroes& ennemy, std::map<std::string, int> creatureStat) = 0;
    virtual std::map<std::string, int> getStat() = 0;
    virtual std::map<std::string, int> monsterSpell(Heroes& ennemy, std::map<std::string, int> creatureStat) = 0;
};
