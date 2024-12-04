#pragma once

#include "Items.hpp"

class BeerPotion : public Items {
public:
    BeerPotion()
        : Items("Potion de bi�re",
            "Une potion brass�e depuis deux ann�es par les moines d'un village pas loin dans l'abbaye Saint Vergeron",
            { {"AD", -5}, {"FO", 10}, {"Poids", 1} },
            "images/BeerPotion.png") {}
};
