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
#include "LookForNewMap.hpp"
#include "Heroes.hpp"
#include "Creatures.hpp"
#include "ExplosiveDuck.hpp"
#include "RhetoricianTroll.hpp"
#include "SarcasticGobelin.hpp"
#include "ProgramLich.hpp"
#include "Fight.hpp"


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
    Jobs* job;
    Race* race;
    Heroes* hero;

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
        this->onMapChange(newTileMap, newCollisionMap); }); //en gros ah carré tu change de map bah dcp appelle cette fonction stp
        this->wall = new Collision(mapManager, player, (this->window->getSize().x), (this->window->getSize().y));
        this->hero = nullptr;
        this->job = nullptr;
        this->race = nullptr;
    };

    // Destructeur
    ~Game() {
        delete this->window;
        delete this->player;
        delete this->mapManager;
        delete this->wall;
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

        //affiche le hero et le monstre
        cout << Character1->getName() << endl;
        cout << Character1->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Character1->getStat()[statistics[i]] << endl;


        cout << Mob1->getName() << endl;
        cout << Mob1->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Mob1->getStat()[statistics[i]] << endl;


        //attaque du hero
        cout << Character1->getRaceSpell(*race, Mob1) << endl;
        cout << Character1->getJobSpell(*job, Mob1) << endl;
        cout << Character1->getBasicAttack(*race, Mob1) << endl;

        //stats retours monstre
        cout << Mob1->getName() << endl;
        cout << Mob1->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Mob1->getStat()[statistics[i]] << endl;

        //attaque du monstre 
        cout << Mob1->getMonsterSpell(*mob, Character1) << endl;
        cout << Mob1->getBasicAttack(*mob, Character1) << endl;

        //affiche boss
        cout << Boss->getName() << endl;
        cout << Boss->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Boss->getStat()[statistics[i]] << endl;


        //attaque p1 boss
        cout << Boss->getBossSpell1(*lich, Character1) << endl;
        cout << Boss->getBossSpell2(*lich, Character1) << endl;


        //stats retours hero
        cout << Character1->getName() << endl;
        cout << Character1->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Character1->getStat()[statistics[i]] << endl;

        Boss->setHealth(45);
        //affiche boss
        cout << Boss->getName() << endl;
        cout << Boss->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Boss->getStat()[statistics[i]] << endl;

        // attaque p2 bosse
        cout << Boss->getBossSpell1(*lich, Character1) << endl;
        cout << Boss->getBossSpell2(*lich, Character1) << endl;

        //stats retours hero
        cout << Character1->getName() << endl;
        cout << Character1->getDesc() << endl;
        for (int i = 0; i < 6; i++)
            cout << Character1->getStat()[statistics[i]] << endl;

    };
};