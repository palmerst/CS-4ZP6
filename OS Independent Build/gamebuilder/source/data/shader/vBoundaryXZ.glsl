#version 330 core

// Portions of this shader source are found in/adapted from 
// the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 58

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec4 vertexTangent;


struct LightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo Light;

uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;
uniform mat3 ModelView3x3;


out vec2 UV;
//out vec3 normal;
out vec3 e;
out vec3 norm;
out vec3 binorm;
out vec3 tang;
out float fogFactor;

void main(){
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	UV = (ModelMatrix * vec4(vertexPosition, 1.0)).xz/1000.0f;
    
    norm = normalize(ModelView3x3*vertexNormal);
    tang = normalize(ModelView3x3*vec3(vertexTangent));
    binorm = normalize(cross(norm, tang)) * vertexTangent.w;
    
        
	e = normalize(vec3(ModelViewMatrix*vec4(vertexPosition, 1.0)));
    
    vec4 modelCoords = ModelMatrix*vec4(vertexPosition,1.0);
    
    float dist = abs(modelCoords.z);
	float fogMax = 5000;
	float fogMin = 3500;
	fogFactor = clamp((fogMax - dist)/(fogMax - fogMin), 0.0, 1.0);
}
