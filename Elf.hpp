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
	map<string, int> stat{ {"COU", 3}, {"CHA", 11}, {"INT", 12}, {"FO",2 }, {"AD", 12} };
	int health = 25;
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
		//if (rand()%2 == 1)
			//=======================  remplacer dans le systeme de combat par faire esquiver une attaque
		return this->spellName;
	}
	void basicAttack(Creatures& foe, Heroes& self) override {
		damage = self.getHeroStat()["INT"];
		proba = 50 - self.getHeroStat()["INT"];
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureHealth() - damage);
	}
};