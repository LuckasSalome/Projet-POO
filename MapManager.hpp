#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;
using namespace std;

class MapManager {
private:
    vector<vector<int>> tileTypes;
    vector<vector<int>> collisionMap;
    vector<vector<RectangleShape>> tileMap;
    map<int, Texture> textures;
    float gridSize;
    int mapSize;

     void loadTextures() {

    Texture grassTex;
    if (!grassTex.loadFromFile("Assets/grass00.png"))
        throw std::runtime_error("Cannot load Assets/grass00.png");
    textures[2] = grassTex;

    Texture waterTex;
    if (!waterTex.loadFromFile("Assets/water.png"))
        throw std::runtime_error("Cannot load Assets/water.png");
    textures[1] = waterTex;

    Texture solClair;
    if (!solClair.loadFromFile("Assets/Sol1.png"))
        throw std::runtime_error("Cannot load Assets/Sol1.png");
    textures[0] = solClair;

    Texture solSombre;
    if (!solSombre.loadFromFile("Assets/Sol2.png"))
        throw std::runtime_error("Cannot load Assets/Sol2.png");
    textures[3] = solSombre;

    Texture entree1;
    if (!entree1.loadFromFile("Assets/entree1.png"))
        throw std::runtime_error("Cannot load Assets/entree1.png");
    textures[4] = entree1;

    Texture fenetreGrille;
    if (!fenetreGrille.loadFromFile("Assets/fenetre1.png"))
        throw std::runtime_error("Cannot load Assets/fenetre1.png");
    textures[5] = fenetreGrille;

    Texture MurH1;
    if (!MurH1.loadFromFile("Assets/MurH1.png"))
        throw std::runtime_error("Cannot load Assets/MurH1.png");
    textures[6] = MurH1;

    Texture MurH2;
    if (!MurH2.loadFromFile("Assets/MurH2.png"))
        throw std::runtime_error("Cannot load Assets/MurH2.png");
    textures[7] = MurH2;

    Texture MurV1;
    if (!MurV1.loadFromFile("Assets/MurV1.png"))
        throw std::runtime_error("Cannot load Assets/MurV1.png");
    textures[8] = MurV1;

    Texture MurV2;
    if (!MurV2.loadFromFile("Assets/MurV2.png"))
        throw std::runtime_error("Cannot load Assets/MurV2.png");
    textures[9] = MurV2;

};

//Methode pour creer le grid, ça va lire le fichier verif les textures et assigner ça aux positions de la grid (qui n'est nul autre qu'une matrice)
void initTileMap() {
    tileMap.resize(mapSize, vector<RectangleShape>(mapSize));

    for (int x = 0; x < mapSize; ++x) {
        for (int y = 0; y < mapSize; ++y) {
            tileMap[x][y].setSize(Vector2f(gridSize, gridSize));
            tileMap[x][y].setPosition(x * gridSize, y * gridSize);

            int tileType = tileTypes[x][y];
            if (textures.find(tileType) != textures.end()) {
                tileMap[x][y].setTexture(&textures[tileType]);
            }
            else {
                cerr << "Texture not found for tile type: " << tileType << endl;
            }
        }
    }

};

//ça regarde le fichier avec les textures
void loadTileTypes(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "cant open tile types file";
    }

    tileTypes.resize(mapSize, vector<int>(mapSize));
    for (int x = 0; x < mapSize; ++x) {
        for (int y = 0; y < mapSize; ++y) {
            file >> tileTypes[x][y];
        }
    }

    file.close();
}
//ça regarde le fichier avec les collisions, a rappeler parce qu'il ne fait que look il ne creer pas de collision
void loadCollisionMap(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw "cant open collision map file";
    }

    collisionMap.resize(mapSize, vector<int>(mapSize));
    for (int x = 0; x < mapSize; ++x) {
        for (int y = 0; y < mapSize; ++y) {
            file >> collisionMap[x][y];
        }
    }

    file.close();
}

public:
    MapManager(float gridSize, int mapSize, const string& tileTypesFile, const string& collisionMapFile)
        : gridSize(gridSize), mapSize(mapSize) {
        loadTextures();
        loadTileTypes(tileTypesFile);
        loadCollisionMap(collisionMapFile);
        initTileMap();
    }

    const vector<vector<RectangleShape>>& getTileMap() const {
        return tileMap;
    }

    const vector<vector<int>>& getCollisionMap() const {
        return collisionMap;
    }

    float getGridSize() {
        return this->gridSize;
    }
};