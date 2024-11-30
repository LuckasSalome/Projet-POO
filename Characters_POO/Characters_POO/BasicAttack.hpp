#pragma once

#include <string>
#include <map>
#include "Abilities.hpp"

using namespace std;

class BasicAttack : public Abilities {
public :
	int damages;
	
	void Attack(string Caster, string Target) override {

	}
};