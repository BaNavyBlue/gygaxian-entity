/*
    Antone Bajor 2023
*/
#include <iostream>
#include "entity.h"

int main(){
    srand((unsigned int) time(NULL));
    std::cout << "**** Welcome to the Gygaxian Character Generator ****" << std::endl;
    
    stats newStats[2];
    rollStats(newStats[0], newStats[1]);
    printStatsFails(newStats[0]);
    while(reRoll()){
        rollStats(newStats[0], newStats[1]);
        printStatsFails(newStats[0]);
    }
    SEX newSex = inputSex();
    RACE newRace = inputRace(newStats[0]);
    std::vector<CHAR_CLASS> newClass;
    newClass.push_back(inputClass(newRace, newStats[0]));
    ALIGNMENT newAlign = inputAlign(newClass[0]);
    std::string newName = inputName();

    Entity dude(newStats, newName, newSex, newRace, newClass, newAlign);

    std::cout << std::endl;
    std::cout << dude.getName() << "'s ";
    printSex(dude.getSex());
    std::cout << dude.getName() << "'s ";
    printAlign(dude.getAlign());
    std::cout << dude.getName() << "'s ";
    printRace(dude.getRace());
    std::cout << dude.getName() << "'s ";
    for(unsigned i = 0; i < dude.getClass().size(); ++i){
        printClass(dude.getClass()[i]);
    }
    printLanguages(dude.getLanguages());
    std::cout << dude.getName() << "'s stats: " << std::endl;
    printStats(dude.getStats());
    printStrTbl(dude.getStrTbl());
    printIntTbl(dude.getIntTbl());
    printWisTbl(dude.getWisTbl());
    printDexTbl(dude.getDexTbl());
    printDexThief(dude.getDexTheif());
    printConsTbl(dude.getConsTbl());
    printCharTbl(dude.getCharTbl());
    printLanguages(dude.getLanguages());

    if(dude.saveChar()){
        std::cout << "file saved" << std::endl;
    } else {
        std::cout << "file save failed" << std::endl;
    }
    
    std::string charFile = "characters/" + dude.getName() + ".json";
    std::cout << "New file name: " << charFile << std::endl;
    Entity jsonTest(charFile.c_str());

    printRacialBias(getRacialBias(DWARF, HALF_ORC));
    printRacialBias(getRacialBias(HALF_ORC, DWARF));
    printRacialBias(getRacialBias(HALF_ELF, ELF));
    // RACE_SKILLS* test = new Dwarf(dude.getStats());
    // delete (Dwarf*)test;


    return 0;
}

