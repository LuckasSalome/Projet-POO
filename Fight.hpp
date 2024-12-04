#pragma once

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include "Group.hpp"0

class Fight {
private:
    std::vector<Heroes*> hParty;
    std::vector<Creatures*> mGroup;
    Group& heroes;
    Group& monsters;

public:
    Fight(Group& heroesGroup, Group& monstersGroup)
        : hParty(heroesGroup.getParty()), mGroup(monstersGroup.getGroup()), heroes(heroesGroup), monsters(monstersGroup) {}

    std::queue<std::string> fightOrder() {
        std::priority_queue<int> OrderPrio;
        std::stack<std::string> Order;
        std::queue<std::string> finalOrder;

        // Remplir la priorité des héros
        for (int i = 0; i < this->hParty.size(); i++) {
            OrderPrio.push(this->hParty[i]->getHeroStat()["COU"] + this->hParty[i]->getHeroStat()["AD"]);
        }

        // Remplir la priorité des monstres
        for (int j = 0; j < this->mGroup.size(); j++) {
            OrderPrio.push(this->mGroup[j]->getCreatureStat()["COU"] + this->mGroup[j]->getCreatureStat()["AD"]);
        }

        // Déterminer l'ordre de combat
        while (!OrderPrio.empty()) {
            for (int i = 0; i < this->hParty.size(); i++) {
                if (this->hParty[i]->getHeroStat()["COU"] + this->hParty[i]->getHeroStat()["AD"] == OrderPrio.top()) {
                    Order.push(this->hParty[i]->getName());
                    OrderPrio.pop();
                }
            }
            for (int i = 0; i < this->mGroup.size(); i++) {
                if (this->mGroup[i]->getCreatureStat()["COU"] + this->mGroup[i]->getCreatureStat()["AD"] == OrderPrio.top()) {
                    Order.push(this->mGroup[i]->getCreatureName());
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
        for (Heroes* hero : this->hParty) {
            if (hero->isHeroAlive())
                heroes.removeParty(hero);
        }
        for (Creatures* mob : this->mGroup) {
            if (mob->isCreatureAlive())
                monsters.removeGroup(mob);
        }
    }


};
