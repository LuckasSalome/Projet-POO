#pragma once

#include "Boots.hpp"

class SorcererBoots : public Boots {
public:
    SorcererBoots()
        : Boots("Chausson de sorcier",
            "+15 magique pénétration, +45 vitesse de déplacement",
            { {"FO", 2}, {"Poids", 2} },
            "images/SorcererBoots.png") {}
};
