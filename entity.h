/*
    Antone Bajor 2023
*/
#ifndef ENTITY_H
#define ENTITY_H

#include "project_headers.h"
#include "StatHelpers.h"
#include "dice_roll.h"
#include "simdjson.h"
#include "skills.h"
#include "char_class.h"

namespace sj = simdjson;

class Entity{
private:
    //std::string _name; name class probably private.  not needed for monsters.
protected:

    //std::string _char_class;
    //std::string _race;
    std::vector<std::shared_ptr<CHR_CLASS_SKILLS>> _chrSkills;
    std::shared_ptr<RACE_SKILLS> _raceSkills;
    std::string _name;
    bool _undead = false;
    stats _stats; // Base Stats upon creation.
    stats _modStats; // Stats altered by effects.
    strengthTable _strTbl;
    inteligenceTable _intTbl;
    wisdomTable _wisTbl;
    dexterityTable _dexTbl;
    dexThieves _dexThief;
    constitutionTable _consTbl;
    charismaTable _charTbl;
    unsigned char _level = 1;
    std::vector<unsigned> _experience; // initialized for each class
    unsigned _hitPointsBase;
    unsigned _curHitPoints;
    unsigned _weightAllowedGP = 450; //Weight in Gold Pieces
    unsigned _totalWeightGP = 0;
    float _meleeAttkRound = 1.0;
    std::vector<CHAR_CLASS> _chrClass; // for multiclass
    std::vector<LANGUAGE> _languages;
    RACE _race;
    SEX _sex;
    ALIGNMENT _alignment;
    void setStrenTbl();
    void setIntTbl();
    void setPossLang();
    void setWisTbl();
    void setDexTbl();
    void setDexThief();
    void setConsTbl();
    void setCharTbl();
    void setBaseLanguages(); 
    void setRaceSkillType();
    void setChrClassSkill(CHAR_CLASS inClass);
    void setMeleeAttkRnd(CHAR_CLASS inClass);
    bool isFighter(); // Decided Paladin and Ranger are under umbrella of Fighter
    bool loadEntity(std::string file);
public:
    Entity(ALIGNMENT align, SEX sex, std::string name);
    Entity(const char* filename);
    ~Entity();
    stats getStats();
    stats getModStats();
    strengthTable getStrTbl();
    inteligenceTable getIntTbl();
    wisdomTable getWisTbl();
    dexterityTable getDexTbl();
    dexThieves getDexTheif();
    constitutionTable getConsTbl();
    charismaTable getCharTbl();
    std::string getName();
    SEX getSex();
    RACE getRace();
    ALIGNMENT getAlign();
    float getMeleeAttkRnd();
    std::vector<CHAR_CLASS> getClass();
    std::vector<unsigned> getExperience();
    std::vector<LANGUAGE> getLanguages();
    bool checkRaceStats(RACE race);
    bool setClass(CHAR_CLASS cls);
    void setRace(RACE race);
    void reRollStats();
    bool saveChar();
};
#endif
