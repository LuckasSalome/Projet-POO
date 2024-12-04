#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

// Définir la fonction pour écouter les pressions de touche
Keyboard::Key listenForKeyPress(RenderWindow& window) {
    Event event;
    while (true) {
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                return event.key.code;  // Retourner la touche pressée
            }
        }
    }
}

// Fonction pour gérer le menu des options
void handleOptionsMenu(GameData& data, bool& inOptionsMenu) {
    while (inOptionsMenu) {
        data.window.clear();

        // Titre de l'option
        Text title("Options Menu", data.font, 60);
        FloatRect titleBounds = title.getLocalBounds();
        title.setPosition((data.window.getSize().x - titleBounds.width) / 2, 30); // Centrage horizontal
        data.window.draw(title);

        // Affichage des configurations des touches
        Text upKeyText("Up Key: " + data.keyToString(data.upKey), data.font, 24);
        FloatRect upKeyTextBounds = upKeyText.getLocalBounds();
        upKeyText.setPosition((data.window.getSize().x - upKeyTextBounds.width) / 2, 150); // Centrage horizontal
        data.window.draw(upKeyText);

        Text downKeyText("Down Key: " + data.keyToString(data.downKey), data.font, 24);
        FloatRect downKeyTextBounds = downKeyText.getLocalBounds();
        downKeyText.setPosition((data.window.getSize().x - downKeyTextBounds.width) / 2, 225); // Centrage horizontal
        data.window.draw(downKeyText);

        Text leftKeyText("Left Key: " + data.keyToString(data.leftKey), data.font, 24);
        FloatRect leftKeyTextBounds = leftKeyText.getLocalBounds();
        leftKeyText.setPosition((data.window.getSize().x - leftKeyTextBounds.width) / 2, 300); // Centrage horizontal
        data.window.draw(leftKeyText);

        Text rightKeyText("Right Key: " + data.keyToString(data.rightKey), data.font, 24);
        FloatRect rightKeyTextBounds = rightKeyText.getLocalBounds();
        rightKeyText.setPosition((data.window.getSize().x - rightKeyTextBounds.width) / 2, 375); // Centrage horizontal
        data.window.draw(rightKeyText);

        Text resizeText("Resize Window (Width x Height): " + to_string(data.windowWidth) + "x" + to_string(data.windowHeight), data.font, 24);
        FloatRect resizeTextBounds = resizeText.getLocalBounds();
        resizeText.setPosition((data.window.getSize().x - resizeTextBounds.width) / 2, 450); // Centrage horizontal
        data.window.draw(resizeText);

        // Affichage de l'option Sound On/Off
        string soundText = data.soundEnabled ? "Sound: On" : "Sound: Off";
        Text soundTextOption(soundText, data.font, 24);
        FloatRect soundTextOptionBounds = soundTextOption.getLocalBounds();
        soundTextOption.setPosition((data.window.getSize().x - soundTextOptionBounds.width) / 2, 525); // Centrage horizontal
        data.window.draw(soundTextOption);

        Text backText("Back to Main Menu", data.font, 24);  // Option retour
        FloatRect backTextBounds = backText.getLocalBounds();
        backText.setPosition((data.window.getSize().x - backTextBounds.width) / 2, 600); // Centrage horizontal
        data.window.draw(backText);

        // Ajouter tous les éléments au dessin
        data.window.draw(title);
        data.window.draw(upKeyText);
        data.window.draw(downKeyText);
        data.window.draw(leftKeyText);
        data.window.draw(rightKeyText);
        data.window.draw(resizeText);
        data.window.draw(soundTextOption);  // Afficher le texte du son
        data.window.draw(backText);

        // Tableau des options du menu
        Text* menuItems[] = { &upKeyText, &downKeyText, &leftKeyText, &rightKeyText, &resizeText, &soundTextOption, &backText };
        Text& currentItem = *menuItems[data.currentSelection];

        // Calculer la taille du rectangle en fonction du texte actuel
        FloatRect bounds = currentItem.getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10)); // Ajout de marges autour du texte
        data.selectionRect.setFillColor(Color(0, 0, 0, 0));
        data.selectionRect.setOutlineColor(Color::White);
        data.selectionRect.setOutlineThickness(2);
        data.selectionRect.setPosition(currentItem.getPosition().x - 10, currentItem.getPosition().y - 5); // Positionner le rectangle

        data.window.draw(data.selectionRect);

        // Gestion des événements
        Event event;
        while (data.window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                data.window.close();
                inOptionsMenu = false;
            }
            // Gestion des clics de souris
            else if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    for (int i = 0; i < 7; ++i) {
                        FloatRect itemBounds = menuItems[i]->getGlobalBounds();
                        Vector2f mousePos = data.window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                        if (itemBounds.contains(mousePos)) {
                            data.currentSelection = i;  // Met à jour la sélection
                            if (i == 6) {  // Retour au menu principal
                                inOptionsMenu = false;
                            }
                            else if (i < 4) {  // Modifier une touche
                                Text assignText("Please assign a touch", data.font, 24);
                                assignText.setPosition(100, 700);
                                data.window.draw(assignText);
                                data.window.display();

                                Keyboard::Key newKey = listenForKeyPress(data.window);

                                switch (i) {
                                case 0: data.upKey = newKey; break;
                                case 1: data.downKey = newKey; break;
                                case 2: data.leftKey = newKey; break;
                                case 3: data.rightKey = newKey; break;
                                }
                            }
                            else if (i == 4) {  // Redimensionner la fenêtre
                                const vector<pair<int, int>> resolutions = { {800, 600}, {1024, 768}, {1280, 720}, {1920, 1080} };
                                int selectedResolution = 0;
                                bool resizing = true;

                                while (resizing) {
                                    data.window.clear();
                                    Text resizeTitle("Choose Window Size:", data.font, 30);
                                    resizeTitle.setPosition(100, 50);
                                    data.window.draw(resizeTitle);

                                    vector<Text> resolutionTexts;
                                    for (size_t j = 0; j < resolutions.size(); ++j) {
                                        Text resText(to_string(resolutions[j].first) + "x" + to_string(resolutions[j].second), data.font, 24);
                                        resText.setPosition(100, 150 + j * 50);

                                        resolutionTexts.push_back(resText);

                                        if (j == selectedResolution) {
                                            FloatRect bounds = resText.getLocalBounds();
                                            data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
                                            data.selectionRect.setOutlineColor(Color::White);
                                            data.selectionRect.setPosition(resText.getPosition().x - 10, resText.getPosition().y - 5);
                                            data.window.draw(data.selectionRect);
                                        }

                                        data.window.draw(resText);
                                    }

                                    while (data.window.pollEvent(event)) {
                                        if (event.type == Event::KeyPressed) {
                                            if (event.key.code == Keyboard::Up) selectedResolution = (selectedResolution - 1 + resolutions.size()) % resolutions.size();
                                            if (event.key.code == Keyboard::Down) selectedResolution = (selectedResolution + 1) % resolutions.size();
                                            if (event.key.code == Keyboard::Return) {
                                                data.windowWidth = resolutions[selectedResolution].first;
                                                data.windowHeight = resolutions[selectedResolution].second;
                                                data.window.setSize(Vector2u(data.windowWidth, data.windowHeight));
                                                resizing = false;
                                            }
                                        }
                                        else if (event.type == Event::MouseButtonPressed) {
                                            if (event.mouseButton.button == Mouse::Left) {
                                                Vector2f mousePos = data.window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));
                                                for (size_t j = 0; j < resolutionTexts.size(); ++j) {
                                                    FloatRect bounds = resolutionTexts[j].getGlobalBounds();
                                                    if (bounds.contains(mousePos)) {
                                                        selectedResolution = j;
                                                        data.windowWidth = resolutions[selectedResolution].first;
                                                        data.windowHeight = resolutions[selectedResolution].second;
                                                        data.window.setSize(Vector2u(data.windowWidth, data.windowHeight));
                                                        resizing = false;
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    data.window.display();
                                }
                            }
                            else if (i == 5) {  // Basculer le son
                                data.soundEnabled = !data.soundEnabled;
                                if (data.soundEnabled) {
                                    data.backgroundMusic.play();  // Reprendre la musique
                                }
                                else {
                                    data.backgroundMusic.pause();  // Mettre la musique en pause
                                }
                            }
                        }
                    }
                }
            }
            // Gestion des pressions de touche
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) data.currentSelection = (data.currentSelection - 1 + 7) % 7;
                if (event.key.code == Keyboard::Down) data.currentSelection = (data.currentSelection + 1) % 7;
                if (event.key.code == Keyboard::Return) {
                    if (data.currentSelection == 6) inOptionsMenu = false; // Retour
                }
            }
        }

        data.window.display();
    }
    // Réinitialiser la sélection sur "New Game" et positionner le rectangle correctement
    if (!inOptionsMenu) {
        data.currentSelection = 0;
        FloatRect bounds = data.menuItems[0].getGlobalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
        data.selectionRect.setPosition(bounds.left - 10, bounds.top - 5);
    }
}
