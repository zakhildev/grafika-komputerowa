#version 330 core

out vec4 pixelColor; //Output variable of the fragment shader. (Almost) final pixel color.

in vec4 i_c;

void main(void) {
	pixelColor=i_c;
}
