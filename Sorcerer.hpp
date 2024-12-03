#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Sorcerer : public Jobs {
private:
	string Name = " Sorcier ";
	string Desc = "Tu es un Sorcier Harry !";
	string spellName = "Mur De Feu";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 1 }, { "INT", 8 }, { "FO", 1 }, { "AD", 1 } };

protected :
	string getNameJob() override {
		return this->Name;
	}
	string getDescJob()override {
		return this->Desc;
	}
	map<string, int> getStatRequiredJob() override {
		return this->requiredStat;
	}
	string jobSpell(Creatures& foe1, map<string, int> selfStat) override {				//attaque de zone qui inflige un quart de l'intelligence
		int damage = selfStat["INT"] / 3;
		foe1.setCreatureHealth(foe1.getCreatureStat()["HP"] - damage);
		return this->spellName;
	}
	string getSpellName() override {
		return this->spellName;
	}

	//string jobSpell(Creatures& foe1, Creatures&foe2, Heroes& self) override {
	//	int damage = self.getHeroStat()["INT"] / 4;
	//	foe1.setCreatureHealth(foe1.getCreatureHealth() - damage);
	//	foe2.setCreatureHealth(foe2.getCreatureHealth() - damage);
	//	return this->spellName;
	//}
	//string jobSpell(Creatures& foe1, Creatures& foe2, Creatures& foe3, Heroes& self) override {
	//	int damage = self.getHeroStat()["INT"] / 4;
	//	foe1.setCreatureHealth(foe1.getCreatureHealth() - damage);
	//	foe2.setCreatureHealth(foe2.getCreatureHealth() - damage);
	//	foe3.setCreatureHealth(foe3.getCreatureHealth() - damage);
	//	return this->spellName;
	//}
	//string jobSpell(Creatures& foe1, Creatures& foe2, Creatures& foe3, Creatures& foe4, Heroes& self) override {
	//	int damage = self.getHeroStat()["INT"] / 4;
	//	foe1.setCreatureHealth(foe1.getCreatureHealth() - damage);
	//	foe2.setCreatureHealth(foe2.getCreatureHealth() - damage);
	//	foe3.setCreatureHealth(foe3.getCreatureHealth() - damage);
	//	foe4.setCreatureHealth(foe4.getCreatureHealth() - damage);
	//	return this->spellName;
	//}
};