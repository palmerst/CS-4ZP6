#include "include/GL/glew.h"
#include "Loader.h"
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>


bool checkSuccess(funcParam getParams, funcErr getError, GLuint handle){
    int status;
    getParams(handle, GL_COMPILE_STATUS, &status);
    if(status)
        return true;
    int errorLength;
    getParams(handle, GL_INFO_LOG_LENGTH, &errorLength);
    if ( errorLength > 0 ){
        std::vector<char> errorMessage(errorLength+1);
        getError(handle, errorLength, NULL, &errorMessage[0]);
        printf("%s\n", &errorMessage[0]);
    }
    exit(1);
}

GLuint compileShader(const char* sourceFileName, GLenum shaderType){

    if(shaderType == GL_VERTEX_SHADER)
        printf("Compiling vertex shader %s... ", sourceFileName);
    else if(shaderType == GL_FRAGMENT_SHADER)
        printf("Compiling fragment shader %s... ", sourceFileName);

    std::ifstream sourceFile(sourceFileName, std::ios::in);

    if(!sourceFile.is_open()){
        printf("Failed to open shader source %s\n", sourceFileName);
        exit(1);
    }

    std::string sourceString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());

    sourceFile.close();

    GLuint shaderHandle = glCreateShader(shaderType);

    const char* sourcePointer = sourceString.c_str();
    glShaderSource(shaderHandle, 1, &sourcePointer, NULL);
    glCompileShader(shaderHandle);

    checkSuccess(glGetShaderiv, glGetShaderInfoLog, shaderHandle);

    printf("DONE\n");

	return shaderHandle;
}


GLuint loadShaders(const char* vShader, const char* fShader){

    GLuint programHandle = glCreateProgram();

    GLuint vertexShaderHandle = compileShader(vShader, GL_VERTEX_SHADER);
    GLuint fragmentShaderHandle = compileShader(fShader, GL_FRAGMENT_SHADER);

    printf("Linking shader program... ");

	glAttachShader(programHandle, vertexShaderHandle);
	glAttachShader(programHandle, fragmentShaderHandle);
	glLinkProgram(programHandle);

	checkSuccess(glGetProgramiv, glGetProgramInfoLog, programHandle);

	glDeleteShader(vertexShaderHandle);
	glDeleteShader(fragmentShaderHandle);

	printf("DONE\n");

	return programHandle;
}


GLuint loadShaders(const char* vShader, const char* gShader, const char* fShader){

    GLuint programHandle = glCreateProgram();

    GLuint vertexShaderHandle = compileShader(vShader, GL_VERTEX_SHADER);
    GLuint geometryShaderHandle = compileShader(gShader, GL_GEOMETRY_SHADER);
    GLuint fragmentShaderHandle = compileShader(fShader, GL_FRAGMENT_SHADER);

	glAttachShader(programHandle, vertexShaderHandle);
	glAttachShader(programHandle, geometryShaderHandle);
	glAttachShader(programHandle, fragmentShaderHandle);
	glLinkProgram(programHandle);

	checkSuccess(glGetProgramiv, glGetProgramInfoLog, programHandle);

	glDeleteShader(vertexShaderHandle);
	glDeleteShader(geometryShaderHandle);
	glDeleteShader(fragmentShaderHandle);

	return programHandle;
}





