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
	const map<string, int> heroStatPerma;
	bool possible = false;
	bool isAlive = true;
	int heroLevel = 1;
	int exp = 0;
	int expMax = 30; 

public :
	Heroes(string Name) : heroName(Name) {};

	void StatComparison(Race& race, Jobs& job) {																//comparaison des stats de race et requises pour un metrier
		string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (race.getStat()[statistics[i]] < job.getStatRequiredJob()[statistics[i]])
				this->possible = false;
		}
		this->possible = true;
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

	int getHeroLevel() const {
		return this->heroLevel;
	}
	bool getHeroAlive() const {
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
	void setHeroIntelligence(int set) {
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
			this->heroStat = this->heroStatPerma;
			setHeroHealth(this->heroStat["HP"] + heroLevel);
			setHeroCourage(this->heroStat["COU"] + heroLevel);
			setHeroCharism(this->heroStat["CHA"] + heroLevel);
			setHeroStrengh(this->heroStat["FO"] + heroLevel);
			setHeroIntelligence(this->heroStat["INT"] + heroLevel);
			setHeroDexterity(this->heroStat["AD"] + heroLevel);
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

	bool isHeroAlive() {
		if (this->heroStat["HP"] <= 0)
			isAlive = false;
		return this->isAlive;
	}
};