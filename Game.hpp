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
#include "DiscretionShoesNoisy.hpp"
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
#include "GameData.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
#include "ChoixPerso.hpp"
#include "Group.hpp"
#include "Enemy.hpp"
#include "Chest.hpp"
#include "trappedChest.hpp"


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
    GameData data;
    vector<Enemy> enemies;
    vector<Chest> chests;
    vector<TrappedChest> trappedChests;
    bool inRange = false;
    bool inGame = true;
    float dt;
    int currentMap = 1;
    sf::Vector2f lichPosition;
    sf::Texture lichTexture;
    sf::Sprite lichSprite;
    vector<string> entityMapFiles = {
        "Config/entityMap1.txt",
        "Config/entityMap2.txt",
        "Config/entityMap3.txt",
        "Config/entityMap5.txt",
        "Config/entityMap6.txt",
        "Config/entityMap7.txt"
    };

    void initGameWindow() {
        ifstream ifs("Config/window.txt");

        // valeurs par défaut si le fichier n'existe pas ou n'est pas disponible
        string title = "CESI & DRAGONS";
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

        if (data.soundEnabled) {
            if (!data.backgroundMusic.openFromFile("mainsound.ogg")) {
                std::cerr << "Erreur de chargement de la musique de fond" << std::endl;
            }
            else {
                data.backgroundMusic.setLoop(true);  // Faire boucler la musique
                data.backgroundMusic.play();         // Démarrer la musique
            }
        }
    }

    void initMenuWindow() {
        data.window.create(VideoMode(data.windowWidth, data.windowHeight), "Main Menu");
        data.window.setKeyRepeatEnabled(false);

        if (!data.backgroundTexture.loadFromFile("images/accueil.jpg") || !data.font.loadFromFile("images/poppins.ttf"))
            return;

        data.background.setTexture(data.backgroundTexture);
        data.background.setScale(
            static_cast<float>(data.window.getSize().x) / data.backgroundTexture.getSize().x,
            static_cast<float>(data.window.getSize().y) / data.backgroundTexture.getSize().y
        );

        initMainMenu(data);

        bool inOptionsMenu = false;
        bool inCharacterSelection = false;

        while (data.window.isOpen()) {
            Event event;
            if (inOptionsMenu) {
                handleOptionsMenu(data, inOptionsMenu);
            }
            else if (inCharacterSelection) {
                inGame = handleCharacterSelection(data, inCharacterSelection, event);
            }
            else if (inGame == false) {
                data.window.close();
                this->initGameWindow(); // Initialiser la fenêtre de jeu après la fermeture de la fenêtre du menu
            }
            else {
                handleMainMenuEvents(data, inOptionsMenu, inCharacterSelection);
                renderMainMenu(data);
            }
        }
    }

    void initFont() {
        if (!font.loadFromFile("images/RobotoBlack.ttf")) {
            cerr << "Error: Unable to load font 'RobotoBlack.ttf'!" << endl;
            throw runtime_error("Font loading failed");
        }
    }

    void initializeChests() {
        if (this->currentMap == 6) {
            // Position du coffre sur la carte tileMap6
            vector<sf::Vector2f> chestPositions = {
                {5 * mapManager->getGridSize(), 6 * mapManager->getGridSize()},
                {14 * mapManager->getGridSize(), 6 * mapManager->getGridSize()}
            };

            for (const auto& pos : chestPositions) {
                chests.emplace_back(pos, inventory);
            }
        }
    }
    void initializeTrappedChests() {
        if (this->currentMap == 6) {
            // Position du coffre sur la carte tileMap6
            vector<sf::Vector2f> trappedChestPositions = {
                {2 * mapManager->getGridSize(), 13 * mapManager->getGridSize()},
                {5 * mapManager->getGridSize(), 13 * mapManager->getGridSize()},
                {8 * mapManager->getGridSize(), 13 * mapManager->getGridSize()},
                {11 * mapManager->getGridSize(), 13 * mapManager->getGridSize()},
                {14 * mapManager->getGridSize(), 13 * mapManager->getGridSize()},
                {2 * mapManager->getGridSize(), 6 * mapManager->getGridSize()},
                {8 * mapManager->getGridSize(), 6 * mapManager->getGridSize()},
                {11 * mapManager->getGridSize(), 6 * mapManager->getGridSize()},
            };

            for (const auto& pos : trappedChestPositions) {
                trappedChests.emplace_back(pos, inventory);
            }
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

    void checkPlayerPosition() {
        if (player->getPositionPlayer() == lichPosition) {
            entityInit(getCharaJob(), getCharaRace(), data, "ProgramLich");
        }
    }

    void loadLichTexture() {
        if (!lichTexture.loadFromFile("Assets/Lich.png")) {
            throw std::runtime_error("Cannot load Assets/Lich.png");
        }
        lichSprite.setTexture(lichTexture);
    }
    void initLichSprite() {
        lichSprite.setTexture(lichTexture);
        lichSprite.setPosition(lichPosition);
    }

public:
    // Constructeur par défaut qui initialise la fenêtre, le joueur et la carte
    Game() {
        this->initMenuWindow();
        this->initFont();
        this->mapManager = new MapManager(75.f, 20, "Config/tileTypes1.txt", "Config/collisionMap1.txt");
        this->player = new Player(mapManager, [this](string newTileMap, string newCollisionMap, string newEntityMap) {
            this->onMapChange(newTileMap, newCollisionMap, newEntityMap); }); //en gros ah carré tu change de map bah dcp appelle cette fonction stp

        this->wall = new Collision(mapManager, player, (this->window->getSize().x), (this->window->getSize().y));
        this->inventory = new Inventory(5, 5, font);
        this->hero = nullptr;
        this->job = nullptr;
        this->race = nullptr;
        this->populateInventory();
        this->populateSecondaryGrid();
        Enemy::resetAllEnemiesInFiles(entityMapFiles);
        this->enemies = Enemy::createEnemies("Config/entityMap1.txt", *this->mapManager);
        this->initializeChests(); // initialise les coffres
        this->initializeTrappedChests(); // initialise les coffres pieges
        lichPosition = { mapManager->getGridSize() * 15, mapManager->getGridSize() * 15 };
        // Charger et initialiser le sprite de la Lich
        this->loadLichTexture();
        this->initLichSprite();


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

    void handleGameWindow() {

        while (this->window->pollEvent(this->sfEvent)) {
            if (this->sfEvent.type == sf::Event::Closed)
                this->window->close();

            if (this->sfEvent.type == sf::Event::KeyPressed) {
                if (this->sfEvent.key.code == sf::Keyboard::I) {
                    this->inventory->toggleInventory();
                }

                if (this->sfEvent.key.code == sf::Keyboard::U && this->inventory->getIsOpen()) {
                    this->inventory->unequipItem("Weapon");
                    this->inventory->unequipItem("ChestArmor");
                    this->inventory->unequipItem("Boots");
                }

                if (this->sfEvent.key.code == sf::Keyboard::E) {
                    for (auto& chest : chests) {
                        if (chest.isPlayerInRange(this->player->getPositionPlayer()))
                            chest.toggleOpen();
                    }
                    for (auto& trappedChest : trappedChests) {
                        if (trappedChest.isPlayerInRange(this->player->getPositionPlayer()))
                        {
                            trappedChest.toggleOpen();
                            startFight();
                        }
                    }
                }
            }

            if (this->sfEvent.type == sf::Event::MouseButtonPressed) {
                if (this->sfEvent.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

                    if (this->inventory->getIsOpen()) {
                        this->inventory->handleMouseClick(
                            sf::Vector2i(mousePos.x, mousePos.y),
                            *this->window
                        );
                        this->inventory->getEquippedStats();
                    }
                }
            }
        }
    }


    void clearChest() {
        chests.clear();
    }
    void clearTrappedChest() {
        trappedChests.clear();
    }

    void startFight() {
        // Initialiser les ExplosiveDuck pour le combat
        entityInit(getCharaJob(), getCharaRace(), data, "Canard Explosif");
    }

    // Update l'horloge dt en seconde pour voir cbn de temp prend une frame a render
    void updateDT() {
        this->dt = this->dtClock.restart().asSeconds();
    };

    // Update les events
    void update() {
        this->handleGameWindow();

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

        for (auto& enemy : enemies) {
            enemy.updateMovement(dt);
            enemy.update(this->dt);
            enemy.drawEnemy(*this->window);
        }


        Enemy* collidedEnemy = Enemy::checkCollisions(*this->player, this->enemies);
        if (collidedEnemy != nullptr) {
            auto creature = collidedEnemy->getCreature();
            if (creature != nullptr) {

                // Obtenir le nom du mob
                std::string mobName = getMobName(collidedEnemy->getTextureKey()); // Assurez-vous que getId() retourne l'identifiant du mob
                cout << "fight vs " << mobName << " at position (" << collidedEnemy->getPosition().x << ", " << collidedEnemy->getPosition().y << ") with texture key " << collidedEnemy->getTextureKey() << endl;
                //this->initFight(this->heroesGroup, this->monstersGroup);
                entityInit(getCharaJob(), getCharaRace(), data, mobName);
                onMapChange(getCurrentTile(), getCurrentColli(), getCurrentEntity());


            }
            else {
                cout << "Error: collided enemy's creature is null." << endl;
            }
        }

    }

    // Display
    void render() {
        this->window->clear();

        // Utiliser la vue du joueur pour afficher les éléments du jeu
        this->window->setView(playerView);

        // afficher la carte
        for (const auto& row : this->mapManager->getTileMap()) {
            for (const auto& tile : row) {
                this->window->draw(tile);
            }
        }

        // afficher les murs
        for (const auto& wall : this->wall->getWalls()) {
            this->window->draw(wall);
        }

        // afficher le joueur
        this->window->draw(this->player->getPlayer());

        // afficher les ennemis
        for (auto& enemy : this->enemies) {
            enemy.drawEnemy(*this->window);
        }

        // les coffres
        for (auto& chest : this->chests) {
            chest.draw(*this->window);
        }

		// les coffres pieges
		for (auto& trappedChest : this->trappedChests) {
			trappedChest.draw(*this->window);
		}

        // Utiliser la vue de l'interface utilisateur pour afficher les éléments de l'interface
        this->window->setView(uiView);
        this->inventory->draw(*this->window);
        this->inventory->drawChest(*this->window);
        if (inventory->getIsSecondaryGridVisible()) {
            inventory->drawSecondaryGrid(*this->window);
        }
        this->window->display();
    }

    // Methode pour gérer le lancement du jeu
    void run() {
        this->initMenuWindow();

        if (this->window == nullptr) {
            this->initGameWindow(); // Initialiser la fenêtre de jeu si elle n'est pas déjà initialisée
        }

        while (this->window->isOpen()) {
            this->updateDT();
            this->update();
            this->render();
        }
    }


    void viewOnPlayer() {
        this->playerView.setCenter(player->getPositionPlayer());
    };

    void onMapChange(string NewTileMap, string NewCollisionMap, string NewEntityMap) {
        this->mapManager->loadNewMap(NewTileMap, NewCollisionMap);
        if (NewTileMap == "Config/tileTypes6.txt") {
            this->currentMap = 6;
            std::cout << currentMap << std::endl;
            clearChest();
            clearTrappedChest();
            initializeChests();
            initializeTrappedChests();
        }
        else if (NewTileMap == "Config/tileTypes7.txt") {
            clearChest();
            clearTrappedChest();
            loadLichTexture();
            initLichSprite();
            if (data.soundEnabled) {
                if (!data.backgroundMusic.openFromFile("Soul of Cinder.mp3")) {
                    std::cerr << "Erreur de chargement de la musique de fond" << std::endl;
                }
                else {
                    data.backgroundMusic.setLoop(true);  // Faire boucler la musique
                    data.backgroundMusic.play();         // Démarrer la musique
                }
            }
        }
        else {
            clearChest();
            clearTrappedChest();
            currentMap++;
            std::cout << currentMap << std::endl;
        }
        this->wall->resetCollisions();
        this->enemies = Enemy::createEnemies(NewEntityMap, *this->mapManager);
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

    string getMobName(int mobId) {
        switch (mobId) {
        case 5:
            return "Troll Rhetoricien";
        case 6:
            return "Gobelin Sarcastique";
        case 7:
            return "Canard Explosif";

        default:
            return "Troll Rhetoricien";
        }
    }

    static std::shared_ptr<Entity> createEntity(const string& type) {
        if (type == "Hero")
            return make_shared<Heroes>();
        else if (type == "Monstre")
            return make_shared<Creatures>();
    }

    string getCurrentTile() {

        return "Config/tileTypes" + to_string(player->getMapIteration()) + ".txt";

    };

    string getCurrentColli() {

        return "Config/collisionMap" + to_string(player->getMapIteration()) + ".txt";

    };

    string getCurrentEntity() {

        return "Config/entityMap" + to_string(player->getMapIteration()) + ".txt";

    };

    void entityInit(string jobName, string raceName, GameData& data, string mobName) {
        string mobType = mobName;
        string statistics[6] = { "COU", "CHA", "INT", "FO", "AD", "HP" };

        Jobs* job = createJobs(jobName);
        Race* race = createRace(raceName);
        Common* mob = createMob(mobType);
        Boss* lich = new ProgramLich();

        std::shared_ptr<Entity> mainCharacter = createEntity("Hero");
        std::shared_ptr<Entity> Character1 = createEntity("Hero");
        std::shared_ptr<Entity> Character2 = createEntity("Hero");
        std::shared_ptr<Entity> Mob1 = createEntity("Monstre");
        //std::shared_ptr<Entity> Mob2 = createEntity("Monstre");
        //std::shared_ptr<Entity> Mob3 = createEntity("Monstre");
        //std::shared_ptr<Entity> Mob4 = createEntity("Monstre");
        std::shared_ptr<Entity> Boss = createEntity("Monstre");
        Group* Heros = new Group();
        Group* Monstres = new Group();

        // Utilisation des valeurs de charaRace et charaJob de GameData
        mainCharacter->StatComparison(*createRace(getCharaRace()), *createJobs(getCharaJob()));
        mainCharacter->initDesc(*createRace(getCharaRace()), *createJobs(getCharaJob()));
        mainCharacter->initName(*createRace(getCharaRace()), *createJobs(getCharaJob()));
        mainCharacter->initHeroStat(*createRace(getCharaRace()), *createJobs(getCharaJob()));
        std::cout << mainCharacter->getName() << endl;
        std::cout << mainCharacter->getDesc() << endl;
        for (auto stat : statistics)
            std::cout << mainCharacter->getStat()[stat] << endl;

        // hero numero 1
        Character1->StatComparison(*race, *job);
        Character1->initDesc(*race, *job);
        Character1->initName(*race, *job);
        Character1->initHeroStat(*race, *job);

        // hero numero 2
        Character2->StatComparison(*race, *job);
        Character2->initDesc(*race, *job);
        Character2->initName(*race, *job);
        Character2->initHeroStat(*race, *job);

        // monstre numero 1
        Mob1->initCreatureDesc(*mob);
        Mob1->initCreatureName(*mob);
        Mob1->initCreatureStat(*mob);

        //// monstre numero 2
        //Mob2->initCreatureDesc(*mob);
        //Mob2->initCreatureName(*mob);
        //Mob2->initCreatureStat(*mob);

        //// monstre numero 3
        //Mob3->initCreatureDesc(*mob);
        //Mob3->initCreatureName(*mob);
        //Mob3->initCreatureStat(*mob);

        //// monstre numero 4
        //Mob4->initCreatureDesc(*mob);
        //Mob4->initCreatureName(*mob);
        //Mob4->initCreatureStat(*mob);

        // boss
        Boss->initBossName(*lich);
        Boss->initBossDesc(*lich);
        Boss->initBossStat(*lich);

        Monstres->addParty(Mob1);
        //Monstres->addParty(Mob2);
        //Monstres->addParty(Mob3);
        //Monstres->addParty(Mob4);
        Heros->addParty(mainCharacter);
        Heros->addParty(Character2);
        Heros->addParty(Character1);

        // Heros->removeParty(Character1);

        Fight* combat = new Fight(*Heros, *Monstres);
        // Affichage de l'ordre de combat 
        auto ordre = combat->fightOrder();
        while (!ordre.empty()) {
            std::cout << ordre.front()->getName() << std::endl;
            ordre.pop();
        }

        combat->fighting(*mob, *lich, *race, *job);
    }
};

