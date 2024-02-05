#ifndef UI_STRUCTS_H
#define UI_STRUCTS_H
#include "project_headers.h"

const int VECT_MAX = 400;

// Define some commonly used unicode characters
const int TL_RAIL = 0x2554;
const int TR_RAIL = 0x2557;
const int BL_RAIL = 0x255A;
const int BR_RAIL = 0x255D;
const int HORZ_RAIL = 0x2550;
const int VERT_RAIL = 0x2551;
const int L_TEE_RAIL = 0x2560;
const int R_TEE_RAIL = 0x2563;
const int TOP_TEE_RAIL = 0x2556;
const int BOT_TEE_RAIL = 0x2569;

const int TL_LINE = 0x256D;
const int TR_LINE = 0x256E;
const int BL_LINE = 0x2570;
const int BR_LINE = 0x256F;
const int HORZ_LINE = 0x2500;
const int VERT_LINE = 0x2502;

const int INV_PENT = 0x26E7;
const int SHLD_CRSS = 0x26E8;
const int RADIOACT = 0x2622;

const int UP_ARROW = 0x2191;
const int DOWN_ARROW = 0x2193;
const int RIGHT_ARROW = 0x2192;
const int LEFT_ARROW = 0x2190;

// Main Options
const std::vector<std::string> options = {"(C)reate New Character", "Create New (P)arty"};

// Contains the Colors and coordinates for one character
struct FrmtChar{
    int symbol;
    color_code symCol;
    color_code bkCol;
    int xCoord;
    int yCoord;
};

struct DrawRange{
    int minX;
    int maxX;
    int minY;
    int maxY;
};

struct Perimeter{
    int uLCorner;
    int uRCorner;
    int bLCorner;
    int bRCorner;
    int topBotWall;
    int sideWalls;
    int leftTee;
    int rightTee;
    color_code cornerColr;
    color_code cornerBGColr;
    color_code wallsColr;
    color_code wallsBGColr;
    Perimeter():uLCorner(0){}
    Perimeter(int uLSym, int uRSym, int bLSym,
        int bRSym, int topBotSym, int sideSym,
        color_code cornerColor, color_code cornerBGColor,
        color_code wallsColor, color_code wallsBGColor):
    uLCorner(uLSym),
    uRCorner(uRSym),
    bLCorner(bLSym),
    bRCorner(bRSym),
    topBotWall(topBotSym),
    sideWalls(sideSym),
    cornerColr(cornerColor),
    cornerBGColr(cornerBGColor),
    wallsColr(wallsColor),
    wallsBGColr(wallsBGColor){}
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

#endif // UI_STRUCTS_H