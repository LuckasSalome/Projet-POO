#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.hpp"

class TrappedChest {
private:
    sf::RectangleShape trappedChest;
    sf::Vector2f position;
    bool isOpen;
    sf::FloatRect detectionZone;
    Inventory* inventory;
    sf::Texture trappedChestTexOpen;
    sf::Texture trappedChestTexClosed;

public:
    TrappedChest(sf::Vector2f pos, Inventory* inv)
        : position(pos), isOpen(false), inventory(inv) {
        detectionZone = sf::FloatRect(position.x - 125.f, position.y - 125.f, 250, 250); // Zone de détection autour du coffre

        // Initialiser la forme du coffre avec une taille appropriée
        trappedChest.setSize(sf::Vector2f(100.f, 100.f));
        trappedChest.setPosition(this->position);

        // Charger les textures
        if (!trappedChestTexOpen.loadFromFile("Assets/Chest.png"))
            throw std::runtime_error("Cannot load Assets/Chest.png");
        if (!trappedChestTexClosed.loadFromFile("Assets/chestclosed.png"))
            throw std::runtime_error("Cannot load Assets/closedchest.png");

        // Appliquer la texture fermée par défaut
        trappedChest.setTexture(&trappedChestTexClosed);
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    bool getIsOpen() const {
        return isOpen;
    }

    void toggleOpen() {
        isOpen = !isOpen;
        if (isOpen) {
            trappedChest.setTexture(&trappedChestTexOpen);
            
        }
        else {
            trappedChest.setTexture(&trappedChestTexClosed);
            
        }
    }


    bool isPlayerInRange(const sf::Vector2f& playerPos) const {
        return detectionZone.contains(playerPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(trappedChest);
    }
};
