#pragma once
#include "GameData.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"

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
        while (data.window.isOpen()) {
            inOptionsMenu ? handleOptionsMenu(data, inOptionsMenu)
                : (handleMainMenuEvents(data, inOptionsMenu), renderMainMenu(data));
        }
    }
};