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

}

std::string Items::getName()
{

}

std::string Items::getDescription()
{

}

money Items::getValue()
{

}

Arms::Arms()
{

}

Arms::Arms(sj::ondemand::document& itemData, int idx)
{
    std::stringstream recv;
    _itemCount = uint64_t(itemData["data"]["index"][std::to_string(idx)]["count"]);
    _type = (EQUIP_TYPE)uint64_t(itemData["data"]["index"][std::to_string(idx)]["type"]);
    _wType = (WEAPON_TYPE)uint64_t(itemData["data"]["index"][std::to_string(idx)]["wType"]);
    recv << ((itemData["data"]["index"][std::to_string(idx)]["name"]));
    _name = recv.str();

    _name.erase(
         std::remove( _name.begin(), _name.end(), '\"' ),
         _name.end());

    recv.str("");

    recv << ((itemData["data"]["index"][std::to_string(idx)]["descrip"]));
    _description = recv.str();

    _description.erase(
                std::remove( _description.begin(), _description.end(), '\"' ),
                _description.end());

    std::cout << "[" << _name << "] description: " << _description << std::endl;
    _value.gold = uint64_t(itemData["data"]["index"][std::to_string(idx)]["money"]["gold"]);
    _value.silver = uint64_t(itemData["data"]["index"][std::to_string(idx)]["money"]["silver"]);
    _value.copper = uint64_t(itemData["data"]["index"][std::to_string(idx)]["money"]["copper"]);
    _value.electrum = uint64_t(itemData["data"]["index"][std::to_string(idx)]["money"]["electrum"]);
    _value.platinum = uint64_t(itemData["data"]["index"][std::to_string(idx)]["money"]["platinum"]);
    _weightGP = uint64_t(itemData["data"]["index"][std::to_string(idx)]["weight"]);
    _smallMedDMG.sidedDie = uint64_t(itemData["data"]["index"][std::to_string(idx)]["smallMedDMG"]["sides"]);
    _smallMedDMG.maxRange = uint64_t(itemData["data"]["index"][std::to_string(idx)]["smallMedDMG"]["rolls"]);
    _lrgDMG.sidedDie = uint64_t(itemData["data"]["index"][std::to_string(idx)]["largeDMG"]["sides"]);
    _lrgDMG.maxRange = uint64_t(itemData["data"]["index"][std::to_string(idx)]["largeDMG"]["rolls"]);
    _lengthInches = uint64_t(itemData["data"]["index"][std::to_string(idx)]["lengthInch"]);
    _spaceReqInch = uint64_t(itemData["data"]["index"][std::to_string(idx)]["spaceReq"]);
    _speedFactor = uint64_t(itemData["data"]["index"][std::to_string(idx)]["speedFactor"]);
    _fireRAte = uint64_t(itemData["data"]["index"][std::to_string(idx)]["fireRate"]);
    _rangeInch.shortRange = uint64_t(itemData["data"]["index"][std::to_string(idx)]["range"]["short"]);
    _rangeInch.medRange = uint64_t(itemData["data"]["index"][std::to_string(idx)]["range"]["medium"]);
    _rangeInch.longRange = uint64_t(itemData["data"]["index"][std::to_string(idx)]["range"]["long"]);
    _defAdj.a2 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a2"]);
    _defAdj.a3 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a3"]);
    _defAdj.a4 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a4"]);
    _defAdj.a5 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a5"]);
    _defAdj.a6 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a6"]);
    _defAdj.a7 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a7"]);
    _defAdj.a8 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a8"]);
    _defAdj.a9 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a9"]);
    _defAdj.a10 = int64_t(itemData["data"]["index"][std::to_string(idx)]["defenseAdj"]["a10"]);
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