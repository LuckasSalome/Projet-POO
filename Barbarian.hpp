#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Barbarian : public Race {
private:
	string name = " Barbare";
	string desc = " SKKAAAAARRRRR,ahoo ahoo ahoo huwhawhawhauaha.";
	string spellName = "Coup Vorace";
	map<string, int> stat{ {"COU", 12}, { "CHA", 9 }, { "INT", 3 }, { "FO", 13}, { "AD", 2 }, {"HP", 35} };
	int damage;
	int proba;

protected:
	string getNameRace() override {
		return this->name;
	}
	string getDescRace()override {
		return this->desc;
	}
	map<string, int> getStat() override {
		return this->stat;
	}
	map<string, int> raceSpell(Creatures& foe, map<string, int> selfStat) override {;
		int damage = 5;
		int regen = 3;
		int foeHealth = foe.getCreatureStat()["HP"];
		selfStat.insert({ "HP", selfStat["HP"] + 3 });
		foe.setCreatureHealth(foeHealth - damage);
		return selfStat;
	}
	void basicAttack(Creatures& foe, map<string, int> selfStat) override {
		damage = selfStat["FO"];
		proba = 50 - selfStat["FO"];
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};