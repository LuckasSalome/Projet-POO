#pragma once
#include "GameData.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"
#include "ChoixPerso.hpp"

class Game {
public:
    static void run() {
        GameData data;
        data.window.create(VideoMode(data.windowWidth, data.windowHeight), "Main Menu");
        data.window.setKeyRepeatEnabled(false);

        if (!data.backgroundTexture.loadFromFile("images/accueil.jpg") || !data.font.loadFromFile("res/poppins.ttf"))
            return;

        data.background.setTexture(data.backgroundTexture);
        data.background.setScale(
            static_cast<float>(data.window.getSize().x) / data.backgroundTexture.getSize().x,
            static_cast<float>(data.window.getSize().y) / data.backgroundTexture.getSize().y
        );

        initMainMenu(data);

        bool inOptionsMenu = false;
        bool inCharacterSelection = false;  // Ajoutez cette ligne
        while (data.window.isOpen()) {
            Event event;
            if (inOptionsMenu) {
                handleOptionsMenu(data, inOptionsMenu);
            }
            else if (inCharacterSelection) {
                handleCharacterSelection(data, inCharacterSelection, event);
            }
            else {
                handleMainMenuEvents(data, inOptionsMenu, inCharacterSelection);
                renderMainMenu(data);
            }
        }
    }
};