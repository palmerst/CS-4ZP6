#ifndef STAGELOADER_H_INCLUDED
#define STAGELOADER_H_INCLUDED

#include <map>
#include <string>
#include <fstream>
#include "IncludeObjects.h"

class StageLoader {

    private:

        void reportError();
        std::string stripWhitespace(std::string str);
        void getNextLine();
        std::string checkField(std::string field);

        std::string fileName;
        int lineNo;
        std::string curLine;
        std::string line;
        std::ifstream inFile;

    public:

        StageLoader(std::string fileName, std::vector<PhysicsObject*>& physicsObjects, std::vector<KinematicObject*>& kinematicObjects, std::vector<StandardObject*>& standardObjects, Skybox*& skybox, Boundary*& boundary, Hero*& userControlObject);


        std::map<std::string, std::string> stageInfo;




};

#endif // STAGELOADER_H_INCLUDED
