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
	map<string, int> raceSpell(Creatures& foe, map<string, int> selfStat) override {
		selfStat.insert({ "COU", selfStat["COU"] + 5 });
		foe.setCreatureCourage(foe.getCreatureStat()["COU"] - 1);
		foe.setCreatureStrengh(foe.getCreatureStat()["FO"] - 1);
		foe.setCreatureIntelligence(foe.getCreatureStat()["INT"] - 1);
		foe.setCreatureCharism(foe.getCreatureStat()["CHA"] - 1);
		foe.setCreatureDexterity(foe.getCreatureStat()["AD"] - 1);
		return selfStat;
	}
	void basicAttack(Creatures& foe, map<string, int> selfStat) override {
		damage = selfStat["FO"];
		proba = 50 - damage;
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};