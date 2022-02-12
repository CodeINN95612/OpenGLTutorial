#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoords;

uniform vec4 uColor;

out vec4 iColor;
out vec2 iTexCoords;

void main(){

	gl_Position = vec4(vPosition, 1.0f, 1.0f);

	iColor = uColor;
	iTexCoords = vTexCoords;

};