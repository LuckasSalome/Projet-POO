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
#include "Items.hpp"
#include "Inventory.hpp"

class Entity;

class Heroes : public Entity {													//class hero observer des class race et job pour savoir avec le polymorphisme la classe et la race du personnage
private:
	std::string heroName;
	std::string heroDesc;
	std::string heroRace;
	std::string heroJob;
	std::map<std::string, int> heroStat;
	const std::map<std::string, int> heroStatPerma;
	bool possible = true;
	bool isAlive = true;
	int heroLevel = 1;
	int exp = 0;
	int expMax = 30;
	Font font;
	Inventory* inventory;
	std::map<std::string, int> stats = inventory->getEquippedStats();

	// Attributs pour les items équipés
	Items* weapon = nullptr;
	Items* armor = nullptr;
	Items* boots = nullptr;

public:
	bool StatComparison(Race& race, Jobs& job) override {
		if (&race == nullptr || &job == nullptr) {
			return false; // Gérer le cas où race ou job est nullptr
		}
		std::string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };
		for (int i = 0; i < 5; i++) {
			if (race.getStat()[statistics[i]] < job.getStatRequiredJob()[statistics[i]])
				this->possible = false;
		}
		return this->possible;
	}


	std::string initName(Race& race, Jobs& job) override {																	//fusionne les noms de race et de classe
		if (&race == nullptr || &job == nullptr) {
			return ""; // Gérer le cas où race ou job est nullptr
		}
		if (this->possible) {
			this->heroRace = race.getNameRace();
			this->heroJob = job.getNameJob();
			this->heroName += race.getNameRace() + job.getNameJob();
			return (this->heroName);
		}
		return "";
	}

	std::string initDesc(Race& race, Jobs& job) override {																	//fusionne les descriptions de race et de classe
		if (&race == nullptr || &job == nullptr) {
			return ""; // Gérer le cas où race ou job est nullptr
		}
		if (this->possible)
			this->heroDesc += (job.getDescJob() + race.getDescRace());
		return this->heroDesc;
	}

	std::map<std::string, int> initHeroStat(Race& race, Jobs& job) override {											//init les stats du hero
		if (&race == nullptr || &job == nullptr) {
			return {};		// Gérer le cas où race ou job est nullptr
		}
		if (this->possible)
			this->heroStat = race.getStat();
		for (const auto& stat : this->stats) {			//parcours la map de stats et les ajoute a la map de stats du hero
			this->heroStat[stat.first] += stat.second;
		}
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
		if (this->heroStat["HP"] <= 0) {
			isAlive = false;
		}
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

	void setExp(int set) {
		this->exp += set;
		transiLevel();
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
			std::cout << "Vous avez gagné un niveau !" << std::endl;
			transiLevel();
		}
	}
	string getRaceSpell(Race& race, std::shared_ptr<Entity> foe) override {
		if (isAlive)
		{
			std::map <std::string, int> result = race.raceSpell(foe, this->heroStat);
			if (result["HP"] != this->heroStat["HP"])
				this->setHealth(result["HP"]);
			return race.getSpellName();
		}
		return"";
	}

	string getBasicAttack(Race& race, std::shared_ptr<Entity> foe) override {
		if (isAlive)
		{
			race.basicAttack(foe, this->heroStat);
			return "Attaque Basique";
		}
		return"";
	}

	string getJobSpell(Jobs& job, std::shared_ptr<Entity> foe) override {
		if (isAlive)
		{
			job.jobSpell(foe, this->heroStat);
			return job.getSpellName();
		}
		return"";
	}

	bool isHeroAlive() const {
		return this->isAlive;
	}

	bool getHeroType() override {
		return true;
	}

};