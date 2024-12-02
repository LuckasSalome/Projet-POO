#pragma once

#include "Items.hpp"

class KeyCorridor : public Items {
public:
    KeyCorridor()
        : Items("Cl� du Corridor des Malentendus",
            "Une cl� permettant l'acc�s au Corridor des personnes sourdes",
            { {"Poids", 1} },
            "images/KeyCorridor.png") {}
};
