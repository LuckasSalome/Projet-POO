// Player.h
#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <vector>
#include <iostream>

class Wall; // D�claration anticip�e
class Teleporteur; // D�claration anticip�e
class Coffre; // D�claration anticip�e

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    void Update(float deltaTime, const std::vector<Wall>& walls, const std::vector<Teleporteur*>& teleporteurs, const std::vector<Coffre*>& Chests, sf::RenderWindow& window); // Enlever const
    ~Player();

    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::FloatRect GetBounds() const { return body.getGlobalBounds(); }
    void PrintPosition() const;

private:
    void CheckChestCollision(const std::vector<Coffre*>& Chests, sf::RenderWindow& window);

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool mousePressed;
};
