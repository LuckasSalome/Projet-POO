#pragma once

#include "Items.hpp"

class ChestArmor : public Items {
public:
    ChestArmor(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        : Items(name, description, stats, spritePath) {}

    bool isChestArmor() const override { 
        return true; 
    }
};
