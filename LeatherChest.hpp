#pragma once

#include "ChestArmor.hpp"

class LeatherChest : public ChestArmor {
public:
	LeatherChest()
		: ChestArmor("Plastron en cuire",
			"Pas besoin de desciption tout le temps",
			{ {"CHA", 3}, {"Poids", 5} },
			"images/LeatherChest.png") {}
};