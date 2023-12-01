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
RACE inputRace(stats inStats);
ALIGNMENT inputAlign();
CHAR_CLASS inputClass(RACE race, stats inStats, ALIGNMENT align);
void printSex(SEX sex);
void printStats(stats inStats);
void printStatsFails(stats inStats);
void printRace(RACE race);
void printAlign(ALIGNMENT align);
void printClass(CHAR_CLASS cClass);
void printStrTbl(strengthTable strTbl);
void printIntTbl(inteligenceTable intTbl);
bool reRoll();
bool raceStatCheck(stats inStats, RACE race);
bool classRaceCheck(CHAR_CLASS cClass, RACE race, ALIGNMENT align);
bool classStatCheck(CHAR_CLASS cClass, stats inStats);
bool checkExists(std::string name);
bool yesNoChoice();
std::string strenFails(stats inStats);
std::string intFails(stats inStats);
std::string wisFails(stats inStats);
std::string dexFails(stats inStats);
std::string consFails(stats inStats);
std::string charisFails(stats inStats);
std::string alignClasses(ALIGNMENT align);

/* Termios prototypes for Handling single unbuffered chars */
/* Initialize new terminal i/o settings */
void initTermios(int echo);
/* Restore old terminal i/o settings */
void resetTermios(void);
/* Read 1 character - echo defines echo mode */
char getch_(int echo); 
/* Read 1 character without echo */
char getch(void); 
/* Read 1 character with echo */
char getche(void); 

static struct termios old, current;

#endif