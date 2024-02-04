#ifndef PARTY_H
#define PARTY_H
#include "project_headers.h"
#include "ui_util.h"

class SaveParty{
private:
    std::vector<std::string> _playerPaths;
    std::string _partyName;
    void writePartyJSON();
public:
    SaveParty(std::string partyName, std::vector<std::string> playerPaths);
};

#endif// PARTY_H