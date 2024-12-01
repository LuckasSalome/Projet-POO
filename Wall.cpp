#include "Wall.h"

Wall::Wall(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Texture* texture)
{
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(color);
    body.setTexture(texture); 

    // R�p�ter la texture
    texture->setRepeated(true); //permet de r�p�ter la texture et �viter d'avoir une image �tir�e, d�couvert en ctrl+click le LoadFromFile mdr
    body.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Wall::Draw(sf::RenderWindow& window) const
{
    window.draw(body);
}

sf::FloatRect Wall::GetBounds() const
{
    return body.getGlobalBounds();
}


