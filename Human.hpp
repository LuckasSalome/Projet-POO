#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Human : public Race {
private:
	string name = " Humain";
	string desc = " Personne pas folle folle, un peu comme toi.";
	string spellName = "Bon Repas";
	map<string, int> stat { { "COU", 8 }, { "CHA", 8 }, { "INT", 8 }, { "FO",8 }, { "AD", 8 } };
	int damage;
	int proba;
	int health = 30;


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
		self.setHeroHealth(self.getHeroHealth() + 5);
		return this->spellName;
	}
	void basicAttack(Creatures& foe, Heroes& self) override {
		if (self.getHeroStat()["FO"] < self.getHeroStat()["INT"])
		{
			damage = self.getHeroStat()["INT"];
			proba = 50 - self.getHeroStat()["INT"];
			//dice roll()
		}
		else
		{
			damage = self.getHeroStat()["FO"];
			proba = 50 - self.getHeroStat()["FO"];
			//dice roll()
			//if (diceRoll())
			//	foe.setCreatureHealth(foe.getCreatureHealth() - damage);
		}
	}
};