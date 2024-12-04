#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameData.hpp"

using namespace sf;
using namespace std;

void initMainMenu(GameData& data) {
    // Rectangle du menu
    float menuWidth = 300;
    float menuHeight = data.window.getSize().y / 2;
    data.menuRect.setSize(Vector2f(menuWidth, menuHeight));
    data.menuRect.setFillColor(Color(0, 0, 0, 170));
    data.menuRect.setPosition(
        (data.window.getSize().x - menuWidth) / 2,
        (data.window.getSize().y - menuHeight) / 2
    );

    // Texte des options
    const string items[] = { "New Game", "Options", "Exit" };
    float verticalSpacing = menuHeight / 4;  // Ajust� pour 3 �l�ments + un espace
    for (int i = 0; i < 3; ++i) {
        data.menuItems[i].setFont(data.font);
        data.menuItems[i].setString(items[i]);
        data.menuItems[i].setCharacterSize(35);
        data.menuItems[i].setFillColor(Color::White);

        FloatRect textBounds = data.menuItems[i].getLocalBounds();
        float textX = data.menuRect.getPosition().x + (menuWidth - textBounds.width) / 2 - textBounds.left;
        float textY = data.menuRect.getPosition().y + verticalSpacing * (i + 1) - textBounds.height / 2 - textBounds.top;
        data.menuItems[i].setPosition(textX, textY);
    }

    // Rectangle de selection
    FloatRect firstTextBounds = data.menuItems[0].getGlobalBounds();
    data.selectionRect.setSize(Vector2f(firstTextBounds.width + 20, firstTextBounds.height + 10));
    data.selectionRect.setFillColor(Color(0, 0, 0, 0));
    data.selectionRect.setOutlineColor(Color::White);
    data.selectionRect.setOutlineThickness(2);
    data.selectionRect.setPosition(
        firstTextBounds.left - 10,
        firstTextBounds.top - 5
    );
}

void handleMainMenuEvents(GameData& data, bool& inOptionsMenu) {
    Event event;
    while (data.window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            data.window.close();
        }
        else if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) {
                data.currentSelection = (data.currentSelection - 1 + 3) % 3;  // Gestion circulaire vers le haut
            }
            else if (event.key.code == Keyboard::Down) {
                data.currentSelection = (data.currentSelection + 1) % 3;  // Gestion circulaire vers le bas
            }
            else if (event.key.code == Keyboard::Enter) {
                switch (data.currentSelection) {
                case 0:
                    std::cout << "New Game selected" << std::endl;
                    break;
                case 1:
                    inOptionsMenu = true;
                    break;
                case 2:
                    data.window.close();
                    break;
                }
            }
            // Mettre � jour le rectangle de s�lection
            FloatRect bounds = data.menuItems[data.currentSelection].getGlobalBounds();
            data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
            data.selectionRect.setPosition(bounds.left - 10, bounds.top - 5);
        }
        // Gestion des clics de souris
        else if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                for (int i = 0; i < 3; ++i) {
                    FloatRect bounds = data.menuItems[i].getGlobalBounds();
                    if (bounds.contains(data.window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)))) {
                        data.currentSelection = i;  // S�lectionner l'�l�ment cliqu�
                        // Ex�cuter l'action associ�e
                        switch (data.currentSelection) {
                        case 0: std::cout << "New Game selected" << std::endl; break;
                        case 1: inOptionsMenu = true; break;
                        case 2: data.window.close(); break;
                        }
                    }
                }
            }
        }
    }
}


void renderMainMenu(GameData& data) {
    data.window.clear();
    data.window.draw(data.background);
    data.window.draw(data.menuRect);

    // Cr�ation du titre "Donjon & Dragon"
    Text title("Donjon & Dragon", data.font, 70);
    title.setFillColor(Color::White);
    title.setPosition((data.window.getSize().x - title.getLocalBounds().width) / 2, 70);
    data.window.draw(title);

    // Affichage des �l�ments du menu
    for (const auto& item : data.menuItems) {
        data.window.draw(item);
    }

    // Dessiner le rectangle de s�lection
    data.window.draw(data.selectionRect);
    data.window.display();
}

