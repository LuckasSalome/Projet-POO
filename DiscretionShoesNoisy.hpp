#pragma once

#include "Boots.hpp"

class DiscretionShoesNoisy : public Boots {
private :
	std::map<std::string, int> stat = { {"AD", -2}, {"Poids", 2} };
public:
    DiscretionShoesNoisy()
        : Boots("Chausson de discr�tion bruyant",
            "Des chaussons ressemblant � ceux de votre grand-m�re, ils sont doux \net l�gers avec le dessous de la chaussure recouvert de claque doigts",
            { {"AD", -2}, {"Poids", 2} },
            "images/DiscretionShoesNoisy.png") {};
};
