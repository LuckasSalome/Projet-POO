#pragma once

#include "Race.hpp"
#include <string>
#include <map>

using namespace std;

class Human : public Race {
private:
	string name = "Humain";
	map<string, int> stat { { "COU", 8 }, { "CHA", 8 }, { "INT", 8 }, { "FO",8 }, { "AD", 8 } };
	string desc = "Personne pas folle folle, un peu comme toi.";

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