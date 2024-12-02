#pragma once

#include "Items.hpp"

class DiscretionShoesNoisy : public Items {
public:
    DiscretionShoesNoisy()
        : Items("Chausson de discr�tion bruyant",
            "Des chaussons ressemblant � ceux de votre grand-m�re, ils sont doux et l�gers avec le dessous de la chaussure recouvert de claque doigts",
            { {"AD", -2}, {"Poids", 2} },
            "images/DiscretionShoesNoisy.png") {}
};
