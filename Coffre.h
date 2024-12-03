#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <vector>
#include <iostream>
#include "Player.h"

using namespace std;

class Coffre
{
private:
    string objet; // le nom de l'objet dans le coffre
    sf::Texture* texture;
    sf::RectangleShape body;
    Animation animation;

public:
    Coffre(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Coffre();
    void ouvrir();
    void draw(sf::RenderWindow& window) const;
    std::string getObjet() const;
    void drawMessage(sf::RenderWindow& window, const std::string& message) const;

    sf::Vector2f GetPosition() const;
    sf::FloatRect GetBounds() const;
};
