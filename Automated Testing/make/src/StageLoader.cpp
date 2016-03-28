#include "StageLoader.h"
#include <iostream>
#include <cstdlib>

StageLoader::StageLoader(std::string fileName, std::vector<PhysicsObject*>& physicsObjects, std::vector<StandardObject*>& standardObjects, Skybox*& skybox, Boundary*& boundary, Hero*& userControlObject){

    this->fileName = fileName;
    this->lineNo = 0;

    float scaleFactor = 50.0f;

    inFile.open(fileName.c_str());
    if(!inFile.is_open()){
        std::cout << "Stage file \"" << fileName << "\" does not exist" << std::endl;
        exit(3);
    }

    /**
     **  Find the **stage** header
     **/

    getNextLine(); // get line from file

    while(inFile.good())
    {

        if(line == "**stage**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                int eqPos = line.find('=');
                if(eqPos == std::string::npos)
                    reportError();
                std::string key = line.substr(0, eqPos);
                std::string val = line.substr(eqPos+1);
                stageInfo.insert(std::pair<std::string, std::string>(key, val));
            }

            continue;
        }
        if(line == "**platforms**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                float x1, x2, y, t;
                t = 1;

                if(sscanf(line.c_str(), "x=%fto%f,ytop=%f,thickness=%f", &x1, &x2, &y, &t) >= 3)
                    y -= t/2.0f;
                else if(sscanf(line.c_str(), "x=%fto%f,ybot=%f,thickness=%f", &x1, &x2, &y, &t) >= 3)
                    y += t/2.0f;
                else if(sscanf(line.c_str(), "x=%fto%f,ymid=%f,thickness=%f", &x1, &x2, &y, &t) >= 3);
                else reportError();

                physicsObjects.push_back(new Platform(x1 * scaleFactor, x2 * scaleFactor, y * scaleFactor, t * scaleFactor));

            }

            continue;
        }
        if(line == "**walls**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                float x, y1, y2, t;
                t = 1;

                if(sscanf(line.c_str(), "xleft=%f,y=%fto%f,thickness=%f", &x, &y1, &y2, &t) >= 3)
                    x += t/2.0f;
                else if(sscanf(line.c_str(), "xright=%f,y=%fto%f,thickness=%f", &x, &y1, &y2, &t) >= 3)
                    x -= t/2.0f;
                else if(sscanf(line.c_str(), "xmid=%f,y=%fto%f,thickness=%f", &x, &y1, &y2, &t) >= 3);
                else reportError();

                physicsObjects.push_back(new Wall(y1 * scaleFactor, y2 * scaleFactor, x * scaleFactor, t * scaleFactor));

            }

            continue;
        }
        if(line == "**ramps**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                float x1, x2, y1, y2, t;
                t = 1;

                if(sscanf(line.c_str(), "x=%fto%f,ytop=%fto%f,thickness=%f", &x1, &x2, &y1, &y2, &t) >= 4){
                    y1 -= t/2.0f;
                    y2 -= t/2.0f;
                }
                else if(sscanf(line.c_str(), "x=%fto%f,ybot=%fto%f,thickness=%f", &x1, &x2, &y1, &y2, &t) >= 4){
                    y1 += t/2.0f;
                    y2 += t/2.0f;
                }
                else if(sscanf(line.c_str(), "x=%fto%f,ymid=%fto%f,thickness=%f", &x1, &x2, &y1, &y2, &t) >= 4);
                else reportError();

                physicsObjects.push_back(new Ramp(x1 * scaleFactor, x2 * scaleFactor, y1 * scaleFactor, y2 * scaleFactor, t * scaleFactor));

            }

            continue;
        }
        if(line == "**hazards**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                float x,y;

                char hazardName[20];

                std::string xyModifiers;

                if(sscanf(line.c_str(), "%[^,],xleft=%f,ybot=%f", &hazardName, &x, &y) == 3) xyModifiers = "lb";
                else if(sscanf(line.c_str(), "%[^,],xleft=%f,ymid=%f", &hazardName, &x, &y) == 3) xyModifiers = "lm";
                else if(sscanf(line.c_str(), "%[^,],xleft=%f,ytop=%f", &hazardName, &x, &y) == 3) xyModifiers = "lt";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ybot=%f", &hazardName, &x, &y) == 3) xyModifiers = "mb";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ymid=%f", &hazardName, &x, &y) == 3) xyModifiers = "mm";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ytop=%f", &hazardName, &x, &y) == 3) xyModifiers = "mt";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ybot=%f", &hazardName, &x, &y) == 3) xyModifiers = "rb";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ymid=%f", &hazardName, &x, &y) == 3) xyModifiers = "rm";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ytop=%f", &hazardName, &x, &y) == 3) xyModifiers = "rt";
                else reportError();

                x *= scaleFactor;
                y *= scaleFactor;

                std::string hazardString = hazardName;

                if(hazardString == "boulder"){
                    if(xyModifiers[0] == 'l') x += 250.0f;
                    else if(xyModifiers[0] == 'r') x -= 250.0f;

                    if(xyModifiers[1] == 'b') y += 250.0f;
                    else if(xyModifiers[1] == 't') y -= 250.0f;

                    physicsObjects.push_back(new Boulder(x, y));
                }

                else if(hazardString == "upspikes" || hazardString == "downspikes"){
                    if(xyModifiers[0] == 'l') x += 239.6f;
                    else if(xyModifiers[0] == 'r') x -= 239.6f;

                    if(xyModifiers[1] == 'b') y += 190.0f;
                    else if(xyModifiers[1] == 't') y -= 190.0f;

                    float rot = 0.0f;

                    if(hazardString == "downspikes")
                        rot = 3.141592f;

                    physicsObjects.push_back(new Spikes(x, y, rot));
                }

                else if(hazardString == "upspear" || hazardString == "leftspear" || hazardString == "rightspear"){
                    if(xyModifiers[0] == 'l') x += 250.0f;
                    else if(xyModifiers[0] == 'r') x -= 250.0f;

                    if(xyModifiers[1] == 'b') y += 250.0f;
                    else if(xyModifiers[1] == 't') y -= 250.0f;

                    physicsObjects.push_back(new Boulder(x, y));
                }

            }

            continue;
        }

        getNextLine();
    }

    userControlObject = new Hero(atof(checkField("startx").c_str()) * scaleFactor, atof(checkField("starty").c_str()) * scaleFactor + 100.0f);

    std::string bg = checkField("background");

    if(bg == "bluesky"){
        skybox = new Skybox(0, 0, 2);
    }
    else if(bg == "");

    std::string setting = checkField("setting");

    if(setting == "desert"){
        boundary = boundary = new Boundary(-30000, 30000, 0, BS_SAND);
    }

    checkField("endx");
    checkField("endy");

}

std::string StageLoader::stripWhitespace(std::string str){
    for(std::string::iterator it = str.begin(); it != str.end(); it++){
        if(*it == ' ' || *it == '\t')
            // clear if whitespace, set iterator to previous
            it = str.erase(it) - 1;
    }
    return str;
}

void StageLoader::reportError(){
    std::cout << "Error while reading stage \"" << fileName << "\"\n\tat line " << lineNo << ": " << curLine << std::endl;
    exit(4);
}

void StageLoader::getNextLine(){
    getline(inFile, curLine);
    line = stripWhitespace(curLine);
    lineNo++;
}

std::string StageLoader::checkField(std::string field){
    if(stageInfo.find(field) == stageInfo.end()){
        std::cout << "Stage file \"" << fileName << "\" missing required field:  " << field << std::endl;
        exit(3);
    }

    return stageInfo.find(field)->second;
}
