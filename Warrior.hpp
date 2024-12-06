#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Warrior : public Jobs {
private:
	string Name = " Combattant ";
	string spellName = "Cri De Guerre";
	string Desc = "Here we are, don't turn away now. We are the warriors that built this town - Imagine Dragons. ";
	map<string, int> requiredStat{ { "COU", 8 }, { "CHA", 1 }, { "INT", 1 }, { "FO", 8 }, { "AD", 1 } };

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
	string jobSpell(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {						//debuff l'ennemi de 4 de courage
		foe->setCourage(foe->getStat()["COU"] - 5);
		return this->spellName;
	}
	string getSpellName() override {
		return this->spellName;
	}
};