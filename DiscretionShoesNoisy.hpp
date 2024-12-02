#pragma once

#include "Items.hpp"

class DiscretionShoesNoisy : Items {
private:

    string name;
    string description;
    map <string, int> stats;

public:

    DiscretionShoesNoisy() : name("Chausson de discretion bruyant"), description("Des chaussons ressemblant à ceux de votre grand-mère, ils sont doux et léger avec le dessous de la chaussure recouvert de claque doigts") {
        stats["AD"] = -2;
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
