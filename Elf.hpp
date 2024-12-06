#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Elf : public Race {
private:
	string name = " Elfe";
	string spellName = "Palais Mental";
	string desc = " Ne se melange pas avec la plebe, cette aventure ne l'emballe guere par ailleur.";
	map<string, int> stat{ {"COU", 3}, {"CHA", 11}, {"INT", 12}, {"FO",2 }, {"AD", 12}, {"HP", 25} };

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
		if (rand() % 2 == 1)
		{
			selfStat.insert({ "CHA", selfStat["CHA"] + 3 });
			selfStat.insert({ "INT", selfStat["INT"] + 3 });
		}
		return selfStat;
	}
	void basicAttack(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {
		int damage = selfStat["INT"];
		int proba = selfStat["INT"] * 2;
		int alea = rand() % 100;
		if (alea <= proba)
			foe->setHealth(foe->getStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};