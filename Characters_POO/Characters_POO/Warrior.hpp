#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Warrior : public Jobs {
private:
	string Name = "Combattant";
	map<string, int> requiredStat{ { "COU", 8 }, { "CHA", 1 }, { "INT", 1 }, { "FO", 8 }, { "AD", 1 } };
	string Desc = "Here we are, don't turn away now. We are the warriors that built this town. - Imagine Dragons";

public:
	string getNameJob() override {
		return this->Name;
	}
	string getDescJob()override {
		return this->Desc;
	}
	map<string, int> getStatRequiredJob() {

	}
};