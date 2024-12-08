#pragma once

#include "Weapon.hpp"

class SorcererStick : public Weapon {
private :
	std::map<std::string, int> stat = { {"ATT", 40}, {"Poids", 5} };
public:
	SorcererStick()
		: Weapon("Bâton de sorcier",
			"Un artefact digne des plus grands mage, seul les mages de plus de 1m80 peuvent les utilisés",
			{ {"ATT", 40}, {"Poids", 5} },
			"images/SorcererStick.png") {};
};