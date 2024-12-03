#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "Wall.h"
#include "Sol.h"
#include "Salle.h"
#include "teleporteur.h"
#include "SpecialTeleporteur.hpp"
#include "Teleporteur2.hpp"
#include "Coffre.h"

static const float VIEW_HEIGHT = 912.0f;
static const float VIEW_WIDTH = 1712.0f;

using namespace std;

void rezisedView(sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * 2 * aspectRatio, 2 * VIEW_HEIGHT);
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 15;
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(VIEW_WIDTH), static_cast<unsigned int>(VIEW_HEIGHT)), "Donjon test", sf::Style::Close | sf::Style::Resize, settings);
    window.setVerticalSyncEnabled(true);

    sf::Music music;
    if (!music.openFromFile("UnderClocked.mp3")) {
        std::cerr << "Erreur lors du chargement du fichier audio" << std::endl;
        return -1;
    }
    music.setLoop(true);
    music.play();

    sf::Texture playerTexture;
    sf::Texture wallTexture;
    sf::Texture solTexture;
    sf::Texture teleporteurTexture;
    sf::Texture ChestTexture;

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

    if (!teleporteurTexture.loadFromFile("Teleporteur.png")) {
        cerr << "Erreur lors du chargement de la texture du teleporteur" << endl;
        return -1;
    }

    if (!ChestTexture.loadFromFile("closed.png")) {
        cerr << "Erreur lors du chargement de la texture du coffre" << endl;
        return -1;
    }

    std::vector<Teleporteur*> teleporteurs;
    teleporteurs.push_back(new SpecialTeleporteur(1800.0f, 1000.0f, 2500.0f, 990.0f, &teleporteurTexture)); //position(x;y) = (1800;965) et position d'arrive(x;y) = (2500;990)
    teleporteurs.push_back(new Teleporteur2(5200.0f, 875.0f, 5750.0f, 1000.0f, &teleporteurTexture));
    teleporteurs.push_back(new Teleporteur2(7900.0f, 875.0f, 8500.0f, 1000.0f, &teleporteurTexture));
    teleporteurs.push_back(new Teleporteur2(12300.0f, 875.0f, 12900.0f, 1000.0f, &teleporteurTexture));
    teleporteurs.push_back(new Teleporteur2(15700.0f, 875.0f, 16300.0f, 1000.0f, &teleporteurTexture));

    // Créer un vecteur de pointeurs vers des objets de type Coffre
    std::vector<Coffre*> chests;
    // Créer deux coffres
    Coffre* chest1 = new Coffre(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3780.0f, 500.0f), &ChestTexture, sf::Vector2u(4, 1), 0.3f); // Coffre dans la salle 3
    chest1->addObjet("Potion de prout");
    chest1->addObjet("Lame en caoutchouc");
    chests.push_back(chest1);

    Coffre* chest2 = new Coffre(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(6000.0f, 990.0f), &ChestTexture, sf::Vector2u(4, 1), 0.3f); // Coffre dans la salle des Trésors
    chest2->addObjet("Chaussures de discrétion bruyantes");
    chests.push_back(chest2);

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

    // Corridor des malentendus
    int largeurCorridor = 20;
    int hauteurCorridor = 5;
    sf::Vector2f positionCorridor(
        positionSalleTroll.x + LargeurSalleTroll * largeurTile + largeurTile, // Décaler la salle du Troll à droite du couloir
        positionSalleTroll.y + (HauteurSalleTroll * hauteurTile - hauteurCorridor * hauteurTile) / 2.0f // Centrer verticalement la salle du Troll par rapport au couloir
    );
    Salle Corridor(largeurCorridor, hauteurCorridor, &solTexture, &wallTexture, positionCorridor);
    Corridor.generateRoom();

    // Salle des Trésors Illusoires
    int largeurSalleTresors = 15;
    int hauteurSalleTresors = 10;
    sf::Vector2f positionSalleTresors(
        positionCorridor.x + largeurCorridor * largeurTile + largeurTile, // Décaler la salle des Trésors à droite du corridor
        positionCorridor.y + (hauteurCorridor * hauteurTile - hauteurSalleTresors * hauteurTile) / 2.0f // Centrer verticalement la salle des Trésors par rapport au corridor
    );
    Salle salleTresors(largeurSalleTresors, hauteurSalleTresors, &solTexture, &wallTexture, positionSalleTresors);
    salleTresors.generateRoom();

    // Antre de la Syntaxe Perdue
    int largeurAntreSyntaxe = 20;
    int hauteurAntreSyntaxe = 20;
    sf::Vector2f positionAntreSyntaxe(
        positionSalleTresors.x + largeurSalleTresors * largeurTile + largeurTile, // Décaler l'Antre de la Syntaxe à droite de la salle des Trésors
        positionSalleTresors.y + (hauteurSalleTresors * hauteurTile - hauteurAntreSyntaxe * hauteurTile) / 2.0f // Centrer verticalement l'Antre de la Syntaxe par rapport à la salle des Trésors
    );
    Salle antreSyntaxe(largeurAntreSyntaxe, hauteurAntreSyntaxe, &solTexture, &wallTexture, positionAntreSyntaxe);
    antreSyntaxe.generateRoom();

    // Combiner les murs des salles pour la détection des collisions
    std::vector<Wall> allWalls = salle.getMurs();
    std::vector<Wall> couloirWalls = couloir.getMurs();
    std::vector<Wall> Salle3Walls = SalleTroll.getMurs();
    std::vector<Wall> CorridorWalls = Corridor.getMurs();
    std::vector<Wall> Salle4Walls = salleTresors.getMurs();
    std::vector<Wall> AntreWalls = antreSyntaxe.getMurs();
    allWalls.insert(allWalls.end(), couloirWalls.begin(), couloirWalls.end());
    allWalls.insert(allWalls.end(), Salle3Walls.begin(), Salle3Walls.end());
    allWalls.insert(allWalls.end(), CorridorWalls.begin(), CorridorWalls.end());
    allWalls.insert(allWalls.end(), Salle4Walls.begin(), Salle4Walls.end());
    allWalls.insert(allWalls.end(), AntreWalls.begin(), AntreWalls.end());

    // Combiner les sols des salles pour la détection des collisions
    std::vector<Sol> allSols = salle.getSols();
    std::vector<Sol> couloirSols = couloir.getSols();
    std::vector<Sol> Salle3Sols = SalleTroll.getSols();
    std::vector<Sol> CorridorSols = Corridor.getSols();
    std::vector<Sol> Salle4Sols = salleTresors.getSols();
    std::vector<Sol> AntreSols = antreSyntaxe.getSols();
    allSols.insert(allSols.end(), couloirSols.begin(), couloirSols.end());
    allSols.insert(allSols.end(), Salle3Sols.begin(), Salle3Sols.end());
    allSols.insert(allSols.end(), CorridorSols.begin(), CorridorSols.end());
    allSols.insert(allSols.end(), Salle4Sols.begin(), Salle4Sols.end());
    allSols.insert(allSols.end(), AntreSols.begin(), AntreSols.end());




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

        player.Update(deltaTime, allWalls, teleporteurs, chests, allSols, window); // Utiliser les murs et les sols combinés pour la collision

        view.setCenter(player.GetPosition());

        window.clear(sf::Color::Magenta);
        window.setView(view);

        salle.drawRoom(window);
        couloir.drawRoom(window);
        SalleTroll.drawRoom(window);
        Corridor.drawRoom(window);
        salleTresors.drawRoom(window);
        antreSyntaxe.drawRoom(window);

        for (const auto& tp : teleporteurs) {
            tp->draw(window);
        }

        for (const auto& chest : chests) {
            chest->draw(window); // Dessiner les coffres
        }

        player.Draw(window);

        window.display();
        rezisedView(window, view);
    }

    for (auto tp : teleporteurs) {
        delete tp;
    }

    for (auto chest : chests) {
        delete chest;
    }

    return 0;
}
