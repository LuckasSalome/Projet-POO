#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Heroes.hpp"
#include "Creatures.hpp"

using namespace sf;
using namespace std;

struct GameData {
    RenderWindow window;
    Texture backgroundTexture;
    Sprite background;
    Font font;
    RectangleShape menuRect;
    RectangleShape selectionRect;
    Text menuItems[3];
    int currentSelection = 0;
    Heroes* currentCharacter = nullptr;
    string selectedRace;

    // Ajout de la musique
    Music backgroundMusic;  // Ajout de l'objet Music

    // Paramètres configurables
    bool soundEnabled = true;  // Paramètre pour savoir si le son est activé
    Keyboard::Key upKey = Keyboard::Up;
    Keyboard::Key downKey = Keyboard::Down;
    Keyboard::Key actionKey = Keyboard::Enter;
    Keyboard::Key cancelKey = Keyboard::Escape;
    Keyboard::Key leftKey = Keyboard::Left;
    Keyboard::Key rightKey = Keyboard::Right;

    int windowWidth = 1400;
    int windowHeight = 800;

    // Fonction pour convertir les touches en chaînes de caractères
    string keyToString(Keyboard::Key key) {
        switch (key) {
        case Keyboard::A: return "A";
        case Keyboard::B: return "B";
        case Keyboard::C: return "C";
        case Keyboard::D: return "D";
        case Keyboard::E: return "E";
        case Keyboard::F: return "F";
        case Keyboard::G: return "G";
        case Keyboard::H: return "H";
        case Keyboard::I: return "I";
        case Keyboard::J: return "J";
        case Keyboard::K: return "K";
        case Keyboard::L: return "L";
        case Keyboard::M: return "M";
        case Keyboard::N: return "N";
        case Keyboard::O: return "O";
        case Keyboard::P: return "P";
        case Keyboard::Q: return "Q";
        case Keyboard::R: return "R";
        case Keyboard::S: return "S";
        case Keyboard::T: return "T";
        case Keyboard::U: return "U";
        case Keyboard::V: return "V";
        case Keyboard::W: return "W";
        case Keyboard::X: return "X";
        case Keyboard::Y: return "Y";
        case Keyboard::Z: return "Z";
        case Keyboard::Num0: return "0";
        case Keyboard::Num1: return "1";
        case Keyboard::Num2: return "2";
        case Keyboard::Num3: return "3";
        case Keyboard::Num4: return "4";
        case Keyboard::Num5: return "5";
        case Keyboard::Num6: return "6";
        case Keyboard::Num7: return "7";
        case Keyboard::Num8: return "8";
        case Keyboard::Num9: return "9";
        default: return "Unknown";
        }
    }

    ~GameData() {
        if (currentCharacter != nullptr) {
            delete currentCharacter;
        }
    }
};