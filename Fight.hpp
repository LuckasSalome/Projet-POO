#pragma once

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <random>
#include "Group.hpp"
#include "Enemy.hpp"
#include "DialogBox.hpp"

class Fight {
private:
    std::vector<std::shared_ptr<Entity>> group1;
    std::vector<std::shared_ptr<Entity>> group2;
    Group& heroes;
    Group& monsters;
    Enemy* enemy;

public:
    Fight(Group& heroesGroup, Group& monstersGroup)
        : heroes(heroesGroup), monsters(monstersGroup), enemy(nullptr) { // Initialisation de enemy
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

    void roundCheck(const std::string& newEntityMap) { // Ajout de const et référence
        for (auto& hero : this->group1) {
            if (!hero->getAlive()) {
                heroes.removeParty(hero);
            }
        }
        for (auto& mob : this->group2) {
            if (!mob->getAlive()) {
                for (int i = 0; i < group1.size(); i++) {
                    group1[i]->setExp(30);
                    std::cout << "Vous etes niveau :" << group1[i]->getHeroLevel() << std::endl;
                }
                enemy->setDefeated(true, newEntityMap);
                monsters.removeParty(mob);
                std::cout << "Enemy defeated" << std::endl;
            }
        }
    }

    void fighting(Common& mob, Boss& lich, Race& race, Jobs& job, sf::RenderWindow& window, const string& newEntityMap) {
        int target;
        int spell;
        std::string content;
        DialogBox dialogBox(window.getSize().x, window.getSize().y / 3);

        // Calculer la position centrale
        float dialogBoxWidth = dialogBox.getSize().x;
        float dialogBoxHeight = dialogBox.getSize().y;
        float windowWidth = window.getSize().x;
        float windowHeight = window.getSize().y;

        // Positionner la boîte de dialogue en bas au milieu de l'écran
        float posX = (windowWidth - dialogBoxWidth) / 2;
        float posY = windowHeight - dialogBoxHeight - 50; // 50 pixels au-dessus du bas de l'écran
        dialogBox.setPosition(posX, posY);

        while (!heroes.isGroupEmpty() && !monsters.isGroupEmpty()) {
            auto Ordre = fightOrder();
            while (!Ordre.empty()) {
                content = "";
                std::shared_ptr<Entity> currentEntity = Ordre.front();
                Ordre.pop();
                if (currentEntity->getHeroType()) {
                    content += "C'est au tour de " + currentEntity->getName() + "\n" + currentEntity->getDesc() + "\n";
                    for (auto& stat : currentEntity->getStat()) {
                        content += (stat.first + " : " + std::to_string(stat.second)) + "\n";
                    }
                    content += "Choisissez une cible et un sort [0: Attaque de base / 1: Competence de race / 2: Competence de metier]";
                    dialogBox.setText(content);
                    dialogBox.draw(window);
                    window.display();
                    std::cin >> target;
                    std::cin >> spell;

                    if (target >= 0 && target < group2.size()) {
                        if (spell == 0) {
                            dialogBox.setText("Vous avez lance " + currentEntity->getBasicAttack(race, group2[target]) + " sur " + group2[target]->getName());
                        }
                        else if (spell == 1) {
                            dialogBox.setText("Vous avez lance " + currentEntity->getRaceSpell(race, group2[target]) + " sur " + group2[target]->getName());
                        }
                        else if (spell == 2) {
                            dialogBox.setText("Vous avez lance " + currentEntity->getJobSpell(job, group2[target]) + " sur " + group2[target]->getName());
                        }
                    }
                    else {
                        dialogBox.setText("Index de cible invalide !");
                    }
                    dialogBox.draw(window);
                    window.display();
                    sf::sleep(sf::seconds(4));
                }
                else if (currentEntity->getIsBoss() == true) {
                    content += "C'est au tour de " + currentEntity->getName() + "\n" + currentEntity->getDesc() + "\n";

                    for (auto& stat : currentEntity->getStat()) {
                        content += stat.first + " : " + std::to_string(stat.second) + "\n";
                    }
                    dialogBox.setText(content);
                    dialogBox.draw(window);
                    window.display();

                    spell = rand() % 2;
                    target = rand() % group1.size();
                    if (spell == 0) {
                        dialogBox.setText(currentEntity->getName() + " lance " + currentEntity->getBossSpell1(lich, group1[target]) + " sur " + group1[target]->getName());
                    }
                    else {
                        dialogBox.setText(currentEntity->getName() + " lance " + currentEntity->getBossSpell2(lich, group1[target]) + " sur " + group1[target]->getName());
                    }
                    dialogBox.draw(window);
                    window.display();
                    sf::sleep(sf::seconds(4));
                }
                else {
                    content += "C'est au tour de " + currentEntity->getName() + "\n" + currentEntity->getDesc() + "\n";

                    for (auto& stat : currentEntity->getStat()) {
                        content += stat.first + " : " + std::to_string(stat.second) + "\n";
                    }
                    dialogBox.setText(content);
                    dialogBox.draw(window);
                    window.display();
                    sf::sleep(sf::seconds(1));

                    spell = rand() % 2;
                    target = rand() % group1.size();
                    if (spell == 0) {
                        dialogBox.setText(currentEntity->getName() + " a lance " + currentEntity->getMonsterSpell(mob, group1[target]) + " sur " + group1[target]->getName());
                    }
                    else {
                        dialogBox.setText(currentEntity->getName() + " a lance " + currentEntity->getBasicAttack(mob, group1[target]) + " et inflige " + std::to_string(currentEntity->getStat()["AD"]) + " degats a " + group1[target]->getName());
                    }
                    dialogBox.draw(window);
                    window.display();
                    sf::sleep(sf::seconds(4));
                }
                roundCheck(newEntityMap);
            }
            roundCheck(newEntityMap);
        }
    }

};