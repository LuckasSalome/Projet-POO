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
	map<string, int> stat{ { "COU", 8 }, { "CHA", 8 }, { "INT", 8 }, { "FO",8 }, { "AD", 8 }, {"HP", 30 }};

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
		selfStat.insert({ "HP", selfStat["HP"] + 5 });
		return selfStat;
	}
	void basicAttack(Creatures& foe, map<string, int> selfStat) override {
		int damage;
		int proba;
		int alea;
		if (selfStat["FO"] < selfStat["INT"])
		{
			damage = selfStat["INT"];
			proba = (50 - selfStat["INT"])*2;
			alea = rand() % 100;
			
		}
		else
		{
			damage = selfStat["FO"];
			proba = (50 - selfStat["FO"])*2;
			alea = rand() % 100;
		}
		if (alea <= proba)
			foe.setCreatureHealth(foe.getStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};