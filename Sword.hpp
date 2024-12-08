#pragma once

#include "Weapon.hpp"

class Sword : public Weapon {
private : 
	std::map<std::string, int> stat = { {"ATT", 40}, {"Poids", 5} };
public:
	Sword()
		: Weapon("Epee longue",
			"Trancheur de vier",
			{ {"ATT", 40}, {"Poids", 5} },
			"images/Sword.png") {};
};