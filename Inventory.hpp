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
    vector<vector<Items*>> secondaryGrid;  
    size_t secondaryRows, secondaryCols;
    Items* selectedItem = nullptr;
    Font& font;
    RectangleShape infoPanel;
    Text infoText;
    bool isOpenInv = false;
    bool isOpenChest = false;
    bool isSecondaryGridVisible = false;

    Items* weaponSlot = nullptr;
    Items* chestSlot = nullptr;
    Items* bootsSlot = nullptr;

    Vector2f weaponSlotPos;
    Vector2f chestSlotPos;
    Vector2f bootsSlotPos;

    Items* weaponSlot2 = nullptr;
    Items* chestSlot2 = nullptr;
    Items* bootsSlot2 = nullptr;

    Vector2f weaponSlot2Pos;
    Vector2f chestSlot2Pos;
    Vector2f bootsSlot2Pos;

    Items* weaponSlot3 = nullptr;
    Items* chestSlot3 = nullptr;
    Items* bootsSlot3 = nullptr;

    Vector2f weaponSlot3Pos;
    Vector2f chestSlot3Pos;
    Vector2f bootsSlot3Pos;

    Items* weaponSlot4 = nullptr;
    Items* chestSlot4 = nullptr;
    Items* bootsSlot4 = nullptr;

    Vector2f weaponSlot4Pos;
    Vector2f chestSlot4Pos;
    Vector2f bootsSlot4Pos;

public:
	Inventory(size_t rows, size_t cols, Font& font)                          //constructeur avec les parametres visuels
        : rows(rows), cols(cols), font(font), weaponSlot(nullptr), chestSlot(nullptr), bootsSlot(nullptr) {
        slotSize = 64;
        inventoryGrid.resize(rows, vector<Items*>(cols, nullptr));
        secondaryRows = 3;
        secondaryCols = 3;
        secondaryGrid.resize(secondaryRows, vector<Items*>(secondaryCols, nullptr));
        infoPanel.setSize(Vector2f(1100, 300));
        infoPanel.setFillColor(Color(50, 50, 50, 200));
        infoPanel.setPosition(500, 100);
        infoText.setFont(font);
        infoText.setCharacterSize(26);
        infoText.setFillColor(Color::White);
        infoText.setPosition(infoPanel.getPosition().x + 10, infoPanel.getPosition().y + 10);
        weaponSlotPos = Vector2f(static_cast<float>(cols * slotSize + 20), 20);
        chestSlotPos = Vector2f(cols * slotSize + 20, weaponSlotPos.y + slotSize + 10);
        bootsSlotPos = Vector2f(cols * slotSize + 20, chestSlotPos.y + slotSize + 10);
        weaponSlot2Pos = Vector2f(cols * slotSize + 20 + slotSize * 2, 20);
        chestSlot2Pos = Vector2f(cols * slotSize + 20 + slotSize * 2, weaponSlot2Pos.y + slotSize + 10);
        bootsSlot2Pos = Vector2f(cols * slotSize + 20 + slotSize * 2, chestSlot2Pos.y + slotSize + 10);
        weaponSlot3Pos = Vector2f(cols * slotSize + 20 + slotSize * 3, 20);
        chestSlot3Pos = Vector2f(cols * slotSize + 20 + slotSize * 3, weaponSlot2Pos.y + slotSize + 10);
        bootsSlot3Pos = Vector2f(cols * slotSize + 20 + slotSize * 3, chestSlot2Pos.y + slotSize + 10);
        weaponSlot4Pos = Vector2f(cols * slotSize + 20 + slotSize * 4, 20);
        chestSlot4Pos = Vector2f(cols * slotSize + 20 + slotSize * 4, weaponSlot2Pos.y + slotSize + 10);
        bootsSlot4Pos = Vector2f(cols * slotSize + 20 + slotSize * 4, chestSlot2Pos.y + slotSize + 10);
    }


	void toggleInventory() {            //change l'etat de l'inventaire
        isOpenInv = !isOpenInv;
    }
    
    void toggleChest() {            //change l'etat de l'inventaire
        isOpenChest = !isOpenChest;
    }

	bool getIsOpen() const {            //retourne l'etat de l'inventaire
        return isOpenInv;
    }

	void toggleSecondaryGrid() {        //change l'etat de la grille secondaire

        if (isOpenChest) return;

        isSecondaryGridVisible = !isSecondaryGridVisible;
    }


	bool getIsSecondaryGridVisible() const {	//retourne l'etat de la grille secondaire
        return isSecondaryGridVisible;
    }

	void addItem(size_t row, size_t col, Items* item) {	    //ajoute un item dans l'inventaire à une position donnée
        if (row < rows && col < cols) {
            inventoryGrid[row][col] = item;
        }
    }

	void handleMouseClick(Vector2i mousePos, RenderWindow& window) {	    //gere les clics de la souris et le drag and drop des items dans les cases
        if (!isOpenInv && !isOpenChest) return;        //si l'inventaire est ouvert

        //regarde si l'item est dans la case d'arme ou s'il correspond
		if (mousePos.x >= weaponSlotPos.x && mousePos.x <= weaponSlotPos.x + slotSize && mousePos.y >= weaponSlotPos.y && mousePos.y <= weaponSlotPos.y + slotSize) { 
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
        //regarde si l'item est dans la case plastron et s'il correspond
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
		//regarde si l'item est dans la case bottes et s'il correspond
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
        if (mousePos.x >= weaponSlot2Pos.x && mousePos.x <= weaponSlot2Pos.x + slotSize &&
            mousePos.y >= weaponSlot2Pos.y && mousePos.y <= weaponSlot2Pos.y + slotSize) {
            if (selectedItem && selectedItem->isWeapon()) {
                if (weaponSlot2 == nullptr) {
                    weaponSlot2 = selectedItem;
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
        if (mousePos.x >= chestSlot2Pos.x && mousePos.x <= chestSlot2Pos.x + slotSize &&
            mousePos.y >= chestSlot2Pos.y && mousePos.y <= chestSlot2Pos.y + slotSize) {
            if (selectedItem && selectedItem->isChestArmor()) {
                if (chestSlot2 == nullptr) {
                    chestSlot2 = selectedItem;
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
        if (mousePos.x >= bootsSlot2Pos.x && mousePos.x <= bootsSlot2Pos.x + slotSize &&
            mousePos.y >= bootsSlot2Pos.y && mousePos.y <= bootsSlot2Pos.y + slotSize) {
            if (selectedItem && selectedItem->isBoots()) {
                if (bootsSlot2 == nullptr) {
                    bootsSlot2 = selectedItem;
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

        if (mousePos.x >= weaponSlot3Pos.x && mousePos.x <= weaponSlot3Pos.x + slotSize &&
            mousePos.y >= weaponSlot3Pos.y && mousePos.y <= weaponSlot3Pos.y + slotSize) {
            if (selectedItem && selectedItem->isWeapon()) {
                if (weaponSlot3 == nullptr) {
                    weaponSlot3 = selectedItem;
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
        if (mousePos.x >= chestSlot3Pos.x && mousePos.x <= chestSlot3Pos.x + slotSize &&
            mousePos.y >= chestSlot3Pos.y && mousePos.y <= chestSlot3Pos.y + slotSize) {
            if (selectedItem && selectedItem->isChestArmor()) {
                if (chestSlot3 == nullptr) {
                    chestSlot3 = selectedItem;
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
        if (mousePos.x >= bootsSlot3Pos.x && mousePos.x <= bootsSlot3Pos.x + slotSize &&
            mousePos.y >= bootsSlot3Pos.y && mousePos.y <= bootsSlot3Pos.y + slotSize) {
            if (selectedItem && selectedItem->isBoots()) {
                if (bootsSlot3 == nullptr) {
                    bootsSlot3 = selectedItem;
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

        if (mousePos.x >= weaponSlot4Pos.x && mousePos.x <= weaponSlot4Pos.x + slotSize &&
            mousePos.y >= weaponSlot4Pos.y && mousePos.y <= weaponSlot4Pos.y + slotSize) {
            if (selectedItem && selectedItem->isWeapon()) {
                if (weaponSlot4 == nullptr) {
                    weaponSlot4 = selectedItem;
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
        if (mousePos.x >= chestSlot4Pos.x && mousePos.x <= chestSlot4Pos.x + slotSize &&
            mousePos.y >= chestSlot4Pos.y && mousePos.y <= chestSlot4Pos.y + slotSize) {
            if (selectedItem && selectedItem->isChestArmor()) {
                if (chestSlot4 == nullptr) {
                    chestSlot4 = selectedItem;
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
        if (mousePos.x >= bootsSlot4Pos.x && mousePos.x <= bootsSlot4Pos.x + slotSize &&
            mousePos.y >= bootsSlot4Pos.y && mousePos.y <= bootsSlot4Pos.y + slotSize) {
            if (selectedItem && selectedItem->isBoots()) {
                if (bootsSlot4 == nullptr) {
                    bootsSlot4 = selectedItem;
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

		//gère le drag and drop des items entre l'inventaire principal et la grille secondaire
        size_t row = mousePos.y / slotSize;
        size_t col = mousePos.x / slotSize;
        if (row < rows && col < cols) {
            if (selectedItem) {
                swap(inventoryGrid[row][col], selectedItem);
            }
            else if (inventoryGrid[row][col]) {
                selectedItem = inventoryGrid[row][col];
                inventoryGrid[row][col] = nullptr;
            }
            return;
        }
        Vector2f secondaryGridOffset(cols * slotSize + 20,
            weaponSlotPos.y + slotSize * 4);
        row = (mousePos.y - secondaryGridOffset.y) / slotSize;
        col = (mousePos.x - secondaryGridOffset.x) / slotSize;

        if (row < secondaryRows && col < secondaryCols) {
            if (selectedItem) {
                swap(secondaryGrid[row][col], selectedItem);
            }
            else if (secondaryGrid[row][col]) {
                selectedItem = secondaryGrid[row][col];
                secondaryGrid[row][col] = nullptr;
            }
        }
    }


	void unequipItem(const string& slotType) {		//desequipe un item dans armes, plastron ou bottes
        if (!isOpenInv && !isOpenChest) return;

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

        if (slotType == "Weapon 2" && weaponSlot2 != nullptr) {
            itemToUnequip = weaponSlot2;
            weaponSlot2 = nullptr;
        }
        else if (slotType == "ChestArmor 2" && chestSlot2 != nullptr) {
            itemToUnequip = chestSlot2;
            chestSlot2 = nullptr;
        }
        else if (slotType == "Boots 2" && bootsSlot2 != nullptr) {
            itemToUnequip = bootsSlot2;
            bootsSlot2 = nullptr;
        }

        if (slotType == "Weapon 3" && weaponSlot3 != nullptr) {
            itemToUnequip = weaponSlot3;
            weaponSlot3 = nullptr;
        }
        else if (slotType == "ChestArmor 3" && chestSlot3 != nullptr) {
            itemToUnequip = chestSlot3;
            chestSlot3 = nullptr;
        }
        else if (slotType == "Boots 3" && bootsSlot3 != nullptr) {
            itemToUnequip = bootsSlot3;
            bootsSlot3 = nullptr;
        }

        if (slotType == "Weapon 4" && weaponSlot4 != nullptr) {
            itemToUnequip = weaponSlot4;
            weaponSlot4 = nullptr;
        }
        else if (slotType == "ChestArmor 4" && chestSlot4 != nullptr) {
            itemToUnequip = chestSlot4;
            chestSlot4 = nullptr;
        }
        else if (slotType == "Boots 4" && bootsSlot4 != nullptr) {
            itemToUnequip = bootsSlot4;
            bootsSlot4 = nullptr;
        }

		if (itemToUnequip == nullptr) return;       //si pas de correspondance on sort

		//accede à l'inventaire principal et ajoute l'item desequipé
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

    void drawEquipmentSlot(RenderWindow& window, Vector2f position, Items* item, const string& label) const {   //dessine les cases d'equipement de personnage
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

        Text text;
        text.setFont(font);
        text.setCharacterSize(12);
        text.setFillColor(Color::White);
        text.setString(label);
        text.setPosition(position.x, position.y - 15);
        window.draw(text);
    }
	void addSecondaryItem(size_t row, size_t col, Items* item) {		//ajoute un item dans la grille secondaire
        if (row < secondaryRows && col < secondaryCols) {
            secondaryGrid[row][col] = item;
        }
    }

	void drawSecondaryGrid(RenderWindow& window) {		            //dessine la grille secondaire
        Vector2f secondaryGridOffset(cols * slotSize + 20,
            weaponSlotPos.y + slotSize * 4);

        for (size_t row = 0; row < secondaryRows; ++row) {
            for (size_t col = 0; col < secondaryCols; ++col) {
                RectangleShape slot(Vector2f(slotSize - 5, slotSize - 5));
                slot.setPosition(secondaryGridOffset.x + col * slotSize,
                    secondaryGridOffset.y + row * slotSize);
                slot.setFillColor(Color(90, 100, 69)); 
                slot.setOutlineColor(Color::Black);
                slot.setOutlineThickness(2);
                window.draw(slot);

                if (secondaryGrid[row][col]) {
                    Sprite sprite = secondaryGrid[row][col]->getSprite();
                    sprite.setPosition(secondaryGridOffset.x + col * slotSize,
                        secondaryGridOffset.y + row * slotSize);
                    window.draw(sprite);
                }
            }
        }

        Text gridLabel;
        gridLabel.setFont(font);
        gridLabel.setCharacterSize(12);
        gridLabel.setFillColor(Color::White);
        gridLabel.setString("Secondary Grid");
        gridLabel.setPosition(secondaryGridOffset.x, secondaryGridOffset.y - 15);
        window.draw(gridLabel);
    }

    void draw(RenderWindow& window) {
        if (!isOpenInv) return;

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
        drawEquipmentSlot(window, weaponSlot2Pos, weaponSlot2, "Weapon ");
        drawEquipmentSlot(window, chestSlot2Pos, chestSlot2, "ChestArmor ");
        drawEquipmentSlot(window, bootsSlot2Pos, bootsSlot2, "Boots ");
        drawEquipmentSlot(window, weaponSlot3Pos, weaponSlot3, "Weapon ");
        drawEquipmentSlot(window, chestSlot3Pos, chestSlot3, "ChestArmor ");
        drawEquipmentSlot(window, bootsSlot3Pos, bootsSlot3, "Boots ");
        drawEquipmentSlot(window, weaponSlot4Pos, weaponSlot4, "Weapon ");
        drawEquipmentSlot(window, chestSlot4Pos, chestSlot4, "ChestArmor ");
        drawEquipmentSlot(window, bootsSlot4Pos, bootsSlot4, "Boots ");


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

    void drawChest(RenderWindow& window) {
        if (!isOpenChest) return;

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

        if (selectedItem) {
            Sprite sprite = selectedItem->getSprite();
            sprite.setPosition(static_cast<Vector2f>(Mouse::getPosition(window)));
            window.draw(sprite);
        }

        drawSecondaryGrid(window);

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

    std::map<std::string, int> getEquippedStats()  {
        std::map<std::string, int> equippedStats;

        if (this != nullptr)
        {
            // Ajoute les stats de l'arme équipée
            if (weaponSlot) {
                for (const auto& stat : weaponSlot->getStats()) {
                    equippedStats[stat.first] += stat.second;
                }
            }

            // Ajoute les stats de l'armure de poitrine équipée
            if (chestSlot) {
                for (const auto& stat : chestSlot->getStats()) {
                    equippedStats[stat.first] += stat.second;
                }
            }

            // Ajoute les stats des bottes équipées
            if (bootsSlot) {
                for (const auto& stat : bootsSlot->getStats()) {
                    equippedStats[stat.first] += stat.second;
                }
            }
        }

        return equippedStats;
    }
};
