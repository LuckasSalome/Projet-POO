#include "Player.h"
#include "Wall.h"
#include "teleporteur.h"
#include "Coffre.h"
#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
    : animation(texture, imageCount, switchTime), speed(speed), row(0), faceRight(true), mousePressed(false), showMessage(false), currentChest(nullptr)
{
    this->speed = speed;
    row = 4;
    faceRight = true;

    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setPosition(400.0f, 400.0f);
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(texture);
}

void Player::Update(float deltaTime, const std::vector<Wall>& walls, const std::vector<Teleporteur*>& teleporteurs, const std::vector<Coffre*>& Chests, const std::vector<Sol>& sols, sf::RenderWindow& window)
{
    if (showMessage && currentChest) {
        currentChest->drawMessage(window, walls, sols, *this);
        return; // Ne pas mettre à jour le joueur tant que le message est affiché
    }

    sf::Vector2f movement(0.0f, 0.0f); //initialise le vecteur de mouvement à 0,0

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        movement.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        movement.y -= speed * deltaTime;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!mousePressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

            // Vérifiez si la position actuelle est déjà proche de la position cible
            if (std::abs(body.getPosition().x - worldPosition.x) > 1.0f || std::abs(body.getPosition().y - worldPosition.y) > 1.0f) {
                body.setPosition(worldPosition);
            }
            mousePressed = true; // Marquez le bouton comme enfoncé
        }
    }
    else {
        mousePressed = false; // Réinitialisez l'état lorsque le bouton est relâché
    }

    // Ajuster la vitesse en diagonale
    if (movement.x != 0.0f && movement.y != 0.0f) {
        movement.x *= 0.75f;
        movement.y *= 0.75f;
    }

    // Sprint
    if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))) {
        movement.x *= 2.00f;
        movement.y *= 2.00f;
    }

    // Mega Sprint
    if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))) {
        movement.x *= 5.00f;
        movement.y *= 5.00f;
    }

    // Mega Sprint
    if ((movement.x || movement.y) != 0 && (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
        movement.x *= 12.0f;
        movement.y *= 12.0f;
    }

    sf::Vector2f newPosition = body.getPosition() + movement;
    sf::FloatRect newBounds = body.getGlobalBounds();
    newBounds.left = newPosition.x - body.getOrigin().x;
    newBounds.top = newPosition.y - body.getOrigin().y;

    for (const auto& wall : walls) {
        if (newBounds.intersects(wall.GetBounds())) {
            movement = sf::Vector2f(0.0f, 0.0f);
            break;
        }
    }

    for (const auto& tp : teleporteurs) {
        if (tp->conditionRemplie() && tp->checkCollision(*this)) {
            body.setPosition(tp->getArrivalPosition());
            break;
        }
    }

    if (movement.x == 0.0f) {
        row = 4;    // 4 = ligne 4 de l'animation donc idle
    }
    else {
        row = 3;    // 3 = ligne 3 de l'animation donc marche vers la gauche

        if (movement.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }

    if (movement.y < 0.0f) {
        row = 1;    // 1 = ligne 1 de l'animation donc marche vers le haut
    }
    else if (movement.y > 0.0f) {
        row = 0;    // 0 = ligne 0 de l'animation donc marche vers le bas
    }

    animation.update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(movement);

    CheckChestCollision(Chests, window, walls, sols); // Passez la fenêtre, les murs et les sols ici
    PrintPosition(); // Ajoutez cet appel pour imprimer la position
}

void Player::Draw(sf::RenderWindow& window) const {
    window.draw(body);
}

void Player::CheckChestCollision(const std::vector<Coffre*>& Chests, sf::RenderWindow& window, const std::vector<Wall>& walls, const std::vector<Sol>& sols)
{
    for (const auto& chest : Chests)
    {
        if (body.getGlobalBounds().intersects(chest->GetBounds()))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                if (!chest->isEKeyPressed()) {
                    chest->ouvrir();
                    chest->setEKeyPressed(true); // Marquer la touche E comme enfoncée
                    showMessage = true; // Afficher le message
                    currentChest = chest; // Mettre à jour le coffre actuel
                }
            }
            else {
                chest->setEKeyPressed(false); // Réinitialiser l'état lorsque la touche est relâchée
            }
        }
    }

    // Afficher le message du coffre si nécessaire
    if (showMessage && currentChest) {
        currentChest->drawMessage(window, walls, sols, *this);
        showMessage = false; // Réinitialiser l'état du message après affichage
    }
}





void Player::PrintPosition() const {
    std::cout << "Position du joueur: (" << body.getPosition().x << ", " << body.getPosition().y << ")" << std::endl;
}

Player::~Player() {}
