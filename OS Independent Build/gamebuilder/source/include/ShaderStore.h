#ifndef SHADERSTORE_H_INCLUDED
#define SHADERSTORE_H_INCLUDED

#include <map>
#include "Shader.h"

class ShaderStore
{

private:

    std::map<std::string, Shader*> shaderMap;

public:

    ShaderStore();

    Shader* add(std::string vpath, std::string fpath);
    Shader* get(std::string vpath, std::string fpath);

};

#endif // SHADERSTORE_H_INCLUDED
