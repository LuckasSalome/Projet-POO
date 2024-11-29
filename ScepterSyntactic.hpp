#pragma once

#include "Items.hpp"

class ScepterSyntactic : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    ScepterSyntactic() : name("Sceptre de la Superiorite Syntaxique"), description("Ce sceptre est digne des grands syntaxeurs, il permet de connaitre toute les syntaxes et de ne plus se tromper une fois en main") {
        stats["ATT"] = 40;
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
