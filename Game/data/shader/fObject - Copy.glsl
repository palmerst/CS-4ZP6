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
in vec3 normal;
in vec3 e;

//in vec3 s;
//in vec3 v;

layout(location=0) out vec4 finalColor;


//vec3 phongModel(vec3 norm, vec3 diffR) {
//	vec3 r = reflect(-s, norm);
//	vec3 ambient = Light.La * Material.Ka * diffR;
//	float sDotN = max(dot(s,norm),0.0);
//	diffuse = Light.Ld * Material.Kd * sDotN;
//	vec3 diffuse = Light.Ld * Material.Kd * sDotN * diffR;
//	vec3 spec = vec3(0.0);
//	if(sDotN > 0.0){
//		spec = Light.Ls * Material.Ks * pow(max(dot(r,v),0.0), Material.shine);
//	}
 //   
  //  return max(ambient, diffuse + spec);
//}

vec3 phongModel(vec3 color){
    vec3 spec = vec3(0.0);
    
    vec3 n = normalize(normal);
    vec3 lDir = normalize(Light.Position.xyz);
    vec3 r = normalize(reflect(lDir, n));
    
    float intensity = max(dot(n, lDir), 0.0);
    
    if(intensity > 0.0){
        float intSpec = max(dot(r,e),0.0);
        spec = Material.Ks * pow(intSpec, Material.shine);
    }
    
    return color*vec3(intensity)*Light.Ld + spec + color*Light.La;
}

void main()
{
    vec4 texColor = texture(Texture, UV).rgba;
	if(texColor.a == 0){
		discard;
	}
    vec3 texNormal = normalize(texture(Bump, UV).rgb*2.0 - 1.0);
	
	finalColor = vec4(phongModel(texColor.rgb), 1.0);
   // finalColor = vec4(phongModel(normal.rgb, texColor.rgb), 1.0);
}