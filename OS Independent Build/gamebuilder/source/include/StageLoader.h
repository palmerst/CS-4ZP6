#ifndef STAGELOADER_H_INCLUDED
#define STAGELOADER_H_INCLUDED

#include <map>
#include <string>

class StageLoader {

    private:

        void reportError(std::string fileName, std::string line);

    public:

        StageLoader(std::string fileName);

        std::map<std::string, std::string> stageInfo;




};

#endif // STAGELOADER_H_INCLUDED
