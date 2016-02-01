#ifndef OBJGPUDATASTORE_H_INCLUDED
#define OBJGPUDATASTORE_H_INCLUDED

#include <map>
#include "ObjGPUData.h"

class ObjGPUDataStore{

    private:

        std::map<std::string, ObjGPUData*> gpuMap;

    public:

        ObjGPUDataStore();

        ObjGPUData* add(std::string path, float angle = 0.0);
        ObjGPUData* get(std::string path);

};

#endif // OBJGPUDATASTORE_H_INCLUDED
