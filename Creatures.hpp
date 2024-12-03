#pragma once

#include <string>
#include <map>
#include "ExplosiveDuck.hpp"
#include "SarcasticGobelin.hpp"
#include "RhetoricianTroll.hpp"
#include "Heroes.hpp"


using namespace std;


class Creatures {
private : 
	string creatureName;
	string creatureDesc;
	map<string, int> creatureStat;
	bool isAlive = true;


public :

	string initCreatureName(Common& mob) {
		this->creatureName = mob.getName();
		return this->creatureName;
	}

	string initCreatureDesc(Common& mob) {
		this->creatureDesc = mob.getDesc();
		return this->creatureDesc;
	}

	map<string, int> initCreatureStat(Common& mob) {
		this->creatureStat = mob.getStat();
		return this->creatureStat;
	}

	//getter

	string getCreatureName() {
		return this->creatureName;
	}

	string getCreatureDesc() {
		return this->creatureDesc;
	}

	map<string, int> getCreatureStat() {
		return this->creatureStat;
	}
	const bool getCreatureAlive() {
		return this->isAlive;
	}

	//setter
	void setCreatureHealth(int set) {
		this->creatureStat["HP"] = set;
	}
	void setCreatureCourage(int set) {
		this->creatureStat["COU"] = set;
	}
	void setCreatureStrengh(int set) {
		this->creatureStat["FO"] = set;
	}
	void setCreatureIntelligence(int set) {
		this->creatureStat["INT"] = set;
	}
	void setCreatureDexterity(int set) {
		this->creatureStat["AD"] = set;
	}
	void setCreatureCharism(int set) {
		this->creatureStat["CHA"] = set;
	}
};	