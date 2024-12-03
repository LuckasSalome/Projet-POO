#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class RhetoricianTroll : public Common {
private:
	string name = "Troll Rhetoricien";
	string description = "Il parle d'abord. Tue pendant qu'il parle.";
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
};