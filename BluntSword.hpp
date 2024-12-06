#pragma once

#include "Weapon.hpp"


class BluntSword : public Weapon {
public:
    BluntSword()
        : Weapon("Epee émoussée",
            "Une épée faiblarde qui à besoin d'être aiguisée",
            { {"ATT", 10}, {"Poids", 5} },
            "images/BluntSword.png") {}
};
