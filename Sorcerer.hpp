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
	string jobSpell(std::shared_ptr<Entity> foe1, map<string, int> selfStat) override {
		int damage = selfStat["INT"] / 2;
		foe1->setHealth(foe1->getStat()["HP"] - damage);
		return this->spellName;
	}
	string getSpellName() override {
		return this->spellName;
	}


};