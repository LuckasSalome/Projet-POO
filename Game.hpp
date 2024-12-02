#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "State.hpp"
#include "Player.hpp"
#include "Map.hpp"

using namespace sf;
using namespace std;

class Game
{
private:
    RenderWindow* window;
    Event sfEvent;
    Player* player;
    Map* tileMap;
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

    //Constructeur
    Game() {

        this->initWindow();
        this->tileMap = new Map();
        this->player = new Player(tileMap);

    };

    //Destructeur

    virtual ~Game() {
        delete this->window;
        delete this->player;
        delete this->tileMap;
    };

    //////////////////Methodes\\\\\\\\\\\\\\\\\\\

    //Gerer les events
    void updateSFMLEvents() {

        while (this->window->pollEvent(this->sfEvent)) {

            if (this->sfEvent.type == Event::Closed)
                this->window->close();


        }

    };

    //Update l'horloge dt en seconde pour voir cbn de temp prend une frame a render

    void updateDT() {

        this->dt = this->dtClock.restart().asSeconds();

        system("cls");
        cout << this->dt << "\n";

    };

    // Update les events
    void update() {

        this->updateSFMLEvents();
        this->player->playerMovement(this -> dt);
        this->viewOnPlayer();
    };


    //Display
    void render() {

        this->window->clear();

        // this->window->draw(this->tileMap->getTileMap());
        for (const auto& row : this->tileMap->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        this->window->setView(playerView);
        this->window->draw(this->player->getPlayer());

        //Render Items

        this->window->display();

    };

    //Methode pour gérer le lancement du jeu
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

    float getPlayerViewCenterX() {

        return this->playerView.getCenter().x;

    };

    float getPlayerViewCenterY() {

        return this->playerView.getCenter().y;

    };

};
