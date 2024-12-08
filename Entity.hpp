#pragma once

#include <string>
#include <map>

class Jobs;
class Race;
class Common;
class Boss;
class Heroes;
class Creatures;

class Entity {
public:
    //virtuelles pures
    virtual std::string getName() = 0;
    virtual std::string getDesc() = 0;
    virtual std::map<std::string, int> getStat() = 0;
    virtual bool getAlive() = 0;
    virtual bool getHeroType() = 0;
    virtual bool getIsBoss() {
        return false;
    }
	virtual int getHeroLevel() const {
		return 0;
	}
    virtual void setHealth(int set) = 0;
    virtual void setCourage(int set) = 0;
    virtual void setStrengh(int set) = 0;
    virtual void setIntelligence(int set) = 0;
    virtual void setDexterity(int set) = 0;
    virtual void setCharism(int set) = 0;
    virtual void setExp(int set) { return; }
    //implementation par defaut
    virtual std::map<std::string, int> initHeroStat(Race& race, Jobs& job) {
        return std::map<std::string, int>();
    }
    virtual std::string initDesc(Race& race, Jobs& job) {
        return "";
    }
    virtual std::string initName(Race& race, Jobs& job) {
        return "";
    }
	virtual bool StatComparison(Race& race, Jobs& job) {
		return true;
    }
    virtual std::string initCreatureName(Common& mob) {
        return "";
    }
    virtual std::string initCreatureDesc(Common& mob) {
        return "";
    }
    virtual std::map<std::string, int> initCreatureStat(Common& mob) {
        return std::map<std::string, int>();
    }
    virtual std::string initBossName(Boss& mob) {
        return "";
    }
    virtual std::string initBossDesc(Boss& mob) {
        return "";
    }
    virtual std::map<std::string, int> initBossStat(Boss& mob) {
        return std::map<std::string, int>();
    }
    virtual std::string getJobSpell(Jobs& job, std::shared_ptr<Entity> foe) {
        return "";
    }
    virtual std::string getRaceSpell(Race& race, std::shared_ptr<Entity> foe) {
        return "";
    }
    virtual std::string getBasicAttack(Race& race, std::shared_ptr<Entity> foe) {
        return "";
    }
    virtual std::string getMonsterSpell(Common& mob, std::shared_ptr<Entity> ennemy) {
        return "";
    }
    virtual std::string getBasicAttack(Common& mob, std::shared_ptr<Entity> ennemy) {
        return "";
    }
    virtual std::string getBossSpell1(Boss& mob, std::shared_ptr<Entity> ennemy) {
        return "";
    }
    virtual std::string getBossSpell2(Boss& mob, std::shared_ptr<Entity> ennemy) {
        return "";
    }
};