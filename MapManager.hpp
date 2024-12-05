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
    const int COLLISION_TRIGGER = 2;

///////////////////////////Ajoutez vos textures ici\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

            Texture Black;
            if (!Black.loadFromFile("Assets/black.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[10] = Black;

            Texture grass01;
            if (!grass01.loadFromFile("Assets/grass01.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[11] = grass01;

            Texture grass02;
            if (!grass02.loadFromFile("Assets/grass02.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[12] = grass02;

            Texture grass03;
            if (!grass03.loadFromFile("Assets/grass03.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[13] = grass03;

            Texture hill1;
            if (!hill1.loadFromFile("Assets/hill1.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[14] = hill1;

            Texture hill2;
            if (!hill2.loadFromFile("Assets/hill2.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[15] = hill2;

            Texture hill3;
            if (!hill3.loadFromFile("Assets/hill3.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[16] = hill3;

            Texture hill4;
            if (!hill4.loadFromFile("Assets/hill4.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[17] = hill4;

            Texture entree2;
            if (!entree2.loadFromFile("Assets/entree2.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[18] = entree2;

            Texture stairs1;
            if (!stairs1.loadFromFile("Assets/stairs1.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[19] = stairs1;

            Texture stairs2;
            if (!stairs2.loadFromFile("Assets/stairs2.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[20] = stairs2;

            Texture mur2;
            if (!mur2.loadFromFile("Assets/mur2.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[21] = mur2;

            Texture sol3;
            if (!sol3.loadFromFile("Assets/sol3.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[22] = sol3;

            Texture sol4;
            if (!sol4.loadFromFile("Assets/sol4.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[23] = sol4;

            Texture sol5;
            if (!sol5.loadFromFile("Assets/sol5.png"))
                throw std::runtime_error("Cannot load Assets/MurV2.png");
            textures[24] = sol5;
        };


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

    void loadNewMap(const string& newTileTypesFile, const string& newCollisionMapFile) {
        vector<vector<int>> newTileTypes(mapSize, vector<int>(mapSize));
        vector<vector<int>> newCollisionMap(mapSize, vector<int>(mapSize));

        ifstream tileTypesFile(newTileTypesFile);
        if (!tileTypesFile.is_open()) {
            throw "cant open tile types file";
        }
        for (int x = 0; x < mapSize; ++x) {
            for (int y = 0; y < mapSize; ++y) {
                tileTypesFile >> newTileTypes[x][y];
            }
        }
        tileTypesFile.close();

        ifstream collisionMapFile(newCollisionMapFile);
        if (!collisionMapFile.is_open()) {
            throw "cant open collision map file";
        }
        for (int x = 0; x < mapSize; ++x) {
            for (int y = 0; y < mapSize; ++y) {
                collisionMapFile >> newCollisionMap[x][y];
            }
        }
        collisionMapFile.close();

        setTileTypes(newTileTypes);
        setCollisionMap(newCollisionMap);
    }


    void setTileTypes(const vector<vector<int>>& newTileTypes) {
        tileTypes = newTileTypes;
        initTileMap();
    }

    void setCollisionMap(const vector<vector<int>>& newCollisionMap) {
        collisionMap = newCollisionMap;
    }

};
