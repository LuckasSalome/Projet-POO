#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float SwitchTime);
	~Animation();

	sf::IntRect uvRect;

	void update(int row, float deltaTime, bool faceRight);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float TotalTime;
	float SwitchTime;
};

