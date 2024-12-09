#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class DialogBox {
private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape box;

public:
    DialogBox(float width, float height) {
        if (!font.loadFromFile("images/RobotoBlack.ttf")) {
            // Handle error
        }
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color(15, 76, 146, 245));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2);
    }

    void setPosition(float x, float y) {
        box.setPosition(x, y);
        text.setPosition(x + 10, y + 10);
    }

    void setText(const std::string& message) {
        text.setString(message);
    }

    sf::Vector2f getSize() const {
        return box.getSize();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }
};