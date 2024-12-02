#pragma once 

#include <iostream>
#include <string>
#include "ProgramLich.hpp"

using namespace std;

class Pattern1 : public ProgramLich {
private:
    virtual map<string, int> stat() = 0;
    virtual map<string, int> Ability1() = 0;
    virtual map<string, int> Ability2() = 0;
    virtual map<string, int> Ability3() = 0;

public:
    virtual map<string, int> getstat() = 0;
    virtual map<string, int> getAbility1(const string) = 0;
    virtual map<string, int> getAbility2(const string) = 0;
    virtual map<string, int> getAbility3(const string) = 0;
};
