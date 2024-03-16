/*
    Antone Bajor 2023
*/
#ifndef ENTITY_STRUCTS_CONSTS_H
#define ENTITY_STRUCTS_CONSTS_H

#include <vector>
#include <string>

enum RACIAL_BIAS{
    HATE,
    ANTIPATHY,
    NEUTRALITY,
    TOLERANCE,
    GOODWILL,
    PREFERRED
};

enum CHAR_CLASS{
    CLERIC,
    DRUID,
    FIGHTER,
    RANGER,
    PALADIN,
    MAGIC_USER,
    ILLUSIONIST,
    THIEF,
    ASSASSIN,
    MONK
};

enum ALIGNMENT{
    CHAOTIC_EVIL,
    CHAOTIC_GOOD,
    CHAOTIC_NEUTRAL,
    LAWFUL_EVIL,
    LAWFUL_GOOD,
    LAWFUL_NEUTRAL,
    NEUTRAL_EVIL,
    NEUTRAL_GOOD,
    TRUE_NEUTRAL
};

enum RACE{
    HUMAN,
    ELF,
    HALF_ORC,
    HALFLING,
    DWARF,
    HALF_ELF,
    GNOME,
    CREATURE
};

enum SEX{
    FUTA,
    INTERSEX,
    FEMALE,
    MALE
};

enum LANGUAGE{
    ELVISH,
    GNOMISH,
    DWARVISH,
    HALFLING_L,
    GOBLIN_L,
    HOBGOBLIN_L,
    ORCISH,
    GNOLL,
    KOBOLD,
    BURROWING_ANIMALS,
    COMMON_L, 
    THIEVES_CANT,
    CHAO_EV_LANG,
    CHAO_GD_LANG,
    CHAO_NU_LANG,
    LAW_EV_LANG,
    LAW_GD_LANG,
    LAW_NU_LANG,
    NU_EV_LANG,
    NU_GD_LANG,
    TRU_NU_LANG
};

enum EQUIP_TYPE{
    ARMOR,
    ARMS,
    AMMO,
    PROJECTILE,
    CLOTHING,
    LIVESTOCK,
    MISC,
    PROVISIONS,
    RELIGIOUS,
    TACK_HARNESS,
    TRANSPORT
};

enum ARMOR_TYPE
{
    LEATHER,
    PADDED,
    STUDDED,
    CHAIN,
    SCALE,
    BANDED,
    SPLINT,
    PLATE
};

enum WEAPON_TYPE{
    KNIFE,    // 0
    DAGGER,   // 1
    SWORD,    // 2
    AXE,      // 3
    POLEARM,  // 4
    BOW,      // 5
    CROSSBOW, // 6
    ARROW,    // 7
    BOLT,     // 8
    DART,     // 9
    BLUNT,    // 10
    SPEAR     // 11
};

struct ULPair{
    unsigned lower;
    unsigned upper;
};

struct DefenseAdj{
    int8_t a2;
    int8_t a3;
    int8_t a4;
    int8_t a5;
    int8_t a6;
    int8_t a7;
    int8_t a8;
    int8_t a9;
    int8_t a10;
};

struct Range{
    unsigned shortRange;
    unsigned medRange;
    unsigned longRange;
};
struct langPair{
    LANGUAGE langE;
    std::string langS;
};

const std::vector<langPair> langPairs = {{ELVISH, "Elvish"},
                                                   {GNOMISH, "Gnomish"},
                                                   {DWARVISH, "Dwarvish"},
                                                   {HALFLING_L, "Halfling"},
                                                   {GOBLIN_L, "Goblin"},
                                                   {HOBGOBLIN_L, "Hobgoblin"},
                                                   {ORCISH, "Orcish"},
                                                   {KOBOLD, "Kobold"},
                                                   {BURROWING_ANIMALS, "Burrowing Animals"},
                                                   {COMMON_L, "Common"},
                                                   {GNOLL, "Gnoll"},
                                                   {THIEVES_CANT,"Thieves' Cant"},
                                                   {CHAO_EV_LANG, "Chaotic Evil"},
                                                   {CHAO_GD_LANG, "Chaotic Good"},
                                                   {CHAO_NU_LANG, "Chaotic Neutral"},
                                                   {LAW_EV_LANG, "Lawful Evil"},
                                                   {LAW_GD_LANG, "Lawful Good"},
                                                   {LAW_NU_LANG, "Lawful Neutral"},
                                                   {NU_EV_LANG, "Neutral Evil"},
                                                   {NU_GD_LANG, "Neutral Good"},
                                                   {TRU_NU_LANG, "True Neutral"}};

struct stats{
    unsigned strength;
    unsigned excStren = 0;
    unsigned intelligence;
    unsigned wisdom;
    unsigned charisma;
    unsigned raceCharisma;
    unsigned dexterity;
    unsigned constitution;
};

struct money{
    unsigned gold = 0;
    unsigned silver = 0;
    unsigned copper = 0;
    unsigned electrum = 0;
    unsigned platinum = 0;
};

struct strengthTable{ // pg. 9
    int hitProb = 0;
    int damageAdj = 0;
    int weightAllowMod = 0;
    unsigned openDoors = 1;
    unsigned bendBarsLiftGatesPer = 1; 
};

struct intelligenceTable{ // pg. 10
    unsigned chanceToKnowPer = 10;
    unsigned minumumSpellsPerLevel = 2;
    unsigned maxiumSpellsPerlevel = 3;
    unsigned possibAddLang = 0;
};

struct wisdomTable{ // pg. 11
    int magicAttackAdj = 0;
    unsigned spellBonus = 0;
    unsigned spellFailPer = 0;
};

struct dexterityTable{
    int reactAttkAdj = 0;
    int defenseAdj = 0;
};

struct dexThieves{ // pg. 12
    int pickPocketPer = 0;
    int openLocks = 0;
    int locRemTraps = 0;
    int movSilent = 0;
    int hideInShadows = 0;
};

struct constitutionTable{ // pg. 12
    int hpAdj = 0;
    unsigned sysShockSurPer = 70; // for const 10
    unsigned resurSurvPer = 75;
};

struct charismaTable{
    unsigned maxHenchMen = 4; // for charisma 10
    int loyaltyBasePer = 0;
    int reactAdjustPer = 0;
};

struct classTable1{ // pg 19
    unsigned HitDieType;
    unsigned MaxHitDie;
    bool spellAbility;
    int LevelLimit;
};

struct thiefTable{
    unsigned pickPockets = 30;
    unsigned openLocks = 25;
    unsigned findRemoveTraps = 20;
    unsigned moveSilently = 15;
    unsigned hideInShadows = 10;
    unsigned hearNoise = 10;
    float climbWalls = 85.0;
    unsigned readLanguages = 0;
};

struct classTable2{

};
// For pairing string with Enum
struct racePair{
    RACE race;
    std::string raceS;  
};

/************NOTE CAN'T INITIALIZE VECTOR IN HEADER UNLESS DEFINED AS CONST***********/
// These vectors are just to help with printing friendly human readable info in the terminal
const std::vector<racePair> racePairs = {{HUMAN, "Human"},
                                         {ELF, "Elf"},
                                         {HALF_ORC, "Half-Orc"},
                                         {DWARF, "Dwarf"},
                                         {HALFLING, "Halfling"},
                                         {HALF_ELF, "Half-Elf"},
                                         {GNOME, "Gnome"}};

struct classPair{
    CHAR_CLASS cClass;
    std::string cS;
};

const std::vector<classPair> classPairs = {{CLERIC, "Cleric"},
                                           {DRUID, "Druid"},
                                           {FIGHTER, "Fighter"},
                                           {RANGER, "Ranger"},
                                           {PALADIN, "Paladin"},
                                           {MAGIC_USER, "Magic-User"},
                                           {ILLUSIONIST, "Illusionist"},
                                           {THIEF, "Thief"},
                                           {ASSASSIN, "Assassin"},
                                           {MONK, "Monk"}};

struct alignPair{
    ALIGNMENT align;
    std::string alignS;
};

const std::vector<alignPair> alignPairs = {{CHAOTIC_EVIL, "Chaotic Evil"},
                                     {CHAOTIC_GOOD, "Chaotic Good"},
                                     {CHAOTIC_NEUTRAL, "Chaotic Neutral"},
                                     {LAWFUL_EVIL, "Lawful Evil"},
                                     {LAWFUL_GOOD, "Lawful Good"},
                                     {LAWFUL_NEUTRAL, "Lawful Neutral"},
                                     {NEUTRAL_EVIL, "Neutral Evil"},
                                     {NEUTRAL_GOOD, "Neutral Good"},
                                     {TRUE_NEUTRAL, "True Neutral"}}; 

struct rollPair{
    u8 sidedDie;
    u8 maxRange;
};


#endif