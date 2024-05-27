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
    unsigned getID();
    unsigned getCount();
    unsigned getWeight();
    void increaseCount(unsigned numToAdd);
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
    DefenseAdj _projDefAdj;
    Range _rangeBase; // Rules state for oldschool figure maps relate to 1" on maps outoors mult by 10 yards indoors 10'
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
    DefenseAdj getProjDefenseAdj();
};

class Armor : public Items
{
private:
    int _armorMod;
    int _moveInch;
    BULK _bulk;
    ARMOR_TYPE _aType;   
public:
    Armor();
    Armor(sj::ondemand::document& itemData, int idx);
    ~Armor();
    int getArmorRating();
    BULK getArmorBulk();
    ARMOR_TYPE getArmorType();
    int getArmorMobility();
};

class Clothing : public Items
{
private:
    //int armorMod;
    CLOTHING_TYPE _cType;
public:
    Clothing(sj::ondemand::document& itemData, int idx);
};

class Herbs : public Items
{
private:
    //int armorMod;
public:
    Herbs();
    Herbs(sj::ondemand::document& itemData, int idx);
    ~Herbs();
};

class Livestock : public Items
{
private:
    //int armorMod;
public:
    Livestock(sj::ondemand::document& itemData, int idx);
    ~Livestock();
};

class MiscItems : public Items
{
private:
    //int armorMod;
public:
    MiscItems(sj::ondemand::document& itemData, int idx);
    ~MiscItems();
};

class Provisions : public Items
{
private:
    //int armorMod;
public:
    Provisions(sj::ondemand::document& itemData, int idx);
    ~Provisions();
};

class Religious : public Items
{
private:
    //int armorMod;
public:
    Religious();
    ~Religious();
};

class TackHarness : public Items
{
private:
    //int armorMod;
public:
    TackHarness();
    ~TackHarness();
};
class Transport : public Items
{
private:
    //int armorMod;
public:
    Transport();
    ~Transport();
};



#endif // ITEMS_H