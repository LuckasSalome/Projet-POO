```mermaid

classDiagram

    class Entity {
        <<abstract>>
        virtual getName() string
        virtual getDesc() string
        virtual getStat() map: string, int 
        virtual getAlive() bool
        virtual getHeroType() bool
        virtual getIsBoss() bool
        virtual setHealth(int) void
        virtual setCourage(int) void
        virtual setStrengh(int) void
        virtual setIntelligence(int) void
        virtual setDexterity(int) void
        virtual setCharism(int) void
        virtual initHeroStat(Race& , Jobs& )  map: string, int
        virtual initDesc(Race& , Jobs& ) string
        virtual initName(Race& , Jobs& ) string 
        virtual StatComparison(Race& race, Jobs& job) void 
        virtual initCreatureName(Common& mob) string 
        virtual initCreatureDesc(Common& mob)  string 
        virtual initCreatureStat(Common& mob) map :string, int 
        virtual initBossName(Boss& mob) string 
        virtual initBossDesc(Boss& mob) string 
        virtual initBossStat(Boss& mob) map:string, int
        virtual getJobSpell(Jobs& job, std::shared_ptr<Entity> foe) string 
        virtual getRaceSpell(Race& race, std::shared_ptr<Entity> foe) string 
        virtual getBasicAttack(Race& race, std::shared_ptr<Entity> foe) string 
        virtual getMonsterSpell(Common& mob, std::shared_ptr<Entity> ennemy) string 
        virtual getBasicAttack(Common& mob, std::shared_ptr<Entity> ennemy) string 
        virtual getBossSpell1(Boss& mob, std::shared_ptr<Entity> ennemy) string 
        virtual getBossSpell2(Boss& mob, std::shared_ptr<Entity> ennemy) string 
    }

    class Hero {
        -  heroName string
        - heroDesc string
        - heroRace string
        - heroJob string
        - heroStat map: string, int
        - heroStatPerma const map : string, int
        - possible bool
        - isAlive bool
        - heroLevel int
        - exp int
        - expMax int

        + Heroes (string)
        + StatCoparison(Race& , Jobs& ) void
        + initName(Race& , Jobs& ) string 
        + initDesc(Race& , Jobs& ) string
        + initHeroStat(Race& , Jobs& ) map :string, int 
        + getName() string
        + getDesc() string
        + getStat() map : string, int
        + getHeroLevel()cosnt int
        + getAlive() bool 
        + setHeroHealth(int) void
        + setHeroCourage(int) void
        + setHeroCharsim(int) void
        + setHeroStrengh(int) void
        + setHeroIntelligence(int) void
        + setHeroDexterity(int) void
        + transiLevel() void
        + getHeroLevel() int
        + getHeroAlive() bool
        + getRaceSpell(Race& , shared_ptr(Entity) ) string
        + getJobSpell(Jobs& , shared_ptr(Entity) ) string
        + isHeroAlive() bool

    }

    class Group {
        - vector : shared_ptr(Entity)

        + addParty(shared_ptr(Entity)) void 
        + removeParty(shared_ptr(Entity)) void 
        + getGroup() vector : shared_ptr(Entity) 
        + isGroupEmpty() bool
    }

    class Jobs {
        <<virtual>>
        + virtual getNameJob() string
        + virtual getDescJob() string
        + virtual getSpellName() string
        + virtual jobSpell(shared_ptr(Entity) , map : string, int) string
        + virtual getStatRequiredJob() map : string, int
    }

    class Warrior {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(shared_ptr(Entity), map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(shared_ptr(Entity), map : string, int) map : string, int
    }

    class Ranger {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(shared_ptr(Entity), map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(shared_ptr(Entity), map : string, int) map : string, int
    }

    class Sorcerer{
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(shared_ptr(Entity), map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(shared_ptr(Entity), map : string, int) map : string, int
    }

    class Thief {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(shared_ptr(Entity), map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(shared_ptr(Entity), map : string, int) map : string, int
    }

    class Race {
        <<abstract>>
        + virtual  getNameRace() string
        + virtual  getDescRace() string
        + virtual  getSpellName() string
        + virtual  basicAttack(shared_ptr(Entity) , map: string, int ) string
        + virtual  getStat() map : string, int
        + virtual  raceSpell(shared_ptr(Entity) , map : string, int>) map : string, int
    }

    class Elf {
        -name string
        -desc string 
        -spellName string
        -stat map : string , int

        # getNameJob() string
        # getDescJob() string
        # getSpellName () string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # raceSpell (shared_ptr(Entity), map : string , int) string 
        # getStat() map(string, int)
    }

    class Dwarf {
        - name string
        - desc string 
        - spellName string
        - stat map : string , int

        # getNameJob() string
        # getDescJob() string
        # getSpellName () string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # raceSpell (shared_ptr(Entity), map : string , int) string 
        # getStat() map(string, int)
    }

    class Human {
        - name string
        - desc string 
        - spellName string
        - stat map : string , int

        # getNameJob() string
        # getDescJob() string
        # getSpellName () string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # raceSpell (shared_ptr(Entity), map : string , int) string 
        # getStat() map(string, int)
    }

    class Barbarian {
        - name string
        - desc string 
        - spellName string
        - stat map : string , int

        # getNameJob() string
        # getDescJob() string
        # getSpellName () string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # raceSpell (shared_ptr(Entity), map : string , int) string 
        # getStat() map(string, int)
    }

    class Creature {
        - creatureName string
        - creatureDesc string
        - creatureStat map : string, int
        - isAlive bool
        - cond bool
        - isBoss bool
        + initCreatureName(Common&) string
        + initCreatureDesc (Common&) string
        + initCreatureStat (Common&) map : string, int
        + initBossName(Common&) string
        + initBossDesc (Common&) string
        + initBossStat (Common&) map : string, int
        + getName () string
        + getDesc() string
        + getStat () map : string, int
        + getIsAlive () bool
        + getIsBoss () bool
        + heroType () bool
        + setHealth (int) void
        + setCourage (int) void
        + setCharism (int) void
        + setStrengh (int) void
        + setIntelligence (int) void
        + setDexterity (int) void
        + getMonsterSpell (Common&, shared_ptr(Entity)) string
        + const getBasicAttack (Common&, shared_ptr(Entity)) string
        + getBossSpell1 (Boss&, shared_ptr(Entity)) string
        + getBossSpell2 (Boss&, shared_ptr(Entity)) string
     }

    class Boss {
        <<virtual>>
        + virtual getBossName() string
        + virtual getBossDesc() string
        + virtual getSpellName1(bool) string
	    + virtual getSpellName2(bool) string
	    + virtual getBossStat() map: string, int 
	    + virtual bossSpell1(shared_ptr(Entity) , map<string, int> , bool ) map: string, int
	    + virtual bossSpell2(shared_ptr(Entity) , map<string, int> , bool ) map: string, int
    }

    class ProgramLich{
        - name string
        - desc string
        - spellName1P1 string
        - spellName1P2 string
        - spellName2P1 string
        - spellName2P2 string

        # getBossName() string
        # getBossDesc() string
        # getSpellName1(bool) string
        # getSpellName2(bool) 
        # getBossStat()  map :string, int
        # bossSpell1(shared_ptr(Entity) , map:string, int , bool )  map :string, int
        # bossSpell2(shared_ptr(Entity) , map:string, int , bool )  map :string, int
    
    }



    class Common {
        <<virtual>>
            + virtual string getName() 
            + virtual string getDesc() 
            + virtual string getSpellName() 
            + virtual void basicAttack(shared_ptr(Entity) , map:string, int ) 
            + virtual getStat() map:string, int
            + virtual monsterSpell(shared_ptr(Entity) , map<string, int> ) map:string, int
    }

    class SarcasticGobelin{
        - name string 
        - desc string 
        - spellName string
        - stat map: string, int

        # getName() string
        # getDesc() string 
        # getSpellName() string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # monsterSpell (shared_ptr(Entity), map : string, int) map : string, int
        # getStat () map : string, int
    }

    class RhetoricianTroll{
        - name string 
        - desc string 
        - spellName string
        - stat map: string, int

        # getName() string
        # getDesc() string 
        # getSpellName() string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # monsterSpell (shared_ptr(Entity), map : string, int) map : string, int
        # getStat () map : string, int
    }

    class ExplosiveDuck {
        - name string 
        - desc string 
        - spellName string
        - stat map: string, int

        # getName() string
        # getDesc() string 
        # getSpellName() string
        # basicAttack (shared_ptr(Entity), map : string, int) string
        # monsterSpell (shared_ptr(Entity), map : string, int) map : string, int
        # getStat () map : string, int
    }

    class Inventory {
        - size_t rows
        - size_t cols
        - size_t slotSize
        - vector<vector<Items*>> inventoryGrid
        - Items* selectedItem
        - Font& font
        - RectangleShape infoPanel
        - Text infoText
        - bool isOpen
        - Items* weaponSlot
        - Items* chestSlot
        - Items* bootsSlot
        - Vector2f weaponSlotPos
        - Vector2f chestSlotPos
        - Vector2f bootsSlotPos

        + Inventory(size_t rows, size_t cols, Font& font)
        + void toggleInventory()
        + bool getIsOpen() const
        + void addItem(size_t row, size_t col, Items* item)
        + void handleMouseClick(Vector2i mousePos, RenderWindow& window)
        + void unequipItem(const string& slotType)
        + void drawEquipmentSlot(RenderWindow& window, Vector2f position, Items* item, const string& label)
        + void draw(RenderWindow& window)
    }

    

    class Animation {
        -Vector2u imageCount
        -Vector2u currentImage
        -float TotalTime
        -float SwitchTime
        +IntRect uvRect
        +Animation(Texture* texture, Vector2u imageCount, float SwitchTime)
        +~Animation()
        +void update(int row, float deltaTime, bool faceRight)
        +void setSwitchTime(float switchTime)
    }

    class Enemy {
    
        -RectangleShape enemy
        -CircleShape hitbox
        -Vector2f position
        -map<int, Texture> enemyTex
        -Player* player
        -MapManager* mapMan
        -bool defeated
        -Creatures* creature
        -void loadEnemyTexture()
        -void initHitbox()
        +Enemy(Vector2f pos, int textureKey, bool def = false)
        +void drawEnemy(RenderWindow& window)
        +CircleShape getHitbox() const
        +RectangleShape getEnemy()
        +Vector2f getPosition() const
        +bool isDefeated() const
        +void setDefeated(bool def, const string& entityMapFile)
        +static vector<Enemy> reloadEnemies(const string& entityMapFile, MapManager& mapMan)
        +void updateEntityMapFile(const string& entityMapFile, const vector<Enemy>& enemies)
        +void markEnemyAsDefeated(const string& entityMapFile)
        +static vector<Enemy> createEnemies(const string& entityMapFile, MapManager& mapMan)
        +static Enemy* checkCollisions(Player& player, vector<Enemy>& enemies)
        +static void saveEnemies(const string& filename, const vector<Enemy>& enemies, MapManager& mapMan)
        +Creatures* getCreature() const
        +int getTextureKey() const
        +static void resetEnemyDefeatedState(const string& entityMapFile)
    }
    
    class Player {
        - RectangleShape player
        - Texture playerTex
        - View playerView
        - MapManager* mapManager
        - Vector2f velocity
        - const float movementSpeed
        - FloatRect playerBounds
        - FloatRect nextPos
        - Vector2f direction
        - mapChangeCallback : callback(string, string)
        - Animation* animation
        - float animationSpeed
        - bool faceRight
        - const int COLLISION_TRIGGER
        - const int COLLISION_TRIGGER_BACK
        - int mapIteration
        + Player(MapManager* mapManager, function<void(string, string)> mapChangeCallback)
        + ~Player()
        + void playerMovement(float dt, const std::vector<RectangleShape>& walls, MapManager& mapManager)
        + const RectangleShape& getPlayer() const
        + Vector2f getPositionPlayer()
        + FloatRect getPlayerBounds()
        + void playerInit(int colonne, int ligne, string race)
        + void setHumanTex()
        + void setBarbarianTex()
        + void setDwarfTex()
        + void setElfTex()
        + void loadPreviousMap()
    }

    class Items{
        - string name
        - string description
        - map<string, int> stats
        - Texture texture
        - Sprite sprite

        + Items(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        + ~Items()
        + bool isChestArmor() const
        + bool isBoots() const
        + bool isWeapon() const
        + const string& getName() const
        + const string& getDescription() const
        + const map<string, int>& getStats() const
        + const Sprite& getSprite() const
    }

    class ChestArmor {
        + ChestArmor(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        + bool isChestArmor() const
    }

    class Boots {
        + Boots(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        + bool isBoots() const
    }

     class Weapon {
        + Weapon(const string& name, const string& description, const map<string, int>& stats, const string& spritePath)
        + bool isWeapon() const
    }

    class MapManager {
        - vector<vector<int>> tileTypes
        - vector<vector<int>> collisionMap
        - vector<vector<RectangleShape>> tileMap
        - map<int, Texture> textures
        - float gridSize
        - int mapSize
        - const int COLLISION_TRIGGER
        - void loadTextures()
        - void initTileMap()
        - void loadTileTypes(string& filename)
        - void loadCollisionMap(string& filename)
        + MapManager(float gridSize, int mapSize, const string& tileTypesFile, const string& collisionMapFile)
        + const vector<vector<RectangleShape>>& getTileMap() const
        + const vector<vector<int>>& getCollisionMap() const
        + float getGridSize()
        + void loadNewMap(const string& newTileTypesFile, const string& newCollisionMapFile)
        + void setTileTypes(const vector<vector<int>>& newTileTypes)
        + void setCollisionMap(const vector<vector<int>>& newCollisionMap)
    }


    class System {
        <<Interface>>
    }


    class Fight {
        - group1 vector:shared_ptr(Entity )
        - group2 vector:shared_ptr(Entity)
        - heroes Group& 
        - monsters Group& 

        + Fight(Group& , Group& )
        + fightOrder() queue : shared_ptr(Entity)
        + roundCheck() void
        + fighting(Common& , Boss& , Race& , Jobs& ) void
    }

    class BeerPotion{
        +BeerPotion
    }

    class PotionIntelligence {
        +PotionIntelligence()
    }

    class MajorHealingPotion {
        +MajorHealingPotion
    }

    class RustyKey {
        +RustyKey
    }

    class KeyCorridor {
        +KeyCorridor()
    }

    class RopeTrap {
        +RopeTrap()
    }

    class BookOfLostRules {
        +BookOfLostRules()
    }

    
    class DiscretionShoesNoisy {
        +DiscretionShoesNoisy()
    }

    class StealBoots {
        +StealBoots()
    }

    class DarkBoots {
        +DarkBoots()
    }

    class SorcererBoots {
        +SorcererBoots()
    }

    class LeatherBoots {
        +LeatherBoots()
    } 

    class BluntSword {
        +BluntSword()
    }

    class Bow {
        +Bow()
    }

    class Dagger {
        +Dagger()
    }

    class Sword {
        +Sword()
    }

    class SorcererStick {
        +SorcererStick()
    }

    class ScepterSyntactic {
        +ScepterSyntactic()
    }

    class DarkCape {
        +DarkCape()
    }

    class ChainMail {
        +ChainMail()
    }

    class LeatherChest {
        +LeatherChest()
    }

    class SorcererCape {
        +SorcererCape()
    }

    class GameData {
        +RenderWindow window
        +Texture backgroundTexture
        +Sprite background
        +Font font
        +RectangleShape menuRect
        +RectangleShape selectionRect
        +Text menuItems[3]
        +int currentSelection
        +Hero* currentCharacter
        +Music backgroundMusic
        +bool soundEnabled
        +Keyboard::Key upKey
        +Keyboard::Key downKey
        +Keyboard::Key actionKey
        +Keyboard::Key cancelKey
        +Keyboard::Key leftKey
        +Keyboard::Key rightKey
        +int windowWidth
        +int windowHeight
        +string keyToString(Keyboard::Key key)
        +~GameData()
    }

    class MainMenu {
        +static initMainMenu(GameData& data)
        +static handleMainMenuEvents(GameData& data, bool& inOptionsMenu, bool &inCharacterSelection)
        +static renderMainMenu(GameData& data)
    }

    class OptionsMenu {
        +static listenForKeyPress(RenderWindow& window) Keyboard::Key
        +static handleOptionsMenu(GameData& data, bool& inOptionsMenu)
    }

    class ChoixPerso {
        +static handleCharacterSelection(GameData& data, bool& inCharacterSelection, Event& event) string
    }

    class Collision {
        -vector~RectangleShape~ walls
        -MapManager* mapManager
        -Player* player
        -float windowWidth
        -float windowHeight
        -void collisionInit()
        +Collision(MapManager* mapManager, Player* player, float windowWidth, float windowHeight)
        +vector~RectangleShape~ getWalls() const
        +void setWallsColor(const Color& color)
        +void resetCollisions()
    }

    Entity --o Hero
    Entity --o Creature

    Hero --o Race
    Hero --o Jobs
    Jobs <-- Warrior
    Race <-- Elf
    Race <-- Barbarian
    Race <-- Dwarf
    Race <-- Human
    Jobs <-- Ranger
    Jobs <-- Sorcerer
    Jobs <-- Thief
    Game <-- MapManager
    Player <-- MapManager
    Player <-- Animation
    Player <-- ChoixPerso
    Enemy <-- MapManager
    Enemy <-- player
    Enemy <-- Creature
    Enemy <-- Fight
    GameData *-- Hero 
    MainMenu ..> GameData 
    OptionsMenu ..> GameData 
    ChoixPerso ..> GameData


    Hero o-- Group

    Creature <-- Common
    Common <-- RhetoricianTroll
    Common <-- SarcasticGobelin
    Common <-- ExplosiveDuck
    Creature <-- Boss
    Boss <-- ProgramLich
    Collision <-- Player
    Collision <-- MapManager

    Inventory <-- Items
    
    
    Items <-- BeerPotion
    Items <-- PotionIntelligence       
    Items <-- MajorHealingPotion
    Items <-- KeyCorridor
    Items <-- RustyKey
    Items <-- RopeTrap
    Items <-- BookOfLostRules
    Items <-- ChestArmor
    Items <-- Boots
    Items <-- Weapon

    ChestArmor <-- ChainMail  
    ChestArmor <-- LeatherChest
    ChestArmor <-- DarkCape
    ChestArmor <-- SorcererCape

    Boots <-- DiscretionShoesNoisy
    Boots <-- StealBoots
    Boots <-- LeatherBoots
    Boots <-- DarkBoots
    Boots <-- SorcererBoots

    Weapon <-- BluntSword
    Weapon <-- ScepterSyntactic
    Weapon <-- Sword
    Weapon <-- Bow
    Weapon <-- Dagger
    Weapon <-- SorcererStick
```

```
