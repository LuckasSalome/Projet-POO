#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Wall.h"
#include "Sol.h"

class Salle
{
public:
    Salle(int widthTiles, int heightTiles, sf::Texture* SolTexture, sf::Texture* MurTexture, sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));
    ~Salle();

    void generateRoom();
    void drawRoom(sf::RenderWindow& window) const;
    std::vector<Wall> getMurs() const;
    std::vector<Sol> getSols() const;

private:
    sf::RectangleShape solbody;
    sf::Texture* MurTexture;
    sf::Texture* SolTexture;
    std::vector<Wall> murs;
    std::vector<Sol> sols;

    float widthTile;
    float heightTile;
    int widthTiles;
    int heightTiles;
    sf::Vector2f position;
};
