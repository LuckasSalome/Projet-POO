#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "GameData.hpp"
#include "Heroes.hpp"
#include "Creatures.hpp"

using namespace sf;
using namespace std;

bool isCreated = false;
string charaRace;
string charaJob;

// Déclarations externes des fonctions de création
extern Jobs* createJobs(const string& type);
extern Race* createRace(const string& type);

// Implémentations des fonctions de création
Jobs* createJobs(const string& type) {
    if (type == "Guerrier") {
        return new Warrior();
    }
    else if (type == "Sorcier") {
        return new Sorcerer();
    }
    else if (type == "Voleur") {
        return new Thief();
    }
    else if (type == "Rodeur") {
        return new Ranger();
    }
    else {
        return nullptr;
    }
}

Race* createRace(const string& type) {
    if (type == "Elfe") {
        return new Elf();
    }
    else if (type == "Barbare") {
        return new Barbarian();
    }
    else if (type == "Nain") {
        return new Dwarf();
    }
    else if (type == "Humain") {
        return new Human();
    }
    else {
        return nullptr;
    }
}

Heroes* createCharacter(Race* race, Jobs* job) {
    if (race == nullptr || job == nullptr) {
        cerr << "Race ou Job est nul" << endl;
        return nullptr;
    }

    Heroes* character = new Heroes();
    if (!character->StatComparison(*race, *job)) {
        cerr << "Erreur de création de personnage" << endl;
        delete character;
        return nullptr;
    }
    character->initDesc(*race, *job);
    character->initName(*race, *job);
    character->initHeroStat(*race, *job);
    isCreated = true;
    return character;
}


bool handleCharacterSelection(GameData& data, bool& inCharacterSelection, Event& event) {
    const string races[] = { "Barbare", "Humain", "Nain", "Elfe", "Retour" };
    const string jobs[] = { "Guerrier", "Sorcier", "Voleur", "Rodeur", "Retour" };

    bool selectingJob = false;
    string selectedRace = "";

    // Préparation des textes de personnages
    Text characterTexts[5];
    float maxWidth = 0.0f;

    // Configuration des textes
    for (int i = 0; i < 5; ++i) {
        characterTexts[i].setFont(data.font);
        characterTexts[i].setString(selectingJob ? jobs[i] : races[i]);
        characterTexts[i].setCharacterSize(35);
        characterTexts[i].setFillColor(Color::White);
    }

    while (inCharacterSelection) {
        data.window.clear();

        // Titre
        Text title(selectingJob ? "Choix du Métier" : "Choix de la Race", data.font, 50);
        title.setPosition(
            (data.window.getSize().x - title.getLocalBounds().width) / 2,
            50
        );
        data.window.draw(title);

        // Positionner les textes centrés
        for (int i = 0; i < 5; ++i) {
            FloatRect textBounds = characterTexts[i].getLocalBounds();
            characterTexts[i].setString(selectingJob ? jobs[i] : races[i]);
            characterTexts[i].setPosition(
                (data.window.getSize().x - textBounds.width) / 2, 200 + i * 100
            );
            data.window.draw(characterTexts[i]);
        }

        // Dessin du rectangle de sélection
        FloatRect bounds = characterTexts[data.currentSelection].getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 15));
        data.selectionRect.setPosition(
            (data.window.getSize().x - bounds.width) / 2 - 10,
            characterTexts[data.currentSelection].getPosition().y
        );
        data.window.draw(data.selectionRect);

        data.window.display();

        // Gestion des événements
        while (data.window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                data.window.close();
                inCharacterSelection = false;
                return false;
            }

            // Gestion du clavier
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    data.currentSelection = (data.currentSelection - 1 + 5) % 5;
                }
                else if (event.key.code == Keyboard::Down) {
                    data.currentSelection = (data.currentSelection + 1) % 5;
                }
                else if (event.key.code == Keyboard::Enter) {
                    if (!selectingJob) {
                        if (data.currentSelection == 4) {
                            inCharacterSelection = false;
                        }
                        else {
                            selectedRace = races[data.currentSelection];
							charaRace = selectedRace;
                            selectingJob = true;
                            data.currentSelection = 0;
                        }
                    }
                    else {
                        if (data.currentSelection == 4) {
                            selectingJob = false;
                        }
                        else {
                            string selectedJob = jobs[data.currentSelection];
							charaJob = selectedJob;

                            // Créer le personnage
                            if (data.currentCharacter != nullptr) {
                                delete data.currentCharacter;
                            }
                            Race* race = createRace(selectedRace);
                            Jobs* job = createJobs(selectedJob);
                            data.currentCharacter = createCharacter(race, job);
                            // Libération de la mémoire temporaire
                            delete race;
                            delete job;
                            inCharacterSelection = false;
                            if (isCreated == true)
                            {
                                return false;
                            }
                            else if (isCreated == false)
                                return true;
                        }
                    }
                }
            }

            // Gestion de la souris
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = data.window.mapPixelToCoords(
                        Vector2i(event.mouseButton.x, event.mouseButton.y)
                    );

                    for (int i = 0; i < 5; ++i) {
                        if (characterTexts[i].getGlobalBounds().contains(mousePos)) {
                            data.currentSelection = i;

                            if (!selectingJob) {
                                if (data.currentSelection == 4) {
                                    inCharacterSelection = false;
                                }
                                else {
                                    selectedRace = races[data.currentSelection];
									charaRace = selectedRace;
                                    selectingJob = true;
                                    data.currentSelection = 0;
                                }
                            }
                            else {
                                if (data.currentSelection == 4) {
                                    selectingJob = false;
                                }
                                else {
                                    string selectedJob = jobs[data.currentSelection];
									charaJob = selectedJob;
                                    // Créer le personnage
                                    if (data.currentCharacter != nullptr) {
                                        delete data.currentCharacter;
                                    }
                                    Race* race = createRace(charaRace);
                                    Jobs* job = createJobs(charaJob);
                                    data.currentCharacter = createCharacter(race, job);
                                    // Libération de la mémoire temporaire
                                    delete race;
                                    delete job;
                                    inCharacterSelection = false;
                                    if (isCreated == true)
                                    {
                                        return false;
                                    }
                                    else if (isCreated == false)
                                        return true;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    // Réinitialiser la sélection au menu principal
    data.currentSelection = 0;

    FloatRect bounds = data.menuItems[0].getLocalBounds();
    data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 25));
    data.selectionRect.setPosition(
        data.menuItems[0].getPosition().x - 10,
        data.menuItems[0].getPosition().y - 5
    );
}

std::string getCharaRace()
{
	return charaRace;
}
std::string getCharaJob()
{
	return charaJob;
}