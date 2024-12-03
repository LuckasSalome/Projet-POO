#pragma once

#include <string>
#include <map>
#include "Common.hpp"

class Creatures {
private:
    std::string creatureName;
    std::string creatureDesc;
    std::map<std::string, int> creatureStat;
    bool isAlive = true;

public:
    std::string initCreatureName(Common& mob) {
        this->creatureName = mob.getName();
        return this->creatureName;
    }

    std::string initCreatureDesc(Common& mob) {
        this->creatureDesc = mob.getDesc();
        return this->creatureDesc;
    }

    std::map<std::string, int> initCreatureStat(Common& mob) {
        this->creatureStat = mob.getStat();
        return this->creatureStat;
    }

    // Getters
    std::string getCreatureName() {
        return this->creatureName;
    }

    std::string getCreatureDesc() {
        return this->creatureDesc;
    }

    std::map<std::string, int> getCreatureStat() {
        return this->creatureStat;
    }

    bool getCreatureAlive() const {
        return this->isAlive;
    }

    // Setters
    void setCreatureHealth(int set) {
        this->creatureStat["HP"] = set;
    }

    void setCreatureCourage(int set) {
        this->creatureStat["COU"] = set;
    }

    void setCreatureStrengh(int set) {
        this->creatureStat["FO"] = set;
    }

    void setCreatureIntelligence(int set) {
        this->creatureStat["INT"] = set;
    }

    void setCreatureDexterity(int set) {
        this->creatureStat["AD"] = set;
    }

    void setCreatureCharism(int set) {
        this->creatureStat["CHA"] = set;
    }

    std::string getMonsterSpell(Common& mob, Heroes& ennemy) {
        if (isAlive) {
            std::map<std::string, int> result = mob.monsterSpell(ennemy, this->creatureStat);
            if (result["HP"] != this->creatureStat["HP"])
                this->setCreatureHealth(result["HP"]);
            return mob.getSpellName();
        }
        return "";
    }

    std::string getBasicAttack(Common& mob, Heroes& ennemy) const {
        if (isAlive) {
            mob.basicAttack(ennemy, this->creatureStat);
            return "Attaque Basique";
        }
        return "";
    }


    bool isCreatureAlive() {
        if (this->creatureStat["HP"] <= 0)
            isAlive = false;
        return this->isAlive;
    }
};
