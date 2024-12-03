#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;
using namespace std;

class Map {

private:

    float gridSizeF = 100.f;
    RenderWindow window;
    Texture grassTex;
    const int mapSize = 10;
    vector<vector<RectangleShape>> tileMap;
    View playerView;
    int fromX = 0;
    int toX = 0;
    int fromY = 0;
    int toY = 0;
    // int renderDistance = 3; POUR PLUS TARD

    void mapInit() {
        this->setTileTex();
        this->tileMap.resize(mapSize, vector<RectangleShape>());
        this->resizeMap();
    };

public:
    Map() {
        this->mapInit();
    };

    void setTileTex() {
        if (!grassTex.loadFromFile("Assets/grass00.png"))
            throw "cant load grass png";
    };

    void resizeMap() {

        for (int x = 0; x < mapSize; x++) {
            tileMap[x].resize(mapSize, RectangleShape());
            for (int y = 0; y < mapSize; y++) {
                tileMap[x][y].setSize(Vector2f(gridSizeF, gridSizeF));
                tileMap[x][y].setOutlineThickness(1.f);
                tileMap[x][y].setTexture(&grassTex);
                tileMap[x][y].setOutlineColor(Color::Blue);
                tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
            }
        }
    };

    // void getRenderDistance() {
    //     fromX = static_cast<int>((game->getPlayerViewCenterX() / gridSizeF) - (renderDistance + 3));
    //     toX = static_cast<int>((game->getPlayerViewCenterX() / gridSizeF) + (renderDistance + 4));
    //     fromY = static_cast<int>((game->getPlayerViewCenterY() / gridSizeF) - (renderDistance + 2));
    //     toY = static_cast<int>((game->getPlayerViewCenterY() / gridSizeF) + renderDistance);

    //     if (fromX < 0)
    //         fromX = 0;
    //     else if (fromX >= mapSize)
    //         fromX = mapSize - 1;

    //     if (fromY < 0)
    //         fromY = 0;
    //     else if (fromY >= mapSize)
    //         fromY = mapSize - 1;

    //     if (toX < 0)
    //         toX = 0;
    //     else if (toX >= mapSize)
    //         toX = mapSize - 1;

    //     if (toY < 0)
    //         toY = 0;
    //     else if (toY >= mapSize)
    //         toY = mapSize - 1;
    // };  POUR PLUS TARD

    const vector<vector<RectangleShape>>& getTileMap() const {
        return this->tileMap;
    }

    float getGridSize() {

        return this->gridSizeF;

    };
};
