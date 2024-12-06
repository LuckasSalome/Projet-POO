#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
using namespace sf;
using namespace std;

class Items {
protected:
    string name;
    string description;
    map<string, int> stats;
    Texture texture;
    Sprite sprite;

public:
    Items(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        : name(name), description(description), stats(stats) {
        if (!texture.loadFromFile(spritePath)) {
            cerr << "Error: Unable to load texture from " << spritePath << endl;
        }
        sprite.setTexture(texture);
        sprite.setScale(0.3f, 0.3f);
    }

    virtual ~Items() = default;

    virtual bool isChestArmor() const { 
        return false; 
    }

    virtual bool isBoots() const { 
        return false; 
    }

    virtual bool isWeapon() const { 
        return false; 
    }

    const string& getName() const { 
        return name; 
    }

    const string& getDescription() const { 
        return description; 
    }

    const map<string, int>& getStats() const { 
        return stats; 
    }

    const Sprite& getSprite() const { 
        return sprite; 
    }
};
