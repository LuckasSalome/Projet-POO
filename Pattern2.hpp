#pragma once 

#include "Pattern1.hpp"

using namespace std;

#pragma once

#include "ProgramLich.hpp"

class Pattern2 : public ProgramLich {
public:
    Pattern2(const string& name, const string& desc, int maxHp)
        : ProgramLich(name, desc, maxHp) {}

    map<string, int> Ability1() const override {
        return { {"Name", "MemoryLeak"}, {"Damage", 40};
    }

    map<string, int> Ability2() const override {
        return { {"Name", "SegmentationFault"}, {"Damage", 60};
    }

    map<string, int> Ability3() const override {
        return { {"Name", "RaceCondition"}, {"Damage", 100};
    }
};

