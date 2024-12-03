#include "Coffre.h"
#include "Wall.h"
#include "Sol.h"
#include <iostream>

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
        std::cout << "Le coffre est deja vide..." << std::endl;
    }
}

void Coffre::drawMessage(sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols, const Player& player) const
{
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
            default:
                fullMessage = "Le coffre est toujours vide.";
                break;
            }
        if (dumbness < 8) {
            const_cast<Coffre*>(this)->dumbness++;
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
    sf::RectangleShape background(sf::Vector2f(textBounds.width + 30, textBounds.height + 100));
    background.setFillColor(sf::Color::Black);
    background.setPosition(body.getPosition().x - textBounds.width / 2 - 10, body.getPosition().y - body.getSize().y / 2 - textBounds.height - 30);
    text.setPosition(background.getPosition().x + 10, background.getPosition().y + 12);

    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Utiliser const_cast pour contourner la constance et modifier les membres
                const_cast<Coffre*>(this)->isOpen = true; // Marquer le coffre comme ouvert après que le message a été affiché
                sf::Texture* openTexture = new sf::Texture();
                if (!openTexture->loadFromFile("open_empty.png")) {
                    std::cerr << "Erreur lors du chargement de la texture du coffre ouvert" << std::endl;
                }
                const_cast<Coffre*>(this)->setTexture(openTexture); // Changer la texture du coffre
                const_cast<Coffre*>(this)->showMessage = false; // Réinitialiser l'état du message
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
