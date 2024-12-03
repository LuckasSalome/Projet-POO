#pragma once
#include <SFML/Graphics.hpp>
#include <string>

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

    // Paramètres configurables
    Keyboard::Key upKey = Keyboard::Up;      // Touche pour monter
    Keyboard::Key downKey = Keyboard::Down;  // Touche pour descendre
    Keyboard::Key actionKey = Keyboard::Enter; // Touche pour confirmer l'action
    Keyboard::Key cancelKey = Keyboard::Escape; // Touche pour annuler
    Keyboard::Key leftKey = Keyboard::Left;    // Touche pour aller à gauche
    Keyboard::Key rightKey = Keyboard::Right;  // Touche pour aller à droite

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
};