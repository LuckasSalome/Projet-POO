#pragma once

#include "Boots.hpp"

class DiscretionShoesNoisy : public Boots {
private :
	std::map<std::string, int> stat = { {"AD", -2}, {"Poids", 2} };
public:
    DiscretionShoesNoisy()
        : Boots("Chausson de discrétion bruyant",
            "Des chaussons ressemblant à ceux de votre grand-mère, ils sont doux \net légers avec le dessous de la chaussure recouvert de claque doigts",
            { {"AD", -2}, {"Poids", 2} },
            "images/DiscretionShoesNoisy.png") {};
};
