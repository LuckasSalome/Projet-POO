#pragma once

#include "Boots.hpp"

class SorcererBoots : public Boots {
private : 
	std::map<std::string, int> stat = { {"FO", 2}, {"Poids", 2} };
public:
    SorcererBoots()
        : Boots("Chausson de sorcier",
            "+15 magique p�n�tration, +45 vitesse de d�placement",
            { {"FO", 2}, {"Poids", 2} },
            "images/SorcererBoots.png") {};
};
