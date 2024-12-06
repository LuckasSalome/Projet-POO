#pragma once

#include "Boss.hpp"
#include <string>
#include <map>
#include <random>

using namespace std;

class ProgramLich : public Boss {
private:
    string name = "Liche Programmatrice";
    string desc = "Desteste lse dyslexiques";
    string spellName1P1 = "Coup De Clavier";
    string spellName1P2 = "Free() Ton Existence";
    string spellName2P1 = "Erreur Syntaxe (HP)";
    string spellName2P2 = "Diminution";
    map<string, int> stat{ { "COU", 17 }, { "CHA", 17 }, { "INT", 21 }, { "FO", 12 }, { "AD", 16 }, { "HP", 100 } };

protected:

    string getBossName() override {
        return this->name;
    }
    string getBossDesc() override {
        return this->desc;
    }
    string getSpellName1(bool midlife) override {
        if (midlife == false)
            return this->spellName1P1;
        else
            return this->spellName1P2;
    }
    string getSpellName2(bool midlife) override {
        if (midlife == false)
            return this->spellName2P1;
        else
            return this->spellName2P2;
    }
    map <string, int> getBossStat() override {
        return this->stat;
    }

    map<string, int> bossSpell1(std::shared_ptr<Entity> ennemy, map<string, int> creatureStat, bool midlife) {
        if (midlife == false) {
            int damage = creatureStat["INT"] / 3 + creatureStat["CHA"] / 3;
            ennemy->setHealth(ennemy->getStat()["HP"] - damage);
            return creatureStat;
        }
        else {
            int vamp = ennemy->getStat()["HP"] / 2;
            ennemy->setHealth(vamp);
            creatureStat.insert({ "HP", (creatureStat["HP"] + vamp) });
            return creatureStat;
        }
    }
    map<string, int> bossSpell2(std::shared_ptr<Entity> ennemy, map<string, int> creatureStat, bool midlife) {
        if (midlife == false) {
            int proba = rand() % 4;
            if (proba == 1)
                ennemy->setHealth(0);
            return creatureStat;
        }
        else {
            ennemy->setCourage(ennemy->getStat()["COU"] - (ennemy->getStat()["COU"] / 4));
            ennemy->setStrengh(ennemy->getStat()["FO"] - (ennemy->getStat()["FO"] / 4));
            ennemy->setIntelligence(ennemy->getStat()["INT"] - (ennemy->getStat()["INT"] / 4));
            ennemy->setCharism(ennemy->getStat()["CHA"] - (ennemy->getStat()["CHA"] / 4));
            ennemy->setDexterity(ennemy->getStat()["AD"] - (ennemy->getStat()["AD"] / 4));
            return creatureStat;
        }
    }
};