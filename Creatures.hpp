#pragma once

#include <string>
#include <map>
#include "Entity.hpp"
#include "Common.hpp"
#include "Boss.hpp"

class Creatures : public Entity{
private:
    std::string creatureName;
    std::string creatureDesc;
    std::map<std::string, int> creatureStat;
    bool isAlive = true;
    bool cond = false;

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

    std::string initBossName(Boss& mob) {
        this->creatureName = mob.getBossName();
        return this->creatureName;
    }

    std::string initBossDesc(Boss& mob) {
        this->creatureDesc = mob.getBossDesc();
        return this->creatureDesc;
    }

    std::map<std::string, int> initBossStat(Boss& mob) {
        this->creatureStat = mob.getBossStat();
        return this->creatureStat;
    }

    // Getters
    std::string getName() override {
        return this->creatureName;
    }

    std::string getDesc() override {
        return this->creatureDesc;
    }

    std::map<std::string, int> getStat() override {
        return this->creatureStat;
    }

    bool getAlive()  override {
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
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBasicAttack(Common& mob, Heroes& ennemy) const {
        if (isAlive) {
            mob.basicAttack(ennemy, this->creatureStat);
            return "Attaque Basique";
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBossSpell1(Boss& mob, Heroes& ennemy) {
        if (isAlive) {
            if (getStat()["HP"] <= 50)
                this->cond = true;
            mob.bossSpell1(ennemy, this->creatureStat, cond);
            return mob.getSpellName1(cond);
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBossSpell2(Boss& mob, Heroes& ennemy) {
        if (isAlive) {
            if (getStat()["HP"] <= 50)
                this->cond = true;
            mob.bossSpell2(ennemy, this->creatureStat, cond);
            return mob.getSpellName2(cond);
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }


    bool isCreatureAlive() {
        if (this->creatureStat["HP"] <= 0)
            isAlive = false;
        return this->isAlive;
    }
};
