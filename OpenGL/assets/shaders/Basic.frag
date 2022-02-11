#version 450 core

in vec3 iColor;

out vec4 fColor;

void main(){

	fColor = vec4(iColor, 1.0f);

}