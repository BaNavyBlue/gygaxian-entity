/*
    Antone Bajor 2023
    Everything here is simply for 
    setting and reading values in the command line code.

    It also contains much of the logic handling for Sex,
    Aligment, Race and Char_Class constraints.

    The Termios library is used to switch to unbuffered character
    reads to respond to single key strokes quickly.
*/
//#include "entity.h"
#include "StatHelpers.h"
//#include <fstream>
// #include "entity.h"

std::string inputName()
{
    // OS Level Write to standard Out
    bool redo = false;
    std::string inputName;
    do{
        std::string message = "*****************************************************\r\nEnter Name: ";
        write(STD_OUT, message.c_str(), message.size());
        unsigned char inChar;
        do{
            //int bytes_read = read(STD_IN, &inChar, 1);
            inChar = getch();
            if(inChar > 0x1f && inChar < 0x80){
                if(inChar == 0x7f){
                    if(inputName.size() > 0){
                        // Clear deleted/backspace characters.
                        write(1, "\b \b", 4);
                        inputName.pop_back();
                    }
                } else {
                    if(inChar != '\r' && inChar != '\n'){
                        write(1, &inChar, 1);
                        inputName += (char)inChar;
                    }
                }
            } else {
                if(inChar == '\33'){

                inChar = getch();
                inChar = getch();
                inChar = 0;
                }
            }
        }while(inChar != '\r' && inChar != '\n' || inputName.size() < 1);
        std::cout << std::endl << std::endl;
        if(checkExists(inputName)){
            std::cout << "\r\nCharacter Already exists.\r\nOver-Write (y/n): ";
            redo = yesNoChoice();
            if(redo){
                inputName.clear();
            }
            std::cout << std::endl;
        } else {
            redo = false;
        }
    }while(redo);
    return inputName;
}

SEX inputSex()
{
    // OS Level Write to standard Out
    std::string message = "Choose Sex: \r\nFuta: 0 \r\nTrans: 1\r\nIntersex: 2\r\nFemale: 3\r\nMale: 4";
    write(STD_OUT, message.c_str(), message.size());
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < '5'){
                std::cout << std::endl;
                switch(inChar){
                    case '0':
                        return FUTA;
                    case '1':
                        return TRANS;
                    case '2':
                        return INTERSEX;
                    case '3':
                        return FEMALE;
                    case '4':
                        return MALE;
                }
            } else {
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
            }
        //} 
    }while(true);
    std::cout << std::endl;
}

RACE inputRace(stats inStats)
{
    // OS Level Write to standard Out
    //std::vector<std::string> races = {"Human: 0", "Elf: 1", "Half-Orc: 2", "Halfling: 3", "Dwarf: 4", "Half-Elf: 5", "Gnome: 6"};
    std::string message = "\r\nSelect Race: \r\n";
    std::string nonViable = "\r\nNon-Viable Races: \r\n";
    std::unordered_map<char, RACE> rList;
    char idx = '0';
    int nonV = 0;
    for(int i = 0; i < racePairs.size(); ++i){
        if(raceStatCheck(inStats, racePairs[i].race)){
            rList[idx] = racePairs[i].race;
            message += racePairs[i].raceS + ": " + idx + "\r\n";
            idx++;         
        } else {
            nonViable += racePairs[i].raceS + "\r\n";
            nonV++;
        }
    }

    if(nonV){
        write(STD_OUT, nonViable.c_str(), nonViable.size());
    }

    write(STD_OUT, message.c_str(), message.size());
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < idx){
                std::cout << std::endl;
                return rList[inChar];
            } else {
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
            }
        //} 
    }while(true);
}

ALIGNMENT inputAlign()
{
    // OS Level Write to standard Out
    //std::vector<std::string> races = {"Human: 0", "Elf: 1", "Half-Orc: 2", "Halfling: 3", "Dwarf: 4", "Half-Elf: 5", "Gnome: 6"};
    //std::vector<racePair> racePairs = {{HUMAN, "Human"}, {ELF, "Elf"}, {HALF_ORC, "Half-Orc"}, {DWARF, "Dwarf"}, {HALFLING, "Halfling"}, {HALF_ELF, "Half-Elf"}, {GNOME, "Gnome"}};
    std::string message = "\r\nSelect Alignment: \r\n";
    std::string nonViable = "\r\nNon-Viable Races: \r\n";
    std::unordered_map<char, ALIGNMENT> aList;
    char idx = '0';
    //int nonV = 0;
    for(int i = 0; i < alignPairs.size(); ++i){
            aList[idx] = alignPairs[i].align;
            message += alignPairs[i].alignS + ": " + idx + ", Compatible Classes: " + alignClasses(alignPairs[i].align) + "\r\n";
            idx++;         
    }

    write(STD_OUT, message.c_str(), message.size());
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < idx){
                std::cout << std::endl;
                return aList[inChar];
            } else {
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
            }
        //} 
    }while(true);   
}

CHAR_CLASS inputClass(RACE race, stats inStats, ALIGNMENT align)
{
    std::string message = "\r\nSelect Class: \r\n";
    std::string nonViable = "\r\nNon-Viable Classes: \r\n";
    std::unordered_map<char, CHAR_CLASS> cList;
    char idx = '0';
    int nonV = 0;
    for(int i = 0; i < classPairs.size(); ++i){
        if(classRaceCheck(classPairs[i].cClass, race, align) && classStatCheck(classPairs[i].cClass, inStats)){
            cList[idx] = classPairs[i].cClass;
            message += classPairs[i].cS + ": " + idx + "\r\n";
            idx++;         
        } else {
            nonViable += classPairs[i].cS + "\r\n";
            nonV++;
        }
    }

    if(nonV){
        write(STD_OUT, nonViable.c_str(), nonViable.size());
    }

    write(STD_OUT, message.c_str(), message.size());
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < idx){
                std::cout << std::endl;
                return cList[inChar];
            } else {
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
            }
        //} 
    }while(true);    
}

void printSex(SEX sex)
{
    std::cout << "Sex: ";
    switch(sex){
        case FUTA:
            std::cout << "Futa." << std::endl;
            break;
        case TRANS:
            std::cout << "Trans." << std::endl;
            break;
        case INTERSEX:
            std::cout << "InterSex." << std::endl;
            break;
        case FEMALE:
            std::cout << "Female." << std::endl;
            break;
        case MALE:
            std::cout << "Male." << std::endl;
            break;
    }
}

void printStats(stats inStats)
{
    std::cout << std::endl << "Strength: " << inStats.strength << std::endl;
    if(inStats.strength > 17 && inStats.excStren > 0){
        std::cout << "Exceptional Strength: " << inStats.excStren << " Fighter Paladin or Ranger only!" << std::endl;
    }
    std::cout << "Intelligence: " << inStats.intellignece << std::endl;
    std::cout << "Wisdom: " << inStats.wisdom << std::endl;
    std::cout << "Charisma: " << inStats.charisma << std::endl;
    std::cout << "Dexterity: " << inStats.dexterity << std::endl;
    std::cout << "Constitution: " << inStats.constitution << std::endl;
}

void printStatsFails(stats inStats)
{
    std::string chkFails;
    std::cout << std::endl << "Strength: " << inStats.strength;
    chkFails = strenFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
    if(inStats.strength > 17){
        std::cout << "Exceptional Strength: " << inStats.excStren << " Fighter Paladin or Ranger only!" << std::endl;
    }
    std::cout << "Intelligence: " << inStats.intellignece;
    chkFails = intFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
    std::cout << "Wisdom: " << inStats.wisdom;
    chkFails = wisFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
    std::cout << "Charisma: " << inStats.charisma;
    chkFails = charisFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
    std::cout << "Dexterity: " << inStats.dexterity;
    chkFails = dexFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
    std::cout << "Constitution: " << inStats.constitution;
    chkFails = consFails(inStats);
    if(chkFails.size()){
        std::cout << ", Fails: " << chkFails << std::endl;
        chkFails.clear();
    } else {
        std::cout << std::endl;
    }
}

bool reRoll()
{
    std::cout << std::endl << "Would you like to keep stats? y/n: ";
    char choice;

    do{
        choice = getch();
        choice = std::tolower(choice);
    }while(choice != 'y' && choice != 'n');

    std::cout << std::endl;

    if(choice == 'y'){
        return false;
    } else {
        return true;
    }
}

void printRace(RACE race){
    std::cout << "Race: ";
    switch(race){
        case HUMAN:
            std::cout << "Human" << std::endl;
            break;
        case ELF:
            std::cout << "Elf" << std::endl;
            break;
        case HALF_ORC:
            std::cout << "Half-Orc" << std::endl;
            break;
        case DWARF:
            std::cout << "Dwarf" << std::endl;
            break;
        case HALFLING:
            std::cout << "Halfling" << std::endl;
            break;
        case HALF_ELF:
            std::cout << "Half-Elf" << std::endl;
            break;
        case GNOME:
            std::cout << "Gnome" << std::endl;
            break;
    }
}

void printStrTbl(strengthTable strTbl)
{
    std::cout << "\r\nStrength Table:" << std::endl;
    std::cout << "Hit Probability: " << strTbl.hitProb << std::endl;
    std::cout << "Damage Adjustment: " << strTbl.damageAdj << std::endl;
    std::cout << "Weight Allowance Modification: " << strTbl.weightAllowMod << std::endl;
    std::cout << "Open Doors: " << strTbl.openDoors << std::endl;
    std::cout << "Bend Bars / Lift Gates: " << strTbl.bendBarsLiftGatesPer << '%' << std::endl;
}

void printIntTbl(inteligenceTable intTbl)
{
    std::cout << "\r\nIntelligence Table:" << std::endl;
    std::cout << "Chance to Know each Listed Spell: " << intTbl.chanceToKnowPer << '%' << std::endl;
    std::cout << "Minimum Number of Spells per Level: " << intTbl.minumumSpellsPerLevel << std::endl;
    std::cout << "Maximum Number of Spells per Level: " << intTbl.maxiumSpellsPerlevel << std::endl;
    std::cout << "Possible Number of Additional Languages: " << intTbl.possibAddLang << std::endl;
}

void printWisTbl(wisdomTable wisTbl)
{
    std::cout << "\r\nWisdom Table:" << std::endl;
    std::cout << "Magic Attack Adjustment: " << wisTbl.magicAttackAdj << std::endl;
    std::cout << "Spell bonus (1 for each level under shown level): " << wisTbl.spellBonus << std::endl;
    std::cout << "Chance for Spell Failure: " << wisTbl.spellFailPer << '%' << std::endl;
}

void printDexTbl(dexterityTable dexTbl)
{
    std::cout << "\r\nDexterity Table:" << std::endl;
    std::cout << "Reaction/Attacking Adjustment: " << dexTbl.reactAttkAdj << std::endl;
    std::cout << "Defensive Adjustment: " << dexTbl.defenseAdj << std::endl;
}

void printDexThief(dexThieves dexThief)
{
    std::cout << "\r\nThieves Dexterity Table:" << std::endl;
    std::cout << "Picking Pockets: " << dexThief.pickPocketPer << '%' << std::endl;
    std::cout << "Opening Locks: " << dexThief.openLocks << '%' << std::endl;
    std::cout << "Locating/Removing Traps: " << dexThief.locRemTraps << '%' << std::endl;
    std::cout << "Moving Silently: " << dexThief.movSilent << '%' << std::endl;
    std::cout << "Hiding In Shadows: " << dexThief.hideInShadows << '%' << std::endl;
}

void printConsTbl(constitutionTable consTbl)
{
    std::cout << "\r\nConstitution Table:" << std::endl;
    std::cout << "Hit Point Adjustment: " << consTbl.hpAdj << std::endl;
    std::cout << "System Shock Survivial: " << consTbl.sysShockSurPer << '%' << std::endl;
    std::cout << "Resurection Survival: " << consTbl.resurSurvPer << '%' << std::endl;
}

bool raceStatCheck(stats inStats, RACE race)
{
    switch(race){
        case HUMAN:
            return true;
        case ELF:
            if(inStats.intellignece < 8){
                //std::cout << "Elf can not have intelligence bellow 8" << std::endl;
                return false;
            }
            if(inStats.dexterity + 1 < 7){
                //std::cout << "Elf can not have dexterity bellow 7" << std::endl;
                return false;
            }
            if(inStats.constitution - 1 < 6){
                //std::cout << "Elf can not have constitution bellow 6" << std::endl;
                return false;
            }
            if(inStats.charisma < 8){
                //std::cout << "Elf can not have charisma bellow 8" << std::endl;
                return false;
            }
            return true;
        case HALF_ORC:
            if(inStats.strength + 1 < 6){
                //std::cout << "Half-Orc Strength bellow 6" << std::endl;
                return false;
            }

            if(inStats.constitution + 1 < 13){
                //std::cout << "Half-Orc constitution bellow 13" << std::endl;
                return false;
            }
            return true;
        case DWARF:
            if(inStats.strength < 8){
                //std::cout << "Dwarf strength bellow 8" << std::endl;
                return false;            
            }

            if(inStats.constitution + 1 < 12){
                //std::cout << "Dwarf constitution bellow 12" << std::endl;
                return false;            
            }
            return true;
        case HALFLING:
            if(inStats.strength - 1 < 6){
                //std::cout << "Halfling strength bellow 6" << std::endl;
                return false;                  
            }

            if(inStats.intellignece < 6){
                //std::cout << "Halfling intelligence bellow 6" << std::endl;
                return false;                
            }

            if(inStats.dexterity + 1 < 8){
                //std::cout << "Halfling dexterity bellow 8" << std::endl;
                return false;
            }

            if(inStats.constitution < 10){
                //std::cout << "Halfling constitution bellow 10" << std::endl;
                return false;
            }
            return true;
        case HALF_ELF:
           if(inStats.intellignece < 4){
                //std::cout << "Intelligence bellow 4" << std::endl;
                return false;
            }

            if(inStats.dexterity < 6){
                //std::cout << "Dexterity bellow 6" << std::endl;
                return false;
            }

            if(inStats.constitution < 6){
                //std::cout << "Constitution bellow 6" << std::endl;
                return false;
            }
            return true;
        case GNOME:
            if(inStats.strength < 6){
                //std::cout << "Strength bellow 6" << std::endl;
                return false;
            }

            if(inStats.intellignece < 7){
                //std::cout << "Intelligence bellow 7" << std::endl;
                return false;
            }

            if(inStats.constitution < 8){
                //std::cout << "Constitution bellow 8" << std::endl;
                return false;
            }
            return true;
    }
}

bool classRaceCheck(CHAR_CLASS cClass, RACE race, ALIGNMENT align)
{
    switch(cClass){
        case CLERIC:
            if(align == TRUE_NEUTRAL){
                return false;
            }
            if(race == HALF_ELF || race == HALF_ORC || race == HUMAN){
                return true;
            }
            return false;
        case DRUID:
            if(align != NEUTRAL_EVIL && align != NEUTRAL_GOOD && align != TRUE_NEUTRAL){
                return false;
            }
            if(race == HALF_ELF || race == HUMAN){
                return true;
            }
            return false;
        case FIGHTER:
            return true;
        case PALADIN:
            if(align != LAWFUL_GOOD){
                return false;
            }
            if(race == HUMAN){
                return true;
            }
            return false;
        case RANGER:
            if(align != CHAOTIC_GOOD && align != NEUTRAL_GOOD && align != LAWFUL_GOOD){
                return false;
            }
            if(race == HALF_ELF || race == HUMAN){
                return true;
            }
            return false;
        case MAGIC_USER:
            if(race == ELF || race == HALF_ELF || race == HUMAN){
                return true;
            }
            return false;
        case ILLUSIONIST:
            if(race == GNOME || race == HUMAN){
                return true;
            }
            return false;
        case THIEF:
            if(align == CHAOTIC_GOOD || align == LAWFUL_GOOD){
                return false;
            }
            return true;
        case ASSASSIN:
            if(align != LAWFUL_EVIL && align != NEUTRAL_EVIL && align != CHAOTIC_EVIL ){
                return false;
            }
            if(race == HALFLING){
                return false;
            }
            return true;
        case MONK:
            if(align != LAWFUL_EVIL && align != LAWFUL_NEUTRAL && align != LAWFUL_GOOD){
                return false;
            }
            if(race == HUMAN){
                return true;
            }
            return false;
        default:
            return false;
    }
}

bool classStatCheck(CHAR_CLASS cClass, stats inStats)
{
    switch(cClass){
        case CLERIC:
            if(inStats.strength < 5){
                return false;
            }
            if(inStats.intellignece < 5){
                return false;
            }
            if(inStats.wisdom < 9){
                return false;
            }
            if(inStats.constitution < 5){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;
        case DRUID:
            if(inStats.strength < 5){
                return false;
            }
            if(inStats.intellignece < 5){
                return false;
            }
            if(inStats.wisdom < 12){
                return false;
            }
            if(inStats.dexterity < 5){
                return false;
            }
            if(inStats.constitution < 5){
                return false;
            }
            if(inStats.charisma < 15){
                return false;
            }
            return true;
        case FIGHTER:
            if(inStats.strength < 9){
                return false;
            }
            if(inStats.wisdom < 5){
                return false;
            }
            if(inStats.dexterity < 5){
                return false;
            }
            if(inStats.constitution < 7){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;
        case PALADIN:
            if(inStats.strength < 12){
                return false;
            }
            if(inStats.intellignece < 9){
                return false;
            }
            if(inStats.wisdom < 13){
                return false;
            }
            if(inStats.dexterity < 5){
                return false;
            }
            if(inStats.constitution < 9){
                return false;
            }
            if(inStats.charisma < 17){
                return false;
            }
            return true;
        case RANGER:
            if(inStats.strength < 13){
                return false;
            }
            if(inStats.intellignece < 5){
                return false;
            }
            if(inStats.wisdom < 14){
                return false;
            }
            if(inStats.dexterity < 5){
                return false;
            }
            if(inStats.constitution < 14){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;
        case MAGIC_USER:
            if(inStats.intellignece < 9){
                return false;
            }
            if(inStats.wisdom < 5){
                return false;
            }
            if(inStats.dexterity < 6){
                return false;
            }
            if(inStats.constitution < 5){
                return false;
            }
            return true;
        case ILLUSIONIST:
            if(inStats.strength < 5){
                return false;
            }
            if(inStats.intellignece < 15){
                return false;
            }
            if(inStats.wisdom < 5){
                return false;
            }
            if(inStats.dexterity < 16){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;
        case THIEF:
            if(inStats.strength < 5){
                return false;
            }
            if(inStats.intellignece < 5){
                return false;
            }
            if(inStats.dexterity < 9){
                return false;
            }
            if(inStats.constitution < 5){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;
        case ASSASSIN:
            if(inStats.strength < 12){
                return false;
            }
            if(inStats.intellignece < 11){
                return false;
            }
            if(inStats.wisdom < 5){
                return false;
            }
            if(inStats.dexterity < 12){
                return false;
            }
            if(inStats.constitution < 5){
                return false;
            }
            return true;
        case MONK:
            if(inStats.strength < 15){
                return false;
            }
            if(inStats.intellignece < 5){
                return false;
            }
            if(inStats.wisdom < 15){
                return false;
            }
            if(inStats.dexterity < 15){
                return false;
            }
            if(inStats.constitution < 11){
                return false;
            }
            if(inStats.charisma < 5){
                return false;
            }
            return true;

    }
}

bool checkExists(std::string name)
{
    std::string file = "characters/" + name + ".json";
    std::ifstream charJson(file);
    return charJson.good();

}

bool yesNoChoice()
{
char choice;

    do{
        choice = getche();
        choice = std::tolower(choice);
    }while(choice != 'y' && choice != 'n');

    std::cout << std::endl;

    if(choice == 'y'){
        return false;
    } else {
        return true;
    }   
}

void printAlign(ALIGNMENT align)
{
    std::unordered_map<ALIGNMENT, std::string> aMap;
    for(int i = 0; i < alignPairs.size(); ++i){
        aMap[alignPairs[i].align] = alignPairs[i].alignS;
    }
    std::cout << "Alignment: " << aMap[align] << std::endl;
}

void printClass(CHAR_CLASS cClass)
{
    std::unordered_map<CHAR_CLASS, std::string> cMap;
    for(int i = 0; i < classPairs.size(); ++i){
        cMap[classPairs[i].cClass] = classPairs[i].cS;
    }
    std::cout << "Class: " << cMap[cClass] << std::endl;   
}

std::string strenFails(stats inStats)
{   
    std::string failures;
    switch(inStats.strength){
        case 3:
        case 4:
            // Strength +1 Half-Orc
            failures += "Halfling Gnome Half-Orc Dwarf and all classes but Magic-User ";
            return failures;
        case 5:
            failures += "Gnome ";
        case 6:
            failures += "HalfLing "; // Strength -1 Halfling
        case 7:
            failures += "Dwarf ";
        case 8: 
            failures += "Fighter ";
        case 9:
        case 10:
        case 11:
            failures += "Assassin Paladin ";
        case 12:
            failures += "Ranger ";
        case 13:
        case 14:
            failures += "Monk ";
    }
    return failures;
}

std::string intFails(stats inStats)
{   
    std::string failures;
    switch(inStats.intellignece){
        case 3:
            failures += "Half-Elf ";
        case 4:
            // Strength +1 Half-Orc
            failures += "Halfling Gnome Elf and all classes but Fighter ";
            return failures;
        case 5:
            failures += "Halfling ";
        case 6:
            failures += "Gnome ";
        case 7:
            failures += "Elf ";
        case 8: 
            failures += "Paladin Magic-User ";
        case 9:
        case 10:
        case 11:
            failures += "Assassin ";
        case 12:
        case 13:
        case 14:
            failures += "Illusionist ";
    }
    return failures;
}

std::string wisFails(stats inStats)
{   
    std::string failures;
    switch(inStats.wisdom){
        case 3:
        case 4:
            // Strength +1 Half-Orc
            failures += "All classes but Thief ";
            return failures;
        case 5:
        case 6:
        case 7:
        case 8: 
            failures += "Cleric ";
        case 9:
        case 10:
        case 11:
            failures += "Druid ";
        case 12:
            failures += "Paladin \"MultiClass Half-Elf Cleric\" ";
        case 13:
            failures += "Ranger ";
        case 14:
            failures += "Monk ";
    }
    return failures;
}

std::string dexFails(stats inStats)
{   
    std::string failures;
    switch(inStats.dexterity){
        case 3:
        case 4:
            failures += "Half-Elf Elf Halfling and all classes but Cleric ";
            return failures;
        case 5:
            // Elf dex + 1
            failures += "Half-Elf Elf Magic-User";
        case 6:
            // Halfling dex + 1
            failures += "Halfling ";
        case 7:
        case 8: 
            failures += "Thief ";
        case 9:
        case 10:
        case 11:
            failures += "Assassin ";
        case 12:
        case 13:
        case 14:
            failures += "Monk ";
        case 15:
            failures += "Illusionist ";
    }
    return failures;
}

std::string consFails(stats inStats)
{   
    std::string failures;
    switch(inStats.constitution){
        case 3:
        case 4:
        case 5:
            failures += "Half-Elf Halfling Gnome Dwarf Half-Orc and all classes but Illusionist ";
            return failures;
        case 6:
            // Elf constitution - 1
            failures += "Elf Fighter ";
        case 7:
            failures += "Gnome ";
        case 8: 
            failures += "Paladin ";
        case 9:
            failures += "Halfling ";
        case 10:
            // Dwarf const + 1
            failures += "Monk Dwarf ";
        case 11:
            // Half-Orc const + 1
            failures += "Half-Orc ";
        case 12:
        case 13:
            failures += "Ranger ";
    }
    return failures;
}

std::string charisFails(stats inStats)
{   
    std::string failures;
    switch(inStats.charisma){
        case 3:
        case 4:
        case 5:
            failures += "Elf and all classes but Assassin ";
            return failures;
        case 6:
        case 7:
        case 8: 
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            failures += "Druid ";
        case 15:
        case 16:
            failures += "Paladin ";

    }
    return failures;
}

std::string alignClasses(ALIGNMENT align)
{
    std::string compat;
    switch(align){
        case CHAOTIC_EVIL:
            compat += "Clrc, Fght, Mage, Illu, Thf, Assas.";
            break;
        case CHAOTIC_GOOD:
            compat += "Clrc, Fght, Rngr, Mage, Illu.";
            break;
        case CHAOTIC_NEUTRAL:
            compat += "Clrc, Druid, Fght, Mage, Illu, Thf.";
            break;
        case LAWFUL_EVIL:
            compat += "Clrc, Fght, Mage, Illu, Thf, Assas, Monk.";
            break;
        case LAWFUL_GOOD:
            compat += "Clrc, Fght, Pldn, Rngr, Mage, Illu, Monk.";
            break;
        case LAWFUL_NEUTRAL:
            compat += "Clrc, Druid, Fght, Mage, Illu, Thf, Monk.";
            break;
        case NEUTRAL_EVIL:
            compat += "Clrc, Druid, Fght, Mage, Illu, Thf, Assas.";
            break;
        case NEUTRAL_GOOD:
            compat += "Clrc, Druid, Fght, Rngr, Mage, Illus, Thf.";
            break;
        case TRUE_NEUTRAL:
            compat += "Clrc, Druid, Fght, Mage, Illu, Thf.";
            break;
        default:
            return compat;
    }
    return compat;
}

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

/* Read 1 character with echo */
char getche(void) 
{
  return getch_(1);
}