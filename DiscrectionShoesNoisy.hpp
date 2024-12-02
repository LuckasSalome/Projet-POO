#pragma once

#include "Items.hpp"

class DiscretionShoesNoisy : public Items {
public:
    DiscretionShoesNoisy()
        : Items("Chausson de discrétion bruyant",
            "Des chaussons ressemblant à ceux de votre grand-mère, ils sont doux et légers avec le dessous de la chaussure recouvert de claque doigts",
            { {"AD", -2}, {"Poids", 2} },
            "images/DiscretionShoesNoisy.png") {}
};
