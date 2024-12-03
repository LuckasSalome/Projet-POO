#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Map.hpp"

using namespace sf;
using namespace std;

class Player {

private:
    RectangleShape player;
    Texture playerTex;
    View playerView;
    Map* map;
    Vector2f velocity;
    const float movementSpeed = 400;
    FloatRect playerBounds;
    FloatRect nextPos;
    Vector2f direction;

    void playerInit() {
        this->player.setSize(Vector2f(map->getGridSize(), map->getGridSize()));
        this->player.setPosition(Vector2f((map->getGridSize() * 0), (map->getGridSize() * 0)));
        this->setPlayerTex();
        this->player.setTexture(&playerTex);
    };

public:
    Player(Map* map) : map(map) {
        this->playerInit();
    }

    void playerMovement(float dt, const std::vector<RectangleShape>& walls) {
        sf::Vector2f movement(0.0f, 0.0f); // initialise le vecteur de mouvement à 0,0

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            movement.x -= movementSpeed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += movementSpeed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += movementSpeed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            movement.y -= movementSpeed * dt;
        }

        // Ajuster la vitesse en diagonale
        if (movement.x != 0.0f && movement.y != 0.0f) {
            movement.x *= 0.75f;
            movement.y *= 0.75f;
        }

        // Sprint
        if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))) {
            movement.x *= 2.00f;
            movement.y *= 2.00f;
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {
            movement.x *= 5.00f;
            movement.y *= 5.00f;
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
            movement.x *= 12.0f;
            movement.y *= 12.0f;
        }

        sf::Vector2f newPosition = player.getPosition() + movement;
        sf::FloatRect newBounds = player.getGlobalBounds();
        newBounds.left = newPosition.x - player.getOrigin().x;
        newBounds.top = newPosition.y - player.getOrigin().y;

        for (const auto& wall : walls) {
            if (newBounds.intersects(wall.getGlobalBounds())) {
                movement = sf::Vector2f(0.0f, 0.0f);
                break;
            }
        }

        player.move(movement);
    }

    void setPlayerTex() {
        if (!playerTex.loadFromFile("Assets/cat.png"))
            throw "cant load cat png";
    };

    const RectangleShape& getPlayer() const {
        return this->player;
    }

    Vector2f getPositionPlayer() {
        return this->player.getPosition();
    };

    FloatRect getPlayerBounds() {
        return this->player.getGlobalBounds();
    };

    FloatRect getNextPos() {
        FloatRect nextPos = this->getPlayerBounds();
        nextPos.left += this->velocity.x;
        nextPos.top += this->velocity.y;
        return nextPos;
    }

    Vector2f getPlayerVelocity() {
        return this->velocity;
    };

    Vector2f getPlayerOrigin() {
        return this->player.getOrigin();
    };

    Vector2f getPlayerSize() {
        return this->player.getSize();
    };

    void setDirection(float x, float y) {
        direction.x = x;
        direction.y = y;
    }

    Vector2f getDirection() const {
        return direction;
    }

    void stopMovement() {
        direction.x = 0;
        direction.y = 0;
    }

    void setPlayerPosition(float x, float y) {
        this->player.setPosition(x, y);
    }

    void setPlayerVelocity(float x, float y) {
        this->velocity.x = x;
        this->velocity.y = y;
    };

    void playerStopMovingBottom(const sf::FloatRect& wallBounds) {
        this->velocity.y = 0.f;
        player.setPosition(player.getPosition().x, wallBounds.top - player.getGlobalBounds().height);
    }

    void playerStopMovingTop(const sf::FloatRect& wallBounds) {
        this->velocity.y = 0.f;
        player.setPosition(player.getPosition().x, wallBounds.top + wallBounds.height);
    }

    void playerStopMovingRight(const sf::FloatRect& wallBounds) {
        this->velocity.x = 0.f;
        player.setPosition(wallBounds.left - player.getGlobalBounds().width, player.getPosition().y);
    }

    void playerStopMovingLeft(const sf::FloatRect& wallBounds) {
        this->velocity.x = 0.f;
        player.setPosition(wallBounds.left + wallBounds.width, player.getPosition().y);
    }

    void test() {
        std::cout << "NextPos: (" << nextPos.left << ", " << nextPos.top << "), Taille: "
                  << nextPos.width << "x" << nextPos.height << "\n";
        std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")\n";
    };
};
