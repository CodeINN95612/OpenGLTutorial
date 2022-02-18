#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoords;

uniform mat4 uMVP;

out vec2 iTexCoords;

void main(){

	gl_Position = uMVP * vec4(vPosition * 10.0f, 1.0f, 1.0f);
	iTexCoords = vTexCoords;

};