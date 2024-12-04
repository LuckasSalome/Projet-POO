#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class RhetoricianTroll : public Common {
private:
	string name = "Troll Rhetoricien";
	string description = "Il parle d'abord. Tue pendant qu'il parle.";
	string spellName = "Coups De Raison";
	map <string, int> stat{ { "COU", 10 }, { "CHA", 7 }, { "INT", 9 }, { "FO", 9 }, { "AD", 10 }, {"HP", 30}};

protected:
	string getName() override {
		return this->name;
	}
	string getDesc() override {
		return this->description;
	}
	map<string, int> getStat() override {
		return this->stat;
	}
	map<string, int> monsterSpell(Heroes& ennemy, map<string, int> creatureStat) override {
		int damage = (creatureStat["FO"]+ creatureStat["AD"])/2;
		int proba = 100 - creatureStat["CHA"] - creatureStat["INT"];
		return creatureStat;
	}
	void basicAttack(Heroes& ennemy, map<string, int> creatureStat) override {
		int damage = creatureStat["FO"];
		int proba = 50 - creatureStat["FO"];
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureStat()["HP"] - damage);
	}

	string getSpellName() override {
		return this->spellName;
	}
};