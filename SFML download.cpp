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
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Donjon BDSM", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape Hamsterzilla(sf::Vector2f(250.0f, 300.0f));
    Hamsterzilla.setPosition(206.0f, 206.0f);
    Hamsterzilla.setOrigin(125.0f, 150.0f);
    sf::Texture playerTexture;
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1212.0f, 712.0f));
	sf::Texture HamsterzillaTexture;
    //player.setTexture(&playerTexture);
    playerTexture.loadFromFile("PlayerSheet_V2.png");
	HamsterzillaTexture.loadFromFile("HamsterZilla.png");
	Hamsterzilla.setTexture(&HamsterzillaTexture);

    

    if (!playerTexture.loadFromFile("PlayerSheet_V2.png")) {
        cerr << "Erreur lors du chargement de la texture du joueur" << endl;
        return -1;
    }

	Player player(&playerTexture, sf::Vector2u(4, 5), 0.3f, 350.0f); //4 = 4 images en largeur, 5 = 5 images en hauteur, 0.3f = temps entre chaque image, 100.0f = vitesse du joueur


	float deltaTime = 0.0f;
    sf::Clock clock;


    

    /*
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x /= 4;
    textureSize.y /= 4;

    player.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
    */

	float Hamspeed = 4.0f; //vitesse du HamsterZilla en pixels par seconde (ne pas aller au delà de 5)



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
    











                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad4)) { //va vers la gauche
                Hamsterzilla.move(-Hamspeed, 0.0f);
                // Retourner le sprite vers la gauche
                Hamsterzilla.setScale(-1.f, 1.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad8)) { //va vers le haut
                Hamsterzilla.move(0.0f, -Hamspeed);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad6)) { //va vers la droite
                Hamsterzilla.move(Hamspeed, 0.0f);
				Hamsterzilla.setScale(1.f, 1.f); // Remettre le sprite dans le bon sens
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad2)) { //va vers le bas
                Hamsterzilla.move(0.0f, Hamspeed);
            }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad7)) { //va vers le haut à gauche
				Hamsterzilla.move(-Hamspeed * 0.75f, -Hamspeed * 0.75f);
				Hamsterzilla.setScale(-1.0f, 1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad9)) { //va vers le haut à droite
				Hamsterzilla.move(Hamspeed * 0.75f, -Hamspeed * 0.75f);
				Hamsterzilla.setScale(1.0f, 1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad1)) { //va vers le bas à gauche
				Hamsterzilla.move(-Hamspeed * 0.75f, Hamspeed * 0.75f);
				Hamsterzilla.setScale(-1.0f, 1.0f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad3)) { //va vers le bas à droite
				Hamsterzilla.move(Hamspeed * 0.75f, Hamspeed * 0.75f);
				Hamsterzilla.setScale(1.0f, 1.0f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Numpad5)) {
                Hamsterzilla.setPosition(600.0f, 400.0f);
			}
        


        
        //player.Update(4, deltaTime, false); // 4 = ligne 4 de l'animation
		//player.setTextureRect(animation.uvRect);

		player.Update(deltaTime); //il sert à quoi le deltatime ?
		//il sert à faire en sorte que le jeu soit fluide et que le joueur ne se déplace pas plus vite sur un ordinateur plus puissant
		view.setCenter(player.GetPosition());



		window.clear(sf::Color::Magenta); //on met la couleur de fond
		window.draw(Hamsterzilla);
        window.setView(view);
        player.Draw(window); //affiche le joueur grâce à la fonction Draw de la classe Player ce qui permet de garder des variables en privé
        window.display();
        rezisedView(window, view);
    }

    return 0;
}























/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Close | sf::Style::Resize); //crée la fenetre graphique
    sf::RectangleShape player(sf::Vector2f(200.0f, 200.0f));        //créer un player en forme carré
    sf::RectangleShape ennemy(sf::Vector2f(100.0f, 100.0f));        //créer un ennemi en forme de cercle

    player.setOrigin(50.0f, 50.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("HamsterZilla.png");
    player.setTexture(&playerTexture);

    ennemy.setOrigin(50.0f, 50.0f);
    sf::Texture ennemyTexture;
    ennemyTexture.loadFromFile("Cyber-Furet.png");
    sf::Texture ennemyTexture2;
    ennemyTexture2.loadFromFile("Cyber-Furet2.png");
    ennemy.setTexture(&ennemyTexture);
    

    player.setPosition(206.0f, 206.0f);
    //ennemy.setPosition(300.0f, 100.0f);



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) // while there are events to process
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                printf("Nouvelle largeur de la fenetre : %i Nouvelle hauteur : %i\n", event.size.width, event.size.height);
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode < 128) {
                    printf("%c", event.text.unicode);
                }
                break;
            }
        }

        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) { //va vers la gauche
            player.move(-0.2f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) { //va vers le haut
            player.move(0.0f, -0.2f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { //va vers la droite
            player.move(0.2f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { //va vers le bas
            player.move(0.0f, 0.2f);
        }
       */


/*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) { //va vers la gauche
            ennemy.move(-0.2f, 0.0f);
            ennemy.setTexture(&ennemyTexture2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) { //va vers le haut
            ennemy.move(0.0f, -0.2f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { //va vers la droite
            ennemy.move(0.2f, 0.0f);
            ennemy.setTexture(&ennemyTexture);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { //va vers le bas
            ennemy.move(0.0f, 0.2f);
        }
*/


        /*
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, (float)mousePos.y);
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);            //on récup la position 24/24
        cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")\n";
        */

		/*
        window.clear();
        window.draw(player);
        window.draw(ennemy);
        window.display();
    }





    return 0;
}



*/





