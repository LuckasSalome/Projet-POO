#pragma once

#include "Boots.hpp"

class SorcererBoots : public Boots {
public:
    SorcererBoots()
        : Boots("Chausson de sorcier",
            "+15 magique p�n�tration, +45 vitesse de d�placement",
            { {"FO", 2}, {"Poids", 2} },
            "images/SorcererBoots.png") {}
};
