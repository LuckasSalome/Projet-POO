// SpecialTeleporteur.hpp
#pragma once
#include "teleporteur.h"

class SpecialTeleporteur : public Teleporteur
{
public:
    SpecialTeleporteur(float coordonneeXduTP, float coordonneeYduTP, float coordonneeXArrivee, float coordonneeYArrivee, sf::Texture* texture)
        : Teleporteur(coordonneeXduTP, coordonneeYduTP, coordonneeXArrivee, coordonneeYArrivee, texture)
    {
    }

    virtual bool conditionRemplie() const override {
        // Condition : la touche Numpad0 est pressée
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0);
    }
};
