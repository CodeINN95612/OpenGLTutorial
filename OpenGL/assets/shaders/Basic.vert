#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoords;

uniform mat4 uProjection;
uniform float uScala;

out vec2 iTexCoords;

void main(){

	gl_Position = uProjection * vec4(vPosition * uScala, 1.0f, 1.0f);
	iTexCoords = vTexCoords;

};