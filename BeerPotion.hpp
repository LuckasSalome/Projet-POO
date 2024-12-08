#pragma once

#include "Items.hpp"

class BeerPotion : public Items {
private : 
	std::map<std::string, int> stat = { {"AD", -5}, {"FO", 10}, {"Poids", 1} };
public:
    BeerPotion()
        : Items("Potion de bière",
            "Une potion brassée depuis deux années par les moines d'un village pas loin \n dans l'abbaye Saint Vergeron",
            { {"AD", -5}, {"FO", 10}, {"Poids", 1} },
            "images/BeerPotion.png") {};
};
