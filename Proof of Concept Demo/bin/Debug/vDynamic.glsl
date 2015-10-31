#version 330 core

layout(location = 0) in vec3 v_pos;

uniform mat4 MVP;

void main(){
    gl_Position.xyz = v_pos;
    gl_Position.w = 1.0;
    gl_Position = MVP*gl_Position;
}