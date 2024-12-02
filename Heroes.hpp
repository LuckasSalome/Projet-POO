#pragma once

#include <string>
#include <map>
#include "Thief.hpp"
#include "Warrior.hpp"
#include "Sorcerer.hpp"
#include "Ranger.hpp"
#include "Barbarian.hpp"
#include "Dwarf.hpp"
#include "Elf.hpp"
#include "Human.hpp"


using namespace std;

class Heroes {																								//class hero observer des class race et job pour savoir avec le polymorphisme la classe et la race du personnage
private  :
	string HeroName;

public :
	Heroes(string Name) : HeroName(Name) {};

	bool StatCoparison(Race& race, Jobs& job) {																//comparaison des stats de race et requises pour un metrier
		string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (race.getStat()[statistics[i]] < job.getStatRequiredJob()[statistics[i]]) {
				return false;
			}
			return true;
		}
	}

	string getName(Race& race, Jobs& job) {																	//fusionne les noms de race et de classe
		if (StatCoparison(race, job)) {
			this->HeroName += race.getNameRace() + job.getNameJob();
			return (this->HeroName);
		}
	}

	string getDesc(Race& race, Jobs& job) {																	//fusionne les descriptions de race et de classe
		if (StatCoparison(race, job))
			return (job.getDescJob() + race.getDescRace());
	}

	virtual map<string, int> getHeroStat(Race& race, Jobs& job) {											//donne les stats du hero
		if (StatCoparison(race, job))
			return race.getStat();
	}

	int getHealth(Race& race) {																						//donne les pv du hero
		return race.getHealth();
	}
};