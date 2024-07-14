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
    _textScreen->xyLimits.maxX = uRandWidth.minX + 64;
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

void TextInput::purgeRecieved()
{
    _receivedString.clear();
}

void OptionWindow::PlaceOptions()
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

// void AlignOptWindow::PlaceOptions()
// {
//     for(std::size_t i = _optScreen->xyLimits.minY; i < _optScreen->xyLimits.maxY + 1; ++i){
//         for(std::size_t j = _optScreen->xyLimits.minX; j < _optScreen->xyLimits.maxX + 1; ++j){
//             if((i == _optScreen->xyLimits.minY + 1) && j == _optScreen->xyLimits.minX + 3){
//                 for(int m = 0; m < _list.size(); ++m){
//                     for(int n = 0; n < _list[m].size(); ++n){
//                         _optScreen->charMap[i][j] = _list[m][n];
//                         _optScreen->colorMap[i][j] = YELLOW;
//                         _optScreen->bGColorMap[i][j++] = BLACK;
//                     }
//                     j = _optScreen->xyLimits.minX + 4; 
//                     i++;
//                 }
//             }
//         }
//     }
//     drawSmall(_optScreen->xyLimits.minX, _optScreen->xyLimits.maxX, _optScreen->xyLimits.minY, _optScreen->xyLimits.maxY + 1, *_optScreen);
// }

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

PrintInfo::PrintInfo(Entity chrctr, DrawRange uRandWidth, Perimeter inPerim, ScreenVals& primary, int horz, int vert)
{
    _primaryScreen = std::make_shared<ScreenVals>(primary);
    _horz = horz;
    _vert = vert;
    _character = &chrctr;
    _infoBoxPerim = inPerim;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));

    _firstBox.minX = uRandWidth.minX;
    _firstBox.minY = uRandWidth.minY;

    MakeCharWin();
    MakeStatsWin();
    MakeCmbtWin();
    MakeWealthWin();
    MakeLangWin();
    MakeEscTag();
    SelectTbl();

    for(int i = 0; i < _infoScreen.size(); ++i){
        drawSmall(_infoScreen[i]->xyLimits.minX,
                    _infoScreen[i]->xyLimits.maxX,
                    _infoScreen[i]->xyLimits.minY,
                    _infoScreen[i]->xyLimits.maxY + 1,
                    *_primaryScreen);
    }
    _infoScreen.clear();
}

void PrintInfo::PlaceInfo(int vectIdx)
{
    for(std::size_t i = _infoScreen[vectIdx]->xyLimits.minY; i < _infoScreen[vectIdx]->xyLimits.maxY + 1; ++i){
        for(std::size_t j = _infoScreen[vectIdx]->xyLimits.minX; j < _infoScreen[vectIdx]->xyLimits.maxX + 1; ++j){
            if((i == _infoScreen[vectIdx]->xyLimits.minY + 1) && j == _infoScreen[vectIdx]->xyLimits.minX + 3){
                for(int m = 0; m < _contents[vectIdx].size(); ++m){
                    for(int n = 0; n < _contents[vectIdx][m].size(); ++n){
                        _infoScreen[vectIdx]->charMap[i][j] = _contents[vectIdx][m][n];
                        //_infoScreen[vectIdx]->colorMap[i][j] = YELLOW;
                        _infoScreen[vectIdx]->bGColorMap[i][j++] = BLACK;
                    }
                    j = _infoScreen[vectIdx]->xyLimits.minX + 4; 
                    i++;
                }
            }
        }
    }
}

void PrintInfo::MakeGenTbl(std::vector<std::string> stringVect)
{
    stringVect.push_back("Push [esc] to go back.");
    int maxLen = 0;
    for(int i = 0; i < stringVect.size(); ++i){
        if(maxLen < stringVect[i].size()){
            maxLen = stringVect[i].size();
        }
    }

    int scrnIdx = _infoScreen.size();

    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[scrnIdx]->xyLimits.minX = _infoScreen[0]->xyLimits.minX + 1;
    _infoScreen[scrnIdx]->xyLimits.minY = _infoScreen[0]->xyLimits.minY + 1;
    _infoScreen[scrnIdx]->xyLimits.maxX = _infoScreen[scrnIdx]->xyLimits.minX + maxLen + 7;
    _infoScreen[scrnIdx]->xyLimits.maxY = _infoScreen[scrnIdx]->xyLimits.minY + stringVect.size() + 1;

    generatePerimeter(*_infoScreen[scrnIdx], _infoBoxPerim);
    _contents.push_back(stringVect);

    PlaceInfo(scrnIdx);

    drawSmall(_infoScreen[scrnIdx]->xyLimits.minX,
                _infoScreen[scrnIdx]->xyLimits.maxX,
                _infoScreen[scrnIdx]->xyLimits.minY,
                _infoScreen[scrnIdx]->xyLimits.maxY + 1,
                *_infoScreen[scrnIdx]);
    
    bool waitEsc = true;

    while(waitEsc){        
        if(kbhit()){
            char k = getkey();
            if(k == KEY_ESCAPE){
                waitEsc = false;
            }
        }   
    }

    drawSmall(_infoScreen[scrnIdx]->xyLimits.minX,
                _infoScreen[scrnIdx]->xyLimits.maxX,
                _infoScreen[scrnIdx]->xyLimits.minY,
                _infoScreen[scrnIdx]->xyLimits.maxY + 1,
                *_primaryScreen);

    _infoScreen.pop_back();
    _contents.pop_back();

    for(int i = 0; i < _infoScreen.size(); ++i){
        drawSmall(_infoScreen[i]->xyLimits.minX,
                    _infoScreen[i]->xyLimits.maxX,
                    _infoScreen[i]->xyLimits.minY,
                    _infoScreen[i]->xyLimits.maxY + 1,
                    *_infoScreen[i]);
    }
}


void PrintInfo::SelectTbl()
{
    bool selectWin = true;
    while(selectWin){        
        if(kbhit()){
            char k = getkey();
            if(k == KEY_ESCAPE){
                selectWin = false;
            }
            switch(tolower(k)){
                case 'c':
                    MakeGenTbl(_character->getCharClassSkills()[0]->getClassSkills());
                    break;
                case 'r':
                    MakeGenTbl(_character->getRaceSkills()->getRaceSkills());
                    break;
                case 's':
                    MakeGenTbl(getStrTbl(_character->getStrTbl()));
                    break;
                case 'i':
                    MakeGenTbl(getIntTbl(_character->getIntTbl()));
                    break;
                case 'w':
                    MakeGenTbl(getWisTbl(_character->getWisTbl()));
                    break;
                case 'd':
                    MakeDexTbl();
                    break;
                case 'o':
                    MakeGenTbl(getConsTbl(_character->getConsTbl()));
                    break;
                case 'h':
                    MakeGenTbl(getCharTbl(_character->getCharTbl()));
                    break;
                default:
                    break;
            }    
        }
    }    
}

void PrintInfo::MakeCharWin()
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Character:");
    basicInfo.push_back("Name: ");
    basicInfo.back() += _character->getName();
    basicInfo.push_back("Sex: " + getSex(_character->getSex()));
    basicInfo.push_back("(C)lass: ");
    basicInfo.back() += getClass(_character->getClass()[0]);
    if(_character->getClass().size() > 1){
        for(int i = 1; i < _character->getClass().size(); ++i){
             basicInfo.back() += ", " + getClass(_character->getClass()[i]);
        }
    }

    basicInfo.push_back("Alignment: ");
    basicInfo.back() += getAlign(_character->getAlign());

    basicInfo.push_back("Level: ");
    basicInfo.back() += std::to_string(_character->getLevel()); 

    basicInfo.push_back("(R)ace: ");
    basicInfo.back() += getRace(_character->getRace());

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
    }

    _firstBox.maxX = _firstBox.minX + maxLen + 5;
    _firstBox.maxY = _firstBox.minY + basicInfo.size() + 1;

    _infoScreen[0]->xyLimits.minX = _firstBox.minX;
    _infoScreen[0]->xyLimits.minY = _firstBox.minY;
    _infoScreen[0]->xyLimits.maxX = _firstBox.maxX;
    _infoScreen[0]->xyLimits.maxY = _firstBox.maxY;

    generatePerimeter(*_infoScreen[0], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(0);

    drawSmall(_infoScreen[0]->xyLimits.minX,
                _infoScreen[0]->xyLimits.maxX,
                _infoScreen[0]->xyLimits.minY,
                _infoScreen[0]->xyLimits.maxY + 1,
                *_infoScreen[0]);   
}

void PrintInfo::MakeStatsWin()
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Stats:");
    basicInfo.push_back("(S)trength: " + std::to_string(_character->getStats().strength));
    if(_character->getStats().strength > 17 && (_character->getClass()[0] == FIGHTER || _character->getClass()[0] == PALADIN || _character->getClass()[0] == RANGER)){
        basicInfo.push_back("Exceptional Strength: " + std::to_string(_character->getStats().excStren));
    }
    basicInfo.push_back("(I)ntelligence: " + std::to_string(_character->getStats().intelligence));
    basicInfo.push_back("(W)isdom: " + std::to_string(_character->getStats().wisdom));
    basicInfo.push_back("(D)exterity: " + std::to_string(_character->getStats().dexterity));
    basicInfo.push_back("C(o)nstitution: " + std::to_string(_character->getStats().constitution));
    basicInfo.push_back("C(h)arisma: " + std::to_string(_character->getStats().charisma));
    if(_character->getRace() == DWARF || _character->getRace() == HALF_ORC){
        basicInfo.back() += "(*" + std::to_string(_character->getStats().raceCharisma) + ")";
        basicInfo.push_back("*Race Charisma");
    }

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
    //    for(int j = 0; j < basicInfo[j].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
    //    }
    }

    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[1]->xyLimits.minX = _infoScreen[0]->xyLimits.maxX + 1;
    _infoScreen[1]->xyLimits.minY = _infoScreen[0]->xyLimits.minY;
    _infoScreen[1]->xyLimits.maxX = _infoScreen[0]->xyLimits.maxX + maxLen + 7;
    _infoScreen[1]->xyLimits.maxY = _infoScreen[0]->xyLimits.minY + basicInfo.size() + 1;

    generatePerimeter(*_infoScreen[1], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(1);

    drawSmall(_infoScreen[1]->xyLimits.minX,
                _infoScreen[1]->xyLimits.maxX,
                _infoScreen[1]->xyLimits.minY,
                _infoScreen[1]->xyLimits.maxY + 1,
                *_infoScreen[1]); 
}

void PrintInfo::MakeCmbtWin()
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Health/Combat:");
    basicInfo.push_back("Hit Points: ");
    char varIn[5];
    basicInfo.back() += "(" + std::to_string(_character->getCurHP()) + "/" + std::to_string(_character->getMaxHP()) + ")";
    sprintf(varIn, "%3d", _character->getArmorRating());
    basicInfo.push_back("Armor Rating: ");
    basicInfo.back() += varIn;
    basicInfo.push_back("Experience: ");
    basicInfo.back() += std::to_string(_character->getExperience()[0]);

    for(int i = 1; i < _character->getExperience().size(); ++i){
        basicInfo.back() += ", " + std::to_string(_character->getExperience()[i]);    
    }

    basicInfo.push_back("Weight GP: (");
    sprintf(varIn, "%d", _character->getWeightCarried());
    basicInfo.back() += varIn;
    sprintf(varIn, "%d", _character->getWeightAllowed());
    basicInfo.back() += "/";
    basicInfo.back() += varIn;
    basicInfo.back() += ")";


    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }

    DrawRange healCom;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[2]->xyLimits.minX = healCom.minX = _infoScreen[1]->xyLimits.maxX + 1;
    _infoScreen[2]->xyLimits.minY = healCom.minY = _infoScreen[1]->xyLimits.minY;
    _infoScreen[2]->xyLimits.maxX = healCom.maxX = _infoScreen[1]->xyLimits.maxX + maxLen + 7;
    _infoScreen[2]->xyLimits.maxY = healCom.maxY = _infoScreen[1]->xyLimits.minY + basicInfo.size() + 1; 
    generatePerimeter(*_infoScreen[2], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(2);
    drawSmall(_infoScreen[2]->xyLimits.minX,
              _infoScreen[2]->xyLimits.maxX,
              _infoScreen[2]->xyLimits.minY,
              _infoScreen[2]->xyLimits.maxY + 1,
              *_infoScreen[2]);   
}

void PrintInfo::MakeWealthWin()
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Wealth:");
    basicInfo.push_back("Gold: " + std::to_string(_character->getMoney().gold));
    basicInfo.push_back("Silver: " + std::to_string(_character->getMoney().silver));
    basicInfo.push_back("Copper: " + std::to_string(_character->getMoney().copper));
    basicInfo.push_back("Electrum: " + std::to_string(_character->getMoney().electrum));
    basicInfo.push_back("Platinum: " + std::to_string(_character->getMoney().platinum));

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }

    DrawRange healCom;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[3]->xyLimits.minX = healCom.minX = _infoScreen[2]->xyLimits.maxX + 1;
    _infoScreen[3]->xyLimits.minY = healCom.minY = _infoScreen[2]->xyLimits.minY;
    _infoScreen[3]->xyLimits.maxX = healCom.maxX = _infoScreen[2]->xyLimits.maxX + maxLen + 7;
    _infoScreen[3]->xyLimits.maxY = healCom.maxY = _infoScreen[2]->xyLimits.minY + basicInfo.size() + 1; 
    generatePerimeter(*_infoScreen[3], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(3);
    drawSmall(_infoScreen[3]->xyLimits.minX,
              _infoScreen[3]->xyLimits.maxX,
              _infoScreen[3]->xyLimits.minY,
              _infoScreen[3]->xyLimits.maxY + 1,
              *_infoScreen[3]); 
}

void PrintInfo::MakeLangWin()
{
    std::vector<std::string> basicInfo = getLanguages(_character->getLanguages());

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }

    DrawRange healCom;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[4]->xyLimits.minX = healCom.minX = _infoScreen[3]->xyLimits.maxX + 1;
    _infoScreen[4]->xyLimits.minY = healCom.minY = _infoScreen[3]->xyLimits.minY;
    _infoScreen[4]->xyLimits.maxX = healCom.maxX = _infoScreen[3]->xyLimits.maxX + maxLen + 7;
    _infoScreen[4]->xyLimits.maxY = healCom.maxY = _infoScreen[3]->xyLimits.minY + basicInfo.size() + 1; 
    generatePerimeter(*_infoScreen[4], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(4);
    drawSmall(_infoScreen[4]->xyLimits.minX,
              _infoScreen[4]->xyLimits.maxX,
              _infoScreen[4]->xyLimits.minY,
              _infoScreen[4]->xyLimits.maxY + 1,
              *_infoScreen[4]);     
}

void PrintInfo::MakeEscTag()
{
    std::vector<std::string> basicInfo;
    basicInfo.push_back("Press [esc] to exit");

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }

    color_code border;
    #ifdef _WIN32
    border = RED;
    #else
    border = DARKRED;
    #endif

    DrawRange healCom;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', border, BLACK));
    _infoScreen[5]->xyLimits.minX = healCom.minX = _infoScreen[0]->xyLimits.minX ;
    _infoScreen[5]->xyLimits.minY = healCom.minY = _infoScreen[0]->xyLimits.maxY + 1;
    _infoScreen[5]->xyLimits.maxX = healCom.maxX = _infoScreen[0]->xyLimits.minX + maxLen + 7;
    _infoScreen[5]->xyLimits.maxY = healCom.maxY = _infoScreen[5]->xyLimits.minY + basicInfo.size() + 1; 
    generatePerimeter(*_infoScreen[5], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(5);
    drawSmall(_infoScreen[5]->xyLimits.minX,
              _infoScreen[5]->xyLimits.maxX,
              _infoScreen[5]->xyLimits.minY,
              _infoScreen[5]->xyLimits.maxY + 1,
              *_infoScreen[5]);      
}

void PrintInfo::MakeDexTbl()
{
    std::vector<std::string> basicInfo = getDexTbl(_character->getDexTbl());
    basicInfo.push_back("Press [esc] to close.");

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }
    
    bool isThief = (_character->getClass()[0] == THIEF || _character->getClass()[0] == ASSASSIN);

    DrawRange healCom;
    int screenIdx = _infoScreen.size();
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[screenIdx]->xyLimits.minX = healCom.minX = _infoScreen[0]->xyLimits.minX + 1;
    _infoScreen[screenIdx]->xyLimits.minY = healCom.minY = _infoScreen[0]->xyLimits.minY + 1;
    _infoScreen[screenIdx]->xyLimits.maxX = healCom.maxX = _infoScreen[0]->xyLimits.minX + maxLen + 7;
    _infoScreen[screenIdx]->xyLimits.maxY = healCom.maxY = _infoScreen[0]->xyLimits.minY + basicInfo.size() + 2; 
    generatePerimeter(*_infoScreen[screenIdx], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(screenIdx);
    drawSmall(_infoScreen[screenIdx]->xyLimits.minX,
              _infoScreen[screenIdx]->xyLimits.maxX,
              _infoScreen[screenIdx]->xyLimits.minY,
              _infoScreen[screenIdx]->xyLimits.maxY + 1,
              *_infoScreen[screenIdx]);     

    if(isThief){

        basicInfo.clear();
        basicInfo = getDexTheif(_character->getDexTheif());

        maxLen = 0;
        for(int i = 0; i < basicInfo.size(); ++i){
            //for(int j = 0; j < basicInfo[i].size(); ++j){
                if(maxLen < basicInfo[i].size()){
                    maxLen = basicInfo[i].size();
                }
            //}
        }

        screenIdx = _infoScreen.size();
        _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
        _infoScreen[screenIdx]->xyLimits.minX = healCom.minX = _infoScreen[screenIdx - 1]->xyLimits.maxX + 1;
        _infoScreen[screenIdx]->xyLimits.minY = healCom.minY = _infoScreen[0]->xyLimits.minY + 1;
        _infoScreen[screenIdx]->xyLimits.maxX = healCom.maxX = _infoScreen[screenIdx]->xyLimits.minX + maxLen + 7;
        _infoScreen[screenIdx]->xyLimits.maxY = healCom.maxY = _infoScreen[screenIdx]->xyLimits.minY + basicInfo.size() + 2; 
        generatePerimeter(*_infoScreen[screenIdx], _infoBoxPerim);
        _contents.push_back(basicInfo);

        PlaceInfo(screenIdx);
        drawSmall(_infoScreen[screenIdx]->xyLimits.minX,
                _infoScreen[screenIdx]->xyLimits.maxX,
                _infoScreen[screenIdx]->xyLimits.minY,
                _infoScreen[screenIdx]->xyLimits.maxY + 1,
                *_infoScreen[screenIdx]);         
    }

    bool waitEsc = true;

    while(waitEsc){        
        if(kbhit()){
            char k = getkey();
            if(k == KEY_ESCAPE){
                waitEsc = false;
            }
        }   
    }

    drawSmall(_infoScreen[screenIdx]->xyLimits.minX,
                _infoScreen[screenIdx]->xyLimits.maxX,
                _infoScreen[screenIdx]->xyLimits.minY,
                _infoScreen[screenIdx]->xyLimits.maxY + 1,
                *_primaryScreen);

    _infoScreen.pop_back();
    _contents.pop_back();

    if(isThief){
        screenIdx = _infoScreen.size() - 1;
        drawSmall(_infoScreen[screenIdx]->xyLimits.minX,
                    _infoScreen[screenIdx]->xyLimits.maxX,
                    _infoScreen[screenIdx]->xyLimits.minY,
                    _infoScreen[screenIdx]->xyLimits.maxY + 1,
                    *_primaryScreen);

        _infoScreen.pop_back();
        _contents.pop_back();        
    }

    for(int i = 0; i < _infoScreen.size(); ++i){
        drawSmall(_infoScreen[i]->xyLimits.minX,
                    _infoScreen[i]->xyLimits.maxX,
                    _infoScreen[i]->xyLimits.minY,
                    _infoScreen[i]->xyLimits.maxY + 1,
                    *_infoScreen[i]);
    }
}

void PrintInfo::MakeRaceSkills()
{
    std::vector<std::string> basicInfo = _character->getRaceSkills()->getRaceSkills();

    int maxLen = 0;
    for(int i = 0; i < basicInfo.size(); ++i){
        //for(int j = 0; j < basicInfo[i].size(); ++j){
            if(maxLen < basicInfo[i].size()){
                maxLen = basicInfo[i].size();
            }
        //}
    }

    DrawRange healCom;
    _infoScreen.push_back(std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK));
    _infoScreen[10]->xyLimits.minX = healCom.minX = _infoScreen[0]->xyLimits.minX;
    _infoScreen[10]->xyLimits.minY = healCom.minY = _infoScreen[8]->xyLimits.maxY + 1;
    _infoScreen[10]->xyLimits.maxX = healCom.maxX = _infoScreen[0]->xyLimits.minX + maxLen + 7;
    _infoScreen[10]->xyLimits.maxY = healCom.maxY = _infoScreen[8]->xyLimits.maxY + basicInfo.size() + 2; 
    generatePerimeter(*_infoScreen[10], _infoBoxPerim);
    _contents.push_back(basicInfo);

    PlaceInfo(10);
    drawSmall(_infoScreen[10]->xyLimits.minX,
              _infoScreen[10]->xyLimits.maxX,
              _infoScreen[10]->xyLimits.minY,
              _infoScreen[10]->xyLimits.maxY + 1,
              *_infoScreen[10]);     
}

void PrintInfo::MakeThiefDexTbl()
{

}

void PrintInfo::createPrimary()
{

    color_code border;
    #ifdef _WIN32
    border = RED;
    #else
    border = DARKRED;
    #endif

    std::string line1 = "Welcome To Gygaxian-Entity";
    std::string line2 = "Character Creator";
    std::string options = "[ESC] to Quit";
    std::string options1 = "(C)reate New Character";
    std::string options2 = "Create New (P)arty";
    int msg1L = line1.size()/2;
    int msg2L = line2.size()/2;
    for(std::size_t i = 0; i < _vert; ++i){
        for(std::size_t j = 0; j < _horz; ++j){
            if(i == _vert/2 - 1 && j == _horz/2 - msg1L){
                for(std::size_t k = 0; k < line1.size(); ++k){
                    _primaryScreen->charMap[i][j] = line1[k];
                    _primaryScreen->colorMap[i][j] = GREEN;
                    _primaryScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == _vert/2 && j == _horz/2 - msg2L){
                for(std::size_t k = 0; k < line2.size(); ++k){
                    _primaryScreen->charMap[i][j] = line2[k];
                    _primaryScreen->colorMap[i][j] = GREEN;
                    _primaryScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if (i == _vert - 1 && j == 0){
                _primaryScreen->charMap[i][j] = 0x2551;
                _primaryScreen->colorMap[i][j] = border;
                _primaryScreen->bGColorMap[i][j++] = WHITE;
                for(std::size_t k = 0; k < options.size(); ++k){
                    _primaryScreen->charMap[i][j] = options[k];
                    _primaryScreen->colorMap[i][j] = border;
                    _primaryScreen->bGColorMap[i][j++] = WHITE;
                }
                _primaryScreen->charMap[i][j] = 0x2551;
                _primaryScreen->colorMap[i][j] = border;
                _primaryScreen->bGColorMap[i][j++] = WHITE;
                for(std::size_t k = 0; k < options2.size(); ++k){
                    _primaryScreen->charMap[i][j] = options2[k];
                    _primaryScreen->colorMap[i][j] = border;
                    _primaryScreen->bGColorMap[i][j++] = WHITE;
                }
                _primaryScreen->charMap[i][j] = 0x2551;
                _primaryScreen->colorMap[i][j] = border;
                _primaryScreen->bGColorMap[i][j++] = WHITE;
                //j--;
            } else if(i == 0 && j == 0){
                _primaryScreen->charMap[i][j] = 0x2554;
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            } else if(i == 0 && j == _horz - 1){
                _primaryScreen->charMap[i][j] = 0x2557;
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            } else if(i == _vert - 2 && j == 0) {
                _primaryScreen->charMap[i][j] = 0x255A; 
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            } else if(i == _vert - 2 && j == _horz - 1){
                _primaryScreen->charMap[i][j] = 0x255D;
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            } else if(i == 0 || i == _vert - 2) {
                _primaryScreen->charMap[i][j] = 0x2550; 
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            } else if ((j == 0 || j == _horz - 1) && i < _vert - 1){
                _primaryScreen->charMap[i][j] = 0x2551;
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            }  else {
                _primaryScreen->charMap[i][j] = 0x0020;
                _primaryScreen->colorMap[i][j] = GREEN;
                _primaryScreen->bGColorMap[i][j] = BLACK;
            }
        }
    }

}

void PrintInfo::drawPrimary()
{
    cls();
    locate(1,1);
    for(std::size_t i = 0; i < _vert; ++i){
        for(std::size_t j = 0; j < _horz; ++j){
            int forPrint = _primaryScreen->charMap[i][j];
                
                locate(j + 1, i + 1);
                    std::string utfChar = getUTF(forPrint);
                    colorPrintUTF(_primaryScreen->colorMap[i][j], _primaryScreen->bGColorMap[i][j], utfChar.c_str());
        }
    }
    locate(1,1);
    fflush(stdout);
}

WarnMessage::WarnMessage(std::string warning, std::string question)
{

    color_code border;
    #ifdef _WIN32
    border = RED;
    #else
    border = DARKRED;
    #endif

    Perimeter warnPerim(RADIOACT, RADIOACT, RADIOACT, RADIOACT, INV_PENT, INV_PENT, YELLOW, BLACK, border, BLACK);
    std::size_t horz_char = tcols();
    std::size_t vert_char = trows();

    int maxLen = warning.size();

    if(maxLen < question.size()){
        maxLen = question.size();
    }
    
    _warnScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', border, BLACK);
    DrawRange boxCorners;
    _warnScreen->xyLimits.minX = boxCorners.minX = horz_char / 2 - maxLen / 2 - 5;
    _warnScreen->xyLimits.minY = boxCorners.minY = vert_char / 2 - 4;
    _warnScreen->xyLimits.maxX = boxCorners.maxX = horz_char / 2 + maxLen / 2 + 5;
    _warnScreen->xyLimits.maxY = boxCorners.maxY = vert_char / 2 + 4;

    generatePerimeter(*_warnScreen, warnPerim);

    for(int i = 0; i < warning.size(); ++i){
        _warnScreen->charMap[boxCorners.minY + 3][boxCorners.minX + 5 + i] = warning[i];
        _warnScreen->colorMap[boxCorners.minY + 3][boxCorners.minX + 5 + i] = border;
        _warnScreen->bGColorMap[boxCorners.minY + 3][boxCorners.minX + 5 + i] = BLACK;
    }

    for(int i = 0; i < question.size(); ++i){
        _warnScreen->charMap[boxCorners.minY + 5][boxCorners.minX + 5 + i] = question[i];
        _warnScreen->colorMap[boxCorners.minY + 5][boxCorners.minX + 5 + i] = border;
        _warnScreen->bGColorMap[boxCorners.minY + 5][boxCorners.minX + 5 + i] = BLACK;
    }

    drawSmall(boxCorners.minX, boxCorners.maxX, boxCorners.minY, boxCorners.maxY + 1, *_warnScreen);    
}

bool WarnMessage::waitForAnswer()
{
    while(true){        
        if(kbhit()){
            char k = getkey();
            switch(tolower(k)){
                case 'y':
                    return false;
                case 'n':
                    return true;
            }    
        }
    }
}

ScreenVals& WarnMessage::getScreen()
{
    return *_warnScreen;
}

void drawSmall(int startX, int maxX, int startY, int maxY, const ScreenVals& inScreen)
{
    for(int i = startY; i < maxY; ++i){
        for(int j = startX; j < maxX + 1; ++j){
            int forPrint = inScreen.charMap.at(i).at(j);
            //if(primaryScreen[i][j] == ' '){
                
                locate(j + 1, i + 1);
                // if(forPrint > 127){
                    //std::string utfCode = std::to_string(forPrint);
                    std::string utfChar = getUTF(forPrint);

                    //printf("%s\n", utfChar.c_str());
                    colorPrintUTF(inScreen.colorMap.at(i).at(j), inScreen.bGColorMap.at(i).at(j), utfChar.c_str());
                // } else {
                //     char singleChar[2];
                //     singleChar[0] = forPrint;
                //     singleChar[1] = '\0';
                //     colorPrint(inScreen.colorMap.at(i).at(j), inScreen.bGColorMap.at(i).at(j), singleChar);
                // }            
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
                //inScreen.colorMap[i][j] = GREEN;
                //inScreen.bGColorMap[i][j] = BLACK;               
            }
        }
    }
}

// void ChooseOpt::PlaceOptions()
// {
//     for(std::size_t i = _optScreen->xyLimits.minY; i < _optScreen->xyLimits.maxY + 1; ++i){
//         for(std::size_t j = _optScreen->xyLimits.minX; j < _optScreen->xyLimits.maxX + 1; ++j){
//             if((i == _optScreen->xyLimits.minY + 1) && j == _optScreen->xyLimits.minX + 3){
//                 for(int m = 0; m < _list.size(); ++m){
//                     for(int n = 0; n < _list[m].size(); ++n){
//                         _optScreen->charMap[i][j] = _list[m][n];
//                         _optScreen->colorMap[i][j] = YELLOW;
//                         _optScreen->bGColorMap[i][j++] = BLACK;
//                     }
//                     j = _optScreen->xyLimits.minX + 4; 
//                     i++;
//                 }
//             }
//         }
//     }
//     drawSmall(_optScreen->xyLimits.minX, _optScreen->xyLimits.maxX, _optScreen->xyLimits.minY, _optScreen->xyLimits.maxY + 1, *_optScreen);
// }

ChooseOpt::ChooseOpt(std::vector<std::string> inOpts)
{
    _list.push_back(inOpts.at(0));
    char idx = '0';
    for(int i = 1; i < inOpts.size(); ++i){
        _list.push_back(inOpts[i] + ": " + idx++ + ")");
    }
    _optScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    DrawRange strtCrn;
    strtCrn.minX = 1;
    strtCrn.minY = 1;
    Perimeter inPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
    createWindow(strtCrn, inPerim);
}

void ChooseOpt::createWindow(DrawRange uRandWidth, Perimeter inPerim)
{
    int maxLen = 0;
    for(int i = 0; i < _list.size(); ++i){
        if(maxLen < _list.at(i).size()){
            maxLen = _list.at(i).size();
        }
    }
    _optScreen->xyLimits.minX = uRandWidth.minX;
    _optScreen->xyLimits.minY = uRandWidth.minY;
    _optScreen->xyLimits.maxX = uRandWidth.minX + maxLen + 6;
    _optScreen->xyLimits.maxY = uRandWidth.minY + _list.size() + 1;

    generatePerimeter(*_optScreen, inPerim);
    PlaceOptions();
}

ScreenVals& ChooseOpt::getScreen()
{
    return *_optScreen;
}

char ChooseOpt::getChoice(char optChoice)
{
    _choice = optChoice;
    return _choice;
}

RollScreen::RollScreen(stats inStats, ScreenVals& primaryScreen)
{
    int maxLen = 0;
    int addRow = 0;

    rollScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);

    Perimeter rollPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
    std::string choices = "Keep current roll? (y/n).";

    char tmp[4];
    sprintf(tmp, "%3u", inStats.strength);
    std::string strength = "            Strength:";
    strength += tmp;
    strength  += " Fails - " + strenFails(inStats);
    sprintf(tmp, "%3u", inStats.excStren);
    std::string exceptStr = "Exceptional Strength:";
    exceptStr += tmp;
    exceptStr += " Fighter, Paladin and Ranger only!";
    sprintf(tmp, "%3u", inStats.intelligence);
    std::string intelligence = "        Intelligence:";
    intelligence += tmp;
    intelligence += " Fails - " + intFails(inStats);
    sprintf(tmp, "%3u", inStats.wisdom);
    std::string wisdom = "              Wisdom:";
    wisdom += tmp;
    wisdom += " Fails - " + wisFails(inStats);
    sprintf(tmp, "%3u", inStats.dexterity);
    std::string dexterity = "           Dexterity:";
    dexterity += tmp;
    dexterity += " Fails - " + dexFails(inStats);
    sprintf(tmp, "%3u", inStats.charisma);
    std::string charisma = "            Charisma:";
    charisma += tmp;
    charisma += " Fails - " + charisFails(inStats);
    sprintf(tmp, "%3u", inStats.constitution);
    std::string constitution = "        Constitution:";
    constitution += tmp;
    constitution += " Fails - " + consFails(inStats);
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

    if(inStats.strength > 17){
        addRow = 1;   
    } else {
        addRow = 0;
    }
    
    // if(prevMax < maxLen){
    //     prevMax = maxLen;
    // }

    // if(prevRow < addRow){
    //     prevRow = addRow;
    // }
    // drawSmall(1, prevMax + 5, 1, 10 + prevRow, primaryScreen);

    rollScreen->xyLimits.minX = 1;
    rollScreen->xyLimits.maxX = maxLen + 5;
    rollScreen->xyLimits.minY = 1;
    rollScreen->xyLimits.maxY = 10 + addRow - 2;


    
    generatePerimeter(*rollScreen, rollPerim);

    rollScreen->xyLimits.maxY = 10 + addRow;

    color_code border;
    #ifdef _WIN32
    border = RED;
    #else
    border = DARKRED;
    #endif

    for(std::size_t i = 1; i < 10 + addRow; ++i){
        for(std::size_t j = 1; j < maxLen + 6; ++j){
            if(i == 2 && j == 3) {
                for(std::size_t k = 0; k < strength.size(); ++k){
                    rollScreen->charMap[i][j] = strength[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 2 + addRow && j == 3 && addRow) {
                for(std::size_t k = 0; k < exceptStr.size(); ++k){
                    rollScreen->charMap[i][j] = exceptStr[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 3 + addRow && j == 3) {
                for(std::size_t k = 0; k < intelligence.size(); ++k){
                    rollScreen->charMap[i][j] = intelligence[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 4 + addRow && j == 3) {
                for(std::size_t k = 0; k < wisdom.size(); ++k){
                    rollScreen->charMap[i][j] = wisdom[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 5 + addRow && j == 3) {
                for(std::size_t k = 0; k < dexterity.size(); ++k){
                    rollScreen->charMap[i][j] = dexterity[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 6 + addRow && j == 3) {
                for(std::size_t k = 0; k < charisma.size(); ++k){
                    rollScreen->charMap[i][j] = charisma[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
            } else if(i == 7 + addRow && j == 3) {
                for(std::size_t k = 0; k < constitution.size(); ++k){
                    rollScreen->charMap[i][j] = constitution[k];
                    rollScreen->colorMap[i][j] = YELLOW;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                j--;
        } else if(i == 9 + addRow && j == 3) {
                rollScreen->charMap[i][j - 2] = ' ';
                rollScreen->colorMap[i][j - 2] = border;
                rollScreen->bGColorMap[i][j- 2] = BLACK;
                rollScreen->charMap[i][j - 1] = ' ';
                rollScreen->colorMap[i][j - 1] = border;
                rollScreen->bGColorMap[i][j- 1] = BLACK;
                for(std::size_t k = 0; k < choices.size(); ++k){
                    rollScreen->charMap[i][j] = choices[k];
                    rollScreen->colorMap[i][j] = border;
                    rollScreen->bGColorMap[i][j++] = BLACK;
                }
                int x = 0 ;
                while(j + x < maxLen + 5){
                    rollScreen->charMap[i][j + x] = ' ';
                    rollScreen->colorMap[i][j + x] = border;
                    rollScreen->bGColorMap[i][j + x] = BLACK;
                    ++x;
                }
                j--;                 
            } 
        }       
    }
    drawSmall(1, rollScreen->xyLimits.maxX, 1, rollScreen->xyLimits.maxY, *rollScreen);
}

ScreenVals& RollScreen::getScreen()
{
   return *rollScreen;
}

bool doesRecordExist(std::string name, std::string path, std::string suffix)
{
    std::string file = path + name + suffix;
    std::ifstream charJson(file);
    return charJson.good(); 
}

ListHighlight::ListHighlight()
{

}

ListHighlight::ListHighlight(std::vector<std::string> inList, ScreenVals &primaryScreen, std::string inName, std::vector<int> inOptions, Perimeter inPerim, DrawRange inRange)
{
    _perim = inPerim;
    _list = inList;
    _title = inName;
    _options = inOptions;
    _cornerDims = inRange;
    _listScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _primaryScreen = std::make_shared<ScreenVals>(primaryScreen);
    createListPerimeter(*_listScreen, _options);
    createListScreen(*_listScreen, _list, _title, _highlightList);
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
}

void ListHighlight::navigateSelection()
{

}

// void ListHighlightPartySelect::navigateSelection()
// {
//     char choice;
//     std::size_t horz_char = tcols();
//     std::size_t vert_char = trows();
//     std::vector<std::string> _optMain = {"[ESC] Back", "(S)elect Party"};
//     while(true){
//         std::size_t new_horz = tcols();
//         std::size_t new_vert = trows();
//         if(horz_char != new_horz || vert_char != new_vert){
//             horz_char = new_horz;
//             vert_char = new_vert;
//             createPrimary(*_primaryScreen, _optMain);
//             drawPrimary(*_primaryScreen);

//             _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
//             _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
//             _listScreen->xyLimits.maxX = _cornerDims.maxX = horz_char / 3;
//             _listScreen->xyLimits.maxY = _cornerDims.maxY = vert_char - 3;
//             //createListPerimeter(*_listScreen, _options);
//             //createListScreen(*_listScreen, _list, _title);
//             listNavigate();
//             drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
//         }
        
//         if(kbhit()){
//             char k = getkey();
//             if(std::tolower(k) == 'a') {
//                 bool idx_found = false;
//                 // for(int i = 0; i < _destIdx.size(); ++i){
//                 //     if(_currPos == _destIdx[i]){
//                 //         idx_found = true;
//                 //     }
//                 // }
//                 if(!idx_found){
                
//                 }
//             } else if(std::tolower(k) == 'v'){
//             DrawRange infoRange;
//                 // if(_parties.size() > 0){
//                 //     infoRange.minX = 1;
//                 //     infoRange.minY = 1;
//                 //     Perimeter rollPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
//                 //     PrintInfo showChar(_players.at(_currPos), infoRange, rollPerim, *_primaryScreen, tcols(), trows());
//                 //     listNavigate();
//                 //     createListPerimeter(*_destListScreen, _destOptions);
//                 //     createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
//                 //     drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
//                 //     drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
//                 //               _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
//                 //               *_destListScreen);
//                 // }
//             } else if(k == KEY_UP){
//                 if(_currPos > 0){
//                     _prevPos = _currPos;
//                     _currPos--;
//                     listNavigate();
//                 }
//             } else if(k == KEY_DOWN){
//                 if(_currPos < _list.size() - 1){
//                     _prevPos = _currPos;
//                     _currPos++;
//                     listNavigate();
//                 }
//             // } else if (k == KEY_RIGHT){
//             //     if(_destList.size() > 0){
//             //         _highlightDest = true;
//             //         _highlightList = false;
//             //         k = navigateDestination();
//             //         if(std::tolower(k) == 's'){
//             //             if(_destList.size() > 0){
//             //                 drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
//             //                 drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
//             //                         _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
//             //                         *_primaryScreen);
//             //                 TextInput partyName;
//             //                 Perimeter textPerim(TL_LINE, TR_LINE, BL_LINE, BR_LINE, HORZ_LINE, VERT_LINE, MAGENTA, BLACK, BLUE, BLACK);
                            
//             //                 bool confirmName = false;
                            
//             //                 std::vector<std::string> memberPaths;
//             //                 for(int i = 0; i < _destIdx.size(); ++i){
//             //                     memberPaths.push_back(_pathList[_destIdx[i]]);
//             //                 }

//             //                 do{
//             //                     confirmName = false;
//             //                     partyName.createTextInput(_cornerDims,textPerim,"Party Name:");
//             //                     if(doesRecordExist(partyName.getAquiredString(), "parties/", ".json")){
//             //                         WarnMessage nameExists("Party name already in use", "Overwrite? (y/n)");
//             //                         confirmName = nameExists.waitForAnswer();
//             //                         drawSmall(nameExists.getScreen().xyLimits.minX, nameExists.getScreen().xyLimits.maxX, nameExists.getScreen().xyLimits.minY, nameExists.getScreen().xyLimits.maxY + 1, *_primaryScreen);
//             //                     }

//             //                     if(confirmName){
//             //                         partyName.purgeRecieved();
//             //                     }

//             //                 }while(confirmName);
                            
//             //                 SaveParty saveMe(partyName.getAquiredString(), memberPaths);
//             //                 drawSmall(partyName.getScreen().xyLimits.minX, partyName.getScreen().xyLimits.maxX, partyName.getScreen().xyLimits.minY, partyName.getScreen().xyLimits.maxY + 1, *_primaryScreen);
//             //                 break;
//             //             }
//             //         } else if(k == KEY_ESCAPE){
//             //             // drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
//             //             // drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
//             //             //         _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
//             //             //         *_primaryScreen);
//             //             break;
//             //         }
//             //     }
//             } else if(std::tolower(k) == 's'){
//                 // if(_destList.size() > 0){
//                 //     drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
//                 //     drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
//                 //             _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
//                 //             *_primaryScreen);
//                 //     TextInput partyName;
//                 //     Perimeter textPerim(TL_LINE, TR_LINE, BL_LINE, BR_LINE, HORZ_LINE, VERT_LINE, MAGENTA, BLACK, BLUE, BLACK);
                    
//                 //     bool confirmName = false;
                    
//                 //     std::vector<std::string> memberPaths;
//                 //     for(int i = 0; i < _destIdx.size(); ++i){
//                 //         memberPaths.push_back(_pathList[_destIdx[i]]);
//                 //     }

//                 //     do{
//                 //         confirmName = false;
//                 //         partyName.createTextInput(_cornerDims,textPerim,"Party Name:");
//                 //         if(doesRecordExist(partyName.getAquiredString(), "parties/", ".json")){
//                 //             WarnMessage nameExists("Party name already in use", "Overwrite? (y/n)");
//                 //             confirmName = nameExists.waitForAnswer();
//                 //             drawSmall(nameExists.getScreen().xyLimits.minX, nameExists.getScreen().xyLimits.maxX, nameExists.getScreen().xyLimits.minY, nameExists.getScreen().xyLimits.maxY + 1, *_primaryScreen);
//                 //         }

//                 //         if(confirmName){
//                 //             partyName.purgeRecieved();
//                 //         }

//                 //     }while(confirmName);
                    
//                 //     SaveParty saveMe(partyName.getAquiredString(), memberPaths);
//                 //     drawSmall(partyName.getScreen().xyLimits.minX, partyName.getScreen().xyLimits.maxX, partyName.getScreen().xyLimits.minY, partyName.getScreen().xyLimits.maxY + 1, *_primaryScreen);
//                 //     break;
//                 // }
//             } else if (k == KEY_ESCAPE) {
//                 // createPrimary(*_primaryScreen, options);
//                 // drawPrimary(*_primaryScreen);
//                 // drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
//                 // drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
//                 //         _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
//                 //         *_primaryScreen);
//                 break;
//             }
//         }
//     }
// }

void ListHighlight::listNavigate()
{

}

void ListHighlight::createListScreen(ScreenVals& inScreen, std::vector<std::string> inList, std::string inTitle, bool highlight)
{
    color_code textCol;
    color_code bgCol;
    #ifdef _WIN32
        textCol = BLUE;
        bgCol = GREY;
    #else
        textCol = DARKBLUE;
        bgCol = WHITE;
    #endif


    int titlePos = inScreen.xyLimits.maxX - (inScreen.xyLimits.maxX - inScreen.xyLimits.minX) / 2 - inTitle.size() / 2 - 1;
    // Print Title
    for(int i = 0; i < inTitle.size(); ++i){
        inScreen.charMap[inScreen.xyLimits.minY + 1][i + titlePos] = inTitle[i];
        inScreen.colorMap[inScreen.xyLimits.minY + 1][i + titlePos] = YELLOW;
    }

    for(int i = inScreen.xyLimits.minY + 3; i < inScreen.xyLimits.maxY - 1; ++i){
        int strdx = i - (inScreen.xyLimits.minY + 3);
        if (strdx < inList.size()){
            int limit = inList[strdx].size();

            if(limit > inScreen.xyLimits.maxX - 2){
                limit = inScreen.xyLimits.maxX - 2;
            }

            for(int j = 0; j < limit; ++j){
                if(strdx == 0 && highlight){
                    inScreen.charMap[i][j + inScreen.xyLimits.minX + 1] = inList[strdx][j];
                    inScreen.colorMap[i][j + inScreen.xyLimits.minX + 1] = textCol;
                    inScreen.bGColorMap[i][j + inScreen.xyLimits.minX + 1] = bgCol;
                } else {
                    inScreen.charMap[i][j + inScreen.xyLimits.minX + 1] = inList[strdx][j];
                    inScreen.colorMap[i][j + inScreen.xyLimits.minX + 1] = YELLOW;
                }
            }
        }
    }
}

void ListHighlight::createListPerimeter(ScreenVals& inScreen, std::vector<int> inOpts)
{
    //printf("ListPerimeter\r\n");
    color_code optionClr;
    #ifdef _WIN32
    optionClr = RED;
    #else
    optionClr = DARKRED;
    #endif

    for(int i = inScreen.xyLimits.minY; i <= inScreen.xyLimits.maxY; ++i){
        for(int j = inScreen.xyLimits.minX; j <= inScreen.xyLimits.maxX; ++j){
            if(i == inScreen.xyLimits.minY && j == inScreen.xyLimits.minX){
                inScreen.charMap[i][j] = _perim.uLCorner;
                inScreen.colorMap[i][j] = _perim.cornerColr;
            } else if(i == inScreen.xyLimits.minY && j == inScreen.xyLimits.maxX){
                inScreen.charMap[i][j] = _perim.uRCorner;
                inScreen.colorMap[i][j] = _perim.cornerColr;     
            } else if(i == inScreen.xyLimits.minY){
                inScreen.charMap[i][j] = _perim.topBotWall;
                inScreen.colorMap[i][j] = _perim.cornerColr; 
            } else if(i == inScreen.xyLimits.minY + 2 && j == inScreen.xyLimits.minX){
                inScreen.charMap[i][j] = _perim.leftTee;
                inScreen.colorMap[i][j] = _perim.cornerColr; 
            } else if(i == inScreen.xyLimits.minY + 2 && j == inScreen.xyLimits.maxX){
                inScreen.charMap[i][j] = _perim.rightTee;
                inScreen.colorMap[i][j] = _perim.cornerColr; 
            } else if(i == inScreen.xyLimits.minY + 2){
                inScreen.charMap[i][j] = _perim.topBotWall;
                inScreen.colorMap[i][j] = _perim.cornerColr; 
            } else if(i == (inScreen.xyLimits.maxY - 1) && j == inScreen.xyLimits.minX){
                inScreen.charMap[i][j] = _perim.bLCorner;
                inScreen.colorMap[i][j] = _perim.cornerColr;                
            } else if(i == (inScreen.xyLimits.maxY - 1) && j == inScreen.xyLimits.maxX){
                inScreen.charMap[i][j] = _perim.bRCorner;
                inScreen.colorMap[i][j] = _perim.cornerColr;                
            } else if(j == inScreen.xyLimits.minX && i < inScreen.xyLimits.maxY - 1){
                inScreen.charMap[i][j] = _perim.sideWalls;
                inScreen.colorMap[i][j] = _perim.cornerColr;                
            } else if(j == inScreen.xyLimits.maxX && i < inScreen.xyLimits.maxY - 1){
                inScreen.charMap[i][j] = _perim.sideWalls;
                inScreen.colorMap[i][j] = _perim.cornerColr;                
            } else if( i == inScreen.xyLimits.maxY - 1){
                inScreen.charMap[i][j] = _perim.topBotWall;
                inScreen.colorMap[i][j] = _perim.cornerColr;                
            } else if(i == inScreen.xyLimits.maxY && j - inScreen.xyLimits.minX < inOpts.size()){
                int stridx = j - inScreen.xyLimits.minX;
                if(stridx < inOpts.size()){
                    inScreen.charMap[i][j] = inOpts[stridx];
                    inScreen.colorMap[i][j] = optionClr;
                    //printf("poopy ");
                }
            } else {
                inScreen.charMap[i][j] = ' ';
                inScreen.bGColorMap[i][j] = BLACK;
            }
        }
    }
}

ScreenVals& ListHighlight::getScreen()
{
    return *_listScreen;
}

ListHighlightPair::ListHighlightPair(std::vector<std::string>& inList, std::vector<Entity>& inPlayers,
                                     std::vector<std::string>& inPaths, ScreenVals &primaryScreen,
                                     std::string inName, std::string destTitle, std::vector<int> inOptions,
                                     std::vector<int> destOptions, Perimeter inPerim, DrawRange inRange)
{
    _perim = inPerim;
    _list = inList;
    _pathList = inPaths;
    _players = inPlayers;
    _title = inName;
    _destTitle = destTitle;
    _options = inOptions;
    _destOptions = destOptions;
    _cornerDims = inRange;
    _listScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _destListScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _primaryScreen = std::make_shared<ScreenVals>(primaryScreen);
    _listScreen->xyLimits.minX = _cornerDims.minX = inRange.minX;
    _listScreen->xyLimits.minY = _cornerDims.minY = inRange.minY;
    _listScreen->xyLimits.maxX = _cornerDims.maxX = inRange.maxX;
    _listScreen->xyLimits.maxY = _cornerDims.maxY = inRange.maxY;

    _destListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
    _destListScreen->xyLimits.minY = inRange.minY;
    _destListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 2 + 1;
    _destListScreen->xyLimits.maxY = inRange.maxY;
    
    createPrimary(*_primaryScreen, _optMain);
    createListPerimeter(*_listScreen, _options);
    createListScreen(*_listScreen, _list, _title, _highlightList);
    createListPerimeter(*_destListScreen, _destOptions);
    createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
    drawPrimary(*_primaryScreen);
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
              *_destListScreen);
    navigateSelection();
}

void ListHighlightPair::navigateSelection()
{
    char choice;
    std::size_t horz_char = tcols();
    std::size_t vert_char = trows();
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary(*_primaryScreen, _optMain);
            drawPrimary(*_primaryScreen);

            _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
            _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
            _listScreen->xyLimits.maxX = _cornerDims.maxX = horz_char / 3;
            _listScreen->xyLimits.maxY = _cornerDims.maxY = vert_char - 3;

            _destListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
            _destListScreen->xyLimits.minY = _primaryScreen->xyLimits.minY + 1;
            _destListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 2 + 1;
            _destListScreen->xyLimits.maxY = vert_char - 3;

            //createListPerimeter(*_listScreen, _options);
            //createListScreen(*_listScreen, _list, _title);
            listNavigate();
            createListPerimeter(*_destListScreen, _destOptions);
            createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
            drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
            drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                      _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                      *_destListScreen);
        }
        
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'a') {
                bool idx_found = false;
                for(int i = 0; i < _destIdx.size(); ++i){
                    if(_currPos == _destIdx[i]){
                        idx_found = true;
                    }
                }
                if(!idx_found){
                    _destIdx.push_back(_currPos);
                    _destList.push_back(_list[_currPos]);
                    createListPerimeter(*_destListScreen, _destOptions);
                    createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
                    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                              *_destListScreen);
                }
            } else if(std::tolower(k) == 'v'){
            DrawRange infoRange;
                if(_players.size() > 0){
                    infoRange.minX = 1;
                    infoRange.minY = 1;
                    Perimeter rollPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
                    PrintInfo showChar(_players.at(_currPos), infoRange, rollPerim, *_primaryScreen, tcols(), trows());
                    listNavigate();
                    createListPerimeter(*_destListScreen, _destOptions);
                    createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
                    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
                    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                              *_destListScreen);
                }
            } else if(k == KEY_UP){
                if(_currPos > 0){
                    _prevPos = _currPos;
                    _currPos--;
                    listNavigate();
                }
            } else if(k == KEY_DOWN){
                if(_currPos < _list.size() - 1){
                    _prevPos = _currPos;
                    _currPos++;
                    listNavigate();
                }
            } else if (k == KEY_RIGHT){
                if(_destList.size() > 0){
                    _highlightDest = true;
                    _highlightList = false;
                    k = navigateDestination();
                    if(std::tolower(k) == 's'){
                        if(_destList.size() > 0){
                            drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
                            drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                                    _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                                    *_primaryScreen);
                            TextInput partyName;
                            Perimeter textPerim(TL_LINE, TR_LINE, BL_LINE, BR_LINE, HORZ_LINE, VERT_LINE, MAGENTA, BLACK, BLUE, BLACK);
                            
                            bool confirmName = false;
                            
                            std::vector<std::string> memberPaths;
                            for(int i = 0; i < _destIdx.size(); ++i){
                                memberPaths.push_back(_pathList[_destIdx[i]]);
                            }

                            do{
                                confirmName = false;
                                partyName.createTextInput(_cornerDims,textPerim,"Party Name:");
                                if(doesRecordExist(partyName.getAquiredString(), "parties/", ".json")){
                                    WarnMessage nameExists("Party name already in use", "Overwrite? (y/n)");
                                    confirmName = nameExists.waitForAnswer();
                                    drawSmall(nameExists.getScreen().xyLimits.minX, nameExists.getScreen().xyLimits.maxX, nameExists.getScreen().xyLimits.minY, nameExists.getScreen().xyLimits.maxY + 1, *_primaryScreen);
                                }

                                if(confirmName){
                                    partyName.purgeRecieved();
                                }

                            }while(confirmName);
                            
                            SaveParty saveMe(partyName.getAquiredString(), memberPaths);
                            drawSmall(partyName.getScreen().xyLimits.minX, partyName.getScreen().xyLimits.maxX, partyName.getScreen().xyLimits.minY, partyName.getScreen().xyLimits.maxY + 1, *_primaryScreen);
                            break;
                        }
                    } else if(k == KEY_ESCAPE){
                        // drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
                        // drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                        //         _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                        //         *_primaryScreen);
                        break;
                    }
                }
            } else if(std::tolower(k) == 's'){
                if(_destList.size() > 0){
                    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
                    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                            _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                            *_primaryScreen);
                    TextInput partyName;
                    Perimeter textPerim(TL_LINE, TR_LINE, BL_LINE, BR_LINE, HORZ_LINE, VERT_LINE, MAGENTA, BLACK, BLUE, BLACK);
                    
                    bool confirmName = false;
                    
                    std::vector<std::string> memberPaths;
                    for(int i = 0; i < _destIdx.size(); ++i){
                        memberPaths.push_back(_pathList[_destIdx[i]]);
                    }

                    do{
                        confirmName = false;
                        partyName.createTextInput(_cornerDims,textPerim,"Party Name:");
                        if(doesRecordExist(partyName.getAquiredString(), "parties/", ".json")){
                            WarnMessage nameExists("Party name already in use", "Overwrite? (y/n)");
                            confirmName = nameExists.waitForAnswer();
                            drawSmall(nameExists.getScreen().xyLimits.minX, nameExists.getScreen().xyLimits.maxX, nameExists.getScreen().xyLimits.minY, nameExists.getScreen().xyLimits.maxY + 1, *_primaryScreen);
                        }

                        if(confirmName){
                            partyName.purgeRecieved();
                        }

                    }while(confirmName);
                    
                    SaveParty saveMe(partyName.getAquiredString(), memberPaths);
                    drawSmall(partyName.getScreen().xyLimits.minX, partyName.getScreen().xyLimits.maxX, partyName.getScreen().xyLimits.minY, partyName.getScreen().xyLimits.maxY + 1, *_primaryScreen);
                    break;
                }
            } else if (k == KEY_ESCAPE) {
                // createPrimary(*_primaryScreen, options);
                // drawPrimary(*_primaryScreen);
                // drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
                // drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                //         _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                //         *_primaryScreen);
                break;
            }
        }
    }
}

char ListHighlightPair::navigateDestination()
{
    char choice;
    std::size_t horz_char = tcols();
    std::size_t vert_char = trows();

    listNavigate();
    destNavigate();
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
              *_destListScreen);
     
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary(*_primaryScreen, _optMain);
            drawPrimary(*_primaryScreen);

            _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
            _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
            _listScreen->xyLimits.maxX = _cornerDims.maxX = horz_char / 3;
            _listScreen->xyLimits.maxY = _cornerDims.maxY = vert_char - 3;

            _destListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
            _destListScreen->xyLimits.minY = _primaryScreen->xyLimits.minY + 1;
            _destListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 2 + 1;
            _destListScreen->xyLimits.maxY = vert_char - 3;

            //createListPerimeter(*_listScreen, _options);
            //createListScreen(*_listScreen, _list, _title);
            listNavigate();
            destNavigate();
            //createListPerimeter(*_destListScreen, _destOptions);
            //createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
            drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
            drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                      _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                      *_destListScreen);
        }
        
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'r') {
                if(_destList.size() > 0){
                    _destList.erase(_destList.begin() + _destCurrPos);
                    _destIdx.erase(_destIdx.begin() + _destCurrPos);
                    if(_destCurrPos > _destList.size() - 1){
                        _destCurrPos--;
                    }
                    
                    listNavigate();
                    destNavigate();
                    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
                    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1, *_destListScreen);                
                }
            } else if(std::tolower(k) == 'v'){
                DrawRange infoRange;
                if(_destList.size() > 0){
                    infoRange.minX = 1;
                    infoRange.minY = 1;
                    Perimeter rollPerim(0x256D, 0x256E, 0x2570, 0x256F, 0x2500, 0x2502, MAGENTA, BLACK, BLUE, BLACK);
                    PrintInfo showChar(_players.at(_destIdx[_destCurrPos]), infoRange, rollPerim, *_primaryScreen, tcols(), trows());
                    listNavigate();
                    destNavigate();
                    // createListPerimeter(*_destListScreen, _destOptions);
                    // createListScreen(*_destListScreen, _destList, _destTitle, _highlightDest);
                    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
                    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                              _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1, *_destListScreen);
                }
            } else if(k == KEY_UP){
                if(_destCurrPos > 0){
                    _destPrevPos = _destCurrPos;
                    _destCurrPos--;
                    destNavigate();
                }
            } else if(k == KEY_DOWN){
                if(_destCurrPos < _destList.size() - 1){
                    _destPrevPos = _destCurrPos;
                    _destCurrPos++;
                    destNavigate();
                }
            } else if (k == KEY_LEFT){
                _highlightDest = false;
                _highlightList = true;
                listNavigate();
                destNavigate();
                drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
                drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                          _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                          *_destListScreen);
                return k;
            } else if(std::tolower(k) == 's'){
                return k;
            } else if (k == KEY_ESCAPE) {
            //     drawSmall(inScreen.xyLimits.minX, inScreen.xyLimits.maxX, inScreen.xyLimits.minY, inScreen.xyLimits.maxY, primaryScreen);
                return KEY_ESCAPE;
            }

            if(_destList.size() < 1){
                _highlightDest = false;
                _highlightList = true;
                listNavigate();
                destNavigate();
                drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
                drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX,
                          _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1,
                          *_destListScreen);
                return k;
            }
        }
    }
}

void ListHighlightPair::listNavigate()
{
    color_code textCol;
    color_code bgCol;
    #ifdef _WIN32
        textCol = BLUE;
        bgCol = GREY;
    #else
        textCol = DARKBLUE;
        bgCol = WHITE;
    #endif
    
    createListPerimeter(*_listScreen, _options);

    int titlePos = _listScreen->xyLimits.maxX - (_listScreen->xyLimits.maxX - _listScreen->xyLimits.minX) / 2 - _title.size() / 2 - 1;

    for(int i = 0; i < _title.size(); ++i){
        _listScreen->charMap[_listScreen->xyLimits.minY + 1][i + titlePos] = _title[i];
        _listScreen->colorMap[_listScreen->xyLimits.minY + 1][i + titlePos] = YELLOW;
    }

    for(int i = _listScreen->xyLimits.minY + 3; i < _listScreen->xyLimits.maxY - 1; ++i){
        //int idxOffset = _currPos - _listScreen->xyLimits.maxY + 6;
        
        if(_currPos > _listScreen->xyLimits.maxY - 6 + _listStartIdx){
            _listStartIdx++;
        } else if(_currPos < _listStartIdx){
            _listStartIdx = _currPos;
        }

        int strdx = i - (_listScreen->xyLimits.minY + 3) + _listStartIdx;
        
        if (strdx < _list.size()){
            for(int j = 0; j < _list[strdx].size(); ++j){
                if(strdx == _currPos && _highlightList){
                    _prevPos = _currPos;
                    _listScreen->charMap[i][j + _listScreen->xyLimits.minX + 1] = _list[strdx][j];
                    _listScreen->colorMap[i][j + _listScreen->xyLimits.minX + 1] = textCol;
                    _listScreen->bGColorMap[i][j + _listScreen->xyLimits.minX + 1] = bgCol;
                } else {
                    _listScreen->charMap[i][j + _listScreen->xyLimits.minX + 1] = _list[strdx][j];
                    _listScreen->colorMap[i][j + _listScreen->xyLimits.minX + 1] = YELLOW;
                    _listScreen->bGColorMap[i][j + _listScreen->xyLimits.minX + 1] = BLACK;
                }
            }
        }
    }   
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);     
}

void ListHighlightPair::destNavigate()
{
    color_code textCol;
    color_code bgCol;
    #ifdef _WIN32
        textCol = BLUE;
        bgCol = GREY;
    #else
        textCol = DARKBLUE;
        bgCol = WHITE;
    #endif
    
    createListPerimeter(*_destListScreen, _destOptions);

    int titlePos = _destListScreen->xyLimits.maxX - (_destListScreen->xyLimits.maxX - _destListScreen->xyLimits.minX) / 2 - _destTitle.size() / 2 - 1;

    for(int i = 0; i < _destTitle.size(); ++i){
        _destListScreen->charMap[_destListScreen->xyLimits.minY + 1][i + titlePos] = _destTitle[i];
        _destListScreen->colorMap[_destListScreen->xyLimits.minY + 1][i + titlePos] = YELLOW;
    }

    for(int i = _destListScreen->xyLimits.minY + 3; i < _destListScreen->xyLimits.maxY - 1; ++i){
        //int idxOffset = _currPos - _destListScreen->xyLimits.maxY + 6;
        
        if(_destCurrPos > _destListScreen->xyLimits.maxY - 6 + _destStartIdx){
            _destStartIdx++;
        } else if(_destCurrPos < _destStartIdx){
            _destStartIdx = _destCurrPos;
        }

        int strdx = i - (_destListScreen->xyLimits.minY + 3) + _destStartIdx;
        
        if (strdx < _destList.size()){
            for(int j = 0; j < _destList[strdx].size(); ++j){
                if(strdx == _destCurrPos && _highlightDest){
                    _destPrevPos = _destCurrPos;
                    _destListScreen->charMap[i][j + _destListScreen->xyLimits.minX + 1] = _destList[strdx][j];
                    _destListScreen->colorMap[i][j + _destListScreen->xyLimits.minX + 1] = textCol;
                    _destListScreen->bGColorMap[i][j + _destListScreen->xyLimits.minX + 1] = bgCol;
                } else {
                    _destListScreen->charMap[i][j + _destListScreen->xyLimits.minX + 1] = _destList[strdx][j];
                    _destListScreen->colorMap[i][j + _destListScreen->xyLimits.minX + 1] = YELLOW;
                    _destListScreen->bGColorMap[i][j + _destListScreen->xyLimits.minX + 1] = BLACK;
                }
            }
        }
    }   
    drawSmall(_destListScreen->xyLimits.minX, _destListScreen->xyLimits.maxX, _destListScreen->xyLimits.minY, _destListScreen->xyLimits.maxY + 1, *_destListScreen);     
}

// void ListHighlightPair::destNavigate()
// {

// }

ScreenVals& ListHighlightPair::getDestScreen()
{
    return *_destListScreen;
}

std::vector<Entity>& ListHighlightPair::getEntityList()
{
    return _players;
}

ListHighlightPartySelect::ListHighlightPartySelect(std::vector<std::string>& inList, std::vector<std::vector<Entity>>& inParties,
                                     std::vector<std::string>& inPaths, ScreenVals &primaryScreen,
                                     std::string inName, std::vector<int> inOptions,
                                     Perimeter inPerim, DrawRange inRange)
{
    _perim = inPerim;
    _list = inList;
    _pathList = inPaths;
    _parties = inParties;
    _title = inName;
    _options = inOptions;
    _cornerDims = inRange;
    _listScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _partyListScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _primaryScreen = std::make_shared<ScreenVals>(primaryScreen);
    // _listScreen->xyLimits.minX = _cornerDims.minX = inRange.minX;
    // _listScreen->xyLimits.minY = _cornerDims.minY = inRange.minY;
    // _listScreen->xyLimits.maxX = _cornerDims.maxX = inRange.maxX;
    // _listScreen->xyLimits.maxY = _cornerDims.maxY = inRange.maxY;

    // createPrimary(*_primaryScreen, _optMain);
    // drawPrimary(*_primaryScreen);
    
    _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
    _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
    _listScreen->xyLimits.maxX = _cornerDims.maxX = tcols() / 3;
    _listScreen->xyLimits.maxY = _cornerDims.maxY = trows() - 3;

    _partyListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
    _partyListScreen->xyLimits.minY = _primaryScreen->xyLimits.minY + 1;
    _partyListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 3 - 3;
    _partyListScreen->xyLimits.maxY = trows() - 3;

    //createListPerimeter(*_listScreen, _options);
    //createListScreen(*_listScreen, _list, _title);
    listNavigate();
    createListPerimeter(*_listScreen, _options);
    createListScreen(*_listScreen, _list, _title, _highlightList);
    createPrimary(*_primaryScreen, _optMain);
    drawPrimary(*_primaryScreen);
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
    createListPerimeter(*_partyListScreen, _partyOptions);
    createListScreen(*_partyListScreen, _party, _partyTitle, false);
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
    drawSmall(_partyListScreen->xyLimits.minX, _partyListScreen->xyLimits.maxX,
                _partyListScreen->xyLimits.minY, _partyListScreen->xyLimits.maxY + 1,
                *_partyListScreen);

    navigateSelection();

    
}

void ListHighlightPartySelect::navigateSelection()
{
    // formatSelectedParty();
    char choice;
    std::size_t horz_char = tcols();
    std::size_t vert_char = trows();
    while(true){
        std::size_t new_horz = tcols();
        std::size_t new_vert = trows();
        if(horz_char != new_horz || vert_char != new_vert){
            horz_char = new_horz;
            vert_char = new_vert;
            createPrimary(*_primaryScreen, _optMain);
            drawPrimary(*_primaryScreen);

            _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
            _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
            _listScreen->xyLimits.maxX = _cornerDims.maxX = horz_char / 3;
            _listScreen->xyLimits.maxY = _cornerDims.maxY = vert_char - 3;

            _partyListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
            _partyListScreen->xyLimits.minY = _primaryScreen->xyLimits.minY + 1;
            _partyListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 3 - 3;
            _partyListScreen->xyLimits.maxY = vert_char - 3;

            //createListPerimeter(*_listScreen, _options);
            //createListScreen(*_listScreen, _list, _title);
            listNavigate();
            // formatSelectedParty();
            createListPerimeter(*_partyListScreen, _partyOptions);
            createListScreen(*_partyListScreen, _party, _partyTitle, false);
            drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
            drawSmall(_partyListScreen->xyLimits.minX, _partyListScreen->xyLimits.maxX,
                      _partyListScreen->xyLimits.minY, _partyListScreen->xyLimits.maxY + 1,
                      *_partyListScreen);
        }
        
        if(kbhit()){
            char k = getkey();
            if(std::tolower(k) == 'a') {

            } else if(std::tolower(k) == 'v'){
            DrawRange infoRange;

            } else if(k == KEY_UP){
                if(_currPos > 0){
                    _prevPos = _currPos;
                    _currPos--;
                    listNavigate();
                }
            } else if(k == KEY_DOWN){
                if(_currPos < _list.size() - 1){
                    _prevPos = _currPos;
                    _currPos++;
                    listNavigate();
                }
            } else if(std::tolower(k) == 's'){
                if(_list.size() > 0){
                    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_primaryScreen);
                    drawSmall(_listScreen->xyLimits.minX, _listScreen->xyLimits.maxX,
                            _listScreen->xyLimits.minY, _listScreen->xyLimits.maxY + 1,
                            *_primaryScreen);
                    TextInput partyName;
                    Perimeter textPerim(TL_LINE, TR_LINE, BL_LINE, BR_LINE, HORZ_LINE, VERT_LINE, MAGENTA, BLACK, BLUE, BLACK);
                    _selIdx = _currPos;
                    partySelected = true;
                    break;
                } else {
                    break;
                }
            } else if (k == KEY_ESCAPE) {
                break;
            }
        }
    }
}

void ListHighlightPartySelect::listNavigate()
{
    color_code textCol;
    color_code bgCol;
    #ifdef _WIN32
        textCol = BLUE;
        bgCol = GREY;
    #else
        textCol = DARKBLUE;
        bgCol = WHITE;
    #endif
    
    createListPerimeter(*_listScreen, _options);

    int titlePos = _listScreen->xyLimits.maxX - (_listScreen->xyLimits.maxX - _listScreen->xyLimits.minX) / 2 - _title.size() / 2 - 1;

    for(int i = 0; i < _title.size(); ++i){
        _listScreen->charMap[_listScreen->xyLimits.minY + 1][i + titlePos] = _title[i];
        _listScreen->colorMap[_listScreen->xyLimits.minY + 1][i + titlePos] = YELLOW;
    }

    for(int i = _listScreen->xyLimits.minY + 3; i < _listScreen->xyLimits.maxY - 1; ++i){
        //int idxOffset = _currPos - _listScreen->xyLimits.maxY + 6;
        
        if(_currPos > _listScreen->xyLimits.maxY - 6 + _listStartIdx){
            _listStartIdx++;
        } else if(_currPos < _listStartIdx){
            _listStartIdx = _currPos;
        }

        int strdx = i - (_listScreen->xyLimits.minY + 3) + _listStartIdx;
        
        if (strdx < _list.size()){
            for(int j = 0; j < _list[strdx].size(); ++j){
                if(strdx == _currPos && _highlightList){
                    _prevPos = _currPos;
                    _listScreen->charMap[i][j + _listScreen->xyLimits.minX + 1] = _list[strdx][j];
                    _listScreen->colorMap[i][j + _listScreen->xyLimits.minX + 1] = textCol;
                    _listScreen->bGColorMap[i][j + _listScreen->xyLimits.minX + 1] = bgCol;
                } else {
                    _listScreen->charMap[i][j + _listScreen->xyLimits.minX + 1] = _list[strdx][j];
                    _listScreen->colorMap[i][j + _listScreen->xyLimits.minX + 1] = YELLOW;
                    _listScreen->bGColorMap[i][j + _listScreen->xyLimits.minX + 1] = BLACK;
                }
            }
        }
    }   
    drawSmall(_cornerDims.minX, _cornerDims.maxX, _cornerDims.minY, _cornerDims.maxY + 1, *_listScreen);
    formatSelectedParty();
    populatePartyList();
}

void ListHighlightPartySelect::populatePartyList()
{
    color_code textCol;
    color_code bgCol;
    #ifdef _WIN32
        textCol = BLUE;
        bgCol = GREY;
    #else
        textCol = DARKBLUE;
        bgCol = WHITE;
    #endif

    std::string partyTitle = "Party: " + _list[_currPos];

    std::vector<int> empty;
    createListPerimeter(*_partyListScreen, empty);

    int titlePos = _partyListScreen->xyLimits.maxX - (_partyListScreen->xyLimits.maxX - _partyListScreen->xyLimits.minX) / 2 - partyTitle.size() / 2 - 1;

    for(int i = 0; i < partyTitle.size(); ++i){
        _partyListScreen->charMap[_partyListScreen->xyLimits.minY + 1][i + titlePos] = partyTitle[i];
        _partyListScreen->colorMap[_partyListScreen->xyLimits.minY + 1][i + titlePos] = YELLOW;
    }

    for(int i = _partyListScreen->xyLimits.minY + 2; i < _partyListScreen->xyLimits.maxY - 1; ++i){
        //int idxOffset = _currPos - _listScreen->xyLimits.maxY + 6;
        
        
        int curMemb = i - (_partyListScreen->xyLimits.minY + 3);
        //std::cout << "_party.size(): " << _party.size() << " curMemb: " << curMemb << std::endl;
        if(curMemb < _party.size()){
            //std::cout << curMemb << std::endl;
            for(int j = 0; j < _party[curMemb].size(); ++j){

                    _partyListScreen->charMap[i][j + _partyListScreen->xyLimits.minX + 1] = _party[curMemb][j];
                    _partyListScreen->colorMap[i][j + _partyListScreen->xyLimits.minX + 1] = YELLOW;
                    _partyListScreen->bGColorMap[i][j + _partyListScreen->xyLimits.minX + 1] = BLACK;
            }
        }
    }   

    drawSmall(_partyListScreen->xyLimits.minX, _partyListScreen->xyLimits.maxX, _partyListScreen->xyLimits.minY, _partyListScreen->xyLimits.maxY + 1, *_partyListScreen); 
}


void ListHighlightPartySelect::formatSelectedParty()
{
    _party.clear();
    _partyTitle = "Party: " + _list[_currPos];
    for(int i = 0; i < _parties[_currPos].size(); ++i){
        auto curMem = _parties[_currPos][i];
        std::string member = curMem.getName() + ", Lvl: " + std::to_string(curMem.getLevel());
        member += ", Class: " + getClass(curMem.getClass()[0]) + " Align: " + getAlign(curMem.getAlign());
        _party.push_back(member);
    }
}

std::vector<Entity> ListHighlightPartySelect::returnParty()
{
    return _parties[_selIdx];
}

int ListHighlightPartySelect::getPartyIdx()
{
    return _selIdx;
}

LoadFileList::LoadFileList()
{

}

LoadFileList::LoadFileList(std::string directory)
{
    const std::filesystem::path files{directory};
    // std::cout << characters << std::endl;
    if(std::filesystem::exists(files)){
        std::vector<std::string> dir;
        for (auto const& dir_entry : std::filesystem::directory_iterator{files}) {
            _pathList.push_back(dir_entry.path().string());
            std::string fullString(dir_entry.path().string());
            Entity newEntity(fullString.c_str());
            std::size_t period = fullString.find_first_of(".");
            fullString = fullString.substr(0, period);
            std::size_t slash = fullString.find_first_of("/");
            fullString = fullString.substr(slash + 1, fullString.size());
            //printf("%s\r\n", fullString.c_str());
            _fileList.push_back(fullString); 
        } 
    }
}

std::vector<std::string>& LoadFileList::getFileList()
{
    return _fileList;
}

std::vector<std::string>& LoadFileList::getPathList()
{
    return _pathList;
}

LoadCharList::LoadCharList(std::string directory)
{
    const std::filesystem::path files{directory};
    // std::cout << characters << std::endl;
    if(std::filesystem::exists(files)){
        std::vector<std::string> dir;
        for (auto const& dir_entry : std::filesystem::directory_iterator{files}) {
            _pathList.push_back(dir_entry.path().string());
            std::string fullString(dir_entry.path().string());
            Entity newEntity(fullString.c_str());
            _players.push_back(newEntity);
            std::size_t period = fullString.find_first_of(".");
            fullString = fullString.substr(0, period);
            std::size_t slash = fullString.find_first_of("/");
            fullString = fullString.substr(slash + 1, fullString.size());
            //printf("%s\r\n", fullString.c_str());
            _fileList.push_back(fullString); 
        } 
    }
}

LoadPartyList::LoadPartyList(std::string directory)
{
    const std::filesystem::path files{directory};
    //std::cout << files << std::endl;
    if(std::filesystem::exists(files)){
        std::vector<std::string> dir;
        for (auto const& dir_entry : std::filesystem::directory_iterator{files}) {
            _pathList.push_back(dir_entry.path().string());
            std::string fullString(dir_entry.path().string());
            //Entity newEntity(fullString.c_str());
            //_players.push_back(newEntity);
            std::size_t period = fullString.find_first_of(".");
            fullString = fullString.substr(0, period);
            std::size_t slash = fullString.find_first_of("/");
            fullString = fullString.substr(slash + 1, fullString.size());
            //printf("%s\r\n", fullString.c_str());
            _fileList.push_back(fullString);
            LoadParty curParty(fullString);
            _parties.push_back(curParty.getParty());
        } 
    }
}

std::vector<std::vector<Entity>>& LoadPartyList::getParties()
{
    return _parties;
}

std::vector<Entity>& LoadCharList::getEntityList()
{
    return _players;
}

void clearPrevScreen(const std::vector<ScreenVals>& screens)
{
    drawSmall(screens.back().xyLimits.minX, screens.back().xyLimits.maxX, screens.back().xyLimits.minY, screens.back().xyLimits.maxY + 1, screens.front());  
}

AccessInventory::AccessInventory(std::vector<std::string>& inList, std::vector<Entity> &inEntity,
                                     ScreenVals& primaryScreen,
                                     std::string inName, std::vector<int> inOptions,
                                     Perimeter inPerim, DrawRange inRange)
{

    _perim = inPerim;
    _list = inList;
    _players = inEntity;
    _title = inName;
    _options = inOptions;
    _cornerDims = inRange;
    _listScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _entityListScreen = std::make_shared<ScreenVals>(VECT_MAX, ' ', YELLOW, BLACK);
    _primaryScreen = std::make_shared<ScreenVals>(primaryScreen);

    _json = sj::padded_string::load("items/Arms.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);
    std::vector<std::shared_ptr<Items>> armsList;
    for(unsigned i = 0; i < _itemCount; ++i){
        armsList.push_back(std::make_shared<Arms>(_itemsData, i));
    }

    _inventoryList.push_back(armsList);

    _json = sj::padded_string::load("items/Armor.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> armorList;

    for(unsigned i = 0; i < _itemCount; ++i){
        armorList.push_back(std::make_shared<Armor>(_itemsData, i));
    }

    _inventoryList.push_back(armorList);

    _json = sj::padded_string::load("items/Clothing.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> clothingList;

    for(unsigned i = 0; i < _itemCount; ++i){
        clothingList.push_back(std::make_shared<Clothing>(_itemsData, i));
    }

    _inventoryList.push_back(clothingList);

    _json = sj::padded_string::load("items/Herbs.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> herbList;

    for(unsigned i = 0; i < _itemCount; ++i){
        herbList.push_back(std::make_shared<Herbs>(_itemsData, i));
    }

    _inventoryList.push_back(herbList);

    _json = sj::padded_string::load("items/Livestock.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> liveStockList;

    for(unsigned i = 0; i < _itemCount; ++i){
        liveStockList.push_back(std::make_shared<Livestock>(_itemsData, i));
    }

    _inventoryList.push_back(liveStockList);

    _json = sj::padded_string::load("items/Misc.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> miscList;

    for(unsigned i = 0; i < _itemCount; ++i){
        miscList.push_back(std::make_shared<MiscItems>(_itemsData, i));
    }

    _inventoryList.push_back(miscList);

    _json = sj::padded_string::load("items/Provisions.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> provisionList;

    for(unsigned i = 0; i < _itemCount; ++i){
        provisionList.push_back(std::make_shared<Provisions>(_itemsData, i));
    }

    _inventoryList.push_back(provisionList);

    _json = sj::padded_string::load("items/Religious.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> religiousList;

    for(unsigned i = 0; i < _itemCount; ++i){
        religiousList.push_back(std::make_shared<Religious>(_itemsData, i));
    }

    _inventoryList.push_back(religiousList);

    _json = sj::padded_string::load("items/TackHarness.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> tackHarnessList;

    for(unsigned i = 0; i < _itemCount; ++i){
        tackHarnessList.push_back(std::make_shared<TackHarness>(_itemsData, i));
    }

    _inventoryList.push_back(tackHarnessList);

    _json = sj::padded_string::load("items/Transport.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> transportList;

    for(unsigned i = 0; i < _itemCount; ++i){
        transportList.push_back(std::make_shared<Transport>(_itemsData, i));
    }

    _inventoryList.push_back(transportList);

    _listScreen->xyLimits.minX = _cornerDims.minX = _primaryScreen->xyLimits.minX + 1;
    _listScreen->xyLimits.minY = _cornerDims.minY = _primaryScreen->xyLimits.minY + 1;
    _listScreen->xyLimits.maxX = _cornerDims.maxX = tcols() / 2;
    _listScreen->xyLimits.maxY = _cornerDims.maxY = trows() - 3;

    _entityListScreen->xyLimits.minX = _listScreen->xyLimits.maxX + 1;
    _entityListScreen->xyLimits.minY = _primaryScreen->xyLimits.minY + 1;
    _entityListScreen->xyLimits.maxX = _listScreen->xyLimits.maxX * 2 - 3;
    _entityListScreen->xyLimits.maxY = trows() - 3;

    createPrimary(*_primaryScreen, _optMain);
}

AccessInventory::AccessInventory()
{

    _json = sj::padded_string::load("items/Arms.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> armsList;
    for(unsigned i = 0; i < _itemCount; ++i){
        armsList.push_back(std::make_shared<Arms>(_itemsData, i));
    }

    _inventoryList.push_back(armsList);

    _json = sj::padded_string::load("items/Armor.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> armorList;

    for(unsigned i = 0; i < _itemCount; ++i){
        armorList.push_back(std::make_shared<Armor>(_itemsData, i));
    }

    _inventoryList.push_back(armorList);

    _json = sj::padded_string::load("items/Clothing.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> clothingList;

    for(unsigned i = 0; i < _itemCount; ++i){
        clothingList.push_back(std::make_shared<Clothing>(_itemsData, i));
    }

    _inventoryList.push_back(clothingList);

    _json = sj::padded_string::load("items/Herbs.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> herbList;

    for(unsigned i = 0; i < _itemCount; ++i){
        herbList.push_back(std::make_shared<Herbs>(_itemsData, i));
    }

    _inventoryList.push_back(herbList);

    _json = sj::padded_string::load("items/Livestock.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> liveStockList;

    for(unsigned i = 0; i < _itemCount; ++i){
        liveStockList.push_back(std::make_shared<Livestock>(_itemsData, i));
    }

    _inventoryList.push_back(liveStockList);

    _json = sj::padded_string::load("items/Misc.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> miscList;

    for(unsigned i = 0; i < _itemCount; ++i){
        miscList.push_back(std::make_shared<MiscItems>(_itemsData, i));
    }

    _inventoryList.push_back(miscList);

    _json = sj::padded_string::load("items/Provisions.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> provisionList;

    for(unsigned i = 0; i < _itemCount; ++i){
        provisionList.push_back(std::make_shared<Provisions>(_itemsData, i));
    }

    _inventoryList.push_back(provisionList);

    _json = sj::padded_string::load("items/Religious.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> religiousList;

    for(unsigned i = 0; i < _itemCount; ++i){
        religiousList.push_back(std::make_shared<Religious>(_itemsData, i));
    }

    _inventoryList.push_back(religiousList);

    _json = sj::padded_string::load("items/TackHarness.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> tackHarnessList;

    for(unsigned i = 0; i < _itemCount; ++i){
        tackHarnessList.push_back(std::make_shared<TackHarness>(_itemsData, i));
    }

    _inventoryList.push_back(tackHarnessList);

    _json = sj::padded_string::load("items/Transport.json");
    _itemsData = _parser.iterate(_json);

    _itemCount = uint64_t(_itemsData["data"]["count"]);

    std::vector<std::shared_ptr<Items>> transportList;

    for(unsigned i = 0; i < _itemCount; ++i){
        transportList.push_back(std::make_shared<Transport>(_itemsData, i));
    }

    _inventoryList.push_back(transportList);

    std::cout << "Size of Inventory Vector:" << _inventoryList.size() << std::endl;

    sleep(10);    
}
