#pragma once

#include "Weapon.hpp"


class BluntSword : public Weapon {
private : 
	std::map<std::string, int> stat = { {"ATT", 10}, {"Poids", 5} };
public:
    BluntSword()
        : Weapon("Epee �mouss�e",
            "Une �p�e faiblarde qui � besoin d'�tre aiguis�e",
            { {"ATT", 10}, {"Poids", 5} },
            "images/BluntSword.png") {};
};
