#pragma once

#include "ChestArmor.hpp"

class SorcererCape : public ChestArmor {
private : 
	std::map<std::string, int> stat = { {"COU", 5}, {"Poids", 10} };
public:
	SorcererCape()
		: ChestArmor("Cape de sorcier",
			"+50 resistance magique",
			{ {"COU", 5}, {"Poids", 10} },
			"images/SorcererCape.png") {};
};