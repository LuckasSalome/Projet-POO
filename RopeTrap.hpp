#pragma once

#include "Items.hpp"


class RopeTrap : public Items {
public:
    RopeTrap()
        : Items("Piege à corde",
            "Cette corde fut tressée à l'aide de poils de torse de troll, \nelle permet de bloquer le tour suivant de son adversaire",
            { {"Poids", 2} },
            "images/RopeTrap.png") {}
};
