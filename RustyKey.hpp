#pragma once

#include "Items.hpp"

class RustyKey : public Items {
public:
    RustyKey()
        : Items("Cle rouill�e",
            "Une cle sale et rouill�e",
            { {"Poids", 1} },
            "images/RustKey.png") {}
};


