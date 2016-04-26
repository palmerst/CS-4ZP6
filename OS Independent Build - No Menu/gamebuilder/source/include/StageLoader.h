#ifndef STAGELOADER_H_INCLUDED
#define STAGELOADER_H_INCLUDED

#include <map>
#include <string>
#include <fstream>
#include "IncludeObjects.h"


class StageLoader {

    private:
        std::string fileName;
        int lineNo;
        std::string curLine;
        std::string line;
        std::ifstream inFile;
        std::map<std::string, std::string> stageInfo;


        std::string stripWhitespace(std::string str);
        std::string checkField(std::string field);

        //! Reports error at current line
        void reportError();

        //! Retrieves next line
        void getNextLine();



    public:

        StageLoader(std::string fileName, std::vector<PhysicsObject*>& physicsObjects, std::vector<KinematicObject*>& kinematicObjects, std::vector<StandardObject*>& standardObjects, Skybox*& skybox, Boundary*& boundary, Hero*& userControlObject);

};

#endif // STAGELOADER_H_INCLUDED
