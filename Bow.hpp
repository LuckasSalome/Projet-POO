#pragma once

#include "Weapon.hpp"

class Bow : public Weapon {
public:
	Bow()
		: Weapon("Arc simple",
			"Un arc de chasse sp�cialement con�u pour une saison",
			{ {"ATT", 25}, {"Poids", 3} },
			"images/Bow.png") {}
};