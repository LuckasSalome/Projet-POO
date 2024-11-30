#pragma once

#include <string>
#include <map>
#include "Heroes.hpp"

using namespace std;

class Race : public Heroes {
protected :
	virtual string getNameRace() = 0;
	virtual map<string, int> getStat() = 0;
	virtual string getDescRace() = 0;
};