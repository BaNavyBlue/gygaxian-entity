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

class LoadParty{
private:
    std::vector<std::string> _memberPaths;
    std::vector<Entity> _party;
    std::string _partyName;
    void getPaths();
    void loadMembers();
public:
    LoadParty(std::string partyName);
    std::vector<Entity> getParty();
};

#endif// PARTY_H