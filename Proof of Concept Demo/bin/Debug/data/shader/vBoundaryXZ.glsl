#version 330 core

// Portions of this shader source are found in/adapted from 
// the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 58

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;


uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 ModelViewMatrix;

out vec2 UV;
out float fogFactor;

void main(){
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	UV = (ModelMatrix * vec4(vertexPosition, 1.0)).xz/2000.0f;
    
    vec4 modelCoords = ModelMatrix*vec4(vertexPosition,1.0);
    
    float dist = abs(modelCoords.z);
	float fogMax = 5000;
	float fogMin = 3500;
	fogFactor = clamp((fogMax - dist)/(fogMax - fogMin), 0.0, 1.0);
}

