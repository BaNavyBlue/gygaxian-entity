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
    void listClassSkills();
    classTable1 getClassTable1();
};

class Cleric: public CHR_CLASS_SKILLS{
public:
    Cleric();
    ~Cleric();
    //void listClassSkills();
};

class Druid: public CHR_CLASS_SKILLS{
public:
    Druid();
    ~Druid();
    //void listClassSkills();
};

class Fighter: public CHR_CLASS_SKILLS{
public:
    Fighter();
    ~Fighter();
    //void listClassSkills();
};

class Paladin: public CHR_CLASS_SKILLS{
public:
    Paladin();
    ~Paladin();
    //void listClassSkills();
};

class Ranger: public CHR_CLASS_SKILLS{
public:
    Ranger();
    ~Ranger();
    //void listClassSkills();
};

class MagicUser: public CHR_CLASS_SKILLS{
public:
    MagicUser();
    ~MagicUser();
    //void listClassSkills();
};

class Illusionist: public CHR_CLASS_SKILLS{
public:
    Illusionist();
    ~Illusionist();
    //void listClassSkills();
};

class Thief: public CHR_CLASS_SKILLS{
public:
    Thief();
    ~Thief();
    //void listClassSkills();
};

class Assassin: public CHR_CLASS_SKILLS{
public:
    Assassin();
    ~Assassin();
    //void listClassSkills();
};

class Monk: public CHR_CLASS_SKILLS{
public:
    Monk();
    ~Monk();
    //void listClassSkills();
};
#endif