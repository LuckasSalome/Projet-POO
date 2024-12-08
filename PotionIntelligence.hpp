#pragma once

#include "Items.hpp"

class PotionIntelligence : public Items {
private:
	std::map<std::string, int> stat = { {"COU", 2}, {"CHA", 2}, {"AD", 2}, {"FO", 2}, {"Poids", 1} };
public:
    PotionIntelligence()
        : Items("Potion d'intelligence discutable",
            "Cet elixir provient d'une cave de mestre nommé epstein, \non pense donc qu'elle rend intelligent ",
            { {"COU", 2}, {"CHA", 2}, {"AD", 2}, {"FO", 2}, {"Poids", 1} },
            "images/PotionIntelligence.png") {};
};
