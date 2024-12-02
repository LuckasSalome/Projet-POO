#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"Map.hpp"
using namespace sf;
using namespace std;

class Player {

private:

	RectangleShape player;
	Texture playerTex;
	View playerView;
	Map* map;
	float velocityY = 0;
	float velocityX = 0;
	const float movementSpeed = 400;

	void playerInit() {

		this->player.setSize(Vector2f(map->getGridSize(), map->getGridSize()));
		this->player.setPosition(Vector2f((map->getGridSize() * 1), (map->getGridSize() * 1)));
		this->setPlayerTex();
		this->player.setTexture(&playerTex);

	};

public:
	Player(Map* map) : map(map) {
		this->playerInit();
	}

	void playerMovement(float dt) {

	if (Keyboard::isKeyPressed(Keyboard::Q)) //Left
	{
		player.move(-movementSpeed * dt, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))//Right 
	{
		player.move(movementSpeed * dt, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) //Up
	{
		player.move(0.f, -movementSpeed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) //Up
	{
		player.move(0.f, movementSpeed * dt);
	}

	};

	void setPlayerTex() {
	
	if (!playerTex.loadFromFile("Assets/cat.png"))
		throw "cant load cat png";

	};

	const RectangleShape& getPlayer() const {
		return this->player;
	}

	Vector2f getPositionPlayer() {

		return this->player.getPosition();

	};
	
};