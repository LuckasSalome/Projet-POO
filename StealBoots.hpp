#pragma once

#include "Boots.hpp"

class StealBoots : public Boots {
public:
    StealBoots()
        : Boots("Chausson de fer",
            "Des chaussons en fer pour faire l'affaire",
            { {"FO", 2}, {"Poids", 2} },
            "images/StealBoots.png") {}
};
