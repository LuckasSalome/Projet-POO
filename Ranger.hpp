#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Ranger : public Jobs {
private:
	string Name = " Rodeur ";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 7 }, { "INT", 1 }, { "FO", 1 }, { "AD", 7 } };
	string Desc = "Il a eu le temps de finir 3 fois le jeu avant que les devs ne lui trouve une description.";

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
};