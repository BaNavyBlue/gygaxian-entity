#include "rogueutil.h"
#include <stdlib.h> /* for srand() / rand() */
#include <stdio.h>
#include <vector>
#include <string>

#define NOCOLOR -1

std::size_t horz_char = 0;
std::size_t vert_char = 0;
const int VECT_MAX = 400;

std::vector<std::vector<int>> primaryScreen(VECT_MAX, std::vector<int>(VECT_MAX, ' '));
std::vector<std::vector<color_code>> colorMap(VECT_MAX, std::vector<color_code>(VECT_MAX, GREEN));
std::vector<std::vector<color_code>> backGColorMap(VECT_MAX, std::vector<color_code>(VECT_MAX, BLACK));

void drawPrimary();
void createPrimary();
void createRollScreen();
std::string getUTF(int inCode);

int main(){

    setlocale(LC_ALL, "en_US.UTF-8");
    // /* We wish to use the user's current locale. */
    // setlocale(LC_ALL, "");

    // /* We intend to use wide functions on standard output. */
    // fwide(stdout, 1);

    // /* For Windows compatibility, print out a Byte Order Mark.
    //  * If you save the output to a file, this helps tell Windows
    //  * applications that the file is Unicode.
    //  * Other systems don't need it nor use it.
    // */
    // fputwc(L'\uFEFF', stdout);

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
                drawPrimary();
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
    //createPrimary(primaryScreen);
    cls();
    locate(1,1);
    // for(int i = 0; i < vert_char; ++i){
    //     for(int j = 0; j < horz_char; ++j){
    //         printf("%c", primaryScreen[i][j]);
    //     }
    //     if(i < vert_char - 1) printf("\r\n");
    // }
    //locate(1,1);
    for(std::size_t i = 0; i < vert_char; ++i){
        for(std::size_t j = 0; j < horz_char; ++j){
            int forPrint = primaryScreen[i][j];
            //if(primaryScreen[i][j] == ' '){
                
                locate(j + 1, i + 1);
                if(forPrint > 127){
                    //std::string utfCode = std::to_string(forPrint);
                    std::string utfChar = getUTF(forPrint);

                    //printf("%s\n", utfChar.c_str());
                    colorPrintUTF(colorMap[i][j], backGColorMap[i][j], utfChar.c_str());
                } else {
                    char singleChar = forPrint;
                    colorPrint(colorMap[i][j], backGColorMap[i][j], &singleChar);
                }
            // } else {
            //     colorPrint(GREEN, BLACK, &forPrint);
            // }
        }
        if(i < vert_char - 1) printf("\r\n");
        //locate(horz_char,vert_char);
    }
    locate(1,1);
    //locate(horz_char ,vert_char + 1);
    fflush(stdout);
}

void createPrimary()
{
    std::string line1 = "Welcome To Gygaxian-Entity";
    std::string line2 = "Character Creator";
    std::string options = "|(C)reate New Character||Create New (P)arty|";
    int msg1L = line1.size()/2;
    int msg2L = line2.size()/2;
    for(std::size_t i = 0; i < vert_char; ++i){
        for(std::size_t j = 0; j < horz_char; ++j){
            if(i == vert_char/2 - 1 && j == horz_char/2 - msg1L){
                for(std::size_t k = 0; k < line1.size(); ++k){
                    primaryScreen[i][j] = line1[k];
                    colorMap[i][j] = GREEN;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == vert_char/2 && j == horz_char/2 - msg2L){
                for(std::size_t k = 0; k < line2.size(); ++k){
                    primaryScreen[i][j] = line2[k];
                    colorMap[i][j] = GREEN;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if (i == vert_char - 1 && j == 0){
                for(std::size_t k = 0; k < options.size(); ++k){
                    primaryScreen[i][j] = options[k];
                    colorMap[i][j] = RED;
                    backGColorMap[i][j++] = GREY;
                }
                j--;
            } else if(i == 0 && j == 0){
                primaryScreen[i][j] = 0x2554;
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == 0 && j == horz_char - 1){
                primaryScreen[i][j] = 0x2557;
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == 0) {
                primaryScreen[i][j] = 0x255A; 
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == horz_char - 1){
                primaryScreen[i][j] = 0x255D;
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == 0 || i == vert_char - 2) {
                primaryScreen[i][j] = 0x2550; 
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if (j == 0 || j == horz_char - 1){
                primaryScreen[i][j] = 0x2551;
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            }  else {
                primaryScreen[i][j] = ' ';
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            }
        }
    }

}

void createRollScreen()
{
    std::string strength = "            Strength: ";
    std::string exceptStr = "Exceptional Strength: ";
    std::string intelligence = "        Intelligence: ";
    std::string wisdom = "              Wisdom: ";
    std::string dexterity = "           Dexterity: ";
    std::string charisma = "            Charisma: ";
    std::string constitution = "        Constitution: ";
    std::string stats = "stats";
    for(std::size_t i = 1; i < 10; ++i){
        for(std::size_t j = 1; j < exceptStr.size() + 6; ++j){
            if(i == 1 && j == 1){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = MAGENTA;
                backGColorMap[i][j] = BLACK;
            } else if(i == 2 && j == 3) {
                for(std::size_t k = 0; k < strength.size(); ++k){
                    primaryScreen[i][j] = strength[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 3 && j == 3) {
                for(std::size_t k = 0; k < exceptStr.size(); ++k){
                    primaryScreen[i][j] = exceptStr[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 4 && j == 3) {
                for(std::size_t k = 0; k < intelligence.size(); ++k){
                    primaryScreen[i][j] = intelligence[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 5 && j == 3) {
                for(std::size_t k = 0; k < wisdom.size(); ++k){
                    primaryScreen[i][j] = wisdom[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 6 && j == 3) {
                for(std::size_t k = 0; k < dexterity.size(); ++k){
                    primaryScreen[i][j] = dexterity[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 7 && j == 3) {
                for(std::size_t k = 0; k < charisma.size(); ++k){
                    primaryScreen[i][j] = charisma[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 8 && j == 3) {
                for(std::size_t k = 0; k < constitution.size(); ++k){
                    primaryScreen[i][j] = constitution[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 1 && j == exceptStr.size() + 5){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = MAGENTA;
                backGColorMap[i][j] = BLACK;
            } else if(i == 9 && j == 1) {
                primaryScreen[i][j] = '@'; 
                colorMap[i][j] = MAGENTA;
                backGColorMap[i][j] = BLACK;
            } else if(i == 9 && j == exceptStr.size() + 5){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = MAGENTA;
                backGColorMap[i][j] = BLACK;
            } else if(i == 1 || i == 9) {
                primaryScreen[i][j] = '*';
                colorMap[i][j] = BLUE;
                backGColorMap[i][j] = BLACK;
            } else if (j == 1 || j == exceptStr.size() + 5){
                primaryScreen[i][j] = '*';
                colorMap[i][j] = BLUE;
                backGColorMap[i][j] = BLACK;
            } else {
                primaryScreen[i][j] = ' ';
                colorMap[i][j] = YELLOW;
                backGColorMap[i][j] = BLACK;               
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