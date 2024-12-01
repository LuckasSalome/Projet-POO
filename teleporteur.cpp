// teleporteur.cpp
#include "Player.h"
#include "Wall.h"
#include "teleporteur.h"

Teleporteur::Teleporteur(float coordonneeXduTP, float coordonneeYduTP, float coordonneeXArrivee, float coordonneeYArrivee, sf::Texture* texture)
    : coordonneeXduTP(coordonneeXduTP), coordonneeYduTP(coordonneeYduTP), coordonneeXArrivee(coordonneeXArrivee), coordonneeYArrivee(coordonneeYArrivee), texture(texture)
{
	body.setSize(sf::Vector2f(250.0f, 250.0f)); //taille du teleporteur png original = 500 * 500
    body.setPosition(coordonneeXduTP, coordonneeYduTP);
    body.setTexture(texture);
}

Teleporteur::~Teleporteur() {}

void Teleporteur::draw(sf::RenderWindow& window) const {
    if (conditionRemplie()) {
        window.draw(body);
    }
}

bool Teleporteur::checkCollision(const Player& player) const {
    return body.getGlobalBounds().intersects(player.GetBounds());
}

sf::Vector2f Teleporteur::getArrivalPosition() const {
    return sf::Vector2f(coordonneeXArrivee, coordonneeYArrivee);
}
