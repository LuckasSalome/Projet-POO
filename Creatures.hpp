#pragma once

#include <string>
#include <map>
#include "Entity.hpp"
#include "Common.hpp"
#include "Boss.hpp"

class Entity;

class Creatures : public Entity {
private:
    std::string creatureName;
    std::string creatureDesc;
    std::map<std::string, int> creatureStat;
    bool isAlive = true;
    bool cond = false;
    bool isBoss = false;

public:
    std::string initCreatureName(Common& mob) override {
        this->creatureName = mob.getName();
        return this->creatureName;
    }

    std::string initCreatureDesc(Common& mob) override {
        this->creatureDesc = mob.getDesc();
        return this->creatureDesc;
    }

    std::map<std::string, int> initCreatureStat(Common& mob) override {
        this->creatureStat = mob.getStat();
        return this->creatureStat;
    }

    std::string initBossName(Boss& mob) override {
        this->creatureName = mob.getBossName();
        return this->creatureName;
    }

    std::string initBossDesc(Boss& mob) override {
        this->creatureDesc = mob.getBossDesc();
        return this->creatureDesc;
    }

    std::map<std::string, int> initBossStat(Boss& mob) override {
        this->isBoss = true;
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

    bool getIsBoss() override {
        return this->isBoss;
    }

    // Setters
    void setHealth(int set) override {
        this->creatureStat["HP"] = set;
        if (this->creatureStat["HP"] <= 0) {
            cout << "hihi" << endl;
            isAlive = false;
        }
    }

    void setCourage(int set) override {
        this->creatureStat["COU"] = set;
    }

    void setStrengh(int set) override {
        this->creatureStat["FO"] = set;
    }

    void setIntelligence(int set) override {
        this->creatureStat["INT"] = set;
    }

    void setDexterity(int set) override {
        this->creatureStat["AD"] = set;
    }

    void setCharism(int set) override {
        this->creatureStat["CHA"] = set;
    }

    std::string getMonsterSpell(Common& mob, std::shared_ptr<Entity> ennemy) override {
        if (isAlive) {
            std::map<std::string, int> result = mob.monsterSpell(ennemy, this->creatureStat);
            if (result["HP"] != this->creatureStat["HP"])
                this->setHealth(result["HP"]);
            return mob.getSpellName();
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBasicAttack(Common& mob, std::shared_ptr<Entity> ennemy) override {
        if (isAlive) {
            mob.basicAttack(ennemy, this->creatureStat);
            return "Attaque Basique";
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBossSpell1(Boss& mob, std::shared_ptr<Entity> ennemy) override {
        if (isAlive) {
            if (getStat()["HP"] <= 50)
                this->cond = true;
            mob.bossSpell1(ennemy, this->creatureStat, cond);
            return mob.getSpellName1(cond);
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    std::string getBossSpell2(Boss& mob, std::shared_ptr<Entity> ennemy) override {
        if (isAlive) {
            if (getStat()["HP"] <= 50)
                this->cond = true;
            mob.bossSpell2(ennemy, this->creatureStat, cond);
            return mob.getSpellName2(cond);
        }
        return "Impossible, " + this->creatureName + " est Mort(e).";
    }

    bool getHeroType() override {
        return false;
    }
};