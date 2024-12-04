#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "MainMenu.hpp"
#include "OptionsMenu.hpp"

int main() {
    GameData data;

    // Initialisation
    data.window.create(VideoMode(data.windowWidth, data.windowHeight), "Main Menu");
    data.window.setKeyRepeatEnabled(false);

    if (!data.backgroundTexture.loadFromFile("images/accueil.jpg") ||
        !data.font.loadFromFile("res/poppins.ttf")) {
        return -1;
    }
    data.background.setTexture(data.backgroundTexture);
    data.background.setScale(
        static_cast<float>(data.window.getSize().x) / data.backgroundTexture.getSize().x,
        static_cast<float>(data.window.getSize().y) / data.backgroundTexture.getSize().y
    );

    initMainMenu(data);

    // Boucle principale
    bool inOptionsMenu = false;
    while (data.window.isOpen()) {
        if (inOptionsMenu) {
            handleOptionsMenu(data, inOptionsMenu);
        }
        else {
            handleMainMenuEvents(data, inOptionsMenu);
            renderMainMenu(data);
        }
    }

    return 0;
}