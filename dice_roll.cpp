#include "dice_roll.h"

unsigned int rollDice(unsigned char sides, bool zeroLowest){
    //srand((unsigned int) time(NULL));
    unsigned char offByOne = 1;
    if(zeroLowest) offByOne = 0;
    return rand()%sides + offByOne;
}