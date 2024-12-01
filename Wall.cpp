#include "Wall.h"

Wall::Wall(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Texture* texture)
{
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(color);
    body.setTexture(texture); 

    // Répéter la texture
    texture->setRepeated(true); //permet de répéter la texture et éviter d'avoir une image étirée, découvert en ctrl+click le LoadFromFile mdr
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


