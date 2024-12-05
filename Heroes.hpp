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
#include "Entity.hpp"

class Entity;

class Heroes : public Entity {													//class hero observer des class race et job pour savoir avec le polymorphisme la classe et la race du personnage
private  :
	std::string heroName;
	std::string heroDesc;
	std::string heroRace;
	std::string heroJob;
	std::map<std::string, int> heroStat;
	const std::map<std::string, int> heroStatPerma;
	bool possible = false;
	bool isAlive = true;
	int heroLevel = 1;
	int exp = 0;
	int expMax = 30; 

public :
	Heroes(std::string Name) : heroName(Name) {};

	void StatComparison(Race& race, Jobs& job) override {																//comparaison des stats de race et requises pour un metrier
		std::string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (race.getStat()[statistics[i]] < job.getStatRequiredJob()[statistics[i]])
				this->possible = false;
		}
		this->possible = true;
	}

	std::string initName(Race& race, Jobs& job) override {																	//fusionne les noms de race et de classe
		if (this->possible) {
			this->heroRace = race.getNameRace();
			this->heroJob = job.getNameJob();
			this->heroName += race.getNameRace() + job.getNameJob();
			return (this->heroName);
		}
	}

	std::string initDesc(Race& race, Jobs& job) override {																	//fusionne les descriptions de race et de classe
		if (this->possible)
			this->heroDesc += (job.getDescJob() + race.getDescRace());
			return this->heroDesc;
	}

	std::map<std::string, int> initHeroStat(Race& race, Jobs& job) override {											//init les stats du hero
		if (this->possible)
			this->heroStat = race.getStat();
			return this->heroStat;
	}


	// getter

	std::string getName() override {
		return (this->heroName);

	}

	std::string getDesc() override {
		return this->heroDesc;
	}

	std::map<std::string, int> getStat() override {
		return this->heroStat;
	}

	int getHeroLevel() const {
		return this->heroLevel;
	}
	bool getAlive()  override {
		return this->isAlive;
	}

	//setter
	void setHealth(int set) {							//modifie les valleurs de stat, equivalent a un .insrt()
		this->heroStat["HP"] = set;
	}
	void setCourage(int set) {
		this->heroStat["COU"] = set;
	}
	void setStrengh(int set) {
		this->heroStat["FO"] = set;
	}
	void setIntelligence(int set) {
		this->heroStat["INT"] = set;
	}
	void setDexterity(int set) {
		this->heroStat["AD"] = set;
	}
	void setCharism(int set) {
		this->heroStat["CHA"] = set;
	}
	void transiLevel() {
		if (this->exp >= this->expMax) {
			this->heroLevel++;
			this->exp -= this->expMax;
			this->expMax += 5;
			this->heroStat = this->heroStatPerma;
			setHealth(this->heroStat["HP"] + heroLevel);
			setCourage(this->heroStat["COU"] + heroLevel);
			setCharism(this->heroStat["CHA"] + heroLevel);
			setStrengh(this->heroStat["FO"] + heroLevel);
			setIntelligence(this->heroStat["INT"] + heroLevel);
			setDexterity(this->heroStat["AD"] + heroLevel);
		}
	}
	string getRaceSpell(Race& race, Entity& foe) override{
		if (isAlive)
		{
			std::map <std::string, int> result = race.raceSpell(foe, this->heroStat);
			if (result["HP"] != this->heroStat["HP"])
				this->setHealth(result["HP"]);
			return race.getSpellName();
		}
	}

	string getBasicAttack(Race& race, Entity& foe) override {
		if (isAlive)
		{
			race.basicAttack(foe, this->heroStat);
			return "Attaque Basique";
		}
	}

    string getJobSpell(Jobs& job, Entity& foe) override {
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

	bool getHeroType() override {
		return true;
	}
};