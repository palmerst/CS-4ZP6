#ifndef SHADERSTORE_H_INCLUDED
#define SHADERSTORE_H_INCLUDED

#include <map>
#include "Shader.h"


/*! The ShaderStore class acts as a storage class for loaded shaders.
 */
class ShaderStore
{

private:

    std::map<std::string, Shader*> shaderMap; //!< Map translates sound file name to shader

public:

    //! Constructor
    ShaderStore();

    //! Adds a new shader to the store:  if not in the store, it loads and stores;  if already present, it does nothing
    /*!
      \param vpath Path to vertex shader
      \param fpath Path to fragment shader
    */
    Shader* add(std::string vpath, std::string fpath);

    //! Retrieves gpu data from the store
    /*!
      \param vpath Path to vertex shader
      \param fpath Path to fragment shader
    */
    Shader* get(std::string vpath, std::string fpath);

};

#endif // SHADERSTORE_H_INCLUDED
