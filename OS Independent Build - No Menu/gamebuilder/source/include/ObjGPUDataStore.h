#ifndef OBJGPUDATASTORE_H_INCLUDED
#define OBJGPUDATASTORE_H_INCLUDED

#include <map>
#include "ObjGPUData.h"


/*! The ObjGPUDataStore class acts as a storage class for loaded object mesh/texture data.
 */
class ObjGPUDataStore
{

private:


    std::map<std::string, ObjGPUData*> gpuMap;  //!< Map translates object file name to stored data

public:

    //! Constructor.
    ObjGPUDataStore();

    //! Adds a new mesh/texture to the store:  if not in the store, it loads and stores;  if already present, it does nothing
    /*!
      \param path Path to object file
      \param angle Initial y-axis rotation in radians (optional:  default 0.0)
      \param scalingMode Flag specifies if object should be scaled to unit height when loaded (default true)
    */
    ObjGPUData* add(std::string path, float angle = 0.0, bool scalingMode = true);

    //! Retrieves gpu data from the store
    /*!
      \param path Path to object file to search for
    */
    ObjGPUData* get(std::string path);

};

#endif // OBJGPUDATASTORE_H_INCLUDED
