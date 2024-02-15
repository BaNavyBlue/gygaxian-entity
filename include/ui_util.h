#ifndef UI_UTIL_H
#define UI_UTIL_H
#include "project_headers.h"
#include "ui_structs.h"
#include "StatHelpers.h"
#include "entity.h"
#include "party.h"

// Some of these prototypes defined in ui-test.cpp for now.
void drawPrimary(ScreenVals& primaryScreen);
void drawSmall(int startX, int maxX, int startY, int maxY, const ScreenVals& inScreen);
void createPrimary(ScreenVals& primaryScreen, std::vector<std::string> inOpts);
void createRollScreen();
void createBruteForceScreen();
std::vector<CHAR_CLASS> classToForce();
bool createRaceScreen(RACE& newRace, stats& inStats, ScreenVals& inScreen, ScreenVals& inScreen2, ScreenVals& inScreen3);
bool createRaceScreenBF(RACE &newRace, CHAR_CLASS inClass, stats& inStats, ScreenVals& inScreen, ScreenVals& inScreen2, ScreenVals& inScreen3);
SEX selSexScreen(ScreenVals& sexScreen, ScreenVals& inScreen);
char selRace(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3);
char selClass(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4);
CHAR_CLASS selClassScreen(stats& inStats, RACE inRace, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& classScreen);
std::string getUTF(int inCode);
bool reRollOptions(stats& stats1, stats& stats2, ScreenVals& inScreen);
void reDoStatScreen();
void generatePerimeter(ScreenVals& inScreen, Perimeter inPerim);
std::string getName(ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4);
char selOpt(const std::vector<ScreenVals>& inScreens, int idx);
bool doesRecordExist(std::string name, std::string path, std::string suffix);
void clearPrevScreen(const std::vector<ScreenVals>& screens);

class TextInput{
private:
    std::string _receivedString;
    std::string _prompt;
    std::shared_ptr<ScreenVals> _textScreen;
    Perimeter _textBoxPerim;
    void PlacePrompt();
    void getText();
public:
    TextInput();
    void createTextInput(DrawRange uRandWidth, Perimeter inPerim, std::string message);
    std::string getAquiredString();
    ScreenVals& getScreen();
    void purgeRecieved();
};

class OptionWindow{
protected:
    std::vector<std::string> _list;
    std::shared_ptr<ScreenVals> _optScreen;
    Perimeter _optionBoxPerim;
    virtual void PlaceOptions();
public:
    OptionWindow();
    virtual void createWindow(DrawRange uRandWidth, Perimeter inPerim) = 0;
};

class AlignOptWindow: public OptionWindow{
private:
    // ALIGNMENT _align;
    std::unordered_map<char, ALIGNMENT> _aList;
    //void PlaceOptions() override;
public:
    AlignOptWindow(CHAR_CLASS inClass);
    void createWindow(DrawRange uRandWidth, Perimeter inPerim);
    ALIGNMENT getAlign(char inChar);
    ScreenVals& getScreen();
    int getOptIdx();
};

class ChooseOpt: public OptionWindow{
private:
    //void PlaceOptions() override;
    char _choice;
public:
    ChooseOpt(std::vector<std::string> inOpts);
    void createWindow(DrawRange uRandWidth, Perimeter inPerim);
    ScreenVals& getScreen();
    char getChoice(char optChoice);
};

class PrintInfo{
protected:
    std::shared_ptr<ScreenVals> _primaryScreen;
    int _horz;
    int _vert;
    std::vector<std::vector<std::string>> _contents;
    std::vector<std::shared_ptr<ScreenVals>> _infoScreen;
    Perimeter _infoBoxPerim;
    DrawRange _firstBox;
    Entity* _character;
    void MakeCharWin();
    void MakeStatsWin();
    void MakeCmbtWin();
    void MakeWealthWin();
    void MakeLangWin();
    void MakeEscTag();
    void MakeDexTbl();
    void MakeThiefDexTbl();
    void MakeRaceSkills();
    void MakeGenTbl(std::vector<std::string> stringVect);
    void SelectTbl();
    void PlaceInfo(int vectIdx);
    void createPrimary();
    void drawPrimary();
public:
    PrintInfo(Entity chrctr, DrawRange uRandWidth, Perimeter inPerim, ScreenVals& primary, int horz, int vert);
};

class WarnMessage{
private:
    std::shared_ptr<ScreenVals> _warnScreen;
public:
    WarnMessage(std::string warning, std::string question);
    bool waitForAnswer();
    ScreenVals& getScreen();
};

class RollScreen{
private:
    std::shared_ptr<ScreenVals> rollScreen;
public:
    RollScreen(stats inStats, ScreenVals& primaryScreen);
    ScreenVals& getScreen();
};

class ListHighlight{
protected:
    std::vector<std::string> _list;
    std::string _title;
    std::vector<std::string> _pathList;
    std::vector<int> _options;
    //std::vector<std::vector<FrmtChar>> _selScreen;
    int _currPos = 0;
    int _prevPos = 0;
    int _listStartIdx = 0;
    bool _highlightList = true;
    Perimeter _perim;
    DrawRange _cornerDims;
    std::shared_ptr<ScreenVals> _listScreen;
    std::shared_ptr<ScreenVals> _primaryScreen;
    void createListScreen(ScreenVals& inScreen, std::vector<std::string> inList, std::string inTitle, bool highlight);
    void createListPerimeter(ScreenVals& inScreen, std::vector<int> inOpts);
    virtual void navigateSelection();
    virtual void listNavigate();
public:
    ListHighlight();
    ListHighlight(std::vector<std::string> inList, ScreenVals& primaryScreen, std::string inName, std::vector<int> inOptions, Perimeter inPerim, DrawRange inRange);
    ScreenVals& getScreen();
};

class ListHighlightPair:public ListHighlight{
private:
    std::vector<std::string> _destList;
    std::vector<int> _destIdx;
    std::string _destTitle;
    std::shared_ptr<ScreenVals> _destListScreen;
    std::vector<int> _destOptions;
    std::vector<Entity> _players;
    const std::vector<std::string> _optMain = {"[ESC] Back", "(S)ave Party"};
    int _destCurrPos = 0;
    int _destPrevPos = 0;
    int _destStartIdx = 0;
    bool _highlightDest = false;
    void navigateSelection() override;
    char navigateDestination();
    void listNavigate() override;
    void destNavigate();
public:
    ListHighlightPair(std::vector<std::string>& inList, std::vector<Entity>& inPlayers,
                      std::vector<std::string>& inPaths, ScreenVals& primaryScreen,
                      std::string inName, std::string destTitle, std::vector<int> inOptions,
                      std::vector<int> destOptions, Perimeter inPerim, DrawRange inRange);
    ScreenVals& getDestScreen();
    std::vector<Entity>& getEntityList();
};

class ListHighlightPartySelect: public ListHighlight{
private:

public:
    //ListHighlightPartySelect();
    ListHighlightPartySelect(std::vector<std::string>& inList, std::vector<Entity>& inPlayers,
                                     std::vector<std::string>& inPaths, ScreenVals &primaryScreen,
                                     std::string inName, std::string destTitle, std::vector<int> inOptions,
                                     std::vector<int> destOptions, Perimeter inPerim, DrawRange inRange);
};

class LoadFileList{
protected:
    std::vector<std::string> _fileList;
    std::vector<std::string> _pathList;
public:
    LoadFileList();
    LoadFileList(std::string directory);
    std::vector<std::string>& getFileList();
    std::vector<std::string>& getPathList(); 
};

class LoadCharList:public LoadFileList{
private:
    std::vector<Entity> _players;
public:
    LoadCharList(std::string directory);
    std::vector<Entity>& getEntityList(); 
};

class LoadPartyList:public LoadFileList{
private:
    std::vector<std::vector<Entity>> _parties;
public:
    LoadPartyList(std::string directory); 
};



#endif //UI_UTIL_H