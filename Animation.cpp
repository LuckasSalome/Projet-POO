#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float SwitchTime)
{
	this->imageCount = imageCount;
	this->SwitchTime = SwitchTime;
	TotalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width  = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}


Animation::~Animation()
{

}

void Animation::update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	TotalTime += deltaTime;

	if (TotalTime >= SwitchTime)
	{
		TotalTime -= SwitchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}


	}


	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}

}