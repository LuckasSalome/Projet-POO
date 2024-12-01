#pragma once

#include <string>
#include <map>

using namespace std;

class Jobs {
public:
	virtual string getNameJob() = 0;
	virtual string getDescJob() = 0;
	virtual map<string, int> getStatRequiredJob() = 0;
	//virtual map < string, int> getAbility1() = 0;
	//virtual map < string, int> getAbility2() = 0;
	//virtual map < string, int> getAbility3() = 0;
};