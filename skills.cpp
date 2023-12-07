#include "skills.h"

RACE_SKILLS::RACE_SKILLS()
{

}

RACE_SKILLS::~RACE_SKILLS()
{
   std::cout << "In RACE_SKILLS destructor" << std::endl;
}

Dwarf::Dwarf()
{
    setRaceSkills();
}

Dwarf::~Dwarf()
{
   std::cout << "In Dwarf destructor" << std::endl;
}

void Dwarf::setRaceSkills()
{
    detectGrade.sidedDie = 4;
    detectGrade.maxRange = 3;
    dtctConstrPsg.sidedDie = 4;
    dtctConstrPsg.maxRange = 3;
    dtctMovingWalls.sidedDie = 6;
    dtctMovingWalls.maxRange = 4;
    dtctTraps.sidedDie = 4;
    dtctTraps.maxRange = 2;
    dtctDepth.sidedDie = 4;
    dtctDepth.maxRange = 2;
}

void Dwarf::listRaceSkills()
{
    std::cout << "Detect Grade or Slope roll d" << (int)detectGrade.sidedDie << " succeeds: 1-" << (int)detectGrade.maxRange << std::endl;
    std::cout << "Detect recent Construction passage or tunnel roll d" << (int)dtctConstrPsg.sidedDie << " succeeds: 1-" << (int)dtctConstrPsg.maxRange << std::endl;
    std::cout << "Detect shifting or sliding walls roll d" << (int)dtctMovingWalls.sidedDie << " succeeds: 1-" << (int)dtctMovingWalls.maxRange << std::endl;
    std::cout << "Detect traps inv. pits blocks or stonework roll d" << (int)dtctTraps.sidedDie << " succeeds: 1-" << (int)dtctTraps.maxRange << std::endl;
    std::cout << "Detect depth bellow ground roll d" << (int)dtctDepth.sidedDie << " succeeds: 1-" << (int)dtctDepth.maxRange << std::endl;
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
    std::cout << "To hit bonus while fighting Half-Orc, Goblin, Hobgoblin and Orc +" << toHitBonus << std::endl;
    std::cout << "Certain Adversary to hit penalty to Dwarf " << adversaryHitPenalty << std::endl;
}

Elf::Elf()
{
    setRaceSkills();
}

Elf::~Elf()
{

}

void Elf::setRaceSkills()
{
    resistSlpChrm.sidedDie = 100; // 90 > d100
    resistSlpChrm.maxRange = 90;
    secConDoorPsv.sidedDie = 6;
    secConDoorPsv.maxRange = 1; // within 10'
    secConDoorActv.sidedDie = 6;
    secConDoorActv.maxRange = 2;
    conPortal.sidedDie = 6;
    conPortal.maxRange = 3;
    chanceToSurprise.sidedDie = 6;
    chanceToSurprise.maxRange = 4;
    chanceToSurprisePort.sidedDie = 6;
    chanceToSurprise.maxRange = 2;
}

void Elf::listRaceSkills()
{
    std::cout << "Resist sleep or charm d" << (int)resistSlpChrm.sidedDie << " succeeds: 1-" << (int)resistSlpChrm.maxRange << std::endl;
    std::cout << "Detect secret or concealed door passive within 10' d" << (int)secConDoorPsv.sidedDie << " succeeds: 1-" << (int)secConDoorPsv.maxRange << std::endl;
    std::cout << "Detect secret or concealed door active d" << (int)secConDoorActv.sidedDie << " succeeds: 1-" << (int)secConDoorActv.maxRange << std::endl;
    std::cout << "Detect concealed portal d" << (int)conPortal.sidedDie << " succeeds: 1-" << (int)conPortal.maxRange << std::endl;
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
    std::cout << "To hit bonus while using short sword, long sword, bow and crossbow +" << toHitBonus << std::endl;
    std::cout << "Chance to surprise creatures in a party of all Elves, or Elves and Halflings d" << (int)chanceToSurprise.sidedDie << " succeeds: 1-" << (int)chanceToSurprise.maxRange << std::endl;
}

