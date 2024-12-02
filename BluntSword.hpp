#pragma once

#include "Items.hpp"

class BluntSword : public Items {
public:
    BluntSword()
        : Items("Epee émoussée",
            "Une épée faiblarde qui a besoin d'être aiguisée",
            { {"ATT", 10}, {"Poids", 5} },
            "images/BluntSword.png") {}
};
