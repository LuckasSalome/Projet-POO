#pragma once

#include "Boss.hpp"

using namespace std;

class ProgramLich : public Boss {
private:
    string name;
    string desc;

public:
    ProgramLich()
        : name("Liche Programmatrice"),
          desc("Une Liche Programmatrice terrifiante, maître des boucles infinies et des segfaults mystiques.") {}

    string getNameCreature() const override {
        return this->name;
    }

    string getDescCreature() const override {
        return this->desc;
    }
};
