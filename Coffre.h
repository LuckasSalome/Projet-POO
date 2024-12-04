#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>
#include <iostream>
#include "Player.h"
#include "Wall.h"
#include "Sol.h" 

using namespace std;

class Coffre
{
private:
    std::vector<std::string> objets;
    sf::Texture* texture;
    sf::RectangleShape body;
    Animation animation;
    bool isOpen;
    bool eKeyPressed;
    bool showMessage;
    int dumbness;

public:
    Coffre(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Coffre();
    void ouvrir();
    void draw(sf::RenderWindow& window) const;
    std::vector<std::string> getObjets() const;
    void drawMessage(sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols, const Player& player) const;
    void addObjet(const std::string& objet);
    void setTexture(sf::Texture* newTexture);
    bool isEKeyPressed() const;
    void setEKeyPressed(bool state);
    bool shouldShowMessage() const;

    sf::Vector2f GetPosition() const;
    sf::FloatRect GetBounds() const;
};
