#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include <vector>
#include <iostream>
#include "Sol.h"

class Wall; // Déclaration anticipée
class Teleporteur; // Déclaration anticipée
class Coffre; // Déclaration anticipée

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    void Update(float deltaTime, const std::vector<Wall>& walls, const std::vector<Teleporteur*>& teleporteurs, const std::vector<Coffre*>& Chests, const std::vector<Sol>& sols, sf::RenderWindow& window);
    ~Player();

    void Draw(sf::RenderWindow& window) const;

    sf::Vector2f GetPosition() { return body.getPosition(); }
    sf::FloatRect GetBounds() const { return body.getGlobalBounds(); }
    void PrintPosition() const;

private:
    void CheckChestCollision(const std::vector<Coffre*>& Chests, sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols);

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool mousePressed;
    bool showMessage; // Ajout d'une variable pour suivre l'état du message du coffre
    const Coffre* currentChest; // Ajout d'un pointeur vers le coffre actuel
};
