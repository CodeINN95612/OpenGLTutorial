#version 450 core

in vec2 iTexCoords;

uniform sampler2D uTextura;
uniform vec4 uColor;

out vec4 fColor;

void main(){

	fColor = texture(uTextura, iTexCoords) * uColor;
}