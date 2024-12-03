#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Map.hpp"
#include "MapManager.hpp"

using namespace sf;
using namespace std;

class Player {

private:
    RectangleShape player;
    Texture playerTex;
    View playerView;
    MapManager* mapManager;
    Vector2f velocity;
    const float movementSpeed = 400;
    FloatRect playerBounds;
    FloatRect nextPos;
    Vector2f direction;

    void playerInit() {
        this->player.setSize(Vector2f((mapManager->getGridSize() -10.f), (mapManager->getGridSize() -10.f )));
        this->player.setPosition(Vector2f((mapManager->getGridSize() * 8), (mapManager->getGridSize() * 2)));
        this->setPlayerTex();
        this->player.setTexture(&playerTex);
    };

public:
    Player(MapManager* mapManager) : mapManager(mapManager) {
        this->playerInit();
    }

    void playerMovement(float dt, const std::vector<RectangleShape>& walls) {
        sf::Vector2f movement(0.0f, 0.0f); // initialise le vecteur de mouvement à 0,0

        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            movement.x -= movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            movement.x += movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            movement.y += movementSpeed * dt;
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            movement.y -= movementSpeed * dt;
        }

        // Ajuster la vitesse en diagonale
        if (movement.x != 0.0f && movement.y != 0.0f) {
            movement.x *= 0.75f;
            movement.y *= 0.75f;
        }

        // Sprint
        if ((movement.x || movement.y) != 0 && (Keyboard::isKeyPressed(Keyboard::LShift))) {
            movement.x *= 2.00f;
            movement.y *= 2.00f;
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (Keyboard::isKeyPressed(Keyboard::LControl))) {
            movement.x *= 5.00f;
            movement.y *= 5.00f;
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (Keyboard::isKeyPressed(Keyboard::RShift))) {
            movement.x *= 12.0f;
            movement.y *= 12.0f;
        }

        Vector2f newPosition = player.getPosition() + movement;
        FloatRect newBounds = player.getGlobalBounds();
        newBounds.left = newPosition.x - player.getOrigin().x;
        newBounds.top = newPosition.y - player.getOrigin().y;

        for (const auto& wall : walls) {
            if (newBounds.intersects(wall.getGlobalBounds())) {
                movement = Vector2f(0.0f, 0.0f);
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

};
