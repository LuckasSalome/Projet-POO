#pragma once

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Boss {
protected:

	virtual string getNameCreature() const = 0;
	virtual map<string, int> getStatCreature() const = 0;
	virtual string getDescCreature() const = 0;
	virtual map<string, int> getAbility1(string) const = 0;
	virtual map<string, int> getAbility2(const string) const = 0;
	virtual map<string, int> getAbility3(const string) const = 0;
};