// SFML download.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "sfml/Graphics.hpp"
#include "SFML/window.hpp"
#include "SFML/system.hpp"
#include "Player.h"

static const float VIEW_HEIGHT = 512.0f;
static const float VIEW_WIDTH = 1212.0f;


using namespace std;

void rezisedView(sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * 2 * aspectRatio, 2 * VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Donjon test", sf::Style::Close | sf::Style::Resize);

    sf::Texture playerTexture;
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1212.0f, 712.0f));


    playerTexture.loadFromFile("PlayerSheet_V2.png");

    if (!playerTexture.loadFromFile("PlayerSheet_V2.png")) {
        cerr << "Erreur lors du chargement de la texture du joueur" << endl;
        return -1;
    }

	Player player(&playerTexture, sf::Vector2u(4, 5), 0.3f, 350.0f); //4 = 4 images en largeur, 5 = 5 images en hauteur, 0.3f = temps entre chaque image, 100.0f = vitesse du joueur


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
            }

        }
    
		player.Update(deltaTime); 
		view.setCenter(player.GetPosition());

		window.clear(sf::Color::Magenta); //on met la couleur de fond
        window.setView(view);
        player.Draw(window); //affiche le joueur grâce à la fonction Draw de la classe Player ce qui permet de garder des variables en privé
        window.display();
        rezisedView(window, view);
    }

    return 0;
}


