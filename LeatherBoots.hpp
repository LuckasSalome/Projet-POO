#pragma once

#include "Boots.hpp"

class LeatherBoots : public Boots {
public:
    LeatherBoots()
        : Boots("Chausson de cuire",
            "Des chaussons tressés par des nains du Pays lointain de shi-in",
            { {"CHA", 2}, {"Poids", 2} },
            "images/LeatherBoots.png") {}
};
