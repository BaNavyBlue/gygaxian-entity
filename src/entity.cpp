/*
    Antone Bajor 2023
*/
#include "entity.h"


Entity::Entity(stats inStats[2], std::string name, SEX sex, RACE race, std::vector<CHAR_CLASS> chrClass, ALIGNMENT align)
{
    _name = name;
    _sex = sex;
    _alignment = align;
    _stats = inStats[0];
    _modStats = inStats[1];
    _race = race;
    _chrClass = chrClass;
    _experience.push_back(0);
    checkRaceStats(_race);
    setStrenTbl();
    _weightAllowedGP += _strTbl.weightAllowMod;
    setIntTbl();
    setPossLang();
    setBaseLanguages();
    setWisTbl();
    setDexTbl();
    if(_chrClass[0] == THIEF || _chrClass[0] == ASSASSIN){
        setDexThief();
    }
    setConsTbl();
    setCharTbl();
    setRaceSkillType();
    setChrClassSkill(_chrClass[0]);
    if(_chrSkills.size() < 2){
        _money.gold = _chrSkills[0]->generateGold();
    }
    _totalWeightGP += _money.gold;

    // First HP roll for Ranger and Monk is double.
    if(_chrClass[0] == RANGER || _chrClass[0] == MONK){
        _hitPointsBase = _curHitPoints = _chrSkills[0]->rollHP() + _chrSkills[0]->rollHP() + _consTbl.hpAdj;
    } else {
        _hitPointsBase = _curHitPoints = _chrSkills[0]->rollHP() + _consTbl.hpAdj;
    }
    //unsigned str_mod = 0;

    // Armor Mod;
    if(_chrClass[0] != MONK){
        _armorRating += _dexTbl.defenseAdj;
    }
}

Entity::~Entity()
{
    ///delete _raceSkills;
}

void Entity::setRaceSkillType()
{
    switch(_race){
        case DWARF:
            _raceSkills = std::make_shared<Dwarf>(_stats);
            //_raceSkills->getch_n(();
            break;
        case ELF:
            _raceSkills = std::make_shared<Elf>(_stats);
            //_raceSkills->getch_n(();
            break;
        case GNOME:  
            _raceSkills = std::make_shared<Gnome>(_stats);
            //_raceSkills->getch_n(();
            break;
        case HALF_ELF:
            _raceSkills = std::make_shared<HalfElf>(_stats);
            //_raceSkills->getch_n(();
            break;
        case HALFLING:
            _raceSkills = std::make_shared<Halfling>(_stats);
            //_raceSkills->getch_n(();
            break;
        case HALF_ORC:
            _raceSkills = std::make_shared<HalfOrc>(_stats);
            //_raceSkills->getch_n(();
            break;
        case HUMAN:
            _raceSkills = std::make_shared<Human>(_stats);
            //_raceSkills->getch_n(();
            break;
        default:
            // _raceSkills = std::make_shared<RACE_SKILLS>(_stats);
            // _raceSkills->getch_n(();
            break;
    }
}

void Entity::setChrClassSkill(CHAR_CLASS inClass)
{
    switch(inClass){
        case CLERIC:
            _chrSkills.push_back(std::make_shared<Cleric>());
            break;
        case DRUID:
            _chrSkills.push_back(std::make_shared<Druid>());
            break;
        case FIGHTER:
            _chrSkills.push_back(std::make_shared<Fighter>());
            break;
        case PALADIN:
            _chrSkills.push_back(std::make_shared<Paladin>());
            break;
        case RANGER:
            _chrSkills.push_back(std::make_shared<Ranger>());
            break;
        case MAGIC_USER:
            _chrSkills.push_back(std::make_shared<MagicUser>());
            break;
        case ILLUSIONIST:
            _chrSkills.push_back(std::make_shared<Illusionist>());
            break;
        case THIEF:
            _chrSkills.push_back(std::make_shared<Thief>(_race, _level));
            if(std::find(_languages.begin(), _languages.end(), THIEVES_CANT) != _languages.end()){

            } else {
                _languages.push_back(THIEVES_CANT);
                //std::cout << "Thieves Cant added" << std::endl;
            }
            break;
        case ASSASSIN:
            _chrSkills.push_back(std::make_shared<Assassin>(_race, _level));
                if(std::find(_languages.begin(), _languages.end(), THIEVES_CANT) != _languages.end()){

            } else {
                _languages.push_back(THIEVES_CANT);
                //std::cout << "Thieves Cant added" << std::endl;
            }
            break;
        case MONK:
            _chrSkills.push_back(std::make_shared<Monk>(_race, _level));
            break;
        default:
            _chrSkills.push_back(std::make_shared<Cleric>());
            break;
    }
}

void Entity::setStrenTbl()
{
    switch(_modStats.strength){
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
            if(_modStats.excStren > 0 && isFighter()){
                if(_modStats.excStren < 51){
                    _strTbl.hitProb = 1;
                    _strTbl.damageAdj = 2;
                    _strTbl.weightAllowMod = 1000;
                    _strTbl.openDoors = 3;
                    _strTbl.bendBarsLiftGatesPer = 20;
                } else if(_modStats.excStren < 76){
                    _strTbl.hitProb = 2;
                    _strTbl.damageAdj = 3;
                    _strTbl.weightAllowMod = 1250;
                    _strTbl.openDoors = 4;
                    _strTbl.bendBarsLiftGatesPer = 25;
                } else if(_modStats.excStren < 91){
                    _strTbl.hitProb = 2;
                    _strTbl.damageAdj = 4;
                    _strTbl.weightAllowMod = 1500;
                    _strTbl.openDoors = 4;
                    _strTbl.bendBarsLiftGatesPer = 30;
                } else if(_modStats.excStren < 100){
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
                _stats.excStren = _modStats.excStren = 0;
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
    switch(_modStats.intelligence){
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
            if(_modStats.intelligence > 19){
            _intTbl.chanceToKnowPer = 95;
            _intTbl.minumumSpellsPerLevel = 10;
            _intTbl.maxiumSpellsPerlevel = 255;
            break; 
            }            

    }  
}

 void Entity::setWisTbl(){

    switch(_modStats.wisdom){
        case 3:
            _wisTbl.magicAttackAdj = -3;
            break;
        case 4:
            _wisTbl.magicAttackAdj = -2;
            break;
        case 5:
        case 6:
        case 7:
            _wisTbl.magicAttackAdj = -1;
        case 8:
        case 9:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 0;
            _wisTbl.spellFailPer = 20;
            break;
        case 10:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 0;
            _wisTbl.spellFailPer = 15;
            break;
        case 11:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 0;
            _wisTbl.spellFailPer = 10;
            break;
        case 12:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 0;
            _wisTbl.spellFailPer = 5;
            break;
        case 13:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 1;
            _wisTbl.spellFailPer = 0;
            break;
        case 14:
            _wisTbl.magicAttackAdj = 0;
            _wisTbl.spellBonus = 1;
            _wisTbl.spellFailPer = 0;
            break;
        case 15:
            _wisTbl.magicAttackAdj = 1;
            _wisTbl.spellBonus = 2;
            _wisTbl.spellFailPer = 0;
            break;
        case 16:
            _wisTbl.magicAttackAdj = 2;
            _wisTbl.spellBonus = 2;
            _wisTbl.spellFailPer = 0;
            break;
        case 17:
            _wisTbl.magicAttackAdj = 3;
            _wisTbl.spellBonus = 3;
            _wisTbl.spellFailPer = 0;
            break;
        case 18:
            _wisTbl.magicAttackAdj = 4;
            _wisTbl.spellBonus = 4;
            _wisTbl.spellFailPer = 0;
            break;
        default:
            break;
    }

 }

void Entity::setDexTbl()
{
    switch(_modStats.dexterity){
        case 3:
            _dexTbl.reactAttkAdj = -3;
            _dexTbl.defenseAdj = 4;
            break;
        case 4:
            _dexTbl.reactAttkAdj = -2;
            _dexTbl.defenseAdj = 3;
            break;
        case 5:
            _dexTbl.reactAttkAdj = -1;
            _dexTbl.defenseAdj = 2;
            break;
        case 6:
            _dexTbl.reactAttkAdj = 0;
            _dexTbl.defenseAdj = 1;
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            _dexTbl.reactAttkAdj = 0;
            _dexTbl.defenseAdj = 0;
            break;
        case 15:
            _dexTbl.reactAttkAdj = 0;
            _dexTbl.defenseAdj = -1; // lower armorclass better
            break;
        case 16:
            _dexTbl.reactAttkAdj = 1;
            _dexTbl.defenseAdj = -2;
            break;
        case 17:
            _dexTbl.reactAttkAdj = 2;
            _dexTbl.defenseAdj = -3;
            break;
        case 18:
            _dexTbl.reactAttkAdj = 3;
            _dexTbl.defenseAdj = -4;
            break;
        default:
            break;
    }
}

void Entity::setPossLang()
{
    switch(_modStats.intelligence){
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

void Entity::setDexThief()
{
    switch(_modStats.dexterity){
        case 9:
            _dexThief.pickPocketPer = -15;
            _dexThief.openLocks = -10;
            _dexThief.locRemTraps = -10;
            _dexThief.movSilent = -20;
            _dexThief.hideInShadows = -10;
            break;
        case 10:
             _dexThief.pickPocketPer = -10;
            _dexThief.openLocks = -5;
            _dexThief.locRemTraps = -10;
            _dexThief.movSilent = -15;
            _dexThief.hideInShadows = -5;
            break;           
        case 11:
            _dexThief.pickPocketPer = -5;
            _dexThief.openLocks = 0;
            _dexThief.locRemTraps = -5;
            _dexThief.movSilent = -10;
            _dexThief.hideInShadows = 0;
            break;
        case 12:
            _dexThief.pickPocketPer = 0;
            _dexThief.openLocks = 0;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = -5;
            _dexThief.hideInShadows = 0;
            break;
        case 13:
            _dexThief.pickPocketPer = 0;
            _dexThief.openLocks = 0;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = 0;
            _dexThief.hideInShadows = 0;
            break;
        case 14:
            _dexThief.pickPocketPer = 0;
            _dexThief.openLocks = 0;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = 0;
            _dexThief.hideInShadows = 0;
            break;
        case 15:
            _dexThief.pickPocketPer = 0;
            _dexThief.openLocks = 0;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = 0;
            _dexThief.hideInShadows = 0;
            break;
        case 16:
            _dexThief.pickPocketPer = 0;
            _dexThief.openLocks = 5;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = 0;
            _dexThief.hideInShadows = 0;
            break;
        case 17:
            _dexThief.pickPocketPer = 5;
            _dexThief.openLocks = 10;
            _dexThief.locRemTraps = 0;
            _dexThief.movSilent = 5;
            _dexThief.hideInShadows = 5;
            break;
        case 18:
            _dexThief.pickPocketPer = 10;
            _dexThief.openLocks = 15;
            _dexThief.locRemTraps = 5;
            _dexThief.movSilent = 10;
            _dexThief.hideInShadows = 10;
            break;
        default:
            _dexThief.pickPocketPer = -15;
            _dexThief.openLocks = -10;
            _dexThief.locRemTraps = -10;
            _dexThief.movSilent = -20;
            _dexThief.hideInShadows = -10;
            break;
    }
}

void Entity::setConsTbl()
{
    switch(_modStats.constitution){
        case 3:
            _consTbl.hpAdj = -2;
            _consTbl.sysShockSurPer = 35;
            _consTbl.resurSurvPer = 40;
            break;
        case 4:
            _consTbl.hpAdj = -1;
            _consTbl.sysShockSurPer = 40;
            _consTbl.resurSurvPer = 45;
            break;
        case 5:
            _consTbl.hpAdj = -1;
            _consTbl.sysShockSurPer = 45;
            _consTbl.resurSurvPer = 50;
            break;
        case 6:
            _consTbl.hpAdj = -1;
            _consTbl.sysShockSurPer = 50;
            _consTbl.resurSurvPer = 55;
            break;
        case 7:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 55;
            _consTbl.resurSurvPer = 60;
            break;
        case 8:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 60;
            _consTbl.resurSurvPer = 65;
            break;
        case 9:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 65;
            _consTbl.resurSurvPer = 70;
            break;
        case 10:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 70;
            _consTbl.resurSurvPer = 75;
            break;
        case 11:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 75;
            _consTbl.resurSurvPer = 80;
            break;
        case 12:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 80;
            _consTbl.resurSurvPer = 85;
            break;
        case 13:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 85;
            _consTbl.resurSurvPer = 90;
            break;
        case 14:
            _consTbl.hpAdj = 0;
            _consTbl.sysShockSurPer = 88;
            _consTbl.resurSurvPer = 92;
            break;
        case 15:
            _consTbl.hpAdj = 1;
            _consTbl.sysShockSurPer = 91;
            _consTbl.resurSurvPer = 94;
            break;
        case 16:
            _consTbl.hpAdj = 2;
            _consTbl.sysShockSurPer = 95;
            _consTbl.resurSurvPer = 96;
            break;
        case 17:
            if(_chrClass[0] == FIGHTER || _chrClass[0] == PALADIN || _chrClass[0] == RANGER){
                _consTbl.hpAdj = 3;                
            } else {
            _consTbl.hpAdj = 2;
            }

            _consTbl.sysShockSurPer = 97;
            _consTbl.resurSurvPer = 98;
            break;
        case 18:
            if(_chrClass[0] == FIGHTER || _chrClass[0] == PALADIN || _chrClass[0] == RANGER){
                _consTbl.hpAdj = 4;                
            } else {
            _consTbl.hpAdj = 2;
            }

            _consTbl.sysShockSurPer = 99;
            _consTbl.resurSurvPer = 100;
            break;
    }
}

void Entity::setCharTbl()
{
    switch(_modStats.charisma){
        case 3:
            _charTbl.maxHenchMen = 1;
            _charTbl.loyaltyBasePer = -30;
            _charTbl.reactAdjustPer = -25;
            break;
        case 4:
            _charTbl.maxHenchMen = 1;
            _charTbl.loyaltyBasePer = -25;
            _charTbl.reactAdjustPer = -20;
            break;
        case 5:
            _charTbl.maxHenchMen = 2;
            _charTbl.loyaltyBasePer = -20;
            _charTbl.reactAdjustPer = -15;
            break;
        case 6:
            _charTbl.maxHenchMen = 2;
            _charTbl.loyaltyBasePer = -15;
            _charTbl.reactAdjustPer = -10;
            break;
        case 7:
            _charTbl.maxHenchMen = 3;
            _charTbl.loyaltyBasePer = -10;
            _charTbl.reactAdjustPer = -05;
            break;
        case 8:
            _charTbl.maxHenchMen = 3;
            _charTbl.loyaltyBasePer = -05;
            _charTbl.reactAdjustPer = 0;
            break;
        case 9:
        case 10:
        case 11:
            _charTbl.maxHenchMen = 4;
            _charTbl.loyaltyBasePer = 0;
            _charTbl.reactAdjustPer = 0;
            break;
        case 12:
            _charTbl.maxHenchMen = 5;
            _charTbl.loyaltyBasePer = 0;
            _charTbl.reactAdjustPer = 0;
            break;
        case 13:
            _charTbl.maxHenchMen = 5;
            _charTbl.loyaltyBasePer = 0;
            _charTbl.reactAdjustPer = 5;
            break;
        case 14:
            _charTbl.maxHenchMen = 6;
            _charTbl.loyaltyBasePer = 5;
            _charTbl.reactAdjustPer = 10;
            break;
        case 15:
            _charTbl.maxHenchMen = 7;
            _charTbl.loyaltyBasePer = 15;
            _charTbl.reactAdjustPer = 15;
            break;
        case 16:
            _charTbl.maxHenchMen = 8;
            _charTbl.loyaltyBasePer = 20;
            _charTbl.reactAdjustPer = 25;
            break;
        case 17:
            _charTbl.maxHenchMen = 10;
            _charTbl.loyaltyBasePer = 30;
            _charTbl.reactAdjustPer = 30;
            break;
        case 18:
            _charTbl.maxHenchMen = 15;
            _charTbl.loyaltyBasePer = 40;
            _charTbl.reactAdjustPer = 35;
            break;
    }
}

void Entity::setMeleeAttkRnd(CHAR_CLASS inClass)
{
    switch(inClass){
        case FIGHTER:
        case PALADIN:
            if(_level < 7){
                _meleeAttkRound = 1.0;
            } else if(_level < 13){
                _meleeAttkRound = 3 / 2;
            } else {
                _meleeAttkRound = 2.0;
            }
            break;
        case RANGER:
            if(_level < 8){
                _meleeAttkRound = 1.0;
            } else if(_level < 15){
                _meleeAttkRound = 3 / 2;
            } else {
                _meleeAttkRound = 2.0;
            }
            break;
        default:
            _meleeAttkRound = 1.0;
            break;
    }
}

float Entity::getMeleeAttkRnd()
{
    return _meleeAttkRound;
}

stats Entity::getStats()
{
    return _stats;
}


stats Entity::getModStats()
{
    return _modStats;
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
                //std::cout << "Human Female Exceptional Strength Capped at 51" << std::endl;
                _stats.excStren = _modStats.excStren = 51;
            }
            _race = race;
            return true;
        case ELF:
            // Stat Limitation Check
            if(_stats.intelligence < 8){
                //std::cout << "Elf can not have intelligence bellow 8" << std::endl;
                return false;
            }
            if(_stats.dexterity + 1 < 7){
                //std::cout << "Elf can not have dexterity bellow 7" << std::endl;
                return false;
            }
            if(_stats.constitution - 1 < 6){
                //std::cout << "Elf can not have constitution bellow 6" << std::endl;
                return false;
            }
            if(_stats.charisma < 8){
                //std::cout << "Elf can not have charisma bellow 8" << std::endl;
                return false;
            }
            if(_sex == FEMALE && _stats.strength > 16){
                //std::cout << "Elf Female Strength Capped at 16" << std::endl;
                _stats.strength = _modStats.strength = 16;
            }
            // Apply Standard Elf Modifiers
            _stats.constitution--; _modStats.constitution--;
            _stats.dexterity++; _modStats.dexterity++;
            _race = race;
            return true;
        case HALF_ORC:
            if(_stats.strength + 1 < 6){
                //std::cout << "Half-Orc Strength bellow 6" << std::endl;
                return false;
            }

            if(_stats.constitution + 1 < 13){
                //std::cout << "Half-Orc constitution bellow 13" << std::endl;
                return false;
            }

            if(_stats.intelligence > 17){
                //std::cout << "Half-Orc Intelligence being set to cap 17" << std::endl;
                _stats.intelligence = _modStats.intelligence = 17;
            }

            if(_stats.dexterity > 17){
                //std::cout << "Half-Orc Dexterity being set to cap 17" << std::endl;
                _stats.dexterity = _modStats.dexterity = 17;
            }

            if(_stats.wisdom > 14){
                //std::cout << "Half-Orc Wisdom being set to cap 14" << std::endl;
                _stats.wisdom = _modStats.wisdom = 14;
            }

            if(_stats.charisma - 2 > 12){
                //std::cout << "Half-Orc Charisma being set to cap 12" << std::endl;
                _stats.charisma = _modStats.charisma = 12;
            } else if(_stats.charisma - 2 < 3) {
                //std::cout << "Half-Orc Charisma minimum being set to 3" << std::endl;
                _stats.charisma = _modStats.charisma = 3;            
            } else {
                _stats.charisma -= 2; 
                _modStats.charisma -=2;
            }

            if(_stats.strength + 1 > 18){
                //std::cout << "Half-Orc strength set to cap 18" << std::endl;
                _stats.strength = _modStats.strength = 18;
            } else {
                _stats.strength++; _stats.strength++;
            }

            _stats.constitution++; _modStats.constitution++;
            _race = race;
            return true;
        case DWARF:
            if(_stats.strength < 8){
                //std::cout << "Dwarf strength bellow 8" << std::endl;
                return false;            
            }

            if(_stats.constitution + 1 < 12){
                //std::cout << "Dwarf constitution bellow 12" << std::endl;
                return false;            
            }
            
            if(_stats.strength > 17 && _sex == FEMALE){
                //std::cout << "Female Dwarf strength cap 17" << std::endl;
                _stats.strength = _modStats.strength = 17;
            }

            if(_stats.dexterity > 17){
                //std::cout << "Dwarf dexterity cap 17" << std::endl;
                _stats.dexterity = _modStats.dexterity = 17;            
            }

            if(_stats.charisma - 1 > 16){
                //std::cout << "Dwarf charisma cap 16" << std::endl;
                _stats.charisma = _modStats.charisma = 16;
            } else {
                _stats.charisma--; _modStats.charisma--;
            }

            _stats.constitution++; _modStats.constitution++;
            _race = race;
            return true;
        case HALFLING:
            if(_stats.strength - 1 < 6){
                //std::cout << "Halfling strength bellow 6" << std::endl;
                return false;                  
            }

            if(_stats.intelligence < 6){
                //std::cout << "Halfling intelligence bellow 6" << std::endl;
                return false;                
            }

            if(_stats.dexterity + 1 < 8){
                //std::cout << "Halfling dexterity bellow 8" << std::endl;
                return false;
            }

            if(_stats.constitution < 10){
                //std::cout << "Halfling constitution bellow 10" << std::endl;
                return false;
            }

            if(_stats.strength - 1 > 14 && _sex == FEMALE){
                //std::cout << "Female Halfling strength cap 14" << std::endl;
                _stats.strength = _modStats.strength = 14;
                _stats.excStren = _modStats.excStren = 0;
            } else {
                _stats.strength--; _modStats.strength--;
            }                    

            if(_stats.wisdom > 17){
                //std::cout << "Halfling wisdom cap 17" << std::endl;
                _stats.wisdom = _modStats.wisdom = 17;
            }

            _stats.dexterity++; _modStats.dexterity++;
            _race = race;
            return true;
        case HALF_ELF:
            if(_stats.intelligence < 4){
                //std::cout << "Intelligence bellow 4" << std::endl;
                return false;
            }

            if(_stats.dexterity < 6){
                //std::cout << "Dexterity bellow 6" << std::endl;
                return false;
            }

            if(_stats.constitution < 6){
                //std::cout << "Constitution bellow 6" << std::endl;
                return false;
            }

            if(_stats.excStren > 90){
                //std::cout << "Half-Elf exceptional strength cap 90" << std::endl;
                _stats.excStren = _modStats.excStren = 90;
            }

            if(_stats.strength > 17 && _sex == FEMALE){
                //std::cout << "Female Half-Elf strength cap 17" << std::endl;
                _stats.strength = _modStats.strength = 17;
            }

            _race = race;
            return true;
        case GNOME:
            if(_stats.strength < 6){
                //std::cout << "Strength bellow 6" << std::endl;
                return false;
            }

            if(_stats.intelligence < 7){
                //std::cout << "Intelligence bellow 7" << std::endl;
                return false;
            }

            if(_stats.constitution < 8){
                //std::cout << "Constitution bellow 8" << std::endl;
                return false;
            }

            if(_stats.strength > 15 && _sex == FEMALE){
                //std::cout << "Female Gnome strength cap 15" << std::endl;
                _stats.strength = _modStats.strength = 15;
            }            

            _race = race;
            return true;
    }
}

// void Entity::reRollStats()
// {
//     do{
//         _stats.strength = _modStats.strength = bestThree();
//         if(_stats.strength > 17){
//             _stats.excStren = _modStats.excStren = rollDice(10, true) + rollDice(10, true)*10 + 1;
//         }
//         _stats.intelligence = _modStats.intelligence = bestThree();
//         _stats.wisdom = _modStats.wisdom = bestThree();
//         _stats.charisma = _stats.raceCharisma = _modStats.charisma = _modStats.raceCharisma = bestThree();
//         _stats.dexterity = _modStats.dexterity = bestThree();
//         _stats.constitution = _modStats.constitution = bestThree();
//     }while(!rollFailure(_stats));  
// }

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

void Entity::setClass(CHAR_CLASS inClass)
{
    _chrClass.push_back(inClass);
    setStrenTbl();
    setIntTbl();
    setPossLang();
    setBaseLanguages();
    setWisTbl();
    setDexTbl();
    _armorRating += _dexTbl.defenseAdj;
    if(_chrClass[0] == THIEF || _chrClass[0] == ASSASSIN){
        setDexThief();
    }
    setConsTbl();
    setRaceSkillType();
    setChrClassSkill(inClass);
    //std::cout << "_chrSkills.size(): " << _chrSkills.size() << std::endl;
    if(_chrSkills.size() < 2){
        _money.gold = _chrSkills[0]->generateGold();
    }
}

void Entity::setBaseLanguages(){
    switch(_race){
        case HUMAN:
            _languages.insert(_languages.end(), {COMMON_L});
            break;
        case ELF:
            _languages.insert(_languages.end(), {COMMON_L, ELVISH, GNOMISH, HALFLING_L, GOBLIN_L, HOBGOBLIN_L, ORCISH, GNOLL});
            break;        
        case GNOME:
            _languages.insert(_languages.end(), {COMMON_L, GNOMISH, DWARVISH, HALFLING_L, GOBLIN_L, KOBOLD, BURROWING_ANIMALS});
            break;
        case HALF_ELF:
            _languages.insert(_languages.end(), {COMMON_L, ELVISH, GNOMISH, HALFLING_L, GOBLIN_L, HOBGOBLIN_L, ORCISH, GNOLL});
            break;
        case HALFLING:
            _languages.insert(_languages.end(), {COMMON_L, HALFLING_L, DWARVISH, ELVISH, GNOMISH,GOBLIN_L, ORCISH});
            break;
        case HALF_ORC:
            _languages.insert(_languages.end(), {COMMON_L, ORCISH});
            break;
        case DWARF:
            _languages.insert(_languages.end(), {COMMON_L, DWARVISH, GNOMISH, GOBLIN_L, KOBOLD, ORCISH});
            break;
    } 
}

strengthTable Entity::getStrTbl()
{
    return _strTbl;
}

intelligenceTable Entity::getIntTbl()
{
    return _intTbl;
}

wisdomTable Entity::getWisTbl()
{
    return _wisTbl;
}

dexterityTable Entity::getDexTbl()
{
    return _dexTbl;
}

dexThieves Entity::getDexTheif()
{
    return _dexThief;
}

constitutionTable Entity::getConsTbl()
{
    return _consTbl;
}

charismaTable Entity::getCharTbl()
{
    return _charTbl;
}

std::vector<LANGUAGE> Entity::getLanguages()
{
    return _languages;
}

money Entity::getMoney()
{
    return _money;
}

unsigned Entity::getLevel()
{
    return _level;
}

unsigned Entity::getMaxHP()
{
    return _hitPointsBase;
}

unsigned Entity::getCurHP()
{
    return _curHitPoints;
}

unsigned Entity::getWeightAllowed()
{
    return _weightAllowedGP;
}

unsigned Entity::getWeightCarried()
{
    return _totalWeightGP;
}

float Entity::getEquivalentGP()
{
    return _money.gold + static_cast<float>(_money.copper) / 200 +  static_cast<float>(_money.silver) / 20 + static_cast<float>(_money.electrum) / 2 + _money.platinum * 5;
}

short int Entity::getArmorRating()
{
    return _armorRating;
}

std::vector<unsigned> Entity::getExperience()
{
    return _experience;
}

std::shared_ptr<RACE_SKILLS> Entity::getRaceSkills()
{
    return _raceSkills;
}

std::vector<std::shared_ptr<CHR_CLASS_SKILLS>> Entity::getCharClassSkills()
{
    return _chrSkills;
}

bool Entity::isFighter(){
    for(unsigned i = 0; i < _chrClass.size(); i++){
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
    outTxt += "        \"maxHP\":" + std::to_string(_hitPointsBase) + ",\r\n";
    outTxt += "        \"curHP\":" + std::to_string(_curHitPoints) + ",\r\n";
    outTxt += "        \"weightAllow\":" + std::to_string(_weightAllowedGP) + ",\r\n";
    outTxt += "        \"totalWeight\":" + std::to_string(_totalWeightGP) + ",\r\n";
    outTxt += "        \"armorRating\":" + std::to_string(_armorRating) + ",\r\n";
    outTxt += "        \"class\":{\r\n";// + std::to_string(_chrClass[0]) + ",\r\n"; // vector for multiclass
    outTxt += "            \"count\":" + std::to_string(_chrClass.size()) + ",\r\n";
    outTxt += "            \"index\":{\r\n";
    for(std::size_t i = 0; i < _chrClass.size(); ++i){
        outTxt += "                \"" + std::to_string(i) + "\":" + std::to_string(_chrClass[i]);
        if(i < _chrClass.size() - 1){
            outTxt += ",\r\n";
        } else {
            outTxt += "\r\n            }\r\n        },\r\n";
        }
    }
    outTxt += "        \"experience\":{\r\n";// + std::to_string(_chrClass[0]) + ",\r\n"; // vector for multiclass
    outTxt += "            \"count\":" + std::to_string(_experience.size()) + ",\r\n";
    outTxt += "            \"index\":{\r\n";
    for(std::size_t i = 0; i < _experience.size(); ++i){
        outTxt += "                \"" + std::to_string(i) + "\":" + std::to_string(_experience[i]);
        if(i < _experience.size() - 1){
            outTxt += ",\r\n";
        } else {
            outTxt += "\r\n            }\r\n        },\r\n";
        }
    }
    outTxt += "        \"money\":{\r\n";
    outTxt += "            \"gold\":" + std::to_string(_money.gold) + ",\r\n";
    outTxt += "            \"silver\":" + std::to_string(_money.silver) + ",\r\n";
    outTxt += "            \"copper\":" + std::to_string(_money.copper) + ",\r\n";
    outTxt += "            \"electrum\":" + std::to_string(_money.electrum) + ",\r\n";
    outTxt += "            \"platinum\":" + std::to_string(_money.platinum) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"inventory\":{\r\n";
    outTxt += "            \"count\":" + std::to_string(_inventory.size()) + ",\r\n";
    outTxt += "            \"index\":{\r\n";
    for(std::size_t i = 0; i < _inventory.size(); ++i){
        outTxt += "                \"" + std::to_string(i) + "\":{\r\n";
        outTxt += "                    \"itemID\":" + std::to_string(_inventory[i].getID()) + ",\r\n";
        outTxt += "                    \"type\":" + std::to_string(_inventory[i].getType()) + ",\r\n";
        outTxt += "                    \"count\":" + std::to_string(_inventory[i].getCount()) + "\r\n";
        if(i < _inventory.size() - 1){
            outTxt += "                },\r\n";
        } else {
            outTxt += "                }\r\n";
        }
    }
    outTxt += "            }\r\n";
    outTxt += "        },\r\n";    
    outTxt += "        \"stats\":{\r\n";
    outTxt += "            \"strength\":" + std::to_string(_stats.strength) + ",\r\n";
    outTxt += "            \"excStrength\":" + std::to_string(_stats.excStren) + ",\r\n";
    outTxt += "            \"intelligence\":" + std::to_string(_stats.intelligence) + ",\r\n";
    outTxt += "            \"wisdom\":" + std::to_string(_stats.wisdom) + ",\r\n";
    outTxt += "            \"dexterity\":" + std::to_string(_stats.dexterity) + ",\r\n";
    outTxt += "            \"constitution\":" + std::to_string(_stats.constitution) + ",\r\n";
    outTxt += "            \"charisma\":" + std::to_string(_stats.charisma) + ",\r\n";
    outTxt += "            \"raceCharisma\":" + std::to_string(_stats.raceCharisma) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"modStats\":{\r\n";
    outTxt += "            \"strength\":" + std::to_string(_stats.strength) + ",\r\n";
    outTxt += "            \"excStrength\":" + std::to_string(_stats.excStren) + ",\r\n";
    outTxt += "            \"intelligence\":" + std::to_string(_stats.intelligence) + ",\r\n";
    outTxt += "            \"wisdom\":" + std::to_string(_stats.wisdom) + ",\r\n";
    outTxt += "            \"dexterity\":" + std::to_string(_stats.dexterity) + ",\r\n";
    outTxt += "            \"constitution\":" + std::to_string(_stats.constitution) + ",\r\n";
    outTxt += "            \"charisma\":" + std::to_string(_stats.charisma) + ",\r\n";
    outTxt += "            \"raceCharisma\":" + std::to_string(_stats.raceCharisma) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"strengthTable\":{\r\n";
    outTxt += "            \"hitProb\":" + std::to_string(_strTbl.hitProb) + ",\r\n";
    outTxt += "            \"damageAdj\":" + std::to_string(_strTbl.damageAdj) + ",\r\n";
    outTxt += "            \"weightAllowMod\":" + std::to_string(_strTbl.weightAllowMod) + ",\r\n";
    outTxt += "            \"openDoors\":" + std::to_string(_strTbl.openDoors) + ",\r\n";
    outTxt += "            \"bendBarsLiftGatesPer\":" + std::to_string(_strTbl.bendBarsLiftGatesPer) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"wisTable\":{\r\n";
    outTxt += "            \"magicAttackAdj\":" + std::to_string(_wisTbl.magicAttackAdj) + ",\r\n";
    outTxt += "            \"spellBonus\":" + std::to_string(_wisTbl.spellBonus) + ",\r\n";
    outTxt += "            \"spellFailPer\":" + std::to_string(_wisTbl.spellFailPer) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"intTable\":{\r\n";
    outTxt += "            \"chanceToKnowPer\":" + std::to_string(_intTbl.chanceToKnowPer) + ",\r\n";
    outTxt += "            \"minimumSpellsPer\":" + std::to_string(_intTbl.minumumSpellsPerLevel) + ",\r\n";
    outTxt += "            \"maximumSpellsPer\":" + std::to_string(_intTbl.maxiumSpellsPerlevel) + ",\r\n";
    outTxt += "            \"possibleAddLang\":" + std::to_string(_intTbl.possibAddLang) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"dexTable\":{\r\n";
    outTxt += "            \"reactAttkAdj\":" + std::to_string(_dexTbl.reactAttkAdj) + ",\r\n";
    outTxt += "            \"defenseAdj\":" + std::to_string(_dexTbl.defenseAdj) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"dexThief\":{\r\n";
    outTxt += "            \"pickPocketPer\":" + std::to_string(_dexThief.pickPocketPer) + ",\r\n";
    outTxt += "            \"openLocks\":" + std::to_string(_dexThief.openLocks) + ",\r\n";
    outTxt += "            \"locRemTraps\":" + std::to_string(_dexThief.locRemTraps) + ",\r\n";
    outTxt += "            \"movSilent\":" + std::to_string(_dexThief.movSilent) + ",\r\n";
    outTxt += "            \"hideInShadows\":" + std::to_string(_dexThief.hideInShadows) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"consTbl\":{\r\n";
    outTxt += "            \"hpAdj\":" + std::to_string(_consTbl.hpAdj) + ",\r\n";
    outTxt += "            \"sysShockSurPer\":" + std::to_string(_consTbl.sysShockSurPer) + ",\r\n";
    outTxt += "            \"resurSurvPer\":" + std::to_string(_consTbl.resurSurvPer) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"charTbl\":{\r\n";
    outTxt += "            \"maxHenchMen\":" + std::to_string(_charTbl.maxHenchMen) + ",\r\n";
    outTxt += "            \"loyaltyBasePer\":" + std::to_string(_charTbl.loyaltyBasePer) + ",\r\n";
    outTxt += "            \"reactAdjustPer\":" + std::to_string(_charTbl.reactAdjustPer) + "\r\n";
    outTxt += "        },\r\n";
    outTxt += "        \"languages\":{\r\n";
    outTxt += "            \"count\":" + std::to_string(_languages.size()) + ",\r\n";
    outTxt += "            \"index\":{\r\n";
    for(unsigned i = 0; i < _languages.size(); ++i){
        outTxt += "                \"" + std::to_string(i) + "\":" + std::to_string(_languages[i]);
        if(i < _languages.size() - 1){
            outTxt += ",\r\n";       
        } else {
            outTxt += "\r\n            }\r\n        }\r\n";
        }
    }
    // outTxt += "            \"reactAdjustPer\":" + std::to_string(_charTbl.reactAdjustPer) + "\r\n";
    // outTxt += "        }\r\n";
    outTxt += "    }\r\n";
    outTxt += "}";

    //std::cout << outTxt << std::endl;
    std::string filename = "characters/" + _name + ".json";
    std::ofstream myFile;
    myFile.open(filename);
    if(myFile.is_open()){
        myFile << outTxt;
        myFile.close();
    } else {
        std::cout << "File Can't open path " << filename << " invalid or cannot be accessed." << std::endl;
        return false;
    }
    return true;
}

void Entity::loadEntity(std::string file)
{
    //std::cout << "loading: " << file << std::endl;
    sj::ondemand::parser parser;
    sj::padded_string json = sj::padded_string::load(file.c_str());
    sj::ondemand::document charData = parser.iterate(json);
    std::stringstream recv;
    recv << ((charData["data"]["name"]));
    //recv >> _name;
    _name = recv.str();

    // Remove all double-quote characters
    _name.erase(
    std::remove( _name.begin(), _name.end(), '\"' ),
    _name.end()
    );

    _alignment = (ALIGNMENT)uint64_t(charData["data"]["alignment"]);
    _sex = (SEX)uint64_t(charData["data"]["sex"]);
    _race = (RACE)uint64_t(charData["data"]["race"]);

    _level = uint64_t(charData["data"]["level"]);
    _hitPointsBase = uint64_t(charData["data"]["maxHP"]);
    _curHitPoints = uint64_t(charData["data"]["curHP"]);
    _stats.strength = uint64_t(charData["data"]["stats"]["strength"]);
    _stats.excStren = uint64_t(charData["data"]["stats"]["excStrength"]);
    _stats.intelligence = uint64_t(charData["data"]["stats"]["intelligence"]);
    _stats.wisdom = uint64_t(charData["data"]["stats"]["wisdom"]);
    _stats.dexterity = uint64_t(charData["data"]["stats"]["dexterity"]);
    _stats.constitution = uint64_t(charData["data"]["stats"]["constitution"]);
    _stats.charisma = uint64_t(charData["data"]["stats"]["charisma"]);
    _stats.raceCharisma = uint64_t(charData["data"]["stats"]["raceCharisma"]);
    _weightAllowedGP = uint64_t(charData["data"]["weightAllow"]);
    _totalWeightGP = uint64_t(charData["data"]["totalWeight"]);
    _armorRating = uint64_t(charData["data"]["armorRating"]);

    _money.gold = uint64_t(charData["data"]["money"]["gold"]);
    _money.silver = uint64_t(charData["data"]["money"]["silver"]);
    _money.copper = uint64_t(charData["data"]["money"]["copper"]);
    _money.electrum = uint64_t(charData["data"]["money"]["electrum"]);
    _money.platinum = uint64_t(charData["data"]["money"]["platinum"]);

    _modStats.strength = uint64_t(charData["data"]["modStats"]["strength"]);
    _modStats.intelligence = uint64_t(charData["data"]["modStats"]["intelligence"]);
    _modStats.wisdom = uint64_t(charData["data"]["modStats"]["wisdom"]);
    _modStats.dexterity = uint64_t(charData["data"]["modStats"]["dexterity"]);
    _modStats.constitution = uint64_t(charData["data"]["modStats"]["constitution"]);
    _modStats.charisma = uint64_t(charData["data"]["modStats"]["charisma"]);
    _modStats.raceCharisma = uint64_t(charData["data"]["modStats"]["raceCharisma"]);

    _strTbl.hitProb = int64_t(charData["data"]["strengthTable"]["hitProb"]);
    _strTbl.damageAdj = int64_t(charData["data"]["strengthTable"]["damageAdj"]);
    _strTbl.weightAllowMod = int64_t(charData["data"]["strengthTable"]["weightAllowMod"]);
    _strTbl.openDoors = uint64_t(charData["data"]["strengthTable"]["openDoors"]);
    _strTbl.bendBarsLiftGatesPer = uint64_t(charData["data"]["strengthTable"]["bendBarsLiftGatesPer"]);

    _intTbl.chanceToKnowPer = uint64_t(charData["data"]["intTable"]["chanceToKnowPer"]);
    _intTbl.minumumSpellsPerLevel = uint64_t(charData["data"]["intTable"]["minimumSpellsPer"]);
    _intTbl.maxiumSpellsPerlevel = uint64_t(charData["data"]["intTable"]["maximumSpellsPer"]);
    _intTbl.possibAddLang = uint64_t(charData["data"]["intTable"]["possibleAddLang"]);

    _wisTbl.magicAttackAdj = int64_t(charData["data"]["wisTable"]["magicAttackAdj"]);
    _wisTbl.spellBonus = uint64_t(charData["data"]["wisTable"]["spellBonus"]);
    _wisTbl.spellFailPer = uint64_t(charData["data"]["wisTable"]["spellFailPer"]);

    _dexTbl.reactAttkAdj = int64_t(charData["data"]["dexTable"]["reactAttkAdj"]);
    _dexTbl.defenseAdj = int64_t(charData["data"]["dexTable"]["defenseAdj"]);

    _dexThief.pickPocketPer = int64_t(charData["data"]["dexThief"]["pickPocketPer"]);
    _dexThief.openLocks = int64_t(charData["data"]["dexThief"]["openLocks"]);
    _dexThief.locRemTraps = int64_t(charData["data"]["dexThief"]["locRemTraps"]);
    _dexThief.movSilent = int64_t(charData["data"]["dexThief"]["movSilent"]);
    _dexThief.hideInShadows = int64_t(charData["data"]["dexThief"]["hideInShadows"]);

    _consTbl.hpAdj = int64_t(charData["data"]["consTbl"]["hpAdj"]);
    _consTbl.sysShockSurPer = uint64_t(charData["data"]["consTbl"]["sysShockSurPer"]);
    _consTbl.resurSurvPer = uint64_t(charData["data"]["consTbl"]["resurSurvPer"]);

    _charTbl.maxHenchMen = uint64_t(charData["data"]["charTbl"]["maxHenchMen"]);
    _charTbl.loyaltyBasePer = int64_t(charData["data"]["charTbl"]["loyaltyBasePer"]);
    _charTbl.reactAdjustPer = int64_t(charData["data"]["charTbl"]["reactAdjustPer"]);
    
    for(int i = 0; i < int64_t(charData["data"]["languages"]["count"]); ++i){
        std::string idx = std::to_string(i);
        _languages.push_back((LANGUAGE)(uint64_t(charData["data"]["languages"]["index"][idx])));
    }

    // _chrClass is a vector of CHAR_CLASS ENUMS
    //_chrClass.push_back((CHAR_CLASS)uint64_t(charData["data"]["class"]));
    for(int i = 0; i < int64_t(charData["data"]["class"]["count"]); ++i){
        std::string idx = std::to_string(i);
        _chrClass.push_back((CHAR_CLASS)(uint64_t(charData["data"]["class"]["index"][idx])));
    }

    //_chrClass.push_back((CHAR_CLASS)uint64_t(charData["data"]["class"]));
    for(int i = 0; i < int64_t(charData["data"]["experience"]["count"]); ++i){
        std::string idx = std::to_string(i);
        _experience.push_back((uint64_t(charData["data"]["experience"]["index"][idx])));
    }

    setRaceSkillType();
    // std::cout << "\r\nPrinting Loaded Character .json" << std::endl;
    // std::cout << "Name: " << _name << std::endl;
    // printAlign(_alignment);
    // printSex(_sex);
    // printRace(_race);
    // printClass(_chrClass[0]);
    // std::cout << "Level: " << (int)_level << std::endl;
    // std::cout << "\r\nStats: ";
    // printStats(_stats);
    // std::cout << "\r\nMax HP: " << getMaxHP() << std::endl;
    // std::cout << "\r\nCurrent HP: " << getCurHP() << std::endl;
    // std::cout << "\r\nWeight Allowed in gold pieces (gp): " << getWeightAllowed() << std::endl;
    // std::cout << "\r\nTotal Weight gp: " << getWeightCarried() << std::endl;
    // printMoney(_money);
    // std::cout << "\r\nMod Stats: ";
    // printStats(_modStats);
    // printStrTbl(_strTbl);
    // printIntTbl(_intTbl);
    // printWisTbl(_wisTbl);
    // printDexTbl(_dexTbl);
    // printDexThief(_dexThief);
    // printConsTbl(_consTbl);
    // printCharTbl(_charTbl);
    // printLanguages(_languages);

    //setRaceSkillType();
    setChrClassSkill(_chrClass[0]);
    //std::cout << "finished loading character" << std::endl;
}

Entity::Entity(const char* filename)
{
    loadEntity(filename);
}

void Entity::addItem(Items setItem, unsigned amount)
{

    bool found = false;
    for(auto it = _inventory.begin(); it != _inventory.end(); ++it){
        if(it->getID() == setItem.getID() && it->getType() == setItem.getType()){
            it->increaseCount(amount);
            _totalWeightGP += setItem.getWeight() * amount;
            found = true;
        }
    }
    if(!found){
        _inventory.push_back(setItem);
        _totalWeightGP += setItem.getWeight() * amount;
    }
}

std::vector<Items> Entity::getInventory()
{
    return _inventory;
}
