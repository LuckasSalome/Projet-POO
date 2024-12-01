#pragma once
#include "SFML/Graphics.hpp"

class Sol {
public:
    Sol(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture);

    void Draw(sf::RenderWindow& window) const;

	sf::FloatRect GetBounds() const; //FloatRect permet de définir une zone rectangulaire avec des coordonnées à virgule flottante

private:
    sf::RectangleShape body;
};
