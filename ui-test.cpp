//#include <stdlib.h> /* for srand() / rand() */
//#include <stdio.h>
// #include <vector>
// #include <string>
//#include "project_headers.h"
#include "rogueutil.h"
#include "entity.h"

const int VECT_MAX = 400;

struct DrawRange{
    int minX;
    int maxX;
    int minY;
    int maxY;
};

struct ScreenVals{
    std::vector<std::vector<int>> charMap;
    std::vector<std::vector<color_code>> colorMap;
    std::vector<std::vector<color_code>> bGColorMap;
    DrawRange xyLimits;
    ScreenVals(const int max, int setInt, color_code charColor, color_code bGColor):
        charMap(max, std::vector<int>(max, setInt)),
        colorMap(max, std::vector<color_code>(max, charColor)),
        bGColorMap(max, std::vector<color_code>(max, bGColor)){}
    
};

#define NOCOLOR -1

std::size_t horz_char = 0;
std::size_t vert_char = 0;


ScreenVals primaryScreen(VECT_MAX, ' ', GREEN, BLACK);

void drawPrimary();
void drawSmall(int startX, int maxX, int startY, int maxY, ScreenVals& inScreen);
void createPrimary();
void createRollScreen();
std::string getUTF(int inCode);
bool reRollOptions(stats& stats1, stats& stats2, ScreenVals& inScreen);

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

    stats newStats[2];
    rollStats(newStats[0], newStats[1]);

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
        drawSmall(1, prevMax + 5, 1, 11 + prevRow, primaryScreen);

        rollScreen.xyLimits.minX = 1;
        rollScreen.xyLimits.maxX = maxLen + 5;
        rollScreen.xyLimits.minY = 1;
        rollScreen.xyLimits.maxY = 10 + addRow;

        for(std::size_t i = 1; i < 10 + addRow; ++i){
            for(std::size_t j = 1; j < maxLen + 6; ++j){
                if(i == 1 && j == 1){
                    rollScreen.charMap[i][j] = 0x256D;
                    rollScreen.colorMap[i][j] = MAGENTA;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else if(i == 2 && j == 3) {
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
                    for(std::size_t k = 0; k < choices.size(); ++k){
                        rollScreen.charMap[i][j] = choices[k];
                        rollScreen.colorMap[i][j] = RED;
                        rollScreen.bGColorMap[i][j++] = BLACK;
                    }
                    j--;                 
                } else if(i == 1 && j == maxLen + 5){
                    rollScreen.charMap[i][j] = 0x256E;
                    rollScreen.colorMap[i][j] = MAGENTA;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else if(i == 8 + addRow && j == 1) {
                    rollScreen.charMap[i][j] = 0x2570; 
                    rollScreen.colorMap[i][j] = MAGENTA;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else if(i == 8 + addRow && j == maxLen + 5){
                    rollScreen.charMap[i][j] = 0x256F;
                    rollScreen.colorMap[i][j] = MAGENTA;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else if(i == 1 || i == 8 + addRow) {
                    rollScreen.charMap[i][j] = 0x2500;
                    rollScreen.colorMap[i][j] = BLUE;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else if ((j == 1 || j == maxLen + 5) && i < 8 + addRow){
                    rollScreen.charMap[i][j] = 0x2502;
                    rollScreen.colorMap[i][j] = BLUE;
                    rollScreen.bGColorMap[i][j] = BLACK;
                } else {
                    rollScreen.charMap[i][j] = ' ';
                    rollScreen.colorMap[i][j] = YELLOW;
                    rollScreen.bGColorMap[i][j] = BLACK;               
                }
            }       
        }
        drawSmall(1, rollScreen.xyLimits.maxX, 1, rollScreen.xyLimits.maxY, rollScreen);
    } while(reRollOptions(newStats[0], newStats[1], rollScreen));

}

void drawSmall(int startX, int maxX, int startY, int maxY, ScreenVals& inScreen)
{
    for(int i = startY; i < maxY; ++i){
        for(int j = startX; j < maxX + 1; ++j){
            int forPrint = inScreen.charMap[i][j];
            //if(primaryScreen[i][j] == ' '){
                
                locate(j + 1, i + 1);
                if(forPrint > 127){
                    //std::string utfCode = std::to_string(forPrint);
                    std::string utfChar = getUTF(forPrint);

                    //printf("%s\n", utfChar.c_str());
                    colorPrintUTF(inScreen.colorMap[i][j], inScreen.bGColorMap[i][j], utfChar.c_str());
                } else {
                    char singleChar[2];
                    singleChar[0] = forPrint;
                    singleChar[1] = '\0';
                    colorPrint(inScreen.colorMap[i][j], inScreen.bGColorMap[i][j], singleChar);
                }            
        }
    }
}

std::string getUTF(int inCode)
{
    //unsigned int codePoint;
    
    //sscanf(unicodeEscape + 2, "%x", &codePoint);  // Skip the "\u" part and parse the hexadecimal value

    // Calculate the number of bytes needed based on the Unicode code point
    int numBytes;
    if (inCode <= 0x7F) {
        numBytes = 1;
    } else if (inCode <= 0x7FF) {
        numBytes = 2;
    } else if (inCode <= 0xFFFF) {
        numBytes = 3;
    } else if (inCode <= 0x10FFFF) {
        numBytes = 4;
    } else {
        fprintf(stderr, "Invalid Unicode code point: %x\n", inCode);
        exit(EXIT_FAILURE);
    }

    // Create the UTF-8 sequence
    switch (numBytes) {
        char utf8Result[5];
        case 1:
            sprintf(utf8Result, "%c", (char)inCode);
            utf8Result[4] = '\0';
            return utf8Result;
        case 2:
            sprintf(utf8Result, "%c%c", (char)(0xC0 | (inCode >> 6)), (char)(0x80 | (inCode & 0x3F)));
            utf8Result[4] = '\0';
            return utf8Result ;
        case 3:
            sprintf(utf8Result, "%c%c%c", (char)(0xE0 | (inCode >> 12)), (char)(0x80 | ((inCode >> 6) & 0x3F)), (char)(0x80 | (inCode & 0x3F)));
            utf8Result[4] = '\0';
            return utf8Result;
        case 4:
            sprintf(utf8Result, "%c%c%c%c", (char)(0xF0 | (inCode >> 18)), (char)(0x80 | ((inCode >> 12) & 0x3F)), (char)(0x80 | ((inCode >> 6) & 0x3F)), (char)(0x80 | (inCode & 0x3F)));
            utf8Result[4] = '\0';
            return utf8Result;
    }
    return "\0";
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
            else if (k == KEY_LEFT){}
            else if (k == KEY_RIGHT){}
            else if (k == KEY_UP){}
            else if (k == KEY_DOWN){}
            else if (k == KEY_ESCAPE) {
                drawSmall(inScreen.xyLimits.minX, inScreen.xyLimits.maxX, inScreen.xyLimits.minY, inScreen.xyLimits.maxY, primaryScreen);
                return false;
            }
        }
    }
    return false;

}