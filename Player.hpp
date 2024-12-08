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
#include "GameData.hpp"
#include "ChoixPerso.hpp"

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
    function<void(string, string, string)> mapChangeCallback; //callback : peux se vulgariser par un guetteur a la cit�, il guette quand quelque chose se passe il crie pour qu'une action d�marre.
    float animationSpeed = 0.2f;
    bool faceRight;
    const int COLLISION_TRIGGER = 2;
    const int COLLISION_TRIGGER_BACK = 3;
    int mapIteration = 2; // numero de la prochaine map
    GameData data;

    void playerInit(int colonne, int ligne, string race) {
        this->player.setSize(Vector2f((mapManager->getGridSize() - 10.f), (mapManager->getGridSize() - 10.f)));
        this->player.setPosition(Vector2f((mapManager->getGridSize() * colonne), (mapManager->getGridSize() * ligne)));
        if (race == "Humain")
          this->setHumanTex();
		else if (race == "Barbare")
			this->setBarbarianTex();
		else if (race == "Nain")
			this->setDwarfTex();
		else if (race == "Elfe")
			this->setElfTex();
        this->player.setTexture(&playerTex);
        this->animation = new Animation(&playerTex, Vector2u(4, 5), animationSpeed); //cbn de ligne, collonne et vitesse de l anim
        this->faceRight = true;
    };

public:
    Player(MapManager* mapManager, function<void(string, string, string)> mapChangeCallback)
        : mapManager(mapManager), mapChangeCallback(mapChangeCallback) {
        this->playerInit(2,9, getCharaRace());
    }

    ~Player() {
        delete this->animation;
    }

    void playerMovement(float dt, const std::vector<RectangleShape>& walls, MapManager& mapManager) {
        sf::Vector2f movement(0.0f, 0.0f); // initialise le vecteur de mouvement � 0,0
        int row = 4; // Ligne par d�faut pour l'animation Idle avant

        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            movement.x -= movementSpeed * dt;
            this->faceRight = false;
            row = 3; // Ligne pour la marche gauche
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            movement.x += movementSpeed * dt;
            this->faceRight = true;
            row = 3; // Ligne pour la marche droite // je sais pas pourquoi �a marche comme �a
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            movement.y += movementSpeed * dt;
            row = 0; // Ligne pour la marche avant
        }
        if (Keyboard::isKeyPressed(Keyboard::Z)) {
            movement.y -= movementSpeed * dt;
            row = 1; // Ligne pour l'Idle arri�re
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

        // D�tecter les collisions avec les triggers
        const auto& collisionMap = mapManager.getCollisionMap();
        int gridX = static_cast<int>(newPosition.x / mapManager.getGridSize());
        int gridY = static_cast<int>(newPosition.y / mapManager.getGridSize());

        if (collisionMap[gridX][gridY] == COLLISION_TRIGGER) {
            if (mapChangeCallback) {
                cout << "MAP" << mapIteration << endl;
                string tileTypesFile = "Config/tileTypes" + to_string(mapIteration) + ".txt";
                string collisionMapFile = "Config/collisionMap" + to_string(mapIteration) + ".txt";
				string entityMapFile = "Config/entityMap" + to_string(mapIteration) + ".txt";
                mapChangeCallback(tileTypesFile, collisionMapFile, entityMapFile);
                this->playerInit(2,9, getCharaRace());
                this->mapIteration++; // Incr�mente l'it�ration pour la prochaine collision
            }
        }
         if (collisionMap[gridX][gridY] == COLLISION_TRIGGER_BACK) {
            loadPreviousMap();
        }

        player.move(movement);
        // Mettre � jour l'animation
        if (movement.x == 0.0f && movement.y == 0.0f) {
            row = 4; // Ligne pour l'Idle avant
            animationSpeed = 0.2f; // R�initialiser la vitesse de l'animation
        }
        this->animation->setSwitchTime(animationSpeed); // vitesse de l'animation par rapport a la vitesse du joueur (hilarant)
        this->animation->update(row, dt, this->faceRight);
        this->player.setTextureRect(this->animation->uvRect);
    }

    void setHumanTex() {
        if (!playerTex.loadFromFile("Assets/HumanSprite.png")) {
            cerr << "Erreur: Impossible de charger la texture 'Assets/HumanSprite.png'" << endl;
            throw "cant load HumanSprite png";
        }
    };
    void setBarbarianTex() {
        if (!playerTex.loadFromFile("Assets/BarbarianSprite.png")) {
            std::cout << "Barabare" << endl;
            cerr << "Erreur: Impossible de charger la texture 'Assets/BarbarianSprite.png'" << endl;
            throw "cant load BarbarianSprite png";
        }
    };
    void setDwarfTex() {
        if (!playerTex.loadFromFile("Assets/DwarfSprite.png")) {
            cerr << "Erreur: Impossible de charger la texture 'Assets/DwarfSprite.png'" << endl;
            throw "cant load DwarfSprite png";
        }
    };
    void setElfTex() {
        if (!playerTex.loadFromFile("Assets/ElfSprite.png")) {
            cerr << "Erreur: Impossible de charger la texture 'Assets/ElfSprite.png'" << endl;
            throw "cant load ElfSprite png";
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
        if (this->mapIteration > 1) { // Emp�che de descendre en dessous de 1
            cout << "Avant d�cr�mentation : " << mapIteration << endl;
            this->mapIteration--;
            cout << "Apr�s d�cr�mentation : " << mapIteration << endl;
            string tileTypesFile = "Config/tileTypes" + to_string(mapIteration-1) + ".txt";
            string collisionMapFile = "Config/collisionMap" + to_string(mapIteration-1) + ".txt";
			string entityMapFile = "Config/entityMap" + to_string(mapIteration - 1) + ".txt";
            mapChangeCallback(tileTypesFile, collisionMapFile, entityMapFile);
            this->playerInit(17,9, getCharaRace());
        }
        else {
            cout << "D�j� � la premi�re map, impossible de reculer." << endl;
        }
    }

	int getMapIteration() {
		return this->mapIteration-1;
	}  
};
