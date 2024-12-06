#pragma once

#include "Items.hpp"

class RustyKey : public Items {
public:
    RustyKey()
        : Items("Cle rouillée",
            "Une cle sale et rouillée",
            { {"Poids", 1} },
            "images/RustKey.png") {}
};


