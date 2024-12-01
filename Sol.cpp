#include "Sol.h"

Sol::Sol(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture) {
    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
    texture->setRepeated(true);
    body.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Sol::Draw(sf::RenderWindow& window) const {
    window.draw(body);
}

sf::FloatRect Sol::GetBounds() const {
    return body.getGlobalBounds();
}
