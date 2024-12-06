#pragma once
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "PotionIntelligence.hpp"
#include "MapManager.hpp"
#include "Inventory.hpp"
#include "BeerPotion.hpp"
#include "RustyKey.hpp"
#include "RopeTrap.hpp"
#include "BookOfLostRules.hpp"
#include "ScepterSintactic.hpp"
#include "KeyCorridor.hpp"
#include "DiscrectionShoesNoisy.hpp"
#include "BluntSword.hpp"
#include "MajorHealingPotion.hpp"
#include "Sword.hpp"
#include "Bow.hpp"
#include "SorcererStick.hpp"
#include "Dagger.hpp"
#include "StealBoots.hpp"
#include "LeatherBoots.hpp"
#include "DarkBoots.hpp"
#include "SorcererBoots.hpp"
#include "ChainMail.hpp"
#include "LeatherChest.hpp"
#include "DarkCape.hpp"
#include "SorcererCape.hpp"

using namespace sf;
using namespace std;

class Game {
private:
    RenderWindow* window;
    Event sfEvent;
    Collision* wall;
    Player* player;
    MapManager* mapManager;
    Inventory* inventory;
    View playerView;
    View uiView;
    Clock dtClock;
    float dt;
    Font font;

    void initWindow() {
        ifstream ifs("Config/window.txt");

        string title = "Game";
        VideoMode window_bounds(1920, 1080);
        unsigned framerate_limit = 120;

        if (ifs.is_open()) {
            getline(ifs, title);
            ifs >> window_bounds.width >> window_bounds.height;
            ifs >> framerate_limit;
        }

        ifs.close();

        this->window = new RenderWindow(window_bounds, title);
        this->window->setFramerateLimit(framerate_limit);

        this->playerView.setSize(window_bounds.width, window_bounds.height);
        this->playerView.setCenter(window_bounds.width / 2.f, window_bounds.height / 2.f);

        this->uiView = this->window->getDefaultView();
    };

    void initFont() {
        if (!font.loadFromFile("images/RobotoBlack.ttf")) {
            cerr << "Error: Unable to load font 'RobotoBlack.ttf'!" << endl;
            throw runtime_error("Font loading failed");
        }
    }

    void populateInventory() {
        inventory->addItem(0, 0, new PotionIntelligence());
        inventory->addItem(0, 1, new RustyKey());
        inventory->addItem(0, 2, new RopeTrap());
        inventory->addItem(0, 3, new BeerPotion());
        inventory->addItem(0, 4, new BookOfLostRules());
        inventory->addItem(1, 0, new ScepterSyntactic());
        inventory->addItem(1, 1, new KeyCorridor());
        inventory->addItem(1, 2, new DiscretionShoesNoisy());
        inventory->addItem(1, 3, new BluntSword());
        inventory->addItem(1, 4, new MajorHealingPotion());;
        inventory->addItem(2, 1, new Bow());
        inventory->addItem(2, 2, new SorcererStick());
        inventory->addItem(2, 3, new Dagger());
        inventory->addItem(2, 4, new StealBoots());
        inventory->addItem(3, 0, new LeatherBoots());
        inventory->addItem(3, 1, new DarkBoots());
        inventory->addItem(3, 2, new SorcererBoots());
        inventory->addItem(3, 3, new ChainMail());
        inventory->addItem(3, 4, new LeatherChest());
        inventory->addItem(4, 0, new DarkCape());
        inventory->addItem(4, 1, new SorcererCape());
    }

    void populateSecondaryGrid() {
        inventory->addSecondaryItem(0, 0, new PotionIntelligence());
        inventory->addSecondaryItem(0, 1, new RustyKey());
        inventory->addSecondaryItem(0, 2, new Sword());
        inventory->addSecondaryItem(1, 0, new BeerPotion());
        inventory->addSecondaryItem(2, 2, new ChainMail());
    }

public:
    Game() {
        this->initWindow();
        this->initFont();
        this->mapManager = new MapManager(75.f, 20, "Config/tileTypes1.txt", "Config/collisionMap1.txt");
        this->player = new Player(mapManager, [this](string newTileMap, string newCollisionMap) {
            this->onMapChange(newTileMap, newCollisionMap);
            });
        this->wall = new Collision(mapManager, player, this->window->getSize().x, this->window->getSize().y);
        this->inventory = new Inventory(5, 5, font);


        this->populateInventory();

        this->populateSecondaryGrid();
        
    };

    ~Game() {
        delete this->window;
        delete this->player;
        delete this->mapManager;
        delete this->wall;
        delete this->inventory;
       
    };

    void updateSFMLEvents() {
        while (this->window->pollEvent(this->sfEvent)) {
            if (this->sfEvent.type == Event::Closed)
                this->window->close();

            if (this->sfEvent.type == Event::KeyPressed) {
                if (this->sfEvent.key.code == Keyboard::I) {
                    this->inventory->toggleInventory();
                }

                if (this->sfEvent.key.code == Keyboard::U && this->inventory->getIsOpen()) {
                    this->inventory->unequipItem("Weapon");
                    this->inventory->unequipItem("ChestArmor");
                    this->inventory->unequipItem("Boots");
                }
            }

            if (this->sfEvent.type == Event::MouseButtonPressed) {
                if (this->sfEvent.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

                    if (this->inventory->getIsOpen()) {
                        this->inventory->handleMouseClick(
                            Vector2i(mousePos.x, mousePos.y),
                            *this->window
                        );
                    }
                }
            }
        }
    };

    void updateDT() {
        this->dt = this->dtClock.restart().asSeconds();
    };

    void update() {
        this->updateSFMLEvents();

        if (!this->inventory->getIsOpen()) {
            this->player->playerMovement(this->dt, this->wall->getWalls(), *this->mapManager);
            this->viewOnPlayer();
        }

        if (Keyboard::isKeyPressed(Keyboard::V)) {
            this->wall->setWallsColor(Color::Red);
        }
        else {
            this->wall->setWallsColor(Color::Transparent);
        }
    }

    void render() {
        this->window->clear();
        this->window->setView(playerView);

        for (const auto& row : this->mapManager->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        for (const auto& wall : this->wall->getWalls()) {
            this->window->draw(wall);
        }

        this->window->draw(this->player->getPlayer());

        this->window->setView(uiView);
        this->inventory->draw(*this->window);

        this->window->display();
    }

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
        this->mapManager->loadNewMap(NewTileMap, NewCollisionMap);
        this->wall->resetCollisions();
    }
};
