#version 400 core

// Portions of this shader source are found in/adapted from 
// the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 58

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

subroutine vec2 uvMode();
 
subroutine uniform uvMode getUV;

uniform mat4 MVP;
uniform mat4 ModelMatrix;

out vec2 UV;

subroutine(uvMode)
vec2 object(){
    return vertexUV;
}

subroutine(uvMode)
vec2 boundary_xy(){
    return (ModelMatrix * vec4(vertexPosition, 1.0)).xy/200.0f;
}

subroutine(uvMode)
vec2 boundary_yz(){
    return (ModelMatrix * vec4(vertexPosition, 1.0)).yz/200.0f;
}

subroutine(uvMode)
vec2 boundary_xz(){
    return (ModelMatrix * vec4(vertexPosition, 1.0)).xz/200.0f;
}

void main(){
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	UV = getUV();
}

