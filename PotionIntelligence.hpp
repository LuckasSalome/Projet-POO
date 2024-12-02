#pragma once

#include "Items.hpp"

// PotionIntelligence class inherits from Items
class PotionIntelligence : public Items {
public:
    // Constructor initializes with specific values for this potion
    PotionIntelligence()
        : Items("Potion d'intelligence discutable",
            "Cet elixir provient d'une cave de mestre nommé epstein, on pense donc qu'elle rend intelligent ",
            { {"COU", 2}, {"CHA", 2}, {"AD", 2}, {"FO", 2}, {"Poids", 1} },
            "images/PotionIntelligence.png") {}
};
