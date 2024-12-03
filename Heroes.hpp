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

class Heroes {													//class hero observer des class race et job pour savoir avec le polymorphisme la classe et la race du personnage
private  :
	string heroName;
	string heroDesc;
	string heroRace;
	string heroJob;
	map<string, int> heroStat;
	bool possible;
	bool isAlive = true;
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

	const int getHeroLevel() const {
		return this->heroLevel;
	}
	const bool getHeroAlive() const {
		return this->isAlive;
	}

	//setter
	void setHeroHealth(int set) {							//modifie les valleurs de stat, equivalent a un .insrt()
		this->heroStat["HP"] = set;
	}
	void setHeroCourage(int set) {
		this->heroStat["COU"] = set;
	}
	void setHeroStrengh(int set) {
		this->heroStat["FO"] = set;
	}
	void seHeroIntelligence(int set) {
		this->heroStat["INT"] = set;
	}
	void setHeroDexterity(int set) {
		this->heroStat["AD"] = set;
	}
	void setHeroCharism(int set) {
		this->heroStat["CHA"] = set;
	}
	void transiLevel() {
		if (this->exp >= this->expMax) {
			this->heroLevel++;
			this->exp -= this->expMax;
			this->expMax += 5;
		}
	}
	string getRaceSpell(Race& race, Creatures& foe) {
		if (isAlive)
		{
			map <string, int> result = race.raceSpell(foe, this->heroStat);
			if (result["HP"] != this->heroStat["HP"])
				this->setHeroHealth(result["HP"]);
			return race.getSpellName();
		}
	}

	string getBasicAttack(Race& race, Creatures& foe) const {
		if (isAlive)
		{
			race.basicAttack(foe, this->heroStat);
			return "Attaque Basique";
		}
	}

    string getJobSpell(Jobs& job, Creatures& foe) const {
		if (isAlive)
		{
			job.jobSpell(foe, this->heroStat);
			return job.getSpellName();
		}

    }
	//virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2) {
	//	job.jobSpell(foe1, foe2, *this);
	//}
	//virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2, Creatures& foe3) {
	//	job.jobSpell(foe1, foe2, foe3, *this);
	//}
	//virtual void getJobSpell(Jobs& job, Creatures& foe1, Creatures& foe2, Creatures& foe3, Creatures& foe4) {
	//	job.jobSpell(foe1, foe2, foe3, foe4, *this);
	//}

	bool isHeroAlive() {
		if (this->heroStat["HP"] <= 0)
			isAlive = false;
		return this->isAlive;
	}
};