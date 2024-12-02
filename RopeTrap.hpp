#pragma once

#include "Items.hpp"

// RopeTrap class inherits from Items
class RopeTrap : public Items {
public:
    // Constructor initializes with specific values for this item
    RopeTrap()
        : Items("Piege à corde",
            "Cette corde fut tressée à l'aide de poils de torse de troll, elle permet de bloquer le tour suivant de son adversaire",
            { {"Poids", 2} },
            "images/RopeTrap.png") {}
};
