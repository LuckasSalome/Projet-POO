#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>

using namespace sf;
using namespace std;

// Items base class
class Items {
protected:
    string name;
    string description;
    map<string, int> stats;
    Texture texture;
    Sprite sprite;

public:
    // Constructor with sprite path and stats initialization
    Items(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        : name(name), description(description), stats(stats) {
        if (!texture.loadFromFile(spritePath)) {
            cerr << "Error: Unable to load texture from " << spritePath << endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.3f, 0.3f); // Adjust size to fit inventory slots
    }

    // Getter methods for item details
    const string& getName() const { return name; }
    const string& getDescription() const { return description; }
    const map<string, int>& getStats() const { return stats; }
    const Sprite& getSprite() const { return sprite; }


};
