#pragma once
#include "Items.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

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
    bool isOpen = false;

    Items* weaponSlot = nullptr;
    Items* chestSlot = nullptr;
    Items* bootsSlot = nullptr;

    Vector2f weaponSlotPos;
    Vector2f chestSlotPos;
    Vector2f bootsSlotPos;

public:
    Inventory(size_t rows, size_t cols, Font& font)
        : rows(rows), cols(cols), font(font) {
        slotSize = 64;
        inventoryGrid.resize(rows, vector<Items*>(cols, nullptr));
        infoPanel.setSize(Vector2f(900, 150));
        infoPanel.setFillColor(Color(50, 50, 50, 200));
        infoPanel.setPosition(500, 100);
        infoText.setFont(font);
        infoText.setCharacterSize(12);
        infoText.setFillColor(Color::White);
        infoText.setPosition(infoPanel.getPosition().x + 10, infoPanel.getPosition().y + 10);
        weaponSlotPos = Vector2f(cols * slotSize + 20, 20);
        chestSlotPos = Vector2f(cols * slotSize + 20, weaponSlotPos.y + slotSize + 10);
        bootsSlotPos = Vector2f(cols * slotSize + 20, chestSlotPos.y + slotSize + 10);
    }

    void toggleInventory() {
        isOpen = !isOpen;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    void addItem(size_t row, size_t col, Items* item) {
        if (row < rows && col < cols) {
            inventoryGrid[row][col] = item;
        }
    }

    void handleMouseClick(Vector2i mousePos, RenderWindow& window) {
        if (!isOpen) return;

        if (mousePos.x >= weaponSlotPos.x && mousePos.x <= weaponSlotPos.x + slotSize &&
            mousePos.y >= weaponSlotPos.y && mousePos.y <= weaponSlotPos.y + slotSize) {
            if (selectedItem && selectedItem->isWeapon()) {
                if (weaponSlot == nullptr) {
                    weaponSlot = selectedItem;
                    for (size_t r = 0; r < rows; ++r) {
                        for (size_t c = 0; c < cols; ++c) {
                            if (inventoryGrid[r][c] == selectedItem) {
                                inventoryGrid[r][c] = nullptr;
                                break;
                            }
                        }
                    }
                    selectedItem = nullptr;
                }
                return;
            }
        }

        if (mousePos.x >= chestSlotPos.x && mousePos.x <= chestSlotPos.x + slotSize &&
            mousePos.y >= chestSlotPos.y && mousePos.y <= chestSlotPos.y + slotSize) {
            if (selectedItem && selectedItem->isChestArmor()) {
                if (chestSlot == nullptr) {
                    chestSlot = selectedItem;
                    for (size_t r = 0; r < rows; ++r) {
                        for (size_t c = 0; c < cols; ++c) {
                            if (inventoryGrid[r][c] == selectedItem) {
                                inventoryGrid[r][c] = nullptr;
                                break;
                            }
                        }
                    }
                    selectedItem = nullptr;
                }
                return;
            }
        }

        if (mousePos.x >= bootsSlotPos.x && mousePos.x <= bootsSlotPos.x + slotSize &&
            mousePos.y >= bootsSlotPos.y && mousePos.y <= bootsSlotPos.y + slotSize) {
            if (selectedItem && selectedItem->isBoots()) { 
                if (bootsSlot == nullptr) { 
                    bootsSlot = selectedItem;
                    for (size_t r = 0; r < rows; ++r) {
                        for (size_t c = 0; c < cols; ++c) {
                            if (inventoryGrid[r][c] == selectedItem) {
                                inventoryGrid[r][c] = nullptr;
                                break;
                            }
                        }
                    }
                    selectedItem = nullptr;
                }
                return;
            }
        }


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
    void unequipItem(const std::string& slotType) {
        if (!isOpen) return;

        Items* itemToUnequip = nullptr;

        if (slotType == "Weapon" && weaponSlot != nullptr) {
            itemToUnequip = weaponSlot;
            weaponSlot = nullptr;
        }
        else if (slotType == "ChestArmor" && chestSlot != nullptr) {
            itemToUnequip = chestSlot;
            chestSlot = nullptr;
        }
        else if (slotType == "Boots" && bootsSlot != nullptr) {
            itemToUnequip = bootsSlot;
            bootsSlot = nullptr;
        }

        if (itemToUnequip == nullptr) return;

        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                if (inventoryGrid[row][col] == nullptr) {
                    inventoryGrid[row][col] = itemToUnequip;
                    return;
                }
            }
        }

        selectedItem = itemToUnequip;
    }
    // Draw equipment slots like weapon, chest, boots with checks
    void drawEquipmentSlot(RenderWindow& window, Vector2f position, Items* item, const string& label) {
        RectangleShape slot(Vector2f(slotSize - 5, slotSize - 5));
        slot.setPosition(position);
        slot.setFillColor(Color(50, 50, 50));
        slot.setOutlineColor(Color::Yellow);
        slot.setOutlineThickness(2);
        window.draw(slot);

        if (item) {
            Sprite sprite = item->getSprite();
            sprite.setPosition(position);
            window.draw(sprite);
        }

        // Draw label
        Text text;
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(Color::White);
        text.setString(label);
        text.setPosition(position.x, position.y - 15);
        window.draw(text);
    }

    // Draw the entire inventory
    void draw(RenderWindow& window) {
        if (!isOpen) return;

        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                RectangleShape slot(Vector2f(slotSize - 5, slotSize - 5));
                slot.setPosition(col * slotSize, row * slotSize);
                slot.setFillColor(Color(90, 100, 69));
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
        drawEquipmentSlot(window, weaponSlotPos, weaponSlot, "Weapon");
        drawEquipmentSlot(window, chestSlotPos, chestSlot, "ChestArmor");
        drawEquipmentSlot(window, bootsSlotPos, bootsSlot, "Boots");

        if (selectedItem) {
            Sprite sprite = selectedItem->getSprite();
            sprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(sprite);
        }

        // Show item info
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
