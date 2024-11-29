#pragma once

#include "Items.hpp"

class KeyCorridor : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    KeyCorridor() : name("Cle du Corridor des Malentendus"), description("Une cle permettant l'acces au Corridor des personnes sourdes") {
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
