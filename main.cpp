/*
    Antone Bajor 2023
*/
#include <iostream>
#include "entity.h"

int main(){
    srand((unsigned int) time(NULL));
    std::cout << "**** Welcome to the Gygaxian Character Generator ****" << std::endl;
    

    Entity dude(inputAlign(), inputSex(), inputName());
    //stats dudeStats = dude.getStats();
    std::cout << std::endl;
    std::cout << dude.getName() << "'s ";
    printSex(dude.getSex());
    std::cout << dude.getName() << "'s ";
    printAlign(dude.getAlign());
    std::cout << dude.getName() << "'s stats: " << std::endl;
    printStatsFails(dude.getStats());
    while(reRoll()){
        dude.reRollStats();
        printStatsFails(dude.getStats());
    }

    do{
        //std::cout << "Choose Race:" << std::endl;
    }while(!dude.checkRaceStats(inputRace(dude.getStats())));
    std::cout << std::endl;
    std::cout << dude.getName() << "'s ";
    printSex(dude.getSex());
    std::cout << dude.getName() << "'s ";
    printAlign(dude.getAlign());
    std::cout << dude.getName() << "'s ";
    printRace(dude.getRace());
    std::cout << dude.getName() << "'s stats: " << std::endl;
    printStats(dude.getStats());

    dude.setClass(inputClass(dude.getRace(), dude.getStats(), dude.getAlign()));
    std::cout << std::endl;
    std::cout << dude.getName() << "'s ";
    printSex(dude.getSex());
    std::cout << dude.getName() << "'s ";
    printAlign(dude.getAlign());
    std::cout << dude.getName() << "'s ";
    printRace(dude.getRace());
    std::cout << dude.getName() << "'s ";
    for(int i = 0; i < dude.getClass().size(); ++i){
        printClass(dude.getClass()[i]);
    }
    std::cout << dude.getName() << "'s stats: " << std::endl;
    printStats(dude.getStats());
    printStrTbl(dude.getStrTbl());
    printIntTbl(dude.getIntTbl());
    printWisTbl(dude.getWisTbl());

    dude.saveChar();
    std::string charFile = "characters/" + dude.getName() + ".json";
    Entity jsonTest(charFile.c_str());
    return 0;
}

