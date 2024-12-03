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
    float verticalSpacing = menuHeight / 4;  // Ajusté pour 3 éléments + un espace
    for (int i = 0; i < 3; ++i) {
        data.menuItems[i].setFont(data.font);
        data.menuItems[i].setString(items[i]);
        data.menuItems[i].setCharacterSize(24);
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
            if (event.key.code == data.upKey) {
                data.currentSelection = (data.currentSelection - 1 + 3) % 3;  // Gestion circulaire
            }
            else if (event.key.code == data.downKey) {
                data.currentSelection = (data.currentSelection + 1) % 3;  // Gestion circulaire
            }
            else if (event.key.code == data.actionKey) {
                switch (data.currentSelection) {
                case 0: std::cout << "New Game selected" << std::endl; break;
                case 1: inOptionsMenu = true; break;
                case 2: data.window.close(); break;
                }
            }
            // Mettre à jour le rectangle de sélection
            FloatRect bounds = data.menuItems[data.currentSelection].getGlobalBounds();
            data.selectionRect.setSize(Vector2f(bounds.width + 20, bounds.height + 10));
            data.selectionRect.setPosition(bounds.left - 10, bounds.top - 5);
        }
    }
}

void renderMainMenu(GameData& data) {
    data.window.clear();
    data.window.draw(data.background);
    data.window.draw(data.menuRect);
    for (const auto& item : data.menuItems) {
        data.window.draw(item);
    }
    data.window.draw(data.selectionRect);
    data.window.display();
}