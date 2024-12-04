#include <iostream>
#include <queue>

#include "Heroes.hpp"
#include "Creatures.hpp"
#include "ExplosiveDuck.hpp"
#include "RhetoricianTroll.hpp"
#include "SarcasticGobelin.hpp"
#include "ProgramLich.hpp"
#include "Fight.hpp"


using namespace std;

static Jobs* createJobs(const string& type) {
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
static Race* createRace(const string& type) {
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
static Common* createMob(const string& type) {
    if (type == "Gobelin Sarcastique") {
        return new SarcasticGobelin();
    }
    else if (type == "Troll Rhetoricien") {
        return new RhetoricianTroll();
    }
    else if (type == "Canard Explosif") {
        return new ExplosiveDuck();
    }
    else {
        return nullptr;
    }
}


int main()
{
    string jobType = "Sorcier";
    string raceType = "Elfe";
    string mobType = "Gobelin Sarcastique";
    string statistics[6] = { "COU", "CHA", "INT", "FO", "AD", "HP"};

    Jobs* job = createJobs(jobType);
    Race* race = createRace(raceType);
    Common* mob = createMob(mobType);
    Boss* lich = new ProgramLich();

    Heroes* Character1 = new Heroes("Michel");
    Creatures* Mob1 = new Creatures();
    Creatures* Boss = new Creatures();
    Group* Heros = new Group();
    Group* Monstres = new Group();


     //hero numero 1
    Character1->StatComparison(*race, *job);
    Character1->initDesc(*race, *job);
    Character1->initName(*race, *job);
    Character1->initHeroStat(*race, *job);


    //monstre numero 1
    Mob1->initCreatureDesc(*mob);
    Mob1->initCreatureName(*mob);
    Mob1->initCreatureStat(*mob);

    //boss
    Boss->initBossName(*lich);
    Boss->initBossDesc(*lich);
    Boss->initBossStat(*lich);

    Heros->addParty(Character1);
    Monstres->addGroup(Mob1);

    Heros->removeParty(Character1);

    Fight* combat = new Fight(*Heros, *Monstres);

    queue<string> Ordre = combat->fightOrder();
    while (!Ordre.empty()) {
        cout << Ordre.front() << endl; Ordre.pop();
    }


    //affiche le hero et le monstre
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getHeroStat()[statistics[i]] << endl;


    cout << Mob1->getCreatureName() << endl;
    cout << Mob1->getCreatureDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Mob1->getCreatureStat()[statistics[i]] << endl;


    //attaque du hero
    cout << Character1->getRaceSpell(*race, *Mob1) << endl;
    cout << Character1->getJobSpell(*job, *Mob1) <<endl;
    cout << Character1->getBasicAttack(*race, *Mob1) << endl;

    //stats retours monstre
    cout << Mob1->getCreatureName() << endl;
    cout << Mob1->getCreatureDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Mob1->getCreatureStat()[statistics[i]] << endl;

    //attaque du monstre 
    cout << Mob1->getMonsterSpell(*mob, *Character1) << endl;
    cout << Mob1->getBasicAttack(*mob, *Character1) << endl;

    //affiche boss
    cout << Boss->getCreatureName() << endl;
    cout << Boss->getCreatureDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Boss->getCreatureStat()[statistics[i]] << endl;


    //attaque p1 boss
    cout << Boss->getBossSpell1(*lich, *Character1) << endl;
    cout << Boss->getBossSpell2(*lich, *Character1) << endl;


    //stats retours hero
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getHeroStat()[statistics[i]] << endl;

    Boss->setCreatureHealth(45);
    //affiche boss
    cout << Boss->getCreatureName() << endl;
    cout << Boss->getCreatureDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Boss->getCreatureStat()[statistics[i]] << endl;

    // attaque p2 bosse
    cout << Boss->getBossSpell1(*lich, *Character1) << endl;
    cout << Boss->getBossSpell2(*lich, *Character1) << endl;

    //stats retours hero
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getHeroStat()[statistics[i]] << endl;

    return 0;
}

