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

out vec2 UV;
out vec3 s;
out vec3 v;
out float fogFactor;

void main(){
	gl_Position =  MVP * vec4(vertexPosition, 1.0);
	UV = (ModelMatrix * vec4(vertexPosition, 1.0)).xz/1000.0f;
    
    vec3 norm = normalize(NormalMatrix * vertexNormal);
    vec3 tang = normalize(NormalMatrix * vec3(vertexTangent));
    vec3 binorm = normalize(cross(norm, tang)) * vertexTangent.w;
    mat3 toObjectLocal = mat3(
        tang.x, binorm.x, norm.x,
        tang.y, binorm.y, norm.y,
        tang.z, binorm.z, norm.z );
        
	vec3 eyeCoords = vec3(ModelViewMatrix*vec4(vertexPosition,1.0));
	s = normalize(toObjectLocal * (Light.Position.xyz - eyeCoords));
	v = toObjectLocal * normalize(-eyeCoords);
    
    vec4 modelCoords = ModelMatrix*vec4(vertexPosition,1.0);
    
    float dist = abs(modelCoords.z);
	float fogMax = 5000;
	float fogMin = 3500;
	fogFactor = clamp((fogMax - dist)/(fogMax - fogMin), 0.0, 1.0);
}

