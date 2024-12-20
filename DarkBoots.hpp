#pragma once

#include "Boots.hpp"

class DarkBoots : public Boots {
private : 
	std::map<std::string, int> stat = { {"AD", 2}, {"Poids", 1} };
public:
    DarkBoots()
        : Boots("Chausson sombre",
            "Des chaussons sombre et l�ger, ils sont con�u pour ne faire aucun bruit",
            { {"AD", 2}, {"Poids", 1} },
            "images/DarkBoots.png") {};
};
