#version 330 core

// This shader source is found in the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 198-203

in vec2 UV;

layout(location=0) out vec4 finalColor;

uniform sampler2D Texture;

void main()
{
	finalColor = texture(Texture, UV).rgba;
}