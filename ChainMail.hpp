#pragma once

#include "ChestArmor.hpp"

class ChainMail : public ChestArmor {
private : 
	std::map<std::string, int> stat = { {"FO", 5}, {"Poids", 10} };
public:
	ChainMail()
		: ChestArmor("Cotte de maille",
			"Une cotte de maille qui laisse passer rien du tout sauf l'air",
			{ {"FO", 5}, {"Poids", 10} },
			"images/ChainMail.png") {};
};