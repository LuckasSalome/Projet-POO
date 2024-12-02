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
	map<string, int> stat{ {"COU", 11}, {"CHA", 7}, {"INT", 3}, {"FO",12 }, {"AD", 7} };
	int health = 35;
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
	int getHealth() override {
		return this->health;
	}
	string raceSpell(Creatures& foe, Heroes& self) override {
		string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		self.getHeroStat()["COU"] += 5;
		for (int i = 0; i < 5; i++)
			foe.getCreatureStat()[statistics[i]] -= 1;
		return this->spellName;
	}
	void basicAttack(Creatures& foe, Heroes& self) override {
		damage = self.getHeroStat()["FO"];
		proba = 50 - self.getHeroStat()["FO"];
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureHealth() - damage);
	}
};