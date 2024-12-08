#pragma once

#include "Boots.hpp"

class LeatherBoots : public Boots {
private : 
	std::map<std::string, int> stat = { {"CHA", 2}, {"Poids", 2} };
public:
    LeatherBoots()
        : Boots("Chausson de cuire",
            "Des chaussons tressés par des nains du Pays lointain de shi-in",
            { {"CHA", 2}, {"Poids", 2} },
            "images/LeatherBoots.png") {};
};
