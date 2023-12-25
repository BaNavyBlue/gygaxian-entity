#ifndef ITEMS_H
#define ITEMS_H
#include "project_headers.h"

namespace sj = simdjson;

class Items
{
protected:
    unsigned _itemID;
    unsigned _itemCount;
    EQUIP_TYPE _type;
    std::string _name;
    std::string _description;
    money _value;
    unsigned _weightGP;
    //std::vector<enchantments> ench; //placeholder
public:
    Items();
    Items(const sj::ondemand::document* itemData, int idx);
    ~Items();
    EQUIP_TYPE getType();
    std::string getName();
    std::string getDescription();
    money getValue();
};

class Arms : public Items
{
private:
    WEAPON_TYPE _wType;
    rollPair _smallMedDMG;
    rollPair _lrgDMG;
    unsigned _lengthInches;
    unsigned _spaceReqInch;
    unsigned _speedFactor;
    unsigned _fireRAte;
    DefenseAdj _defAdj;
    Range _rangeInch;
public:
    Arms();
    Arms(sj::ondemand::document& itemData, int idx);
    ~Arms();
    rollPair getSmallMedDMG();
    rollPair getLargeDMG();
    unsigned getLength();
    unsigned getSpaceReq();
    unsigned getSpeedFactor();
    unsigned getFireRate();
    DefenseAdj getDefenseAdj();
};

class Armor : public Items
{
private:
    int armorMod;
public:
    Armor();
    ~Armor();
    int getArmorRating();
};

#endif // ITEMS_H