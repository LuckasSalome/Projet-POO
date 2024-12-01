#pragma once
#include "SFML/Graphics.hpp"

class Sol {
public:
    Sol(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture);

    void Draw(sf::RenderWindow& window) const;

	sf::FloatRect GetBounds() const; //FloatRect permet de d�finir une zone rectangulaire avec des coordonn�es � virgule flottante

private:
    sf::RectangleShape body;
};
