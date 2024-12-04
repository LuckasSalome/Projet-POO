#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class SarcasticGobelin : public Common {
private:
	string name = "Gobelin Sarcastique";
	string description = "Il vient de dire que tu es tres beau.";
	string spellName = "Coup De Bibine";
	map <string, int> stat{ { "COU", 8 }, { "CHA", 8 }, { "INT", 4 }, { "FO", 15 }, { "AD", 6 }, {"HP", 30}};

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
		int damage = 15;
		int proba = (50 - creatureStat["AD"])*2;
		return creatureStat;
	}
	void basicAttack(Heroes& ennemy, map<string, int> creatureStat) override {
		int damage = creatureStat["FO"];
		int proba = (50 - creatureStat["FO"])*2;
		//dice roll()
		//if (diceRoll())
		//	foe.setCreatureHealth(foe.getCreatureStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};