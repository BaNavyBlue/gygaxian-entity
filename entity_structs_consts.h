/*
    Antone Bajor 2023
*/
#ifndef ENTITY_STRUCTS_CONSTS_H
#define ENTITY_STRUCTS_CONSTS_H

#include <vector>
#include <string>

enum CHAR_CLASS{
    CLERIC,
    DRUID,
    FIGHTER,
    RANGER,
    PALADIN,
    THIEF,
    ASSASSIN,
    MAGIC_USER,
    ILLUSIONIST,
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
    TRANS,
    INTERSEX,
    FEMALE,
    MALE
};

struct stats{
    unsigned strength;
    unsigned excStren = 0;
    unsigned intellignece;
    unsigned wisdom;
    unsigned charisma;
    unsigned dexterity;
    unsigned constitution;
};

struct strengthTable{ // pg. 9
    int hitProb = 0;
    int damageAdj = 0;
    int weightAllowMod = 0;
    unsigned openDoors = 1;
    unsigned bendBarsLiftGatesPer = 1; 
};

struct inteligenceTable{ // pg. 10
    unsigned chanceToKnowPer = 10;
    unsigned minumumSpellsPerLevel = 2;
    unsigned maxiumSpellsPerlevel = 3;
    unsigned possibAddLang = 0;
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
                                           {PALADIN, "Paladin"},
                                           {RANGER, "Ranger"},
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


#endif