#version 400 core

// This shader source is found in the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 198-203

in vec2 UV;

layout(location=0) out vec4 finalColor;

uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = texture(myTextureSampler, UV).rgba;
	if(texColor.a == 0){
		discard;
	}
	
	finalColor = texColor;
}