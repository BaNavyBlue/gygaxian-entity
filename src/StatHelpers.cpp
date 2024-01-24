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

// Stat Dice Helper Function best 3 out of 4
unsigned bestThree(){
    std::vector<unsigned> rolls;
    int min_idx = 0;
    for(int i = 0; i < 4; ++i){
        rolls.push_back(rollDice(6, false));
    }
    unsigned min_val = rolls[0];
    for(int i = 1; i < 4; ++i){
        if(rolls[i] < min_val){min_idx = i;}
    }
    unsigned final_val = 0;
    for(int i = 0; i < 4; ++i){
        if(i != min_idx){
            final_val += rolls[i];
        }
    }
    return final_val;
}

void rollStats(stats& _stats, stats& _modStats)
{
    do{
        _stats.strength = _modStats.strength = bestThree();
        if(_stats.strength > 17){
            _stats.excStren = _modStats.excStren = rollDice(10, true) + rollDice(10, true)*10 + 1;
        }
        _stats.intelligence = _modStats.intelligence = bestThree();
        _stats.wisdom = _modStats.wisdom = bestThree();
        _stats.charisma = _stats.raceCharisma = _modStats.charisma = _modStats.raceCharisma = bestThree();
        _stats.dexterity = _modStats.dexterity = bestThree();
        _stats.constitution = _modStats.constitution = bestThree();
    }while(!rollFailure(_stats, false));
}

std::string inputName()
{
    // OS Level Write to standard Out
    bool redo = false;
    std::string inputName;
    do{
        std::string message = "*****************************************************\r\nEnter Name: ";
#ifndef _WIN32
        write(STD_OUT, message.c_str(), message.size());
#endif 
        unsigned char inChar;
        do{
            //int bytes_read = read(STD_IN, &inChar, 1);
            inChar = getch();
            if(inChar > 0x1f && inChar < 0x80){
                if(inChar == 0x7f){
                    if(inputName.size() > 0){
                        // Clear deleted/backspace characters.
#ifndef _WIN32
                        write(1, "\b \b", 4);
#endif 
                        inputName.pop_back();
                    }
                } else {
                    if(inChar != '\r' && inChar != '\n'){
#ifndef _WIN32
                        write(1, &inChar, 1);
#endif 
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
        }while((inChar != '\r' && inChar != '\n') || inputName.size() < 1);
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
    std::string message = "Choose Sex: \r\nFuta: 0 \r\nIntersex: 1\r\nFemale: 2\r\nMale: 3";
#ifndef _WIN32 
    write(STD_OUT, message.c_str(), message.size());
#endif
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
                        return INTERSEX;
                    case '2':
                        return FEMALE;
                    case '3':
                        return MALE;
                }
            } else {
#ifndef _WIN32 
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
#endif
            }
        //} 
    }while(true);
    std::cout << std::endl;
}

RACE inputRace(stats inStats, std::vector<std::string>& viable, std::vector<std::string>& nonViable)
{
    // OS Level Write to standard Out
    //std::vector<std::string> races = {"Human: 0", "Elf: 1", "Half-Orc: 2", "Halfling: 3", "Dwarf: 4", "Half-Elf: 5", "Gnome: 6"};
    viable.push_back("Select Race:");
    nonViable.push_back("Non-Viable Races:");
    std::unordered_map<char, RACE> rMap;
    char idx = '0';
    int nonV = 0;
    for(unsigned i = 0; i < racePairs.size(); ++i){
        if(raceStatCheck(inStats, racePairs[i].race)/*&&checkRaceStats(racePairs[i].race, inStats)*/){
            rMap[idx] = racePairs[i].race;
            viable.push_back(racePairs[i].raceS + ": " + idx);
            idx++;         
        } else {
            nonViable.push_back(racePairs[i].raceS);
            nonV++;
        }
    }

    //if(nonV){
    //    write(STD_OUT, nonViable.c_str(), nonViable.size());
    //}

    //write(STD_OUT, message.c_str(), message.size());
    // unsigned char inChar;
    // do{
    //     inChar = getch_n();
    //     //int bytes_read = read(STD_IN, &inChar, 1);
    //     //if(bytes_read > 0){
    //         if(inChar >= '0' && inChar < idx){
    //             std::cout << std::endl;
    //             return rMap[inChar];
    //         } //else {
    //         //    write(STD_OUT, "Invalid Selection\r\n",20);
    //         //    write(STD_OUT, message.c_str(), message.size());
    //        // }
    //     //} 
    // }while(true);
    return HUMAN;
}

// A Viability Hack to prevent a race that can't select a class
// Thank you Gary
stats checkRaceStats(RACE race, stats _stats)
{
    // stat changes aren't applied just using for checks
    switch(race){
        // check for failures before adding race bonus's
        case HUMAN:
            // Check Stat Limitation.
            return _stats;
        case ELF:
            // Stat Limitation Check
            // if(_stats.dexterity + 1 < 7){
            //     std::cout << "Elf can not have dexterity bellow 7" << std::endl;
            //     return false;
            // }
            // if(_stats.constitution - 1 < 6){
            //     std::cout << "Elf can not have constitution bellow 6" << std::endl;
            //     return false;
            // }
            // Apply Standard Elf Modifiers
            _stats.constitution--;
            _stats.dexterity++;
            return _stats;
        case HALF_ORC:
            // if(_stats.strength + 1 < 6){
            //     std::cout << "Half-Orc Strength bellow 6" << std::endl;
            //     return false;
            // }

            // if(_stats.constitution + 1 < 13){
            //     std::cout << "Half-Orc constitution bellow 13" << std::endl;
            //     return false;
            // }

            if(_stats.charisma - 2 > 12){
                std::cout << "Half-Orc Charisma being set to cap 12" << std::endl;
                _stats.charisma = 12;
            } else if(_stats.charisma - 2 < 3) {
                std::cout << "Half-Orc Charisma minimum being set to 3" << std::endl;
                _stats.charisma = 3;            
            } else {
                _stats.charisma -= 2;
            }

            if(_stats.strength + 1 > 18){
                std::cout << "Half-Orc strength set to cap 18" << std::endl;
                _stats.strength = 18;
            } else {
                _stats.strength++;
            }

            _stats.constitution++;
            return _stats;
        case DWARF:
            // if(_stats.constitution + 1 < 12){
            //     std::cout << "Dwarf constitution bellow 12" << std::endl;
            //     return false;            
            // }

            // if(_stats.strength < 8){
            //     std::cout << "Dwarf strength bellow 8" << std::endl;
            //     return false;            
            // }

            // if(_stats.dexterity < 6){
            //     std::cout << "Dwarf dexterity bellow 6 Cleric Case" << std::endl;
            //     return false;            
            // }

            if(_stats.charisma - 1 > 16){
                std::cout << "Dwarf charisma cap 16" << std::endl;
                _stats.charisma = 16;
            } else {
                _stats.charisma--;
            }

            _stats.constitution++;
            return _stats;
        case HALFLING:
            // if(_stats.strength - 1 < 6){
            //     std::cout << "Halfling strength bellow 6 Magic-User Case" << std::endl;
            //     return false;                  
            // }

            // if(_stats.dexterity + 1 < 8){
            //     std::cout << "Halfling dexterity bellow 8 Cleric Case" << std::endl;
            //     return false;
            // }

            // if(_stats.constitution < 6){
            //     std::cout << "Halfling constititon bellow 6 Illusionist Case" << std::endl;
            //     return false;                  
            // }

            // if(_stats.charisma - 1 < 6){
            //     std::cout << "Halfling charisma bellow 6 Assassin Case" << std::endl;
            //     return false;                  
            // }

            _stats.strength--;
            _stats.dexterity++;

            return _stats;
        case HALF_ELF:
            // if(_stats.constitution < 6){
            //     std::cout << "Constitution bellow 6 Illusionist Only Case" << std::endl;
            //     return false;
            // }
            return _stats;
        case GNOME:
            // if(_stats.strength < 6){
            //     std::cout << "Strength bellow 6 magic user only case" << std::endl;
            //     return false;
            // }
            // if(_stats.dexterity < 6){
            //     std::cout << "Dexterity bellow 6 cleric only case" << std::endl;
            //     return false;
            // }
            return _stats;
        default:
            return _stats;
    }
}

ALIGNMENT inputAlign(CHAR_CLASS inClass)
{
    // OS Level Write to standard Out
    //std::vector<std::string> races = {"Human: 0", "Elf: 1", "Half-Orc: 2", "Halfling: 3", "Dwarf: 4", "Half-Elf: 5", "Gnome: 6"};
    //std::vector<racePair> racePairs = {{HUMAN, "Human"}, {ELF, "Elf"}, {HALF_ORC, "Half-Orc"}, {DWARF, "Dwarf"}, {HALFLING, "Halfling"}, {HALF_ELF, "Half-Elf"}, {GNOME, "Gnome"}};
    std::string message = "\r\nSelect Alignment: \r\n";
    std::unordered_map<char, ALIGNMENT> aList;
    char idx = '0';
    //int nonV = 0;
    for(unsigned i = 0; i < alignPairs.size(); ++i){
            if(alignClassCheck(inClass, alignPairs[i].align)){
                aList[idx] = alignPairs[i].align;
                message += alignPairs[i].alignS + ": " + idx + "\r\n";
                idx++;
            }         
    }
#ifndef _WIN32
    write(STD_OUT, message.c_str(), message.size());
#endif
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < idx){
                std::cout << std::endl;
                return aList[inChar];
            } else {
#ifndef _WIN32
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
#endif
            }
        //} 
    }while(true);   
}

CHAR_CLASS inputClass(RACE race, stats inStats)
{
    std::string message = "\r\nSelect Class: \r\n";
    std::string nonViable = "\r\nNon-Viable Classes: \r\n";
    std::unordered_map<char, CHAR_CLASS> cList;
    char idx = '0';
    int nonV = 0;
    inStats = checkRaceStats(race, inStats); // Fix that race stat mods aren't taken into class consideration;
    for(unsigned i = 0; i < classPairs.size(); ++i){
        if(classRaceCheck(classPairs[i].cClass, race) && classStatCheck(classPairs[i].cClass, inStats)){
            cList[idx] = classPairs[i].cClass;
            message += classPairs[i].cS + ": " + idx + "\r\n";
            idx++;         
        } else {
            nonViable += classPairs[i].cS + "\r\n";
            nonV++;
        }
    }

    if(nonV){
#ifndef _WIN32
        write(STD_OUT, nonViable.c_str(), nonViable.size());
#endif
    }
#ifndef _WIN32
    write(STD_OUT, message.c_str(), message.size());
#endif
    unsigned char inChar;
    do{
        inChar = getch();
        //int bytes_read = read(STD_IN, &inChar, 1);
        //if(bytes_read > 0){
            if(inChar >= '0' && inChar < idx){
                std::cout << std::endl;
                return cList[inChar];
            } else {
#ifndef _WIN32
                write(STD_OUT, "Invalid Selection\r\n",20);
                write(STD_OUT, message.c_str(), message.size());
#endif
            }
        //} 
    }while(true);    
}

void printSex(SEX sex)
{
    //std::cout << "Sex: ";
    switch(sex){
        case FUTA:
            std::cout << "Futa." << std::endl;
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

std::string getSex(SEX sex)
{
    //std::cout << "Sex: ";
    switch(sex){
        case FUTA:
            return "Futa";
        case INTERSEX:
            return "InterSex";
        case FEMALE:
            return "Female";
        case MALE:
            return "Male";
    }
}

void printStats(stats inStats)
{
    std::cout << std::endl << "Strength: " << inStats.strength << std::endl;
    if(inStats.strength > 17 && inStats.excStren > 0){
        std::cout << "Exceptional Strength: " << inStats.excStren << " Fighter Paladin or Ranger only!" << std::endl;
    }
    std::cout << "Intelligence: " << inStats.intelligence << std::endl;
    std::cout << "Wisdom: " << inStats.wisdom << std::endl;
    std::cout << "Charisma: " << inStats.charisma << std::endl;
    std::cout << "Charisma to ones own race: " << inStats.raceCharisma << std::endl;
    std::cout << "Dexterity: " << inStats.dexterity << std::endl;
    std::cout << "Constitution: " << inStats.constitution << std::endl;
}

std::vector<std::string> getStats(stats inStats, CHAR_CLASS inClass, RACE inRace)
{
    std::vector<std::string> returnVect;
    char statVal[5]; 
    returnVect.push_back("Stats:");
    sprintf(statVal, "%3.d", inStats.strength);
    returnVect.push_back("Strength: ");
    returnVect.back() += statVal;

    if(inClass == FIGHTER || inClass == PALADIN || inClass == RANGER){
        if(inStats.strength > 17 && inStats.excStren > 0){
            sprintf(statVal, "%3.d", inStats.excStren);
            returnVect.push_back("Exceptional Strength: ");
            returnVect.back() += statVal;
        }
    }

    sprintf(statVal, "%3.d", inStats.intelligence);
    returnVect.push_back("Intelligence: ");
    returnVect.back() += statVal;

    sprintf(statVal, "%3.d", inStats.wisdom);
    returnVect.push_back("Wisdom: ");
    returnVect.back() += statVal;

    sprintf(statVal, "%3.d", inStats.dexterity);
    returnVect.push_back("Dexterity: ");
    returnVect.back() += statVal;

    sprintf(statVal, "%3.d", inStats.charisma);
    returnVect.push_back("Charisma: ");
    returnVect.back() += statVal;
    if(inRace == DWARF || inRace == HALF_ORC){
        sprintf(statVal, "%3.d", inStats.raceCharisma);
        returnVect.back() += "(*";
        returnVect.back() += statVal;
        returnVect.back() += ")";
    }

    sprintf(statVal, "%3.d", inStats.constitution);
    returnVect.push_back("Constitution: ");
    returnVect.back() += statVal;
    
    if(inRace == DWARF || inRace == HALF_ORC){
        returnVect.push_back("* To one's own race");
    }

    return returnVect;
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
    std::cout << "Intelligence: " << inStats.intelligence;
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
    //std::cout << std::endl << "Would you like to keep stats? y/n: ";
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

std::string getRace(RACE inRace)
{
    switch(inRace){
        case HUMAN:
            return "Human";
        case ELF:
            return "Elf";
        case HALF_ORC:
            return "Half-Orc";
        case DWARF:
            return "Dwarf";
        case HALFLING:
            return "Halfling";
        case HALF_ELF:
            return "Half-Elf";
        case GNOME:
            return "Gnome";
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

void printIntTbl(intelligenceTable intTbl)
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

std::vector<std::string> getDexTheif(dexThieves dexThief)
{
    std::vector<std::string> basicList;
    basicList.push_back("Thieves Dexterity Table:");
    basicList.push_back("Picking Pockets: " + std::to_string(dexThief.pickPocketPer) + " prcnt");
    basicList.push_back("Opening Locks: " + std::to_string(dexThief.openLocks) + " prcnt");
    basicList.push_back("Locating/Removing Traps: " + std::to_string(dexThief.locRemTraps) + " prcnt");
    basicList.push_back("Moving Silently: " + std::to_string(dexThief.movSilent) + " prcnt");
    basicList.push_back("Hiding In Shadows: " + std::to_string(dexThief.hideInShadows) + " prcnt");
    return basicList;    
}

void printConsTbl(constitutionTable consTbl)
{
    std::cout << "\r\nConstitution Table:" << std::endl;
    std::cout << "Hit Point Adjustment: " << consTbl.hpAdj << std::endl;
    std::cout << "System Shock Survivial: " << consTbl.sysShockSurPer << '%' << std::endl;
    std::cout << "Resurection Survival: " << consTbl.resurSurvPer << '%' << std::endl;
}

std::vector<std::string> getConsTbl(constitutionTable consTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Constitution Table:");
    basicInfo.push_back("Hit Point Adjustment: " + std::to_string(consTbl.hpAdj));
    basicInfo.push_back("System Shock Survivial: " + std::to_string(consTbl.sysShockSurPer) + "prcnt");
    basicInfo.push_back("Resurection Survival: " + std::to_string(consTbl.resurSurvPer) + "prcnt");
    return basicInfo;    
}

std::vector<std::string> getCharTbl(charismaTable charTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Charisma Table: ");
    basicInfo.push_back("Maximum Number of Followers: " + std::to_string(charTbl.maxHenchMen));
    basicInfo.push_back("Loyalty Percentage: " + std::to_string(charTbl.loyaltyBasePer) + "prcnt");
    basicInfo.push_back("Reaction of others: " + std::to_string(charTbl.reactAdjustPer) + "prcnt");
    return basicInfo;    
}

void printCharTbl(charismaTable charTbl)
{
    std::cout << "\r\nCharisma Table: " << std::endl;
    std::cout << "Maximum Number of Followers: " << charTbl.maxHenchMen << std::endl;
    std::cout << "Loyalty Percentage: " << charTbl.loyaltyBasePer << '%' << std::endl;
    std::cout << "Reaction of others: " << charTbl.reactAdjustPer << '%' << std::endl;
}

void printLanguages(std::vector<LANGUAGE> lang)
{
    std::unordered_map<LANGUAGE, std::string> langMap;
    for(unsigned i = 0; i < langPairs.size(); ++i){
        langMap[langPairs[i].langE] = langPairs[i].langS;
    }
    std::cout << "\r\nKnown Languages: " << std::endl;
    for(unsigned i = 0; i < lang.size(); ++i){
        std::cout << langMap[lang[i]];
        if(i < lang.size() - 1){
            std::cout << ", ";
        }
    }
    std::cout << std::endl << std::endl;
}

std::vector<std::string> getLanguages(std::vector<LANGUAGE> lang)
{
    std::unordered_map<LANGUAGE, std::string> langMap;
    for(unsigned i = 0; i < langPairs.size(); ++i){
        langMap[langPairs[i].langE] = langPairs[i].langS;
    }
    std::vector<std::string> langVect;
    langVect.push_back("Known Languages:");
    for(unsigned i = 0; i < lang.size(); ++i){
        langVect.push_back(langMap[lang[i]]);
    }    
    return langVect;
}

void printMoney(money inMoney)
{
    std::cout << "\r\nChar Money: " << std::endl;
    std::cout << "gold: " << inMoney.gold << std::endl;
    std::cout << "silver: " << inMoney.silver << std::endl;
    std::cout << "copper: " << inMoney.copper << std::endl;
    std::cout << "electrum: " << inMoney.electrum << std::endl;
    std::cout << "platinum: " << inMoney.platinum << std::endl;
}

bool raceStatCheck(stats inStats, RACE race)
{
    switch(race){
        case HUMAN:
            return true;
        case ELF:
            if(inStats.intelligence < 8){
                //std::cout << "Elf can not have intelligence bellow 8" << std::endl;
                return false;
            }
            if(inStats.dexterity + 1 < 7){
                //std::cout << "Elf can not have dexterity bellow 7" << std::endl;
                return false;
            }

            if(inStats.charisma < 8){
                //std::cout << "Elf can not have charisma bellow 8" << std::endl;
                return false;
            }

            if(inStats.constitution - 1 < 6){
                //std::cout << "Elf can not have constitution bellow 6" << std::endl;
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
            if(inStats.charisma < 8){
                stats tmpStats = inStats;
                tmpStats.constitution += 1;
                tmpStats.strength += 1;
                return classStatCheck(ASSASSIN, tmpStats);
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

            if(inStats.charisma - 1 < 6){
                stats tmpStats = inStats;
                tmpStats.constitution += 1;
                tmpStats.charisma -= 1;
                return classStatCheck(ASSASSIN, tmpStats);
            }

            return true;
        case HALFLING:
            if(inStats.strength - 1 < 6){
                //std::cout << "Halfling strength bellow 6" << std::endl;
                return false;                  
            }

            if(inStats.intelligence < 6){
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
           if(inStats.intelligence < 4){
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

            if(inStats.intelligence < 7){
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

bool classRaceCheck(CHAR_CLASS cClass, RACE race)
{
    switch(cClass){
        case CLERIC:
            if(race == HALF_ELF || race == HALF_ORC || race == HUMAN){
                return true;
            }
            return false;
        case DRUID:
            if(race == HALF_ELF || race == HUMAN){
                return true;
            }
            return false;
        case FIGHTER:
            return true;
        case PALADIN:
            if(race == HUMAN){
                return true;
            }
            return false;
        case RANGER:
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
            return true;
        case ASSASSIN:
            if(race == HALFLING){
                return false;
            }
            return true;
        case MONK:
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
            if(inStats.strength < 6){
                return false;
            }
            if(inStats.intelligence < 6){
                return false;
            }
            if(inStats.wisdom < 9){
                return false;
            }
            if(inStats.constitution < 6){
                return false;
            }
            if(inStats.charisma < 6){
                return false;
            }
            return true;
        case DRUID:
            if(inStats.strength < 6){
                return false;
            }
            if(inStats.intelligence < 6){
                return false;
            }
            if(inStats.wisdom < 12){
                return false;
            }
            if(inStats.dexterity < 6){
                return false;
            }
            if(inStats.constitution < 6){
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
            if(inStats.wisdom < 6){
                return false;
            }
            if(inStats.dexterity < 6){
                return false;
            }
            if(inStats.constitution < 7){
                return false;
            }
            if(inStats.charisma < 6){
                return false;
            }
            return true;
        case PALADIN:
            if(inStats.strength < 12){
                return false;
            }
            if(inStats.intelligence < 9){
                return false;
            }
            if(inStats.wisdom < 13){
                return false;
            }
            if(inStats.dexterity < 6){
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
            if(inStats.intelligence < 6){
                return false;
            }
            if(inStats.wisdom < 14){
                return false;
            }
            if(inStats.dexterity < 6){
                return false;
            }
            if(inStats.constitution < 14){
                return false;
            }
            if(inStats.charisma < 6){
                return false;
            }
            return true;
        case MAGIC_USER:
            if(inStats.intelligence < 9){
                return false;
            }
            if(inStats.wisdom < 6){
                return false;
            }
            if(inStats.dexterity < 6){
                return false;
            }
            if(inStats.constitution < 6){
                return false;
            }
            return true;
        case ILLUSIONIST:
            if(inStats.strength < 6){
                return false;
            }
            if(inStats.intelligence < 15){
                return false;
            }
            if(inStats.wisdom < 6){
                return false;
            }
            if(inStats.dexterity < 16){
                return false;
            }
            if(inStats.charisma < 6){
                return false;
            }
            return true;
        case THIEF:
            if(inStats.strength < 6){
                return false;
            }
            if(inStats.intelligence < 6){
                return false;
            }
            if(inStats.dexterity < 9){
                return false;
            }
            if(inStats.constitution < 6){
                return false;
            }
            if(inStats.charisma < 6){
                return false;
            }
            return true;
        case ASSASSIN:
            if(inStats.strength < 12){
                return false;
            }
            if(inStats.intelligence < 11){
                return false;
            }
            if(inStats.wisdom < 6){
                return false;
            }
            if(inStats.dexterity < 12){
                return false;
            }
            if(inStats.constitution < 6){
                return false;
            }
            return true;
        case MONK:
            if(inStats.strength < 15){
                return false;
            }
            if(inStats.intelligence < 6){
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
            if(inStats.charisma < 6){
                return false;
            }
            return true;

    }
}

bool alignClassCheck(CHAR_CLASS inClass, ALIGNMENT inAlign)
{
    switch(inClass){
        case CLERIC:
            if(inAlign == TRUE_NEUTRAL){
                return false;
            } else {
                return true;
            }
        case DRUID:
            if(inAlign != TRUE_NEUTRAL){
                return false;
            }
            return true;
        case FIGHTER:
            return true;
        case PALADIN:
            if(inAlign != LAWFUL_GOOD){
                return false;
            }
            return true;
        case RANGER:
            if(inAlign != CHAOTIC_GOOD && inAlign != NEUTRAL_GOOD && inAlign != LAWFUL_GOOD){
                return false;
            }
        case MAGIC_USER:
            return true;
        case ILLUSIONIST:
            return true;
        case THIEF:
            if(inAlign == CHAOTIC_GOOD || inAlign == LAWFUL_GOOD){
                return false;
            }
            return true;
        case ASSASSIN:
            if(inAlign != LAWFUL_EVIL && inAlign != NEUTRAL_EVIL && inAlign != CHAOTIC_EVIL ){
                return false;
            }
            return true;
        case MONK:
            if(inAlign != LAWFUL_EVIL && inAlign != LAWFUL_NEUTRAL && inAlign != LAWFUL_GOOD){
                return false;
            }
            return true;
        default:
            return true;
    }
}

bool checkClassStats(CHAR_CLASS inClass, stats inStats)
{
    switch(inClass){
        case DRUID:
            if(inStats.wisdom < 12 || inStats.charisma < 15){
                return false;
            }

            if(inStats.strength < 6 || inStats.intelligence < 6){
                return false;
            }

            if(inStats.dexterity < 6 || inStats.constitution < 6){
                return false;
            }

            return true;
        case PALADIN:
            if(inStats.charisma < 17){
                return false;
            }

            if(inStats.strength < 12 || inStats.intelligence < 9 || inStats.wisdom < 13 || inStats.constitution < 9 || inStats.charisma < 17){
                return false;
            }

            if(inStats.dexterity < 6){
                return false;
            }

            return true;
        case RANGER:
            if(inStats.strength < 13 || inStats.intelligence < 13 || inStats.wisdom < 14 || inStats.constitution < 14){
                return false;
            }

            if(inStats.charisma < 6 || inStats.dexterity < 6){
                return false;
            }

            return true;
        case ILLUSIONIST:
            if(inStats.intelligence < 15 || inStats.dexterity < 16){
                return false;
            }

            if(inStats.charisma < 6 || inStats.wisdom < 6){
                return false;
            }

            return true;
        case ASSASSIN:
            if(inStats.strength < 12 || inStats.intelligence < 11 || inStats.dexterity <12){
                return false;
            }

            if(inStats.constitution < 6){
                return false;
            }

            return true;
        case MONK:
            if(inStats.strength < 15 || inStats.wisdom < 15 || inStats.dexterity < 15 || inStats.constitution < 11){
                return false;
            }

            if(inStats.intelligence < 6 || inStats.charisma < 6){
                return false;
            }

            return true;
        default:
            return false;
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

// This checks to see of stat rolls will generate non viable class
// Based off of Gygaxian 1st Ed. rules.
bool rollFailure(stats inStats, bool printMsg){
    if(inStats.constitution < 6 && (inStats.intelligence < 15 || inStats.dexterity < 16)){
        //fails illusionist only case const <= 5
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Illusionist only.\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    if(inStats.intelligence < 6 && inStats.strength < 9){
        //fails Fighter only case int <= 5
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Fighter only\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    if(inStats.wisdom < 6 && inStats.dexterity < 9){
        //fails Thief only case wis <= 5
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Thief only\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    if(inStats.strength < 6 && inStats.intelligence < 9){
        //fails Magic User only case
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Magic-User only\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    if(inStats.dexterity < 6 && inStats.wisdom < 9){
        //fails Cleric only case
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Cleric only\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    if(inStats.charisma < 6 && (inStats.strength < 12 || inStats.intelligence < 11 || inStats.dexterity < 12)){
        //fails Assasin only case
        if(printMsg){
            std::cout << "\r\nCursed Stats:" << std::endl;
            printStats(inStats);
            std::cout << "\r\nFailed Assasin only\r\nAuto re-roll." << std::endl;
        }
        return false;
    }
    return true;
}

void printAlign(ALIGNMENT align)
{
    std::unordered_map<ALIGNMENT, std::string> aMap;
    for(unsigned i = 0; i < alignPairs.size(); ++i){
        aMap[alignPairs[i].align] = alignPairs[i].alignS;
    }
    std::cout << "Alignment: " << aMap[align] << std::endl;
}

std::string getAlign(ALIGNMENT align)
{
    std::unordered_map<ALIGNMENT, std::string> aMap;
    for(unsigned i = 0; i < alignPairs.size(); ++i){
        aMap[alignPairs[i].align] = alignPairs[i].alignS;
    }
    return aMap[align];
}

void printClass(CHAR_CLASS cClass)
{
    std::unordered_map<CHAR_CLASS, std::string> cMap;
    for(unsigned i = 0; i < classPairs.size(); ++i){
        cMap[classPairs[i].cClass] = classPairs[i].cS;
    }
    std::cout << "Class: " << cMap[cClass] << std::endl;   
}

std::string getClass(CHAR_CLASS inClass)
{
    std::unordered_map<CHAR_CLASS, std::string> cMap;
    for(unsigned i = 0; i < classPairs.size(); ++i){
        cMap[classPairs[i].cClass] = classPairs[i].cS;
    }
    return cMap[inClass];    
}

std::string strenFails(stats inStats)
{   
    std::string failures;
    switch(inStats.strength){
        case 3:
        case 4:
            failures += "Half-Orc";
            failures += "Halfling Gnome Dwarf and all classes but Magic-User";
            return failures;
        case 5:
            // Strength +1 Half-Orc
            failures += "Halfling Gnome Dwarf and all classes but Magic-User except for Half-Orcs";
            return failures;
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
    switch(inStats.intelligence){
        case 3:
            failures += "Half-Elf ";
        case 4:
        case 5:
            failures += "Halfling ";
            failures += "Gnome Elf All classes but Fighter";
            return failures;
        case 6:
            failures += "Gnome ";
        case 7:
            failures += "Elf ";
        case 8: 
            failures += "Paladin Magic-User ";
        case 9:
        case 10:
            failures += "Assassin ";
        case 11:
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
        case 5:
            failures += "All classes but Thief ";
            return failures;
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
        case 5:
            failures += "Half-Elf Elf Halfling and all classes but Cleric ";
            return failures;
        case 6:
            // Halfling dex + 1
            failures += "Magic-User ";
            failures += "Halfling Elf ";
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
            failures += "Elf ";
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

RACIAL_BIAS getRacialBias(RACE race1, RACE race2)
{
    if(race1 == DWARF && race2 == DWARF){
        return PREFERRED;
    } else if(race1 == DWARF && race2 == ELF){
        return ANTIPATHY;        
    } else if(race1 == DWARF && race2 == GNOME){
        return GOODWILL;        
    } else if(race1 == DWARF && race2 == HALF_ELF){
        return NEUTRALITY;        
    } else if(race1 == DWARF && race2 == HALFLING){
        return GOODWILL;        
    } else if(race1 == DWARF && race2 == HALF_ORC){
        return HATE;        
    } else if(race1 == DWARF && race2 == HUMAN){
        return NEUTRALITY;        
    } else if(race1 == ELF && race2 == ELF){
        return PREFERRED;        
    } else if(race1 == ELF && race2 == GNOME){
        return TOLERANCE;        
    } else if(race1 == ELF && race2 == HALF_ELF){
        return PREFERRED;        
    } else if(race1 == ELF && race2 == HALFLING){
        return GOODWILL;        
    } else if(race1 == ELF && race2 == HALF_ORC){
        return ANTIPATHY;        
    } else if(race1 == ELF && race2 == HUMAN){
        return NEUTRALITY;        
    } else if(race1 == GNOME && race2 == GNOME){
        return PREFERRED;        
    } else if(race1 == GNOME && race2 == HALF_ELF){
        return TOLERANCE;        
    } else if(race1 == GNOME && race2 == HALFLING){
        return GOODWILL;        
    } else if(race1 == GNOME && race2 == HALF_ORC){
        return HATE;        
    } else if(race1 == GNOME && race2 == HUMAN){
        return NEUTRALITY;        
    } else if(race1 == HALF_ELF && race2 == HALF_ELF){
        return PREFERRED;        
    } else if(race1 == HALF_ELF && race2 == HALFLING){
        return NEUTRALITY;        
    } else if(race1 == HALF_ELF && race2 == HALF_ORC){
        return ANTIPATHY;        
    } else if(race1 == HALF_ELF && race2 == HUMAN){
        return TOLERANCE;        
    } else if(race1 == HALFLING && race2 == HALFLING){
        return PREFERRED;        
    } else if(race1 == HALFLING && race2 == HALF_ORC){
        return NEUTRALITY;        
    } else if(race1 == HALFLING && race2 == HUMAN){
        return NEUTRALITY;        
    } else if(race1 == HALF_ORC && race2 == HALF_ORC){
        return PREFERRED;        
    } else if(race1 == HALF_ORC && race2 == HUMAN){
        return TOLERANCE;        
    } else if(race1 == HUMAN && race2 == HUMAN){
        return PREFERRED;        
    } else {
        return getRacialBias(race2, race1);
    }
}
void printRacialBias(RACIAL_BIAS bias)
{
    switch(bias){
        case HATE:
            std::cout << "Hatred\r\n" << std::endl;
            break;
        case ANTIPATHY:
            std::cout << "Antipathy\r\n" << std::endl;
            break;
        case NEUTRALITY:
            std::cout << "Neutrality\r\n" << std::endl;
            break;
        case TOLERANCE:
            std::cout << "Tolerance\r\n" << std::endl;
            break;
        case GOODWILL:
            std::cout << "Goodwill\r\n" << std::endl;
            break;
        case PREFERRED:
            std::cout << "Preferred\r\n" << std::endl;
            break;
        default:
            std::cout << "Error Bias\r\n" << std::endl;
            break;
    }
}

std::vector<std::string> getStrTbl(strengthTable strTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Strength Table:");
    basicInfo.push_back("Hit Probability: "  + std::to_string(strTbl.hitProb));
    basicInfo.push_back("Damage Adjustment: " + std::to_string(strTbl.damageAdj));
    basicInfo.push_back("Weight Allowance Modification: " + std::to_string(strTbl.weightAllowMod));
    basicInfo.push_back("Open Doors: " + std::to_string(strTbl.openDoors));
    basicInfo.push_back("Bend Bars / Lift Gates: " + std::to_string(strTbl.bendBarsLiftGatesPer) + " prcnt");
    return basicInfo; 
}

std::vector<std::string> getIntTbl(intelligenceTable intTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Intelligece Table:");
    basicInfo.push_back("Chance to Know each Listed Spell: " + std::to_string(intTbl.chanceToKnowPer) + " prcnt");
    basicInfo.push_back("Minimum Number of Spells per Level: " + std::to_string(intTbl.minumumSpellsPerLevel));
    basicInfo.push_back("Maximum Number of Spells per Level: " + std::to_string(intTbl.maxiumSpellsPerlevel));
    basicInfo.push_back("Possible Number of Additional Languages: " + std::to_string(intTbl.possibAddLang));  
    return basicInfo; 
}

std::vector<std::string> getWisTbl(wisdomTable wisTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Wisdom Table:");
    basicInfo.push_back("Magic Attack Adjustment: " + std::to_string(wisTbl.magicAttackAdj));
    basicInfo.push_back("Spell bonus (1 for each level under shown level): " + std::to_string(wisTbl.spellBonus));
    basicInfo.push_back("Chance for Spell Failure: " + std::to_string(wisTbl.spellFailPer) + " prcnt");
    return basicInfo;  
}

std::vector<std::string> getDexTbl(dexterityTable dexTbl)
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Dexterity Table:");
    basicInfo.push_back("Reaction/Attacking Adjustment: " + std::to_string(dexTbl.reactAttkAdj));
    basicInfo.push_back("Defensive Adjustment: "+ std::to_string(dexTbl.defenseAdj));
    return basicInfo;    
}

/* Initialize new terminal i/o settings */
//void initTermios(int echo)//
//{
//  tcgetattr(0, &old); /* grab old terminal i/o settings */
//  current = old; /* make new settings same as old settings */
//  current.c_lflag &= ~ICANON; /* disable buffered i/o */
//  if (echo) {
//      current.c_lflag |= ECHO; /* set echo mode */
//  } else {
//      current.c_lflag &= ~ECHO; /* set no echo mode */
//  }
//  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
//}

/* Restore old terminal i/o settings */
//void resetTermios(void) 
//{
//  tcsetattr(0, TCSANOW, &old);
//}

/* Read 1 character - echo defines echo mode */
//char getch_(int echo) 
//{
//  char ch;
//  initTermios(echo);
//  ch = getchar();
//  resetTermios();
//  return ch;
//}

/* Read 1 character without echo */
//char getch_n(void) 
//{
//  return getch_(0);
//}

/* Read 1 character with echo */
//char getche(void) 
//{
//  return getch_(1);
//}