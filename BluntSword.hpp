#pragma once

#include "Items.hpp"

class BluntSword : public Items {
public:
    BluntSword()
        : Items("Epee �mouss�e",
            "Une �p�e faiblarde qui a besoin d'�tre aiguis�e",
            { {"ATT", 10}, {"Poids", 5} },
            "images/BluntSword.png") {}
};
