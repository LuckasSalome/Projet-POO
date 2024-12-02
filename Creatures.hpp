#pragma once

#include <string>
#include <map>
#include "ExplosiveDuck.hpp"
#include "SarcasticGobelin.hpp"
#include "RhetoricianTroll.hpp"


using namespace std;


class Creatures {
private:
	int Health;

public :
	int getHealth() {																						//donne les pv du mob
		return this->Health;
	}

	string getCreatureName(Common& mob) {
		return mob.getName();
	}

	string getCreatureDesc(Common& mob) {
		return mob.getDesc();
	}

	map<string, int> getCreatureStat(Common& mob) {
		return mob.getStat();
	}

};