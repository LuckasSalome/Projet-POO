#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Barbarian : public Race {
private:
	string name = "Barbare";
	map<string, int> stat{ {"COU", 12}, { "CHA", 9 }, { "INT", 3 }, { "FO", 13}, { "AD", 2 }};
	string desc = "SKKAAAAARRRRR,ahoo ahoo ahoo huwhawhawhauaha.";

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