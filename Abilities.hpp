#pragma once

#include <string>
#include <map>

using namespace std;


class Abilities {

protected :
	virtual void Attack(string Caster, string Target) = 0;
	virtual void Block(string Caster, string Target) = 0;
	virtual void Spell(string Caster, string Target) = 0;
	virtual string getAbilityDesc() = 0;
};