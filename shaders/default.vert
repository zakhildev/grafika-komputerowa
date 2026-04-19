#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main()
{
  TexCoords = texCoords;
  FragPos = vec3(M * vec4(position, 1.0));
  Normal = mat3(transpose(inverse(M))) * normal;
  gl_Position = P * V * M * vec4(position, 1.0);
}