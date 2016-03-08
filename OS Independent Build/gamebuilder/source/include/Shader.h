#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include "GL/glew.h"

#include <map>
#include <string>


/*! The Shader class is used to build shaders.  All of the names/identifiers required to bind/use the shader afterwards are stored.
 */
class Shader
{

public:
    //! Shader constructor
    /*!
      \param vShader Vertex shader path
      \param fShader Fragment shader path
    */
    Shader(const char* vShader, const char* fShader);
    GLuint shaderProgram;  //!< Name to bind the shader program
    std::map<std::string, GLuint> uniformIDMap;  //!< Stores names which bind the shader uniform IDs

};

#endif // SHADER_H_INCLUDED
