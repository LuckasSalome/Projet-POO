#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "MapManager.hpp"
#include "LookForNewMap.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    RenderWindow* window;
    Event sfEvent;
    Collision* wall;
    Player* player;
    MapManager* mapManager;
    View playerView;
    Clock dtClock;
    float dt;

    void initWindow() {
        ifstream ifs("Config/window.txt");

        string title = "None";
        VideoMode window_bounds(1920, 600);
        unsigned framerate_limit = 120;

        if (ifs.is_open()) {
            getline(ifs, title);
            ifs >> window_bounds.width >> window_bounds.height;
            ifs >> framerate_limit;
        }

        ifs.close();

        this->window = new RenderWindow(window_bounds, title);
        this->window->setFramerateLimit(framerate_limit);
    };

public:
    // Constructeur
    Game() {
        this->initWindow();
        this->mapManager = new MapManager(75.f, 20, "Config/tileTypes1.txt", "Config/collisionMap1.txt");
        this->player = new Player(mapManager, [this](string newTileMap, string newCollisionMap) {
            this->onMapChange(newTileMap, newCollisionMap);}); //en gros ah carré tu change de map bah dcp appelle cette fonction stp
        this->wall = new Collision(mapManager, player, (this->window->getSize().x),(this->window->getSize().y));
    };

    // Destructeur
    ~Game() {
        delete this->window;
        delete this->player;
        delete this->mapManager;
        delete this->wall;
    };

    //////////////////Methodes\\\\\\\\\\\\\\\\\\\

    // Gerer les events
    void updateSFMLEvents() {
        while (this->window->pollEvent(this->sfEvent)) {
            if (this->sfEvent.type == Event::Closed)
                this->window->close();
        }
    };

    // Update l'horloge dt en seconde pour voir cbn de temp prend une frame a render
    void updateDT() {
        this->dt = this->dtClock.restart().asSeconds();
    };

    // Update les events
    void update() {
        this->updateSFMLEvents();
        this->player->playerMovement(this->dt, this->wall->getWalls(), *this->mapManager);
        this->viewOnPlayer();

        //Voir collisions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            this->wall->setWallsColor(Color::Red);
        }
        else {
            this->wall->setWallsColor(Color::Transparent);
        }
    }

    // Display
    void render() {
        this->window->clear();

        for (const auto& row : this->mapManager->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        this->window->setView(playerView);
        for (const auto& wall : this->wall->getWalls()) {
            this->window->draw(wall);
        }
        this->window->draw(this->player->getPlayer());

        // Render Items
        this->window->display();
    }

    // Methode pour gérer le lancement du jeu
    void run() {
        while (this->window->isOpen()) {
            this->updateDT();
            this->update();
            this->render();
        }
    };

    void viewOnPlayer() {
        this->playerView.setCenter(player->getPositionPlayer());
    };

    void onMapChange(string NewTileMap, string NewCollisionMap) {
        this-> mapManager->loadNewMap(NewTileMap, NewCollisionMap);
        this-> wall->resetCollisions();
    }

};
