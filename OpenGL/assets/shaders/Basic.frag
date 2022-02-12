#version 450 core

in vec2 iTexCoords;

uniform sampler2D uTextura;

out vec4 fColor;

void main(){

	fColor = texture(uTextura, iTexCoords);
}