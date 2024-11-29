#pragma once

#include "Items.hpp"

class RustyKey : Items {
private:

	string name;
	string description;
    map <string, int> stats;

public:

	RustyKey() : name("Cle rouillee"), description("Une cle sale et rouillee") {
        stats["Poids"] = 1;
    }

    string getNameItem() const override {
        return name;
    }

    string getDescItem() const override {
        return description;
    }

    map<string, int> getStatItem() const override {
        return stats;
    }
};
