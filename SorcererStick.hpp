#pragma once

#include "Weapon.hpp"

class SorcererStick : public Weapon {
private :
	std::map<std::string, int> stat = { {"ATT", 40}, {"Poids", 5} };
public:
	SorcererStick()
		: Weapon("B�ton de sorcier",
			"Un artefact digne des plus grands mage, seul les mages de plus de 1m80 peuvent les utilis�s",
			{ {"ATT", 40}, {"Poids", 5} },
			"images/SorcererStick.png") {};
};