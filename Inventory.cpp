#include <SFML/Graphics.hpp>
#include <iostream>
#include "Inventory.hpp"
#include "PotionIntelligence.hpp"
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

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(1920, 1080), "Inventory System");
    Font font;
    if (!font.loadFromFile("images/RobotoBlack.ttf")) {
        cerr << "Error: Unable to load font 'RobotoBlack.ttf'!" << endl;
        return 1;
    }
    Inventory inventory(5, 5, font);

    PotionIntelligence potionIntelligence;
    inventory.addItem(0, 0, &potionIntelligence);
    RustyKey rustyKey;
    inventory.addItem(0, 1, &rustyKey);
    BeerPotion beerPotion;
    inventory.addItem(0, 2, &beerPotion);
    Weapon* bluntsword = new BluntSword();
    inventory.addItem(0, 3, bluntsword);
    KeyCorridor keyCorridor;
    inventory.addItem(0, 4, &keyCorridor);
    BookOfLostRules bookOfLostRules;
    inventory.addItem(1, 0, &bookOfLostRules);
    DiscretionShoesNoisy discretionShoesNoisy;
    inventory.addItem(1, 1, &discretionShoesNoisy);
    MajorHealingPotion majorHealingPotion;
    inventory.addItem(1, 2, &majorHealingPotion);
    RopeTrap ropeTrap;
    inventory.addItem(1, 3, &ropeTrap);
    ScepterSyntactic scepterSyntactic;
    inventory.addItem(2, 0, &scepterSyntactic);
    Weapon* bow = new Bow();
    inventory.addItem(2, 1, bow);
    Weapon* sword = new Sword();
    inventory.addItem(4, 2, sword);
    Weapon* dagger = new Dagger();
    inventory.addItem(2, 2, dagger);
    Weapon* sorcererStick = new SorcererStick();
    inventory.addItem(2, 3, sorcererStick);
    Boots* stealBoots = new StealBoots();
    inventory.addItem(2, 4, stealBoots);
    Boots* leatherBoots = new LeatherBoots();
    inventory.addItem(3, 0, leatherBoots);
    Boots* darkBoots = new DarkBoots();
    inventory.addItem(3, 1, darkBoots);
    Boots* sorcererBoots = new SorcererBoots();
    inventory.addItem(3, 2, sorcererBoots);
    ChestArmor* chainMail = new ChainMail();
    inventory.addItem(3, 3, chainMail);
    ChestArmor* leatherChest = new LeatherChest();
    inventory.addItem(3, 4, leatherChest);
    ChestArmor* darkCape = new DarkCape();
    inventory.addItem(4, 0, darkCape);
    ChestArmor* sorcererCape = new SorcererCape();
    inventory.addItem(4, 1, sorcererCape);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::I) {
                    inventory.toggleInventory();
                }
            }
            else if (event.key.code == Keyboard::U) {
                if (inventory.getIsOpen()) {
                    inventory.unequipItem("Weapon");
                    inventory.unequipItem("ChestArmor");
                    inventory.unequipItem("Boots");

                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left && inventory.getIsOpen()) {
                    inventory.handleMouseClick(Mouse::getPosition(window), window);
                }
            }
        }

        window.clear(Color::Black); 
        
     
        inventory.draw(window);
        
        window.display();
    }
    return 0;
}