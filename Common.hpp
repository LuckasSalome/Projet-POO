#pragma once

#include <string>
#include <map>
#include "Creatures.hpp"
#include "Heroes.hpp"

using namespace std;

class Common {
public :
	virtual string getName() = 0;
	virtual string getDesc() = 0;
	virtual map<string, int> getStat() = 0;
};