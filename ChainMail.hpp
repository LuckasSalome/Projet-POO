#pragma once

#include "ChestArmor.hpp"

class ChainMail : public ChestArmor {
public:
	ChainMail()
		: ChestArmor("Cotte de maille",
			"Une cotte de maille qui laisse passer rien du tout sauf l'air",
			{ {"FO", 5}, {"Poids", 10} },
			"images/ChainMail.png") {}
};