#pragma once

#include <string>
#include <map>
#include "Entity.hpp"

using namespace std;

class Heroes : public Entity {
private  :
	string Name;
	string Desc;
	map<string, int> Ability1;
	map<string, int> Ability2;
	map<string, int> Ability3;

protected : 
	virtual string getNameJob() = 0;
	virtual string getDescJob() = 0;
	virtual string getNameRace() = 0;
	virtual string getDescRace() = 0;
	virtual map<string, int> getStat() = 0;
	virtual map<string, int> getStatRequiredJob() = 0;
	virtual map<string, int> getAbility1() = 0;
	virtual map<string, int> getAbility2() = 0;
	virtual map<string, int> getAbility3() = 0;

public :

	string getName() {																	//fusionne les noms de race et de classe
		this->Name = getNameJob() + getNameRace();
		return (this->Name);
	}

	string getDesc() {																	//fusionne les descriptions de race et de classe
		this->Desc = getDescJob() + getDescRace();
		return (this->Desc);
	}

	bool StatCoparison() {																//comparaison des stats de race et requises pour un metrier
		string statistics[5] = { "COU","CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (getStat()[statistics[i]] != getStatRequiredJob()[statistics[i]]) {
				return false;
			}
			return true;
		}
	}
};