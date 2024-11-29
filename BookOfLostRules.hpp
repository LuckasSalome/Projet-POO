#pragma once

#include "Items.hpp"

class BookOfLostRules : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    BookOfLostRules() : name("Livre des regles perdues"), description("Un livre renfermant les regles du fight club") {
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
