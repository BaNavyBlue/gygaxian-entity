/*
    Antone Bajor 2023
*/
#include <iostream>
#include "entity.h"

std::vector<std::shared_ptr<Items>> armsList;

int main(){
    srand((unsigned int) time(NULL));

    std::cout << "loading: " << "items/Arms.json" << std::endl;
    sj::ondemand::parser parser;
    sj::padded_string json = sj::padded_string::load("items/Arms.json");
    sj::ondemand::document itemsData = parser.iterate(json);


    unsigned itemCount = uint64_t(itemsData["data"]["count"]);
    std::cout << "itemCount: " << itemCount << std::endl;
    for(unsigned i = 0; i < itemCount; ++i){
        armsList.push_back(std::make_shared<Arms>(itemsData, i));
    }

    std::cout << "**** Welcome to the Gygaxian Character Generator ****" << std::endl;
    
    stats newStats[2];
    rollStats(newStats[0], newStats[1]);
    // newStats[0].strength = newStats[1].strength = 5;
    // newStats[0].intelligence = newStats[1].intelligence = 10;
    // newStats[0].wisdom = newStats[1].wisdom = 10;
    // newStats[0].dexterity = newStats[1].dexterity = 10;
    // newStats[0].charisma = newStats[1].charisma = 10;
    // newStats[0].constitution = newStats[1].constitution = 12;
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
    std::cout << "\r\nMax HP: " << dude.getMaxHP() << std::endl;
    std::cout << "\r\nWeight Allowed in gold pieces (gp): " << dude.getWeightAllowed() << std::endl;
    std::cout << "\r\nTotal Weight gp: " << dude.getWeightCarried() << std::endl;
    printMoney(dude.getMoney());
    printStrTbl(dude.getStrTbl());
    printIntTbl(dude.getIntTbl());
    printWisTbl(dude.getWisTbl());
    printDexTbl(dude.getDexTbl());
    printDexThief(dude.getDexTheif());
    printConsTbl(dude.getConsTbl());
    printCharTbl(dude.getCharTbl());
    printLanguages(dude.getLanguages());

    dude.addItem(*armsList[0], 1);
    dude.addItem(*armsList[1], 1);
    dude.addItem(*armsList[0], 1);

    std::vector<Items> test = dude.getInventory();
    std::cout << "name: " << test[0].getName() << std::endl;
    std::cout << "description: " << test[0].getDescription() << std::endl;  

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

