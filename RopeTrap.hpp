#pragma once

#include "Items.hpp"

class RopeTrap : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    RopeTrap() : name("Piege a corde"), description("Cette corde fut tressees a l'aide de poils de torse de troll, elle permet de bloquer le tour suivant de son adversaire") {
        stats["Poids"] = 2;
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
