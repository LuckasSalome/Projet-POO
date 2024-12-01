#include <iostream>
#include <vector>
#include "sfml/Graphics.hpp"
#include "SFML/window.hpp"
#include "SFML/System.hpp"
#include "Player.h"
#include "Wall.h"
#include "Sol.h"
#include "Salle.h"

static const float VIEW_HEIGHT = 912.0f;
static const float VIEW_WIDTH = 1712.0f;

using namespace std;

void rezisedView(sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * 2 * aspectRatio, 2 * VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Donjon test", sf::Style::Close | sf::Style::Resize);

    sf::Texture playerTexture;
    sf::Texture wallTexture;
    sf::Texture solTexture;
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1212.0f, 712.0f));

    if (!playerTexture.loadFromFile("PlayerSheet_V2.png")) {
        cerr << "Erreur lors du chargement de la texture du joueur" << endl;
        return -1;
    }

    if (!wallTexture.loadFromFile("Mur.png")) {
        cerr << "Erreur lors du chargement de la texture du mur" << endl;
        return -1;
    }

    if (!solTexture.loadFromFile("SolV3.png")) {
        cerr << "Erreur lors du chargement de la texture du sol" << endl;
        return -1;
    }

    Player player(&playerTexture, sf::Vector2u(4, 5), 0.3f, 350.0f);

    int largeurSalle = 10;
    int hauteurSalle = 10;

    // Créer une instance de la classe Salle
    Salle salle(largeurSalle, hauteurSalle, &solTexture, &wallTexture, sf::Vector2f(0.0f, 0.0f));
    salle.generateRoom(); // Générer les murs et les sols de la salle

    // Créer une instance de la classe Salle pour le couloir
    int largeurCouloir = 15;
    int hauteurCouloir = 5;
    float largeurTile = 210.0f;
    float hauteurTile = 199.0f;
    sf::Vector2f positionCouloir(
        largeurSalle * largeurTile + largeurTile, // Décaler le couloir d'une tuile à droite de la salle
        (hauteurSalle * hauteurTile - hauteurCouloir * hauteurTile) / 2.0f // Centrer verticalement le couloir par rapport à la salle
    );
    Salle couloir(largeurCouloir, hauteurCouloir, &solTexture, &wallTexture, positionCouloir);
    couloir.generateRoom(); // Générer les murs et les sols du couloir

    // Créer une instance de la classe Salle pour la 3ème salle : Salle du Troll Rhétoricien
    int LargeurSalleTroll = 12;
    int HauteurSalleTroll = 12;
    sf::Vector2f positionSalleTroll(
        positionCouloir.x + largeurCouloir * largeurTile + largeurTile, // Décaler la salle du Troll à droite du couloir
        positionCouloir.y + (hauteurCouloir * hauteurTile - HauteurSalleTroll * hauteurTile) / 2.0f // Centrer verticalement la salle du Troll par rapport au couloir
    );
    Salle SalleTroll(LargeurSalleTroll, HauteurSalleTroll, &solTexture, &wallTexture, positionSalleTroll);
    SalleTroll.generateRoom(); // Générer les murs et les sols de la Salle 3

    // Combiner les murs des deux salles pour la détection des collisions
    std::vector<Wall> allWalls = salle.getMurs();
    std::vector<Wall> couloirWalls = couloir.getMurs();
    std::vector<Wall> Salle3Walls = SalleTroll.getMurs();
    allWalls.insert(allWalls.end(), couloirWalls.begin(), couloirWalls.end());
    allWalls.insert(allWalls.end(), Salle3Walls.begin(), Salle3Walls.end());

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                printf("Nouvelle largeur de la fenetre : %i Nouvelle hauteur : %i\n", event.size.width, event.size.height);
                rezisedView(window, view);
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            }
        }

        player.Update(deltaTime, allWalls, window); // Utiliser les murs combinés pour la collision

        view.setCenter(player.GetPosition());

        window.clear(sf::Color::Magenta);
        window.setView(view);

        salle.drawRoom(window);
        couloir.drawRoom(window);
		SalleTroll.drawRoom(window);

        player.Draw(window);

        window.display();
        rezisedView(window, view);
    }

    return 0;
}
