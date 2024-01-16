#ifndef SKILLS_H
#define SKILLS_H
#include "project_headers.h"

class RACE_SKILLS
{
private:

protected:
    virtual void setRaceSkills(stats inStats) = 0;
public:
    RACE_SKILLS();
    RACE_SKILLS(stats inStats);
    ~RACE_SKILLS();

    virtual void listRaceSkills() = 0;
    virtual std::vector<std::string> getRaceSkills() = 0;
};

class Dwarf: public RACE_SKILLS{
private:
    rollPair detectGrade; // 1-3 d4
    rollPair dtctConstrPsg; // 1-3 d4
    rollPair dtctMovingWalls; // 1-4 d6
    rollPair dtctTraps; // 1-2 d4
    rollPair dtctDepth; // 1-2 d4
    unsigned infraVision = 60; // 60'
    int toHitBonus = 1; // half-orcs, goblins, hobgoblins or orcs
    int adversaryHitPenalty = -4; // list on pg. 16
    int defensiveBonus = 0;
protected:
    void setRaceSkills(stats inStats);
public:
    Dwarf();
    Dwarf(stats inStats);
    ~Dwarf();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();

};

class Elf: public RACE_SKILLS{
private:
    rollPair resistSlpChrm; // < 90 d100
    rollPair secConDoorPsv; // within 10'
    rollPair secConDoorActv;
    rollPair conPortal;
    unsigned infraVision = 60; // 60'
    int toHitBonus = 1; // swords, short swords, bows, crossbows
    rollPair chanceToSurprise; //d6 1-4
    rollPair chanceToSurprisePort; //d6 1-2
    int defensiveBonus = 0;
protected:
    void setRaceSkills(stats inStats);
public:
    Elf();
    Elf(stats inStats);
    ~Elf();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();

};

class Gnome: public RACE_SKILLS{
private:
    rollPair detectGrade; // 1-8 d10
    rollPair dtctUnsafeWCF; // 1-7 d10
    rollPair detDirecUG; // 1-5 d10
    rollPair dtctDepth; // 1-6 d10
    unsigned infraVision = 60; // 60'
    int toHitBonus = 1; // Kobolds or Goblins
    int adversaryHitPenalty = -4; // list on pg. 17
    int defensiveBonus = 0;
protected:
    void setRaceSkills(stats inStats);
public:
    Gnome();
    Gnome(stats inStats);
    ~Gnome();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();

};

class HalfElf: public RACE_SKILLS{
private:
    rollPair resistSlpChrm; // < 30 d100
    rollPair secConDoorPsv; // within 10'
    rollPair secConDoorActv;
    rollPair conPortal;
    unsigned infraVision = 60; // 60'
protected:
    void setRaceSkills(stats inStats);
public:
    HalfElf();
    HalfElf(stats inStats);
    ~HalfElf();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();
};

class Halfling: public RACE_SKILLS{
private:
    rollPair detectGrade; // 1-3 d4
    rollPair detDirecUG; // 1-5 d10
    rollPair chanceToSurprise; //d6 1-4
    rollPair chanceToSurprisePort; //d6 1-2
    unsigned infraVision = 30; // 30'-60'
    int defensiveBonus = 0;
protected:
    void setRaceSkills(stats inStats);
public:
    Halfling();
    Halfling(stats inStats);
    ~Halfling();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();
};

class HalfOrc: public RACE_SKILLS{
private:
    unsigned infraVision = 60; // 60'
protected:
    void setRaceSkills(stats inStats);
public:
    HalfOrc();
    HalfOrc(stats inStats);
    ~HalfOrc();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();
};

class Human: public RACE_SKILLS{
private:
protected:
    void setRaceSkills(stats inStats);
public:
    Human();
    Human(stats inStats);
    ~Human();

    void listRaceSkills();
    std::vector<std::string> getRaceSkills();
};
#endif // SKILLS_H
