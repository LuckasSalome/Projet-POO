#pragma once

#include "Weapon.hpp"

class Dagger : public Weapon {
public:
	Dagger()
		: Weapon("Dague des sentinelles de la nuit obscure",
			"Une dague simple sans aspect particulier et des plus ordinaires",
			{ {"ATT", 25}, {"Poids", 3} },
			"images/Dagger.png") {}
};