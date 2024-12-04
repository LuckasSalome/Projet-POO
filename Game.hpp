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
#include "BeerPotion.hpp"
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
#include "Chest.hpp"

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
    Chest* chest;

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
        PotionIntelligence* potionIntelligence = new PotionIntelligence();
        RustyKey* rustyKey = new RustyKey();
        RopeTrap* ropeTrap = new RopeTrap();
        BeerPotion* beerPotion = new BeerPotion();
        BookOfLostRules* bookOfLostRules = new BookOfLostRules();
        ScepterSyntactic* scepterSyntactic = new ScepterSyntactic();
        KeyCorridor* keyCorridor = new KeyCorridor();
        DiscretionShoesNoisy* discretionShoesNoisy = new DiscretionShoesNoisy();
        BluntSword* bluntSword = new BluntSword();
        MajorHealingPotion* majorHealingPotion = new MajorHealingPotion();
        Sword* sword = new Sword();
        Bow* bow = new Bow();
        SorcererStick* sorcererStick = new SorcererStick();
        Dagger* dagger = new Dagger();
        StealBoots* stealBoots = new StealBoots();
        LeatherBoots* leatherBoots = new LeatherBoots();
        DarkBoots* darkBoots = new DarkBoots();
        SorcererBoots* sorcererBoots = new SorcererBoots();
        ChainMail* chainMail = new ChainMail();
        LeatherChest* leatherChest = new LeatherChest();
        DarkCape* darkCape = new DarkCape();
        SorcererCape* sorcererCape = new SorcererCape();



        inventory->addItem(0, 0, potionIntelligence);
        inventory->addItem(0, 1, rustyKey);
        inventory->addItem(0, 2, ropeTrap);
        inventory->addItem(0, 3, beerPotion);
        inventory->addItem(0, 4, bookOfLostRules);
        inventory->addItem(1, 0, scepterSyntactic);
        inventory->addItem(1, 1, keyCorridor);
        inventory->addItem(1, 2, discretionShoesNoisy);
        inventory->addItem(1, 3, bluntSword);
        inventory->addItem(1, 4, majorHealingPotion);
        inventory->addItem(2, 0, sword);
        inventory->addItem(2, 1, bow);
        inventory->addItem(2, 2, sorcererStick);
        inventory->addItem(2, 3, dagger);
        inventory->addItem(2, 4, stealBoots);
        inventory->addItem(3, 0, leatherBoots);
        inventory->addItem(3, 1, darkBoots);
        inventory->addItem(3, 2, sorcererBoots);
        inventory->addItem(3, 3, chainMail);
        inventory->addItem(3, 4, leatherChest);
        inventory->addItem(4, 0, darkCape);
        inventory->addItem(4, 1, sorcererCape);



    }



public:
    Game() {
        this->initWindow();
        this->initFont();
        this->mapManager = new MapManager(75.f, 20, "Config/tileTypes.txt", "Config/collisionMap.txt");
        this->player = new Player(mapManager);
        this->wall = new Collision(mapManager, player, this->window->getSize().x, this->window->getSize().y);
        this->inventory = new Inventory(5, 5, font);

        this->populateInventory();
        this->chest = new Chest(100.f, 100.f, 3, 3, font, "images/Chest.png");
        this->chest->getInventory()->addItem(0, 0, new BeerPotion());
        this->chest->getInventory()->addItem(1, 1, new BluntSword());

    };

    ~Game() {
        delete this->window;
        delete this->player;
        delete this->mapManager;
        delete this->wall;
        delete this->inventory;
        delete this->chest;
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
        if (this->sfEvent.type == sf::Event::KeyPressed) {
            if (this->sfEvent.key.code == sf::Keyboard::F) {
                if (!this->inventory->getIsOpen() && !this->chest->getIsOpen()) {
                    if (this->player->getPlayer().getGlobalBounds().intersects(this->chest->getBounds())) {
                        this->chest->toggleChest();
                    }
                }
            }
            else if (this->sfEvent.key.code == sf::Keyboard::Escape) {
                if (this->chest->getIsOpen()) {
                    this->chest->toggleChest();
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
            this->player->playerMovement(this->dt, this->wall->getWalls());
            this->viewOnPlayer();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            this->wall->setWallsColor(Color::Red);
        }
        else {
            this->wall->setWallsColor(Color::Transparent);
        }
    }

    void render() {
        this->window->clear();

        // Set view to follow player
        this->window->setView(playerView);

        // Draw world elements
        for (const auto& row : this->mapManager->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        for (const auto& wall : this->wall->getWalls()) {
            this->window->draw(wall);
        }

        // Draw chest at its fixed position
        this->window->draw(this->chest->getSprite());  // You might need to add a getSprite() method to Chest class

        this->window->draw(this->player->getPlayer());

        // Set back to UI view for UI elements
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
};