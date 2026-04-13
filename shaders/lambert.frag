#version 330 core

out vec4 pixelColor; //Output variable of the fragment shader. (Almost) final pixel color.

//Varying variables
in vec4 i_color;

void main(void) {
	pixelColor=i_color;
}
