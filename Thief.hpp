#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Thief : public Jobs {
private:
	string Name = " Voleur ";
	string Desc = "Il a meme vole sa description.";
	string spellName = "Coup Dans Le Dos";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 1 }, { "INT", 1 }, { "FO", 1}, { "AD", 8 } };

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
	string jobSpell(std::shared_ptr<Entity> foe, map<string, int> selfStat) override {						//le fait attaquer en premier de 5 degats
		int damage = 5;
		//le met en premier en attaque
		foe->setHealth(foe->getStat()["HP"] - damage);
		return this->spellName;
	}
	string getSpellName() override {
		return this->spellName;
	}
};