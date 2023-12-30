#ifndef UI_STRUCTS_H
#define UI_STRUCTS_H
#include "project_headers.h"

const int VECT_MAX = 400;

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