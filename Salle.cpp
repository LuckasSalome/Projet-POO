#include "Salle.h"
#include <iostream>

Salle::Salle(int widthTiles, int heightTiles, sf::Texture* SolTexture, sf::Texture* MurTexture, sf::Vector2f position)
    : SolTexture(SolTexture), MurTexture(MurTexture), widthTiles(widthTiles), heightTiles(heightTiles), widthTile(210.0f), heightTile(199.0f), position(position)
{
    // Initialisation des sols
    solbody.setSize(sf::Vector2f(widthTiles * widthTile, heightTiles * heightTile));
    solbody.setTexture(SolTexture);
    SolTexture->setRepeated(true);
    solbody.setTextureRect(sf::IntRect(0, 0, widthTiles * widthTile, heightTiles * heightTile));
    solbody.setPosition(position);
}

Salle::~Salle() {}

void Salle::generateRoom() {
    // Générer les sols
    for (int i = 0; i < widthTiles; ++i) {
        for (int j = 0; j < heightTiles; ++j) {
            sf::Vector2f solPosition(position.x + i * widthTile, position.y + j * heightTile);
            Sol sol(sf::Vector2f(widthTile, heightTile), solPosition, SolTexture);
            sols.push_back(sol);
        }
    }

    // Générer les murs
    for (int i = -1; i <= widthTiles; ++i) {
        // Mur du haut
        sf::Vector2f murPositionTop(position.x + i * widthTile, position.y - heightTile);
        Wall murTop(sf::Vector2f(widthTile, heightTile), murPositionTop, sf::Color::White, MurTexture);
        murs.push_back(murTop);

        // Mur du bas
        sf::Vector2f murPositionBottom(position.x + i * widthTile, position.y + heightTiles * heightTile);
        Wall murBottom(sf::Vector2f(widthTile, heightTile), murPositionBottom, sf::Color::White, MurTexture);
        murs.push_back(murBottom);
    }

    for (int j = 0; j < heightTiles; ++j) {
        // Mur de gauche
        sf::Vector2f murPositionLeft(position.x - widthTile, position.y + j * heightTile);
        Wall murLeft(sf::Vector2f(widthTile, heightTile), murPositionLeft, sf::Color::White, MurTexture);
        murs.push_back(murLeft);

        // Mur de droite
        sf::Vector2f murPositionRight(position.x + widthTiles * widthTile, position.y + j * heightTile);
        Wall murRight(sf::Vector2f(widthTile, heightTile), murPositionRight, sf::Color::White, MurTexture);
        murs.push_back(murRight);
    }
}

void Salle::drawRoom(sf::RenderWindow& window) const {
    window.draw(solbody);
    for (const auto& mur : murs) {
        mur.Draw(window);
    }
    for (const auto& sol : sols) {
        sol.Draw(window);
    }
}

std::vector<Wall> Salle::getMurs() const {
    return murs;
}

std::vector<Sol> Salle::getSols() const {
    return sols;
}
