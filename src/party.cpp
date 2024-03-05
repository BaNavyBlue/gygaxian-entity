#include "party.h"

SaveParty::SaveParty(std::string partyName, std::vector<std::string> playerPaths)
{
    _partyName = partyName;
    _playerPaths = playerPaths;
    writePartyJSON();
}

void SaveParty::writePartyJSON()
{
    std::string outTxt = "{\r\n    \"data\":{\r\n";
    outTxt += "        \"members\":{\r\n";
    outTxt += "            \"count\":" + std::to_string(_playerPaths.size()) + ",\r\n";
    outTxt += "            \"index\":{\r\n";
    for(std::size_t i = 0; i < _playerPaths.size(); ++i){
        outTxt += "                \"" + std::to_string(i) + "\":" + '"' + _playerPaths[i] + '"';
        if(i < _playerPaths.size() - 1){
            outTxt += ",\r\n";
        } else {
            outTxt += "\r\n            }\r\n        }\r\n";
        }
    }
    outTxt += "    }\r\n";
    outTxt += "}";

    std::string filename = "parties/" + _partyName + ".json";
    std::ofstream myFile;
    myFile.open(filename);
    if(myFile.is_open()){
        myFile << outTxt;
        myFile.close();
    } else {
        std::cout << "File Can't open path " << filename << " invalid or cannot be accessed." << std::endl;
    }
}

LoadParty::LoadParty(std::string partyName)
{
    _partyName = partyName;
    getPaths();
    loadMembers();
}

void LoadParty::getPaths()
{
    std::string path = "parties/" + _partyName + ".json";
    sj::ondemand::parser parser;
    sj::padded_string json = sj::padded_string::load(path.c_str());
    sj::ondemand::document partyData = parser.iterate(json);

    int count = uint64_t(partyData["data"]["members"]["count"]);
    auto memberPath = partyData["data"]["members"]["index"];
    
    for(int i = 0; i < count; ++i){
        std::stringstream recv;
        recv << ((memberPath[std::to_string(i)]));
        //recv >> _name;
        std::string path = recv.str();
        // Remove all double-quote characters
        path.erase(
            std::remove( path.begin(), path.end(), '\"' ),
            path.end()
        );
        _memberPaths.push_back(path);
    }   
}

void LoadParty::loadMembers()
{
    for(int i = 0; i < _memberPaths.size(); ++i){
        Entity newMember(_memberPaths[i].c_str());
        _party.push_back(newMember);
    }
}

std::vector<Entity> LoadParty::getParty()
{
    return _party;
}