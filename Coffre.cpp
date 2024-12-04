#include "Coffre.h"
#include "Wall.h"
#include "Sol.h"
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>

Coffre::Coffre(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : animation(texture, imageCount, switchTime), isOpen(false), eKeyPressed(false), showMessage(false), dumbness(0) // Initialisation de showMessage à false
{
    this->texture = texture;
    body.setSize(size);
    body.setPosition(position);
    body.setTexture(texture);
}

Coffre::~Coffre() {}

void Coffre::ouvrir() {
    if (!isOpen) {
        showMessage = true; // Marquer le message comme devant être affiché
    }
    else {
        std::cout << "Le coffre est déjà vide..." << std::endl;
    }
}

void Coffre::drawMessage(sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols, const Player& player) const
{
    if (!isOpen) {
        sf::Texture* transitionTexture = new sf::Texture();
        if (!transitionTexture->loadFromFile("transition.png")) {
            std::cerr << "Erreur lors du chargement de la texture de transition" << std::endl;
            return;
        }
        const_cast<sf::RectangleShape&>(body).setTexture(transitionTexture);

        window.draw(body);
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        sf::Texture* openTexture = new sf::Texture();
        if (!openTexture->loadFromFile("open_full.png")) {
            std::cerr << "Erreur lors du chargement de la texture du coffre ouvert" << std::endl;
            return;
        }
        const_cast<sf::RectangleShape&>(body).setTexture(openTexture);

        window.draw(body);
        window.display();
    }

    std::string fullMessage;
    if (!isOpen) {
        fullMessage = "Le coffre contient :";
        for (const auto& obj : objets) {
            fullMessage += "\n- " + obj;
        }
    }
    else {
        switch (dumbness) {
        case 0:
            fullMessage = "Le coffre est déjà vide...";
            break;
        case 1:
            fullMessage = "Je t'ai dit, il est vide.";
            break;
        case 2:
            fullMessage = "Toujours vide...";
            break;
        case 3:
            fullMessage = "Pourquoi tu continues à vérifier ?";
            break;
        case 4:
            fullMessage = "Tu n'as rien de mieux à faire ? ...";
            break;
        case 5:
            fullMessage = "Je commence à me lasser...";
            break;
        case 6:
            fullMessage = "Tu es vraiment têtu...";
            break;
        case 7:
            fullMessage = "Je ne te le dirai plus...";
            break;
        case 8:
            fullMessage = "...";
            break;
        case 9:
            fullMessage = "La prochaine fois je ferme le jeu!";
            break;
        case 10:
            window.close();
            break;
        default:
            fullMessage = "Le coffre est toujours vide.";
            break;
        }
        if (dumbness < 10) {
            const_cast<int&>(dumbness)++;
        }
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(fullMessage);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text.getLocalBounds();
    sf::RectangleShape background(sf::Vector2f(textBounds.width + 30.0f, textBounds.height + 250.0f));
    background.setFillColor(sf::Color::Black);
    background.setPosition(body.getPosition().x - textBounds.width / 2.0f - 10.0f, body.getPosition().y - body.getSize().y / 1.5f - textBounds.height - 30.0f);
    text.setPosition(background.getPosition().x + 10.0f, background.getPosition().y + 5.0f);

    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Utiliser const_cast pour contourner la constance et modifier les membres
                const_cast<bool&>(isOpen) = true; // Marquer le coffre comme ouvert après que le message a été affiché
                sf::Texture* openTexture = new sf::Texture();
                if (!openTexture->loadFromFile("open_empty.png")) {
                    std::cerr << "Erreur lors du chargement de la texture du coffre ouvert" << std::endl;
                }
                const_cast<Coffre*>(this)->setTexture(openTexture); // Changer la texture du coffre
                const_cast<bool&>(showMessage) = false; // Réinitialiser l'état du message
                return;
            }
        }

        // Dessiner le rectangle noir et le texte par-dessus la scène existante
        window.draw(background);
        window.draw(text);
        window.display();
    }
}

bool Coffre::shouldShowMessage() const {
    return showMessage;
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

void Coffre::setTexture(sf::Texture* newTexture) {
    body.setTexture(newTexture);
}

bool Coffre::isEKeyPressed() const {
    return eKeyPressed;
}

void Coffre::setEKeyPressed(bool state) {
    eKeyPressed = state;
}
