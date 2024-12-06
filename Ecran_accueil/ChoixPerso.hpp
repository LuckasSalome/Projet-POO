#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "GameData.hpp"
#include "Heroes.hpp"
#include "Creatures.hpp"

using namespace sf;
using namespace std;

string handleCharacterSelection(GameData& data, bool& inCharacterSelection, Event& event) {
    const string races[] = { "Barbare", "Humain", "Nain", "Elfe", "Retour" };
    const string jobs[] = { "Guerrier", "Sorcier", "Voleur", "Rodeur", "Retour" };

    bool selectingJob = false;
    string selectedRace = "";

    // Pr�paration des textes de personnages
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

        // Titre dynamique
        Text title(selectingJob ? "Choix du M�tier" : "Choix de la Race", data.font, 50);
        title.setPosition(
            (data.window.getSize().x - title.getLocalBounds().width) / 2,
            50
        );
        data.window.draw(title);

        // Positionner les textes centr�s
        for (int i = 0; i < 5; ++i) {
            FloatRect textBounds = characterTexts[i].getLocalBounds();
            characterTexts[i].setString(selectingJob ? jobs[i] : races[i]);
            characterTexts[i].setPosition(
                (data.window.getSize().x - textBounds.width) / 2, 200 + i * 100
            );
            data.window.draw(characterTexts[i]);
        }

        // Dessin du rectangle de s�lection
        FloatRect bounds = characterTexts[data.currentSelection].getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 15));
        data.selectionRect.setPosition(
            (data.window.getSize().x - bounds.width) / 2 - 10,
            characterTexts[data.currentSelection].getPosition().y
        );
        data.window.draw(data.selectionRect);

        data.window.display();

        // Gestion des �v�nements
        while (data.window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                data.window.close();
                inCharacterSelection = false;
                // R�initialiser la s�lection sur "New Game"
                data.currentSelection = 0;
                return ""; // Retourne une cha�ne vide si fen�tre ferm�e
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
                                    // R�initialiser explicitement la s�lection et le rectangle
                                    data.currentSelection = 0;

                                    // Repositionner le rectangle de s�lection sur "New Game"
                                    FloatRect bounds = data.menuItems[0].getLocalBounds();
                                    data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 25));
                                    data.selectionRect.setPosition(
                                        data.menuItems[0].getPosition().x - 10,
                                        data.menuItems[0].getPosition().y - 5
                                    );

                                    return ""; // Retour au menu principal
                                }
                                else {
                                    // S�lectionner la race et passer � la s�lection du m�tier
                                    selectedRace = races[data.currentSelection];
                                    selectingJob = true;
                                    data.currentSelection = 0;
                                    break; // Sortir de la boucle pour rafra�chir l'affichage
                                }
                            }
                            else {
                                if (data.currentSelection == 4) {
                                    // Retour � la s�lection de race
                                    selectingJob = false;
                                    data.currentSelection = 0;
                                    break; // Sortir de la boucle pour rafra�chir l'affichage
                                }
                                else {
                                    // Retourner la race et le m�tier s�lectionn�s
                                    inCharacterSelection = false;
                                    return selectedRace + ":" + jobs[data.currentSelection];
                                }
                            }
                        }
                    }
                }
            }

            // Gestion du clavier (similaire � la gestion de la souris)
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
                            // R�initialiser explicitement la s�lection et le rectangle
                            data.currentSelection = 0;

                            // Repositionner le rectangle de s�lection sur "New Game"
                            FloatRect bounds = data.menuItems[0].getLocalBounds();
                            data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 25));
                            data.selectionRect.setPosition(
                                data.menuItems[0].getPosition().x - 10,
                                data.menuItems[0].getPosition().y - 5
                            );

                            return ""; // Retour au menu principal
                        }
                        else {
                            // S�lectionner la race et passer � la s�lection du m�tier
                            selectedRace = races[data.currentSelection];
                            selectingJob = true;
                            data.currentSelection = 0;
                        }
                    }
                    else {
                        if (data.currentSelection == 4) {
                            // Retour � la s�lection de race
                            selectingJob = false;
                            data.currentSelection = 0;
                        }
                        else {
                            // Retourner la race et le m�tier s�lectionn�s
                            inCharacterSelection = false;
                            return selectedRace + ":" + jobs[data.currentSelection];
                        }
                    }
                }
                else if (event.key.code == Keyboard::Escape) {
                    if (selectingJob) {
                        // Retour � la s�lection de race
                        selectingJob = false;
                        data.currentSelection = 0;
                    }
                    else {
                        // Retour au menu principal
                        inCharacterSelection = false;
                        // R�initialiser la s�lection sur "New Game"
                        data.currentSelection = 0;
                        return "";
                    }
                }
            }
        }
    }

    // � la fin de la fonction handleCharacterSelection, ajoutez :
    if (!inCharacterSelection) {
        data.currentSelection = 0;

        // Positionner correctement le rectangle de s�lection
        FloatRect bounds = data.menuItems[0].getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
        data.selectionRect.setPosition(
            data.menuItems[0].getPosition().x - 10,
            data.menuItems[0].getPosition().y - 5
        );
    }
}