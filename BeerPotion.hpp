#pragma once

#include "Items.hpp"

class BeerPotion : public Items {
public:
    BeerPotion()
        : Items("Potion de bière",
            "Une potion brassée depuis deux années par les moines d'un village pas loin dans l'abbaye Saint Vergeron",
            { {"AD", -5}, {"FO", 10}, {"Poids", 1} },
            "images/BeerPotion.png") {}
};
