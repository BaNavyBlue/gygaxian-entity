/*
    Antone Bajor 2023
    Everything here is simply for 
    setting and reading values in the command line code.

    It also contains much of the logic handling for Sex,
    Aligment, Race and Char_Class constraints.

    The Termios library is used to switch to unbuffered character
    reads to respond to single key strokes quickly.
*/
#ifndef STATHELPERS_H
#define STATHELPERS_H
#include "project_headers.h"

const unsigned MAX_BUFFER = 32768;
const unsigned char STD_IN = 0;
const unsigned char STD_OUT = 1;

std::string inputName();
SEX inputSex();
RACE inputRace(stats inStats, std::vector<std::string>& viable, std::vector<std::string>& nonViable);
ALIGNMENT inputAlign(CHAR_CLASS inClass);
CHAR_CLASS inputClass(RACE race, stats inStats);
RACIAL_BIAS getRacialBias(RACE race1, RACE race2);
void rollStats(stats& _stats, stats& _modStats);
void printSex(SEX sex);
std::string getSex(SEX sex);
void printStats(stats inStats);
std::vector<std::string> getStats(stats inStats, CHAR_CLASS inClass, RACE inRace);
void printStatsFails(stats inStats);
void printRace(RACE race);
std::string getRace(RACE inRace);
void printAlign(ALIGNMENT align);
std::string getAlign(ALIGNMENT align);
void printClass(CHAR_CLASS cClass);
std::string getClass(CHAR_CLASS inClass);
void printStrTbl(strengthTable strTbl);
std::vector<std::string> getStrTbl(strengthTable strTbl);
void printIntTbl(intelligenceTable intTbl);
std::vector<std::string> getIntTbl(intelligenceTable intTbl);
void printWisTbl(wisdomTable wisTbl);
std::vector<std::string> getWisTbl(wisdomTable wisTbl);
void printDexTbl(dexterityTable dexTbl);
std::vector<std::string> getDexTbl(dexterityTable dexTbl);
void printDexThief(dexThieves dexThief);
std::vector<std::string> getDexTheif(dexThieves dexThief);
void printConsTbl(constitutionTable consTbl);
std::vector<std::string> getConsTbl(constitutionTable consTbl);
void printCharTbl(charismaTable charTbl);
std::vector<std::string> getCharTbl(charismaTable charTbl);
void printLanguages(std::vector<LANGUAGE> lang);
std::vector<std::string> getLanguages(std::vector<LANGUAGE> lang);
void printRacialBias(RACIAL_BIAS bias);
void printMoney(money inMoney);
bool reRoll();
bool raceStatCheck(stats inStats, RACE race);
bool classRaceCheck(CHAR_CLASS cClass, RACE race);
bool classStatCheck(CHAR_CLASS cClass, stats inStats);
bool checkExists(std::string name);
bool yesNoChoice();
bool rollFailure(stats inStats, bool printMsg);  // Handle Borked Gygaxian
stats checkRaceStats(RACE race, stats _stats);
bool alignClassCheck(CHAR_CLASS inClass, ALIGNMENT inAlign);
bool checkClassStats(CHAR_CLASS inClass, stats inStats);
std::string strenFails(stats inStats);
std::string intFails(stats inStats);
std::string wisFails(stats inStats);
std::string dexFails(stats inStats);
std::string consFails(stats inStats);
std::string charisFails(stats inStats);
std::string alignClasses(ALIGNMENT align);

/* Termios prototypes for Handling single unbuffered chars */
/* Initialize new terminal i/o settings */
//void initTermios(int echo);
/* Restore old terminal i/o settings */
//void resetTermios(void);
/* Read 1 character - echo defines echo mode */
//char getch_(int echo); 
/* Read 1 character without echo */
//char getch_n(void); 
/* Read 1 character with echo */
//char getche(void); 

//static struct termios old, current;

#endif