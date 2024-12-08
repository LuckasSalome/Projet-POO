#pragma once

#include "Weapon.hpp"

class Bow : public Weapon {
private : 
	std::map<std::string, int> stat = { {"ATT", 25}, {"Poids", 3} };
public:
	Bow()
		: Weapon("Arc simple",
			"Un arc de chasse spécialement conçu pour une saison",
			{ {"ATT", 25}, {"Poids", 3} },
			"images/Bow.png") {};
};