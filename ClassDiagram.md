```mermaid
---
title: CESI & Dragons , L'Épique Donjon du Code
---
classDiagram
    class Entity {

    }

    class Hero {
        -HeroName string
        -map HeroStat : string, int
        -HeroDesc string
        -map HeroItems : string, int
        -map HeroAbility1 : string, int
        -map HeroAbility2 : string, int
        -map HeroAbility3 : string, int
        # virtual getNameJob() string
        # virtual getStatJob() map(string, int)
        # virtual getDescJob() string
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
        # virtual getNameRace() string
        # virtual getStatRace() map<string, int>
        # virtual getDescRace() string
        +get HeroStat() map(string, int)
        +get HeroName() string
        +get HeroDesc() string
        +get HeroItems() map(string, int)

    }

    class Creature {
        <<abstract>>
        # virtual getNameCreature() string
        # virtual getStatCreature() map(string, int)
        # virtual getDescCreature() string
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
    }

    class Party {
        -HeroParty vector 
        -CreatureParty vector
        +getHeroParty() vector
        +getcreatureParty() vector
    }

    class Jobs {
        <<abstract>>
        # virtual getNameJob() string
        # virtual getStatJob() map(string, int)
        # virtual getDescJob() string
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
    }

    class Race {
        <<abstract>>
        # virtual getNameRace() string
        # virtual getStatRace() map<string, int>
        # virtual getDescRace() string


    }

    class Boss {
        <<abstract>>
        # virtual getNameCreature() string
        # virtual getStatCreature() map(string, int)
        # virtual getDescCreature() string
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

    class Common {
        <<abstract>>
        # virtual getNameCreature() string
        # virtual getStatCreature() map(string, int)
        # virtual getDescCreature() string
        # virtual getAbility1(string) map(string,int)
        # virtual getAbility2(string) map(string,int)
        # virtual getAbility3(string) map(string,int)
    }

    class SarcasticGobelin{
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameCreature() string
        +getStatCreature() map(string, int)
        +getDescCreature() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class RhetoricianTroll{
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameCreature() string
        +getStatCreature() map(string, int)
        +getDescCreature() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class ExplosiveDuck {
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameCreature() string
        +getStatCreature() map(string, int)
        +getDescCreature() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Inventory {

    }

    class Menus {

    }

    class Patern1 {
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        + get getStat() map (string, int)
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Patern2 {
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        + get getStat() map (string, int)
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Movement {

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

    }

    class Items{

    }

    class Elf {
        -name : string 
        -map stat : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string

    }

    class Warrior {
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
        +getAbility1()
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Ranger {
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Sorcerer{
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Thief {
        -name : string 
        -map stat : string , int
        -map Ability1 : string , int
        -map Ability2 : string , int
        -map Ability3 : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
        + getAbility1(string) map(string,int)
        + getAbility2(string) map(string,int)
        + getAbility3(string) map(string,int)
    }

    class Dwarf {
        -name : string 
        -map stat : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
    }

    class Human {
        -name : string 
        -map stat : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
    }

    class Barbarian {
        -name : string 
        -map stat : string , int
        -desc : string
        +getNameJob() string
        +getStatJob() map(string, int)
        +getDescJob() string
    }

    class System {
        <<Interface>>
    }

    class Player {

    }

    class Fight {

    }

    class BeerPotion{

    }

    class RustyKey {

    }

    class PotionIntelligence {

    }

    class RopeTrap {

    }

    class KeyCorridor {

    }

     class DiscretionShoesNoisy {

    }


    class BluntSword {

    }

    class MajorHealingPotion {

    }

    class ScepterSyntactic {

    }

    class BookOfLostRules {

    }

Entity <--Hero
Hero <-- Race
Hero <-- Jobs
Entity <-- Creature
Creature <-- Common
Creature <-- Boss
Boss <-- ProgramLich
ProgramLich <-- Patern1
Patern1 <-- Patern2
Hero o-- Party
Jobs <-- Warrior
Race <-- Elf
Race <-- Barbarian
Race <-- Dwarf
Race <-- Human
Jobs <-- Ranger
Jobs <-- Sorcerer
Jobs <-- Thief
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
Warrior --o Ability
Ranger --o Ability
Sorcerer --o Ability
Thief --o Ability
RhetoricianTroll --o Ability
ExplosiveDuck --o Ability
SarcasticGobelin --o Ability
Inventory <-- Items
Player <-- Inventory
Common <-- RhetoricianTroll
Common <-- SarcasticGobelin
Common <-- ExplosiveDuck
Items <-- RustyKey
Items <-- BeerPotion
Items <-- PotionIntelligence
Items <-- RopeTrap
Items <-- KeyCorridor
Items <-- DiscretionShoesNoisy
Items <-- BluntSword
Items <-- MajorHealingPotion
Items <-- ScepterSyntactic
Items <-- BookOfLostRules
```
