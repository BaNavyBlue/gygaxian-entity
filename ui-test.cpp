//#include <stdlib.h> /* for srand() / rand() */
//#include <stdio.h>
// #include <vector>
// #include <string>
//#include "project_headers.h"
//#include "rogueutil.h"
#include "ui_util.h"
// #include <cstddef>

#define NOCOLOR -1

// naughty globals
std::size_t horz_char = 0;
std::size_t vert_char = 0;

ScreenVals primaryScreen(VECT_MAX, ' ', GREEN, BLACK);

int main(){

    setlocale(LC_ALL,"");
    srand((unsigned int) time(NULL));

    horz_char = tcols();
    vert_char = trows();

    hidecursor();
    setConsoleTitle("Gygaxian-Entity");
    createPrimary();
    drawPrimary();
    
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
        }
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'c') {
                createRollScreen();
            } 
            else if (k == KEY_LEFT){drawPrimary();}
			else if (k == KEY_RIGHT){drawPrimary();}
			else if (k == KEY_UP){drawPrimary();}
			else if (k == KEY_DOWN){drawPrimary();}
            else if (k == KEY_ESCAPE) {
				break;
			} else {
                createPrimary();
            }
        }
    }


    cls();
    showcursor();
    return 0;
}

/************************************************************************************
    All of these function definitions were moved to ui_util.h
************************************************************************************/

void drawPrimary()
{
    cls();
    locate(1,1);
    for(std::size_t i = 0; i < vert_char; ++i){
        for(std::size_t j = 0; j < horz_char; ++j){
            int forPrint = primaryScreen.charMap[i][j];
                
                locate(j + 1, i + 1);
                if(forPrint > 127){
                    std::string utfChar = getUTF(forPrint);
                    colorPrintUTF(primaryScreen.colorMap[i][j], primaryScreen.bGColorMap[i][j], utfChar.c_str());
                } else {
                    char singleChar[2];
                    singleChar[0] = forPrint;
                    singleChar[1] = '\0';
                    colorPrint(primaryScreen.colorMap[i][j], primaryScreen.bGColorMap[i][j], singleChar);
                }
        }
    }
    locate(1,1);
    fflush(stdout);
}

void createPrimary()
{
    std::string line1 = "Welcome To Gygaxian-Entity";
    std::string line2 = "Character Creator";
    std::string options = "(C)reate New Character";
    std::string options2 = "Create New (P)arty";
    int msg1L = line1.size()/2;
    int msg2L = line2.size()/2;
    for(std::size_t i = 0; i < vert_char; ++i){
        for(std::size_t j = 0; j < horz_char; ++j){
            if(i == vert_char/2 - 1 && j == horz_char/2 - msg1L){
                for(std::size_t k = 0; k < line1.size(); ++k){
                    primaryScreen.charMap[i][j] = line1[k];
                    primaryScreen.colorMap[i][j] = GREEN;
                    primaryScreen.bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == vert_char/2 && j == horz_char/2 - msg2L){
                for(std::size_t k = 0; k < line2.size(); ++k){
                    primaryScreen.charMap[i][j] = line2[k];
                    primaryScreen.colorMap[i][j] = GREEN;
                    primaryScreen.bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if (i == vert_char - 1 && j == 0){
                primaryScreen.charMap[i][j] = 0x2551;
                primaryScreen.colorMap[i][j] = RED;
                primaryScreen.bGColorMap[i][j++] = GREY;
                for(std::size_t k = 0; k < options.size(); ++k){
                    primaryScreen.charMap[i][j] = options[k];
                    primaryScreen.colorMap[i][j] = RED;
                    primaryScreen.bGColorMap[i][j++] = GREY;
                }
                primaryScreen.charMap[i][j] = 0x2551;
                primaryScreen.colorMap[i][j] = RED;
                primaryScreen.bGColorMap[i][j++] = GREY;
                for(std::size_t k = 0; k < options2.size(); ++k){
                    primaryScreen.charMap[i][j] = options2[k];
                    primaryScreen.colorMap[i][j] = RED;
                    primaryScreen.bGColorMap[i][j++] = GREY;
                }
                primaryScreen.charMap[i][j] = 0x2551;
                primaryScreen.colorMap[i][j] = RED;
                primaryScreen.bGColorMap[i][j++] = GREY;
                //j--;
            } else if(i == 0 && j == 0){
                primaryScreen.charMap[i][j] = 0x2554;
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            } else if(i == 0 && j == horz_char - 1){
                primaryScreen.charMap[i][j] = 0x2557;
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == 0) {
                primaryScreen.charMap[i][j] = 0x255A; 
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == horz_char - 1){
                primaryScreen.charMap[i][j] = 0x255D;
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            } else if(i == 0 || i == vert_char - 2) {
                primaryScreen.charMap[i][j] = 0x2550; 
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            } else if ((j == 0 || j == horz_char - 1) && i < vert_char - 1){
                primaryScreen.charMap[i][j] = 0x2551;
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            }  else {
                primaryScreen.charMap[i][j] = 0x0020;
                primaryScreen.colorMap[i][j] = GREEN;
                primaryScreen.bGColorMap[i][j] = BLACK;
            }
        }
    }

}

void createRollScreen()
{
    int prevMax = 0;
    int prevRow = 0;
    ScreenVals rollScreen(VECT_MAX, ' ', YELLOW, BLACK);
    ScreenVals sexScreen(VECT_MAX, ' ', YELLOW, BLACK);
    ScreenVals raceScreen(VECT_MAX, ' ', YELLOW, BLACK);
    ScreenVals classScreen(VECT_MAX, ' ', YELLOW, BLACK);

    stats newStats[2];
    rollStats(newStats[0], newStats[1]);
    Perimeter rollPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);

    std::string choices = "Keep current roll? (y/n) (B)rute Force a Class? [esc] to go back.";
    do{
        int maxLen = 0;
        int addRow = 0;

        char tmp[4];
        sprintf(tmp, "%3u", newStats[0].strength);
        std::string strength = "            Strength:";
        strength += tmp;
        strength  += " Fails - " + strenFails(newStats[0]);
        sprintf(tmp, "%3u", newStats[0].excStren);
        std::string exceptStr = "Exceptional Strength:";
        exceptStr += tmp;
        exceptStr += " Fighter, Paladin and Ranger only!";
        sprintf(tmp, "%3u", newStats[0].intelligence);
        std::string intelligence = "        Intelligence:";
        intelligence += tmp;
        intelligence += " Fails - " + intFails(newStats[0]);
        sprintf(tmp, "%3u", newStats[0].wisdom);
        std::string wisdom = "              Wisdom:";
        wisdom += tmp;
        wisdom += " Fails - " + wisFails(newStats[0]);
        sprintf(tmp, "%3u", newStats[0].dexterity);
        std::string dexterity = "           Dexterity:";
        dexterity += tmp;
        dexterity += " Fails - " + dexFails(newStats[0]);
        sprintf(tmp, "%3u", newStats[0].charisma);
        std::string charisma = "            Charisma:";
        charisma += tmp;
        charisma += " Fails - " + charisFails(newStats[0]);
        sprintf(tmp, "%3u", newStats[0].constitution);
        std::string constitution = "        Constitution:";
        constitution += tmp;
        constitution += " Fails - " + consFails(newStats[0]);
        std::string stats = "stats";
        
        std::vector<int> lengths;
        lengths.push_back(strength.size());
        lengths.push_back(intelligence.size());
        lengths.push_back(wisdom.size());
        lengths.push_back(dexterity.size());
        lengths.push_back(charisma.size());
        lengths.push_back(constitution.size());
        lengths.push_back(exceptStr.size());
        lengths.push_back(choices.size());

        for(int i = 0; i < lengths.size(); ++i){
            if(lengths[i] > maxLen){
                maxLen = lengths[i];
            }
        }

        if(newStats[0].strength > 17){
            addRow = 1;   
        } else {
            addRow = 0;
        }
        
        if(prevMax < maxLen){
            prevMax = maxLen;
        }

        if(prevRow < addRow){
            prevRow = addRow;
        }
        drawSmall(1, prevMax + 5, 1, 10 + prevRow, primaryScreen);

        rollScreen.xyLimits.minX = 1;
        rollScreen.xyLimits.maxX = maxLen + 5;
        rollScreen.xyLimits.minY = 1;
        rollScreen.xyLimits.maxY = 10 + addRow - 2;


        
        generatePerimeter(rollScreen, rollPerim);

        rollScreen.xyLimits.maxY = 10 + addRow;

        for(std::size_t i = 1; i < 10 + addRow; ++i){
            for(std::size_t j = 1; j < maxLen + 6; ++j){
                if(i == 2 && j == 3) {
                    for(std::size_t k = 0; k < strength.size(); ++k){
                        rollScreen.charMap[i][j] = strength[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 2 + addRow && j == 3 && addRow) {
                    for(std::size_t k = 0; k < exceptStr.size(); ++k){
                        rollScreen.charMap[i][j] = exceptStr[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 3 + addRow && j == 3) {
                    for(std::size_t k = 0; k < intelligence.size(); ++k){
                        rollScreen.charMap[i][j] = intelligence[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 4 + addRow && j == 3) {
                    for(std::size_t k = 0; k < wisdom.size(); ++k){
                        rollScreen.charMap[i][j] = wisdom[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 5 + addRow && j == 3) {
                    for(std::size_t k = 0; k < dexterity.size(); ++k){
                        rollScreen.charMap[i][j] = dexterity[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 6 + addRow && j == 3) {
                    for(std::size_t k = 0; k < charisma.size(); ++k){
                        rollScreen.charMap[i][j] = charisma[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
                } else if(i == 7 + addRow && j == 3) {
                    for(std::size_t k = 0; k < constitution.size(); ++k){
                        rollScreen.charMap[i][j] = constitution[k];
                        rollScreen.colorMap[i][j] = YELLOW;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;
            } else if(i == 9 + addRow && j == 3) {
                    rollScreen.charMap[i][j - 2] = ' ';
                    rollScreen.colorMap[i][j - 2] = RED;
                    rollScreen.bGColorMap[i][j- 2] = BLACK;
                    rollScreen.charMap[i][j - 1] = ' ';
                    rollScreen.colorMap[i][j - 1] = RED;
                    rollScreen.bGColorMap[i][j- 1] = BLACK;
                    for(std::size_t k = 0; k < choices.size(); ++k){
                        rollScreen.charMap[i][j] = choices[k];
                        rollScreen.colorMap[i][j] = RED;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    int x = 0 ;
                    while(j + x < maxLen + 5){
                        rollScreen.charMap[i][j + x] = ' ';
                        rollScreen.colorMap[i][j + x] = RED;
                        rollScreen.bGColorMap[i][j + x] = BLACK;
                        ++x;
                    }
                    j--;                 
                } 
            }       
        }
        drawSmall(1, rollScreen.xyLimits.maxX, 1, rollScreen.xyLimits.maxY, rollScreen);
    } while(reRollOptions(newStats[0], newStats[1], rollScreen));
    drawSmall(1, rollScreen.xyLimits.maxX, rollScreen.xyLimits.maxY - 1, rollScreen.xyLimits.maxY, primaryScreen);
    RACE newRace;
    SEX newSex = selSexScreen(sexScreen, rollScreen);
    createRaceScreen(newRace, newStats[0], rollScreen, sexScreen, raceScreen);
    CHAR_CLASS newClass = selClassScreen(newStats[0], newRace, rollScreen, sexScreen, raceScreen, classScreen);
    
    DrawRange alignCorner;
    alignCorner.minX = classScreen.xyLimits.maxX + 1;
    alignCorner.minY = classScreen.xyLimits.minY;

    AlignOptWindow alignWin(newClass);
    alignWin.createWindow(alignCorner, rollPerim);

    std::vector<ScreenVals> screenVec;
    screenVec.push_back(rollScreen);
    screenVec.push_back(sexScreen);
    screenVec.push_back(raceScreen);
    screenVec.push_back(classScreen);
    screenVec.push_back(alignWin.getScreen());
    
    ALIGNMENT newAlign = alignWin.getAlign(selAlign(screenVec, alignWin.getOptIdx()));

    TextInput textBox;
    DrawRange textCorner;
    textCorner.minX = sexScreen.xyLimits.minX;
    textCorner.minY = sexScreen.xyLimits.maxY + 1;

    std::string newName;
    bool confirmName = false;

    do{
        confirmName = false;
        //newName.erase(std::remove(newName.begin(), newName.end(), '0'), newName.end());
        textBox.createTextInput(textCorner, rollPerim, "Enter Name:");
        newName = textBox.getAquiredString();
        if(doesRecordExist(newName, "characters/", ".json")){
            WarnMessage nameExists("Name already in use", "Overwrite? (y/n)");
            confirmName = nameExists.waitForAnswer();
            drawSmall(nameExists.getScreen().xyLimits.minX, nameExists.getScreen().xyLimits.maxX, nameExists.getScreen().xyLimits.minY, nameExists.getScreen().xyLimits.maxY + 1, primaryScreen);
            drawSmall(alignWin.getScreen().xyLimits.minX, alignWin.getScreen().xyLimits.maxX, alignWin.getScreen().xyLimits.minY, alignWin.getScreen().xyLimits.maxY + 1, alignWin.getScreen());
            drawSmall(classScreen.xyLimits.minX, classScreen.xyLimits.maxX, classScreen.xyLimits.minY, classScreen.xyLimits.maxY + 1, classScreen);
            drawSmall(raceScreen.xyLimits.minX, raceScreen.xyLimits.maxX, raceScreen.xyLimits.minY, raceScreen.xyLimits.maxY + 1, raceScreen);
            drawSmall(sexScreen.xyLimits.minX, sexScreen.xyLimits.maxX, sexScreen.xyLimits.minY, sexScreen.xyLimits.maxY + 1, sexScreen);
            drawSmall(rollScreen.xyLimits.minX, rollScreen.xyLimits.maxX, rollScreen.xyLimits.minY, rollScreen.xyLimits.maxY - 1, rollScreen);           
        }
        if(confirmName){
            textBox.purgeRecieved();
        }
    } while(confirmName);

    std::vector<CHAR_CLASS> classVect;
    classVect.push_back(newClass);

    Entity dude(newStats, newName, newSex, newRace, classVect, newAlign);
    dude.saveChar();

    drawSmall(textBox.getScreen().xyLimits.minX, textBox.getScreen().xyLimits.maxX, textBox.getScreen().xyLimits.minY, textBox.getScreen().xyLimits.maxY + 1, primaryScreen);
    usleep(40000);
    drawSmall(alignWin.getScreen().xyLimits.minX, alignWin.getScreen().xyLimits.maxX, alignWin.getScreen().xyLimits.minY, alignWin.getScreen().xyLimits.maxY + 1, primaryScreen);
    usleep(40000);
    drawSmall(classScreen.xyLimits.minX, classScreen.xyLimits.maxX, classScreen.xyLimits.minY, classScreen.xyLimits.maxY + 1, primaryScreen);
    usleep(40000);
    drawSmall(raceScreen.xyLimits.minX, raceScreen.xyLimits.maxX, raceScreen.xyLimits.minY, raceScreen.xyLimits.maxY + 1, primaryScreen);
    usleep(40000);
    drawSmall(sexScreen.xyLimits.minX, sexScreen.xyLimits.maxX, sexScreen.xyLimits.minY, sexScreen.xyLimits.maxY + 1, primaryScreen);
    usleep(40000);
    drawSmall(rollScreen.xyLimits.minX, rollScreen.xyLimits.maxX, rollScreen.xyLimits.minY, rollScreen.xyLimits.maxY - 1, primaryScreen);
    
    DrawRange infoRange;
    infoRange.minX = 1;
    infoRange.minY = 1;
    PrintInfo showChar(dude, infoRange, rollPerim);






}

bool createRaceScreen(RACE &newRace, stats& inStats, ScreenVals& inScreen, ScreenVals& inScreen2, ScreenVals& inScreen3)
{
    //ScreenVals raceScreen(VECT_MAX, ' ', GREEN, BLACK);
    std::vector<std::string> viable;
    std::vector<std::string> nonViable;

    viable.push_back("Select Race:");
    nonViable.push_back("Non-Viable Races:");
    std::unordered_map<char, RACE> rMap;
    char idx = '0';
    int nonV = 0;
    for(unsigned i = 0; i < racePairs.size(); ++i){
        if(raceStatCheck(inStats, racePairs[i].race)/*&&checkRaceStats(racePairs[i].race, inStats)*/){
            rMap[idx] = racePairs[i].race;
            viable.push_back(racePairs[i].raceS + ": " + idx);
            idx++;         
        } else {
            nonViable.push_back(racePairs[i].raceS);
            nonV++;
        }
    }

    int maxLen = 0;
    int addRow = 0;
    int totalStrings = viable.size();

    for(int i = 0; i < viable.size(); ++i){
        if(maxLen < viable[i].size()){
            maxLen = viable[i].size();
        }
    }
    
    if(nonViable.size() > 1){
        for(int i = 0; i < nonViable.size(); ++i){
            if(maxLen < nonViable[i].size()){
                maxLen = nonViable[i].size();
            }
        }
        totalStrings  += nonViable.size();
        addRow = 1;
    }

    inScreen3.xyLimits.minX = inScreen2.xyLimits.maxX + 1;
    inScreen3.xyLimits.maxX = inScreen2.xyLimits.maxX + 1 + maxLen + 6;
    inScreen3.xyLimits.minY = inScreen.xyLimits.maxY - 1; // - 1 because of the previous prompt
    inScreen3.xyLimits.maxY = inScreen.xyLimits.maxY + totalStrings + addRow;

    Perimeter racePerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
    generatePerimeter(inScreen3, racePerim);

    for(std::size_t i = inScreen3.xyLimits.minY; i < inScreen3.xyLimits.maxY + 1; ++i){
        for(std::size_t j = inScreen3.xyLimits.minX; j < inScreen3.xyLimits.maxX + 1 ; ++j){
            if((i == inScreen3.xyLimits.minY + 1) && j == inScreen3.xyLimits.minX + 3){
                if(nonViable.size() > 1){
                    for(int m = 0; m < nonViable.size(); ++m){
                        for(int n = 0; n < nonViable[m].size(); ++n){
                            inScreen3.charMap[i][j] = nonViable[m][n];
                            inScreen3.colorMap[i][j] = RED;
                            inScreen3.bGColorMap[i][j++] = BLACK;
                        }
                        j = inScreen3.xyLimits.minX + 4; 
                        i++;
                    }
                    i++;
                    j = inScreen3.xyLimits.minX + 3;
                }
                for(int m = 0; m < viable.size(); ++m){
                    for(int n = 0; n < viable[m].size(); ++n){
                        inScreen3.charMap[i][j] = viable[m][n];
                        inScreen3.colorMap[i][j] = YELLOW;
                        inScreen3.bGColorMap[i][j++] = BLACK;
                    }
                    j = inScreen3.xyLimits.minX + 4; 
                    i++;
                }
            }
        }
    }
    
    drawSmall(inScreen3.xyLimits.minX, inScreen3.xyLimits.maxX, inScreen3.xyLimits.minY, inScreen3.xyLimits.maxY + 1, inScreen3);

    char raceSelection = selRace(idx, inScreen, inScreen2, inScreen3);
    if(raceSelection < 0){
        printf("Something Unpossible happened!\r\n");
        return false;
    } else {
        newRace = rMap[raceSelection];
    }         
    return true;
}

SEX selSexScreen(ScreenVals& sexScreen, ScreenVals& inScreen)
{
    std::vector<std::string> sexList;
    sexList.push_back("Select Sex:");
    sexList.push_back("Futa: 0");
    sexList.push_back("Intersex*: 1");
    sexList.push_back("Female**: 2");
    sexList.push_back("Male: 3");
    sexList.push_back("");
    sexList.push_back("*Intersex");
    sexList.push_back("const -1.");
    sexList.push_back("charis +1.");
    sexList.push_back("");
    sexList.push_back("**Females");
    sexList.push_back("have stren.");
    sexList.push_back("caps.");
    
    
    int maxLen = 0;

    for(int i = 0; i < sexList.size(); ++i){
        if(maxLen < sexList[i].size()){
            maxLen = sexList[i].size();
        }
    }

    sexScreen.xyLimits.minX = inScreen.xyLimits.minX;
    sexScreen.xyLimits.maxX = maxLen + 6;
    sexScreen.xyLimits.minY = inScreen.xyLimits.maxY - 1; // - 1 because of the previous prompt
    sexScreen.xyLimits.maxY = inScreen.xyLimits.maxY + sexList.size();

    Perimeter sexPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
    generatePerimeter(sexScreen, sexPerim);

    for(std::size_t i = sexScreen.xyLimits.minY; i < sexScreen.xyLimits.maxY + 1; ++i){
        for(std::size_t j = 1; j < maxLen + 7; ++j){
            if((i == sexScreen.xyLimits.minY + 1) && j == 4){
                for(int m = 0; m < sexList.size(); ++m){
                    for(int n = 0; n < sexList[m].size(); ++n){
                        sexScreen.charMap[i][j] = sexList[m][n];
                        sexScreen.colorMap[i][j] = YELLOW;
                        sexScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j = 5; 
                    i++;
                }
            }
        }
    }
    drawSmall(1, sexScreen.xyLimits.maxX, sexScreen.xyLimits.minY, sexScreen.xyLimits.maxY + 1, sexScreen);
    char choice;
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
            drawSmall(inScreen.xyLimits.minX, inScreen.xyLimits.maxX, inScreen.xyLimits.minY, inScreen.xyLimits.maxY - 1, inScreen);
            drawSmall(sexScreen.xyLimits.minX, sexScreen.xyLimits.maxX, sexScreen.xyLimits.minY, sexScreen.xyLimits.maxY + 1, sexScreen);
        }
        
        if(kbhit()){
            char k = getkey();
            if(k >= '0' && k < '4'){
                switch(k){
                    case '0':
                        return FUTA;
                    case '1':
                        return INTERSEX;
                    case '2':
                        return FEMALE;
                    case '3':
                        return MALE;
                }
            }
        }
    }
    return FUTA;   
}

bool reRollOptions(stats& stats1, stats& stats2, ScreenVals& inScreen)
{
    //std::cout << std::endl << "Would you like to keep stats? y/n: ";
    char choice;
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
            drawSmall(inScreen.xyLimits.minX, inScreen.xyLimits.maxX, inScreen.xyLimits.minY, inScreen.xyLimits.maxY, inScreen);
        }
        
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'n') {
                rollStats(stats1, stats2);
                return true;
            } else if(std::tolower(k) == 'y'){
                return false;
            }
            else if (k == KEY_ESCAPE) {
                drawSmall(inScreen.xyLimits.minX, inScreen.xyLimits.maxX, inScreen.xyLimits.minY, inScreen.xyLimits.maxY, primaryScreen);
                return false;
            }
        }
    }
    return false;
}

char selRace(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3)
{
    //std::cout << std::endl << "Would you like to keep stats? y/n: ";
    char choice;
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
            drawSmall(inScreen1.xyLimits.minX, inScreen1.xyLimits.maxX, inScreen1.xyLimits.minY, inScreen1.xyLimits.maxY - 1, inScreen1);
            drawSmall(inScreen2.xyLimits.minX, inScreen2.xyLimits.maxX, inScreen2.xyLimits.minY, inScreen2.xyLimits.maxY + 1, inScreen2);
            drawSmall(inScreen3.xyLimits.minX, inScreen3.xyLimits.maxX, inScreen3.xyLimits.minY, inScreen3.xyLimits.maxY + 1, inScreen3);
        }
        
        if(kbhit()){
            char k = getkey();
            if(k >= '0' && k < maxIdx){
                return k;
            } 
        }
    }
    return -1;
}

CHAR_CLASS selClassScreen(stats& inStats, RACE inRace, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& classScreen)
{
    std::vector<std::string> classList;
    classList.push_back("Select Class:");
    std::vector<std::string> nonViable;
    nonViable.push_back("Non-Viable Classes: ");
    std::unordered_map<char, CHAR_CLASS> cList;
    char idx = '0';
    int nonV = 0;
    stats tempStats = checkRaceStats(inRace, inStats); // Fix that race stat mods aren't taken into class consideration;
    for(unsigned i = 0; i < classPairs.size(); ++i){
        if(classRaceCheck(classPairs[i].cClass, inRace) && classStatCheck(classPairs[i].cClass, tempStats)){
            cList[idx] = classPairs[i].cClass;
            classList.push_back(classPairs[i].cS + ": " + idx);
            idx++;         
        } else {
            nonViable.push_back(classPairs[i].cS);
            nonV++;
        }
    }

    int maxLen = 0;
    int addRow = 0;
    int totalStrings = classList.size();

    for(int i = 0; i < classList.size(); ++i){
        if(maxLen < classList[i].size()){
            maxLen = classList[i].size();
        }
    }
    
    if(nonViable.size() > 1){
        for(int i = 0; i < nonViable.size(); ++i){
            if(maxLen < nonViable[i].size()){
                maxLen = nonViable[i].size();
            }
        }
        totalStrings  += nonViable.size();
        addRow = 1;
    }

    classScreen.xyLimits.minX = inScreen3.xyLimits.maxX + 1;
    classScreen.xyLimits.maxX = inScreen3.xyLimits.maxX + 1 + maxLen + 6;
    classScreen.xyLimits.minY = inScreen1.xyLimits.maxY - 1; // - 1 because of the previous prompt
    classScreen.xyLimits.maxY = inScreen1.xyLimits.maxY + totalStrings + addRow;

    Perimeter classPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
    generatePerimeter(classScreen, classPerim);
    drawSmall(classScreen.xyLimits.minX, classScreen.xyLimits.maxX, classScreen.xyLimits.minY, classScreen.xyLimits.maxY + 1, classScreen);

    for(std::size_t i = classScreen.xyLimits.minY; i < classScreen.xyLimits.maxY + 1; ++i){
        for(std::size_t j = classScreen.xyLimits.minX; j < classScreen.xyLimits.maxX + 1 ; ++j){
            if((i == classScreen.xyLimits.minY + 1) && j == classScreen.xyLimits.minX + 3){
                if(nonViable.size() > 1){
                    for(int m = 0; m < nonViable.size(); ++m){
                        for(int n = 0; n < nonViable[m].size(); ++n){
                            classScreen.charMap[i][j] = nonViable[m][n];
                            classScreen.colorMap[i][j] = RED;
                            classScreen.bGColorMap[i][j++] = BLACK;
                        }
                        j = classScreen.xyLimits.minX + 4; 
                        i++;
                    }
                    i++;
                    j = classScreen.xyLimits.minX + 3;
                }
                for(int m = 0; m < classList.size(); ++m){
                    for(int n = 0; n < classList[m].size(); ++n){
                        classScreen.charMap[i][j] = classList[m][n];
                        classScreen.colorMap[i][j] = YELLOW;
                        classScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j = classScreen.xyLimits.minX + 4; 
                    i++;
                }
            }
        }
    }
    
    drawSmall(classScreen.xyLimits.minX, classScreen.xyLimits.maxX, classScreen.xyLimits.minY, classScreen.xyLimits.maxY + 1, classScreen);
    char classKey = selClass(idx, inScreen1, inScreen2, inScreen3, classScreen);
    return cList[classKey];
    return CLERIC;
}

char selClass(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4)
{
    //std::cout << std::endl << "Would you like to keep stats? y/n: ";
    char choice;
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
            drawSmall(inScreen1.xyLimits.minX, inScreen1.xyLimits.maxX, inScreen1.xyLimits.minY, inScreen1.xyLimits.maxY - 1, inScreen1);
            drawSmall(inScreen2.xyLimits.minX, inScreen2.xyLimits.maxX, inScreen2.xyLimits.minY, inScreen2.xyLimits.maxY + 1, inScreen2);
            drawSmall(inScreen3.xyLimits.minX, inScreen3.xyLimits.maxX, inScreen3.xyLimits.minY, inScreen3.xyLimits.maxY + 1, inScreen3);
            drawSmall(inScreen4.xyLimits.minX, inScreen4.xyLimits.maxX, inScreen4.xyLimits.minY, inScreen4.xyLimits.maxY + 1, inScreen4);
        }
        
        if(kbhit()){
            char k = getkey();
            if(k >= '0' && k < maxIdx){
                return k;
            } 
        }
    }
    return -1;
}

char selAlign(std::vector<ScreenVals> inScreens, int idx)
{
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary();
            drawPrimary();
            for(int i = 0; i < inScreens.size(); ++i){
                int offSet = 1;
                if(i < 1){
                    offSet = -1;
                }
                drawSmall(inScreens[i].xyLimits.minX, inScreens[i].xyLimits.maxX, inScreens[i].xyLimits.minY, inScreens[i].xyLimits.maxY + offSet, inScreens[i]);
            }
        }
        
        if(kbhit()){
            char k = getkey();
            if(k >= '0' && k < idx + '0'){
                return k;
            } 
        }
    }
    return -1;    
}

std::string getName(ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4)
{

}

