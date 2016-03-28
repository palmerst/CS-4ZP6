#include "ObjGPUDataStore.h"

ObjGPUDataStore::ObjGPUDataStore() {};

ObjGPUData* ObjGPUDataStore::add(std::string path, float angle, bool scalingMode)
{

    std::map<std::string, ObjGPUData*>::iterator it = gpuMap.find(path);
    ObjGPUData* gpuData;


    if(it == gpuMap.end())
    {
        gpuData = new ObjGPUData(path.c_str(), angle, scalingMode);
        gpuMap.insert(std::pair<std::string, ObjGPUData*>(path, gpuData));
    }
    else
    {
        gpuData = it->second;
    }

    return gpuData;

}

ObjGPUData* ObjGPUDataStore::get(std::string path)
{

    return gpuMap.find(path)->second;

}
