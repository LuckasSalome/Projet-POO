#include <iostream>
#include <queue>


//fichiers a utilisier
#include "Heroes.hpp"
#include "Creatures.hpp"
#include "ExplosiveDuck.hpp"
#include "RhetoricianTroll.hpp"
#include "SarcasticGobelin.hpp"
#include "ProgramLich.hpp"
#include "Fight.hpp"


using namespace std;

//##########  IMPORTANT   #########  pour creer les objets les fonctions en dessous prennent juste un string et renvoient un objet du type voulu [obligatoire pour init / utiliser]
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

static Entity* createEntity(const string& type, const string name) {
    if (type == "Hero")
        return new Heroes(name);
    else if (type == "Monstre")
        return new Creatures();
}

//############   totallement inutile c juste pour savoir comment utiliser et parce que les comme les fonctions sont virtuelles elle doivent etre crées pour lancer
int main()
{
    //def des string pour le type de race hero, le metier hero, le type de mob
    string jobType = "Sorcier";
    string raceType = "Elfe";
    string mobType = "Gobelin Sarcastique";
    string statistics[6] = { "COU", "CHA", "INT", "FO", "AD", "HP"};  //les stats sont sous ce format pour y acceder utiliser les clés ["COU"] etc. pour modifier utiliser les fonctions set(inser)Stat()

    // crée les classes filles pour instancier les meres
    Jobs* job = createJobs(jobType);
    Race* race = createRace(raceType);
    Common* mob = createMob(mobType);
    Boss* lich = new ProgramLich();

    //crée les héros, boss et monstres 
    Entity* Character1 = createEntity("Hero", "Michel");
    Entity* Mob1 = createEntity("Monstre", "");
    Entity* Boss = createEntity("Monstre", "");
    Group* Heros = new Group();
    Group* Monstres = new Group();


     //init hero numero 1
    Character1->StatComparison(*race, *job);
    Character1->initDesc(*race, *job);
    Character1->initName(*race, *job);
    Character1->initHeroStat(*race, *job);


    //init monstre numero 1
    Mob1->initCreatureDesc(*mob);
    Mob1->initCreatureName(*mob);
    Mob1->initCreatureStat(*mob);

    //init boss
    Boss->initBossName(*lich);
    Boss->initBossDesc(*lich);
    Boss->initBossStat(*lich);

    //definition des groupes
    Heros->addParty(Character1);
    Monstres->addGroup(Mob1);

    Heros->removeParty(Character1);
    Heros->addParty(Character1);

    //============================================       LIGNEs POUR LANCER COMBAT      =================================================
    Fight* combat = new Fight(*Heros, *Monstres);
    combat->fighting();

    //affiche le hero et le monstre
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getStat()[statistics[i]] << endl;


    cout << Mob1->getName() << endl;
    cout << Mob1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Mob1->getStat()[statistics[i]] << endl;


    //attaque du hero
    cout << Character1->getRaceSpell(*race, *Mob1) << endl;
    cout << Character1->getJobSpell(*job, *Mob1) <<endl;
    cout << Character1->getBasicAttack(*race, *Mob1) << endl;

    //stats retours monstre
    cout << Mob1->getName() << endl;
    cout << Mob1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Mob1->getStat()[statistics[i]] << endl;

    //attaque du monstre 
    cout << Mob1->getMonsterSpell(*mob, *Character1) << endl;
    cout << Mob1->getBasicAttack(*mob, *Character1) << endl;

    //affiche boss
    cout << Boss->getName() << endl;
    cout << Boss->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Boss->getStat()[statistics[i]] << endl;


    //attaque p1 boss
    cout << Boss->getBossSpell1(*lich, *Character1) << endl;
    cout << Boss->getBossSpell2(*lich, *Character1) << endl;


    //stats retours hero
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getStat()[statistics[i]] << endl;

    Boss->setHealth(45);
    //affiche boss
    cout << Boss->getName() << endl;
    cout << Boss->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Boss->getStat()[statistics[i]] << endl;

    // attaque p2 bosse
    cout << Boss->getBossSpell1(*lich, *Character1) << endl;
    cout << Boss->getBossSpell2(*lich, *Character1) << endl;

    //stats retours hero
    cout << Character1->getName() << endl;
    cout << Character1->getDesc() << endl;
    for (int i = 0; i < 6; i++)
        cout << Character1->getStat()[statistics[i]] << endl;

    return 0;
}

