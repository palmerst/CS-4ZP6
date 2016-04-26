#version 330 core

// Portions of this shader source are found in/adapted from 
// the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 58

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec4 vertexTangent;

out vec2 UV;

uniform mat4 MVP;

void main(){
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	UV = vertexUV;	
}

