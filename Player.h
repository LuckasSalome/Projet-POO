// Player.h
#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <vector>
#include <iostream>

class Wall; // Déclaration anticipée
class Teleporteur; // Déclaration anticipée

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    void Update(float deltaTime, const std::vector<Wall>& walls, const std::vector<Teleporteur*>& teleporteurs, const sf::RenderWindow& window);
    ~Player();

    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::FloatRect GetBounds() const { return body.getGlobalBounds(); }
    void PrintPosition() const;

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool mousePressed;
};
