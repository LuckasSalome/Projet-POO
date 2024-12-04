#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Map.hpp"
#include "MapManager.hpp"
#include "Animation.hpp"

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
    Animation* animation;
    bool faceRight;

    void playerInit() {
        this->player.setSize(Vector2f((mapManager->getGridSize() - 10.f), (mapManager->getGridSize() - 10.f)));
        this->player.setPosition(Vector2f((mapManager->getGridSize() * 1), (mapManager->getGridSize() * 9)));
        this->setPlayerTex();
        this->player.setTexture(&playerTex);

        // Initialiser l'animation
        this->animation = new Animation(&playerTex, Vector2u(4, 5), 0.2f); //cbn de ligne, collonne et vitesse de l anim
        this->faceRight = true;
    };

public:
    Player(MapManager* mapManager) : mapManager(mapManager) {
        this->playerInit();
    }

    ~Player() {
        delete this->animation;
    }

    void playerMovement(float dt, const std::vector<RectangleShape>& walls) {
        sf::Vector2f movement(0.0f, 0.0f); // initialise le vecteur de mouvement à 0,0
        int row = 4; // Ligne par défaut pour l'animation Idle avant

        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            movement.x -= movementSpeed * dt;
            this->faceRight = false;
            row = 3; // Ligne pour la marche gauche
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            movement.x += movementSpeed * dt;
            this->faceRight = true;
            row = 3; // Ligne pour la marche droite // je sais pas pourquoi ça marche comme ça
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            movement.y += movementSpeed * dt;
            row = 0; // Ligne pour la marche avant
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            movement.y -= movementSpeed * dt;
            row = 1; // Ligne pour l'Idle arrière
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

        // Mettre à jour l'animation
        if (movement.x == 0.0f && movement.y == 0.0f) {
            row = 4; // Ligne pour l'Idle avant
        }
        this->animation->update(row, dt, this->faceRight);
        this->player.setTextureRect(this->animation->uvRect);
    }

    void setPlayerTex() {
        if (!playerTex.loadFromFile("Assets/sheetP1.png")) {
            cerr << "Erreur: Impossible de charger la texture 'Assets/sheet1.png'" << endl;
            throw "cant load sheet1 png";
        }
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
