#include "rogueutil.h"
#include <stdlib.h> /* for srand() / rand() */
#include <stdio.h>
#include <vector>
#include <string>

#define NOCOLOR -1

int horz_char = 0;
int vert_char = 0;
const int VECT_MAX = 400;

void drawPrimary(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap);
void createPrimary(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap);
void createRollScreen(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap);

int main(){
    
    horz_char = tcols();
    vert_char = trows();

    std::vector<std::vector<int>> primaryScreen(VECT_MAX, std::vector<int>(VECT_MAX));
    std::vector<std::vector<color_code>> colorMap(VECT_MAX, std::vector<color_code>(VECT_MAX, GREEN));
    std::vector<std::vector<color_code>> backGColorMap(VECT_MAX, std::vector<color_code>(VECT_MAX, BLACK));
    hidecursor();
    createPrimary(primaryScreen, colorMap, backGColorMap);
    drawPrimary(primaryScreen, colorMap, backGColorMap);
    
    while(true){
        int new_horz = tcols();
        int new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary(primaryScreen, colorMap, backGColorMap);
            drawPrimary(primaryScreen, colorMap, backGColorMap);
        }
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'c') {
                createRollScreen(primaryScreen, colorMap, backGColorMap);
                drawPrimary(primaryScreen, colorMap, backGColorMap);
            } 
            else if (k == KEY_LEFT){drawPrimary(primaryScreen, colorMap, backGColorMap);}
			else if (k == KEY_RIGHT){drawPrimary(primaryScreen, colorMap, backGColorMap);}
			else if (k == KEY_UP){drawPrimary(primaryScreen, colorMap, backGColorMap);}
			else if (k == KEY_DOWN){drawPrimary(primaryScreen, colorMap, backGColorMap);}
            else if (k == KEY_ESCAPE) {
				break;
			} else {
                createPrimary(primaryScreen, colorMap, backGColorMap);
            }
        }
    }


    cls();
    showcursor();
    return 0;
}

void drawPrimary(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap)
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
    for(int i = 0; i < vert_char; ++i){
        for(int j = 0; j < horz_char; ++j){
            char forPrint = primaryScreen[i][j];
            //if(primaryScreen[i][j] == ' '){
                locate(j + 1, i + 1);
                colorPrint(colorMap[i][j], backGColorMap[i][j], &forPrint);
            // } else {
            //     colorPrint(GREEN, BLACK, &forPrint);
            // }
        }
        if(i < vert_char - 1) printf("\r\n");
    }
    locate(1,1);
    //locate(horz_char ,vert_char + 1);
    fflush(stdout);
}

void createPrimary(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap)
{
    std::string line1 = "Welcome To Gygaxian-Entity";
    std::string line2 = "Character Creator";
    std::string options = "|(C)reate New Character||Create New (P)arty|";
    int msg1L = line1.size()/2;
    int msg2L = line2.size()/2;
    for(int i = 0; i < vert_char; ++i){
        for(int j = 0; j < horz_char; ++j){
            if(i == vert_char/2 - 1 && j == horz_char/2 - msg1L){
                for(int k = 0; k < line1.size(); ++k){
                    primaryScreen[i][j] = line1[k];
                    colorMap[i][j] = GREEN;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == vert_char/2 && j == horz_char/2 - msg2L){
                for(int k = 0; k < line2.size(); ++k){
                    primaryScreen[i][j] = line2[k];
                    colorMap[i][j] = GREEN;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if (i == vert_char - 1 && j == 0){
                for(int k = 0; k < options.size(); ++k){
                    primaryScreen[i][j] = options[k];
                    colorMap[i][j] = RED;
                    backGColorMap[i][j++] = GREY;
                }
                j--;
            } else if(i == 0 && j == 0){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == 0 && j == horz_char - 1){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == 0) {
                primaryScreen[i][j] = '@'; 
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == vert_char - 2 && j == horz_char - 1){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if(i == 0 || i == vert_char - 2) {
                primaryScreen[i][j] = '*'; 
                colorMap[i][j] = GREEN;
                backGColorMap[i][j] = BLACK;
            } else if (j == 0 || j == horz_char - 1){
                primaryScreen[i][j] = '*';
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

void createRollScreen(std::vector<std::vector<int>>& primaryScreen, std::vector<std::vector<color_code>>& colorMap, std::vector<std::vector<color_code>>& backGColorMap)
{
    std::string strength = "            Strength: ";
    std::string exceptStr = "Exceptional Strength: ";
    std::string intelligence = "        Intelligence: ";
    std::string wisdom = "              Wisdom: ";
    std::string dexterity = "           Dexterity: ";
    std::string charisma = "            Charisma: ";
    std::string constitution = "        Constitution: ";
    std::string stats = "stats";
    for(int i = 1; i < 10; ++i){
        for(int j = 1; j < exceptStr.size() + 6; ++j){
            if(i == 1 && j == 1){
                primaryScreen[i][j] = '@';
                colorMap[i][j] = MAGENTA;
                backGColorMap[i][j] = BLACK;
            } else if(i == 2 && j == 3) {
                for(int k = 0; k < strength.size(); ++k){
                    primaryScreen[i][j] = strength[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 3 && j == 3) {
                for(int k = 0; k < exceptStr.size(); ++k){
                    primaryScreen[i][j] = exceptStr[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 4 && j == 3) {
                for(int k = 0; k < intelligence.size(); ++k){
                    primaryScreen[i][j] = intelligence[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 5 && j == 3) {
                for(int k = 0; k < wisdom.size(); ++k){
                    primaryScreen[i][j] = wisdom[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 6 && j == 3) {
                for(int k = 0; k < dexterity.size(); ++k){
                    primaryScreen[i][j] = dexterity[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 7 && j == 3) {
                for(int k = 0; k < charisma.size(); ++k){
                    primaryScreen[i][j] = charisma[k];
                    colorMap[i][j] = YELLOW;
                    backGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 8 && j == 3) {
                for(int k = 0; k < constitution.size(); ++k){
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

