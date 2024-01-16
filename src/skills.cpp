#include "skills.h"

//helper prototype
static void setDefenseBonus(stats inStats, int& defensiveBonus)
{
    switch(inStats.constitution){
        case 4:
        case 5:
        case 6:
            defensiveBonus = 1;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            defensiveBonus = 2;
            break;
        case 11:
        case 12:
        case 13:
            defensiveBonus = 3;
            break;
        case 14:
        case 15:
        case 16:
        case 17:
            defensiveBonus = 4;
            break;
        case 18:
        case 19:
            defensiveBonus = 5;
            break;
        default:
            if(inStats.constitution > 19){
                defensiveBonus = 5;
            } else {
                defensiveBonus = 0;
            }
            break;
    }
}

RACE_SKILLS::RACE_SKILLS(stats inStats)
{

}

RACE_SKILLS::RACE_SKILLS()
{

}

RACE_SKILLS::~RACE_SKILLS()
{
   //std::cout << "In RACE_SKILLS destructor" << std::endl;
}

Dwarf::Dwarf(stats inStats)
{
    setRaceSkills(inStats);
}

Dwarf::~Dwarf()
{
   //std::cout << "In Dwarf destructor" << std::endl;
}

void Dwarf::setRaceSkills(stats inStats)
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
    setDefenseBonus(inStats, defensiveBonus);
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
    std::cout << "Defense against Wands, staves, rods and spells: +" << defensiveBonus << std::endl;
}

std::vector<std::string> Dwarf::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (DWARF):");
    skillList.push_back("Detect Grade or Slope roll d" + std::to_string(detectGrade.sidedDie) + " succeeds: 1-" + std::to_string(detectGrade.maxRange));
    skillList.push_back("Detect recent Construction passage or tunnel roll d" + std::to_string(dtctConstrPsg.sidedDie) + " succeeds: 1-" + std::to_string(dtctConstrPsg.maxRange));
    skillList.push_back("Detect shifting or sliding walls roll d" + std::to_string(dtctMovingWalls.sidedDie) + " succeeds: 1-" + std::to_string(dtctMovingWalls.maxRange));
    skillList.push_back("Detect traps inv. pits blocks or stonework roll d" + std::to_string(dtctTraps.sidedDie) + " succeeds: 1-" + std::to_string(dtctTraps.maxRange));
    skillList.push_back("Detect depth bellow ground roll d" + std::to_string(dtctDepth.sidedDie) + " succeeds: 1-" + std::to_string(dtctDepth.maxRange));
    skillList.push_back("Infravision up to " + std::to_string(infraVision) +  "'");
    skillList.push_back("To hit bonus while fighting Half-Orc, Goblin, Hobgoblin and Orc +" + std::to_string(toHitBonus));
    skillList.push_back("Certain Adversary to hit penalty to Dwarf " + std::to_string(adversaryHitPenalty));
    skillList.push_back("Defense against Wands, staves, rods and spells: +" + std::to_string(defensiveBonus));
    return skillList;
}

Elf::Elf(stats inStats)
{
    setRaceSkills(inStats);
}

Elf::~Elf()
{
    //std::cout << "Elf Destructor Called." << std::endl;
}

void Elf::setRaceSkills(stats inStats)
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

std::vector<std::string> Elf::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (ELF):");
    skillList.push_back("Resist sleep or charm d" + std::to_string(resistSlpChrm.sidedDie) + " succeeds: 1-" + std::to_string(resistSlpChrm.maxRange));
    skillList.push_back("Detect secret or concealed door passive within 10' d" + std::to_string(secConDoorActv.sidedDie) + " succeeds: 1-" + std::to_string(secConDoorPsv.maxRange));
    skillList.push_back("Detect secret or concealed door active d" + std::to_string(secConDoorActv.sidedDie) + " succeeds: 1-" + std::to_string(secConDoorActv.maxRange));
    skillList.push_back("Detect concealed portal d" + std::to_string(conPortal.sidedDie) + " succeeds: 1-" + std::to_string(conPortal.maxRange));
    skillList.push_back("Infravision up to " + std::to_string(infraVision) + "'");
    skillList.push_back("To hit bonus while using short sword, long sword, bow and crossbow +" + std::to_string(toHitBonus));
    skillList.push_back("Chance to surprise creatures in a party of all Elves, or Elves and Halflings d" + std::to_string(chanceToSurprise.sidedDie) + " succeeds: 1-" + std::to_string(chanceToSurprise.maxRange));
    return skillList;
}

Gnome::Gnome(stats inStats)
{
    setRaceSkills(inStats);
}

Gnome::~Gnome()
{
   //std::cout << "In Gnome destructor" << std::endl;
}

void Gnome::setRaceSkills(stats inStats)
{
    detectGrade.sidedDie = 10;
    detectGrade.maxRange = 8;
    dtctUnsafeWCF.sidedDie = 10;
    dtctUnsafeWCF.maxRange = 7;
    detDirecUG.sidedDie = 10;
    detDirecUG.maxRange = 5;
    dtctDepth.sidedDie = 10;
    dtctDepth.maxRange = 6;
    setDefenseBonus(inStats, defensiveBonus);
}

void Gnome::listRaceSkills()
{
    std::cout << "Detect Grade or Slope roll d" << (int)detectGrade.sidedDie << " succeeds: 1-" << (int)detectGrade.maxRange << std::endl;
    std::cout << "Detect unsafe walls or ceilings d" << (int)dtctUnsafeWCF.sidedDie << " succeeds: 1-" << (int)dtctUnsafeWCF.maxRange << std::endl;
    std::cout << "Determine direction of travel underground d" << (int)detDirecUG.sidedDie << " succeeds: 1-" << (int)detDirecUG.maxRange << std::endl;
    std::cout << "Detect depth bellow ground roll d" << (int)dtctDepth.sidedDie << " succeeds: 1-" << (int)dtctDepth.maxRange << std::endl;
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
    std::cout << "To hit bonus while fighting Half-Orc, Goblin, Hobgoblin and Orc +" << toHitBonus << std::endl;
    std::cout << "Certain Adversary to hit penalty to Dwarf " << adversaryHitPenalty << std::endl;
    std::cout << "Defense against Wands, staves, rods and spells: +" << defensiveBonus << std::endl;
}

std::vector<std::string> Gnome::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (Gnome):");
    skillList.push_back("Detect Grade or Slope roll d" + std::to_string(detectGrade.sidedDie) + " succeeds: 1-" + std::to_string(detectGrade.maxRange));
    skillList.push_back("Determine direction of travel underground d" + std::to_string(detDirecUG.sidedDie) + " succeeds: 1-" + std::to_string(detDirecUG.maxRange));
    skillList.push_back("Detect unsafe walls or ceilings d" + std::to_string(dtctUnsafeWCF.sidedDie) + " succeeds: 1-" + std::to_string(dtctUnsafeWCF.maxRange));
    skillList.push_back("Detect depth bellow ground roll d" + std::to_string(dtctDepth.sidedDie) + " succeeds: 1-" + std::to_string(dtctDepth.maxRange));
    skillList.push_back("Infravision up to " + std::to_string(infraVision) +  "'");
    skillList.push_back("To hit bonus while fighting Half-Orc, Goblin, Hobgoblin and Orc +" + std::to_string(toHitBonus));
    skillList.push_back("Certain Adversary to hit penalty to Dwarf " + std::to_string(adversaryHitPenalty));
    skillList.push_back("Defense against Wands, staves, rods and spells: +" + std::to_string(defensiveBonus));
    return skillList;
}

HalfElf::HalfElf(stats inStats)
{
    setRaceSkills(inStats);
}

HalfElf::~HalfElf()
{
    //std::cout << "Half-Elf Destructor Called." << std::endl;
}

void HalfElf::setRaceSkills(stats inStats)
{
    resistSlpChrm.sidedDie = 100; // 90 > d100
    resistSlpChrm.maxRange = 30;
    secConDoorPsv.sidedDie = 6;
    secConDoorPsv.maxRange = 1; // within 10'
    secConDoorActv.sidedDie = 6;
    secConDoorActv.maxRange = 2;
    conPortal.sidedDie = 6;
    conPortal.maxRange = 3;
}

void HalfElf::listRaceSkills()
{
    std::cout << "Resist sleep or charm d" << (int)resistSlpChrm.sidedDie << " succeeds: 1-" << (int)resistSlpChrm.maxRange << std::endl;
    std::cout << "Detect secret or concealed door passive within 10' d" << (int)secConDoorPsv.sidedDie << " succeeds: 1-" << (int)secConDoorPsv.maxRange << std::endl;
    std::cout << "Detect secret or concealed door active d" << (int)secConDoorActv.sidedDie << " succeeds: 1-" << (int)secConDoorActv.maxRange << std::endl;
    std::cout << "Detect concealed portal d" << (int)conPortal.sidedDie << " succeeds: 1-" << (int)conPortal.maxRange << std::endl;
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
}

std::vector<std::string> HalfElf::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (Half-Elf):");
    skillList.push_back("Resist sleep or charm d" + std::to_string(resistSlpChrm.sidedDie) + " succeeds: 1-" + std::to_string(resistSlpChrm.maxRange));
    skillList.push_back("Detect secret or concealed door passive within 10' d" + std::to_string(secConDoorActv.sidedDie) + " succeeds: 1-" + std::to_string(secConDoorPsv.maxRange));
    skillList.push_back("Detect secret or concealed door active d" + std::to_string(secConDoorActv.sidedDie) + " succeeds: 1-" + std::to_string(secConDoorActv.maxRange));
    skillList.push_back("Detect concealed portal d" + std::to_string(conPortal.sidedDie) + " succeeds: 1-" + std::to_string(conPortal.maxRange));
    skillList.push_back("Infravision up to " + std::to_string(infraVision) + "'");
    return skillList;
}

Halfling::Halfling(stats inStats)
{
    setRaceSkills(inStats);
}

Halfling::~Halfling()
{
    //std::cout << "Halfling Destructor Called." << std::endl;
}

void Halfling::setRaceSkills(stats inStats)
{
    detectGrade.sidedDie = 10;
    detectGrade.maxRange = 8;
    detDirecUG.sidedDie = 10;
    detDirecUG.maxRange = 5;
    chanceToSurprise.sidedDie = 6;
    chanceToSurprise.maxRange = 4;
    chanceToSurprisePort.sidedDie = 6;
    chanceToSurprise.maxRange = 2;
    setDefenseBonus(inStats, defensiveBonus);
}

void Halfling::listRaceSkills()
{
    std::cout << "Detect Grade or Slope roll d" << (int)detectGrade.sidedDie << " succeeds: 1-" << (int)detectGrade.maxRange << std::endl;
    std::cout << "Determine direction of travel d" << (int)detDirecUG.sidedDie << " succeeds: 1-" << (int)detDirecUG.maxRange << std::endl;
    std::cout << "Chance to surprise creatures in a party of all Elves, or Elves and Halflings d" << (int)chanceToSurprise.sidedDie << " succeeds: 1-" << (int)chanceToSurprise.maxRange << std::endl;
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
    std::cout << "Defense against Wands, staves, rods and spells and poinson: +" << defensiveBonus << std::endl;
}

std::vector<std::string> Halfling::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (Halfling):");
    skillList.push_back("Detect Grade or Slope roll d" + std::to_string(detectGrade.sidedDie) + " succeeds: 1-" + std::to_string(detectGrade.maxRange));
    skillList.push_back("Determine direction of travel underground d" + std::to_string(detDirecUG.sidedDie) + " succeeds: 1-" + std::to_string(detDirecUG.maxRange));
    skillList.push_back("Chance to surprise creatures in a party of all Elves, or Elves and Halflings d" + std::to_string(chanceToSurprise.sidedDie) + " succeeds: 1-" + std::to_string(chanceToSurprise.maxRange));
    skillList.push_back("Infravision up to " + std::to_string(infraVision) +  "'");
    skillList.push_back("Defense against Wands, staves, rods and spells: +" + std::to_string(defensiveBonus));
    return skillList;
}

HalfOrc::HalfOrc(stats inStats)
{
    setRaceSkills(inStats);
}

HalfOrc::~HalfOrc()
{
    //std::cout << "Half-Orc Destructor Called." << std::endl;
}

void HalfOrc::setRaceSkills(stats inStats)
{

}

void HalfOrc::listRaceSkills()
{
    std::cout << "Infravision up to " << infraVision << " feet" << std::endl;
}

std::vector<std::string> HalfOrc::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (Half-Orc):");
    skillList.push_back("Infravision up to " + std::to_string(infraVision) +  "'");
    return skillList;
}

Human::Human(stats inStats)
{
    setRaceSkills(inStats);
}

Human::~Human()
{
    //std::cout << "Human Destructor Called." << std::endl;
}

void Human::setRaceSkills(stats inStats)
{

}

void Human::listRaceSkills()
{
    std::cout << "Humans have no bonus or penalty skills" << std::endl;
}

std::vector<std::string> Human::getRaceSkills()
{
    std::vector<std::string> skillList;
    skillList.push_back("Race Skills (Human):");
    skillList.push_back("Humans have no bonus or penalty skills");
    return skillList;
}