#pragma once

#include "ProgramLich.hpp"

using namespace std;

class Pattern1 : public ProgramLich {
public:
    Pattern1(const string& name, const string& desc, int maxHp) : ProgramLich(name, desc, maxHp) {}

    map<string, int> Ability1() const override {
        return { {"Name", "SyntaxError"}, {"Damage", 30};
    }

    map<string, int> Ability2() const override {
            return { {"Name", "NullPointerException"}, {"Damage", 50};
    }

    map<string, int> Ability3() const override {
                return { {"Name", "StackOverflow"}, {"Damage", 80};
    }
};
