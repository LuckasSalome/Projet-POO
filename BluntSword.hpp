#pragma once

#include "Weapon.hpp"


class BluntSword : public Weapon {
private : 
	std::map<std::string, int> stat = { {"ATT", 10}, {"Poids", 5} };
public:
    BluntSword()
        : Weapon("Epee émoussée",
            "Une épée faiblarde qui à besoin d'être aiguisée",
            { {"ATT", 10}, {"Poids", 5} },
            "images/BluntSword.png") {};
};
