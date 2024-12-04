#pragma once

#include <vector>
#include "Heroes.hpp"
#include "Creatures.hpp"

class Group {
private:
    std::vector<Heroes*> heroParty;
    std::vector<int>::iterator it;
    std::vector<Creatures*> monsterGroup;

public:
    std::vector<Heroes*> getParty() {
        return this->heroParty;
    }
    std::vector<Creatures*> getGroup() {
        return this->monsterGroup;
    }

    void addParty(Heroes* hero) {
        this->heroParty.push_back(hero);
    }
    void addGroup(Creatures* mob) {
        this->monsterGroup.push_back(mob);
    }
    void removeParty(Heroes* hero) {
        for (int i=0; i<this->heroParty.size(); i++)
            if (this->heroParty[i] == hero)
                this->heroParty.erase(this->heroParty.begin() + i);
    }
    void removeGroup(Creatures* creature) {
        for (int i = 0; i < this->monsterGroup.size(); i++)
            if (this->monsterGroup[i] == creature)
                this->monsterGroup.erase(this->monsterGroup.begin() + i);
    }
};
