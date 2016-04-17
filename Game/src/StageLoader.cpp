#include "StageLoader.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

StageLoader::StageLoader(std::string fileName, std::vector<PhysicsObject*>& physicsObjects, std::vector<KinematicObject*>& kinematicObjects, std::vector<StandardObject*>& standardObjects, Skybox*& skybox, Boundary*& boundary, Hero*& userControlObject){

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

        if(line == "**movingplatforms**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;

                std::vector<cpVect> path;
                float w, s, t;
                t = 1;

                if(sscanf(line.c_str(), "w=%f,speed=%f,thickness=%f", &w, &s, &t) >= 2){
                    while(inFile.good()){
                        getNextLine();
                        if(line.empty() || line[0] == '%')
                            continue;
                        if(line == "end")
                            break;

                        float x, y;
                        std::string xyModifiers;

                        if(sscanf(line.c_str(), "xleft=%f,ybot=%f", &x, &y) == 2) xyModifiers = "lb";
                        else if(sscanf(line.c_str(), "xleft=%f,ymid=%f", &x, &y) == 2) xyModifiers = "lm";
                        else if(sscanf(line.c_str(), "xleft=%f,ytop=%f", &x, &y) == 2) xyModifiers = "lt";
                        else if(sscanf(line.c_str(), "xmid=%f,ybot=%f", &x, &y) == 2) xyModifiers = "mb";
                        else if(sscanf(line.c_str(), "xmid=%f,ymid=%f", &x, &y) == 2) xyModifiers = "mm";
                        else if(sscanf(line.c_str(), "xmid=%f,ytop=%f", &x, &y) == 2) xyModifiers = "mt";
                        else if(sscanf(line.c_str(), "xright=%f,ybot=%f", &x, &y) == 2) xyModifiers = "rb";
                        else if(sscanf(line.c_str(), "xright=%f,ymid=%f", &x, &y) == 2) xyModifiers = "rm";
                        else if(sscanf(line.c_str(), "xright=%f,ytop=%f", &x, &y) == 2) xyModifiers = "rt";
                        else reportError();

                        if(xyModifiers[0] == 'l')
                            x += w/2.0f;
                        else if(xyModifiers[0] == 'r')
                            x -= w/2.0f;

                        if(xyModifiers[1] == 'b')
                            y += t/2.0f;
                        else if(xyModifiers[1] == 't')
                            y -= t/2.0f;

                        x *= scaleFactor;
                        y *= scaleFactor;

                        path.push_back(cpv(x, y));
                    }

                    w *= scaleFactor;
                    s *= scaleFactor;
                    s = std::min(s, 1000.0f);
                    t *= scaleFactor;

                    kinematicObjects.push_back(new MovingPlatform(w, s, path, t));
                }
                else reportError();
            }
        }

        if(line == "**hazards**"){
            while(inFile.good()){
                getNextLine();
                if(line.empty() || line[0] == '%')
                    continue;
                if(line[0] == '*')
                    break;
                float x,y;
                float rot = 0.0f;

                char hazardName[20];

                std::string xyModifiers;

                if(sscanf(line.c_str(), "%[^,],xleft=%f,ybot=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "lb";
                else if(sscanf(line.c_str(), "%[^,],xleft=%f,ymid=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "lm";
                else if(sscanf(line.c_str(), "%[^,],xleft=%f,ytop=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "lt";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ybot=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "mb";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ymid=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "mm";
                else if(sscanf(line.c_str(), "%[^,],xmid=%f,ytop=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "mt";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ybot=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "rb";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ymid=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "rm";
                else if(sscanf(line.c_str(), "%[^,],xright=%f,ytop=%f,rot=%f", &hazardName, &x, &y, &rot) >= 3) xyModifiers = "rt";
                else reportError();

                x *= scaleFactor;
                y *= scaleFactor;
                rot *= 3.141592f/180.0f;


                std::string hazardString = hazardName;

                PhysicsObject* newHazard;

                if(hazardString == "boulder"){
                    newHazard = new Boulder(0, 0);
                }

                else if(hazardString == "spikes"){
                    newHazard = new Spikes(0, 0, rot);
                }

                else if(hazardString == "spear"){
                    //if(xyModifiers[0] == 'l') x += 26.25f;
                    //else if(xyModifiers[0] == 'r') x -= 26.25f;

                    //if(xyModifiers[1] == 'b') y += 250.0f;
                   // else if(xyModifiers[1] == 't') y -= 250.0f;
                    newHazard = new Spear(0, 0, rot);
                }

                cpShapeCacheBB(newHazard->shape);
                cpBB bb = cpShapeGetBB(newHazard->shape);

                if(xyModifiers[0] == 'l') x -= bb.l;
                else if(xyModifiers[0] == 'r') x -= bb.r;

                if(xyModifiers[1] == 'b') y -= bb.b;
                else if(xyModifiers[1] == 't') y -= bb.t;

                cpBodySetPosition(newHazard->body, cpv(x, y));

                physicsObjects.push_back(newHazard);

            }

            continue;
        }

        getNextLine();
    }

    userControlObject = new Hero(atof(checkField("startx").c_str()) * scaleFactor, atof(checkField("starty").c_str()) * scaleFactor + 100.0f);

    std::string bg = checkField("background");

    if(bg == "bluesky"){
        skybox = new Skybox(0, 0, 1);
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
