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
	map<string, int> stat{ {"COU", 12}, { "CHA", 9 }, { "INT", 3 }, { "FO", 13}, { "AD", 2 } };
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

	string raceSpell(Creatures& foe, Heroes& self) override {;
		int damage = 5;
		int regen = 3;
		int foeHealth = foe.getCreatureHealth();
		self.setHeroHealth(self.getHeroHealth() + regen);
		foe.setCreatureHealth(foeHealth - damage);
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