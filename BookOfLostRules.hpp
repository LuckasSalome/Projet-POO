#pragma once

#include "Items.hpp"

class BookOfLostRules : public Items {
public:
    BookOfLostRules()
        : Items("Livre des règles perdues",
            "Un livre renfermant les règles du fight club",
            { {"Poids", 1} },
            "images/BookOfLostRules.png") {}
};
