#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Sorcerer : public Jobs {
private:
	string Name = " Sorcier ";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 1 }, { "INT", 8 }, { "FO", 1 }, { "AD", 1 } };
	string Desc = "Tu es un Sorcier Harry !";

protected :
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