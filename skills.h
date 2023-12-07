#ifndef SKILLS_H
#define SKILLS_H
#include "project_headers.h"


class RACE_SKILLS
{
private:

protected:
    virtual void setRaceSkills() = 0;
public:
    RACE_SKILLS();
    ~RACE_SKILLS();

    virtual void listRaceSkills() = 0;
};

class CHR_CLASS_SKILLS
{
public:
    CHR_CLASS_SKILLS();
    virtual void listClassSkills();
};



class Dwarf: public RACE_SKILLS{
private:
    rollPair detectGrade; // 1-3 d4
    rollPair dtctConstrPsg; // 1-3 d4
    rollPair dtctMovingWalls; // 1-4 d6
    rollPair dtctTraps; // 1-2 d4
    rollPair dtctDepth; // 1-2 d4
protected:
    void setRaceSkills();
public:
    Dwarf();
    ~Dwarf();

    void listRaceSkills();

};


#endif // SKILLS_H