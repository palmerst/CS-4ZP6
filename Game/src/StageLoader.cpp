#include "StageLoader.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

StageLoader::StageLoader(std::string fileName){

    std::ifstream inFile(fileName.c_str());
    if(!inFile.is_open()){
        std::cout << "Stage file \"" << fileName << "\" does not exist" << std::endl;
        exit(3);
    }

    /**
     **  Find the **stage** header
     **/

    while(inFile.good())
    {
        std::string line;
        getline(inFile, line); // get line from file
        if(line == "**stage**"){
            while(inFile.good()){
                getline(inFile, line);
                if(line.empty())
                    continue;
                if(line[0] == '*')
                    break;
                int eqPos = line.find('=');
                if(eqPos == std::string::npos)
                    reportError(fileName, line);
                std::string key = line.substr(0, eqPos-1);
                std::string val = line.substr(eqPos+1);
                stageInfo.insert(std::pair<std::string, std::string>(key, val));
            }

        }
        if(line == "**platforms**"){
        }

    }
}

void StageLoader::reportError(std::string fileName, std::string line){
    std::cout << "Error while reading stage \"" << fileName << "\"\n\tat line: " << line << std::endl;
    exit(4);
}
