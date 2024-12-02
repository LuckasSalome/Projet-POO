#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Boss.hpp"

using namespace std;

class ProgramLich : public Boss {
private:
    string name;
    string desc;

public:
    ProgramLich(const string& name, const string& desc) : name(name), desc(desc) {}

    string getNameCreature() const override {
        return name;
    }

    string getDescCreature() const override {
        return desc;
    }

protected:
    virtual map<string, int> getStatCreature() = 0;
    virtual map<string, int> getAbility1(const string) const = 0;
    virtual map<string, int> getAbility2(const string) const = 0;
    virtual map<string, int> getAbility3(const string) const = 0;
};
