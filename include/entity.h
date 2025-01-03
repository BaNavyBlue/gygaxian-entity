/*
    Antone Bajor 2023
*/
#ifndef ENTITY_H
#define ENTITY_H
//#include "ui_util.h"
#include "StatHelpers.h"
#include "skills.h"
#include "char_class.h"
#include "items.h"

namespace sj = simdjson;

class Entity{
private:
    //std::string _name; name class probably private.  not needed for monsters.
protected:

    //std::string _char_class;
    //std::string _race;
    std::vector<std::shared_ptr<CHR_CLASS_SKILLS>> _chrSkills;
    std::shared_ptr<RACE_SKILLS> _raceSkills;
    std::vector<Items> _inventory;
    std::string _name;
    bool _undead = false;
    stats _stats; // Base Stats upon creation.
    money _money;
    stats _modStats; // Stats altered by effects.
    strengthTable _strTbl;
    intelligenceTable _intTbl;
    wisdomTable _wisTbl;
    dexterityTable _dexTbl;
    dexThieves _dexThief;
    constitutionTable _consTbl;
    charismaTable _charTbl;
    unsigned char _level = 1;
    std::vector<unsigned> _experience; // initialized for each class
    unsigned _hitPointsBase;
    unsigned _curHitPoints;
    unsigned _numWeapProf;
    int _nonProfPenalty;
    unsigned _addWeapLevelDenom;
    short int _armorRating = 10; // base unarmored
    double _weightAllowedGP = 350.0f; //Weight in Gold Pieces
    double _totalWeightGP = 0.0f;
    float _meleeAttkRound = 1.0;
    std::vector<CHAR_CLASS> _chrClass; // for multiclass
    std::vector<LANGUAGE> _languages;
    std::vector<WEAPON_PROF> _weaponProf;
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
    void setAlignLanguages();
    void setRaceSkillType();
    void setChrClassSkill(CHAR_CLASS inClass);
    void setMeleeAttkRnd(CHAR_CLASS inClass);
    bool checkRaceStats(RACE race);
    void setClass(CHAR_CLASS cls);
    void setRace(RACE race);
    void addWeapProf(WEAPON_PROF prof);
    bool isFighter(); // Decided Paladin and Ranger are under umbrella of Fighter
    void loadEntity(std::string file);
public:
    Entity(stats inStats[2], std::string name, SEX sex, RACE race, std::vector<CHAR_CLASS> chrClass, ALIGNMENT align);
    Entity(const char* filename);
    ~Entity();
    stats getStats();
    stats getModStats();
    strengthTable getStrTbl();
    intelligenceTable getIntTbl();
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
    money getMoney();
    unsigned getMaxHP();
    unsigned getLevel();
    unsigned getCurHP();
    double getWeightAllowed();
    double getWeightCarried();
    short int getArmorRating();
    float getEquivalentGP();
    void addItem(Items setItem, unsigned amount);
    std::vector<Items> getInventory();
    //void reRollStats();
    std::shared_ptr<RACE_SKILLS> getRaceSkills();
    std::vector<std::shared_ptr<CHR_CLASS_SKILLS>> getCharClassSkills();
    std::vector<WEAPON_PROF> getWeapProf();
    void setWeaponProf(WEAPON_PROF newProf);
    bool saveChar();
};
#endif
