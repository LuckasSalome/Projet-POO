#pragma once

#include "ChestArmor.hpp"

class DarkCape : public ChestArmor {
public:
	DarkCape()
		: ChestArmor("Une cape sombre et pleine de malice",
			"Quand je suis sous ma capuche, je suis sous ma capuche.",
			{ {"AD", 5}, {"Poids", 3} },
			"images/DarkCape.png") {}
};