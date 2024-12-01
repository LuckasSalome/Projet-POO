// teleporteur.h
#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Player; // Déclaration anticipée

class Teleporteur
{
private:
    float coordonneeXduTP;
    float coordonneeYduTP;
    float coordonneeXArrivee;
    float coordonneeYArrivee;
    sf::Texture* texture;
    sf::RectangleShape body;

public:
    Teleporteur(float coordonneeXduTP, float coordonneeYduTP, float coordonneeXArrivee, float coordonneeYArrivee, sf::Texture* texture);
    virtual ~Teleporteur();

    virtual bool conditionRemplie() const = 0;
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const Player& player) const;
    sf::Vector2f getArrivalPosition() const;
};
