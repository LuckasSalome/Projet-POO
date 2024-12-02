#pragma once

#include "Items.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "WeaponsItems.hpp"

using namespace sf;
using namespace std;

class Inventory {
private:
    size_t rows, cols;
    size_t slotSize;
    vector<vector<Items*>> inventoryGrid;
    Items* selectedItem = nullptr;
    Font& font;

    RectangleShape infoPanel;
    Text infoText;

public:
    Inventory(size_t rows, size_t cols, Font& font)
        : rows(rows), cols(cols), font(font) {
        slotSize = 64; 
        inventoryGrid.resize(rows, vector<Items*>(cols, nullptr));

        infoPanel.setSize(Vector2f(300, 150));
        infoPanel.setFillColor(Color(50, 50, 50, 200));
        infoPanel.setPosition(500, 100);

        infoText.setFont(font);
        infoText.setCharacterSize(14);
        infoText.setFillColor(Color::White);
        infoText.setPosition(infoPanel.getPosition().x + 10, infoPanel.getPosition().y + 10);
    }

    void addItem(size_t row, size_t col, Items* item) {
        if (row < rows && col < cols) {
            inventoryGrid[row][col] = item;
        }
    }

    void handleMouseClick(Vector2i mousePos) {
        size_t row = mousePos.y / slotSize;
        size_t col = mousePos.x / slotSize;

        if (row < rows && col < cols) {
            if (selectedItem) {
                std::swap(inventoryGrid[row][col], selectedItem);
            }
            else if (inventoryGrid[row][col]) {
                selectedItem = inventoryGrid[row][col];
                inventoryGrid[row][col] = nullptr;
            }
        }
    }

    void draw(RenderWindow& window) {
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                RectangleShape slot(Vector2f(slotSize - 2, slotSize - 2));
                slot.setPosition(col * slotSize, row * slotSize);
                slot.setFillColor(Color(100, 100, 100));
                slot.setOutlineColor(Color::Black);
                slot.setOutlineThickness(2);
                window.draw(slot);

                if (inventoryGrid[row][col]) {
                    Sprite sprite = inventoryGrid[row][col]->getSprite();
                    sprite.setPosition(col * slotSize, row * slotSize);
                    window.draw(sprite);
                }
            }
        }

        if (selectedItem) {
            Sprite sprite = selectedItem->getSprite();
            sprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(sprite);
        }

        Vector2i mousePos = Mouse::getPosition(window);
        size_t row = mousePos.y / slotSize;
        size_t col = mousePos.x / slotSize;

        if (row < rows && col < cols && inventoryGrid[row][col]) {
            Items* hoveredItem = inventoryGrid[row][col];
            string info = "Name: " + hoveredItem->getName() + "\n" +
                "Description: " + hoveredItem->getDescription() + "\nStats:\n";

            for (const auto& stat : hoveredItem->getStats()) {
                info += " - " + stat.first + ": " + to_string(stat.second) + "\n";
            }

            infoText.setString(info);
            window.draw(infoPanel);
            window.draw(infoText);
        }
    }


};
