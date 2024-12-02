#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

using namespace sf;
using namespace std;

// WeaponsItems class for weapon-specific items
class WeaponsItems {
private:
    string name;
    string description;
    map<string, int> stats;
    string damageType; // e.g., "Physical", "Magical", "Hybrid"
    int durability;    // Weapon durability
    Texture texture;
    Sprite sprite;

public:
    // Constructor for WeaponsItems
    WeaponsItems(const string& name, const string& description, const map<string, int>& stats, const string& spritePath, const string& damageType, int durability)
        : name(name), description(description), stats(stats), damageType(damageType), durability(durability) {
        if (!texture.loadFromFile(spritePath)) {
            cerr << "Error: Unable to load texture from " << spritePath << endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.3f, 0.3f); // Adjust size to fit inventory slots
    }

    // Getter methods for weapon details
    const string& getName() const { return name; }
    const string& getDescription() const { return description; }
    const map<string, int>& getStats() const { return stats; }
    const string& getDamageType() const { return damageType; }
    int getDurability() const { return durability; }
    const Sprite& getSprite() const { return sprite; }

    // Method to reduce durability
    void reduceDurability(int amount) {
        durability = max(0, durability - amount); // Prevent durability from going below 0
    }
};
