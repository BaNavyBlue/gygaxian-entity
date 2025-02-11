#include "char_class.h"

CHR_CLASS_SKILLS::CHR_CLASS_SKILLS()
{

}

unsigned CHR_CLASS_SKILLS::generateGold()
{
    return (rollDice(4, false) + rollDice(4, false) + rollDice(4, false) + rollDice(4, false) + rollDice(4, false))*10;
}

unsigned CHR_CLASS_SKILLS::rollHP()
{
    return rollDice(_classTbl.HitDieType, false);
}

CHR_CLASS_SKILLS::~CHR_CLASS_SKILLS()
{
    //std::cout << "In CHR_CLASS_SKILLS destructor." << std::endl;
}

classTable1 CHR_CLASS_SKILLS::getClassTable1()
{
    return _classTbl;
}

void CHR_CLASS_SKILLS::listClassSkills()
{
    std::cout << "Hit Die Type d" << (int)_classTbl.HitDieType << " Max Hit Die: " << (int)_classTbl.MaxHitDie << std::endl;
    if(_classTbl.spellAbility){
        std::cout << "Can use spells." << std::endl;
    } else {
        std::cout << "Can't use spells." << std::endl;
    }
    if(_classTbl.LevelLimit > 0){
        std::cout << "Class Level Limit: " << _classTbl.LevelLimit << std::endl;
    } else {
        std::cout << "No class level Limit unless multiclass" << std::endl;
    }
    std::cout << "Initial Number of Weapons: " << _initNumWeap << std::endl;
    std::cout << "Non proficieny pentalty: " << _nonProfPenalty << std::endl;
    std::cout << "Added Proficiency in Weapons Per Level: 1/" << _addedWeapLvlDen << std::endl;
}

std::vector<std::string> CHR_CLASS_SKILLS::getClassSkills()
{
    std::vector<std::string> stringVect;
    stringVect.push_back("Class Skills:");
    stringVect.push_back("Hit Die Type d" + std::to_string((int)_classTbl.HitDieType) + " Max Hit Die: " + std::to_string(_classTbl.MaxHitDie));
    if(_classTbl.spellAbility){
        stringVect.push_back("Can use spells.");
    } else {
        stringVect.push_back("Can't use spells.");
    }

    if(_classTbl.LevelLimit > 0){
        stringVect.push_back("Class Level Limit: " + std::to_string(_classTbl.LevelLimit));
    } else {
        stringVect.push_back("No class level Limit unless multiclass");
    }

    stringVect.push_back("Initial Number of Weapons: " + std::to_string(_initNumWeap));
    stringVect.push_back("Non Proficiency Penalty: " + std::to_string(_nonProfPenalty));
    stringVect.push_back("Added Proficiency in Weapons Per Level: 1/" + std::to_string(_addedWeapLvlDen));
    return stringVect;

}

unsigned CHR_CLASS_SKILLS::getInitNumWeap()
{
    return _initNumWeap;
}

int CHR_CLASS_SKILLS::getNonProfPenalty()
{
    return _nonProfPenalty;
}

unsigned CHR_CLASS_SKILLS::getAddedWeapLevDen()
{
    return _addedWeapLvlDen;
}

Cleric::Cleric(){
    _classTbl.HitDieType = 8;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1; // -1 = no limit
    _initNumWeap = 2;
    _nonProfPenalty = -3;
    _addedWeapLvlDen = 4;
    //std::cout << "This should list Cleric HitDieType" << std::endl;
    //listClassSkills();
}

Cleric::~Cleric(){
    //std::cout << "Cleric Destructor" << std::endl;
}

unsigned Cleric::generateGold()
{
    return (rollDice(6, false) + rollDice(6, false) + rollDice(6, false))*10;
}

Druid::Druid(){
    _classTbl.HitDieType = 8;
    _classTbl.MaxHitDie = 14;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = 14; // The Great Druid
    _initNumWeap = 2;
    _nonProfPenalty = -4;
    _addedWeapLvlDen = 5;
    //listClassSkills();
}

Druid::~Druid(){
    //std::cout << "Druid Destructor" << std::endl;
}

unsigned Druid::generateGold()
{
    return (rollDice(6, false) + rollDice(6, false) + rollDice(6, false))*10;
}

Fighter::Fighter(){
    _classTbl.HitDieType = 10;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = -1;
    _initNumWeap = 4;
    _nonProfPenalty = -2;
    _addedWeapLvlDen = 3;
    //listClassSkills();
}

Fighter::~Fighter(){
    //std::cout << "Fighter Destructor" << std::endl;
}

Paladin::Paladin(){
    _classTbl.HitDieType = 10;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    _initNumWeap = 3;
    _nonProfPenalty = -2;
    _addedWeapLvlDen = 3;
    //listClassSkills();
}

Paladin::~Paladin(){
    //std::cout << "Paladin Destructor" << std::endl; 
}

void Ranger::listClassSkills()
{
    std::cout << "Hit Die Type d" << (int)_classTbl.HitDieType << " Max Hit Die: " << (int)_classTbl.MaxHitDie << std::endl;
    if(_classTbl.spellAbility){
        std::cout << "Can use spells." << std::endl;
    } else {
        std::cout << "Can't use spells." << std::endl;
    }
    if(_classTbl.LevelLimit > 0){
        std::cout << "Class Level Limit: " << _classTbl.LevelLimit << std::endl;
    } else {
        std::cout << "No class level Limit unless multiclass" << std::endl;
    }
    std::cout << "Initial Number of Weapons: " << _initNumWeap << std::endl;
    std::cout << "Non proficieny pentalty: " << _nonProfPenalty << std::endl;
    std::cout << "Added Proficiency in Weapons Per Level: 1/" << _addedWeapLvlDen << std::endl;
    std::cout << "Chance to be surprised d" << (int)_chanceToBeSurprised.sidedDie << " roll 1-" << (int)_chanceToBeSurprised.maxRange << std::endl;
    std::cout << "Chance to surprise d" << (int)_chanceToSurprise.sidedDie << " roll 1-" << (int)_chanceToSurprise.maxRange << std::endl;
    std::cout << "Track underground normal passage: " << (int)uGTrackPassagePer << "%" << std::endl;
    std::cout << "Track underground door or stairs: " << (int)uGTrackDrStrPer << "%" << std::endl;
    std::cout << "Track underground trap door: " << (int)uGTrackTrpDrPer << "%" << std::endl;
    std::cout << "Track underground chimney or sealed door: " << (int)uGTrackChimConDrPer << "%" << std::endl;
    std::cout << "Track underground secret door: " << (int)uGTrackScrtDoorPer << "%" << std::endl;
    std::cout << "Track outdoors general: " << (int)oDTrack << "%" << std::endl;
    std::cout << "Track outdoors each creature above 1: +" << (int)oDTrackMoreThan1Per << "\% per creature" << std::endl;
    std::cout << "Track outdoors every 24hours passed: " << oDTrack24HrPer << "\% per day" << std::endl;
    std::cout << "Track outdoors every hour of precipitaion: " << oDTrackHourPercip << "\% per hour" << std::endl;
}

std::vector<std::string> Ranger::getClassSkills()
{
    std::vector<std::string> stringVect;
    stringVect.push_back("Class Skills:");
    stringVect.push_back("Hit Die Type d" + std::to_string((int)_classTbl.HitDieType) + " Max Hit Die: " + std::to_string(_classTbl.MaxHitDie));
    if(_classTbl.spellAbility){
        stringVect.push_back("Can use spells.");
    } else {
        stringVect.push_back("Can't use spells.");
    }

    if(_classTbl.LevelLimit > 0){
        stringVect.push_back("Class Level Limit: " + std::to_string(_classTbl.LevelLimit));
    } else {
        stringVect.push_back("No class level Limit unless multiclass");
    }

    stringVect.push_back("Initial Number of Weapons: " + std::to_string(_initNumWeap));
    stringVect.push_back("Non Proficiency Penalty: " + std::to_string(_nonProfPenalty));
    stringVect.push_back("Added Proficiency in Weapons Per Level: 1/" + std::to_string(_addedWeapLvlDen));
    stringVect.push_back("Chance to be surprised d" + std::to_string(_chanceToBeSurprised.sidedDie) + " roll 1-" + std::to_string(_chanceToBeSurprised.maxRange));
    stringVect.push_back("Chance to surprise d" + std::to_string(_chanceToSurprise.sidedDie) + " roll 1-" + std::to_string(_chanceToSurprise.maxRange));
    stringVect.push_back("Track underground normal passage: " + std::to_string(uGTrackPassagePer) + "%");
    stringVect.push_back("Track underground door or stairs: " + std::to_string(uGTrackDrStrPer) + "%");
    stringVect.push_back("Track underground trap door: " + std::to_string(uGTrackTrpDrPer) + "%");
    stringVect.push_back("Track underground chimney or sealed door: " + std::to_string(uGTrackChimConDrPer) + "%");
    stringVect.push_back("Track underground secret door: " + std::to_string(uGTrackScrtDoorPer) + "%");
    stringVect.push_back("Track outdoors general: " + std::to_string(oDTrack) + "%");
    stringVect.push_back("Track outdoors each creature above 1: +" + std::to_string(oDTrackMoreThan1Per) + "\% per creature");
    stringVect.push_back("Track outdoors every 24hours passed: " + std::to_string(oDTrack24HrPer) + "\% per day");
    stringVect.push_back("Track outdoors every hour of precipitaion: " + std::to_string(oDTrackHourPercip) + "\% per hour");
    return stringVect;
}

Ranger::Ranger(){
    _classTbl.HitDieType = 8;// Begins with 2d8
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    _chanceToSurprise.sidedDie = 6;
    _chanceToSurprise.maxRange = 3; // 1-3
    _chanceToBeSurprised.sidedDie = 6;
    _chanceToBeSurprised.maxRange = 1; // 1-1
    _initNumWeap = 3;
    _nonProfPenalty = -2;
    _addedWeapLvlDen = 3;
    //std::cout << "Should Show Ranger variables" << std::endl;
    //listClassSkills();
}

Ranger::~Ranger(){
    //std::cout << "Ranger Destructor" << std::endl; 
}

MagicUser::MagicUser(){
    _classTbl.HitDieType = 4;
    _classTbl.MaxHitDie = 11;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    _initNumWeap = 1;
    _nonProfPenalty = -5;
    _addedWeapLvlDen = 6;
    //listClassSkills();
}

MagicUser::~MagicUser(){
    //std::cout << "MagicUser Destructor" << std::endl; 
}

unsigned MagicUser::generateGold()
{
    return (rollDice(4, false) + rollDice(4, false))*10;
}

Illusionist::Illusionist(){
    _classTbl.HitDieType = 4;
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    _initNumWeap = 1;
    _nonProfPenalty = -5;
    _addedWeapLvlDen = 6;
    //listClassSkills();
}

Illusionist::~Illusionist(){
    //std::cout << "Illusionist Destructor" << std::endl; 
}

unsigned Illusionist::generateGold()
{
    return (rollDice(4, false) + rollDice(4, false))*10;
}

Thief::Thief()
{

}

Thief::Thief(RACE inRace, unsigned inLevel){
    _classTbl.HitDieType = 6;
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = -1;
    _initNumWeap = 2;
    _nonProfPenalty = -3;
    _addedWeapLvlDen = 4;
    setThiefSkills(inRace, inLevel);
    //listClassSkills();
}

Thief::~Thief(){
    //std::cout << "Thief Destructor" << std::endl; 
}

unsigned Thief::generateGold()
{
    return (rollDice(6, false) + rollDice(6, false))*10;
}

void Thief::listClassSkills()
{
    std::cout << "Hit Die Type d" << (int)_classTbl.HitDieType << " Max Hit Die: " << (int)_classTbl.MaxHitDie << std::endl;
    if(_classTbl.spellAbility){
        std::cout << "Can use spells." << std::endl;
    } else {
        std::cout << "Can't use spells." << std::endl;
    }
    if(_classTbl.LevelLimit > 0){
        std::cout << "Class Level Limit: " << _classTbl.LevelLimit << std::endl;
    } else {
        std::cout << "No class level Limit unless multiclass" << std::endl;
    }
    std::cout << "Initial Number of Weapons: " << _initNumWeap << std::endl;
    std::cout << "Non proficieny pentalty: " << _nonProfPenalty << std::endl;
    std::cout << "Added Proficiency in Weapons Per Level: 1/" << _addedWeapLvlDen << std::endl;
    std::cout << "Bonus to hit while sneak/backstab: +" <<  (int)_surpriseAtk << std::endl;
    std::cout << "Pick Pockets: " << (int)_thiefTbl.pickPockets << "%" << std::endl;
    std::cout << "Open Locks: " << (int)_thiefTbl.openLocks << "%" << std::endl;
    std::cout << "Find/Remove Traps: " << (int)_thiefTbl.findRemoveTraps << "%" << std::endl;
    std::cout << "Move silently: " << (int)_thiefTbl.moveSilently << "%" << std::endl;
    std::cout << "Hide in Shadows: " << (int)_thiefTbl.hideInShadows << "%" << std::endl;
    std::cout << "Hear Noise: " << (int)_thiefTbl.hearNoise << "%" << std::endl;
    std::cout << "Climb Walls: " << _thiefTbl.climbWalls << "%" << std::endl;
    std::cout << "Read Languages: " << (int)_thiefTbl.readLanguages << "%" << std::endl;        
}

std::vector<std::string> Thief::getClassSkills()
{
    std::vector<std::string> stringVect;
    stringVect.push_back("Class Skills:");
    stringVect.push_back("Hit Die Type d" + std::to_string((int)_classTbl.HitDieType) + " Max Hit Die: " + std::to_string(_classTbl.MaxHitDie));
    if(_classTbl.spellAbility){
        stringVect.push_back("Can use spells.");
    } else {
        stringVect.push_back("Can't use spells.");
    }

    if(_classTbl.LevelLimit > 0){
        stringVect.push_back("Class Level Limit: " + std::to_string(_classTbl.LevelLimit));
    } else {
        stringVect.push_back("No class level Limit unless multiclass");
    }

    stringVect.push_back("Initial Number of Weapons: " + std::to_string(_initNumWeap));
    stringVect.push_back("Non Proficiency Penalty: " + std::to_string(_nonProfPenalty));
    stringVect.push_back("Added Proficiency in Weapons Per Level: 1/" + std::to_string(_addedWeapLvlDen));

    stringVect.push_back("Bonus to hit while sneak/backstab: +" +  std::to_string(_surpriseAtk));
    stringVect.push_back("Pick Pockets: " + std::to_string(_thiefTbl.pickPockets) + "%");
    stringVect.push_back("Open Locks: " + std::to_string(_thiefTbl.openLocks) + "%");
    stringVect.push_back("Find/Remove Traps: " + std::to_string(_thiefTbl.findRemoveTraps) + "%");
    stringVect.push_back("Move silently: " + std::to_string(_thiefTbl.moveSilently) + "%");
    stringVect.push_back("Hide in Shadows: " + std::to_string(_thiefTbl.hideInShadows) + "%");
    stringVect.push_back("Hear Noise: " + std::to_string(_thiefTbl.hearNoise) + "%");
    stringVect.push_back("Climb Walls: " + std::to_string(_thiefTbl.climbWalls) + "%");
    stringVect.push_back("Read Languages: " + std::to_string(_thiefTbl.readLanguages) + "%");  

    return stringVect;
}

void Thief::setRaceMod(RACE race)
{
    switch(race){
        case DWARF:
            _thiefTbl.openLocks += 10;
            _thiefTbl.findRemoveTraps += 15;
            _thiefTbl.climbWalls -= 10;
            if(_thiefTbl.readLanguages > 0){
                _thiefTbl.readLanguages -= 5; 
            }
            break;
        case ELF:
            _thiefTbl.pickPockets += 5;
            _thiefTbl.openLocks -= 5;
            _thiefTbl.moveSilently += 5;
            _thiefTbl.hideInShadows += 10;
            _thiefTbl.hearNoise += 5;
            break;
        case GNOME:
            _thiefTbl.openLocks += 5;
            _thiefTbl.findRemoveTraps += 10;
            _thiefTbl.moveSilently += 5;
            _thiefTbl.hideInShadows += 5;
            _thiefTbl.hearNoise += 10;
            _thiefTbl.climbWalls -= 15;
            break;
        case HALF_ELF:
            _thiefTbl.pickPockets += 10;
            _thiefTbl.hideInShadows += 5;
            break;
        case HALFLING:
            _thiefTbl.pickPockets += 5;
            _thiefTbl.openLocks += 5;
            _thiefTbl.findRemoveTraps += 5;
            _thiefTbl.moveSilently += 10;
            _thiefTbl.hideInShadows += 15;
            _thiefTbl.hearNoise += 5;
            _thiefTbl.climbWalls -= 15;
            if(_thiefTbl.readLanguages > 0){
                _thiefTbl.readLanguages -= 5; 
            }
            break;
        case HALF_ORC:
            _thiefTbl.pickPockets -= 5;
            _thiefTbl.openLocks += 5;
            _thiefTbl.findRemoveTraps += 5;
            _thiefTbl.hearNoise += 5;
            _thiefTbl.climbWalls += 5;
            if(_thiefTbl.readLanguages > 0){
                _thiefTbl.readLanguages -= 10; 
            }
            break;
    }
}

void Thief::setThiefSkills(RACE inRace, unsigned level){
    
    switch(level){
        case 17:
            _thiefTbl.pickPockets = 125;
            _thiefTbl.openLocks = 99;
            _thiefTbl.findRemoveTraps = 99;
            _thiefTbl.moveSilently = 99;
            _thiefTbl.hideInShadows = 99;
            _thiefTbl.hearNoise = 55;
            _thiefTbl.climbWalls = 99.7;
            _thiefTbl.readLanguages = 80;
            break;
        case 16:
            _thiefTbl.pickPockets = 125;
            _thiefTbl.openLocks = 97;
            _thiefTbl.findRemoveTraps = 95;
            _thiefTbl.moveSilently = 99;
            _thiefTbl.hideInShadows = 99;
            _thiefTbl.hearNoise = 50;
            _thiefTbl.climbWalls = 99.6;
            _thiefTbl.readLanguages = 80;
            break;
        case 15:
            _thiefTbl.pickPockets = 115;
            _thiefTbl.openLocks = 92;
            _thiefTbl.findRemoveTraps = 90;
            _thiefTbl.moveSilently = 99;
            _thiefTbl.hideInShadows = 99;
            _thiefTbl.hearNoise = 50;
            _thiefTbl.climbWalls = 99.5;
            _thiefTbl.readLanguages = 75;
            break;
        case 14:
            _thiefTbl.pickPockets = 110;
            _thiefTbl.openLocks = 87;
            _thiefTbl.findRemoveTraps = 85;
            _thiefTbl.moveSilently = 99;
            _thiefTbl.hideInShadows = 93;
            _thiefTbl.hearNoise = 40;
            _thiefTbl.climbWalls = 99.4;
            _thiefTbl.readLanguages = 70;
            break;
        case 13:
            _thiefTbl.pickPockets = 105;
            _thiefTbl.openLocks = 82;
            _thiefTbl.findRemoveTraps = 80;
            _thiefTbl.moveSilently = 99;
            _thiefTbl.hideInShadows = 85;
            _thiefTbl.hearNoise = 40;
            _thiefTbl.climbWalls = 99.3;
            _thiefTbl.readLanguages = 65;
            break;
        case 12:
            _thiefTbl.pickPockets = 100;
            _thiefTbl.openLocks = 77;
            _thiefTbl.findRemoveTraps = 75;
            _thiefTbl.moveSilently = 94;
            _thiefTbl.hideInShadows = 77;
            _thiefTbl.hearNoise = 35;
            _thiefTbl.climbWalls = 99.2;
            _thiefTbl.readLanguages = 60;
            break;
        case 11:
            _thiefTbl.pickPockets = 90;
            _thiefTbl.openLocks = 72;
            _thiefTbl.findRemoveTraps = 70;
            _thiefTbl.moveSilently = 86;
            _thiefTbl.hideInShadows = 70;
            _thiefTbl.hearNoise = 35;
            _thiefTbl.climbWalls = 99.1;
            _thiefTbl.readLanguages = 55;
            break;
        case 10:
            _thiefTbl.pickPockets = 80;
            _thiefTbl.openLocks = 67;
            _thiefTbl.findRemoveTraps = 65;
            _thiefTbl.moveSilently = 78;
            _thiefTbl.hideInShadows = 63;
            _thiefTbl.hearNoise = 30;
            _thiefTbl.climbWalls = 99.0;
            _thiefTbl.readLanguages = 50;
            break;
        case 9:
            _thiefTbl.pickPockets = 70;
            _thiefTbl.openLocks = 62;
            _thiefTbl.findRemoveTraps = 60;
            _thiefTbl.moveSilently = 70;
            _thiefTbl.hideInShadows = 56;
            _thiefTbl.hearNoise = 30;
            _thiefTbl.climbWalls = 98.0;
            _thiefTbl.readLanguages = 45;
            break;
        case 8:
            _thiefTbl.pickPockets = 65;
            _thiefTbl.openLocks = 57;
            _thiefTbl.findRemoveTraps = 55;
            _thiefTbl.moveSilently = 62;
            _thiefTbl.hideInShadows = 49;
            _thiefTbl.hearNoise = 25;
            _thiefTbl.climbWalls = 96.0;
            _thiefTbl.readLanguages = 40;
            break;
        case 7:
            _thiefTbl.pickPockets = 60;
            _thiefTbl.openLocks = 52;
            _thiefTbl.findRemoveTraps = 50;
            _thiefTbl.moveSilently = 55;
            _thiefTbl.hideInShadows = 43;
            _thiefTbl.hearNoise = 25;
            _thiefTbl.climbWalls = 94.0;
            _thiefTbl.readLanguages = 35;
            break;
        case 6:
            _thiefTbl.pickPockets = 55;
            _thiefTbl.openLocks = 47;
            _thiefTbl.findRemoveTraps = 45;
            _thiefTbl.moveSilently = 47;
            _thiefTbl.hideInShadows = 37;
            _thiefTbl.hearNoise = 20;
            _thiefTbl.climbWalls = 92.0;
            _thiefTbl.readLanguages = 30;
            break;
        case 5:
            _thiefTbl.pickPockets = 50;
            _thiefTbl.openLocks = 42;
            _thiefTbl.findRemoveTraps = 40;
            _thiefTbl.moveSilently = 40;
            _thiefTbl.hideInShadows = 31;
            _thiefTbl.hearNoise = 20;
            _thiefTbl.climbWalls = 90.0;
            _thiefTbl.readLanguages = 25;
            break;
        case 4:
            _thiefTbl.pickPockets = 45;
            _thiefTbl.openLocks = 37;
            _thiefTbl.findRemoveTraps = 35;
            _thiefTbl.moveSilently = 33;
            _thiefTbl.hideInShadows = 25;
            _thiefTbl.hearNoise = 15;
            _thiefTbl.climbWalls = 88.0;
            _thiefTbl.readLanguages = 20;
            break;
        case 3:
            _thiefTbl.pickPockets = 40;
            _thiefTbl.openLocks = 33;
            _thiefTbl.findRemoveTraps = 30;
            _thiefTbl.moveSilently = 27;
            _thiefTbl.hideInShadows = 20;
            _thiefTbl.hearNoise = 15;
            _thiefTbl.climbWalls = 87.0;
            _thiefTbl.readLanguages = 0;
            break;
        case 2:
            _thiefTbl.pickPockets = 35;
            _thiefTbl.openLocks = 29;
            _thiefTbl.findRemoveTraps = 25;
            _thiefTbl.moveSilently = 21;
            _thiefTbl.hideInShadows = 15;
            _thiefTbl.hearNoise = 10;
            _thiefTbl.climbWalls = 86.0;
            _thiefTbl.readLanguages = 0;
            break;
        case 1:
            _thiefTbl.pickPockets = 30;
            _thiefTbl.openLocks = 25;
            _thiefTbl.findRemoveTraps = 20;
            _thiefTbl.moveSilently = 15;
            _thiefTbl.hideInShadows = 10;
            _thiefTbl.hearNoise = 10;
            _thiefTbl.climbWalls = 85.0;
            _thiefTbl.readLanguages = 0;
            break;
    }
    setRaceMod(inRace);
}

Assassin::Assassin(RACE inRace, unsigned inLevel)
{
    _classTbl.HitDieType = 6;
    _classTbl.MaxHitDie = 15;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = 14;
    _initNumWeap = 3;
    _nonProfPenalty = -2;
    _addedWeapLvlDen = 4;
    setThiefSkills(inRace, inLevel);
    //listClassSkills();
}

Assassin::~Assassin(){
    //std::cout << "Assasin Destructor" << std::endl; 
}

Monk::Monk(RACE inRace, unsigned inLevel){
    _classTbl.HitDieType = 4; // starts 2d4
    _classTbl.MaxHitDie = 17;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = 17;
    _initNumWeap = 1;
    _nonProfPenalty = -3;
    _addedWeapLvlDen = 2;
    //listClassSkills();
}

unsigned Monk::generateGold()
{
    return (rollDice(4, false) + rollDice(4, false) + rollDice(4, false) + rollDice(4, false) + rollDice(4, false));
}

Monk::~Monk(){
    //std::cout << "Assasin Destructor" << std::endl; 
}
