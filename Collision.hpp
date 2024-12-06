#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "Map.hpp"
#include "mapManager.hpp"
#include "Player.hpp"

using namespace sf;
using namespace std;

class Collision {
private:
    vector<RectangleShape> walls;
    MapManager* mapManager;
    Player* player;
    float windowWidth;
    float windowHeight;

    void collisionInit() {
        const auto& collisionMap = mapManager->getCollisionMap();
        float gridSize = mapManager->getGridSize();

        for (int x = 0; x < collisionMap.size(); ++x) {
            for (int y = 0; y < collisionMap[x].size(); ++y) {
                if (collisionMap[x][y] == 1) {
                    RectangleShape wall(Vector2f(gridSize, gridSize));
                    wall.setPosition(x * gridSize, y * gridSize);
                    wall.setFillColor(Color::Transparent); // Vous pouvez changer la couleur ou la texture du mur ici
                    walls.push_back(wall);
                }
            }
        }
    }

public:
    Collision(MapManager* mapManager, Player* player, float windowWidth, float windowHeight)
        : mapManager(mapManager), player(player), windowWidth(windowWidth), windowHeight(windowHeight) {
        this->collisionInit();
    }

    const vector<RectangleShape>& getWalls() const {
        return walls;
    }

    void setWallsColor(const Color& color) {
        for (auto& wall : walls) {
            wall.setFillColor(color);
        }
    } 

    void resetCollisions() {
        walls.clear();
        collisionInit();
    }

};
