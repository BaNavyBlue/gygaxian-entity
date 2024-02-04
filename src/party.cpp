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

