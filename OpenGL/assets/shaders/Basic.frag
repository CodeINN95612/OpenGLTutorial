#version 450 core

in vec4 iColor;
in vec2 iTexCoords;

uniform sampler2D uTextura;

out vec4 fColor;

void main(){

	fColor = mix(texture(uTextura, iTexCoords), iColor, 0.1);

}