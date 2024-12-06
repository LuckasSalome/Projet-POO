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
        bool inCharacterSelection = false;
        string selectedRace = "";

        while (data.window.isOpen()) {
            Event event;
            if (inOptionsMenu) {
                handleOptionsMenu(data, inOptionsMenu);
            }
            else if (inCharacterSelection) {
                string selection = handleCharacterSelection(data, inCharacterSelection, event);

                if (!selection.empty()) {
                    // Séparer la race et le métier
                    size_t colonPos = selection.find(':');
                    if (colonPos != string::npos) {
                        string race = selection.substr(0, colonPos);
                        string job = selection.substr(colonPos + 1);

                        cout << "Race selectionnee : " << race << endl;
                        cout << "Metier selectionne : " << job << endl;
                    }
                }
            }
            else {
                handleMainMenuEvents(data, inOptionsMenu, inCharacterSelection);
                renderMainMenu(data);
            }
        }
    }
};