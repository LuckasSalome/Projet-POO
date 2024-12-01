#pragma once

#include <string>
#include <map>

using namespace std;

class Race {
public :
	virtual string getNameRace() = 0;
	virtual map<string, int> getStat() = 0;
	virtual string getDescRace() = 0;
};