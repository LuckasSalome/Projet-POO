#pragma once

#include "Heroes.hpp"
#include <string>
#include <map>

class Heroes; // Déclaration avancée

class Common {
public:
    virtual std::string getName() = 0;
    virtual std::string getDesc() = 0;
    virtual std::string getSpellName() = 0;
    virtual void basicAttack(Heroes& ennemy, std::map<std::string, int> creatureStat) = 0;
    virtual std::map<std::string, int> getStat() = 0;
    virtual std::map<std::string, int> monsterSpell(Heroes& ennemy, std::map<std::string, int> creatureStat) = 0;
};
