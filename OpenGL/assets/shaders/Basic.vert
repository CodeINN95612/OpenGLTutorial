#version 450 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec2 vTexCoords;

uniform mat4 uVistaProyeccion;
uniform float uEscala;

out vec2 iTexCoords;

void main(){

	gl_Position = uVistaProyeccion * vec4(vPosition * uEscala, 1.0f, 1.0f);
	iTexCoords = vTexCoords;

};