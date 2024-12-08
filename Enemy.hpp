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

    }

    void initHitbox() {
        hitbox.setRadius(75.f); // Taille de la hitbox
        hitbox.setFillColor(Color::Transparent);
        hitbox.setOutlineColor(Color::Red);
        hitbox.setOutlineThickness(1.f);
        hitbox.setPosition(position.x - 25, position.y - 25); //-25 pour recentrer pifometre tkt
    }

public:
    Enemy(Vector2f pos, int textureKey, bool def = false) : position(pos), defeated(def) {
        enemy.setSize(Vector2f(100.f, 100.f));
        enemy.setPosition(position);
        loadEnemyTexture();
        if (enemyTex.find(textureKey) != enemyTex.end()) {
            enemy.setTexture(&enemyTex[textureKey]);
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


    void setDefeated(bool def, const string& entityMapFile) {
        cout << "testdefeated" << endl;
        markEnemyAsDefeated(entityMapFile);

    }

    static vector<Enemy> reloadEnemies(const string& entityMapFile, MapManager& mapMan) {
        vector<Enemy> enemies;
        ifstream file(entityMapFile);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        int col, row, type;
        bool defeated;

        while (file >> col >> row >> type >> defeated) {
            if (!defeated) {
                Vector2f position(col * mapMan.getGridSize(), row * mapMan.getGridSize());
                enemies.emplace_back(position, type, defeated);
            }
            if (defeated) {
                Vector2f position(20 * mapMan.getGridSize(), 20 * mapMan.getGridSize());
				enemies.erase(enemies.begin(), enemies.end());
            }
        }

        file.close();
        return enemies;
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
                << enemy.isDefeated() << endl;
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
        int col, row, type;
        bool defeated;

        // Lire toutes les lignes du fichier
        while (fileIn >> col >> row >> type >> defeated) {
            defeated = true; // Mettre à jour defeated à 1 (true)
            lines.emplace_back(to_string(col) + " " + to_string(row) + " " +
                to_string(type) + " " + to_string(defeated));
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

        int col, row, type;
        bool defeated;
        while (file >> col >> row >> type >> defeated) {
            if (!defeated) {
                Vector2f position(col * mapMan.getGridSize(), row * mapMan.getGridSize());
                enemies.emplace_back(position, type, defeated);
            };
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

    static void saveEnemies(const string& filename, const vector<Enemy>& enemies, MapManager& mapMan) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open entityMap.txt");
        }

        for (const auto& enemy : enemies) {
            file << enemy.getPosition().x / mapMan.getGridSize() << " "
                << enemy.getPosition().y / mapMan.getGridSize() << " "
                << enemy.getTextureKey() << " "
                << enemy.isDefeated() << endl;
        }

        file.close();
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

    void resetEnemyDefeatedState(const string& entityMapFile) {
        ifstream fileIn(entityMapFile);
        if (!fileIn.is_open()) {
            throw std::runtime_error("Cannot open " + entityMapFile);
        }

        vector<string> lines;
        string line;
        int col, row, type;
        bool defeated;

        // Lire toutes les lignes du fichier
        while (fileIn >> col >> row >> type >> defeated) {
            defeated = false; // Réinitialiser defeated à 0 (false)
            lines.emplace_back(to_string(col) + " " + to_string(row) + " " +
                to_string(type) + " " + to_string(defeated));
        }
        fileIn.close();

        // Réécrire le fichier avec les nouvelles valeurs
        ofstream fileOut(entityMapFile);
        if (!fileOut.is_open()) {
            throw std::runtime_error("Cannot write to " + entityMapFile);
        }

        for (const auto& l : lines) {
            fileOut << l << endl;
        }
        fileOut.close();
    }


    void resetAllEnemyDefeatedStates(const vector<string>& entityMapFiles) {
        for (const auto& entityMapFile : entityMapFiles) {
            resetEnemyDefeatedState(entityMapFile);
        }
    }
};