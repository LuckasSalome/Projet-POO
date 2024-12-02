#pragma once

#include "Items.hpp"

// RustyKey class inherits from Items
class RustyKey : public Items {
public:
    // Constructor initializes with specific values for this key
    RustyKey()
        : Items("Cle rouillée",
            "Une cle sale et rouillée",
            { {"Poids", 1} },
            "images/RustKey.png") {}
};


