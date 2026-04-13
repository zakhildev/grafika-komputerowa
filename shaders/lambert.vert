#version 330 core

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 color=vec4(1,1,1,1);
uniform vec4 lightDir=vec4(0,0,1,0);

//Attributes
layout (location=0) in vec4 vertex; //vertex coordinates in model space
layout (location=1) in vec3 normal; //vertex normal vector in model space

//varying variables
out vec4 i_color;

void main(void) {
  gl_Position=P*V*M*vertex;

  mat4 G=mat4(inverse(transpose(mat3(M))));
  vec4 n=normalize(V * G * vec4(normal.xyz, 0.0));

  float nl=clamp(dot(n, normalize(lightDir)), 0.0, 1.0);
  float ambient = 0.2;

  i_color=vec4(color.rgb * clamp(nl + ambient, 0.0, 1.0), color.a);
}
