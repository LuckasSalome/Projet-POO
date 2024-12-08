#pragma once

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <random>
#include "Group.hpp"
#include "Enemy.hpp"

class Fight {
private:
    std::vector<std::shared_ptr<Entity>> group1;
    std::vector<std::shared_ptr<Entity>> group2;
    Group& heroes;
    Group& monsters;
    Enemy* enemy;

public:
    Fight(Group& heroesGroup, Group& monstersGroup)
        : heroes(heroesGroup), monsters(monstersGroup) {
        group1 = heroes.getGroup();
        group2 = monsters.getGroup();
    }

    std::queue<std::shared_ptr<Entity>> fightOrder() {
        std::priority_queue<std::pair<int, std::shared_ptr<Entity>>> orderPrio;
        std::queue<std::shared_ptr<Entity>> finalOrder;

        // Remplir la priorité des héros
        for (int i = 0; i < this->group1.size(); i++) {
            int priority = this->group1[i]->getStat()["COU"] + this->group1[i]->getStat()["AD"];
            orderPrio.emplace(priority, this->group1[i]);
        }

        // Remplir la priorité des monstres
        for (int j = 0; j < this->group2.size(); j++) {
            int priority = this->group2[j]->getStat()["COU"] + this->group2[j]->getStat()["AD"];
            orderPrio.emplace(priority, this->group2[j]);
        }

        // Déterminer l'ordre de combat
        while (!orderPrio.empty()) {
            finalOrder.push(orderPrio.top().second);
            orderPrio.pop();
        }

        return finalOrder;
    }

    void roundCheck() {
        for (auto& hero : this->group1) {
            if (!hero->getAlive()) {
                heroes.removeParty(hero);
            }
        }
        for (auto& mob : this->group2) {
            if (!mob->getAlive()) {
                for (int i = 0; i < group1.size(); i++) {
                    group1[i]->setExp(30);
					cout << "Vous etes niveau :" << group1[i]->getHeroLevel() << endl;
                }
                enemy->setDefeated(true,"Config/entityMap1.txt");
                monsters.removeParty(mob);
				cout << "Enemy defeated" << endl;
            }
        }
    }

    void fighting(Common& mob, Boss& lich, Race& race, Jobs& job) {
        int target;
        int spell;
        while (!heroes.isGroupEmpty() && !monsters.isGroupEmpty()) {
            auto Ordre = fightOrder();
            while (!Ordre.empty()) {
                std::shared_ptr<Entity> currentEntity = Ordre.front();
                Ordre.pop();
                std::cout << group1[0]->getStat()["HP"] << std::endl;
                std::cout << group1[1]->getStat()["HP"] << std::endl;
                std::cout << group2[0]->getStat()["HP"] << std::endl;
                if (currentEntity->getHeroType()) {
                    std::cout << currentEntity->getName() << std::endl;
                    std::cin >> target;
                    std::cin >> spell;
                    if (target >= 0 && target < group2.size()) {
                        if (spell == 0)
                            currentEntity->getBasicAttack(race, group2[target]);
                        else if (spell == 1)
                            currentEntity->getRaceSpell(race, group2[target]);
                        else if (spell == 2)
                            currentEntity->getJobSpell(job, group2[target]);
                    }
                    else {
                        std::cout << "Index de cible invalide !" << std::endl;
                    }
                }
                else if (currentEntity->getIsBoss()) {
                    std::cout << currentEntity->getName() << std::endl;
                    spell = rand() % 2;
                    target = rand() % group1.size();
                    if (spell == 0) {
                        currentEntity->getBossSpell1(lich, group1[target]);
                    }
                    else {
                        currentEntity->getBossSpell2(lich, group1[target]);
                    }
                }
                else {
                    std::cout << currentEntity->getName() << std::endl;
                    spell = rand() % 2;
                    target = rand() % group1.size();
                    if (spell == 0) {
                        currentEntity->getMonsterSpell(mob, group1[target]);
                    }
                    else {
                        currentEntity->getBasicAttack(mob, group1[target]);
                    }
                }
                roundCheck();
            }
            roundCheck();
        }
    }
};
