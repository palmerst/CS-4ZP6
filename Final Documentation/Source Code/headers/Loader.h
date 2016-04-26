#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

typedef void __attribute__((__stdcall__)) (*funcParam)(GLuint, GLenum, GLint*);
typedef void __attribute__((__stdcall__)) (*funcErr)(GLuint, GLsizei, GLsizei*, GLchar*);

bool checkSuccess(funcParam, funcErr, GLuint, GLenum);
GLuint compileShader(const char*, GLenum);
GLuint loadShaders(const char*, const char*);
GLuint loadShaders(const char*, const char*, const char*);


#endif // LOADER_H_INCLUDED
