#pragma once

#include <string>
#include <map>
#include "Boss.hpp"

class Pattern2 : public Boss {
private :
        std::string name = "Liche Programmatrice";
        std::string desc = "Va te corriger";

protected :

    virtual std::string getBossName() override {
        return this->name;
    }
    virtual std::string getBossDesc() override {
        return this->desc;
    }

};
