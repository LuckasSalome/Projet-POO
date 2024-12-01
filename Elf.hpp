#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Elf : public Race {
private :
	string name = " Elfe";
	map<string, int> stat{ {"COU", 3}, {"CHA", 11}, {"INT", 12}, {"FO",2 }, {"AD", 12} };
	string desc = " Ne se melange pas avec la plebe, cette aventure ne l'emballe guere par ailleur.";

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
};