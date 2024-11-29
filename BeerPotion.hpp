#pragma once

#include "Items.hpp"

class BeerPotion : Items {
private:
		
	string name;
	string description;
	map <string, int> stats;

public:
    BeerPotion() : name("Potion de bière"), description("Une potion brassée depuis deux années par les moines d'un village pas loin dans l'abbaye Saint Vergeron") {
        stats["AD"] = -5;                                            
        stats["FO"] = 10;
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


