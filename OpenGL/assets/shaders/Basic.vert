#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 iColor;

void main(){

	gl_Position = vec4(vPosition, 1.0f, 1.0f);

	iColor = vColor;

};