/*
    Antone Bajor 2023
*/
#include "entity.h"

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

Entity::Entity(ALIGNMENT align, SEX sex, std::string name)
{
    _name = name;
    _sex = sex;
    _alignment = align;
    unsigned str_mod = 0;
    _stats.strength = bestThree();
    if(_stats.strength > 17){
        _stats.excStren = rollDice(10, true) + rollDice(10, true)*10 + 1;
    }
    _stats.intellignece = bestThree();
    _stats.wisdom = bestThree();
    _stats.charisma = bestThree();
    _stats.dexterity = bestThree();
    _stats.constitution = bestThree();
}

void Entity::setStrenTbl()
{
    switch(_stats.strength){
        case 3:
            _strTbl.hitProb = -3;
            _strTbl.damageAdj = -1;
            _strTbl.weightAllowMod = -350;
            _strTbl.openDoors = 1;
            _strTbl.bendBarsLiftGatesPer = 0;
            break;
        case 4:
        case 5:
            _strTbl.hitProb = -2;
            _strTbl.damageAdj = -1;
            _strTbl.weightAllowMod = -250;
            _strTbl.openDoors = 1;
            _strTbl.bendBarsLiftGatesPer = 0;
            break;
        case 6:
        case 7:
            _strTbl.hitProb = -1;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = -150;
            _strTbl.openDoors = 1;
            _strTbl.bendBarsLiftGatesPer = 0;
            break;
        case 8:
        case 9:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = 0;
            _strTbl.openDoors = 2;
            _strTbl.bendBarsLiftGatesPer = 1;
            break;
        case 10:
        case 11:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = 0;
            _strTbl.openDoors = 2;
            _strTbl.bendBarsLiftGatesPer = 2;
            break;
        case 12:
        case 13:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = 100;
            _strTbl.openDoors = 2;
            _strTbl.bendBarsLiftGatesPer = 4;
            break;
        case 14:
        case 15:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = 200;
            _strTbl.openDoors = 2;
            _strTbl.bendBarsLiftGatesPer = 7;
            break;
        case 16:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 1;
            _strTbl.weightAllowMod = 350;
            _strTbl.openDoors = 3;
            _strTbl.bendBarsLiftGatesPer = 10;
            break;
        case 17:
            _strTbl.hitProb = 1;
            _strTbl.damageAdj = 1;
            _strTbl.weightAllowMod = 500;
            _strTbl.openDoors = 3;
            _strTbl.bendBarsLiftGatesPer = 13;
            break;
        case 18:
            if(_stats.excStren > 0 && isFighter()){
                if(_stats.excStren < 51){
                    _strTbl.hitProb = 1;
                    _strTbl.damageAdj = 2;
                    _strTbl.weightAllowMod = 1000;
                    _strTbl.openDoors = 3;
                    _strTbl.bendBarsLiftGatesPer = 20;
                } else if(_stats.excStren < 76){
                    _strTbl.hitProb = 2;
                    _strTbl.damageAdj = 3;
                    _strTbl.weightAllowMod = 1250;
                    _strTbl.openDoors = 4;
                    _strTbl.bendBarsLiftGatesPer = 25;
                } else if(_stats.excStren < 91){
                    _strTbl.hitProb = 2;
                    _strTbl.damageAdj = 4;
                    _strTbl.weightAllowMod = 1500;
                    _strTbl.openDoors = 4;
                    _strTbl.bendBarsLiftGatesPer = 30;
                } else if(_stats.excStren < 100){
                    _strTbl.hitProb = 2;
                    _strTbl.damageAdj = 5;
                    _strTbl.weightAllowMod = 2000;
                    _strTbl.openDoors = 4;
                    _strTbl.bendBarsLiftGatesPer = 35;
                } else {
                    _strTbl.hitProb = 3;
                    _strTbl.damageAdj = 6;
                    _strTbl.weightAllowMod = 3000;
                    _strTbl.openDoors = 5;
                    _strTbl.bendBarsLiftGatesPer = 40;
                }
            } else {
                _strTbl.hitProb = 1;
                _strTbl.damageAdj = 2;
                _strTbl.weightAllowMod = 750;
                _strTbl.openDoors = 3;
                _strTbl.bendBarsLiftGatesPer = 16;
                _stats.excStren = 0;
            }
            break;
        default:
            _strTbl.hitProb = 0;
            _strTbl.damageAdj = 0;
            _strTbl.weightAllowMod = 0;
            _strTbl.openDoors = 0;
            _strTbl.bendBarsLiftGatesPer = 0;
            break;
    }
}

void Entity::setIntTbl()
{
    switch(_stats.intellignece){
        case 9:
            _intTbl.chanceToKnowPer = 35;
            _intTbl.minumumSpellsPerLevel = 4;
            _intTbl.maxiumSpellsPerlevel = 6;
            break;
        case 10:
        case 11:
        case 12:
            _intTbl.chanceToKnowPer = 45;
            _intTbl.minumumSpellsPerLevel = 5;
            _intTbl.maxiumSpellsPerlevel = 7;
            break;
        case 13:
        case 14:
            _intTbl.chanceToKnowPer = 55;
            _intTbl.minumumSpellsPerLevel = 4;
            _intTbl.maxiumSpellsPerlevel = 6;
            break;
        case 15:
        case 16:
            _intTbl.chanceToKnowPer = 65;
            _intTbl.minumumSpellsPerLevel = 7;
            _intTbl.maxiumSpellsPerlevel = 11;
            break;
        case 17:
            _intTbl.chanceToKnowPer = 75;
            _intTbl.minumumSpellsPerLevel = 8;
            _intTbl.maxiumSpellsPerlevel = 14;
            break;
        case 18:
            _intTbl.chanceToKnowPer = 85;
            _intTbl.minumumSpellsPerLevel = 9;
            _intTbl.maxiumSpellsPerlevel = 18;
            break;
        case 19:
            _intTbl.chanceToKnowPer = 95;
            _intTbl.minumumSpellsPerLevel = 10;
            _intTbl.maxiumSpellsPerlevel = 255;
            break;
        default:
            if(_stats.intellignece > 19){
            _intTbl.chanceToKnowPer = 95;
            _intTbl.minumumSpellsPerLevel = 10;
            _intTbl.maxiumSpellsPerlevel = 255;
            break; 
            }            

    }  
}

void Entity::setPossLang()
{
    switch(_stats.intellignece){
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            _intTbl.possibAddLang = 1;
            break;
        case 10:
        case 11:
            _intTbl.possibAddLang = 2;
            break;
        case 12:
        case 13:
            _intTbl.possibAddLang = 3;
            break;
        case 14:
        case 15:
            _intTbl.possibAddLang = 4;
            break;
        case 16:
            _intTbl.possibAddLang = 5;
            break;
        case 17:
            _intTbl.possibAddLang = 6;
            break;
        case 18:
            _intTbl.possibAddLang = 7;
            break;
        default:
           break;
    }
}

stats Entity::getStats()
{
    return _stats;
}

std::string Entity::getName()
{
    return _name;
}

SEX Entity::getSex()
{
    return _sex;
}

void Entity::setRace(RACE race)
{
    _race = race;
}

bool Entity::checkRaceStats(RACE race)
{
    switch(race){
        // check for failures before adding race bonus's
        case HUMAN:
            // Check Stat Limitation.
            if(_stats.excStren > 51 && _sex == FEMALE){
                std::cout << "Human Female Exceptional Strength Capped at 51" << std::endl;
                _stats.excStren = 51;
            }
            _race = race;
            return true;
        case ELF:
            // Stat Limitation Check
            if(_stats.intellignece < 8){
                std::cout << "Elf can not have intelligence bellow 8" << std::endl;
                return false;
            }
            if(_stats.dexterity + 1 < 7){
                std::cout << "Elf can not have dexterity bellow 7" << std::endl;
                return false;
            }
            if(_stats.constitution - 1 < 6){
                std::cout << "Elf can not have constitution bellow 6" << std::endl;
                return false;
            }
            if(_stats.charisma < 8){
                std::cout << "Elf can not have charisma bellow 8" << std::endl;
                return false;
            }
            if(_sex == FEMALE && _stats.strength > 16){
                std::cout << "Elf Female Strength Capped at 16" << std::endl;
                _stats.strength = 16;
            }
            // Apply Standard Elf Modifiers
            _stats.constitution--;
            _stats.dexterity++;
            _race = race;
            return true;
        case HALF_ORC:
            if(_stats.strength + 1 < 6){
                std::cout << "Half-Orc Strength bellow 6" << std::endl;
                return false;
            }

            if(_stats.constitution + 1 < 13){
                std::cout << "Half-Orc constitution bellow 13" << std::endl;
                return false;
            }

            if(_stats.intellignece > 17){
                std::cout << "Half-Orc Intelligence being set to cap 17" << std::endl;
                _stats.intellignece = 17;
            }

            if(_stats.dexterity > 17){
                std::cout << "Half-Orc Dexterity being set to cap 17" << std::endl;
                _stats.dexterity = 17;
            }

            if(_stats.wisdom > 14){
                std::cout << "Half-Orc Wisdom being set to cap 14" << std::endl;
                _stats.wisdom = 14;
            }

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
            _race = race;
            return true;
        case DWARF:
            if(_stats.strength < 8){
                std::cout << "Dwarf strength bellow 8" << std::endl;
                return false;            
            }

            if(_stats.constitution + 1 < 12){
                std::cout << "Dwarf constitution bellow 12" << std::endl;
                return false;            
            }
            
            if(_stats.strength > 17 && _sex == FEMALE){
                std::cout << "Female Dwarf strength cap 17" << std::endl;
                _stats.strength = 17;
            }

            if(_stats.dexterity > 17){
                std::cout << "Dwarf dexterity cap 17" << std::endl;
                _stats.dexterity = 17;            
            }

            if(_stats.charisma - 1 > 16){
                std::cout << "Dwarf charisma cap 16" << std::endl;
                _stats.charisma = 16;
            } else {
                _stats.charisma--;
            }

            _stats.constitution++;
            _race = race;
            return true;
        case HALFLING:
            if(_stats.strength - 1 < 6){
                std::cout << "Halfling strength bellow 6" << std::endl;
                return false;                  
            }

            if(_stats.intellignece < 6){
                std::cout << "Halfling intelligence bellow 6" << std::endl;
                return false;                
            }

            if(_stats.dexterity + 1 < 8){
                std::cout << "Halfling dexterity bellow 8" << std::endl;
                return false;
            }

            if(_stats.constitution < 10){
                std::cout << "Halfling constitution bellow 10" << std::endl;
                return false;
            }

            if(_stats.strength - 1 > 14 && _sex == FEMALE){
                std::cout << "Female Halfling strength cap 14" << std::endl;
                _stats.strength = 14;
                _stats.excStren = 0;
            } else {
                _stats.strength--;
            }                    

            if(_stats.wisdom > 17){
                std::cout << "Halfling wisdom cap 17" << std::endl;
                _stats.wisdom = 17;
            }

            _stats.dexterity++;
            _race = race;
            return true;
        case HALF_ELF:
            if(_stats.intellignece < 4){
                std::cout << "Intelligence bellow 4" << std::endl;
                return false;
            }

            if(_stats.dexterity < 6){
                std::cout << "Dexterity bellow 6" << std::endl;
                return false;
            }

            if(_stats.constitution < 6){
                std::cout << "Constitution bellow 6" << std::endl;
                return false;
            }

            if(_stats.excStren > 90){
                std::cout << "Half-Elf exceptional strength cap 90" << std::endl;
                _stats.excStren = 90;
            }

            if(_stats.strength > 17 && _sex == FEMALE){
                std::cout << "Female Half-Elf strength cap 17" << std::endl;
                _stats.strength = 17;
            }

            _race = race;
            return true;
        case GNOME:
            if(_stats.strength < 6){
                std::cout << "Strength bellow 6" << std::endl;
                return false;
            }

            if(_stats.intellignece < 7){
                std::cout << "Intelligence bellow 7" << std::endl;
                return false;
            }

            if(_stats.constitution < 8){
                std::cout << "Constitution bellow 8" << std::endl;
                return false;
            }

            if(_stats.strength > 15 && _sex == FEMALE){
                std::cout << "Female Gnome strength cap 15" << std::endl;
                _stats.strength = 15;
            }            

            _race = race;
            return true;
    }
}

void Entity::reRollStats()
{
    _stats.strength = bestThree();
    if(_stats.strength > 17){
        _stats.excStren = rollDice(10, true) + rollDice(10, true)*10 + 1;
    }
    _stats.intellignece = bestThree();
    _stats.wisdom = bestThree();
    _stats.charisma = bestThree();
    _stats.dexterity = bestThree();
    _stats.constitution = bestThree();  
}

RACE Entity::getRace(){
    return _race;
}

ALIGNMENT Entity::getAlign(){
    return _alignment;
}

std::vector<CHAR_CLASS> Entity::getClass()
{
    return _chrClass;
}

bool Entity::setClass(CHAR_CLASS inClass)
{
    _chrClass.push_back(inClass);
    setStrenTbl();
    setIntTbl();
    setPossLang();
}

strengthTable Entity::getStrTbl()
{
    return _strTbl;
}

inteligenceTable Entity::getIntTbl()
{
    return _intTbl;
}

bool Entity::isFighter(){
    for(int i = 0; i < _chrClass.size(); i++){
        if(_chrClass[i] == FIGHTER || _chrClass[i] == PALADIN || _chrClass[i] == RANGER){
            return true;
        }
    }
    return false;
}

bool Entity::saveChar()
{
    // Making Fun Difficult Hardcoding the Jason Format.
    std::string outTxt = "{\r\n    \"data\":{\r\n";
    outTxt += "        \"name\":\"" + _name + "\",\r\n";
    outTxt += "        \"alignment\":" + std::to_string(_alignment) + ",\r\n";
    outTxt += "        \"sex\":" + std::to_string(_sex) + ",\r\n";
    outTxt += "        \"race\":" + std::to_string(_race) + ",\r\n";
    outTxt += "        \"level\":" + std::to_string(_level) + ",\r\n";
    outTxt += "        \"class\":" + std::to_string(_chrClass[0]) + ",\r\n"; // vector for multiclass
    outTxt += "        \"stats\":{\r\n";
    outTxt += "            \"strength\":" + std::to_string(_stats.strength) + ",\r\n";
    outTxt += "            \"excStrength\":" + std::to_string(_stats.excStren) + ",\r\n";
    outTxt += "            \"intelligence\":" + std::to_string(_stats.intellignece) + ",\r\n";
    outTxt += "            \"wisdom\":" + std::to_string(_stats.wisdom) + ",\r\n";
    outTxt += "            \"dexterity\":" + std::to_string(_stats.dexterity) + ",\r\n";
    outTxt += "            \"constitution\":" + std::to_string(_stats.constitution) + ",\r\n";
    outTxt += "            \"charisma\":" + std::to_string(_stats.charisma) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"strengthTable\":{\r\n";
    outTxt += "            \"hitProb\":" + std::to_string(_strTbl.hitProb) + ",\r\n";
    outTxt += "            \"damageAdj\":" + std::to_string(_strTbl.damageAdj) + ",\r\n";
    outTxt += "            \"weightAllowMod\":" + std::to_string(_strTbl.weightAllowMod) + ",\r\n";
    outTxt += "            \"openDoors\":" + std::to_string(_strTbl.openDoors) + ",\r\n";
    outTxt += "            \"bendBarsLiftGatesPer\":" + std::to_string(_strTbl.bendBarsLiftGatesPer) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"intTable\":{\r\n";
    outTxt += "            \"chanceToKnowPer\":" + std::to_string(_intTbl.chanceToKnowPer) + ",\r\n";
    outTxt += "            \"minimumSpellsPer\":" + std::to_string(_intTbl.minumumSpellsPerLevel) + ",\r\n";
    outTxt += "            \"maximumSpellsPer\":" + std::to_string(_intTbl.maxiumSpellsPerlevel) + ",\r\n";
    outTxt += "            \"possibleAddLang\":" + std::to_string(_intTbl.possibAddLang) + "\r\n";
    outTxt += "        }\r\n";
    outTxt += "    }\r\n";
    outTxt += "}";

    std::cout << outTxt << std::endl;
    std::string filename = "characters/" + _name + ".json";
    std::ofstream myFile;
    myFile.open(filename);
    if(myFile.is_open()){
        myFile << outTxt;
        myFile.close();
    } else {
        std::cout << "File Can't open path " << filename << " invalid or cannot be accessed." << std::endl;
    }
}

bool Entity::loadEntity(std::string file)
{
    sj::ondemand::parser parser;
    sj::padded_string json = sj::padded_string::load(file.c_str());
    sj::ondemand::document charData = parser.iterate(json);
    std::stringstream recv;
    recv << ((charData["data"]["name"]));
    recv >> _name;
    _alignment = (ALIGNMENT)uint64_t(charData["data"]["alignment"]);
    _sex = (SEX)uint64_t(charData["data"]["sex"]);
    _race = (RACE)uint64_t(charData["data"]["race"]);
    // _chrClass is a vector of CHAR_CLASS ENUMS
    _chrClass.push_back((CHAR_CLASS)uint64_t(charData["data"]["class"]));
    _level = (unsigned)uint64_t(charData["data"]["level"]);
    _stats.strength = uint64_t(charData["data"]["stats"]["strength"]);
    _stats.intellignece = uint64_t(charData["data"]["stats"]["intelligence"]);
    _stats.wisdom = uint64_t(charData["data"]["stats"]["wisdom"]);
    _stats.dexterity = uint64_t(charData["data"]["stats"]["dexterity"]);
    _stats.constitution = uint64_t(charData["data"]["stats"]["constitution"]);
    _stats.charisma = uint64_t(charData["data"]["stats"]["charisma"]);

    _strTbl.hitProb = int64_t(charData["data"]["strengthTable"]["hitProb"]);
    _strTbl.damageAdj = int64_t(charData["data"]["strengthTable"]["damageAdj"]);
    _strTbl.weightAllowMod = int64_t(charData["data"]["strengthTable"]["weightAllowMod"]);
    _strTbl.openDoors = uint64_t(charData["data"]["strengthTable"]["openDoors"]);
    _strTbl.bendBarsLiftGatesPer = uint64_t(charData["data"]["strengthTable"]["bendBarsLiftGatesPer"]);

    _intTbl.chanceToKnowPer = uint64_t(charData["data"]["intTable"]["chanceToKnowPer"]);
    _intTbl.minumumSpellsPerLevel = uint64_t(charData["data"]["intTable"]["minimumSpellsPer"]);
    _intTbl.maxiumSpellsPerlevel = uint64_t(charData["data"]["intTable"]["maximumSpellsPer"]);
    _intTbl.possibAddLang = uint64_t(charData["data"]["intTable"]["possibleAddLang"]);
    

    std::cout << "Name: " << _name << std::endl;
    printAlign(_alignment);
    printSex(_sex);
    printRace(_race);
    printClass(_chrClass[0]);
    std::cout << "Level: " << _level << std::endl;
    printStats(_stats);
    printStrTbl(_strTbl);
    printIntTbl(_intTbl);

}

Entity::Entity(const char* filename)
{
    loadEntity(filename);
}
