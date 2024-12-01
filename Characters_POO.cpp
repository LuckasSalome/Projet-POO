#include <iostream>

#include "Heroes.hpp"

using namespace std;

Jobs* createJobs(const string& type) {
    if (type == "Guerrier") {
        return new Warrior();
    }
    else if (type == "Sorcier") {
        return new Sorcerer();
    }
    else if (type == "Voleur") {
        return new Thief();
    }
    else if (type == "Rodeur") {
        return new Ranger();
    }
    else {
        return nullptr;
    }
}
Race* createRace(const string& type) {
    if (type == "Elfe") {
        return new Elf();
    }
    else if (type == "Barbare") {
        return new Barbarian();
    }
    else if (type == "Nain") {
        return new Dwarf();
    }
    else if (type == "Humain") {
        return new Human();
    }
    else {
        return nullptr;
    }
}

int main()
{
    string jobType;
    string raceType;
    string statistics[5] = { "COU", "CHA", "INT", "FO", "AD" };

    cin >> jobType;
    cin >> raceType;

    Jobs* job = createJobs(jobType);
    Race* race = createRace(raceType);
    Heroes* Character1 = new Heroes("Michel");


    cout << Character1->getName(*race, *job) << endl;
    cout << Character1->getDesc(*race, *job) << endl;
    cout << Character1->getHealth() << endl;
    for (int i = 0; i < 5; i++)
        cout << Character1->getHeroStat(*race, *job)[statistics[i]] << endl;
}

