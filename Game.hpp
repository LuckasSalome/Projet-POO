#pragma once
#include <iostream>
#include <sstream>
#include <queue>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include "MapManager.hpp"
//#include "LookForNewMap.hpp"
#include "Heroes.hpp"
#include "Creatures.hpp"
#include "ExplosiveDuck.hpp"
#include "RhetoricianTroll.hpp"
#include "SarcasticGobelin.hpp"
#include "ProgramLich.hpp"
#include "Fight.hpp"
#include "Inventory.hpp"
#include "BeerPotion.hpp"
#include "RustyKey.hpp"
#include "RopeTrap.hpp"
#include "BookOfLostRules.hpp"
#include "ScepterSintactic.hpp"
#include "KeyCorridor.hpp"
#include "DiscrectionShoesNoisy.hpp"
#include "BluntSword.hpp"
#include "PotionIntelligence.hpp"
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
    Jobs* job;
    Race* race;
    View playerView;
    View uiView;
    Clock dtClock;
    Heroes* hero;
    Font font;

    float dt;

    void initWindow() {
        ifstream ifs("Config/window.txt");

        // valeurs par défaut si le fichier n'existe pas ou n'est pas disponible
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
    // Constructeur par défaut qui initialise la fenêtre, le joueur et la carte
    Game() {
        this->initWindow();
		this->initFont();
        this->mapManager = new MapManager(75.f, 20, "Config/tileTypes1.txt", "Config/collisionMap1.txt");
        this->player = new Player(mapManager, [this](string newTileMap, string newCollisionMap) {
            this->onMapChange(newTileMap, newCollisionMap); }); //en gros ah carré tu change de map bah dcp appelle cette fonction stp

        this->wall = new Collision(mapManager, player, (this->window->getSize().x), (this->window->getSize().y));
        this->inventory = new Inventory(5, 5, font); 
        this->hero = nullptr;
        this->job = nullptr;
        this->race = nullptr;
        this->populateInventory();
        this->populateSecondaryGrid();

    };

    // // Destructeur qui supprime la fenêtre, le joueur et la carte
    ~Game() {
        delete this->window;
        delete this->player;
        delete this->mapManager;
        delete this->wall;
        delete this->inventory;
        delete this->hero;
        delete this->job;
        delete this->race;
    };

    //////////////////Methodes\\\\\\\\\\\\\\\\\\\

    // Gerer les events
    void updateSFMLEvents() {
        while (this->window->pollEvent(this->sfEvent)) {
            if (this->sfEvent.type == Event::Closed)
                this->window->close();

            if (this->sfEvent.type == Event::KeyPressed) {
                if (this->sfEvent.key.code == Keyboard::I) {
                    this->inventory->toggleInventory();
                }

                if (this->sfEvent.key.code == Keyboard::U && this->inventory->getIsOpen()) {        //appuyer sur U pour déséquiper tous les objets
                    this->inventory->unequipItem("Weapon");
                    this->inventory->unequipItem("ChestArmor");
                    this->inventory->unequipItem("Boots");
                }
            }

            if (this->sfEvent.type == Event::MouseButtonPressed) {          //action de la souris qaudn on clique
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

    // Update l'horloge dt en seconde pour voir cbn de temp prend une frame a render
    void updateDT() {
        this->dt = this->dtClock.restart().asSeconds();
    };

    // Update les events
    void update() {
        this->updateSFMLEvents();

        if (!this->inventory->getIsOpen()) {    //deplacement du joueur
            this->player->playerMovement(this->dt, this->wall->getWalls(), *this->mapManager);
            this->viewOnPlayer();
        }

        //Voir collisions
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
            this->wall->setWallsColor(Color::Color(255, 0, 0, 125));
        }
        else {
            this->wall->setWallsColor(Color::Transparent);
        }
    }

    // Display
    void render() {
        this->window->clear();
        this->window->setView(playerView);

        for (const auto& row : this->mapManager->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        //this->window->setView(playerView);
        for (const auto& wall : this->wall->getWalls()) {
            this->window->draw(wall);
        }
        this->window->draw(this->player->getPlayer());

        // Render Items
        this->window->setView(uiView);
        this->inventory->draw(*this->window);

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
        this->mapManager->loadNewMap(NewTileMap, NewCollisionMap);
        this->wall->resetCollisions();
        this->entityInit("Sorcier", "Elfe");
    };

    static Jobs* createJobs(const string& type) {
        if (type == "Guerrier") {
            return new Warrior();
        }
        else if (type == "Sorcier") {
            return new Sorcerer();
        }
        else if (type == "Voleur") {
            return new Thief();
        }
        else if (type == "Rodeur") {
            return new Ranger();
        }
        else {
            return nullptr;
        }
    }
    static Race* createRace(const string& type) {
        if (type == "Elfe") {
            return new Elf();
        }
        else if (type == "Barbare") {
            return new Barbarian();
        }
        else if (type == "Nain") {
            return new Dwarf();
        }
        else if (type == "Humain") {
            return new Human();
        }
        else {
            return nullptr;
        }
    }
    static Common* createMob(const string& type) {
        if (type == "Gobelin Sarcastique") {
            return new SarcasticGobelin();
        }
        else if (type == "Troll Rhetoricien") {
            return new RhetoricianTroll();
        }
        else if (type == "Canard Explosif") {
            return new ExplosiveDuck();
        }
        else {
            return nullptr;
        }
    }

    static std::shared_ptr<Entity> createEntity(const string& type, const string name) {
        if (type == "Hero")
            return make_shared<Heroes>(name);
        else if (type == "Monstre")
            return make_shared<Creatures>();
    }


    void entityInit(string jobName, string raceName) {

        string jobType = "Sorcier";
        string raceType = "Elfe";
        string mobType = "Gobelin Sarcastique";
        string statistics[6] = { "COU", "CHA", "INT", "FO", "AD", "HP" };

        Jobs* job = createJobs(jobType);
        Race* race = createRace(raceType);
        Common* mob = createMob(mobType);
        Boss* lich = new ProgramLich();

        std::shared_ptr<Entity> Character1 = createEntity("Hero", "Michel");
        std::shared_ptr<Entity> Character2 = createEntity("Hero", "Pierre");
        std::shared_ptr<Entity> Mob1 = createEntity("Monstre", "");
        std::shared_ptr<Entity> Boss = createEntity("Monstre", "");
        Group* Heros = new Group();
        Group* Monstres = new Group();


        //hero numero 1
        Character1->StatComparison(*race, *job);
        Character1->initDesc(*race, *job);
        Character1->initName(*race, *job);
        Character1->initHeroStat(*race, *job);

        //hero numero 2
        Character2->StatComparison(*race, *job);
        Character2->initDesc(*race, *job);
        Character2->initName(*race, *job);
        Character2->initHeroStat(*race, *job);


        //monstre numero 1
        Mob1->initCreatureDesc(*mob);
        Mob1->initCreatureName(*mob);
        Mob1->initCreatureStat(*mob);

        //boss
        Boss->initBossName(*lich);
        Boss->initBossDesc(*lich);
        Boss->initBossStat(*lich);

        Monstres->addParty(Mob1);
        Heros->addParty(Character2);
        Heros->addParty(Character1);

        //Heros->removeParty(Character1);

        Fight* combat = new Fight(*Heros, *Monstres);
        // Affichage de l'ordre de combat 
        auto ordre = combat->fightOrder();
        while (!ordre.empty()) {
            std::cout << ordre.front()->getName() << std::endl;
            ordre.pop();
        }

        combat->fighting(*mob, *lich, *race, *job);

        ////affiche le hero et le monstre
        //cout << Character1->getName() << endl;
        //cout << Character1->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Character1->getStat()[statistics[i]] << endl;


        //cout << Mob1->getName() << endl;
        //cout << Mob1->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Mob1->getStat()[statistics[i]] << endl;


        ////attaque du hero
        //cout << Character1->getRaceSpell(*race, Mob1) << endl;
        //cout << Character1->getJobSpell(*job, Mob1) << endl;
        //cout << Character1->getBasicAttack(*race, Mob1) << endl;

        ////stats retours monstre
        //cout << Mob1->getName() << endl;
        //cout << Mob1->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Mob1->getStat()[statistics[i]] << endl;

        ////attaque du monstre 
        //cout << Mob1->getMonsterSpell(*mob, Character1) << endl;
        //cout << Mob1->getBasicAttack(*mob, Character1) << endl;

        ////affiche boss
        //cout << Boss->getName() << endl;
        //cout << Boss->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Boss->getStat()[statistics[i]] << endl;


        ////attaque p1 boss
        //cout << Boss->getBossSpell1(*lich, Character1) << endl;
        //cout << Boss->getBossSpell2(*lich, Character1) << endl;


        ////stats retours hero
        //cout << Character1->getName() << endl;
        //cout << Character1->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Character1->getStat()[statistics[i]] << endl;

        //Boss->setHealth(45);
        ////affiche boss
        //cout << Boss->getName() << endl;
        //cout << Boss->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Boss->getStat()[statistics[i]] << endl;

        //// attaque p2 bosse
        //cout << Boss->getBossSpell1(*lich, Character1) << endl;
        //cout << Boss->getBossSpell2(*lich, Character1) << endl;

        ////stats retours hero
        //cout << Character1->getName() << endl;
        //cout << Character1->getDesc() << endl;
        //for (int i = 0; i < 6; i++)
        //    cout << Character1->getStat()[statistics[i]] << endl;

    };
};