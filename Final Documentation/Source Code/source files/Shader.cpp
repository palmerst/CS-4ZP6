#include "Shader.h"
#include "Loader.h"
#include <iostream>

Shader::Shader(const char* vShader, const char* fShader)
{
    /*** Load the shaders and store handle ***/
    shaderProgram = loadShaders(vShader, fShader);

    GLint uniforms;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniforms);

    GLchar name[100];
    GLenum type;
    GLint size;
    GLsizei length;

    for(GLuint i = 0; i < uniforms; i++)
    {
        glGetActiveUniform(shaderProgram, i, 99, &length, &size, &type, name);

        std::string uniformName(name);

        uniformIDMap.insert(std::pair<std::string, GLuint>(uniformName, glGetUniformLocation(shaderProgram, name)));
    }
}
