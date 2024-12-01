#pragma once
#include "SFML/Graphics.hpp"

class Wall
{
public:
    Wall(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Texture* texture);
    void Draw(sf::RenderWindow& window) const;
    sf::FloatRect GetBounds() const;

private:
    sf::RectangleShape body;
};


