#pragma once

#include <random>
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
#include "Creatures.hpp"

using namespace std;

class Heroes {																								//class hero observer des class race et job pour savoir avec le polymorphisme la classe et la race du personnage
private  :
	string heroName;
	string heroDesc;
	string heroRace;
	string heroJob;
	int heroHealth;
	map<string, int> heroStat;
	bool possible;
	bool isAlive;
	int heroLevel = 1;
	int exp = 0;
	int expMax = 30;

public :
	Heroes(string Name) : heroName(Name) {};

	bool StatCoparison(Race& race, Jobs& job) {																//comparaison des stats de race et requises pour un metrier
		string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (race.getStat()[statistics[i]] < job.getStatRequiredJob()[statistics[i]]) {
				this->possible = false;
				return this->possible;
			}
			this->possible = true;
			return this->possible;
		}
	}

	string initName(Race& race, Jobs& job) {																	//fusionne les noms de race et de classe
		if (this->possible) {
			this->heroRace = race.getNameRace();
			this->heroJob = job.getNameJob();
			this->heroName += race.getNameRace() + job.getNameJob();
			return (this->heroName);
		}
	}

	string initDesc(Race& race, Jobs& job) {																	//fusionne les descriptions de race et de classe
		if (this->possible)
			this->heroDesc += (job.getDescJob() + race.getDescRace());
			return this->heroDesc;
	}

	virtual map<string, int> initHeroStat(Race& race, Jobs& job) {											//init les stats du hero
		if (this->possible)
			this->heroStat = race.getStat();
			return this->heroStat;
	}

	int initHeroHealth(Race& race) {																				//init les pv du hero
		this->heroHealth = race.getHealth();
		return this->heroHealth;
	}


	// getter

	string getName() {																	
		return (this->heroName);

	}

	string getDesc() {																	
		return this->heroDesc;
	}

	virtual map<string, int> getHeroStat() {											
		return this->heroStat;
	}

	int getHeroHealth() {																				
		return this->heroHealth;
	}
	int getHeroLevel() {
		return this->heroLevel;
	}

	//setter
	void setHeroHealth(int set) {
		this->heroHealth = set;
	}

	bool getHeroAlive() {
		return this->isAlive;
	}
	
	void transiLevel() {
		if (this->exp >= this->expMax) {
			this->heroLevel++;
			this->exp -= this->expMax;
			this->expMax += 5;
		}
	}

	virtual void getRaceSpell(Race& race, Creatures& foe) {
		race.raceSpell(foe, *this);
	}

	virtual void getBasicAttack(Race& race, Creatures& foe) {
		race.basicAttack(foe, *this);
	}

	virtual void getJobSpell(Jobs& job, Creatures& foe) {
		job.jobSpell(foe, *this);
	}
	virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2) {
		job.jobSpell(foe1, foe2, *this);
	}
	virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2, Creatures& foe3) {
		job.jobSpell(foe1, foe2, foe3, *this);
	}
	virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2, Creatures& foe3, Creatures& foe4) {
		job.jobSpell(foe1, foe2, foe3, foe4, *this);
	}

};