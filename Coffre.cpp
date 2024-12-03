#include "Coffre.h"
#include "Wall.h"
#include "Sol.h"
#include <iostream>

Coffre::Coffre(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : animation(texture, imageCount, switchTime)
{
    this->texture = texture;
    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
}

Coffre::~Coffre() {}

void Coffre::ouvrir() {
    std::cout << "Le coffre contient : " << std::endl;
    for (const auto& objet : objets) {
        std::cout << "- " << objet << std::endl;
    }
}

void Coffre::drawMessage(sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols, const Player& player) const
{
    std::string fullMessage = "Le coffre contient :";
    for (const auto& obj : objets) {
        fullMessage += "\n- " + obj;
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(fullMessage);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::RectangleShape background(sf::Vector2f(textBounds.width + 20, textBounds.height + 20));
    background.setFillColor(sf::Color::Black);
    background.setPosition(body.getPosition().x - textBounds.width / 2 - 10, body.getPosition().y - body.getSize().y / 2 - textBounds.height - 30);
    text.setPosition(background.getPosition().x + 10, background.getPosition().y + 10);

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

        // Dessiner le rectangle noir et le texte par-dessus la scène existante
        window.draw(background);
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

std::vector<std::string> Coffre::getObjets() const {
    return objets;
}

void Coffre::addObjet(const std::string& objet) {
    objets.push_back(objet);
}


