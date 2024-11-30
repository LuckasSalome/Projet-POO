#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Dwarf : public Race {
private:
	string name = "Nain";
	map<string, int> stat{ {"COU", 11}, {"CHA", 7}, {"INT", 3}, {"FO",12 }, {"AD", 7} };
	string desc = "De nos jour, il serait plus adapte de dire 'personne de petite taille'.";

public:
	string getNameJob() override {
		return this->name;
	}
	string getDescJob()override {
		return this->desc;
	}
	map<string, int> getStat() override {
		return this->stat;
	}
};