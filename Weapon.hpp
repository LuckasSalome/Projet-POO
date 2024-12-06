#pragma once

#include "Items.hpp"

class Weapon : public Items {
public:
    Weapon(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        : Items(name, description, stats, spritePath) {}

    bool isWeapon() const override { 
        return true; 
    }
};
