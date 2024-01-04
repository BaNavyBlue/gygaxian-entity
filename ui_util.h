#ifndef UI_UTIL_H
#define UI_UTIL_H
#include "project_headers.h"
#include "ui_structs.h"
#include "StatHelpers.h"
#include "entity.h"

// Some of these prototypes defined in ui-test.cpp for now.
void drawPrimary();
void drawSmall(int startX, int maxX, int startY, int maxY, ScreenVals& inScreen);
void createPrimary();
void createRollScreen();
bool createRaceScreen(RACE& newRace, stats& inStats, ScreenVals& inScreen, ScreenVals& inScreen2, ScreenVals& inScreen3);
SEX selSexScreen(ScreenVals& sexScreen, ScreenVals& inScreen);
char selRace(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3);
char selClass(char maxIdx, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4);
CHAR_CLASS selClassScreen(stats& inStats, RACE inRace, ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& classScreen);
std::string getUTF(int inCode);
bool reRollOptions(stats& stats1, stats& stats2, ScreenVals& inScreen);
void reDoStatScreen();
void generatePerimeter(ScreenVals& inScreen, Perimeter inPerim);
std::string getName(ScreenVals& inScreen1, ScreenVals& inScreen2, ScreenVals& inScreen3, ScreenVals& inScreen4);
char selAlign(std::vector<ScreenVals> inScreens, int idx);
bool doesRecordExist(std::string name, std::string path, std::string suffix);

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
    virtual void PlaceOptions() = 0;
public:
    OptionWindow();
    virtual void createWindow(DrawRange uRandWidth, Perimeter inPerim) = 0;
};

class AlignOptWindow: public OptionWindow{
private:
    // ALIGNMENT _align;
    std::unordered_map<char, ALIGNMENT> _aList;
    void PlaceOptions();
public:
    AlignOptWindow(CHAR_CLASS inClass);
    void createWindow(DrawRange uRandWidth, Perimeter inPerim);
    ALIGNMENT getAlign(char inChar);
    ScreenVals& getScreen();
    int getOptIdx();
};

class PrintInfo{
protected:
    std::vector<std::vector<std::string>> _contents;
    std::vector<std::shared_ptr<ScreenVals>> _infoScreen;
    Perimeter _infoBoxPerim;
    DrawRange _firstBox;
    Entity* _character;
    void MakeCharWin();
    void MakeStatsWin();
    void MakeCmbtWin();
    void MakeWealthWin();
    void MakeStrenTbl();
    void MakeIntTbl();
    void MakeWisTbl();
    void MakeDexTbl();
    void MakeCharisTbl();
    void MakeConsTbl();
    void MakeThiefDexTbl();
    void MakeRaceSkills();
    void PlaceInfo(int vectIdx);
public:
    PrintInfo(Entity& chrctr, DrawRange uRandWidth, Perimeter inPerim);
};

class WarnMessage{
private:
    std::shared_ptr<ScreenVals> _warnScreen;
public:
    WarnMessage(std::string warning, std::string question);
    bool waitForAnswer();
    ScreenVals& getScreen();
};

#endif //UI_UTIL_H