#pragma once

#include "Common.hpp"
#include <string>
#include <map>

using namespace std;

class ExplosiveDuck : public Common {
private : 
	string name = "Canard Explofif";
	string description = "Il aime pas Macron.";
	map <string, int> stat{ { "COU", 10 }, { "CHA", 5 }, { "INT", 1 }, { "FO", 1 }, { "AD", 10 } };
	int health = 20;

protected : 
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