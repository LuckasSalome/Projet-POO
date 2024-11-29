#pragma once

#include "Items.hpp"

class MajorHealingPotion : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    MajorHealingPotion() : name("Potion de soin majeur"), description("Une potion digne des plus grands, confectionner à partir de jus de mirabelle, elle restaure une grande quantité de point de vie") {
        stats["PV"] = 50;
        stats["Poids"] = 1;
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
