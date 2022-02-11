#version 450 core

layout (location = 0) in vec2 vPosition;

uniform vec4 uColor;

out vec4 iColor;

void main(){

	gl_Position = vec4(vPosition, 1.0f, 1.0f);

	iColor = uColor;

};