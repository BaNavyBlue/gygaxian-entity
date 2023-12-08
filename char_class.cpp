#include "char_class.h"

CHR_CLASS_SKILLS::CHR_CLASS_SKILLS()
{

}

CHR_CLASS_SKILLS::~CHR_CLASS_SKILLS()
{

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
}

Cleric::Cleric(){
    _classTbl.HitDieType = 8;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1; // -1 = no limit
    std::cout << "This should list Cleric HitDieType" << std::endl;
    listClassSkills();
}

Cleric::~Cleric(){
    std::cout << "Cleric Destructor" << std::endl;
}

Druid::Druid(){
    _classTbl.HitDieType = 8;
    _classTbl.MaxHitDie = 14;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = 14; // The Great Druid
    listClassSkills();
}

Fighter::Fighter(){
    _classTbl.HitDieType = 10;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

Paladin::Paladin(){
    _classTbl.HitDieType = 10;
    _classTbl.MaxHitDie = 9;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

Ranger::Ranger(){
    _classTbl.HitDieType = 8;// Begins with 2d8
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

MagicUser::MagicUser(){
    _classTbl.HitDieType = 4;
    _classTbl.MaxHitDie = 11;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

Illusionist::Illusionist(){
    _classTbl.HitDieType = 4;
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = true;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

Thief::Thief(){
    _classTbl.HitDieType = 6;
    _classTbl.MaxHitDie = 10;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = -1;
    listClassSkills();
}

Assassin::Assassin(){
    _classTbl.HitDieType = 6;
    _classTbl.MaxHitDie = 15;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = 14;
    listClassSkills();
}

Monk::Monk(){
    _classTbl.HitDieType = 4; // starts 2d4
    _classTbl.MaxHitDie = 17;
    _classTbl.spellAbility = false;
    _classTbl.LevelLimit = 17;
    listClassSkills();
}
