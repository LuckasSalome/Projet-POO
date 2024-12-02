#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class SarcasticGobelin : public Common {
private:
	string name = "Gobelin Sarcastique";
	string description = "Il vient de dire que tu es tres beau.";
	map <string, int> stat{ { "COU", 7 }, { "CHA", 7 }, { "INT", 4 }, { "FO", 15 }, { "AD", 8 } };
	int health = 20;

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
};