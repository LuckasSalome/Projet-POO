#pragma once

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include "Group.hpp"

class Fight {
private:
    std::vector<Heroes*> group1;
    std::vector<Creatures*> group2;
    Group& heroes;
    Group& monsters;

public:
    Fight(Group& heroesGroup, Group& monstersGroup)
        : group1(heroesGroup.getGroup()), group2(monstersGroup.getGroup()), heroes(heroesGroup), monsters(monstersGroup) {}

    std::queue<std::string> fightOrder() {
        std::priority_queue<int> OrderPrio;
        std::stack<std::string> Order;
        std::queue<std::string> finalOrder;

        // Remplir la priorité des héros
        for (int i = 0; i < this->group1.size(); i++) {
            OrderPrio.push(this->group1[i]->getStat()["COU"] + this->group1[i]->getStat()["AD"]);
        }

        // Remplir la priorité des monstres
        for (int j = 0; j < this->group2.size(); j++) {
            OrderPrio.push(this->group2[j]->getStat()["COU"] + this->group2[j]->getStat()["AD"]);
        }

        // Déterminer l'ordre de combat
        while (!OrderPrio.empty()) {
            for (int i = 0; i < this->group1.size(); i++) {
                if (this->group1[i]->getStat()["COU"] + this->group1[i]->getStat()["AD"] == OrderPrio.top()) {
                    Order.push(this->group1[i]->getName());
                    OrderPrio.pop();
                }
            }
            for (int i = 0; i < this->group2.size(); i++) {
                if (this->group2[i]->getStat()["COU"] + this->group2[i]->getStat()["AD"] == OrderPrio.top()) {
                    Order.push(this->group2[i]->getName());
                    OrderPrio.pop();
                }
            }
        }

        // Transférer de la pile vers la file d'attente
        while (!Order.empty()) {
            finalOrder.push(Order.top());
            Order.pop();
        }

        return finalOrder;
    }

    void roundCheck() {
        for (Heroes* hero : this->group1) {
            if (hero->isHeroAlive())
                heroes.removeParty(hero);
        }
        for (Creatures* mob : this->group2) {
            if (mob->isCreatureAlive())
                monsters.removeGroup(mob);
        }
    }


};
