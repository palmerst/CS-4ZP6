#version 330 core

// This shader source is found in the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 198-203

in vec2 UV;

layout(location=0) out vec4 finalColor;

uniform sampler2D myTextureSampler;

void main()
{
	finalColor = texture(myTextureSampler, UV).rgba;
}