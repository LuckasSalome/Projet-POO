#pragma once

#include "Items.hpp"

class ScepterSyntactic : public Items {
public:
    ScepterSyntactic()
        : Items("Sceptre de la Sup�riorit� Syntaxique",
            "Ce sceptre est digne des grands syntaxeurs, il permet de conna�tre toutes les syntaxes et de ne plus se tromper une fois en main",
            { {"ATT", 40}, {"Poids", 1} },
            "images/ScepterSyntactic.png") {}
};
