``` mermaid
 classDiagram
    class Hero {
        - string heroName;
        - string heroDesc;
        - string heroRace;
        - string heroJob;
        - map  heroStat:string, int;
        - bool possible;
        - bool isAlive = true;
        - int heroLevel = 1;
        - int exp = 0;
        - int expMax = 30;

        + Heroes (string)
        + StatCoparison(Race& , Jobs& ) void
        + initName(Race& , Jobs& ) string 
        + initDesc(Race& , Jobs& ) string
        + virtual initHeroStat(Race& , Jobs& ) map :string, int 
        + getName() string
        + getDesc() string
        + getStat() map : string, int
        + setHeroHealth(int) void
        + setHeroCourage(int) void
        + setHeroCharsim(int) void
        + setHeroStrengh(int) void
        + setHeroIntelligence(int) void
        + setHeroDexterity(int) void
        + transiLevel() void
        + const getHeroLevel() int
        + const getHeroAlive() bool
        + const getRaceSpell(Race& , Creatures& ) string
        + const getJobSpell(Jobs& , Creatures& ) string
        + isHeroAlive() bool

    }

    class Party {
        -HeroParty vector
        -CreatureParty vector
        +getHeroParty() vector
        +getcreatureParty() vector
    }

    class Jobs {
        <<abstract>>
        + virtual  getNameJob() string
        + virtual  getDescJob() string
        + virtual  getSpellName() string
        + virtual  jobSpell(Creatures& , map : string, int) string
        + virtual  getStatRequiredJob() map : string, int
    }

    class Warrior {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(Creatures&, map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(Creatures&, map : string, int) map : string, int
    }

    class Ranger {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(Creatures&, map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(Creatures&, map : string, int) map : string, int
    }

    class Sorcerer{
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(Creatures&, map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(Creatures&, map : string, int) map : string, int
    }

    class Thief {
        - name string 
        - desc string  
        - spellName string 
        - requiredStat map : string, int

        # getNameJob() string
        # getDescJob() string
        # getSpellName() string
        # getBasicAttack(Creatures&, map : string, int) string
        # getStatJob() map: string, int
        # jobSpell(Creatures&, map : string, int) map : string, int
    }

    class Race {
        <<abstract>>
        + virtual  getNameRace() string
        + virtual  getDescRace() string
        + virtual  getSpellName() string
        + virtual  basicAttack(Creatures& , map: string, int ) string
        + virtual  getStat() map : string, int
        + virtual  raceSpell(Creatures& , map : string, int>) map : string, int
    }

    class Elf {
        -name string
        -desc string 
        -spellName string
        -stat map : string , int

        # getNameJob() string
        # getDescJob() string
        # getSpellName () string
        # basicAttack (Creatures&, map : string, int) string
        # raceSpell (Creatures&, map : string , int) string 
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
        # basicAttack (Creatures&, map : string, int) string
        # raceSpell (Creatures&, map : string , int) string 
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
        # basicAttack (Creatures&, map : string, int) string
        # raceSpell (Creatures&, map : string , int) string 
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
        # basicAttack (Creatures&, map : string, int) string
        # raceSpell (Creatures&, map : string , int) string 
        # getStat() map(string, int)
    }

    class Creature {
        - creatureName string
        - creatureDesc string
        - isAlive bool
        - creatureStat map : string, int

        + initCreatureName(Common&) string
        + initCreatureDesc (Common&) string
        + initCreatureStat (Common&) map : string, int
        + getCreatureName () string
        + getCreatureDesc() string
        + getCreatureStat () map : string, int
        + getCreatureAlive () bool
        + setCreatureHealth (int) void
        + setCreatureCourage (int) void
        + setCreatureCharism (int) void
        + setCreatureStrengh (int) void
        + setCreatureIntelligence (int) void
        + setCreatureDexterity (int) void
        + isCreatureAlive () void
        + getMonsterSpell (Common&, Heroes&) string
        + const getBasicAttack (Common&, Heroes&) string
     }

    class Boss {
        <<abstract>>
        + virtual getNameCreature() string
        + virtual getStatCreature() map(string, int)
        + virtual getDescCreature() string
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
    }

    class ProgramLich{
        - name string
        - desc string
        + getNameCreature() string
        + getDescCreature() string
        # virtual getStatCreature() map(string, int)
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
    }

        class Pattern1 {
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        + get getStat() map (string, int)
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Pattern2 {
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        + get getStat() map (string, int)
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Common {
        <<abstract>>
        + virtual getName() string
        + virtual getDesc() string
        + virtual getSpellName() string 
        + virtual basicAttack (Heroes&, map : string, int)
        + virtual getStat() map(string, int)
        + virtual monsterSpell(Heroes&, map : string , int) map : string, int
    }

    class SarcasticGobelin{
        - name string 
        - desc string 
        - spellName string
        - stat map: string, int

        # getName() string
        # getDesc() string 
        # getSpellName() string
        # basicAttack (Heroes&, map : string, int) string
        # monsterSpell (Heroes&, map : string, int) map : string, int
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
        # basicAttack (Heroes&, map : string, int) string
        # monsterSpell (Heroes&, map : string, int) map : string, int
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
        # basicAttack (Heroes&, map : string, int) string
        # monsterSpell (Heroes&, map : string, int) map : string, int
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

    class Menus {

    }


    class Movement {
        - speed float
        - x float
        - y float
        + Movement(float initialSpeed)
        + getSpeed() float
        + void setSpeed(float newSpeed)
        + void move(sf::Vector2f &mapOffset)
        + getX() float
        + getY() float
    }

    class Sprites {

    }

    class Camera {

    }

    class Audio {

    }

    class Scene{

    }

    class Map{

    }

    class Ability {

    }

    class DiceRolls {
        -int sides
        -unsigned long seed
        -unsigned long random()
        +DiceRoll(int sides=6, unsigned long initialSeed=1)
        +int roll()
        +int getSides() const
        +void setSides(int newSides)
        +void setSeed(unsigned long newSeed)
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


    class System {
        <<Interface>>
    }

    class Player {

    }

    class Fight {

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

    Hero o-- Party

    Creature <-- Common
    Common <-- RhetoricianTroll
    Common <-- SarcasticGobelin
    Common <-- ExplosiveDuck
    Creature <-- Boss
    Boss <-- ProgramLich
    ProgramLich <-- Pattern1
    Pattern1 <-- Pattern2
    
    System <-- Camera
    System <-- Audio
    System <-- Sprites
    System <-- Menus
    System <-- Player
    Player <-- Movement
    System <-- Fight
    Fight <-- DiceRolls
    System <-- Map
    Map <-- Scene
    Inventory <-- Items
    Player <-- Inventory
    
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
