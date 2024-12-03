#pragma once

#include "Weapon.hpp"

class Sword : public Weapon {
public:
	Sword()
		: Weapon("Epee longue", 
			"Trancheur de vier", 
			{ {"ATT", 40}, {"Poids", 5} },
		"images/Sword.png") {}
};