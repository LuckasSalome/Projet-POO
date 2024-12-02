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


using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(800, 600), "Inventory System");
    Font font;

    if (!font.loadFromFile("images/RobotoBlack.ttf")) {
        cerr << "Error: Unable to load font 'RobotoBlack.ttf'!" << endl;
        return 1;
    }

    Inventory inventory(4, 5, font); // 4 rows x 5 columns

    PotionIntelligence potionIntelligence;
    inventory.addItem(0, 0, &potionIntelligence);

    RustyKey rustyKey;
    inventory.addItem(0, 1, &rustyKey);  // Add RustyKey to the inventory at position (0, 2)

    BeerPotion beerPotion;
    inventory.addItem(0, 2, &beerPotion);

    BluntSword bluntSword;
    inventory.addItem(0, 3, &bluntSword);

    KeyCorridor keyCorridor;
    inventory.addItem(0, 4, &keyCorridor);

    BookOfLostRules bookOfLostRules;
    inventory.addItem(1, 0, &bookOfLostRules);

    DiscretionShoesNoisy discretionShoesNoisy;
    inventory.addItem(1, 1, &discretionShoesNoisy);

    MajorHealingPotion majorHealingPotion;
    inventory.addItem(1, 2, &majorHealingPotion);

    RopeTrap ropeTrap;
    inventory.addItem(1, 4, &ropeTrap);

    ScepterSyntactic scepterSyntactic;
    inventory.addItem(2, 0, &scepterSyntactic);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                inventory.handleMouseClick(Mouse::getPosition(window));
            }
        }

        window.clear();
        inventory.draw(window);
        window.display();
    }

    return 0;
}
