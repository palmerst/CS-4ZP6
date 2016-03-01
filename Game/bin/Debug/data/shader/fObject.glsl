#version 330 core

// This shader source is found in the OpenGL 4.0 Shading Language Cookbook by David Wolff pg 198-203

struct LightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};
uniform LightInfo Light;

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float shine;
};
uniform MaterialInfo Material;

uniform sampler2D Texture;
uniform sampler2D Bump;

in vec2 UV;
in vec3 s;
in vec3 v;

layout(location=0) out vec4 finalColor;


vec3 phongModel(vec3 norm, vec3 diffR) {
	vec3 r = reflect(-s, norm);
	vec3 ambient = Light.La * Material.Ka * diffR;
	float sDotN = max(dot(s,norm),0.0);
//	diffuse = Light.Ld * Material.Kd * sDotN;
	vec3 diffuse = Light.Ld * Material.Kd * sDotN * diffR;
	vec3 spec = vec3(0.0);
	if(sDotN > 0.0){
		spec = Light.Ls * Material.Ks * pow(max(dot(r,v),0.0), Material.shine);
	}
    
    return ambient + diffuse + spec;
}


void main()
{
    vec4 texColor = texture(Texture, UV).rgba;
	if(texColor.a == 0){
		discard;
	}
    vec4 normal = texture(Bump, UV).rgba;
	
	
    finalColor = vec4(phongModel(normal.rgb, texColor.rgb), 1.0);
}