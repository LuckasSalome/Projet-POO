#pragma once

#include "Items.hpp"

class BluntSword : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    BluntSword() : name("Epee emoussee"), description("Une epee faiblarde qui a besoin d'etre aiguisee ") {
        stats["ATT"] = 10;
        stats["Poids"] = 5;
    }

    string getNameItem() const override {
        return name;
    }

    string getDescItem() const override {
        return description;
    }

    map<string, int> getStatItem() const override {
        return stats;
    }
};
