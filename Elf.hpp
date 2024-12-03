#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Elf : public Race {
private :
	string name = " Elfe";
	string spellName = "Jeu De Jambes";
	string desc = " Ne se melange pas avec la plebe, cette aventure ne l'emballe guere par ailleur.";
	map<string, int> stat{ {"COU", 3}, {"CHA", 11}, {"INT", 12}, {"FO",2 }, {"AD", 12}, {"HP", 25} };
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
		//if (rand()%2 == 1)
			//=======================  remplacer dans le systeme de combat par faire esquiver une attaque
		return selfStat;
	}
	void basicAttack(Creatures& foe, map<string, int> selfStat) override {
		damage = selfStat["INT"];
		proba = 50 - selfStat["INT"];
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};