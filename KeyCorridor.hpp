#pragma once

#include "Items.hpp"

class KeyCorridor : public Items {
public:
    KeyCorridor()
        : Items("Clé du Corridor des Malentendus",
            "Une clé permettant l'accès au Corridor des personnes sourdes",
            { {"Poids", 1} },
            "images/KeyCorridor.png") {}
};
