#include "ShaderStore.h"

ShaderStore::ShaderStore() {};

Shader* ShaderStore::add(std::string vpath, std::string fpath)
{
    std::map<std::string, Shader*>::iterator it = shaderMap.find(vpath + fpath);
    Shader* shader;

    if(it == shaderMap.end())
    {
        shader = new Shader(vpath.c_str(), fpath.c_str());
        shaderMap.insert(std::pair<std::string, Shader*>(vpath + fpath, shader));
    }
    else
    {
        shader = it->second;
    }

    return shader;
}

Shader* ShaderStore::get(std::string vpath, std::string fpath)
{

    return shaderMap.find(vpath + fpath)->second;

}
