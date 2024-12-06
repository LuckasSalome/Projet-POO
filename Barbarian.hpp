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
	map<string, int> raceSpell(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {
		;
		int damage = 5;
		int regen = 3;
		int foeHealth = foe->getStat()["HP"];
		selfStat.insert({ "HP", selfStat["HP"] + 3 });
		foe->setHealth(foeHealth - damage);
		return selfStat;
	}
	void basicAttack(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {
		int damage = selfStat["FO"];
		int proba = selfStat["FO"] * 2;
		int alea = rand() % 100;
		if (alea <= proba)
			foe->setHealth(foe->getStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};