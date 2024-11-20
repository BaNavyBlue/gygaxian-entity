#include "items.h"

Items::Items()
{

}

Items::Items(const sj::ondemand::document* itemData, int idx)
{

}

Items::~Items()
{
    
}

EQUIP_TYPE Items::getType()
{
    return _type;
}

std::string Items::getName()
{
    return _name;
}

std::string Items::getDescription()
{
    return _description;
}

money Items::getValue()
{
    return _value;
}

unsigned Items::getID()
{
    return _itemID;
}

unsigned Items::getCount()
{
    return _itemCount;
}

void Items::increaseCount(unsigned numToAdd)
{
    _itemCount += numToAdd;
}

unsigned Items::getWeight()
{
    return _weightGP;
}

Arms::Arms()
{

}

Arms::Arms(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;

    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);
    _wType = (WEAPON_TYPE)uint64_t(itemRef["wType"]);
    _hasProf = (bool)uint64_t(itemRef["prof"]);
    if(_hasProf){
        _profType = (WEAPON_PROF)uint64_t(itemRef["profType"]);
    }
    recv << ((itemRef["name"]));
    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);
    _smallMedDMG.sidedDie = uint64_t(itemRef["smallMedDMG"]["sides"]);
    _smallMedDMG.maxRange = uint64_t(itemRef["smallMedDMG"]["rolls"]);
    _lrgDMG.sidedDie = uint64_t(itemRef["largeDMG"]["sides"]);
    _lrgDMG.maxRange = uint64_t(itemRef["largeDMG"]["rolls"]);
    _lengthInches = uint64_t(itemRef["lengthInch"]);
    _spaceReqInch = uint64_t(itemRef["spaceReq"]);
    _speedFactor = uint64_t(itemRef["speedFactor"]);
    _fireRAte = uint64_t(itemRef["fireRate"]);
    _rangeBase.shortRange = uint64_t(itemRef["range"]["short"]);
    _rangeBase.medRange = uint64_t(itemRef["range"]["medium"]);
    _rangeBase.longRange = uint64_t(itemRef["range"]["long"]);

    auto defenseAdj = itemRef["defenseAdj"];
    _defAdj.a2 = int64_t(defenseAdj["a2"]);
    _defAdj.a3 = int64_t(defenseAdj["a3"]);
    _defAdj.a4 = int64_t(defenseAdj["a4"]);
    _defAdj.a5 = int64_t(defenseAdj["a5"]);
    _defAdj.a6 = int64_t(defenseAdj["a6"]);
    _defAdj.a7 = int64_t(defenseAdj["a7"]);
    _defAdj.a8 = int64_t(defenseAdj["a8"]);
    _defAdj.a9 = int64_t(defenseAdj["a9"]);
    _defAdj.a10 = int64_t(defenseAdj["a10"]);

    if(_type == PROJECTILE){
        auto projDefenseAdj = itemRef["projDefenseAdj"];
        _projDefAdj.a2 = int64_t(projDefenseAdj["a2"]);
        _projDefAdj.a3 = int64_t(projDefenseAdj["a3"]);
        _projDefAdj.a4 = int64_t(projDefenseAdj["a4"]);
        _projDefAdj.a5 = int64_t(projDefenseAdj["a5"]);
        _projDefAdj.a6 = int64_t(projDefenseAdj["a6"]);
        _projDefAdj.a7 = int64_t(projDefenseAdj["a7"]);
        _projDefAdj.a8 = int64_t(projDefenseAdj["a8"]);
        _projDefAdj.a9 = int64_t(projDefenseAdj["a9"]);
        _projDefAdj.a10 = int64_t(projDefenseAdj["a10"]);
    }
}

Arms::~Arms()
{
    //std::cout << "Arms Destructor." << std::endl;
}

rollPair Arms::getSmallMedDMG()
{
    return _smallMedDMG;
}

rollPair Arms::getLargeDMG()
{
    return _lrgDMG;
}

unsigned Arms::getLength()
{
    return _lengthInches;
}

unsigned Arms::getSpaceReq()
{
    return _spaceReqInch;
}

unsigned Arms::getSpeedFactor()
{
    return _speedFactor;
}

unsigned Arms::getFireRate()
{
    return _fireRAte;
}

DefenseAdj Arms::getDefenseAdj()
{
    return _defAdj;
}

DefenseAdj Arms::getProjDefenseAdj()
{
    return _projDefAdj;
}

bool Arms::getHasProf()
{
    return _hasProf;
}

WEAPON_PROF Arms::getWeaponProf()
{
    return _profType;
}

Armor::Armor()
{

}

Armor::Armor(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);
    _aType = (ARMOR_TYPE)uint64_t(itemRef["aType"]);
    _armorMod = int64_t(itemRef["armorMod"]);
    _bulk = (BULK)uint64_t(itemRef["bulk"]);
    _moveInch = uint64_t(itemRef["bMoveInch"]);
    recv << ((itemRef["name"]));
    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);
}

Armor::~Armor()
{

}

Clothing::Clothing(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);
    _cType = (CLOTHING_TYPE)uint64_t(itemRef["cType"]);
    recv << ((itemRef["name"]));
    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);    
}

Herbs::Herbs(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);  
}

Herbs::~Herbs()
{

}

Livestock::Livestock(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);  
}

Livestock::~Livestock()
{

}

MiscItems::MiscItems(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);
}
    
MiscItems::~MiscItems()
{

}

Provisions::Provisions(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]);    
}

Provisions::~Provisions()
{

}

Religious::Religious(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]); 
}

Religious::~Religious()
{

}

TackHarness::TackHarness(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]); 
}

TackHarness::~TackHarness()
{

}

Transport::Transport(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemID = idx;
    auto itemRef = itemData["data"]["index"][std::to_string(idx)];
    _itemCount = uint64_t(itemRef["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemRef["type"]);

    recv << ((itemRef["name"]));

    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemRef["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    //std::cout << "[" << _name << "] description: " << _description << std::endl;
    auto money = itemRef["money"];
    _value.gold = uint64_t(money["gold"]);
    _value.silver = uint64_t(money["silver"]);
    _value.copper = uint64_t(money["copper"]);
    _value.electrum = uint64_t(money["electrum"]);
    _value.platinum = uint64_t(money["platinum"]);
    _weightGP = uint64_t(itemRef["weight"]); 
}

Transport::~Transport()
{

}