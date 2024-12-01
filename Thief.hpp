#pragma once

#include "Jobs.hpp"
#include <string>
#include <map>

using namespace std;

class Thief : public Jobs {
private:
	string Name = " Voleur ";
	map<string, int> requiredStat{ { "COU", 1 }, { "CHA", 1 }, { "INT", 1 }, { "FO", 1}, { "AD", 8 } };
	string Desc = "Il a meme vole sa description.";

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