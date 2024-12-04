#pragma once

#include "Items.hpp"

class BookOfLostRules : public Items {
public:
    BookOfLostRules()
        : Items("Livre des r�gles perdues",
            "Un livre renfermant les r�gles du fight club",
            { {"Poids", 1} },
            "images/BookOfLostRules.png") {}
};
