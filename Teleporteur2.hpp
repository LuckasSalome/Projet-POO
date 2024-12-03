// Teleporteur2.hpp
#pragma once
#include "teleporteur.h"

class Teleporteur2 : public Teleporteur
{
public:
    Teleporteur2(float coordonneeXduTP, float coordonneeYduTP, float coordonneeXArrivee, float coordonneeYArrivee, sf::Texture* texture)
        : Teleporteur(coordonneeXduTP, coordonneeYduTP, coordonneeXArrivee, coordonneeYArrivee, texture)
    {
    }

    virtual bool conditionRemplie() const override {
        return true;
    }
};
