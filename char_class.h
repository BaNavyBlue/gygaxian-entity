#ifndef CHAR_CLASS_H
#define CHAR_CLASS_H
#include "project_headers.h"
/************************************************************/
/*                       Class Skills                       */
/************************************************************/
class CHR_CLASS_SKILLS
{
protected:
    classTable1 _classTbl;
public:
    CHR_CLASS_SKILLS();
    ~CHR_CLASS_SKILLS();
    virtual void listClassSkills();
    virtual unsigned generateGold();
    virtual unsigned rollHP();
    classTable1 getClassTable1();
};

class Cleric: public CHR_CLASS_SKILLS{
public:
    Cleric();
    ~Cleric();
    unsigned generateGold() override;
    //unsigned rollHP() override;
    //void listClassSkills();
};

class Druid: public CHR_CLASS_SKILLS{
public:
    Druid();
    ~Druid();
    unsigned generateGold() override;
    //void listClassSkills();
};

class Fighter: public CHR_CLASS_SKILLS{
public:
    Fighter();
    ~Fighter();
    //void listClassSkills();
};

class Paladin: public CHR_CLASS_SKILLS{
private:
    unsigned detectEvil = 60; // 60' on concentration
    unsigned defensiveBonus = 2;
    // immunity to all dissease
    unsigned cureWounds = 2; // 2HP per level
    // Cure Disease 1 + (level / 5) integer times per week
    // continuous emination of protection from evil 1" radius
    // 1 armor suit, 1 shield, 4 weapons 4 other.
    unsigned magicItemLimit = 10;
    // Will never retain wealth
    // 10% of income/treasure goes to lawful good charity
    // non cleric
    // only lawful good henchmen can only adventure with
    // non evil but only temoporarily if adventuring with neutral
    // take service or align with lawful good characters.

public:
    Paladin();
    ~Paladin();
    void getMagicItemLimit();
    //void listClassSkills();
};

class Ranger: public CHR_CLASS_SKILLS{
private:
    rollPair _chanceToSurprise;
    rollPair _chanceToBeSurprised;
    unsigned uGTrackPassagePer = 65;
    unsigned uGTrackDrStrPer = 55;
    unsigned uGTrackTrpDrPer = 45;
    unsigned uGTrackChimConDrPer = 35;
    unsigned uGTrackScrtDoorPer = 25;
    unsigned oDTrack = 90;
    unsigned oDTrackMoreThan1Per = 2; // +2% per creature
    int oDTrack24HrPer = -10;
    int oDTrackHourPercip = -25;

    // damage to giant class +1 per level
public:
    Ranger();
    ~Ranger();
    void listClassSkills() override;
};

class MagicUser: public CHR_CLASS_SKILLS{
public:
    MagicUser();
    ~MagicUser();
    unsigned generateGold() override;
    //void listClassSkills();
};

class Illusionist: public CHR_CLASS_SKILLS{
public:
    Illusionist();
    ~Illusionist();
    unsigned generateGold() override;
    //void listClassSkills();
};

class Thief: public CHR_CLASS_SKILLS{
protected:
    unsigned char _surpriseAtk = 4; // +4 to hit roll
    // back stab // blow from behind 1 + level/4 (int)
    thiefTable _thiefTbl;
    // if roll is 21% too high for pick pockets victim notices.
    // -5% for everly level of victim.
    void setRaceMod(RACE inRace);
public:
    Thief();
    Thief(RACE inRace, unsigned inLevel);
    ~Thief();
    void setThiefSkills(RACE inRace, unsigned inLevel);
    void listClassSkills();
    unsigned generateGold() override;
};

class Assassin: public Thief{
public:
    Assassin(RACE inRace, unsigned inLevel);
    ~Assassin();
    //void listClassSkills();
};

// Monk extends Thief only because uses some thief tables.
class Monk: public Thief{
private:
    // chance to surprise goes down 1% at level 2
    // and goes down 2% every level thereafter.
    unsigned _chanceToBeSurprise = 33; 
    int effectiveAC = 10; // -1 per level
    unsigned char moveInches = 15; // +1" per level
    unsigned char openHandMeleeAtk = 1; // increases with level
    // Open handed damage changes with level
    unsigned char openHandedDUpper = 3;
    unsigned char openHandedDLower = 1;
    //
public:
    Monk(RACE inRace, unsigned inLevel);
    ~Monk();
    unsigned generateGold() override;
    //void listClassSkills();
};
#endif