#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.hpp"

class Chest {
private:
    Texture chestTexture;
    Sprite chestSprite;
    bool isOpen;
    Inventory* chestInventory;
    FloatRect chestBounds;

public:
    Chest(float x, float y, size_t rows, size_t cols, Font& font, const std::string& texturePath)
        : isOpen(false) {
        if (!chestTexture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load chest texture!");
        }
        chestSprite.setTexture(chestTexture);
        chestSprite.setPosition(x, y);
        chestBounds = chestSprite.getGlobalBounds();
        chestInventory = new Inventory(rows, cols, font);
    }

    ~Chest() {
        delete chestInventory;
    }

    void draw(RenderWindow& window) {
        window.draw(chestSprite);
        if (isOpen) {
            chestInventory->draw(window);
        }
    }

    void toggleChest() {
        isOpen = !isOpen;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    FloatRect getBounds() const {
        return chestBounds;
    }

    Inventory* getInventory() {
        return chestInventory;
    }

    Sprite& getSprite() {
        return chestSprite;
    }
};