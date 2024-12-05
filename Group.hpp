#pragma once

#include <vector>
#include "Heroes.hpp"
#include "Creatures.hpp"

class Group {
private:
    std::vector<Entity*> group;
    std::vector<int>::iterator it;
    bool isEmpty = false;

public:
    std::vector<Entity*> getGroup() {
        return this->group;
    }

    void addParty(Entity* chara) {
        this->group.push_back(chara);
    }
    void addGroup(Entity* chara) {
        this->group.push_back(chara);
    }
    void removeParty(Entity* chara) {
        for (int i=0; i<this->group.size(); i++)
            if (this->group[i] == chara)
                this->group.erase(this->group.begin() + i);
    }
    void removeGroup(Entity* creature) {
        for (int i = 0; i < this->group.size(); i++)
            if (this->group[i] == creature)
                this->group.erase(this->group.begin() + i);
    }

    bool isGroupEmpty() {
        if (this->group.size() == 0)
            this->isEmpty == true;
        return this->isEmpty;
    }
};
