#pragma once

#include "Items.hpp"

class MajorHealingPotion : public Items {
private : 
	std::map<std::string, int> stat = { {"PV", 50}, {"Poids", 1} };
public:
    MajorHealingPotion()
        : Items("Potion de soin majeur",
            "Une potion digne des plus grands, confectionn�e � partir de jus de mirabelle,\n elle restaure une grande quantit� de points de vie",
            { {"PV", 50}, {"Poids", 1} },
            "images/MajorHealingPotion.png") {};
};
