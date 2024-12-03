#include "Coffre.h"
#include <iostream>

Coffre::Coffre(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : animation(texture, imageCount, switchTime)
{
    this->texture = texture;
    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
    objet = "Nom de l'objet";
}

Coffre::~Coffre() {}

void Coffre::ouvrir() {
    std::cout << "Le coffre contient : " << objet << std::endl;
}

void Coffre::drawMessage(sf::RenderWindow& window, const std::string& message) const
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::Vector2f textPosition = body.getPosition();
    textPosition.y -= body.getSize().y / 2.0f + 30.0f;
    text.setPosition(textPosition);

    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                return;
            }
        }

        window.clear();
        window.draw(body);
        window.draw(text);
        window.display();
    }
}

void Coffre::draw(sf::RenderWindow& window) const {
    window.draw(body);
}

sf::Vector2f Coffre::GetPosition() const {
    return body.getPosition();
}

sf::FloatRect Coffre::GetBounds() const {
    return body.getGlobalBounds();
}

std::string Coffre::getObjet() const {
    return objet;
}
