#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Ranger : public Jobs {
private:
	string Name = " Rodeur ";
	string Desc = "Il a eu le temps de finir 3 fois le jeu avant que les devs ne lui trouve une description.";
	string spellName = "Tir Dans la Tete";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 7 }, { "INT", 1 }, { "FO", 1 }, { "AD", 7 } };

protected:
	string getNameJob() override {
		return this->Name;
	}
	string getDescJob()override {
		return this->Desc;
	}
	map<string, int> getStatRequiredJob() override {
		return this->requiredStat;
	}
	string jobSpell(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {			//attaque inratable qui inflige la moitie de l'adresse du hero
		int damage = selfStat["AD"] / 2;
		foe->setHealth(foe->getStat()["HP"] - damage);
		return spellName;
	}
	string getSpellName() override {
		return this->spellName;
	}
};