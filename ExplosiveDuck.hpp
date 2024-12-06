#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class ExplosiveDuck : public Common {
private:
	string name = "Canard Explosif";
	string description = "Il aime pas Macron.";
	string spellName = "AUTODESTRUCTION";
	map <string, int> stat{ { "COU", 10 }, { "CHA", 5 }, { "INT", 1 }, { "FO", 1 }, { "AD", 10 }, {"HP", 20} };

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
		int damage = 30;
		int proba = 100;
		creatureStat.insert({ "HP", 0 });
		ennemy->setHealth(ennemy->getStat()["HP"] - damage);
		return creatureStat;
	}
	void basicAttack(std::shared_ptr<Entity> ennemy, map<string, int> creatureStat) override {
		int damage = creatureStat["FO"];
		int proba = 50 - creatureStat["FO"];
		int alea = rand() % 100;
		if (alea <= proba)
			ennemy->setHealth(ennemy->getStat()["HP"] - damage);
	}

	string getSpellName() override {
		return this->spellName;
	}
};