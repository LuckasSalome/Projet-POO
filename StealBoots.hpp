#pragma once

#include "Boots.hpp"

class StealBoots : public Boots {
private:
	std::map<std::string, int> stat = { {"FO", 2}, {"Poids", 2} };
public:
    StealBoots()
        : Boots("Chausson de fer",
            "Des chaussons en fer pour faire l'affaire",
            { {"FO", 2}, {"Poids", 2} },
            "images/StealBoots.png") {};
};
