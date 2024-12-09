#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <functional>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "MapManager.hpp"
#include "Player.hpp"
#include "Creatures.hpp"
#include "Fight.hpp"
#include "Animation.hpp"

using namespace sf;
using namespace std;

class Enemy {
private:
    RectangleShape enemy;
    CircleShape hitbox;
    Vector2f position;
    map<int, Texture> enemyTex;
    Player* player;
    MapManager* mapMan;
    bool defeated;
    Creatures* creature;
    Animation* animation;
    int direction; // 0: haut, 1: bas, 2: gauche, 3: droite
    float distance; // Distance totale à parcourir
    float movedDistance; // Distance déjà parcourue
    bool movingForward; // Sens du mouvement
    float deltaTime;

    void loadEnemyTexture() {
        Texture trollTex;
        if (!trollTex.loadFromFile("Assets/TrollSprite.png"))
            throw std::runtime_error("Cannot load Assets/troll.png");
        enemyTex[5] = trollTex;

        Texture goblinTex;
        if (!goblinTex.loadFromFile("Assets/GoblinSprite.png"))
            throw std::runtime_error("Cannot load Assets/gobelin.png");
        enemyTex[6] = goblinTex;

        Texture duckTex;
        if (!duckTex.loadFromFile("Assets/DuckSprite.png"))
            throw std::runtime_error("Cannot load Assets/black.png");
        enemyTex[7] = duckTex;

        Texture lichTex;
        if (!lichTex.loadFromFile("Assets/Lich.png"))
            throw std::runtime_error("Cannot load Assets/black.png");
        enemyTex[8] = lichTex;
    }

    void initHitbox() {
        hitbox.setRadius(75.f); // Taille de la hitbox
        hitbox.setFillColor(Color::Transparent);
        hitbox.setOutlineColor(Color::Transparent);
        hitbox.setOutlineThickness(1.f);
        hitbox.setPosition(position.x - 25, position.y - 25); //-25 pour recentrer pifometre tkt
    }

public:
    Enemy(Vector2f pos, int textureKey, int dir, float dist, bool def = false)
        : position(pos), direction(dir), distance(dist), defeated(def), movedDistance(0.f), movingForward(true) {
        enemy.setSize(Vector2f(100.f, 100.f));
        enemy.setPosition(position);
        loadEnemyTexture();
        if (enemyTex.find(textureKey) != enemyTex.end()) {
            enemy.setTexture(&enemyTex[textureKey]);
            animation = new Animation(&enemyTex[textureKey], Vector2u(4, 1), 0.3f);
        }
        else {
            throw std::runtime_error("Texture key not found");
        }
        initHitbox();
    }


    void drawEnemy(RenderWindow& window) {
        if (!defeated) {
            window.draw(enemy);
            window.draw(hitbox);
        }
    }

    CircleShape getHitbox() const {
        return hitbox;
    }

    RectangleShape getEnemy() {
        return this->enemy;
    }

    Vector2f getPosition() const {
        return position;
    }

    bool isDefeated() const {
        return defeated;
    }

    int getDirection() const {
        return direction;
    }

    float getDistance() const {
        return distance;
    }



    void setDefeated(bool def, const string& entityMapFile) {

        markEnemyAsDefeated(entityMapFile);

    }

    static vector<Enemy> reloadEnemies(const string& entityMapFile, MapManager& mapMan) {
        vector<Enemy> enemies;
        ifstream file(entityMapFile);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        int col, row, type, direction;
        float distance;
        bool defeated;

        while (file >> col >> row >> type >> defeated >> direction >> distance) {
            if (!defeated) {
                Vector2f position(col * mapMan.getGridSize(), row * mapMan.getGridSize());
                enemies.emplace_back(position, type, direction, distance, defeated);
            }
        }

        file.close();
        return enemies;
    }

    void update(float deltaTime) {
        this->deltaTime = deltaTime;
        animation->update(0, deltaTime, true); // Utiliser la ligne 0 pour l'animation idle
        enemy.setTextureRect(animation->uvRect);
    }


    void updateMovement(float deltaTime) {
        if (defeated) return; // Ne bouge pas si l'ennemi est vaincu

        float speed = 50.f; // Vitesse de déplacement (pixels/sec)
        float movement = speed * deltaTime;

        // Appliquer le mouvement selon la direction
        switch (direction) {
        case 0: // Haut
            if (movingForward) {
                position.y -= movement;
                movedDistance += movement;
            }
            else {
                position.y += movement;
                movedDistance -= movement;
            }
            break;
        case 1: // Bas
            if (movingForward) {
                position.y += movement;
                movedDistance += movement;
            }
            else {
                position.y -= movement;
                movedDistance -= movement;
            }
            break;
        case 2: // Gauche
            if (movingForward) {
                position.x -= movement;
                movedDistance += movement;
            }
            else {
                position.x += movement;
                movedDistance -= movement;
            }
            break;
        case 3: // Droite
            if (movingForward) {
                position.x += movement;
                movedDistance += movement;
            }
            else {
                position.x -= movement;
                movedDistance -= movement;
            }
            break;
        }

        // Changer de direction si la distance maximale est atteinte
        if (movedDistance >= distance) {
            movingForward = false;
        }
        else if (movedDistance <= 0.f) {
            movingForward = true;
        }

        enemy.setPosition(position);
        hitbox.setPosition(position.x - 25, position.y - 25); // Mise à jour de la hitbox
    }




    void updateEntityMapFile(const string& entityMapFile, const vector<Enemy>& enemies) {
        ofstream file(entityMapFile);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        for (const auto& enemy : enemies) {
            file << enemy.getPosition().x / mapMan->getGridSize() << " "
                << enemy.getPosition().y / mapMan->getGridSize() << " "
                << enemy.getTextureKey() << " "
                << enemy.isDefeated() << " "
                << enemy.getDirection() << " "
                << enemy.getDistance() << endl;
        }

        file.close();
    }

    void markEnemyAsDefeated(const string& entityMapFile) {
        ifstream fileIn(entityMapFile);
        if (!fileIn.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        vector<string> lines; // Stocke toutes les lignes du fichier
        string line;
        int col, row, type, direction;
        float distance;
        bool defeated;

        // Lire toutes les lignes du fichier
        while (fileIn >> col >> row >> type >> defeated >> direction >> distance) {
            defeated = true; // Mettre à jour defeated à 1 (true)
            lines.emplace_back(to_string(col) + " " + to_string(row) + " " +
                to_string(type) + " " + to_string(defeated) + " " +
                to_string(direction) + " " + to_string(distance));
        }
        fileIn.close();

        // Réécrire le fichier avec les nouvelles valeurs
        ofstream fileOut(entityMapFile);
        if (!fileOut.is_open()) {
            throw std::runtime_error("Cannot write to entityMap.txt");
        }

        for (const auto& l : lines) {
            fileOut << l << endl;
        }
        fileOut.close();
    }



    static vector<Enemy> createEnemies(const string& entityMapFile, MapManager& mapMan) {
        vector<Enemy> enemies;
        ifstream file(entityMapFile);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        int col, row, type, direction;
        float distance;
        bool defeated;

        while (file >> col >> row >> type >> defeated >> direction >> distance) {
            if (!defeated) {
                Vector2f position(col * mapMan.getGridSize(), row * mapMan.getGridSize());
                enemies.emplace_back(position, type, direction, distance, defeated);
            }
        }

        file.close();
        return enemies;
    }



    static Enemy* checkCollisions(Player& player, std::vector<Enemy>& enemies) {
        for (auto& enemy : enemies) {
            if (enemy.getHitbox().getGlobalBounds().intersects(player.getPlayerBounds())) {
                enemy.getEnemy().setPosition(Vector2f(0, 0));
                return &enemy;
            }
        }
        return nullptr;
    }

    Creatures* getCreature() const {
        return creature;
    }

    int getTextureKey() const {
        for (const auto& tex : enemyTex) {
            if (enemy.getTexture() == &tex.second) {
                return tex.first;
            }
        }
        throw std::runtime_error("Texture not found");
    }

    static void resetAllDefeated(const string& entityMapFile) {
        ifstream fileIn(entityMapFile);
        if (!fileIn.is_open()) {
            throw runtime_error("Cannot open " + entityMapFile);
        }

        vector<string> lines;
        string line;
        int col, row, type, direction;
        float distance;
        bool defeated;

        // Lire et modifier chaque ligne
        while (fileIn >> col >> row >> type >> defeated >> direction >> distance) {
            defeated = false; // Mettre à jour defeated à 0 (false)
            lines.emplace_back(to_string(col) + " " + to_string(row) + " " +
                to_string(type) + " " + to_string(defeated) + " " +
                to_string(direction) + " " + to_string(distance));
        }
        fileIn.close();

        // Réécrire dans le fichier
        ofstream fileOut(entityMapFile);
        if (!fileOut.is_open()) {
            throw runtime_error("Cannot write to " + entityMapFile);
        }

        for (const auto& l : lines) {
            fileOut << l << endl;
        }
        fileOut.close();
    }

    static void resetAllEnemiesInFiles(const vector<string>& entityMapFiles) {
        for (const auto& file : entityMapFiles) {
            resetAllDefeated(file);
        }
    }


};