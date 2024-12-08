#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

// Fonction pour écouter les pressions de touche
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

        // Tableau des options du menu
        Text* menuItems[] = {
            new Text("Up Key: " + data.keyToString(data.upKey), data.font, 24),
            new Text("Down Key: " + data.keyToString(data.downKey), data.font, 24),
            new Text("Left Key: " + data.keyToString(data.leftKey), data.font, 24),
            new Text("Right Key: " + data.keyToString(data.rightKey), data.font, 24),
            new Text("Resize Window (Width x Height): " + to_string(data.windowWidth) + "x" + to_string(data.windowHeight), data.font, 24),
            new Text(data.soundEnabled ? "Sound: On" : "Sound: Off", data.font, 24),
            new Text("Back to Main Menu", data.font, 24)
        };

        // Positionnement des éléments de menu
        for (int i = 0; i < 7; ++i) {
            FloatRect itemBounds = menuItems[i]->getLocalBounds();
            menuItems[i]->setPosition(
                (data.window.getSize().x - itemBounds.width) / 2,
                150 + i * 75
            );
        }

        // Dessin des éléments de menu
        data.window.draw(title);
        for (int i = 0; i < 7; ++i) {
            data.window.draw(*menuItems[i]);
        }

        // Calcul et dessin du rectangle de sélection
        Text& currentItem = *menuItems[data.currentSelection];
        FloatRect bounds = currentItem.getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
        data.selectionRect.setFillColor(Color(0, 0, 0, 0));
        data.selectionRect.setOutlineColor(Color::White);
        data.selectionRect.setOutlineThickness(2);
        data.selectionRect.setPosition(currentItem.getPosition().x - 10, currentItem.getPosition().y - 5);
        data.window.draw(data.selectionRect);

        // Gestion des événements
        Event event;
        while (data.window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                data.window.close();
                inOptionsMenu = false;
                break;
            }

            // Gestion des touches
            if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                case Keyboard::Up:
                    data.currentSelection = (data.currentSelection - 1 + 7) % 7;
                    break;
                case Keyboard::Down:
                    data.currentSelection = (data.currentSelection + 1) % 7;
                    break;
                case Keyboard::Return:
                    // Comportement similaire à l'ancien code
                    switch (data.currentSelection) {
                    case 0: // Up Key
                    case 1: // Down Key
                    case 2: // Left Key
                    case 3: // Right Key
                    {
                        Text assignText("Please assign a key", data.font, 24);
                        assignText.setPosition(100, 700);
                        data.window.draw(assignText);
                        data.window.display();

                        Keyboard::Key newKey = listenForKeyPress(data.window);

                        switch (data.currentSelection) {
                        case 0: data.upKey = newKey; break;
                        case 1: data.downKey = newKey; break;
                        case 2: data.leftKey = newKey; break;
                        case 3: data.rightKey = newKey; break;
                        }
                        menuItems[data.currentSelection]->setString(
                            menuItems[data.currentSelection]->getString().substring(0, menuItems[data.currentSelection]->getString().find(':') + 2)
                            + data.keyToString(newKey)
                        );
                        break;
                    }
                    case 4: // Resize Window
                    {
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
                                    FloatRect resBounds = resText.getLocalBounds();
                                    data.selectionRect.setSize(Vector2f(resBounds.width + 20, resBounds.height + 10));
                                    data.selectionRect.setOutlineColor(Color::White);
                                    data.selectionRect.setPosition(resText.getPosition().x - 10, resText.getPosition().y - 5);
                                    data.window.draw(data.selectionRect);
                                }

                                data.window.draw(resText);
                            }

                            data.window.display();

                            Event resizeEvent;
                            while (data.window.pollEvent(resizeEvent)) {
                                if (resizeEvent.type == Event::KeyPressed) {
                                    if (resizeEvent.key.code == Keyboard::Up)
                                        selectedResolution = (static_cast<unsigned long long>(selectedResolution) - 1 + resolutions.size()) % resolutions.size();
                                    if (resizeEvent.key.code == Keyboard::Down)
                                        selectedResolution = (static_cast<unsigned long long>(selectedResolution) + 1) % resolutions.size();
                                    if (resizeEvent.key.code == Keyboard::Return) {
                                        data.windowWidth = resolutions[selectedResolution].first;
                                        data.windowHeight = resolutions[selectedResolution].second;
                                        data.window.setSize(Vector2u(data.windowWidth, data.windowHeight));
                                        resizing = false;
                                    }
                                }
                            }
                        }

                        // Mise à jour du texte de résolution
                        menuItems[4]->setString(
                            "Resize Window (Width x Height): " +
                            to_string(data.windowWidth) + "x" + to_string(data.windowHeight)
                        );
                        break;
                    }
                    case 5: // Sound Toggle
                    {
                        data.soundEnabled = !data.soundEnabled;
                        if (data.soundEnabled) {
                            data.backgroundMusic.play();
                        }
                        else {
                            data.backgroundMusic.pause();
                        }
                        menuItems[5]->setString(data.soundEnabled ? "Sound: On" : "Sound: Off");
                        break;
                    }
                    case 6: // Back to Main Menu
                        inOptionsMenu = false;
                        break;
                    }
                    break;
                }
            }

            // Gestion des clics de souris
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = data.window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y));

                for (int i = 0; i < 7; ++i) {
                    if (menuItems[i]->getGlobalBounds().contains(mousePos)) {
                        data.currentSelection = i;

                        // Action correspondante à l'élément cliqué
                        switch (i) {
                        case 0: // Up Key
                        case 1: // Down Key
                        case 2: // Left Key
                        case 3: // Right Key
                        {
                            Text assignText("Please assign a key", data.font, 24);
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
                            menuItems[i]->setString(
                                menuItems[i]->getString().substring(0, menuItems[i]->getString().find(':') + 2)
                                + data.keyToString(newKey)
                            );
                            break;
                        }
                        case 4: // Resize Window 
                        {
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

                                    data.window.draw(resText);
                                }

                                data.window.display();

                                Event resizeEvent;
                                while (data.window.pollEvent(resizeEvent)) {
                                    if (resizeEvent.type == Event::MouseButtonPressed &&
                                        resizeEvent.mouseButton.button == Mouse::Left) {
                                        Vector2f mousePos = data.window.mapPixelToCoords(
                                            Vector2i(resizeEvent.mouseButton.x, resizeEvent.mouseButton.y)
                                        );

                                        for (size_t j = 0; j < resolutions.size(); ++j) {
                                            if (resolutionTexts[j].getGlobalBounds().contains(mousePos)) {
                                                data.windowWidth = resolutions[j].first;
                                                data.windowHeight = resolutions[j].second;
                                                data.window.setSize(Vector2u(data.windowWidth, data.windowHeight));
                                                resizing = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            // Mise à jour du texte de résolution
                            menuItems[4]->setString(
                                "Resize Window (Width x Height): " +
                                to_string(data.windowWidth) + "x" + to_string(data.windowHeight)
                            );
                            break;
                        }
                        case 5: // Sound Toggle
                        {
                            data.soundEnabled = !data.soundEnabled;
                            if (data.soundEnabled) {
                                data.backgroundMusic.play();
                            }
                            else {
                                data.backgroundMusic.pause();
                            }
                            menuItems[5]->setString(data.soundEnabled ? "Sound: On" : "Sound: Off");
                            break;
                        }
                        case 6: // Back to Main Menu
                            inOptionsMenu = false;
                            break;
                        }
                        break;
                    }
                }
            }
        }

        data.window.display();

        // Libérer la mémoire des textes
        for (int i = 0; i < 7; ++i) {
            delete menuItems[i];
        }
    }

    // Réinitialiser la sélection sur "New Game" et positionner le rectangle correctement
    if (!inOptionsMenu) {
        data.currentSelection = 0;

        // Positionner le rectangle de sélection sur "New Game"
        FloatRect bounds = data.menuItems[0].getLocalBounds();
        data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 25));
        data.selectionRect.setPosition(
            data.menuItems[0].getPosition().x - 10,
            data.menuItems[0].getPosition().y - 5
        );
    }
}