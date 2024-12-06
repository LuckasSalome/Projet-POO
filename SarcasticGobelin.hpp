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
	map <string, int> stat{ { "COU", 8 }, { "CHA", 8 }, { "INT", 4 }, { "FO", 15 }, { "AD", 6 }, {"HP", 30} };

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
	map<string, int> monsterSpell(std::shared_ptr<Entity> ennemy, map<string, int> creatureStat) override {
		int damage = 15;
		int proba = (50 - creatureStat["AD"]) * 2;
		return creatureStat;
	}
	void basicAttack(std::shared_ptr<Entity> ennemy, map<string, int> creatureStat) override {
		int damage = creatureStat["FO"];
		int proba = (50 - creatureStat["FO"]) * 2;
		int alea = rand() % 100;
		if (alea <= proba)
			ennemy->setHealth(ennemy->getStat()["HP"] - damage);
	}
	string getSpellName() override {
		return this->spellName;
	}
};