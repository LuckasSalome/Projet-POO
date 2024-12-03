#pragma once

#include "Weapon.hpp"

class ScepterSyntactic : public Weapon {
public:
    ScepterSyntactic()
        : Weapon("Sceptre de la Sup�riorit� Syntaxique",
            "Ce sceptre est digne des grands syntaxeurs, il permet de \nconna�tre toutes les syntaxes et de ne plus se tromper une fois en main",
            { {"ATT", 40}, {"Poids", 1} },
            "images/ScepterSyntactic.png") {}
};
