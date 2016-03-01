#version 330 core

layout(location = 0) in vec3 v_pos;

void main(){
    gl_Position.xyz = v_pos;
    gl_Position.w = 1.0;
}