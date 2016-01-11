#include "Shader.h"
#include "Loader.h"
#include <iostream>

Shader::Shader(const char* vShader, const char* fShader){
    /*** Load the shaders and store handle ***/
    shaderProgram = loadShaders(vShader, fShader);

    GLint uniforms;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &uniforms);

    GLchar name[100];
    GLenum type;
    GLint size;
    GLsizei length;

    for(GLuint i = 0; i < uniforms; i++){
        glGetActiveUniform(shaderProgram, i, 99, &length, &size, &type, name);

        std::string uniformName(name);

        uniformIDMap.insert(std::pair<std::string, GLuint>(uniformName, glGetUniformLocation(shaderProgram, name)));
    }

}

//
//    /*** Associate identifiers with locations in shader ***/
//	MVP_ID = glGetUniformLocation(shaderProgram, "MVP");
//    MV_ID = glGetUniformLocation(shaderProgram, "ModelViewMatrix");
//    M_ID = glGetUniformLocation(shaderProgram, "ModelMatrix");
//    P_ID = glGetUniformLocation(shaderProgram, "ProjectionMatrix");
//    N_ID = glGetUniformLocation(shaderProgram, "NormalMatrix");
//    MTL_KA_ID = glGetUniformLocation(shaderProgram, "Material.Ka");
//    MTL_KD_ID = glGetUniformLocation(shaderProgram, "Material.Kd");
//    MTL_KS_ID = glGetUniformLocation(shaderProgram, "Material.Ks");
//    MTL_SHINE_ID = glGetUniformLocation(shaderProgram, "Material.shine");
//    LPOS_ID = glGetUniformLocation(shaderProgram, "Light.Position");
//    LA_ID = glGetUniformLocation(shaderProgram, "Light.La");
//    LD_ID = glGetUniformLocation(shaderProgram, "Light.Ld");
//    LS_ID = glGetUniformLocation(shaderProgram, "Light.Ls");
//    texture_ID = glGetUniformLocation(shaderProgram, "myTextureSampler");
//    subroutine_object = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "object");
//    subroutine_boundary_xy = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xy");
//    subroutine_boundary_yz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_yz");
//    subroutine_boundary_xz = glGetSubroutineIndex(shaderProgram, GL_VERTEX_SHADER, "boundary_xz");
