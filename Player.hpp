#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <functional>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
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
    function<void(string, string)> mapChangeCallback; //callback : peux se vulgariser par un guetteur a la cité, il guette quand quelque chose se passe il crie pour qu'une action démarre.
    float animationSpeed = 0.2f;
    bool faceRight;
    const int COLLISION_TRIGGER = 2;
    const int COLLISION_TRIGGER_BACK = 3;
    int mapIteration = 2; // numero de la prochaine map

    void playerInit(int colonne, int ligne) {
        this->player.setSize(Vector2f((mapManager->getGridSize() - 10.f), (mapManager->getGridSize() - 10.f)));
        this->player.setPosition(Vector2f((mapManager->getGridSize() * colonne), (mapManager->getGridSize() * ligne)));
        this->setPlayerTex();
        this->player.setTexture(&playerTex);
        this->animation = new Animation(&playerTex, Vector2u(4, 5), animationSpeed); //cbn de ligne, collonne et vitesse de l anim
        this->faceRight = true;
    };

public:
    Player(MapManager* mapManager, function<void(string, string)> mapChangeCallback)
        : mapManager(mapManager), mapChangeCallback(mapChangeCallback) {
        this->playerInit(2, 9);
    }

    ~Player() {
        delete this->animation;
    }

    void playerMovement(float dt, const std::vector<RectangleShape>& walls, MapManager& mapManager) {
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
            animationSpeed = 0.1f; // Augmenter la vitesse de l'animation en sprint
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (Keyboard::isKeyPressed(Keyboard::LControl))) {
            movement.x *= 5.00f;
            movement.y *= 5.00f;
            animationSpeed = 0.05f; // Augmenter encore plus la vitesse de l'animation en mega sprint
        }

        // Mega Sprint
        if ((movement.x || movement.y) != 0 && (Keyboard::isKeyPressed(Keyboard::RShift))) {
            movement.x *= 12.0f;
            movement.y *= 12.0f;
            animationSpeed = 0.02f; // Augmenter encore encore plus la vitesse de l'animation en mega sprint
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

        // Détecter les collisions avec les triggers
        const auto& collisionMap = mapManager.getCollisionMap();
        int gridX = static_cast<int>(newPosition.x / mapManager.getGridSize());
        int gridY = static_cast<int>(newPosition.y / mapManager.getGridSize());

        if (collisionMap[gridX][gridY] == COLLISION_TRIGGER) {
            if (mapChangeCallback) {
                cout << "MAP" << mapIteration << endl;
                string tileTypesFile = "Config/tileTypes" + to_string(mapIteration) + ".txt";
                string collisionMapFile = "Config/collisionMap" + to_string(mapIteration) + ".txt";
                mapChangeCallback(tileTypesFile, collisionMapFile);
                this->playerInit(2, 9);
                this->mapIteration++; // Incrémente l'itération pour la prochaine collision
            }
        }
        if (collisionMap[gridX][gridY] == COLLISION_TRIGGER_BACK) {
            loadPreviousMap();
        }

        player.move(movement);
        // Mettre à jour l'animation
        if (movement.x == 0.0f && movement.y == 0.0f) {
            row = 4; // Ligne pour l'Idle avant
            animationSpeed = 0.2f; // Réinitialiser la vitesse de l'animation
        }
        this->animation->setSwitchTime(animationSpeed); // vitesse de l'animation par rapport a la vitesse du joueur (hilarant)
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

    void loadPreviousMap() {
        if (this->mapIteration > 1) {
            cout << "Avant décrémentation : " << mapIteration << endl;
            this->mapIteration--;
            cout << "Après décrémentation : " << mapIteration << endl;
            string tileTypesFile = "Config/tileTypes" + to_string(mapIteration - 1) + ".txt";  //Obligé de faire -1 sinon il faut appuyer 2 fois pour revenir a la map d'avant
            string collisionMapFile = "Config/collisionMap" + to_string(mapIteration - 1) + ".txt";
            mapChangeCallback(tileTypesFile, collisionMapFile);
            this->playerInit(17, 9);
        }
        else {
            cout << "Déjà à la première map, impossible de reculer." << endl;
        }
    }

};
