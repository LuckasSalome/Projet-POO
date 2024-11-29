#pragma once 

#include "Items.hpp"

class PotionIntelligence : Items {
private:

	string name;
	string description;
	map <string, int> stats;

public:

    PotionIntelligence() : name("Potion d'intelligence discutable"), description("Cet elixir provient d'une cave de mestre nommé epstein, on pense donc qu'elle rend intelligent ") {
        stats["COU"] = 2;
        stats["CHA"] = 2;
        stats["AD"] = 2;
        stats["FO"] = 2;
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
