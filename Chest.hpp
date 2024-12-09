#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.hpp"

class Chest {
private:
    sf::RectangleShape chest;
    sf::Vector2f position;
    bool isOpen;
    sf::FloatRect detectionZone;
    Inventory* inventory;
    sf::Texture chestTexOpen;
    sf::Texture chestTexClosed;

public:
    Chest(sf::Vector2f pos, Inventory* inv)
        : position(pos), isOpen(false), inventory(inv) {
        detectionZone = sf::FloatRect(position.x - 125.f, position.y - 125.f, 250, 250); // Zone de détection autour du coffre

        // Initialiser la forme du coffre avec une taille appropriée
        chest.setSize(sf::Vector2f(100.f, 100.f));
        chest.setPosition(this->position);

        // Charger les textures
        if (!chestTexOpen.loadFromFile("Assets/Chest.png"))
            throw std::runtime_error("Cannot load Assets/Chest.png");
        if (!chestTexClosed.loadFromFile("Assets/chestclosed.png"))
            throw std::runtime_error("Cannot load Assets/closedchest.png");

        // Appliquer la texture fermée par défaut
        chest.setTexture(&chestTexClosed);
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
            chest.setTexture(&chestTexOpen);
            inventory->toggleSecondaryGrid();
        }
        else {
            chest.setTexture(&chestTexClosed);
            inventory->toggleSecondaryGrid(); // Fermer la secondaryGrid si le coffre est fermé
        }
    }


    bool isPlayerInRange(const sf::Vector2f& playerPos) const {
        return detectionZone.contains(playerPos);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(chest);
    }
};
