#pragma once

#include <string>
#include <map>


using namespace std;

class Common {
public :
	virtual string getName() = 0;
	virtual string getDesc() = 0;
	virtual map<string, int> getStat() = 0;
	//virtual map < string, int> Ability1() = 0;
	//virtual map < string, int> Ability2() = 0;
	//virtual map < string, int> Ability3() = 0;
};