#version 330 core

// This shader source is found in the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 198-203

in vec2 UV;
in float fogFactor;

layout(location=0) out vec4 finalColor;

uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = texture(myTextureSampler, UV).rgba;
	if(texColor.a == 0){
		discard;
	}
	
	vec4 fogColor = vec4(0.843, 0.796, 0.690, 0.0);
	
	finalColor = mix(fogColor, texColor, fogFactor);
}