#pragma once

#include "Items.hpp"

class Boots : public Items {
public:
    Boots(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        : Items(name, description, stats, spritePath) {}

    bool isBoots() const override { 
        return true; 
    }
};
