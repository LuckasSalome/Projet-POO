#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Wall.h"
#include <vector>
#include <iostream>

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float SwitchTime, float speed);
    ~Player();

    void Update(float deltaTime, const std::vector<Wall>& walls, const sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::FloatRect GetBounds() { return body.getGlobalBounds(); }
    void PrintPosition() const;

private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool mousePressed; 
};
