#include "ui_util.h"

TextInput::TextInput()
{
  //std::cout << "woopty woo" << std::endl;    
}

void TextInput::createTextInput(DrawRange uRandWidth, Perimeter inPerim, std::string message)
{

    // const int max, int setInt, color_code charColor, color_code bGColor
    _prompt = message;
    _textScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _textScreen->xyLimits.minX = uRandWidth.minX;
    _textScreen->xyLimits.maxX = uRandWidth.minX + 32;
    _textScreen->xyLimits.minY = uRandWidth.minY;
    _textScreen->xyLimits.maxY = uRandWidth.minY + 3;

    _textBoxPerim = inPerim;
    generatePerimeter(*_textScreen, _textBoxPerim);
    PlacePrompt();
    
    drawSmall(_textScreen->xyLimits.minX, _textScreen->xyLimits.maxX, _textScreen->xyLimits.minY, _textScreen->xyLimits.maxY + 1, *_textScreen);
    getText();
}

void TextInput::PlacePrompt()
{
    int promptRow = _textScreen->xyLimits.minY + 1;
    int columnOffset = _textScreen->xyLimits.minX + 1;
    for(int j = 0; j < _prompt.size(); ++j){
        _textScreen->charMap[promptRow][j + columnOffset] = _prompt[j];
        _textScreen->colorMap[promptRow][j + columnOffset] = GREEN;
        _textScreen->bGColorMap[promptRow][j + columnOffset] = BLACK;
    }
}

void TextInput::getText()
{
    showcursor();
    int cursX = _textScreen->xyLimits.minX + 2;
    int cursY = _textScreen->xyLimits.minY + 3;
    int cursLeftLim = cursX;
    locate(cursX, cursY);
    bool gather = true;
    while(gather){
        if(kbhit()){
            int k = getkey();
            switch(k){
                case KEY_NUMDEL:
                case KEY_DELETE:
                case KEY_BKSP:
                case KEY_NRMLDEL:
                    if(_receivedString.size() > 0){
                        _receivedString.pop_back();
                        locate(--cursX, cursY);
                        colorPrintUTF(YELLOW, BLACK, " ");
                        locate(cursX, cursY);
                    }
                    break;
                case KEY_ENTER:
                    if(_receivedString.size() > 0){
                       gather = false;
                    }
                    break;
                default:
                    if(k > 31 && k < 127 || k > 127){
                        if(_receivedString.size() < _textScreen->xyLimits.maxX - 3){
                            _receivedString.push_back(k);
                            colorPrintUTF(YELLOW, BLACK, getUTF(k).c_str());
                            locate(++cursX, cursY);
                        }
                    }
                    break;
            }
        }
    }
    hidecursor();
}

ScreenVals& TextInput::getScreen()
{
    return *_textScreen;
}

std::string TextInput::getAquiredString()
{
    return _receivedString;
}

void OptionWindow::PlaceOptions()
{
    
}

OptionWindow::OptionWindow()
{

}

AlignOptWindow::AlignOptWindow(CHAR_CLASS inClass)
{
    std::string alignList = "Select Alignment:";
    _list.push_back(alignList);
    _optScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    char idx = '0';
    //int nonV = 0;
    for(unsigned i = 0; i < alignPairs.size(); ++i){
            if(alignClassCheck(inClass, alignPairs[i].align)){
                _aList[idx] = alignPairs[i].align;
                _list.push_back(alignPairs[i].alignS + ": " + idx);
                idx++;
            }         
    }
}

void AlignOptWindow::createWindow(DrawRange uRandWidth, Perimeter inPerim)
{
    int maxLen = 0;
    for(int i = 0; i < _list.size(); ++i){
        if(maxLen < _list[i].size()){
            maxLen = _list[i].size();
        }
    }
    _optScreen->xyLimits.minX = uRandWidth.minX;
    _optScreen->xyLimits.minY = uRandWidth.minY;
    _optScreen->xyLimits.maxX = uRandWidth.minX + maxLen + 5;
    _optScreen->xyLimits.maxY = uRandWidth.minY + _list.size() + 1;

    generatePerimeter(*_optScreen, inPerim);
    PlaceOptions();
}

void AlignOptWindow::PlaceOptions()
{
    for(std::size_t i = _optScreen->xyLimits.minY; i < _optScreen->xyLimits.maxY + 1; ++i){
        for(std::size_t j = _optScreen->xyLimits.minX; j < _optScreen->xyLimits.maxX + 1; ++j){
            if((i == _optScreen->xyLimits.minY + 1) && j == _optScreen->xyLimits.minX + 3){
                for(int m = 0; m < _list.size(); ++m){
                    for(int n = 0; n < _list[m].size(); ++n){
                        _optScreen->charMap[i][j] = _list[m][n];
                        _optScreen->colorMap[i][j] = YELLOW;
                        _optScreen->bGColorMap[i][j++] = BLACK;
                    }
                    j = _optScreen->xyLimits.minX + 4; 
                    i++;
                }
            }
        }
    }
    drawSmall(_optScreen->xyLimits.minX, _optScreen->xyLimits.maxX, _optScreen->xyLimits.minY, _optScreen->xyLimits.maxY + 1, *_optScreen);
}

ALIGNMENT AlignOptWindow::getAlign(char inChar)
{
    return _aList[inChar];
}

ScreenVals& AlignOptWindow::getScreen()
{
    return *_optScreen;
}

int AlignOptWindow::getOptIdx()
{
    return _aList.size();
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


// Unicode to UTF-8 conversion created care of CHAT GPT 3.5
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

void generatePerimeter(ScreenVals& inScreen, Perimeter inPerim)
{
    for(std::size_t i = inScreen.xyLimits.minY; i < inScreen.xyLimits.maxY + 1; ++i){
        for(std::size_t j = inScreen.xyLimits.minX; j < inScreen.xyLimits.maxX + 1; ++j){
            if(i == inScreen.xyLimits.minY && j == inScreen.xyLimits.minX){
                inScreen.charMap[i][j] = inPerim.uLCorner;
                inScreen.colorMap[i][j] = inPerim.cornerColr;
                inScreen.bGColorMap[i][j] = inPerim.cornerBGColr;
            } else if(i == inScreen.xyLimits.minY  && j == inScreen.xyLimits.maxX){
                inScreen.charMap[i][j] = inPerim.uRCorner;
                inScreen.colorMap[i][j] = inPerim.cornerColr;
                inScreen.bGColorMap[i][j] = inPerim.cornerBGColr;
            } else if((i == inScreen.xyLimits.maxY) && j == inScreen.xyLimits.minX) {
                inScreen.charMap[i][j] = inPerim.bLCorner;
                inScreen.colorMap[i][j] = inPerim.cornerColr;
                inScreen.bGColorMap[i][j] = inPerim.cornerBGColr;
            } else if((i == inScreen.xyLimits.maxY) && j == inScreen.xyLimits.maxX){
                inScreen.charMap[i][j] = inPerim.bRCorner;
                inScreen.colorMap[i][j] = inPerim.cornerColr;
                inScreen.bGColorMap[i][j] = inPerim.cornerBGColr;
            } else if(i == inScreen.xyLimits.minY || (i == inScreen.xyLimits.maxY)) {
                inScreen.charMap[i][j] = inPerim.topBotWall;
                inScreen.colorMap[i][j] = inPerim.wallsColr;
                inScreen.bGColorMap[i][j] = inPerim.wallsBGColr;
            } else if ((j == inScreen.xyLimits.minX || j == inScreen.xyLimits.maxX) && (i < inScreen.xyLimits.maxY)){
                inScreen.charMap[i][j] = inPerim.sideWalls;
                inScreen.colorMap[i][j] = inPerim.wallsColr;
                inScreen.bGColorMap[i][j] = inPerim.wallsBGColr;
            } else {
                inScreen.charMap[i][j] = ' ';
                inScreen.colorMap[i][j] = GREEN;
                inScreen.bGColorMap[i][j] = BLACK;               
            }
        }
    }
}