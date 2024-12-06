#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Dwarf : public Race {
private:
	string name = " Nain";
	string spellName = "Fierte De Nain";
	string desc = " De nos jour, il serait plus adapte de dire 'personne de petite taille'.";
	map<string, int> stat{ {"COU", 11}, {"CHA", 7}, {"INT", 3}, {"FO",12 }, {"AD", 7}, {"HP", 35} };

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
		selfStat.insert({ "COU", selfStat["COU"] + 5 });
		foe->setCourage(foe->getStat()["COU"] - 1);
		foe->setStrengh(foe->getStat()["FO"] - 1);
		foe->setIntelligence(foe->getStat()["INT"] - 1);
		foe->setCharism(foe->getStat()["CHA"] - 1);
		foe->setDexterity(foe->getStat()["AD"] - 1);
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